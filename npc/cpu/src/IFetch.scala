import chisel3._

class IFetch extends Module{
  val io = IO(new Bundle{
    val jump_en = Input(Bool())
    val jump_pc = Input(UInt(64.W))
    val pc      = Input(UInt(64.W))
    
    val next_pc = Output(UInt(64.W))
    val valid   = Output(Bool()) 
  })

  io.next_pc := Mux(io.jump_en, io.jump_pc, io.pc + 4.U)
  io.valid   := !reset.asBool()
}












