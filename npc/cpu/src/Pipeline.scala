import chisel3._
import chisel3.util._
import chisel3.util.experimental._
import Decode_constant._
import Instructions._

class ImemIO extends Bundle{
    val en          = Output(Bool())
    val addr        = Output(UInt(64.W))
    val data        = Input(UInt(32.W))
}

class DmemIO extends Bundle{
    val ren   = Output(Bool())
    val raddr = Output(UInt(64.W))
    val wen   = Output(Bool())
    val waddr = Output(UInt(64.W))
    val wdata = Output(UInt(64.W))
    val wmask = Output(UInt(8.W))
    val rdata = Input(UInt(64.W))
}

class Pipeline extends Module{
    val io = IO(new Bundle{
        val imem = new ImemIO
        val dmem = new DmemIO
        val dmem_transfer = Output(UInt(32.W))

        val rs1_addr = Output(UInt(5.W))
        val rs2_addr = Output(UInt(5.W))
        val rs1_data = Input(UInt(64.W))
        val rs2_data = Input(UInt(64.W))

        val rfconflict  = Output(Bool())

        val mu_code     = Output(UInt(mu_code_length.W))
        val mu_op1      = Output(UInt(64.W))
        val mu_op2      = Output(UInt(64.W))
        val mu_out      = Input(UInt(64.W))

        val du_code     = Output(UInt(du_code_length.W))
        val du_op1      = Output(UInt(64.W))
        val du_op2      = Output(UInt(64.W))
        val du_out      = Input(UInt(64.W))
        // csr
        val csr_raddr   = Output(UInt(12.W))
        val csr_rdata   = Input(UInt(64.W))
        val csr_wen     = Output(Bool())
        val csr_waddr   = Output(UInt(12.W))
        val csr_wdata   = Output(UInt(64.W))

        val csr_mtvec   = Input(UInt(64.W))
        val csr_mepc    = Input(UInt(64.W))
        val id_ecall    = Output(Bool())
        val id_mret     = Output(Bool())
        val id_pc       = Output(UInt(64.W))

        val intr        = Input(Bool())         // 中断请求
        val cause       = Input(UInt(64.W))     // 异常号
        val id_intr     = Output(Bool())
        val id_cause    = Output(UInt(64.W))
        // fence
        val id_fencei   = Output(Bool())
        
        // pipeline control
        val stall_id    = Input(Bool())
        val stall_ie    = Input(Bool())
        val stall_mem   = Input(Bool())
        val stall_wb    = Input(Bool())

        val id_valid    = Output(Bool())
        val ie_valid    = Output(Bool())
        val mem_valid   = Output(Bool())
        val wb_valid    = Output(Bool())
        // commit
        val commit      = Output(Bool())
        val commit_pc   = Output(UInt(64.W))
        val commit_inst = Output(UInt(32.W))

        val rf_rd_en    = Output(Bool())
        val rf_rd_addr  = Output(UInt(5.W))
        val rf_rd_data  = Output(UInt(64.W))

        val commit_intr  = Output(Bool())
        val commit_cause = Output(UInt(64.W))

        val putch       = Output(Bool())

        val commit_clint = Output(Bool())   // 用于skip掉difftest

        // info
        val mem_pc      = Output(UInt(64.W))
        val mem_inst    = Output(UInt(32.W))

        val commit_dmem_ren     = Output(Bool())        // use to skip difftest
        val commit_dmem_raddr   = Output(UInt(64.W))
        val commit_dmem_wen     = Output(Bool())
        val commit_dmem_waddr   = Output(UInt(64.W))
    })
    val ifu     = Module(new IFetch)
    val idu     = Module(new Decode)
    val ieu     = Module(new Execution)
    val preamu  = Module(new PreAccessMemory)
    val amu     = Module(new AccessMemory)
    val wbu     = Module(new WriteBack)

    val idreg   = Module(new IDReg)
    val exereg  = Module(new ExeReg)
    val memreg  = Module(new MemReg)
    val wbreg   = Module(new WBReg)

    val rfconflict  = Module(new RegfileConflict)

    //ifu
    ifu.io.jump_en  := idu.io.jump_en
    ifu.io.jump_pc  := idu.io.jump_pc
    ifu.io.pc       := idreg.io.out.pc
    //idreg
    io.imem.addr        := idreg.io.imem.addr 
    io.imem.en          := idreg.io.imem.en
    idreg.io.imem.data  := io.imem.data
    idreg.io.in.pc      := ifu.io.next_pc

    idreg.io.in.intr    := io.intr
    idreg.io.in.cause   := io.cause
    io.id_intr          := idreg.io.out.intr
    io.id_cause         := idreg.io.out.cause

    io.id_fencei        := idreg.io.inst === FENCEI
    //idu
    idu.io.pc       := idreg.io.out.pc
    idu.io.inst     := idreg.io.inst
    idu.io.rs1_data := io.rs1_data
    idu.io.rs2_data := io.rs2_data
    io.rs1_addr     := idu.io.rs1_addr
    io.rs2_addr     := idu.io.rs2_addr
    idu.io.mtvec    := io.csr_mtvec
    idu.io.mepc     := io.csr_mepc

    io.id_ecall     := idreg.io.inst === ECALL
    io.id_mret      := idreg.io.inst === MRET
    io.id_pc        := idreg.io.out.pc
    idu.io.intr     := idreg.io.out.intr
    //exereg
    exereg.io.in.pc         := idreg.io.out.pc
    exereg.io.in.inst       := idreg.io.inst
    exereg.io.in.intr       := Mux(io.stall_id, false.B, idreg.io.out.intr)
    exereg.io.in.cause      := idreg.io.out.cause
    exereg.io.in.rd_en      := idu.io.rd_en
    exereg.io.in.rd_addr    := idu.io.rd_addr
    exereg.io.in.imm        := idu.io.imm
    exereg.io.in.op1        := idu.io.op1
    exereg.io.in.op2        := idu.io.op2
    exereg.io.in.rs1_addr   := idu.io.rs1_addr
    exereg.io.in.fu_code    := idu.io.decode_info.fu_code
    exereg.io.in.alu_code   := idu.io.decode_info.alu_code
    exereg.io.in.bu_code    := idu.io.decode_info.bu_code
    exereg.io.in.mu_code    := idu.io.decode_info.mu_code
    exereg.io.in.du_code    := idu.io.decode_info.du_code
    exereg.io.in.lu_code    := idu.io.decode_info.lu_code
    exereg.io.in.su_code    := idu.io.decode_info.su_code
    exereg.io.in.csru_code  := idu.io.decode_info.csru_code
    exereg.io.in.putch      := idu.io.putch
    
    //ieu
    ieu.io.fu_code      := exereg.io.out.fu_code
    ieu.io.alu_code     := exereg.io.out.alu_code
    ieu.io.bu_code      := exereg.io.out.bu_code
    ieu.io.lu_code      := exereg.io.out.lu_code
    ieu.io.su_code      := exereg.io.out.su_code
    ieu.io.csru_code    := exereg.io.out.csru_code
    ieu.io.op1          := exereg.io.out.op1
    ieu.io.op2          := exereg.io.out.op2
    ieu.io.pc           := exereg.io.out.pc
    ieu.io.imm          := exereg.io.out.imm
    ieu.io.rs1_addr     := exereg.io.out.rs1_addr
    ieu.io.csr_rdata    := io.csr_rdata
    io.csr_raddr        := ieu.io.csr_raddr

    // mu.io.en      := exereg.io.out.valid && (exereg.io.out.mu_code =/= 0.U)
    io.mu_code      := exereg.io.out.mu_code
    io.mu_op1       := exereg.io.out.op1
    io.mu_op2       := exereg.io.out.op2

    // du.io.en      := exereg.io.out.valid && (exereg.io.out.du_code =/= 0.U)
    io.du_code      := exereg.io.out.du_code
    io.du_op1       := exereg.io.out.op1
    io.du_op2       := exereg.io.out.op2
    //memreg
    memreg.io.in.pc       := exereg.io.out.pc
    memreg.io.in.inst     := exereg.io.out.inst
    memreg.io.in.intr     := exereg.io.out.intr
    memreg.io.in.cause    := exereg.io.out.cause
    memreg.io.in.rd_en    := exereg.io.out.rd_en
    memreg.io.in.rd_addr  := exereg.io.out.rd_addr
    memreg.io.in.imm      := exereg.io.out.imm
    memreg.io.in.op1      := exereg.io.out.op1
    memreg.io.in.op2      := exereg.io.out.op2
    memreg.io.in.fu_code  := exereg.io.out.fu_code
    memreg.io.in.alu_code := exereg.io.out.alu_code
    memreg.io.in.bu_code  := exereg.io.out.bu_code
    memreg.io.in.mu_code  := exereg.io.out.mu_code
    memreg.io.in.du_code  := exereg.io.out.du_code
    memreg.io.in.lu_code  := exereg.io.out.lu_code
    memreg.io.in.su_code  := exereg.io.out.su_code
    memreg.io.in.csru_code := exereg.io.out.csru_code

    memreg.io.in.alu_out  := ieu.io.alu_out
    memreg.io.in.bu_out   := ieu.io.bu_out
    memreg.io.in.mu_out   := io.mu_out
    memreg.io.in.du_out   := io.du_out
    memreg.io.in.csru_out := ieu.io.csru_out

    memreg.io.in.putch      := exereg.io.out.putch
    memreg.io.in.csr_wen    := ieu.io.csr_wen
    memreg.io.in.csr_waddr  := ieu.io.csr_waddr
    memreg.io.in.csr_wdata  := ieu.io.csr_wdata

    io.mem_pc   := memreg.io.out.pc
    io.mem_inst := memreg.io.out.inst
    //preamu
    preamu.io.lu_code := memreg.io.out.lu_code
    preamu.io.su_code := memreg.io.out.su_code
    preamu.io.op1     := memreg.io.out.op1
    preamu.io.op2     := memreg.io.out.op2
    preamu.io.imm     := memreg.io.out.imm
    //dmem
    // val dmem_en = preamu.io.ren || preamu.io.wen 
    // val dmem_op = preamu.io.wen   // 按理说ren和wen不会同时为true
    // val dmem_addr = Mux(dmem_op, preamu.io.waddr, preamu.io.raddr)
    // io.dmem.en    := dmem_en & memreg.io.out.valid //必须是有效的流水线指令才读写
    // io.dmem.op    := dmem_op
    // io.dmem.addr  := dmem_addr
    // io.dmem.wdata := preamu.io.wdata
    // io.dmem.wmask := preamu.io.wmask
    // io.dmem.transfer := preamu.io.transfer
    io.dmem.ren     := preamu.io.ren
    io.dmem.raddr   := preamu.io.raddr
    io.dmem.wen     := preamu.io.wen
    io.dmem.waddr   := preamu.io.waddr
    io.dmem.wdata   := preamu.io.wdata
    io.dmem.wmask   := preamu.io.wmask
    io.dmem_transfer := preamu.io.transfer
    //wbreg
    wbreg.io.in.pc        := memreg.io.out.pc
    wbreg.io.in.inst      := memreg.io.out.inst
    wbreg.io.in.intr      := memreg.io.out.intr
    wbreg.io.in.cause     := memreg.io.out.cause
    wbreg.io.in.rd_en     := memreg.io.out.rd_en
    wbreg.io.in.rd_addr   := memreg.io.out.rd_addr
    wbreg.io.in.alu_out   := memreg.io.out.alu_out
    wbreg.io.in.bu_out    := memreg.io.out.bu_out
    wbreg.io.in.mu_out    := memreg.io.out.mu_out
    wbreg.io.in.du_out    := memreg.io.out.du_out
    wbreg.io.in.csru_out  := memreg.io.out.csru_out
    wbreg.io.in.fu_code   := memreg.io.out.fu_code
    wbreg.io.in.lu_code   := memreg.io.out.lu_code
    wbreg.io.in.csru_code := memreg.io.out.csru_code
    
    wbreg.io.in.lu_shift  := preamu.io.lu_shift

    wbreg.io.in.putch     := memreg.io.out.putch
    wbreg.io.in.csr_wen   := memreg.io.out.csr_wen
    wbreg.io.in.csr_waddr := memreg.io.out.csr_waddr
    wbreg.io.in.csr_wdata := memreg.io.out.csr_wdata

    // wbreg.io.in.csr_set_mtip    := false.B//////////////////////io.set_mtip
    // wbreg.io.in.csr_clear_mtip  := false.B//////////////////////io.clear_mtip
    //amu
    amu.io.lu_code  := wbreg.io.out.lu_code
    amu.io.lu_shift := wbreg.io.out.lu_shift
    amu.io.rdata    := io.dmem.rdata
    //wbu
    wbu.io.fu_code  := wbreg.io.out.fu_code
    wbu.io.alu_out  := wbreg.io.out.alu_out
    wbu.io.bu_out   := wbreg.io.out.bu_out
    wbu.io.mu_out   := wbreg.io.out.mu_out
    wbu.io.du_out   := wbreg.io.out.du_out
    wbu.io.csru_out := wbreg.io.out.csru_out
    wbu.io.lu_out   := amu.io.lu_out

    //rfu
    // rfu.io.rs1_en   := idu.io.rs1_en
    // rfu.io.rs2_en   := idu.io.rs2_en
    
    
    // rfu.io.rd_data  := Mux(wbreg.io.inst_out === "hff86b683".U, csru.io.mcycle, wbu.io.out)
    

    //csru
    // csru.io.raddr     := ieu.io.csr_raddr
    // csru.io.waddr     := wbreg.io.out.csr_waddr
    // csru.io.wdata     := wbreg.io.out.csr_wdata

    // csru.io.set_mtip    := wbreg.io.out.csr_set_mtip
    // csru.io.clear_mtip  := wbreg.io.out.csr_clear_mtip
    
    /*********************** 相关性冲突 ***********************/
    rfconflict.io.rs_valid   := idreg.io.out.valid
    rfconflict.io.rs1_en     := idu.io.rs1_en
    rfconflict.io.rs2_en     := idu.io.rs2_en
    rfconflict.io.rs1_addr   := idu.io.rs1_addr
    rfconflict.io.rs2_addr   := idu.io.rs2_addr
    rfconflict.io.rd1_valid  := exereg.io.out.valid
    rfconflict.io.rd1_en     := exereg.io.out.rd_en
    rfconflict.io.rd1_addr   := exereg.io.out.rd_addr
    rfconflict.io.rd2_valid  := memreg.io.out.valid
    rfconflict.io.rd2_en     := memreg.io.out.rd_en
    rfconflict.io.rd2_addr   := memreg.io.out.rd_addr
    rfconflict.io.rd3_valid  := wbreg.io.out.valid
    rfconflict.io.rd3_en     := wbreg.io.out.rd_en
    rfconflict.io.rd3_addr   := wbreg.io.out.rd_addr

    //--------------------流水线控制------------------
    // val stall_id = Wire(Bool())
    // val stall_ie = Wire(Bool())
    // val stall_mem = 
    // val stall_wb = Wire(Bool())
    // val imem_not_ok = !io.imem.ok
    // val dmem_not_ok = !io.dmem.ok

    // 对于异常调用的处理------------------------------------------------------
    // 当idreg遇到ecall或mret的时候阻塞idreg，直到流水线清空
    // 当idreg遇到ecall或mret时，且流水线为空，且idreg不阻塞时（exception_stall不阻塞，但是其他东西在阻塞，例如imem_not_ok），则对csr进行写入
    // val exception_stall = (idreg.io.inst === ECALL || idreg.io.inst === MRET) && (exereg.io.out.valid || memreg.io.out.valid || wbreg.io.out.valid)
    // val exception_execution = !stall_id && (idreg.io.inst === ECALL || idreg.io.inst === MRET) && !exereg.io.out.valid && !memreg.io.out.valid && !wbreg.io.out.valid
    // csru.io.exception := exception_execution && idreg.io.inst === ECALL
    // csru.io.mret      := exception_execution && idreg.io.inst === MRET
    // csru.io.cause     := Mux(csru.io.time_intr, "h8000000000000007".U, "hb".U)
    // csru.io.pc        := idreg.io.out.pc
    // 对于时钟中断的处理
    // idreg.io.imem.data  := Mux(csru.io.time_intr, "h00000073".U, io.imem.data)

    // 对于fence.i的处理------------------------------------------------------
    // 当遇到fence.i时，首先要清空流水线，清空后给go信号让fence执行，等到fence执行完就继续流动
    // val fence_wait = idreg.io.inst === FENCEI && (exereg.io.out.valid || memreg.io.out.valid || wbreg.io.out.valid)
    // fence.io.go := idreg.io.inst === FENCEI && !exereg.io.out.valid && !memreg.io.out.valid && !wbreg.io.out.valid
    // val fence_running = !fence.io.ok

    // fence.io.ifence <> io.ifence
    // fence.io.dfence <> io.dfence

    // 熄火的时候（暂停idreg以及自前的流水线）: --------------------------------
    //    1.exereg的valid要为false.B
    //    2.ifu维持原值
    //    3.idreg维持原值(en为false)
    //    其实2和3只要实现一个就能保证功能正确，这里两个都实现了，后期看情况再修改.
    // stall_id := rfconflict.io.conflict || imem_not_ok || exception_stall || fence_wait || fence_running

    // mul和div需要阻塞ie级
    // stall_ie := mu.io.stall || du.io.stall

    // 全部熄火（这时候要等待dmem加载完成,暂停整个流水线）:----------------------
    //    1.全部流水线寄存器都保持原值
    //    2.wbreg的输出valid要为false.B，也就是rfu.io.rf_en要为false
    // stall_wb := dmem_not_ok
    
    
    idreg.io.in.valid   := ifu.io.valid && !io.intr     // difftest不把intr当作commit
    exereg.io.in.valid  := idreg.io.out.valid && !io.stall_id
    memreg.io.in.valid  := exereg.io.out.valid && !io.stall_ie
    wbreg.io.in.valid   := memreg.io.out.valid && !io.stall_mem
    val commit_valid    = wbreg.io.out.valid && !io.stall_wb
    
    idreg.io.en     := !io.stall_wb && !io.stall_mem && !io.stall_ie && !io.stall_id
    exereg.io.en    := !io.stall_wb && !io.stall_mem && !io.stall_ie
    memreg.io.en    := !io.stall_wb && !io.stall_mem 
    wbreg.io.en     := !io.stall_wb 


    // pipeline commit
    io.id_valid     := idreg.io.out.valid
    io.ie_valid     := exereg.io.out.valid
    io.mem_valid    := memreg.io.out.valid
    io.wb_valid     := wbreg.io.out.valid

    io.rfconflict   := rfconflict.io.conflict

    io.commit       := commit_valid
    io.commit_inst  := wbreg.io.out.inst
    io.commit_pc    := wbreg.io.out.pc

    io.rf_rd_en     := wbreg.io.out.rd_en
    io.rf_rd_addr   := wbreg.io.out.rd_addr
    io.rf_rd_data   := wbu.io.out

    io.csr_wen      := wbreg.io.out.csr_wen
    io.csr_waddr    := wbreg.io.out.csr_waddr
    io.csr_wdata    := wbreg.io.out.csr_wdata

    io.commit_intr  := wbreg.io.out.intr
    io.commit_cause := wbreg.io.out.cause

    io.putch        := wbreg.io.out.putch


    val dmem_read_clint  = io.dmem.ren && (io.dmem.raddr === "h0200bff8".U || io.dmem.raddr === "h02004000".U)
    val dmem_write_clint = io.dmem.wen && (io.dmem.waddr === "h0200bff8".U || io.dmem.waddr === "h02004000".U)
    io.commit_clint := commit_valid && RegNext(dmem_read_clint || dmem_write_clint)

    io.commit_dmem_ren      := RegEnable(io.dmem.ren, false.B, wbreg.io.en)
    io.commit_dmem_raddr    := RegEnable(io.dmem.raddr, 0.U(64.W), wbreg.io.en)
    io.commit_dmem_wen      := RegEnable(io.dmem.wen, false.B, wbreg.io.en)
    io.commit_dmem_waddr    := RegEnable(io.dmem.waddr, 0.U(64.W), wbreg.io.en)
}
