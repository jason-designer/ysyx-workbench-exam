import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import scala.math._

trait CacheParameters {
    val OffsetWidth     = 5     // SoC的sram限制，不可更改
    val IndexWidth      = 6     // SoC的sram限制，不可更改
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


/******************************************/
class SRamIO extends Bundle{
    val addr    = Output(UInt(6.W))
    val cen     = Output(Bool())
    val wen     = Output(Bool())
    val wmask   = Output(UInt(128.W))
    val wdata   = Output(UInt(128.W))
    val rdata   = Input(UInt(128.W))
}

class SRam_1k extends BlackBox with HasBlackBoxInline{
    val io = IO(new Bundle{
        val CLK     = Input(Clock())
        val A       = Input(UInt(6.W))
        val CEN     = Input(Bool())
        val WEN     = Input(Bool())
        val BWEN    = Input(UInt(128.W))
        val D       = Input(UInt(128.W))
        val Q       = Output(UInt(128.W))
    })

    setInline("SRam_1k.v",
            """
           |
           |     module SRam_1k(
           |        Q, CLK, CEN, WEN, BWEN, A, D
           |     );
           |     parameter Bits = 128;
           |     parameter Word_Depth = 64;
           |     parameter Add_Width = 6;
           |     parameter Wen_Width = 128;
           |
           |     output reg [Bits-1:0] Q;
           |     input                 CLK;
           |     input                 CEN;
           |     input                 WEN;
           |     input [Wen_Width-1:0] BWEN;
           |     input [Add_Width-1:0] A;
           |     input [Bits-1:0]      D;
           |
           |     wire cen  = ~CEN;
           |     wire wen  = ~WEN;
           |     wire [Wen_Width-1:0] bwen = ~BWEN;
           |
           |     reg [Bits-1:0] ram [0:Word_Depth-1];
           |     always @(posedge CLK) begin
           |         if(cen && wen) begin
           |             ram[A] <= (D & bwen) | (ram[A] & ~bwen);
           |         end
           |         Q <= cen && !wen ? ram[A] : {4{$random}};
           |     end
           |
           |     endmodule
           |
            """.stripMargin)
}

class SRamIO_2k extends Bundle{
    val addr    = Output(UInt(6.W))
    val cen     = Output(Bool())
    val wen     = Output(Bool())
    val wmask   = Output(UInt(256.W))
    val wdata   = Output(UInt(256.W))
    val rdata   = Input(UInt(256.W))
}

class SRam_2k extends Module{
    val io = IO(Flipped(new SRamIO_2k))

    val sram0 = Module(new SRam_1k)
    val sram1 = Module(new SRam_1k)
    sram0.io.CLK    := clock
    sram0.io.A      := io.addr
    sram0.io.CEN    := false.B              // ysyx给的sram的逻辑是反的
    sram0.io.WEN    := ~io.wen              // ysyx给的sram的逻辑是反的
    sram0.io.BWEN   := ~io.wmask(127, 0)    // ysyx给的sram的逻辑是反的
    sram0.io.D      := io.wdata(127, 0)

    sram1.io.CLK    := clock
    sram1.io.A      := io.addr
    sram1.io.CEN    := false.B              // ysyx给的sram的逻辑是反的
    sram1.io.WEN    := ~io.wen              // ysyx给的sram的逻辑是反的
    sram1.io.BWEN   := ~io.wmask(255, 128)  // ysyx给的sram的逻辑是反的
    sram1.io.D      := io.wdata(255, 128)


    // 读保持功能
    val rdata = Cat(sram1.io.Q, sram0.io.Q)
    val data_stay = RegInit(0.U(256.W))

    val idle :: stop :: stay :: Nil = Enum(3)
    val state = RegInit(idle)
    switch(state){
        is(idle){
            when(!io.cen){state := stop}
        }
        is(stop){
            state := Mux(io.cen, idle, stay)
        }
        is(stay){
            when(io.cen){state := idle}
        }
    }
    data_stay := Mux(state === stop, rdata, data_stay)
    io.rdata := Mux(state === stay, data_stay, rdata)
}


// 1.同步icache.当en的时候会把操作数都保存到寄存器内，并开始取值。
// 若发生miss，icache会通过axi取值，此时会输出的ok为false，这
// 时即使输入的en为true也不会接受新的input请求
// 2.icache初始化时ok为true，此时data并非为有效值，只是为了避免core进入stall状态
// class ICache extends Module with CacheParameters{
//     val io = IO(new Bundle{
//         val imem    = new ICacheIO
//         val axi     = new ICacheAxiIO
//         val fence   = Flipped(new FenceIO)
//     })
//     // addr reg
//     val addr = RegEnable(io.imem.addr, 0.U(64.W), io.imem.en && io.imem.ok)

//     // addr
//     val tag_addr    = addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
//     val index_addr  = addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
//     val offset_addr = addr(OffsetWidth - 1, 0)
//     // cache data
//     val v1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val age1    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val tag1    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
//     val block1  = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(CacheLineWidth.W))))
//     val v2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val age2    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val tag2    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
//     val block2  = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(CacheLineWidth.W))))
//     // cacheway output
//     val hit1    = tag_addr === tag1(index_addr) && v1(index_addr) === true.B
//     val hit2    = tag_addr === tag2(index_addr) && v2(index_addr) === true.B
//     val data1   = (block1(index_addr) >> (offset_addr << 3))(31, 0)
//     val data2   = (block2(index_addr) >> (offset_addr << 3))(31, 0)
//     //
//     val hit     = hit1 || hit2
//     val data    = Mux(hit2, data2, Mux(hit1, data1, 0.U))   // 两个都hit就随便取一个,按理说不会两个都hit
//     // update age
//     // 当hit1和hit2的值不同时，age才需要发生改变
//     age1(index_addr) := Mux(hit1 ^ hit2, hit1, age1(index_addr))
//     age2(index_addr) := Mux(hit1 ^ hit2, hit2, age2(index_addr))
//     //state machine define
//     val idle :: miss :: clear_block1 :: clear_block2 :: Nil = Enum(4)
//     val state = RegInit(idle)

//     // icache output
//     val not_en_yet  = RegInit(true.B)                       // 用于复位后让icache输出ok，避免进入stall
//     not_en_yet      := Mux(io.imem.en, false.B, not_en_yet) // 复位后在en没来前还需要保持state的idle状态

//     io.imem.data    := data
//     io.imem.ok      := (hit || not_en_yet) && state === idle 

//     val fence_cnt = RegInit(0.U(IndexWidth.W))
//     switch(state){
//         is(idle){
//             when(io.fence.req){state := clear_block1}
//             .elsewhen(!hit && !not_en_yet){state := miss}
//         }
//         is(miss){
//             when(io.axi.valid) {state := idle}
//         }
//         is(clear_block1){
//             when(fence_cnt === (CacheLineNum - 1).U){state := clear_block2}
//         }
//         is(clear_block2){
//             when(fence_cnt === (CacheLineNum - 1).U){state := idle}
//         }
//     }

//     //axi request signals
//     io.axi.req    := state === miss
//     io.axi.addr   := addr & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))

//     // update cache data
//     val age = Cat(age2(index_addr), age1(index_addr))
//     val updateway2 = age === "b01".U    
//     val updateway1 = !updateway2        // 特殊情况都默认换掉way1
//     val update = state === miss && io.axi.valid
//     block1(index_addr)   := Mux(update && updateway1, io.axi.data, block1(index_addr))
//     tag1(index_addr)     := Mux(update && updateway1, tag_addr, tag1(index_addr))
//     v1(index_addr)       := Mux(update && updateway1, true.B, v1(index_addr))
//     block2(index_addr)   := Mux(update && updateway2, io.axi.data, block2(index_addr))
//     tag2(index_addr)     := Mux(update && updateway2, tag_addr, tag2(index_addr))
//     v2(index_addr)       := Mux(update && updateway2, true.B, v2(index_addr))

//     10when(state === clear_block1)    {v1(fence_cnt) := false.B}
//     .elsewhen(update && updateway1) {v1(index_addr) := true.B}
//     when(state === clear_block2)    {v2(fence_cnt) := false.B}
//     .elsewhen(update && updateway2) {v2(index_addr) := true.B}

//     // fence_cnt
//     when(state === clear_block1 || state === clear_block2){fence_cnt := fence_cnt + 1.U}
//     .otherwise{fence_cnt := 0.U}
    
//     // fence output
//     io.fence.done := fence_cnt === (CacheLineNum - 1).U && state === clear_block2
// }



class ICache extends Module with CacheParameters{
    val io = IO(new Bundle{
        val imem    = new ICacheIO
        val axi     = new ICacheAxiIO
        val fence   = Flipped(new FenceIO)
    })
    io.fence.done := false.B

    // addr
    val tag_addr    = io.imem.addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr  = io.imem.addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr = io.imem.addr(OffsetWidth - 1, 0)
    // cache data
    val v1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age1    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag1    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val sram1   = Module(new SRam_2k)
    val block1  = sram1.io
    val v2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age2    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag2    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val sram2   = Module(new SRam_2k)
    val block2  = sram2.io
    
    //state machine define
    val idle :: fetch :: update :: update_done :: Nil = Enum(4)
    val state = RegInit(idle)
    val miss  = Wire(Bool())

    switch(state){
        is(idle){
            when(miss && io.imem.en){state := fetch}
        }
        is(fetch){
            when(io.axi.valid) {state := update}
        }
        is(update){
            state := update_done
        }
        is(update_done){
            state := idle
        }
    }

    // cacheway info

    val addr_stay = RegEnable(io.imem.addr, 0.U(64.W), state === idle && io.imem.en)    // addr保存
    val tag_addr_stay       = addr_stay(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr_stay     = addr_stay(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr_stay    = addr_stay(OffsetWidth - 1, 0)


    val hit1    = tag_addr === tag1(index_addr) && v1(index_addr) === true.B
    val hit2    = tag_addr === tag2(index_addr) && v2(index_addr) === true.B
    miss        := !(hit1 || hit2)


    val hit1_stay = tag_addr_stay === tag1(index_addr_stay) && v1(index_addr_stay) === true.B
    val hit2_stay = tag_addr_stay === tag2(index_addr_stay) && v2(index_addr_stay) === true.B
    val data1   = (block1.rdata >> (offset_addr_stay << 3))(31, 0)
    val data2   = (block2.rdata >> (offset_addr_stay << 3))(31, 0)
    val data    = Mux(hit2_stay, data2, Mux(hit1_stay, data1, 0.U))                     // 两个都hit就随便取一个,按理说不会两个都hit


    // cache output
    io.imem.data := Mux(state === idle, data, 0.U)
    io.imem.ok   := state === idle

    // AXI output
    io.axi.req  := state === fetch
    io.axi.addr := addr_stay & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))
    val axi_buffer = RegEnable(io.axi.data, 0.U(CacheLineWidth.W), (state === fetch) && io.axi.valid)

    // update age
    // 当hit1和hit2的值不同时，age才需要发生改变
    when((state === idle) && (hit1 ^ hit2) && io.imem.en){
        age1(index_addr) := hit1
        age2(index_addr) := hit2
    }
    
    // choose which way to update
    val age = Cat(age2(addr_stay), age1(addr_stay))
    val updateway2 = age === "b01".U    
    val updateway1 = !updateway2        // 特殊情况都默认换掉way1

    // sram io
    when(state === idle && io.imem.en){
        block1.addr := index_addr
        block2.addr := index_addr
    }
    .elsewhen((state === idle && !io.imem.en) || state === update || state === update_done){
        block1.addr := index_addr_stay
        block2.addr := index_addr_stay
    }
    .otherwise{
        block1.addr := 0.U
        block2.addr := 0.U
    }
    block1.cen  := !(state === idle && !io.imem.en)
    block1.wen  := state === update && updateway1
    block1.wdata := axi_buffer
    block1.wmask := Fill(CacheLineWidth, 1.U)
    block2.cen  := !(state === idle && !io.imem.en)
    block2.wen  := state === update && updateway2
    block2.wdata := axi_buffer
    block2.wmask := Fill(CacheLineWidth, 1.U)
    // v and tag
    when(state === update && updateway1){
        tag1(index_addr_stay) := tag_addr_stay
        v1(index_addr_stay)   := true.B
    }
    when(state === update && updateway2){
        tag2(index_addr_stay) := tag_addr_stay
        v2(index_addr_stay)   := true.B
    }
}