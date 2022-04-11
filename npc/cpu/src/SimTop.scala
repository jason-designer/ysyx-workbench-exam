import chisel3._


class SimTop extends Module{
  val io = IO(new Bundle{
    // val imem = new ImemIO
  })

  val imemory = Module(new IMemory)
  val dmemory = Module(new DMemory)
  val core = Module(new Core)
  // imem
  imemory.io.clk    := clock
  imemory.io.ren    := core.io.imem.en
  imemory.io.raddr  := core.io.imem.addr
  core.io.imem.data := imemory.io.rdata
  // dmem
  dmemory.io.clk := clock
  dmemory.io.ren      := core.io.dmem.ren 
  dmemory.io.raddr    := core.io.dmem.raddr 
  core.io.dmem.rdata  := dmemory.io.rdata
  dmemory.io.wen      := core.io.dmem.wen 
  dmemory.io.waddr    := core.io.dmem.waddr
  dmemory.io.wdata    := core.io.dmem.wdata
  dmemory.io.wmask    := core.io.dmem.wmask

  
  // val inst = Reg(UInt(32.W))
  // inst := inst + "h100".U
  // val pc = Reg(UInt(32.W))
  // pc := pc + 4.U

  // val idreg = Module(new IDReg)
  // idreg.io.pr.valid_in := true.B
  // idreg.io.pr.en := true.B
  // idreg.io.pc_in := pc
  // idreg.io.inst_in := inst

  // printf("%d\n",idreg.io.inst_out)


}




