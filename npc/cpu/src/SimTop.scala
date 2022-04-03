import chisel3._

class ImemIO extends Bundle{
  val en = Output(Bool())
  val addr = Output(UInt(64.W))
  val data = Input(UInt(32.W))
}


class DmemIO extends Bundle{
  val ren   = Output(Bool())
  val raddr = Output(UInt(64.W))
  val rdata = Input(UInt(64.W))
  val wen   = Output(Bool())
  val waddr = Output(UInt(64.W))
  val wdata = Output(UInt(64.W))
  val wmask = Output(UInt(8.W))
}


class SimTop extends Module{
  val io = IO(new Bundle{
    val imem = new ImemIO
    //val dmem = new DmemIO
  })

  val core = Module(new Core)
  io.imem <> core.io.imem



}