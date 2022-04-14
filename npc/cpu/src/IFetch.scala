import chisel3._

class PreIFetch extends Module{
  val io = IO(new Bundle{
    val jump_en = Input(Bool())
    val jump_pc = Input(UInt(64.W))
    val stall   = Input(Bool())
    
    val next_pc = Output(UInt(64.W))
    val valid   = Output(Bool()) 
  })
  val next_pc = RegInit("h80000000".U)
  next_pc := Mux(io.stall, next_pc, Mux(io.jump_en, io.jump_pc, next_pc + 4.U))

  io.next_pc := next_pc
  io.valid   := !reset.asBool()
}



// class IFetch extends Module{
//   val io = IO(new Bundle{
//     val pc_in    = Input(UInt(64.W))
//     val inst_in  = Input(UInt(32.W))
//     val pc_out   = Output(UInt(64.W))
//     val inst_out  = Output(UInt(32.W))
//   })

//   io.pc_out   := io.pc_in
//   io.inst_out := io.inst_in 
// }


class IFetch extends Module{
  val io = IO(new Bundle{
    val jump_en = Input(Bool())
    val jump_pc = Input(UInt(64.W))
    val stall   = Input(Bool())
    val pc      = Input(UInt(64.W))
    
    val next_pc = Output(UInt(64.W))
    val valid   = Output(Bool()) 
  })

  io.next_pc := Mux(io.stall, io.pc, Mux(io.jump_en, io.jump_pc, io.pc + 4.U))
  io.valid   := !reset.asBool()
}












