import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import Instructions._
// import difftest._

// class Core extends Module{
//     val io = IO(new Bundle{
//         val imem = new ImemIO
//         val dmem = new DmemIO
//     })
//     val pipeline        = Module(new Pipeline)
//     val rfu             = Module(new RegFile)
//     val csru            = Module(new Csr)
//     // mul/div
//     val mu              = Module(new MU)
//     val du              = Module(new DU)

//     // pipeline control
//     val env_wait = (pipeline.io.id_ecall || pipeline.io.id_mret || pipeline.io.id_intr) && (pipeline.io.ie_valid || pipeline.io.mem_valid || pipeline.io.wb_valid)
//     val env_go = !pipeline.io.stall_id && (pipeline.io.id_ecall || pipeline.io.id_mret || pipeline.io.id_intr) && (!pipeline.io.ie_valid && !pipeline.io.mem_valid && !pipeline.io.wb_valid)
//     val imem_not_ok = false.B //!icache.io.imem.ok
//     val dmem_not_ok = false.B //!dmmio.io.dmem.ok

//     pipeline.io.stall_id    := pipeline.io.rfconflict || imem_not_ok || env_wait
//     pipeline.io.stall_ie    := mu.io.stall || du.io.stall
//     pipeline.io.stall_mem   := false.B
//     pipeline.io.stall_wb    := dmem_not_ok

//     // pipeline <--> regfile
//     rfu.io.rs1_addr         := pipeline.io.rs1_addr 
//     rfu.io.rs2_addr         := pipeline.io.rs2_addr
//     pipeline.io.rs1_data    := rfu.io.rs1_data
//     pipeline.io.rs2_data    := rfu.io.rs2_data
//     rfu.io.rd_en    := pipeline.io.commit && pipeline.io.rf_rd_en
//     rfu.io.rd_addr  := pipeline.io.rf_rd_addr
//     rfu.io.rd_data  := pipeline.io.rf_rd_data

//     // pipeline <--> mul/div
//     mu.io.en            := pipeline.io.mu_code =/= 0.U && pipeline.io.ie_valid
//     mu.io.mu_code       := pipeline.io.mu_code
//     mu.io.op1           := pipeline.io.mu_op1
//     mu.io.op2           := pipeline.io.mu_op2
//     pipeline.io.mu_out  := mu.io.mu_out

//     du.io.en            := pipeline.io.du_code =/= 0.U && pipeline.io.ie_valid
//     du.io.du_code       := pipeline.io.du_code
//     du.io.op1           := pipeline.io.du_op1
//     du.io.op2           := pipeline.io.du_op2
//     pipeline.io.du_out  := du.io.du_out

//     // pipeline <--> csr
//     csru.io.raddr           := pipeline.io.csr_raddr
//     pipeline.io.csr_rdata   := csru.io.rdata
//     csru.io.wen             := pipeline.io.commit && pipeline.io.csr_wen
//     csru.io.waddr           := pipeline.io.csr_waddr
//     csru.io.wdata           := pipeline.io.csr_wdata

//     csru.io.set_mtip    := false.B//clintreg.io.set_mtip
//     csru.io.clear_mtip  := false.B//clintreg.io.clear_mtip
    
//     csru.io.interrupt   := env_go && pipeline.io.id_intr
//     csru.io.cause       := pipeline.io.id_cause

//     pipeline.io.intr    := csru.io.time_intr && !env_go     // 防止连续给出两个intr
//     pipeline.io.cause   := "h8000000000000007".U

//     pipeline.io.csr_mtvec   := csru.io.mtvec
//     pipeline.io.csr_mepc    := csru.io.mepc
//     csru.io.ecall   := env_go && pipeline.io.id_ecall
//     csru.io.mret    := env_go && pipeline.io.id_mret
//     csru.io.pc      := pipeline.io.id_pc

//     // access memory
//     io.imem <> pipeline.io.imem
//     io.dmem <> pipeline.io.dmem
//     io.dmem.ren := pipeline.io.dmem.ren && pipeline.io.mem_valid
//     io.dmem.wen := pipeline.io.dmem.wen && pipeline.io.mem_valid
        
//     /* ------------------------------------ use difftest ---------------------------------------- */
//     val commit      = pipeline.io.commit
//     val pc          = pipeline.io.commit_pc
//     val inst        = pipeline.io.commit_inst
    
//     val putch       = inst === "h0000007b".U
//     val read_mcycle = (inst & "hfff0307f".U) === "hb0002073".U 
//     val rtthread_test_skip =  pc === "h80005360".U // 读mip
//     val skip = putch || read_mcycle || pipeline.io.commit_clint || rtthread_test_skip
//     // halt
//     val halt = Module(new Halt)
//     halt.io.clk   := clock
//     halt.io.reset := reset
//     halt.io.halt  := inst === EBREAK || inst === "h0000006b".U 
//     // itrace
//     val itrace = Module(new ITrace)
//     itrace.io.clk       := clock
//     itrace.io.reset     := reset
//     itrace.io.commit    := commit
//     itrace.io.pc        := pc
//     itrace.io.inst      := inst
//     itrace.io.ren       := pipeline.io.commit_dmem_ren
//     itrace.io.raddr     := pipeline.io.commit_dmem_raddr
//     itrace.io.wen       := pipeline.io.commit_dmem_wen
//     itrace.io.waddr     := pipeline.io.commit_dmem_waddr
//     // mtrace
//     val mtrace = Module(new MTrace)
//     mtrace.io.clk   := clock
//     mtrace.io.reset := reset
//     mtrace.io.valid := pipeline.io.mem_valid
//     mtrace.io.pc    := pipeline.io.mem_pc
//     mtrace.io.inst  := pipeline.io.mem_inst
//     mtrace.io.ren   := pipeline.io.dmem.ren
//     mtrace.io.raddr := pipeline.io.dmem.raddr
//     mtrace.io.rdata := io.dmem.rdata
//     mtrace.io.wen   := pipeline.io.dmem.wen
//     mtrace.io.waddr := pipeline.io.dmem.waddr
//     mtrace.io.wdata := pipeline.io.dmem.wdata
//     mtrace.io.wmask := pipeline.io.dmem.wmask
// }


class Core extends Module{
    val io = IO(new Bundle{
        val axi = new AxiIO
    })
    val pipeline        = Module(new Pipeline)
    val rfu             = Module(new RegFile)
    val csru            = Module(new Csr)
    val fence           = Module(new Fence)
    // mul/div
    val mu              = Module(new MU)
    val du              = Module(new DU)
    // imem
    val icache          = Module(new ICache)
    val icacheaxi       = Module(new ICacheSocAxi)
    // dmem
    val dmmio           = Module(new DMMIO)
    val dcache          = Module(new DCache)
    val clintreg        = Module(new ClintReg)
    val dcachebypass    = Module(new DCacheBypass)
    //
    val axi             = Module(new AXI)


    // pipeline control
    val env_wait = (pipeline.io.id_ecall || pipeline.io.id_mret || pipeline.io.id_intr) && (pipeline.io.ie_valid || pipeline.io.mem_valid || pipeline.io.wb_valid)
    val env_go = !pipeline.io.stall_id && (pipeline.io.id_ecall || pipeline.io.id_mret || pipeline.io.id_intr) && (!pipeline.io.ie_valid && !pipeline.io.mem_valid && !pipeline.io.wb_valid)
    val imem_not_ok = !icache.io.imem.ok
    val dmem_not_ok = !dmmio.io.dmem.ok

    val fence_wait = pipeline.io.id_fencei && (pipeline.io.ie_valid || pipeline.io.mem_valid || pipeline.io.wb_valid)
    fence.io.go := pipeline.io.id_fencei && !pipeline.io.ie_valid && !pipeline.io.mem_valid && !pipeline.io.wb_valid
    val fence_running = !fence.io.ok    

    pipeline.io.stall_id    := pipeline.io.rfconflict || imem_not_ok || env_wait
    pipeline.io.stall_ie    := mu.io.stall || du.io.stall
    pipeline.io.stall_mem   := false.B
    pipeline.io.stall_wb    := dmem_not_ok

    // pipeline <--> regfile
    rfu.io.rs1_addr         := pipeline.io.rs1_addr 
    rfu.io.rs2_addr         := pipeline.io.rs2_addr
    pipeline.io.rs1_data    := rfu.io.rs1_data
    pipeline.io.rs2_data    := rfu.io.rs2_data
    rfu.io.rd_en    := pipeline.io.commit && pipeline.io.rf_rd_en
    rfu.io.rd_addr  := pipeline.io.rf_rd_addr
    rfu.io.rd_data  := pipeline.io.rf_rd_data

    // pipeline <--> mul/div
    mu.io.en            := pipeline.io.mu_code =/= 0.U && pipeline.io.ie_valid
    mu.io.mu_code       := pipeline.io.mu_code
    mu.io.op1           := pipeline.io.mu_op1
    mu.io.op2           := pipeline.io.mu_op2
    pipeline.io.mu_out  := mu.io.mu_out

    du.io.en            := pipeline.io.du_code =/= 0.U && pipeline.io.ie_valid
    du.io.du_code       := pipeline.io.du_code
    du.io.op1           := pipeline.io.du_op1
    du.io.op2           := pipeline.io.du_op2
    pipeline.io.du_out  := du.io.du_out

    // pipeline <--> csr
    csru.io.raddr           := pipeline.io.csr_raddr
    pipeline.io.csr_rdata   := csru.io.rdata
    csru.io.wen             := pipeline.io.commit && pipeline.io.csr_wen
    csru.io.waddr           := pipeline.io.csr_waddr
    csru.io.wdata           := pipeline.io.csr_wdata

    csru.io.set_mtip    := false.B//clintreg.io.set_mtip
    csru.io.clear_mtip  := false.B//clintreg.io.clear_mtip
    
    csru.io.interrupt   := env_go && pipeline.io.id_intr
    csru.io.cause       := pipeline.io.id_cause

    pipeline.io.intr    := csru.io.time_intr && !env_go     // 防止连续给出两个intr
    pipeline.io.cause   := "h8000000000000007".U

    pipeline.io.csr_mtvec   := csru.io.mtvec
    pipeline.io.csr_mepc    := csru.io.mepc
    csru.io.ecall   := env_go && pipeline.io.id_ecall
    csru.io.mret    := env_go && pipeline.io.id_mret
    csru.io.pc      := pipeline.io.id_pc

    // fence
    icache.io.fence <> fence.io.ifence
    dcache.io.fence <> fence.io.dfence

    // pipeline <--> memory <--> axi
    /******************* access memory *****************

       pipeline ->|-> dmmio -->|-> dcache ------->|-> axi
                  |            |-> clintreg       |
                  |            |-> dcachebypass ->| 
                  |                               |
                  |-> icache ----> icacheaxi ---->|      

    ****************************************************/                                                                    
    icache.io.imem.addr     := pipeline.io.imem.addr
    icache.io.imem.en       := pipeline.io.imem.en
    pipeline.io.imem.data   := icache.io.imem.data

    val dmem_en = pipeline.io.dmem.ren || pipeline.io.dmem.wen 
    val dmem_op = pipeline.io.dmem.wen   // 按理说ren和wen不会同时为true
    val dmem_addr = Mux(dmem_op, pipeline.io.dmem.waddr, pipeline.io.dmem.raddr)
    dmmio.io.dmem.en        := dmem_en && pipeline.io.mem_valid
    dmmio.io.dmem.op        := dmem_op
    dmmio.io.dmem.addr      := dmem_addr
    dmmio.io.dmem.wdata     := pipeline.io.dmem.wdata
    dmmio.io.dmem.wmask     := pipeline.io.dmem.wmask
    dmmio.io.dmem.transfer  := pipeline.io.dmem_transfer
    pipeline.io.dmem.rdata  := dmmio.io.dmem.rdata
    
    icache.io.axi <> icacheaxi.io.in
    icacheaxi.io.out0 <> axi.io.icacheio
    icacheaxi.io.out1 <> axi.io.icacheBypassIO

    dmmio.io.mem0 <> dcache.io.dmem
    dmmio.io.mem1 <> clintreg.io.mem
    dmmio.io.mem2 <> dcachebypass.io.dmem

    dcache.io.axi       <> axi.io.dcacheio
    dcachebypass.io.axi <> axi.io.dcacheBypassIO

    axi.io.out.ar <> io.axi.ar
    axi.io.out.r  <> io.axi.r
    axi.io.out.aw <> io.axi.aw
    axi.io.out.w  <> io.axi.w
    axi.io.out.b  <> io.axi.b 
       
    /* ------------------------------------ use difftest ---------------------------------------- */
    val commit      = pipeline.io.commit
    val pc          = pipeline.io.commit_pc
    val inst        = pipeline.io.commit_inst
    
    val putch       = inst === "h0000007b".U
    val read_mcycle = (inst & "hfff0307f".U) === "hb0002073".U 
    val rtthread_test_skip =  pc === "h80005360".U // 读mip
    val skip = putch || read_mcycle || pipeline.io.commit_clint || rtthread_test_skip
    // halt
    val halt = Module(new Halt)
    halt.io.clk   := clock
    halt.io.reset := reset
    halt.io.halt  := inst === EBREAK || inst === "h0000006b".U 
    // itrace
    val itrace = Module(new ITrace)
    itrace.io.clk       := clock
    itrace.io.reset     := reset
    itrace.io.commit    := commit
    itrace.io.pc        := pc
    itrace.io.inst      := inst
    itrace.io.ren       := pipeline.io.commit_dmem_ren
    itrace.io.raddr     := pipeline.io.commit_dmem_raddr
    itrace.io.wen       := pipeline.io.commit_dmem_wen
    itrace.io.waddr     := pipeline.io.commit_dmem_waddr
    // mtrace
    val mtrace = Module(new MTrace)
    mtrace.io.clk   := clock
    mtrace.io.reset := reset
    mtrace.io.valid := pipeline.io.mem_valid
    mtrace.io.pc    := pipeline.io.mem_pc
    mtrace.io.inst  := pipeline.io.mem_inst
    mtrace.io.ren   := pipeline.io.dmem.ren
    mtrace.io.raddr := pipeline.io.dmem.raddr
    mtrace.io.rdata := pipeline.io.dmem.rdata
    mtrace.io.wen   := pipeline.io.dmem.wen
    mtrace.io.waddr := pipeline.io.dmem.waddr
    mtrace.io.wdata := pipeline.io.dmem.wdata
    mtrace.io.wmask := pipeline.io.dmem.wmask
}



// class Core extends Module{
//     val io = IO(new Bundle{
//         val axi = new AxiIO
//     })
//     val pipeline        = Module(new Pipeline)
//     val rfu             = Module(new RegFile)
//     val csru            = Module(new Csr)
//     val fence           = Module(new Fence)
//     // mul/div
//     val mu              = Module(new MU)
//     val du              = Module(new DU)
//     // imem
//     val icache          = Module(new ICache)
//     val icacheaxi       = Module(new ICacheSocAxi)
//     // dmem
//     val dmmio           = Module(new DMMIO)
//     val dcache          = Module(new DCache)
//     val clintreg        = Module(new ClintReg)
//     val dcachebypass    = Module(new DCacheBypass)
//     //
//     val axi             = Module(new AXI)

//     // pipeline control
//     val env_wait = (pipeline.io.id_ecall || pipeline.io.id_mret || pipeline.io.id_intr) && (pipeline.io.ie_valid || pipeline.io.mem_valid || pipeline.io.wb_valid)
//     val env_go = !pipeline.io.stall_id && (pipeline.io.id_ecall || pipeline.io.id_mret || pipeline.io.id_intr) && (!pipeline.io.ie_valid && !pipeline.io.mem_valid && !pipeline.io.wb_valid)

//     val fence_wait = pipeline.io.id_fencei && (pipeline.io.ie_valid || pipeline.io.mem_valid || pipeline.io.wb_valid)
//     fence.io.go := pipeline.io.id_fencei && !pipeline.io.ie_valid && !pipeline.io.mem_valid && !pipeline.io.wb_valid
//     val fence_running = !fence.io.ok
    
//     pipeline.io.stall_id    := pipeline.io.rfconflict || !icache.io.imem.ok || env_wait || fence_wait || fence_running
//     pipeline.io.stall_ie    := mu.io.stall || du.io.stall
//     pipeline.io.stall_mem   := false.B
//     pipeline.io.stall_wb    := !dmmio.io.dmem.ok

//     // pipeline <--> regfile
//     rfu.io.rs1_addr         := pipeline.io.rs1_addr 
//     rfu.io.rs2_addr         := pipeline.io.rs2_addr
//     pipeline.io.rs1_data    := rfu.io.rs1_data
//     pipeline.io.rs2_data    := rfu.io.rs2_data
//     rfu.io.rd_en    := pipeline.io.commit && pipeline.io.rf_rd_en
//     rfu.io.rd_addr  := pipeline.io.rf_rd_addr
//     rfu.io.rd_data  := pipeline.io.rf_rd_data

//     // pipeline <--> mul/div
//     mu.io.en            := pipeline.io.mu_code =/= 0.U && pipeline.io.ie_valid
//     mu.io.mu_code       := pipeline.io.mu_code
//     mu.io.op1           := pipeline.io.mu_op1
//     mu.io.op2           := pipeline.io.mu_op2
//     pipeline.io.mu_out  := mu.io.mu_out

//     du.io.en            := pipeline.io.du_code =/= 0.U && pipeline.io.ie_valid
//     du.io.du_code       := pipeline.io.du_code
//     du.io.op1           := pipeline.io.du_op1
//     du.io.op2           := pipeline.io.du_op2
//     pipeline.io.du_out  := du.io.du_out

//     // pipeline <--> csr
//     csru.io.raddr           := pipeline.io.csr_raddr
//     pipeline.io.csr_rdata   := csru.io.rdata
//     csru.io.wen             := pipeline.io.commit && pipeline.io.csr_wen
//     csru.io.waddr           := pipeline.io.csr_waddr
//     csru.io.wdata           := pipeline.io.csr_wdata

//     csru.io.set_mtip    := clintreg.io.set_mtip
//     csru.io.clear_mtip  := clintreg.io.clear_mtip
    
//     csru.io.interrupt   := env_go && pipeline.io.id_intr
//     csru.io.cause       := pipeline.io.id_cause

//     pipeline.io.intr    := csru.io.time_intr && !env_go     // 防止连续给出两个intr
//     pipeline.io.cause   := "h8000000000000007".U

//     pipeline.io.csr_mtvec   := csru.io.mtvec
//     pipeline.io.csr_mepc    := csru.io.mepc
//     csru.io.ecall   := env_go && pipeline.io.id_ecall
//     csru.io.mret    := env_go && pipeline.io.id_mret
//     csru.io.pc      := pipeline.io.id_pc

//     // fence
//     icache.io.fence <> fence.io.ifence
//     dcache.io.fence <> fence.io.dfence

//     // pipeline <--> memory <--> axi
//     /******************* access memory *****************

//        pipeline ->|-> dmmio -->|-> dcache ------->|-> axi
//                   |            |-> clintreg       |
//                   |            |-> dcachebypass ->| 
//                   |                               |
//                   |-> icache ----> icacheaxi ---->|      

//     ****************************************************/                                                                    
//     icache.io.imem.addr     := pipeline.io.imem.addr
//     icache.io.imem.en       := pipeline.io.imem.en
//     pipeline.io.imem.data   := icache.io.imem.data

//     val dmem_en = pipeline.io.dmem.ren || pipeline.io.dmem.wen 
//     val dmem_op = pipeline.io.dmem.wen   // 按理说ren和wen不会同时为true
//     val dmem_addr = Mux(dmem_op, pipeline.io.dmem.waddr, pipeline.io.dmem.raddr)
//     dmmio.io.dmem.en        := dmem_en && pipeline.io.mem_valid
//     dmmio.io.dmem.op        := dmem_op
//     dmmio.io.dmem.addr      := dmem_addr
//     dmmio.io.dmem.wdata     := pipeline.io.dmem.wdata
//     dmmio.io.dmem.wmask     := pipeline.io.dmem.wmask
//     dmmio.io.dmem.transfer  := pipeline.io.dmem_transfer
//     pipeline.io.dmem.rdata  := dmmio.io.dmem.rdata
    
//     icache.io.axi <> icacheaxi.io.in
//     icacheaxi.io.out0 <> axi.io.icacheio
//     icacheaxi.io.out1 <> axi.io.icacheBypassIO

//     dmmio.io.mem0 <> dcache.io.dmem
//     dmmio.io.mem1 <> clintreg.io.mem
//     dmmio.io.mem2 <> dcachebypass.io.dmem

//     dcache.io.axi       <> axi.io.dcacheio
//     dcachebypass.io.axi <> axi.io.dcacheBypassIO

//     axi.io.out.ar <> io.axi.ar
//     axi.io.out.r  <> io.axi.r
//     axi.io.out.aw <> io.axi.aw
//     axi.io.out.w  <> io.axi.w
//     axi.io.out.b  <> io.axi.b 

//     if(Config.soc == false){
//         /* ------------------------------------ putch --------------------------------- */
//         val regfile_a0 = WireInit(0.U(64.W))
//         BoringUtils.addSink(regfile_a0, "rf_a0")
//         when(pipeline.io.putch && pipeline.io.commit) {printf("%c",regfile_a0)}

//         /* ------------------------------------ debug ---------------------------------------- */
//         when(clock.asBool()){
//             val commit = pipeline.io.commit
//             val pc = pipeline.io.commit_pc
//             val inst = pipeline.io.commit_inst

//             val en = dmmio.io.dmem.en
//             val op = dmmio.io.dmem.op
//             val addr = dmmio.io.dmem.addr
//             val wdata = dmmio.io.dmem.wdata
//             val wmask = dmmio.io.dmem.wmask
//             val transfer = dmmio.io.dmem.transfer
//             val rdata = dmmio.io.dmem.rdata

//             // printf("valid=%d pc=%x inst=%x %d %d %x %x %x %d %x \n", commit, pc, inst, en, op, addr, wdata, wmask, transfer, rdata)
//         }
            
//         /* ------------------------------------ use difftest ---------------------------------------- */
//         val inst        = pipeline.io.commit_inst
//         val pc          = pipeline.io.commit_pc
//         val putch       = inst === "h0000007b".U
//         val read_mcycle = (inst & "hfff0307f".U) === "hb0002073".U 
//         val rtthread_test_skip =  pc === "h80005360".U // 读mip
//         val skip = putch || read_mcycle || pipeline.io.commit_clint || rtthread_test_skip
        
//         val dt_ic = Module(new DifftestInstrCommit)
//         dt_ic.io.clock    := clock
//         dt_ic.io.coreid   := 0.U
//         dt_ic.io.index    := 0.U
//         dt_ic.io.valid    := RegNext(pipeline.io.commit)
//         dt_ic.io.pc       := RegNext(pipeline.io.commit_pc)
//         dt_ic.io.instr    := RegNext(pipeline.io.commit_inst)
//         dt_ic.io.special  := 0.U
//         dt_ic.io.skip     := RegNext(skip)
//         dt_ic.io.isRVC    := false.B
//         dt_ic.io.scFailed := false.B
//         dt_ic.io.wen      := RegNext(pipeline.io.rf_rd_en)
//         dt_ic.io.wdata    := RegNext(pipeline.io.rf_rd_data)
//         dt_ic.io.wdest    := RegNext(pipeline.io.rf_rd_addr)

//         val dt_ae = Module(new DifftestArchEvent)
//         dt_ae.io.clock        := clock
//         dt_ae.io.coreid       := 0.U
//         dt_ae.io.intrNO       := RegNext(Mux(pipeline.io.commit_intr, pipeline.io.commit_cause(31, 0), 0.U))
//         dt_ae.io.cause        := RegNext(Mux(pipeline.io.commit_intr, pipeline.io.commit_cause, 0.U))
//         dt_ae.io.exceptionPC  := RegNext(Mux(pipeline.io.commit_intr, pipeline.io.commit_pc, 0.U))

//         val cycle_cnt = RegInit(0.U(64.W))
//         val instr_cnt = RegInit(0.U(64.W))

//         cycle_cnt := cycle_cnt + 1.U
//         instr_cnt := Mux(pipeline.io.commit, instr_cnt + 1.U, instr_cnt)

//         val rf_a0 = WireInit(0.U(64.W))
//         BoringUtils.addSink(rf_a0, "rf_a0")

//         val dt_te = Module(new DifftestTrapEvent)
//         dt_te.io.clock    := clock
//         dt_te.io.coreid   := 0.U
//         dt_te.io.valid    := (pipeline.io.commit_inst === "h0000006b".U || pipeline.io.commit_inst === "h00100073".U) && pipeline.io.commit
//         dt_te.io.code     := rf_a0(2, 0)
//         dt_te.io.pc       := pipeline.io.commit_pc
//         dt_te.io.cycleCnt := cycle_cnt
//         dt_te.io.instrCnt := instr_cnt
//     }
// }




// import chisel3._
// import chisel3.util._
// import Instructions._

// class ImemIO extends Bundle{
//   val en = Output(Bool())
//   val addr = Output(UInt(64.W))
//   val data = Input(UInt(32.W))
// }

// class DmemIO extends Bundle{
//   val ren   = Output(Bool())
//   val raddr = Output(UInt(64.W))
//   val rdata = Input(UInt(64.W))
//   val wen   = Output(Bool())
//   val waddr = Output(UInt(64.W))
//   val wdata = Output(UInt(64.W))
//   val wmask = Output(UInt(8.W))
// }

// class Core extends Module{
//   val io = IO(new Bundle{
//     val imem = new ImemIO
//     val dmem = new DmemIO
//   })

//   // val preifu  = Module(new PreIFetch)
//   val ifu     = Module(new IFetch)
//   val idu     = Module(new Decode)
//   val ieu     = Module(new Execution)
//   val rfu     = Module(new RegFile)
//   val preamu  = Module(new PreAccessMemory)
//   val amu     = Module(new AccessMemory)
//   val wbu     = Module(new WriteBack)

//   // val flushdelay       = Module(new JumpFlushDelay)
//   // val imemrh           = Module(new ImemoryReadHold)
//   val cconflict_exereg = Module(new CorrelationConflict)
//   val cconflict_memreg = Module(new CorrelationConflict)
//   val cconflict_wbreg  = Module(new CorrelationConflict)

//   //val ifreg   = Module(new IFReg)
//   val idreg   = Module(new IDReg)
//   val exereg  = Module(new ExeReg)
//   val memreg  = Module(new MemReg)
//   val wbreg   = Module(new WBReg)
//   //
//   rfu.io.clk    := clock
//   rfu.io.reset  := reset
 
//   //ifu
//   ifu.io.jump_en  := idu.io.jump_en
//   ifu.io.jump_pc  := idu.io.jump_pc
//   ifu.io.pc       := idreg.io.pc_out
//   //idreg
//   idreg.io.imem <> io.imem
//   idreg.io.pc_in  := ifu.io.next_pc
//   //idu
//   idu.io.pc       := idreg.io.pc_out
//   idu.io.inst     := idreg.io.inst_out
//   idu.io.rs1_data := rfu.io.rs1_data
//   idu.io.rs2_data := rfu.io.rs2_data
//   //exereg
//   exereg.io.pc_in       := idreg.io.pc_out
//   exereg.io.inst_in     := idreg.io.inst_out
//   exereg.io.rd_en_in    := idu.io.rd_en
//   exereg.io.rd_addr_in  := idu.io.rd_addr
//   exereg.io.imm_in      := idu.io.imm
//   exereg.io.op1_in      := idu.io.op1
//   exereg.io.op2_in      := idu.io.op2
//   exereg.io.decode_info_in <> idu.io.decode_info
//   //ieu
//   ieu.io.decode_info <> exereg.io.decode_info_out
//   ieu.io.op1 := exereg.io.op1_out
//   ieu.io.op2 := exereg.io.op2_out
//   ieu.io.pc  := exereg.io.pc_out
//   ieu.io.imm := exereg.io.imm_out
//   //memreg
//   memreg.io.pc_in      := exereg.io.pc_out
//   memreg.io.inst_in    := exereg.io.inst_out
//   memreg.io.rd_en_in   := exereg.io.rd_en_out
//   memreg.io.rd_addr_in := exereg.io.rd_addr_out
//   memreg.io.imm_in     := exereg.io.imm_out
//   memreg.io.op1_in     := exereg.io.op1_out
//   memreg.io.op2_in     := exereg.io.op2_out
//   memreg.io.decode_info_in <> exereg.io.decode_info_out

//   memreg.io.alu_out_in := ieu.io.alu_out
//   memreg.io.bu_out_in  := ieu.io.bu_out
//   memreg.io.mdu_out_in := ieu.io.mdu_out
//   //preamu
//   preamu.io.lu_code := memreg.io.decode_info_out.lu_code
//   preamu.io.su_code := memreg.io.decode_info_out.su_code
//   preamu.io.op1     := memreg.io.op1_out
//   preamu.io.op2     := memreg.io.op2_out
//   preamu.io.imm     := memreg.io.imm_out
//   //dmem
//   io.dmem.ren   := preamu.io.ren
//   io.dmem.raddr := preamu.io.raddr
//   io.dmem.wen   := preamu.io.wen & memreg.io.pr.valid_out //必须是有效的流水线指令才写入
//   io.dmem.waddr := preamu.io.waddr
//   io.dmem.wdata := preamu.io.wdata
//   io.dmem.wmask := preamu.io.wmask
//   //wbreg
//   wbreg.io.pc_in      := memreg.io.pc_out
//   wbreg.io.inst_in    := memreg.io.inst_out
//   wbreg.io.rd_en_in   := memreg.io.rd_en_out
//   wbreg.io.rd_addr_in := memreg.io.rd_addr_out
//   wbreg.io.alu_out_in := memreg.io.alu_out_out
//   wbreg.io.bu_out_in  := memreg.io.bu_out_out
//   wbreg.io.mdu_out_in := memreg.io.mdu_out_out
//   wbreg.io.fu_code_in := memreg.io.decode_info_out.fu_code
//   wbreg.io.lu_code_in := memreg.io.decode_info_out.lu_code
  
//   wbreg.io.lu_shift_in := preamu.io.lu_shift
//   //amu
//   amu.io.lu_code  := wbreg.io.lu_code_out
//   amu.io.lu_shift := wbreg.io.lu_shift_out
//   amu.io.rdata    := io.dmem.rdata
//   //wbu
//   wbu.io.fu_code := wbreg.io.fu_code_out
//   wbu.io.alu_out := wbreg.io.alu_out_out
//   wbu.io.bu_out  := wbreg.io.bu_out_out
//   wbu.io.mdu_out := wbreg.io.mdu_out_out
//   wbu.io.lu_out  := amu.io.lu_out


//   //rfu
//   rfu.io.rs1_en   := idu.io.rs1_en
//   rfu.io.rs2_en   := idu.io.rs2_en
//   rfu.io.rs1_addr := idu.io.rs1_addr
//   rfu.io.rs2_addr := idu.io.rs2_addr

//   rfu.io.rd_en    := wbreg.io.rd_en_out & wbreg.io.pr.valid_out //必须是有效的流水线指令才写入
//   rfu.io.rd_addr  := wbreg.io.rd_addr_out 
//   rfu.io.rd_data  := wbu.io.out
  
//   //相关性冲突
//   cconflict_exereg.io.rs_valid  := idreg.io.pr.valid_out
//   cconflict_exereg.io.rd_valid  := exereg.io.pr.valid_out
//   cconflict_exereg.io.rs1_en    := idu.io.rs1_en
//   cconflict_exereg.io.rs2_en    := idu.io.rs2_en
//   cconflict_exereg.io.rs1_addr  := idu.io.rs1_addr
//   cconflict_exereg.io.rs2_addr  := idu.io.rs2_addr
//   cconflict_exereg.io.rd_en     := exereg.io.rd_en_out
//   cconflict_exereg.io.rd_addr   := exereg.io.rd_addr_out

//   cconflict_memreg.io.rs_valid  := idreg.io.pr.valid_out
//   cconflict_memreg.io.rd_valid  := memreg.io.pr.valid_out
//   cconflict_memreg.io.rs1_en    := idu.io.rs1_en
//   cconflict_memreg.io.rs2_en    := idu.io.rs2_en
//   cconflict_memreg.io.rs1_addr  := idu.io.rs1_addr
//   cconflict_memreg.io.rs2_addr  := idu.io.rs2_addr
//   cconflict_memreg.io.rd_en     := memreg.io.rd_en_out
//   cconflict_memreg.io.rd_addr   := memreg.io.rd_addr_out

//   cconflict_wbreg.io.rs_valid   := idreg.io.pr.valid_out
//   cconflict_wbreg.io.rd_valid   := wbreg.io.pr.valid_out
//   cconflict_wbreg.io.rs1_en     := idu.io.rs1_en
//   cconflict_wbreg.io.rs2_en     := idu.io.rs2_en
//   cconflict_wbreg.io.rs1_addr   := idu.io.rs1_addr
//   cconflict_wbreg.io.rs2_addr   := idu.io.rs2_addr
//   cconflict_wbreg.io.rd_en      := wbreg.io.rd_en_out
//   cconflict_wbreg.io.rd_addr    := wbreg.io.rd_addr_out

//   //--------------------流水线控制------------------

//   val stall = cconflict_exereg.io.conflict || cconflict_memreg.io.conflict || cconflict_wbreg.io.conflict
//   //熄火的时候: 1.exereg的valid要为false.B
//   //          2.ifu维持原值
//   //          3.idreg维持原值
  
//   ifu.io.stall := stall

//   idreg.io.pr.valid_in  := ifu.io.valid
//   exereg.io.pr.valid_in := idreg.io.pr.valid_out && (!stall)
//   memreg.io.pr.valid_in := exereg.io.pr.valid_out
//   wbreg.io.pr.valid_in  := memreg.io.pr.valid_out
  
//   idreg.io.pr.en  := !stall
//   exereg.io.pr.en := true.B
//   memreg.io.pr.en := true.B
//   wbreg.io.pr.en  := true.B


  
//   // debug
//   //printf("pc=%x inst=%x valid=%d wen=%d waddr=%d wdata=%x stall=%d\n", wbreg.io.pc_out, wbreg.io.inst_out, wbreg.io.pr.valid_out, wbreg.io.rd_en_out, wbreg.io.rd_addr_out, wbu.io.out, stall)
//   // halt
//   val halt = Module(new Halt)
//   halt.io.clk   := clock
//   halt.io.reset := reset
//   halt.io.halt  := wbreg.io.inst_out === EBREAK || wbreg.io.inst_out === "h0000006b".U
//   // difftest
//   val difftest = Module(new Difftest)
//   difftest.io.valid := wbreg.io.pr.valid_out
//   difftest.io.pc    := wbreg.io.pc_out
// }


// class Halt extends BlackBox with HasBlackBoxInline{
//   val io = IO(new Bundle{
//     val clk = Input(Clock())
//     val reset = Input(Reset())  //csdn的教程错了，是Reset()才对，不是Bool()
//     val halt = Input(Bool())
//   })
//     setInline("Halt.v",
//             """
//            |import "DPI-C" function void read_halt(input logic halt);
//            |
//            |module Halt(input clk,
//            |            input reset,
//            |            input halt);
//            |
//            |  always @(posedge clk) begin
//            |    read_halt(halt);
//            |  end
//            |endmodule
//            |
//             """.stripMargin)
// }


// class DMemory extends BlackBox with HasBlackBoxInline{
//   val io = IO(new Bundle{
//     val clk   = Input(Clock())
//     val ren   = Input(Bool())
//     val raddr = Input(UInt(64.W))
//     val rdata = Output(UInt(64.W))
//     val wen   = Input(Bool())
//     val waddr = Input(UInt(64.W))
//     val wdata = Input(UInt(64.W))
//     val wmask = Input(UInt(8.W))
//   })
//     setInline("DMemory.v",
//             """
//            |import "DPI-C" function void pmem_read(input logic ren, input longint raddr, output longint rdata);
//            |import "DPI-C" function void pmem_write(input logic wen, input longint waddr, input longint wdata, input byte wmask);
//            |
//            |module DMemory(
//            |            input  clk,
//            |            input  ren,
//            |            input  [63:0] raddr,
//            |            output [63:0] rdata,
//            |            input  wen,
//            |            input  [63:0] waddr,
//            |            input  [63:0] wdata,
//            |            input  [7:0]  wmask);
//            |
//            |  always @(posedge clk) begin
//            |    pmem_read(ren, raddr, rdata);
//            |    pmem_write(wen, waddr, wdata, wmask);
//            |  end
//            |
//            |endmodule
//            |
//            |
//             """.stripMargin)
// }

// class IMemory extends BlackBox with HasBlackBoxInline{
//   val io = IO(new Bundle{
//     val clk   = Input(Clock())
//     val ren   = Input(Bool())
//     val raddr = Input(UInt(64.W))
//     val rdata = Output(UInt(32.W))
//   })
//     setInline("IMemory.v",
//             """
//            |import "DPI-C" function void imem_read(input logic ren, input longint raddr, output int rdata);
//            |
//            |module IMemory(
//            |            input  clk,
//            |            input  ren,
//            |            input  [63:0] raddr,
//            |            output reg [31:0] rdata);
//            |
//            |  wire [31:0] val; 
//            |
//            |  always @(*) begin
//            |    imem_read(ren, raddr, val);
//            |  end
//            |  
//            |  always @(posedge clk) begin
//            |    if (clk) begin
//            |      rdata <= val;
//            |    end else begin
//            |      rdata <= rdata;
//            |    end
//            |  end
//            |
//            |endmodule
//            |
//            |
//             """.stripMargin)
// }



// class Difftest extends BlackBox with HasBlackBoxInline{
//   val io = IO(new Bundle{
//     val valid = Input(Bool())
//     val pc = Input(UInt(64.W))
//   })
//   setInline("Difftest.v",
//             """
//            |import "DPI-C" function void read_difftest_valid(input logic valid);
//            |import "DPI-C" function void read_pc(input longint pc);
//            |
//            |module Difftest(input valid,
//            |                input [63:0] pc);
//            |
//            |  always @(*) begin
//            |    read_difftest_valid(valid);
//            |    read_pc(pc);
//            |  end
//            |
//            |endmodule
//            |
//             """.stripMargin)
// }



