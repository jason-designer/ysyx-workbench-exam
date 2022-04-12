import chisel3._
import chisel3.util._

class WriteBack extends Module{
    val io = IO(new Bundle{
        val fu_code = Input(UInt())
        val alu_out = Input(UInt(64.W))
        val bu_out  = Input(UInt(64.W))
        val mdu_out = Input(UInt(64.W))
        val lu_out  = Input(UInt(64.W))

        val out     = Output(UInt(64.W))
    })

    io.out := MuxLookup(io.fu_code, 0.U, Array(
        "b000001".U -> io.alu_out,
        "b000010".U -> io.bu_out,
        "b000100".U -> io.lu_out,
        "b001000".U -> 0.U,         //su_out
        "b010000".U -> io.mdu_out,
    ))
}