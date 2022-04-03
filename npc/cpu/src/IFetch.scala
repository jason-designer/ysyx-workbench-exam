import chisel3._

class IFetch extends Module{
  val io = IO(new Bundle{
    val imem = new ImemIO
    val pc = Output(UInt(64.W))
    val inst = Output(UInt(32.W))
    val jump_en = Input(Bool())
    val jump_pc = Input(UInt(32.W))

  })

  val pc = RegInit("h80000000".U)
  pc := Mux(io.jump_en, io.jump_pc, pc + 4.U)

  
  io.imem.en    := true.B
  io.imem.addr  := pc
  io.pc         := pc
  io.inst       := io.imem.data 
}
















