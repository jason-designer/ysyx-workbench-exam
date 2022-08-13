import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import difftest._
import Instructions._

trait CsrConstant {
    def MSTATUS     = "h300".U
    def MTVEC       = "h305".U
    def MEPC        = "h341".U
    def MCAUSE      = "h342".U
    def MCYCLE      = "hB00".U
    def MHARTID     = "hF14".U
    def MIE         = "h304".U
    def MIP         = "h344".U
    def MSCRATCH    = "h340".U
    def SATP        = "h180".U

    def MSTATUS_FS_DIRTY = "b11".U
    def MSTATUS_XS_SOME_DIRTY = "b11".U
}

class Csr extends Module with CsrConstant{
    val io = IO(new Bundle{
        val raddr = Input(UInt(12.W))
        val rdata = Output(UInt(64.W))
        val wen   = Input(Bool())
        val waddr = Input(UInt(12.W))
        val wdata = Input(UInt(64.W))

        val mtvec       = Output(UInt(64.W))
        val mepc        = Output(UInt(64.W))
        val ecall       = Input(Bool())
        val mret        = Input(Bool())
        val pc          = Input(UInt(64.W))
        
        val time_intr   = Output(Bool())
        val interrupt   = Input(Bool())         // 中断异常
        val cause       = Input(UInt(64.W))     // 异常号

        val set_mtip    = Input(Bool())
        val clear_mtip  = Input(Bool())     
    })
    // Csr
    val mstatus     = RegInit("h00001800".U(64.W))
    val mtvec       = RegInit(0.U(64.W))
    val mepc        = RegInit(0.U(64.W))
    val mcause      = RegInit(0.U(64.W))
    val mcycle      = RegInit(0.U(64.W))

    val mhartid     = RegInit(0.U(64.W))
    val mie         = RegInit(0.U(64.W))
    val mip         = RegInit(0.U(64.W))
    val mscratch    = RegInit(0.U(64.W))
    val satp        = RegInit(0.U(64.W))
    // Csr read --------------------------------------
    io.rdata := MuxLookup(io.raddr, 0.U, Array(
        MSTATUS     -> mstatus,
        MTVEC       -> mtvec,
        MEPC        -> mepc,
        MCAUSE      -> mcause,
        MCYCLE      -> mcycle,
        MHARTID     -> mhartid,
        MIE         -> mie,
        MIP         -> mip,
        MSCRATCH    -> mscratch,
        SATP        -> satp
    ))
    // Csr val change ---------------------------------
    mcycle  := Mux(io.wen && io.waddr === MCYCLE, io.wdata, mcycle + 1.U) 
    // mstatus
    val mstatus_SD = io.wdata(14, 13) === MSTATUS_FS_DIRTY || io.wdata(16, 15) === MSTATUS_XS_SOME_DIRTY
    
    when(io.interrupt || io.ecall){ 
        mstatus := Cat(mstatus(63,13), Fill(2, 1.U), mstatus(10,8), mstatus(3), mstatus(6, 4), 0.U, mstatus(2, 0))
    }
    .elsewhen(io.mret){ // mret
        mstatus := Cat(mstatus(63,13), Fill(2, 0.U), mstatus(10,8), 1.U, mstatus(6, 4), mstatus(7), mstatus(2, 0))
    }
    .elsewhen(io.wen && io.waddr === MSTATUS){
        mstatus := Cat(mstatus_SD, io.wdata(62, 0))  // mstatus的SD位是只读的，含义是FS或XS是否有dirty
    }
    .otherwise{
        mstatus := mstatus
    }
    // mtvec
    mtvec := Mux(io.wen && io.waddr === MTVEC, io.wdata, mtvec)
    // mepc
    when(io.interrupt || io.ecall) {mepc := io.pc} // ecall
    .elsewhen(io.wen && io.waddr === MEPC) {mepc := Cat(io.wdata(63, 2), 0.U(2.W))}
    .otherwise {mepc := mepc}
    // mcause
    when(io.interrupt) {mcause := io.cause} 
    .elsewhen(io.ecall) {mcause := "hb".U} // ecall
    .elsewhen(io.wen && io.waddr === MCAUSE) {mcause := io.wdata}
    .otherwise {mcause := mcause}
    // mip
    when(io.clear_mtip) {mip := mip & "hffffffffffffff7f".U}        // clear的优先级要高于set
    .elsewhen(io.set_mtip) {mip := mip | "h0000000000000080".U}
    .elsewhen(io.wen && io.waddr === MIP) {mip := Cat(io.wdata(63, 8), mip(7), io.wdata(6, 0))}  // mtip位只读
    // .elsewhen(io.wen && io.waddr === MIP) {mip := io.wdata}  // mtip位只读
    .otherwise {mip := mip}
    // mhartid, mie, mscratch, sato
    mhartid     := Mux(io.wen && io.waddr === MHARTID, io.wdata, mhartid) 
    mie         := Mux(io.wen && io.waddr === MIE, io.wdata, mie) 
    mscratch    := Mux(io.wen && io.waddr === MSCRATCH, io.wdata, mscratch) 
    satp        := Mux(io.wen && io.waddr === SATP, io.wdata, satp) 
    
    // Csr output-----------------------------------------------------
    io.mtvec := mtvec
    io.mepc  := mepc
    io.time_intr := mip(7) && mie(7) && mstatus(3)

    /************** difftest for CSR state *****************/
    if(Config.soc == false){
        val dt_cs = Module(new DifftestCSRState)
        dt_cs.io.clock          := clock
        dt_cs.io.coreid         := 0.U
        dt_cs.io.priviledgeMode := 3.U        // machine mode
        dt_cs.io.mstatus        := mstatus
        dt_cs.io.sstatus        := mstatus & "h80000003000de122".U
        dt_cs.io.mepc           := mepc
        dt_cs.io.sepc           := 0.U
        dt_cs.io.mtval          := 0.U
        dt_cs.io.stval          := 0.U
        dt_cs.io.mtvec          := mtvec
        dt_cs.io.stvec          := 0.U
        dt_cs.io.mcause         := mcause
        dt_cs.io.scause         := 0.U
        dt_cs.io.satp           := satp
        // dt_cs.io.mip            := mip
        dt_cs.io.mie            := mie
        dt_cs.io.mscratch       := mscratch
        dt_cs.io.sscratch       := 0.U
        dt_cs.io.mideleg        := 0.U
        dt_cs.io.medeleg        := 0.U
    }
}
