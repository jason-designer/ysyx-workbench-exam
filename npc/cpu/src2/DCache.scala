import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import scala.math._


class DCacheIO extends Bundle{
    val en          = Input(Bool())
    val op          = Input(Bool())         // 0表示读操作，1表示写操作
    val addr        = Input(UInt(64.W)) 
    val wdata       = Input(UInt(64.W))     // 8字节对齐
    val wmask       = Input(UInt(8.W))      // 8字节对齐
    val transfer    = Input(UInt(32.W))     // 用于外设访问，部分外设需要指定transfer宽度
    val ok          = Output(Bool())
    val rdata       = Output(UInt(64.W))
}

class DCacheAxiIO extends Bundle with CacheParameters{
    val req     = Output(Bool())
    val raddr   = Output(UInt(64.W))
    val rvalid  = Input(Bool())
    val rdata   = Input(UInt(CacheLineWidth.W))

    val weq     = Output(Bool())
    val waddr   = Output(UInt(64.W))
    val wdata   = Output(UInt(CacheLineWidth.W))
    val wdone   = Input(Bool())
}

// 同步dcache.当en的时候会把操作数都保存到寄存器内，并开始取值。
// 若发生miss，dcache会通过axi取值，此时会输出的ok为false，这
// 时即使输入的en为true也不会接受新的input请求
// dcache输入的地址要求是8对齐.
class DCache extends Module with CacheParameters{
    val io = IO(new Bundle{
        val dmem    = new DCacheIO
        val axi     = new DCacheAxiIO
        val fence   = Flipped(new FenceIO)
    })
    // input reg
    // 当en为ture且dcache不处于busy状态（也就是输出ok）时才可以改变
    val op      = RegEnable(io.dmem.op,    false.B,   io.dmem.en && io.dmem.ok)
    val addr    = RegEnable(io.dmem.addr & "hfffffffffffffff8".U,  0.U(64.W), io.dmem.en && io.dmem.ok) // 地址8对齐
    val wdata   = RegEnable(io.dmem.wdata, 0.U(64.W), io.dmem.en && io.dmem.ok)
    val wmask   = RegEnable(io.dmem.wmask, 0.U(8.W),  io.dmem.en && io.dmem.ok)

    // addr
    val tag_addr    = addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr  = addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr = addr(OffsetWidth - 1, 0)
    // cache data
    val v1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val d1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age1    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag1    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val block1  = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(CacheLineWidth.W))))
    val v2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val d2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age2    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag2    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val block2  = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(CacheLineWidth.W))))
    // cacheway output
    val hit1    = tag_addr === tag1(index_addr) && v1(index_addr) === true.B
    val hit2    = tag_addr === tag2(index_addr) && v2(index_addr) === true.B
    val rdata1  = (block1(index_addr) >> (offset_addr << 3))(63, 0)
    val rdata2  = (block2(index_addr) >> (offset_addr << 3))(63, 0)
    // state machine define
    val idle :: write_back :: fetch_data :: write_block1 :: block1_written :: write_block2 :: block2_written ::Nil = Enum(7)
    val state = RegInit(idle)
    // cache output
    val hit         = hit1 || hit2
    val rdata       = Mux(hit2, rdata2, Mux(hit1, rdata1, 0.U))     // 两个都hit就随便取一个,按理说不会两个都hit

    val not_en_yet  = RegInit(true.B)                       // 用于复位后让dcache输出ok，避免进入stall_all
    not_en_yet      := Mux(io.dmem.en, false.B, not_en_yet) // 复位后在en没来前还需要保持state的idle状态
    
    io.dmem.rdata   := rdata 
    io.dmem.ok      := (hit || not_en_yet) && state === idle
    // update age
    // 当en且hit1和hit2的值不同时，age才需要发生改变
    age1(index_addr) := Mux((hit1 ^ hit2), hit1, age1(index_addr))
    age2(index_addr) := Mux((hit1 ^ hit2), hit2, age2(index_addr))

    // state machine
    val age         = Cat(age2(index_addr), age1(index_addr))
    val updateway2  = age === "b01".U    
    val updateway1  = !updateway2        // 特殊情况都默认换掉way1
    val miss        = !hit
    val dirty       = Mux(updateway1, d1(index_addr), d2(index_addr))
    // 
    val fence_cnt = RegInit(0.U(IndexWidth.W))
    switch(state){
        is(idle){
            when(io.fence.req){state := write_block1}
            .elsewhen(miss && !not_en_yet){state := Mux(dirty, write_back, fetch_data)}
        }
        is(write_back){
            when(io.axi.wdone) {state := fetch_data}
        }
        is(fetch_data){
            when(io.axi.rvalid) {state := idle}
        }
        is(write_block1){
            when(d1(fence_cnt) === false.B || (d1(fence_cnt) === true.B && io.axi.wdone)) {state := block1_written}
        }
        is(block1_written){
            when(fence_cnt === (CacheLineNum - 1).U) {state := write_block2}
            .otherwise {state := write_block1}
        }
        is(write_block2){
            when(d2(fence_cnt) === false.B || (d2(fence_cnt) === true.B && io.axi.wdone)) {state := block2_written}
        }
        is(block2_written){
            when(fence_cnt === (CacheLineNum - 1).U) {state := idle}
            .otherwise {state := write_block2}
        }
    }

    // update dirty
    // 按理说不会两个都hit，所以这里不考虑两个都hit的情况
    val update = state === fetch_data && io.axi.rvalid
    val way1write = hit1 && op
    val way2write = hit2 && op 
    // d1(index_addr) := Mux(update && updateway1, false.B, Mux(way1write, true.B, d1(index_addr)))
    // d2(index_addr) := Mux(update && updateway2, false.B, Mux(way2write, true.B, d2(index_addr)))
    when(state === block1_written){d1(fence_cnt) := false.B}
    .elsewhen(update && updateway1){d1(index_addr) := false.B}
    .elsewhen(way1write){d1(index_addr) := true.B}

    when(state === block2_written){d2(fence_cnt) := false.B}
    .elsewhen(update && updateway2){d2(index_addr) := false.B}
    .elsewhen(way2write){d2(index_addr) := true.B}
    // update cache data
    // block after write data
    val wm = wmask
    val mask64 = Cat(0.U((CacheLineWidth - 64).W),Fill(8,wm(7)),Fill(8,wm(6)),Fill(8,wm(5)),Fill(8,wm(4)),Fill(8,wm(3)),Fill(8,wm(2)),Fill(8,wm(1)),Fill(8,wm(0)))
    val blockmask = (mask64 << ((offset_addr >> 3) << 6))(CacheLineWidth-1, 0)
    val blockwdata = (wdata << ((offset_addr >> 3) << 6))(CacheLineWidth-1, 0)
    val block1_after_write = (block1(index_addr) & (~blockmask)) | (blockmask & blockwdata)
    val block2_after_write = (block2(index_addr) & (~blockmask)) | (blockmask & blockwdata)
    
    // block 若要替换则更新数据，否则看是否需要写入，要写入就写入，不写入就维持原值
    block1(index_addr)   := Mux(update && updateway1, io.axi.rdata, Mux(way1write, block1_after_write, block1(index_addr)))
    tag1(index_addr)     := Mux(update && updateway1, tag_addr, tag1(index_addr))
    v1(index_addr)       := Mux(update && updateway1, true.B, v1(index_addr))
    block2(index_addr)   := Mux(update && updateway2, io.axi.rdata, Mux(way2write, block2_after_write, block2(index_addr)))
    tag2(index_addr)     := Mux(update && updateway2, tag_addr, tag2(index_addr))
    v2(index_addr)       := Mux(update && updateway2, true.B, v2(index_addr))

    // axi request signals
    io.axi.req      := state === fetch_data
    io.axi.raddr    := addr & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))
    // io.axi.weq      := state === write_back
    // io.axi.waddr    := Cat(Mux(updateway1, tag1(index_addr), tag2(index_addr)), index_addr, 0.U(OffsetWidth.W)) 
    // io.axi.wdata    := Mux(updateway1, block1(index_addr), block2(index_addr))

    when(state === write_block1 && d1(fence_cnt)){
        io.axi.weq      := true.B 
        io.axi.waddr    := Cat(tag1(fence_cnt), fence_cnt, 0.U(OffsetWidth.W)) 
        io.axi.wdata    := block1(fence_cnt)
    }
    .elsewhen(state === write_block2 && d2(fence_cnt)){
        io.axi.weq      := true.B 
        io.axi.waddr    := Cat(tag2(fence_cnt), fence_cnt, 0.U(OffsetWidth.W)) 
        io.axi.wdata    := block2(fence_cnt)
    }
    .elsewhen(state === write_back){
        io.axi.weq      := state === write_back
        io.axi.waddr    := Cat(Mux(updateway1, tag1(index_addr), tag2(index_addr)), index_addr, 0.U(OffsetWidth.W)) 
        io.axi.wdata    := Mux(updateway1, block1(index_addr), block2(index_addr))
    }
    .otherwise{
        io.axi.weq      := false.B
        io.axi.waddr    := 0.U
        io.axi.wdata    := 0.U
    }

    // fence_cnt
    // 从block1_written到write_block2不需要清零，因为fence_cnt的位宽是与index位宽一致，它加1会自动清零
    when(state === block1_written || state === block2_written){fence_cnt := fence_cnt + 1.U}
    .elsewhen(state === write_block1 || state === write_block2){fence_cnt := fence_cnt}
    .otherwise{fence_cnt := 0.U}

    // fence output
    io.fence.done := state === block2_written && fence_cnt === (CacheLineNum - 1).U
}


