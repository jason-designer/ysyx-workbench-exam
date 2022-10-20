import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import scala.math._

trait CacheParameters {
    val OffsetWidth     = 6     // SoC的sram限制，不可更改
    val IndexWidth      = 6     // SoC的sram限制，不可更改
    val TagWidth        = 64 - OffsetWidth - IndexWidth // 三个数之和为64

    val CacheWay        = 1

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

class SRam extends BlackBox with HasBlackBoxInline{
    val io = IO(new Bundle{
        val CLK     = Input(Clock())
        val A       = Input(UInt(6.W))
        val CEN     = Input(Bool())
        val WEN     = Input(Bool())
        val BWEN    = Input(UInt(128.W))
        val D       = Input(UInt(128.W))
        val Q       = Output(UInt(128.W))
    })
    setInline("SRam.v",
            """
           |
           |     module SRam(
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

class SRam_1k extends Module{
    val io = IO(Flipped(new SRamIO))
    val sram = Module(new SRam)
    sram.io.CLK     := clock
    sram.io.A       := io.addr
    sram.io.CEN     := io.cen
    sram.io.WEN     := io.wen
    sram.io.BWEN    := io.wmask
    sram.io.D       := io.wdata
    io.rdata        := sram.io.Q 
}

class SRam_2k extends Module{
    val io = IO(new Bundle{
        val addr    = Input(UInt(6.W))
        val cen     = Input(Bool())
        val wen     = Input(Bool())
        val wmask   = Input(UInt(256.W))
        val wdata   = Input(UInt(256.W))
        val rdata   = Output(UInt(256.W))

        val sram0   = new SRamIO
        val sram1   = new SRamIO
    })

    io.sram0.addr   := io.addr
    io.sram0.cen    := false.B              // ysyx给的sram的逻辑是反的
    io.sram0.wen    := !(io.wen && io.cen)  // ysyx给的sram的逻辑是反的
    io.sram0.wmask  := ~io.wmask(127, 0)    // ysyx给的sram的逻辑是反的
    io.sram0.wdata  := io.wdata(127, 0)

    io.sram1.addr   := io.addr
    io.sram1.cen    := false.B              // ysyx给的sram的逻辑是反的
    io.sram1.wen    := !(io.wen && io.cen)  // ysyx给的sram的逻辑是反的
    io.sram1.wmask  := ~io.wmask(255, 128)  // ysyx给的sram的逻辑是反的
    io.sram1.wdata  := io.wdata(255, 128)


    // 读保持功能
    val rdata = Cat(io.sram1.rdata, io.sram0.rdata)
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

class SRam_4k extends Module{
    val io = IO(new Bundle{
        val addr    = Input(UInt(6.W))
        val cen     = Input(Bool())
        val wen     = Input(Bool())
        val wmask   = Input(UInt(512.W))
        val wdata   = Input(UInt(512.W))
        val rdata   = Output(UInt(512.W))

        val sram0   = new SRamIO
        val sram1   = new SRamIO
        val sram2   = new SRamIO
        val sram3   = new SRamIO
    })

    io.sram0.addr   := io.addr
    io.sram0.cen    := false.B              // ysyx给的sram的逻辑是反的
    io.sram0.wen    := !(io.wen && io.cen)  // ysyx给的sram的逻辑是反的
    io.sram0.wmask  := ~io.wmask(127, 0)    // ysyx给的sram的逻辑是反的
    io.sram0.wdata  := io.wdata(127, 0)

    io.sram1.addr   := io.addr
    io.sram1.cen    := false.B              // ysyx给的sram的逻辑是反的
    io.sram1.wen    := !(io.wen && io.cen)  // ysyx给的sram的逻辑是反的
    io.sram1.wmask  := ~io.wmask(255, 128)  // ysyx给的sram的逻辑是反的
    io.sram1.wdata  := io.wdata(255, 128)

    io.sram2.addr   := io.addr
    io.sram2.cen    := false.B              // ysyx给的sram的逻辑是反的
    io.sram2.wen    := !(io.wen && io.cen)  // ysyx给的sram的逻辑是反的
    io.sram2.wmask  := ~io.wmask(383, 256)  // ysyx给的sram的逻辑是反的
    io.sram2.wdata  := io.wdata(383, 256)

    io.sram3.addr   := io.addr
    io.sram3.cen    := false.B              // ysyx给的sram的逻辑是反的
    io.sram3.wen    := !(io.wen && io.cen)  // ysyx给的sram的逻辑是反的
    io.sram3.wmask  := ~io.wmask(511, 384)  // ysyx给的sram的逻辑是反的
    io.sram3.wdata  := io.wdata(511, 384)


    // 读保持功能
    val rdata = Cat(io.sram3.rdata, io.sram2.rdata, io.sram1.rdata, io.sram0.rdata)
    val data_stay = RegInit(0.U(512.W))

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


// 二路组相联
// class ICache extends Module with CacheParameters{
//     val io = IO(new Bundle{
//         val imem    = new ICacheIO
//         val axi     = new ICacheAxiIO
//         val fence   = Flipped(new FenceIO)

//         val sram0   = new SRamIO
//         val sram1   = new SRamIO
//         val sram2   = new SRamIO
//         val sram3   = new SRamIO
//     })

//     // addr
//     val tag_addr    = io.imem.addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
//     val index_addr  = io.imem.addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
//     val offset_addr = io.imem.addr(OffsetWidth - 1, 0)
//     // cache data
//     val v1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val age1    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val tag1    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
//     val block1  = Module(new SRam_2k).io
//     val v2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val age2    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val tag2    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
//     val block2  = Module(new SRam_2k).io

//     block1.sram0 <> io.sram0
//     block1.sram1 <> io.sram1
//     block2.sram0 <> io.sram2
//     block2.sram1 <> io.sram3
    
//     //state machine define
//     val idle :: fetch :: update :: update_done :: fence_start :: fence_clean :: Nil = Enum(6)
//     val state = RegInit(idle)
//     val miss  = Wire(Bool())
//     val fence_reg = RegInit(0.U((1 + IndexWidth).W))    // 添加一位用于记录正在情况哪一路
//     val fence_way = fence_reg(IndexWidth)
//     val fence_cnt = fence_reg(IndexWidth - 1, 0)

//     switch(state){
//         is(idle){
//             when(io.fence.req){state := fence_start}
//             when(miss && io.imem.en){state := fetch}
//         }
//         is(fetch){
//             when(io.axi.valid) {state := update}
//         }
//         is(update){
//             state := update_done
//         }
//         is(update_done){
//             state := idle
//         }
//         // fence
//         is(fence_start){
//             state := fence_clean
//         }
//         is(fence_clean){
//             when(fence_reg === Fill(IndexWidth + 1, 1.U(1.W))){state := idle}
//             .otherwise{state := fence_clean}
//         }
//     }

//     // cacheway info

//     val addr_stay = RegEnable(io.imem.addr, 0.U(64.W), state === idle && io.imem.en)    // addr保存
//     val tag_addr_stay       = addr_stay(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
//     val index_addr_stay     = addr_stay(OffsetWidth + IndexWidth - 1, OffsetWidth)
//     val offset_addr_stay    = addr_stay(OffsetWidth - 1, 0)


//     val hit1    = tag_addr === tag1(index_addr) && v1(index_addr) === true.B
//     val hit2    = tag_addr === tag2(index_addr) && v2(index_addr) === true.B
//     miss        := !(hit1 || hit2)
//     val output_way = RegInit(0.U(2.W))

//     val data1   = (block1.rdata >> (offset_addr_stay << 3))(31, 0)
//     val data2   = (block2.rdata >> (offset_addr_stay << 3))(31, 0)
//     val data = Mux(output_way === "b10".U, data2, Mux(output_way === "b01".U, data1, 0.U))
    

//     // cache output
//     io.imem.data := Mux(state === idle, data, 0.U) 
//     io.imem.ok   := state === idle

//     // AXI output
//     io.axi.req  := state === fetch
//     io.axi.addr := addr_stay & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))
//     val axi_buffer = RegEnable(io.axi.data, 0.U(CacheLineWidth.W), (state === fetch) && io.axi.valid)

//     // update age
//     // 当hit1和hit2的值不同时，age才需要发生改变
//     when((state === idle) && (hit1 ^ hit2) && io.imem.en){
//         age1(index_addr) := hit1
//         age2(index_addr) := hit2
//     }
    
//     // choose which way to update
//     val age = Cat(age2(index_addr_stay), age1(index_addr_stay))
//     val updateway2 = age === "b01".U    
//     val updateway1 = !updateway2        // 特殊情况都默认换掉way1

//     // sram io
//     when(state === idle && io.imem.en){
//         block1.addr := index_addr
//         block2.addr := index_addr
//     }
//     .elsewhen((state === idle && !io.imem.en) || state === update || state === update_done){
//         block1.addr := index_addr_stay
//         block2.addr := index_addr_stay
//     }
//     .otherwise{
//         block1.addr := 0.U
//         block2.addr := 0.U
//     }
//     block1.cen  := !(state === idle && !io.imem.en)
//     block1.wen  := state === update && updateway1
//     block1.wdata := axi_buffer
//     block1.wmask := Fill(CacheLineWidth, 1.U)
//     block2.cen  := !(state === idle && !io.imem.en)
//     block2.wen  := state === update && updateway2
//     block2.wdata := axi_buffer
//     block2.wmask := Fill(CacheLineWidth, 1.U)

//     // v and tag
//     when(state === update && updateway1){
//         tag1(index_addr_stay) := tag_addr_stay
//         v1(index_addr_stay)   := true.B
//     }
//     when(state === update && updateway2){
//         tag2(index_addr_stay) := tag_addr_stay
//         v2(index_addr_stay)   := true.B
//     }
//     when(state === fence_clean && fence_way === 0.U){
//         v1(fence_cnt) := false.B
//     }
//     when(state === fence_clean && fence_way === 1.U){
//         v2(fence_cnt) := false.B
//     }

//     // choose output way
//     when(state === idle && io.imem.en){
//         output_way := Cat(hit2, hit1)
//     }
//     .elsewhen(state === update){
//         output_way := Cat(updateway2, updateway1)
//     }

//     // fence reg
//     when(state === fence_start){fence_reg := 0.U}
//     .elsewhen(state === fence_clean){fence_reg := fence_reg + 1.U}
    
//     // fence output
//     when(state === fence_clean){
//         io.fence.done := fence_reg === Fill(IndexWidth + 1, 1.U(1.W))
//     }
//     .otherwise{io.fence.done := false.B}
    
// }




class ICache extends Module with CacheParameters{
    val io = IO(new Bundle{
        val imem    = new ICacheIO
        val axi     = new ICacheAxiIO
        val fence   = Flipped(new FenceIO)

        val sram0   = new SRamIO
        val sram1   = new SRamIO
        val sram2   = new SRamIO
        val sram3   = new SRamIO
    })

    // addr
    val tag_addr    = io.imem.addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr  = io.imem.addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr = io.imem.addr(OffsetWidth - 1, 0)
    // cache data
    val v       = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag     = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val block   = Module(new SRam_4k).io

    block.sram0 <> io.sram0
    block.sram1 <> io.sram1
    block.sram2 <> io.sram2
    block.sram3 <> io.sram3
    
    //state machine define
    val idle :: fetch :: update :: update_done :: fence_start :: fence_clean :: Nil = Enum(6)
    val state = RegInit(idle)
    val miss  = Wire(Bool())
    val fence_reg = RegInit(0.U(IndexWidth.W))   
    val fence_cnt = fence_reg(IndexWidth - 1, 0)

    switch(state){
        is(idle){
            when(io.fence.req){state := fence_start}
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
        // fence
        is(fence_start){
            state := fence_clean
        }
        is(fence_clean){
            when(fence_reg === Fill(IndexWidth, 1.U(1.W))){state := idle}
            .otherwise{state := fence_clean}
        }
    }

    // cacheway info

    val addr_stay = RegEnable(io.imem.addr, 0.U(64.W), state === idle && io.imem.en)    // addr保存
    val tag_addr_stay       = addr_stay(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr_stay     = addr_stay(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr_stay    = addr_stay(OffsetWidth - 1, 0)

    val hit         = tag_addr === tag(index_addr) && v(index_addr) === true.B
    miss            := !hit
    val data        = (block.rdata >> (offset_addr_stay << 3))(31, 0)
    
    // cache output
    io.imem.data    := Mux(state === idle, data, 0.U) 
    io.imem.ok      := state === idle

    // AXI output
    io.axi.req      := state === fetch
    io.axi.addr     := addr_stay & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))
    val axi_buffer  = RegEnable(io.axi.data, 0.U(CacheLineWidth.W), (state === fetch) && io.axi.valid)

    // sram io
    when(state === idle && io.imem.en){
        block.addr := index_addr
    }
    .elsewhen((state === idle && !io.imem.en) || state === update || state === update_done){
        block.addr := index_addr_stay
    }
    .otherwise{
        block.addr := 0.U
    }
    block.cen   := !(state === idle && !io.imem.en)
    block.wen   := state === update
    block.wdata := axi_buffer
    block.wmask := Fill(CacheLineWidth, 1.U)

    // v and tag
    when(state === update){
        tag(index_addr_stay)    := tag_addr_stay
        v(index_addr_stay)      := true.B
    }
    when(state === fence_clean){
        v(fence_cnt)            := false.B
    }


    // fence reg
    when(state === fence_start){fence_reg := 0.U}
    .elsewhen(state === fence_clean){fence_reg := fence_reg + 1.U}
    
    // fence output
    when(state === fence_clean){
        io.fence.done := fence_reg === Fill(IndexWidth, 1.U(1.W))
    }
    .otherwise{io.fence.done := false.B}
}