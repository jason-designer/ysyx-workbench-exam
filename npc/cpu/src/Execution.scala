import chisel3._
import chisel3.util._

class Execution extends Module{
    val io = IO(new Bundle{
        val decode_info = Flipped(new DecodeInfo)

        val op1 = Input(UInt(64.W))
        val op2 = Input(UInt(64.W))
        val op3 = Input(UInt(64.W))

        val out = Output(UInt(64.W))
        val jump_en = Output(Bool())
        val jump_pc = Output(UInt(64.W))
    })
    val op1 = io.op1
    val op2 = io.op2
    val op3 = io.op3
    val fu_code = io.decode_info.fu_code
    val alu_code = io.decode_info.alu_code

    //
    val alu_out = MuxLookup(alu_code, 0.U, Array(
        "b000001".U -> (op1 + op2 + 1.U),
    ))


    //
    io.out := MuxLookup(fu_code, 0.U, Array(
        "b000001".U -> alu_out,
    ))
    io.jump_en := false.B
    io.jump_pc := 0.U

}








