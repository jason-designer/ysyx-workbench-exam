import chisel3._
import chisel3.util._
import Decode_constant._

class Execution extends Module{
    val io = IO(new Bundle{
        val fu_code     = Input(UInt(fu_code_length.W))
        val alu_code    = Input(UInt(alu_code_length.W))
        val bu_code     = Input(UInt(bu_code_length.W))
        val lu_code     = Input(UInt(lu_code_length.W))
        val su_code     = Input(UInt(su_code_length.W))
        val csru_code   = Input(UInt(csru_code_length.W))

        val op1 = Input(UInt(64.W))
        val op2 = Input(UInt(64.W))
        val pc  = Input(UInt(64.W))
        val imm = Input(UInt(64.W))

        val alu_out     = Output(UInt(64.W))
        val bu_out      = Output(UInt(64.W))
        val csru_out    = Output(UInt(64.W))

        val rs1_addr    = Input(UInt(5.W))
        val csr_raddr   = Output(UInt(12.W))
        val csr_rdata   = Input(UInt(64.W))
        val csr_wen     = Output(Bool())
        val csr_waddr   = Output(UInt(12.W))
        val csr_wdata   = Output(UInt(64.W))
    })
    val op1 = io.op1
    val op2 = io.op2
    val pc  = io.pc
    val imm = io.imm
    val fu_code     = io.fu_code
    val alu_code    = io.alu_code
    val bu_code     = io.bu_code
    val lu_code     = io.lu_code
    val su_code     = io.su_code
    val csru_code   = io.csru_code

    //
    def sext(v:UInt, len:Int):UInt = len match{
        case 1 => Cat(Fill(56, v(7)), v(7, 0))
        case 2 => Cat(Fill(48, v(15)), v(15, 0))
        case 4 => Cat(Fill(32, v(31)), v(31, 0))
    }
    def zext(v:UInt, len:Int):UInt = len match{
        case 1 => Cat(Fill(56, 0.U), v(7, 0))
        case 2 => Cat(Fill(48, 0.U), v(15, 0))
        case 4 => Cat(Fill(32, 0.U), v(31, 0))
    }

    //alu
    val alu_out = MuxLookup(alu_code, 0.U, Array(
        "b0000000000000001".U -> (op1 + op2),                   //add
        "b0000000000000010".U -> sext((op1 + op2), 4),            //addw
        "b0000000000000100".U -> (op1 - op2),                   //sub
        "b0000000000001000".U -> sext((op1 - op2), 4),            //subw
        "b0000000000010000".U -> (op2 + pc),                    //imm,pc
        "b0000000000100000".U -> (op1 << op2(5, 0))(63, 0),     //sll
        "b0000000001000000".U -> (op1 >> op2(5, 0)),            //srl
        "b0000000010000000".U -> (op1.asSInt() >> op2(5, 0)).asUInt(),   //sra        
        "b0000000100000000".U -> sext((op1(31, 0) << op2(4, 0)), 4),    //sllw
        "b0000001000000000".U -> sext((op1(31, 0) >> op2(4, 0)), 4),    //srlw
        "b0000010000000000".U -> sext((op1(31, 0).asSInt() >> op2(4, 0)).asUInt(), 4),   //sraw        
        "b0000100000000000".U -> (op1 ^ op2),           //xor
        "b0001000000000000".U -> (op1 | op2),           //or
        "b0010000000000000".U -> (op1 & op2),           //and
        "b0100000000000000".U -> (op1.asSInt() < op2.asSInt()),  //slt
        "b1000000000000000".U -> (op1 < op2),           //sltu
    ))

    //bu
    val bu_out = Mux(bu_code === "b10000000".U || bu_code === "b01000000".U, pc + 4.U, 0.U)

    //csru
    io.csr_raddr := op2
    val csru_out = MuxLookup(csru_code, 0.U, Array(
        "b00000100".U -> io.csr_rdata,
        "b00001000".U -> io.csr_rdata,
        "b00010000".U -> io.csr_rdata,
        "b00100000".U -> io.csr_rdata,
        "b01000000".U -> io.csr_rdata,
        "b10000000".U -> io.csr_rdata,
    ))
    val csr_wen = MuxLookup(csru_code, false.B, Array(
        "b00000100".U -> true.B,
        "b00001000".U -> true.B,
        "b00010000".U -> true.B,
        "b00100000".U -> true.B,
        "b01000000".U -> true.B,
        "b10000000".U -> true.B,
    ))
    val csr_waddr = MuxLookup(csru_code, 0.U, Array(
        "b00000100".U -> op2,
        "b00001000".U -> op2,
        "b00010000".U -> op2,
        "b00100000".U -> op2,
        "b01000000".U -> op2,
        "b10000000".U -> op2,
    ))
    val csr_wdata = MuxLookup(csru_code, 0.U, Array(
        "b00000100".U -> (io.csr_rdata | op1),
        "b00001000".U -> op1,
        "b00010000".U -> (io.csr_rdata & (~op1)),
        "b00100000".U -> (io.csr_rdata | (Cat(0.U(59.W), io.rs1_addr))),
        "b01000000".U -> Cat(0.U(59.W), io.rs1_addr),
        "b10000000".U -> (io.csr_rdata & (~Cat(0.U(59.W), io.rs1_addr))),
    ))

    // out
    io.alu_out  := alu_out
    io.bu_out   := bu_out
    io.csru_out := csru_out

    // csr io
    io.csr_wen      := csr_wen
    io.csr_waddr    := csr_waddr
    io.csr_wdata    := csr_wdata
}








