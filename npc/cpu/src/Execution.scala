import chisel3._
import chisel3.util._

class Execution extends Module{
    val io = IO(new Bundle{
        val decode_info = Flipped(new DecodeInfo)

        val op1 = Input(UInt(64.W))
        val op2 = Input(UInt(64.W))
        val pc  = Input(UInt(64.W))
        val imm = Input(UInt(64.W))

        val out = Output(UInt(64.W))
        val jump_en = Output(Bool())
        val jump_pc = Output(UInt(64.W))
    })
    val op1 = io.op1
    val op2 = io.op2
    val pc  = io.pc
    val imm = io.imm
    val fu_code = io.decode_info.fu_code
    val alu_code = io.decode_info.alu_code
    val bu_code = io.decode_info.bu_code
    val lu_code = io.decode_info.lu_code
    val su_code = io.decode_info.su_code

    //
    val alu_out = MuxLookup(alu_code, 0.U, Array(
        "b0000000000000001".U -> (op1 + op2),           //add
        "b0000000000000010".U -> (op1 + op2)(31, 0),    //addw
        "b0000000000000100".U -> (op1 - op2),           //sub
        "b0000000000001000".U -> (op1 - op2)(31, 0),    //subw
        "b0000000000010000".U -> (op2 + pc),           //imm,pc
        "b0000000000100000".U -> (op1 << op2(5, 0)),    //sll
        "b0000000001000000".U -> (op1 >> op2(5, 0)),    //srl
        "b0000000010000000".U -> (op1.asSInt() >> op2(5, 0)).asUInt(),   //sra        
        "b0000000100000000".U -> (op1(31, 0) << op2(4, 0)),    //sllw
        "b0000001000000000".U -> (op1(31, 0) >> op2(4, 0)),    //srlw
        "b0000010000000000".U -> (op1.asSInt()(31, 0) >> op2(4, 0)).asUInt(),   //sraw        
        "b0000100000000000".U -> (op1 ^ op2),           //xor
        "b0001000000000000".U -> (op1 | op2),           //or
        "b0010000000000000".U -> (op1 & op2),           //and
        "b0100000000000000".U -> (op1.asSInt() < op2.asSInt()),  //slt
        "b1000000000000000".U -> (op1 < op2),           //sltu
    ))

    val bu_out = Mux(bu_code === "b10000000".U || bu_code === "b01000000".U, pc + 4.U, 0.U)
    val bu_jump_pc = Mux(bu_code === "b10000000".U, ((op1 + op2) & "hfffffffffffffffe".U), pc + imm)
    val bu_jump_en = MuxLookup(bu_code, 0.U, Array(
        "b00000001".U -> (op1 === op2),                     //beq
        "b00000010".U -> (op1 =/= op2),                     //bne
        "b00000100".U -> (op1.asSInt()  <  op2.asSInt()),   //blt
        "b00001000".U -> (op1.asSInt()  >= op2.asSInt()),   //bge
        "b00010000".U -> (op1  <  op2),                     //bltu
        "b00100000".U -> (op1  >= op2),                     //bgeu
        "b01000000".U -> true.B,                            //jal
        "b10000000".U -> true.B,                            //jalr
    ))
    



    //
    io.out := MuxLookup(fu_code, 0.U, Array(
        "b000001".U -> alu_out,
        "b000010".U -> bu_out,
    ))
    io.jump_en := bu_jump_en
    io.jump_pc := bu_jump_pc

}








