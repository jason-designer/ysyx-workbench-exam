import chisel3._
import chisel3.util._
import chisel3.experimental._
import Decode_constant._

// 当cnt==65时，complete会变高，表示完成计算
// 当cnt==0时，ready会变高，表示可以接受输入
class Div extends Module{
    val io = IO(new Bundle{
        val en = Input(Bool())
        val signed = Input(Bool())  // 1表示有符号数
        val x = Input(UInt(64.W))
        val y = Input(UInt(64.W))
        val s = Output(UInt(64.W))
        val r = Output(UInt(64.W))
        val ready = Output(Bool())
        val complete = Output(Bool())

        val stall = Output(Bool())
    })
    //
    val x_abs = Cat(0.U(64.W), Mux(io.x(63), ~io.x + 1.U, io.x))
    val y_abs = Mux(io.y(63), ~io.y + 1.U, io.y)

    // input 处理是否为有符号运算
    val x_input = Mux(io.signed, x_abs, Cat(0.U(64.W), io.x))
    val y_input = Mux(io.signed, y_abs, io.y)

    //
    val signed = RegInit(false.B)           // 记录io.signed
    val x_input_signed = RegInit(false.B)   // x的符号
    val y_input_signed = RegInit(false.B)   // y的符号
    val x = RegInit(0.U(128.W))
    val y = RegInit(0.U(64.W))
    val s = RegInit(0.U(64.W))
    val r_out = RegInit(0.U(64.W))
    val s_out = RegInit(0.U(64.W))
    val cnt = RegInit(0.U(7.W))
    
    //----------减法----------------------------------------
    val x_sub = (x << cnt)(128, 64) - y
    val x_sign = x_sub(64)
    val x_mask = (Cat(x_sub, 0.U(64.W)) >> cnt)
    val x_clean = (Cat(0.U(64.W), Fill(64, 1.U)) >> cnt) & x 
    val x_update = Mux(x_sign, x, x_mask | x_clean)

    val s_update = Mux(x_sign, s, s | (Cat(1.U, 0.U(64.W)) >> cnt)(63, 0))
    //-----------update------------------------------------
    // signed
    when(io.en && cnt === 0.U){signed := io.signed}
    // input_signed
    when(io.en && cnt === 0.U){x_input_signed := io.x(63)}
    when(io.en && cnt === 0.U){y_input_signed := io.y(63)}
    // y
    when(io.en && cnt === 0.U){y := y_input}   
    // x
    when(io.en && cnt === 0.U){x := x_input}   
    .elsewhen(cnt =/= 0.U && cnt =/= 65.U){x := x_update}
    // s  
    when(cnt =/= 0.U && cnt =/= 65.U){s := s_update}
    .elsewhen(cnt === 65.U){s := 0.U}
    // s_out
    when(cnt === 64.U){s_out := Mux(signed && (x_input_signed ^ y_input_signed), ~s_update + 1.U, s_update)}
    // r_out
    when(cnt === 64.U){r_out := Mux(signed && x_input_signed, ~x_update(63, 0) + 1.U, x_update(63, 0))}
    // cnt
    when(cnt === 0.U){cnt := Mux(io.en, 1.U, 0.U)}
    .elsewhen(cnt === 65.U){cnt := 0.U}  
    .otherwise{cnt := cnt + 1.U}

    //------------------output------------------
    io.ready := cnt === 0.U
    io.complete := cnt === 65.U
    io.s := s_out
    io.r := r_out

    io.stall := !(cnt === 65.U || (cnt === 0.U && !io.en))
}


class DU extends Module{
    val io = IO(new Bundle{
        val en      = Input(Bool())
        val du_code = Input(UInt(du_code_length.W))
        val op1     = Input(UInt(64.W))
        val op2     = Input(UInt(64.W))
        val du_out  = Output(UInt(64.W))
        val stall   = Output(Bool())
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
    //
    val x = MuxLookup(io.du_code, 0.U, Array(
        "b00000001".U -> io.op1,           // div
        "b00000010".U -> sext(io.op1, 4),  // divw
        "b00000100".U -> io.op1,           // divu
        "b00001000".U -> zext(io.op1, 4),  // divuw
        "b00010000".U -> io.op1,           // rem
        "b00100000".U -> sext(io.op1, 4),  // remw        
        "b01000000".U -> io.op1,           // remu
        "b10000000".U -> zext(io.op1, 4),  // remuw
    ))
    val y = MuxLookup(io.du_code, 0.U, Array(
        "b00000001".U -> io.op2,           // div
        "b00000010".U -> sext(io.op2, 4),  // divw
        "b00000100".U -> io.op2,           // divu
        "b00001000".U -> zext(io.op2, 4),  // divuw
        "b00010000".U -> io.op2,           // rem
        "b00100000".U -> sext(io.op2, 4),  // remw        
        "b01000000".U -> io.op2,           // remu
        "b10000000".U -> zext(io.op2, 4),  // remuw
    ))
    val signed = MuxLookup(io.du_code, false.B, Array(
        "b00000001".U -> true.B,    // div
        "b00000010".U -> true.B,    // divw
        "b00000100".U -> false.B,   // divu
        "b00001000".U -> false.B,   // divuw
        "b00010000".U -> true.B,    // rem
        "b00100000".U -> true.B,    // remw        
        "b01000000".U -> false.B,   // remu
        "b10000000".U -> false.B,   // remuw
    ))
    // 
    val div = Module(new Div)
    div.io.en       := io.en
    div.io.signed   := signed
    div.io.x        := x
    div.io.y        := y
    //
    val out = MuxLookup(io.du_code, 0.U, Array(
        "b00000001".U -> div.io.s,  // div
        "b00000010".U -> div.io.s,  // divw
        "b00000100".U -> div.io.s,  // divu
        "b00001000".U -> div.io.s,  // divuw
        "b00010000".U -> div.io.r,  // rem
        "b00100000".U -> div.io.r,  // remw        
        "b01000000".U -> div.io.r,  // remu
        "b10000000".U -> div.io.r,  // remuw
    ))

    io.du_out   := out
    io.stall    := div.io.stall
}


