import chisel3._
import chisel3.util._

class AccessMemory extends Module{
    val io = IO(new Bundle{
        val lu_code  = Input(UInt())
        val lu_shift = Input(UInt(6.W))
        val rdata    = Input(UInt(64.W))

        val lu_out   = Output(UInt(64.W))
    })
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
    io.lu_out := MuxLookup(io.lu_code, 0.U, Array(
        "b0000001".U -> sext((io.rdata) >> io.lu_shift, 1),  //lb
        "b0000010".U -> sext((io.rdata) >> io.lu_shift, 2),  //lh
        "b0000100".U -> sext((io.rdata) >> io.lu_shift, 4),  //lw
        "b0001000".U -> ((io.rdata) >> io.lu_shift),         //ld
        "b0010000".U -> zext((io.rdata) >> io.lu_shift, 1),  //lbu
        "b0100000".U -> zext((io.rdata) >> io.lu_shift, 2),  //lhu
        "b1000000".U -> zext((io.rdata) >> io.lu_shift, 4),  //lwu
    ))
}