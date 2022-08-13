import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import scala.math._

trait CacheParameters {
    val OffsetWidth     = 6     // 这个大于3，因为dcache写入的最低单位是64位。
                                // 因为后面的axi的transfer大小设为了4Byte（这个条件要求它>=2）
    val IndexWidth      = 5
    val TagWidth        = 64 - OffsetWidth - IndexWidth // 三个数之和为64

    val CacheWay        = 2

    val CacheLineNum    = scala.math.pow(2, IndexWidth).toInt
    val CacheLineByte   = scala.math.pow(2, OffsetWidth).toInt
    val CacheLineWidth  = CacheLineByte * 8
    val AxiArLen        = scala.math.pow(2, (OffsetWidth - 3)).toInt
}

class ICacheIO extends Bundle{
    val addr        = Input(UInt(64.W))
    val en          = Input(Bool())
    val data        = Output(UInt(32.W))
    val ok          = Output(Bool())
}

class ICacheAxiIO extends Bundle with CacheParameters{
    val req     = Output(Bool())
    val addr    = Output(UInt(64.W))
    val valid   = Input(Bool())
    val data    = Input(UInt(CacheLineWidth.W))
}


// 1.同步icache.当en的时候会把操作数都保存到寄存器内，并开始取值。
// 若发生miss，icache会通过axi取值，此时会输出的ok为false，这
// 时即使输入的en为true也不会接受新的input请求
// 2.icache初始化时ok为true，此时data并非为有效值，只是为了避免core进入stall状态
class ICache extends Module with CacheParameters{
    val io = IO(new Bundle{
        val imem    = new ICacheIO
        val axi     = new ICacheAxiIO
        val fence   = Flipped(new FenceIO)
    })
    // addr reg
    val addr = RegEnable(io.imem.addr, 0.U(64.W), io.imem.en && io.imem.ok)

    // addr
    val tag_addr    = addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr  = addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr = addr(OffsetWidth - 1, 0)
    // cache data
    val v1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age1    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag1    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val block1  = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(CacheLineWidth.W))))
    val v2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age2    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag2    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val block2  = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(CacheLineWidth.W))))
    // cacheway output
    val hit1    = tag_addr === tag1(index_addr) && v1(index_addr) === true.B
    val hit2    = tag_addr === tag2(index_addr) && v2(index_addr) === true.B
    val data1   = (block1(index_addr) >> (offset_addr << 3))(31, 0)
    val data2   = (block2(index_addr) >> (offset_addr << 3))(31, 0)
    //
    val hit     = hit1 || hit2
    val data    = Mux(hit2, data2, Mux(hit1, data1, 0.U))   // 两个都hit就随便取一个,按理说不会两个都hit
    // update age
    // 当hit1和hit2的值不同时，age才需要发生改变
    age1(index_addr) := Mux(hit1 ^ hit2, hit1, age1(index_addr))
    age2(index_addr) := Mux(hit1 ^ hit2, hit2, age2(index_addr))
    //state machine define
    val idle :: miss :: clear_block1 :: clear_block2 :: Nil = Enum(4)
    val state = RegInit(idle)

    // icache output
    val not_en_yet  = RegInit(true.B)                       // 用于复位后让icache输出ok，避免进入stall
    not_en_yet      := Mux(io.imem.en, false.B, not_en_yet) // 复位后在en没来前还需要保持state的idle状态

    io.imem.data    := data
    io.imem.ok      := (hit || not_en_yet) && state === idle 

    val fence_cnt = RegInit(0.U(IndexWidth.W))
    switch(state){
        is(idle){
            when(io.fence.req){state := clear_block1}
            .elsewhen(!hit && !not_en_yet){state := miss}
        }
        is(miss){
            when(io.axi.valid) {state := idle}
        }
        is(clear_block1){
            when(fence_cnt === (CacheLineNum - 1).U){state := clear_block2}
        }
        is(clear_block2){
            when(fence_cnt === (CacheLineNum - 1).U){state := idle}
        }
    }

    //axi request signals
    io.axi.req    := state === miss
    io.axi.addr   := addr & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))

    // update cache data
    val age = Cat(age2(index_addr), age1(index_addr))
    val updateway2 = age === "b01".U    
    val updateway1 = !updateway2        // 特殊情况都默认换掉way1
    val update = state === miss && io.axi.valid
    block1(index_addr)   := Mux(update && updateway1, io.axi.data, block1(index_addr))
    tag1(index_addr)     := Mux(update && updateway1, tag_addr, tag1(index_addr))
    v1(index_addr)       := Mux(update && updateway1, true.B, v1(index_addr))
    block2(index_addr)   := Mux(update && updateway2, io.axi.data, block2(index_addr))
    tag2(index_addr)     := Mux(update && updateway2, tag_addr, tag2(index_addr))
    v2(index_addr)       := Mux(update && updateway2, true.B, v2(index_addr))

    when(state === clear_block1)    {v1(fence_cnt) := false.B}
    .elsewhen(update && updateway1) {v1(index_addr) := true.B}
    when(state === clear_block2)    {v2(fence_cnt) := false.B}
    .elsewhen(update && updateway2) {v2(index_addr) := true.B}

    // fence_cnt
    when(state === clear_block1 || state === clear_block2){fence_cnt := fence_cnt + 1.U}
    .otherwise{fence_cnt := 0.U}
    
    // fence output
    io.fence.done := fence_cnt === (CacheLineNum - 1).U && state === clear_block2
}



