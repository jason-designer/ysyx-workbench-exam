import chisel3._
import chisel3.util._

class WriteBack extends Module{
    val io = IO(new Bundle{
        val fu_code     = Input(UInt())
        val alu_out     = Input(UInt(64.W))
        val bu_out      = Input(UInt(64.W))
        val mu_out      = Input(UInt(64.W))
        val du_out      = Input(UInt(64.W))
        val lu_out      = Input(UInt(64.W))
        val csru_out    = Input(UInt(64.W))

        val out     = Output(UInt(64.W))
    })

    io.out := MuxLookup(io.fu_code, 0.U, Array(
        "b0000001".U -> io.alu_out,
        "b0000010".U -> io.bu_out,
        "b0000100".U -> io.lu_out,
        "b0001000".U -> 0.U,         //su_out
        "b0010000".U -> io.mu_out,
        "b0100000".U -> io.du_out,
        "b1000000".U -> io.csru_out,
    ))
}