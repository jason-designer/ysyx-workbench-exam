import chisel3._
import chisel3.util._
// import difftest._

class SimTop extends Module{
  val io = IO(new Bundle{

  })

  val core = Module(new Core)
  val imemory = Module(new IMemory_syn)
  val dmemory = Module(new DMemory)
  // imem
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

}




// class SimTop extends Module{
//   val io = IO(new Bundle {
//     val logCtrl   = new LogCtrlIO
//     val perfInfo  = new PerfInfoIO
//     val uart      = new UARTIO
//     val memAXI_0  = new AxiIO
//   })

//   val core = Module(new Core)
  
//   core.io.axi.ar <> io.memAXI_0.ar
//   core.io.axi.r  <> io.memAXI_0.r
//   core.io.axi.aw <> io.memAXI_0.aw
//   core.io.axi.w  <> io.memAXI_0.w
//   core.io.axi.b  <> io.memAXI_0.b 

//   io.uart.out.valid := false.B
//   io.uart.out.ch := 0.U
//   io.uart.in.valid := false.B
// }

/***********************************************************************/
// import chisel3._
// class SimTop extends Module{
//   val io = IO(new Bundle{
//     // val imem = new ImemIO
//   })

//   val imemory = Module(new IMemory)
//   val dmemory = Module(new DMemory)
//   val core = Module(new Core)
//   // imem
//   imemory.io.clk    := clock
//   imemory.io.ren    := core.io.imem.en
//   imemory.io.raddr  := core.io.imem.addr
//   core.io.imem.data := imemory.io.rdata
//   // dmem
//   dmemory.io.clk := clock
//   dmemory.io.ren      := core.io.dmem.ren 
//   dmemory.io.raddr    := core.io.dmem.raddr 
//   core.io.dmem.rdata  := dmemory.io.rdata
//   dmemory.io.wen      := core.io.dmem.wen 
//   dmemory.io.waddr    := core.io.dmem.waddr
//   dmemory.io.wdata    := core.io.dmem.wdata
//   dmemory.io.wmask    := core.io.dmem.wmask

  
//   // val inst = Reg(UInt(32.W))
//   // inst := inst + "h100".U
//   // val pc = Reg(UInt(32.W))
//   // pc := pc + 4.U

//   // val idreg = Module(new IDReg)
//   // idreg.io.pr.valid_in := true.B
//   // idreg.io.pr.en := true.B
//   // idreg.io.pc_in := pc
//   // idreg.io.inst_in := inst

//   // printf("%d\n",idreg.io.inst_out)


// }




/***********************************************************************/

// class SocTop extends Module{
//   val io = IO(new Bundle {
//     val interrupt = Input(Bool())
//     val master = new SocAXI4IO
//     val slave = Flipped(new SocAXI4IO)
//   })

//   val core = Module(new Core)
  
//   /************************ SoC-AXI *************************/
//   core.io.axi.aw.ready     := io.master.awready
//   io.master.awvalid       := core.io.axi.aw.valid
//   io.master.awaddr        := core.io.axi.aw.bits.addr
//   io.master.awid          := core.io.axi.aw.bits.id
//   io.master.awlen         := core.io.axi.aw.bits.len
//   io.master.awsize        := core.io.axi.aw.bits.size
//   io.master.awburst       := core.io.axi.aw.bits.burst

//   core.io.axi.w.ready      := io.master.wready    
//   io.master.wvalid        := core.io.axi.w.valid
//   io.master.wdata         := core.io.axi.w.bits.data
//   io.master.wstrb         := core.io.axi.w.bits.strb
//   io.master.wlast         := core.io.axi.w.bits.last

//   io.master.bready        := core.io.axi.b.ready
//   core.io.axi.b.valid      := io.master.bvalid
//   core.io.axi.b.bits.resp  := io.master.bresp
//   core.io.axi.b.bits.id    := io.master.bid

//   core.io.axi.ar.ready     := io.master.arready
//   io.master.arvalid       := core.io.axi.ar.valid
//   io.master.araddr        := core.io.axi.ar.bits.addr
//   io.master.arid          := core.io.axi.ar.bits.id
//   io.master.arlen         := core.io.axi.ar.bits.len
//   io.master.arsize        := core.io.axi.ar.bits.size
//   io.master.arburst       := core.io.axi.ar.bits.burst

//   io.master.rready        := core.io.axi.r.ready
//   core.io.axi.r.valid      := io.master.rvalid
//   core.io.axi.r.bits.resp  := io.master.rresp
//   core.io.axi.r.bits.data  := io.master.rdata
//   core.io.axi.r.bits.last  := io.master.rlast
//   core.io.axi.r.bits.id    := io.master.rid

//   core.io.axi.r.bits.user  := 0.U
//   core.io.axi.b.bits.user  := 0.U
  
//   // 不用的slave端口要置零
//   io.slave.awready  := false.B
//   // io.slave.awvalid  
//   // io.slave.awaddr   
//   // io.slave.awid     
//   // io.slave.awlen    
//   // io.slave.awsize   
//   // io.slave.awburst  

//   io.slave.wready   := false.B  
//   // io.slave.wvalid   
//   // io.slave.wdata    
//   // io.slave.wstrb    
//   // io.slave.wlast    

//   // io.slave.bready   
//   io.slave.bvalid   := false.B
//   io.slave.bresp    := 0.U
//   io.slave.bid      := 0.U

//   io.slave.arready  := false.B
//   // io.slave.arvalid
//   // io.slave.araddr   
//   // io.slave.arid    
//   // io.slave.arlen    
//   // io.slave.arsize  
//   // io.slave.arburst 

//   // io.slave.rready  
//   io.slave.rvalid   := false.B
//   io.slave.rresp    := false.B
//   io.slave.rdata    := 0.U
//   io.slave.rlast    := false.B
//   io.slave.rid      := 0.U
//   /****************************************************/
// }