import chisel3._


class SimTop extends Module{
  val io = IO(new Bundle{
    val imem = new ImemIO
  })

  val memory = Module(new Memory)
  val core = Module(new Core)
  io.imem <> core.io.imem
  memory.io.clk := clock
  memory.io.ren   := core.io.dmem.ren 
  memory.io.raddr := core.io.dmem.raddr 
  core.io.dmem.rdata   := memory.io.rdata
  memory.io.wen   := core.io.dmem.wen 
  memory.io.waddr := core.io.dmem.waddr
  memory.io.wdata := core.io.dmem.wdata
  memory.io.wmask := core.io.dmem.wmask


}




