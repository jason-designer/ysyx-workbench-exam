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

// 二路组相联
// class DCache extends Module with CacheParameters{
//     val io = IO(new Bundle{
//         val dmem    = new DCacheIO
//         val axi     = new DCacheAxiIO
//         val fence   = Flipped(new FenceIO)

//         val sram0   = new SRamIO
//         val sram1   = new SRamIO
//         val sram2   = new SRamIO
//         val sram3   = new SRamIO
//     })
//     // addr
//     val addr = io.dmem.addr & "hfffffffffffffff8".U
//     val tag_addr    = addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
//     val index_addr  = addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
//     val offset_addr = addr(OffsetWidth - 1, 0)
//     // cache data
//     val v1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val d1      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val age1    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val tag1    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
//     val block1  = Module(new SRam_2k).io
//     val v2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val d2      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val age2    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
//     val tag2    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
//     val block2  = Module(new SRam_2k).io

//     block1.sram0 <> io.sram0
//     block1.sram1 <> io.sram1
//     block2.sram0 <> io.sram2
//     block2.sram1 <> io.sram3
    
//     //state machine define
//     val idle :: getblock1 :: getblock2 :: writeback :: fetch :: update :: update_done :: fence_start :: getblock3 :: getblock4 :: fence_axi :: fence_axi_done :: Nil = Enum(12)
//     val state = RegInit(idle)
//     val miss  = Wire(Bool())
//     val dirty = Wire(Bool())
//     val fence_reg = RegInit(0.U((1 + IndexWidth).W))    // 添加一位用于记录正在情况哪一路
//     val fence_way = fence_reg(IndexWidth)
//     val fence_cnt = fence_reg(IndexWidth - 1, 0)

//     switch(state){
//         is(idle){
//             when(io.fence.req){state := fence_start}
//             when(miss && io.dmem.en){state := Mux(dirty, getblock1, fetch)}
//         }
//         is(getblock1){
//             state := getblock2
//         }
//         is(getblock2){
//             state := writeback
//         }
//         is(writeback){
//             when(io.axi.wdone){state := fetch}
//         }
//         is(fetch){
//             when(io.axi.rvalid){state := update}
//         }
//         is(update){
//             state := update_done
//         }
//         is(update_done){
//             state := idle
//         }
//         // fence
//         is(fence_start){
//             state := getblock3
//         }
//         is(getblock3){
//             val v = Mux(fence_way, v2(fence_cnt), v1(fence_cnt))
//             val d = Mux(fence_way, d2(fence_cnt), d1(fence_cnt))
//             when(v && d){state := getblock4}        // 有效且脏的时候才写回
//             .otherwise{state := fence_axi_done}
//         }
//         is(getblock4){
//             state := fence_axi
//         }
//         is(fence_axi){
//             when(io.axi.wdone){state := fence_axi_done}
//         }
//         is(fence_axi_done){
//             when(fence_reg === Fill(IndexWidth + 1, 1.U(1.W))){state := idle}
//             .otherwise{state := getblock3}
//         }
//     }

//     // cacheway info -----------------------------------------------------------
//     // choose which way to update
//     val age                 = Cat(age2(index_addr), age1(index_addr))
//     val updateway2          = age === "b01".U    
//     val updateway1          = !updateway2        // 特殊情况都默认换掉way1
//     val updateway_stay      = RegEnable(Cat(updateway2, updateway1), 0.U, state === idle && io.dmem.en)
//     // save addr
//     val addr_stay           = RegEnable(addr, 0.U(64.W), state === idle && io.dmem.en)    // addr保存
//     val tag_addr_stay       = addr_stay(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
//     val index_addr_stay     = addr_stay(OffsetWidth + IndexWidth - 1, OffsetWidth)
//     val offset_addr_stay    = addr_stay(OffsetWidth - 1, 0)
//     // save write info
//     val op_stay             = RegEnable(io.dmem.op, false.B, state === idle && io.dmem.en)
//     val wdata_stay          = RegEnable(io.dmem.wdata, 0.U, state === idle && io.dmem.en)
//     val wmask_stay          = RegEnable(io.dmem.wmask, 0.U, state === idle && io.dmem.en)
//     // dirty
//     dirty                   := Mux(updateway1, d1(index_addr), d2(index_addr))
//     // hit info
//     val hit1                = tag_addr === tag1(index_addr) && v1(index_addr) === true.B
//     val hit2                = tag_addr === tag2(index_addr) && v2(index_addr) === true.B
//     miss                    := !(hit1 || hit2)
//     // cache output info
//     val output_way          = RegInit(0.U(2.W))
//     val data1               = (block1.rdata >> (offset_addr_stay << 3))(63, 0)
//     val data2               = (block2.rdata >> (offset_addr_stay << 3))(63, 0)
//     val data                = Wire(UInt(64.W))
//     when(op_stay === true.B){data := 0.U}
//     .elsewhen(output_way === "b10".U){data := data2}
//     .elsewhen(output_way === "b01".U){data := data1}
//     .otherwise{data := 0.U}
//     // -----------------------------------------------------------------------------

//     // state machine output --------------------------------------------------------
//     io.dmem.rdata   := 0.U
//     io.dmem.ok      := false.B
    
//     io.axi.req      := false.B
//     io.axi.raddr    := 0.U
//     io.axi.weq      := false.B
//     io.axi.waddr    := 0.U
//     io.axi.wdata    := 0.U

//     io.fence.done   := false.B
    
//     block1.addr     := 0.U
//     block1.cen      := false.B
//     block1.wen      := false.B
//     block1.wdata    := 0.U
//     block1.wmask    := 0.U
//     block2.addr     := 0.U
//     block2.cen      := false.B
//     block2.wen      := false.B
//     block2.wdata    := 0.U
//     block2.wmask    := 0.U

//     // v, d, age, tag 

//     val axi_wbuffer = RegInit(0.U(CacheLineWidth.W))
//     val axi_rbuffer = RegInit(0.U(CacheLineWidth.W))
//     val fence_buffer = RegInit(0.U(CacheLineWidth.W))

//     def mask8_to_64(wm:UInt):UInt = Cat(Fill(8,wm(7)),Fill(8,wm(6)),Fill(8,wm(5)),Fill(8,wm(4)),Fill(8,wm(3)),Fill(8,wm(2)),Fill(8,wm(1)),Fill(8,wm(0)))
    
//     switch(state){
//         is(idle){
//             io.dmem.rdata   := data
//             io.dmem.ok      := true.B

//             block1.addr     := index_addr
//             block1.cen      := io.dmem.en
//             block1.wen      := io.dmem.op && hit1
//             block1.wdata    := io.dmem.wdata << (offset_addr << 3.U)
//             block1.wmask    := mask8_to_64(io.dmem.wmask) << (offset_addr << 3.U)

//             block2.addr     := index_addr
//             block2.cen      := io.dmem.en
//             block2.wen      := io.dmem.op && hit2
//             block2.wdata    := io.dmem.wdata << (offset_addr << 3.U)
//             block2.wmask    := mask8_to_64(io.dmem.wmask) << (offset_addr << 3.U)
            
//             output_way      := Cat(hit2, hit1)

//             when((hit1 ^ hit2) && io.dmem.en){
//                 age1(index_addr) := hit1
//                 age2(index_addr) := hit2
//             }

//             when(io.dmem.op && hit1){d1(index_addr) := true.B}
//             when(io.dmem.op && hit2){d2(index_addr) := true.B}
//         }
//         is(getblock1){
//            when(updateway_stay === "b01".U){
//                 block1.addr     := index_addr_stay
//                 block1.cen      := true.B
//                 block1.wen      := false.B

//            }
//            when(updateway_stay === "b10".U){
//                 block2.addr     := index_addr_stay
//                 block2.cen      := true.B
//                 block2.wen      := false.B
//            }
//         }
//         is(getblock2){
//            when(updateway_stay === "b01".U){
//                 axi_wbuffer := block1.rdata
//            }
//            when(updateway_stay === "b10".U){
//                 axi_wbuffer := block2.rdata
//            }
//         }
//         is(writeback){
//             io.axi.weq      := true.B
//             io.axi.waddr    := Cat(Mux(updateway_stay === "b01".U, tag1(index_addr_stay), tag2(index_addr_stay)), index_addr_stay, 0.U(OffsetWidth.W)) 
//             io.axi.wdata    := axi_wbuffer
//         }
//         is(fetch){
//             io.axi.req      := state === fetch
//             io.axi.raddr    := addr_stay & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))
//             when(io.axi.rvalid){axi_rbuffer := io.axi.rdata}
//         }
//         is(update){
//             block1.addr     := index_addr_stay
//             block1.cen      := true.B
//             block1.wen      := updateway_stay === "b01".U
//             block1.wdata    := axi_rbuffer
//             block1.wmask    := Fill(CacheLineWidth, 1.U)

//             block2.addr     := index_addr_stay
//             block2.cen      := true.B
//             block2.wen      := updateway_stay === "b10".U
//             block2.wdata    := axi_rbuffer
//             block2.wmask    := Fill(CacheLineWidth, 1.U)

//             when(updateway_stay === "b01".U){
//                 tag1(index_addr_stay) := tag_addr_stay
//                 v1(index_addr_stay)   := true.B
//                 d1(index_addr_stay)   := false.B
//             }
//             when(updateway_stay === "b10".U){
//                 tag2(index_addr_stay) := tag_addr_stay
//                 v2(index_addr_stay)   := true.B
//                 d2(index_addr_stay)   := false.B
//             }
//         }
//         is(update_done){
//             block1.addr     := index_addr_stay
//             block1.cen      := true.B
//             block1.wen      := op_stay && updateway_stay === "b01".U
//             block1.wdata    := wdata_stay << (offset_addr_stay << 3.U)
//             block1.wmask    := mask8_to_64(wmask_stay) << (offset_addr_stay << 3.U)

//             block2.addr     := index_addr_stay
//             block2.cen      := true.B
//             block2.wen      := op_stay && updateway_stay === "b10".U
//             block2.wdata    := wdata_stay << (offset_addr_stay << 3.U)
//             block2.wmask    := mask8_to_64(wmask_stay) << (offset_addr_stay << 3.U)

//             when(op_stay && updateway_stay === "b01".U){d1(index_addr_stay) := true.B}
//             when(op_stay && updateway_stay === "b10".U){d2(index_addr_stay) := true.B}

//             output_way      := updateway_stay 
//         }
//         // fence
//         is(fence_start){
//             fence_reg := 0.U
//         }
//         is(getblock3){
//             block1.addr     := fence_cnt
//             block1.cen      := true.B
//             block2.addr     := fence_cnt
//             block2.cen      := true.B
//         }
//         is(getblock4){
//             fence_buffer    := Mux(fence_way === 0.U, block1.rdata, block2.rdata)
//         }
//         is(fence_axi){
//             io.axi.weq      := true.B
//             io.axi.waddr    := Cat(Mux(fence_way === 0.U, tag1(fence_cnt), tag2(fence_cnt)), fence_cnt, 0.U(OffsetWidth.W))
//             io.axi.wdata    := fence_buffer
//         }
//         is(fence_axi_done){
//             fence_reg := fence_reg + 1.U
//             when(fence_way === 0.U){
//                 v1(fence_cnt)   := false.B
//                 d1(fence_cnt)   := false.B
//             }
//             .otherwise{
//                 v2(fence_cnt)   := false.B
//                 d2(fence_cnt)   := false.B
//             }

//             io.fence.done   := fence_reg === Fill(IndexWidth + 1, 1.U(1.W))
//         }
//     }
// }



class DCache extends Module with CacheParameters{
    val io = IO(new Bundle{
        val dmem    = new DCacheIO
        val axi     = new DCacheAxiIO
        val fence   = Flipped(new FenceIO)

        val sram0   = new SRamIO
        val sram1   = new SRamIO
        val sram2   = new SRamIO
        val sram3   = new SRamIO
    })
    // addr
    val addr = io.dmem.addr & "hfffffffffffffff8".U
    val tag_addr    = addr(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr  = addr(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr = addr(OffsetWidth - 1, 0)
    // cache data
    val v      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val d      = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val age    = RegInit(VecInit(Seq.fill(CacheLineNum)(false.B)))
    val tag    = RegInit(VecInit(Seq.fill(CacheLineNum)(0.U(TagWidth.W))))
    val block  = Module(new SRam_4k).io

    block.sram0 <> io.sram0
    block.sram1 <> io.sram1
    block.sram2 <> io.sram2
    block.sram3 <> io.sram3
    
    //state machine define
    val idle :: getblock1 :: getblock2 :: writeback :: fetch :: update :: update_done :: fence_start :: getblock3 :: getblock4 :: fence_axi :: fence_axi_done :: Nil = Enum(12)
    val state = RegInit(idle)
    val miss  = Wire(Bool())
    val dirty = Wire(Bool())
    val fence_reg = RegInit(0.U((IndexWidth).W))   
    val fence_cnt = fence_reg(IndexWidth - 1, 0)

    switch(state){
        is(idle){
            when(io.fence.req){state := fence_start}
            when(miss && io.dmem.en){state := Mux(dirty, getblock1, fetch)}
        }
        is(getblock1){
            state := getblock2
        }
        is(getblock2){
            state := writeback
        }
        is(writeback){
            when(io.axi.wdone){state := fetch}
        }
        is(fetch){
            when(io.axi.rvalid){state := update}
        }
        is(update){
            state := update_done
        }
        is(update_done){
            state := idle
        }
        // fence
        is(fence_start){
            state := getblock3
        }
        is(getblock3){
            when(v(fence_cnt) && d(fence_cnt)){state := getblock4}        // 有效且脏的时候才写回
            .otherwise{state := fence_axi_done}
        }
        is(getblock4){
            state := fence_axi
        }
        is(fence_axi){
            when(io.axi.wdone){state := fence_axi_done}
        }
        is(fence_axi_done){
            when(fence_reg === Fill(IndexWidth, 1.U(1.W))){state := idle}
            .otherwise{state := getblock3}
        }
    }

    // cacheway info -----------------------------------------------------------
    // save addr
    val addr_stay           = RegEnable(addr, 0.U(64.W), state === idle && io.dmem.en)    // addr保存
    val tag_addr_stay       = addr_stay(OffsetWidth + IndexWidth + TagWidth - 1, OffsetWidth + IndexWidth)
    val index_addr_stay     = addr_stay(OffsetWidth + IndexWidth - 1, OffsetWidth)
    val offset_addr_stay    = addr_stay(OffsetWidth - 1, 0)
    // save write info
    val op_stay             = RegEnable(io.dmem.op, false.B, state === idle && io.dmem.en)
    val wdata_stay          = RegEnable(io.dmem.wdata, 0.U, state === idle && io.dmem.en)
    val wmask_stay          = RegEnable(io.dmem.wmask, 0.U, state === idle && io.dmem.en)
    // dirty
    dirty                   := d(index_addr)
    // hit info
    val hit                 = tag_addr === tag(index_addr) && v(index_addr) === true.B
    miss                    := !hit
    // cache output info
    val data                = Mux(op_stay, 0.U, (block.rdata >> (offset_addr_stay << 3))(63, 0))
    // -----------------------------------------------------------------------------

    // state machine output --------------------------------------------------------
    io.dmem.rdata   := 0.U
    io.dmem.ok      := false.B
    
    io.axi.req      := false.B
    io.axi.raddr    := 0.U
    io.axi.weq      := false.B
    io.axi.waddr    := 0.U
    io.axi.wdata    := 0.U

    io.fence.done   := false.B
    
    block.addr      := 0.U
    block.cen       := false.B
    block.wen       := false.B
    block.wdata     := 0.U
    block.wmask     := 0.U

    // v, d, age, tag 
    val axi_wbuffer = RegInit(0.U(CacheLineWidth.W))
    val axi_rbuffer = RegInit(0.U(CacheLineWidth.W))
    val fence_buffer = RegInit(0.U(CacheLineWidth.W))

    def mask8_to_64(wm:UInt):UInt = Cat(Fill(8,wm(7)),Fill(8,wm(6)),Fill(8,wm(5)),Fill(8,wm(4)),Fill(8,wm(3)),Fill(8,wm(2)),Fill(8,wm(1)),Fill(8,wm(0)))
    
    switch(state){
        is(idle){
            io.dmem.rdata   := data
            io.dmem.ok      := true.B

            block.addr      := index_addr
            block.cen       := io.dmem.en
            block.wen       := io.dmem.op && hit
            block.wdata     := io.dmem.wdata << (offset_addr << 3.U)
            block.wmask     := mask8_to_64(io.dmem.wmask) << (offset_addr << 3.U)

            when(io.dmem.op && hit){d(index_addr) := true.B}
        }
        is(getblock1){
            block.addr      := index_addr_stay
            block.cen       := true.B
            block.wen       := false.B
        }
        is(getblock2){
            axi_wbuffer     := block.rdata
        }
        is(writeback){
            io.axi.weq      := true.B
            io.axi.waddr    := Cat(tag(index_addr_stay), index_addr_stay, 0.U(OffsetWidth.W)) 
            io.axi.wdata    := axi_wbuffer
        }
        is(fetch){
            io.axi.req      := state === fetch
            io.axi.raddr    := addr_stay & Cat(Fill(IndexWidth + TagWidth, 1.U(1.W)), 0.U(OffsetWidth.W))
            when(io.axi.rvalid){axi_rbuffer := io.axi.rdata}
        }
        is(update){
            block.addr      := index_addr_stay
            block.cen       := true.B
            block.wen       := true.B
            block.wdata     := axi_rbuffer
            block.wmask     := Fill(CacheLineWidth, 1.U)


            tag(index_addr_stay)    := tag_addr_stay
            v(index_addr_stay)      := true.B
            d(index_addr_stay)      := false.B

        }
        is(update_done){
            block.addr      := index_addr_stay
            block.cen       := true.B
            block.wen       := op_stay
            block.wdata     := wdata_stay << (offset_addr_stay << 3.U)
            block.wmask     := mask8_to_64(wmask_stay) << (offset_addr_stay << 3.U)

            when(op_stay){d(index_addr_stay) := true.B}
        }
        // fence
        is(fence_start){
            fence_reg := 0.U
        }
        is(getblock3){
            block.addr      := fence_cnt
            block.cen       := true.B
        }
        is(getblock4){
            fence_buffer    := block.rdata
        }
        is(fence_axi){
            io.axi.weq      := true.B
            io.axi.waddr    := Cat(tag(fence_cnt), fence_cnt, 0.U(OffsetWidth.W))
            io.axi.wdata    := fence_buffer
        }
        is(fence_axi_done){
            fence_reg := fence_reg + 1.U
            v(fence_cnt)    := false.B
            d(fence_cnt)    := false.B
            io.fence.done   := fence_reg === Fill(IndexWidth, 1.U(1.W))
        }
    }
}