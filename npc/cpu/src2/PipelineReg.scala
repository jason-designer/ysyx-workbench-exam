import chisel3._
import chisel3.util._
import Decode_constant._

class IDReg_BUS_R extends Bundle {
  val valid = Bool()
  val pc    = UInt(64.W)
  val intr  = Bool()
  val cause = UInt(64.W)
}

class IDReg extends Module {
    val io = IO(new Bundle {
        val en      = Input(Bool())
        val in      = Input(new IDReg_BUS_R)
        val out     = Output(new IDReg_BUS_R)
        // icache
        val imem    = new ImemIO
        val inst    = Output(UInt(32.W))
    })
    val valid   = RegEnable(io.in.valid, false.B, io.en)
    val pc = Config.soc match{
        case true   => RegEnable(io.in.pc, "h2ffffffc".U(64.W), io.en)
        case false  => RegEnable(io.in.pc, "h7ffffffc".U(64.W), io.en)
    }  
    val intr    = RegEnable(io.in.intr, false.B, io.en)
    val cause   = RegEnable(io.in.cause, 0.U(64.W), io.en)

    io.imem.addr    := io.in.pc
    io.imem.en      := io.en 
    io.inst         := io.imem.data

    io.out.valid    := valid
    io.out.pc       := pc
    io.out.intr     := intr
    io.out.cause    := cause
}

class ExeReg_BUS_R extends Bundle {
    val valid   = Bool()
    val pc      = UInt(64.W)
    val inst    = UInt(32.W)
    //
    val rd_en   = Bool()
    val rd_addr = UInt(5.W)
    val imm     = UInt(64.W)
    val op1     = UInt(64.W)
    val op2     = UInt(64.W)
    //
    val fu_code     = UInt(fu_code_length.W)
    val alu_code    = UInt(alu_code_length.W)
    val bu_code     = UInt(bu_code_length.W)
    val lu_code     = UInt(lu_code_length.W)
    val su_code     = UInt(su_code_length.W)
    val mu_code     = UInt(mu_code_length.W)
    val du_code     = UInt(du_code_length.W)
    val csru_code   = UInt(csru_code_length.W)
    //
    val rs1_addr    = UInt(5.W)
    val putch       = Bool()
    //
    val intr  = Bool()
    val cause = UInt(64.W)

    // def flush() : Unit = {
    //     valid       := false.B
    //     pc          := 0.U
    //     inst        := 0.U
    //     rd_en       := false.B
    //     rd_addr     := 0.U
    //     imm         := 0.U
    //     op1         := 0.U
    //     op2         := 0.U
    //     fu_code     := 0.U
    //     alu_code    := 0.U
    //     bu_code     := 0.U
    //     lu_code     := 0.U
    //     su_code     := 0.U
    //     mu_code     := 0.U
    //     du_code     := 0.U
    //     csru_code   := 0.U
    //     rs1_addr    := 0.U
    //     putch       := false.B
    //     intr        := false.B
    //     cause       := 0.U
    // }
}

class ExeReg extends Module {
    val io = IO(new Bundle {
        val en  = Input(Bool())
        // val flush = Input(Bool())
        val in  = Input(new ExeReg_BUS_R)
        val out = Output(new ExeReg_BUS_R)
    })
  val reg = RegEnable(io.in, 0.U.asTypeOf(new ExeReg_BUS_R), io.en)
//   when(io.flush){reg.flush()}
  io.out := reg
}

class MemReg_BUS_R extends Bundle {
    val valid   = Bool()
    val pc      = UInt(64.W)
    val inst    = UInt(32.W)
    //
    val rd_en   = Bool()
    val rd_addr = UInt(5.W)
    //
    val imm     = UInt(64.W)
    val op1     = UInt(64.W)
    val op2     = UInt(64.W)
    //
    val alu_out = UInt(64.W)
    val bu_out  = UInt(64.W)
    val mu_out  = UInt(64.W)
    val du_out  = UInt(64.W)
    val csru_out = UInt(64.W)
    //
    val fu_code     = UInt(fu_code_length.W)
    val alu_code    = UInt(alu_code_length.W)
    val bu_code     = UInt(bu_code_length.W)
    val lu_code     = UInt(lu_code_length.W)
    val su_code     = UInt(su_code_length.W)
    val mu_code     = UInt(mu_code_length.W)
    val du_code     = UInt(du_code_length.W)
    val csru_code   = UInt(csru_code_length.W)
    //
    val putch   = Bool()
    //
    val csr_wen = Bool()
    val csr_waddr = UInt(12.W)
    val csr_wdata = UInt(64.W)
    //
    val intr  = Bool()
    val cause = UInt(64.W)

    // def flush() : Unit = {
    //     valid       := false.B
    //     pc          := 0.U
    //     inst        := 0.U
    //     rd_en       := false.B
    //     rd_addr     := 0.U
    //     imm         := 0.U
    //     op1         := 0.U
    //     op2         := 0.U
    //     alu_out     := 0.U
    //     bu_out      := 0.U
    //     mu_out      := 0.U
    //     du_out      := 0.U
    //     csru_out    := 0.U
    //     fu_code     := 0.U
    //     alu_code    := 0.U
    //     bu_code     := 0.U
    //     lu_code     := 0.U
    //     su_code     := 0.U
    //     mu_code     := 0.U
    //     du_code     := 0.U
    //     csru_code   := 0.U
    //     putch       := false.B
    //     csr_wen     := false.B
    //     csr_waddr   := 0.U
    //     csr_wdata   := 0.U
    //     intr        := false.B
    //     cause       := 0.U
    // }
}

class MemReg extends Module {
    val io = IO(new Bundle {
        val en  = Input(Bool())
        // val flush = Input(Bool())
        val in  = Input(new MemReg_BUS_R)
        val out = Output(new MemReg_BUS_R)
    })
  val reg = RegEnable(io.in, 0.U.asTypeOf(new MemReg_BUS_R), io.en)
//   when(io.flush){reg.flush()}
  io.out := reg
}

class WBReg_BUS_R extends Bundle {
    val valid   = Bool()
    val pc      = UInt(64.W)
    val inst    = UInt(32.W)
    //
    val rd_en   = Bool()
    val rd_addr = UInt(5.W)
    //
    val alu_out = UInt(64.W)
    val bu_out  = UInt(64.W)
    val mu_out  = UInt(64.W)
    val du_out  = UInt(64.W)
    val csru_out = UInt(64.W)
    //
    val fu_code     = UInt(fu_code_length.W)
    val lu_code     = UInt(lu_code_length.W)
    val csru_code   = UInt(csru_code_length.W)
    //
    val lu_shift = UInt(6.W)
    //
    val putch   = Bool()
    //
    val csr_wen = Bool()
    val csr_waddr = UInt(12.W)
    val csr_wdata = UInt(64.W)
    //
    val intr  = Bool()
    val cause = UInt(64.W)

    // def flush() : Unit = {
    //     valid       := false.B
    //     pc          := 0.U
    //     inst        := 0.U
    //     rd_en       := false.B
    //     rd_addr     := 0.U
    //     alu_out     := 0.U
    //     bu_out      := 0.U
    //     mu_out      := 0.U
    //     du_out      := 0.U
    //     csru_out    := 0.U
    //     fu_code     := 0.U
    //     lu_code     := 0.U
    //     csru_code   := 0.U
    //     lu_shift    := 0.U
    //     putch       := false.B
    //     csr_wen     := false.B
    //     csr_waddr   := 0.U
    //     csr_wdata   := 0.U
    //     intr        := false.B
    //     cause       := 0.U
    // }
}

class WBReg extends Module {
    val io = IO(new Bundle {
        val en  = Input(Bool())
        // val flush = Input(Bool())
        val in  = Input(new WBReg_BUS_R)
        val out = Output(new WBReg_BUS_R)
    })
  val reg = RegEnable(io.in, 0.U.asTypeOf(new WBReg_BUS_R), io.en)
//   when(io.flush){reg.flush()}
  io.out := reg
}

class CorrelationConflict extends Module{
    val io = IO(new Bundle{
        val rs_valid    = Input(Bool())
        val rd_valid    = Input(Bool())
        val rs1_en      = Input(Bool())
        val rs2_en      = Input(Bool())
        val rs1_addr    = Input(UInt(5.W))
        val rs2_addr    = Input(UInt(5.W))
        val rd_en       = Input(Bool())
        val rd_addr     = Input(UInt(5.W))

        val conflict    = Output(Bool())
    })
    val inst_valid      = io.rs_valid && io.rd_valid
    val rs1_conflict    = io.rs1_en && (io.rs1_addr === io.rd_addr)
    val rs2_conflict    = io.rs2_en && (io.rs2_addr === io.rd_addr)
    val rd_valid        = (io.rd_addr =/= 0.U) && io.rd_en

    io.conflict := inst_valid && rd_valid && (rs1_conflict || rs2_conflict)
}

class RegfileConflict extends Module{
    val io = IO(new Bundle{
        val rs_valid    = Input(Bool())
        val rs1_en      = Input(Bool())
        val rs2_en      = Input(Bool())
        val rs1_addr    = Input(UInt(5.W))
        val rs2_addr    = Input(UInt(5.W))
        //
        val rd1_valid   = Input(Bool())
        val rd1_en      = Input(Bool())
        val rd1_addr    = Input(UInt(5.W))
        val rd2_valid   = Input(Bool())
        val rd2_en      = Input(Bool())
        val rd2_addr    = Input(UInt(5.W))
        val rd3_valid   = Input(Bool())
        val rd3_en      = Input(Bool())
        val rd3_addr    = Input(UInt(5.W))
        //
        val conflict    = Output(Bool())
    })
    val cconflict1 = Module(new CorrelationConflict)
    val cconflict2 = Module(new CorrelationConflict)
    val cconflict3 = Module(new CorrelationConflict)

    cconflict1.io.rs_valid  := io.rs_valid
    cconflict1.io.rd_valid  := io.rd1_valid
    cconflict1.io.rs1_en    := io.rs1_en
    cconflict1.io.rs2_en    := io.rs2_en
    cconflict1.io.rs1_addr  := io.rs1_addr
    cconflict1.io.rs2_addr  := io.rs2_addr
    cconflict1.io.rd_en     := io.rd1_en
    cconflict1.io.rd_addr   := io.rd1_addr

    cconflict2.io.rs_valid  := io.rs_valid
    cconflict2.io.rd_valid  := io.rd2_valid
    cconflict2.io.rs1_en    := io.rs1_en
    cconflict2.io.rs2_en    := io.rs2_en
    cconflict2.io.rs1_addr  := io.rs1_addr
    cconflict2.io.rs2_addr  := io.rs2_addr
    cconflict2.io.rd_en     := io.rd2_en
    cconflict2.io.rd_addr   := io.rd2_addr

    cconflict3.io.rs_valid  := io.rs_valid
    cconflict3.io.rd_valid  := io.rd3_valid
    cconflict3.io.rs1_en    := io.rs1_en
    cconflict3.io.rs2_en    := io.rs2_en
    cconflict3.io.rs1_addr  := io.rs1_addr
    cconflict3.io.rs2_addr  := io.rs2_addr
    cconflict3.io.rd_en     := io.rd3_en
    cconflict3.io.rd_addr   := io.rd3_addr

    io.conflict := cconflict1.io.conflict || cconflict2.io.conflict || cconflict3.io.conflict
}


