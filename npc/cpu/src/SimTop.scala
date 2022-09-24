import chisel3._
import chisel3.util._


class SimTop extends Module{
    val io = IO(new Bundle{
        val master = new SocAXI4IO
        val slave = Flipped(new SocAXI4IO)
    })

    val core = Module(new Core)

    val sram0 = Module(new SRam_1k)
    val sram1 = Module(new SRam_1k)
    val sram2 = Module(new SRam_1k)
    val sram3 = Module(new SRam_1k)
    val sram4 = Module(new SRam_1k)
    val sram5 = Module(new SRam_1k)
    val sram6 = Module(new SRam_1k)
    val sram7 = Module(new SRam_1k)
    /************************* Core-SRam *********************/
    core.io.sram0 <> sram0.io
    core.io.sram1 <> sram1.io
    core.io.sram2 <> sram2.io
    core.io.sram3 <> sram3.io
    core.io.sram4 <> sram4.io
    core.io.sram5 <> sram5.io
    core.io.sram6 <> sram6.io
    core.io.sram7 <> sram7.io
    /************************ SoC-AXI *************************/
    core.io.axi.aw.ready    := io.master.awready
    io.master.awvalid       := core.io.axi.aw.valid
    io.master.awaddr        := core.io.axi.aw.bits.addr
    io.master.awid          := core.io.axi.aw.bits.id
    io.master.awlen         := core.io.axi.aw.bits.len
    io.master.awsize        := core.io.axi.aw.bits.size
    io.master.awburst       := core.io.axi.aw.bits.burst

    core.io.axi.w.ready     := io.master.wready    
    io.master.wvalid        := core.io.axi.w.valid
    io.master.wdata         := core.io.axi.w.bits.data
    io.master.wstrb         := core.io.axi.w.bits.strb
    io.master.wlast         := core.io.axi.w.bits.last

    io.master.bready        := core.io.axi.b.ready
    core.io.axi.b.valid     := io.master.bvalid
    core.io.axi.b.bits.resp := io.master.bresp
    core.io.axi.b.bits.id   := io.master.bid

    core.io.axi.ar.ready    := io.master.arready
    io.master.arvalid       := core.io.axi.ar.valid
    io.master.araddr        := core.io.axi.ar.bits.addr
    io.master.arid          := core.io.axi.ar.bits.id
    io.master.arlen         := core.io.axi.ar.bits.len
    io.master.arsize        := core.io.axi.ar.bits.size
    io.master.arburst       := core.io.axi.ar.bits.burst

    io.master.rready        := core.io.axi.r.ready
    core.io.axi.r.valid     := io.master.rvalid
    core.io.axi.r.bits.resp := io.master.rresp
    core.io.axi.r.bits.data := io.master.rdata
    core.io.axi.r.bits.last := io.master.rlast
    core.io.axi.r.bits.id   := io.master.rid

    core.io.axi.r.bits.user := 0.U
    core.io.axi.b.bits.user := 0.U
    
    // 不用的slave端口要置零
    io.slave.awready  := false.B
    // io.slave.awvalid  
    // io.slave.awaddr   
    // io.slave.awid     
    // io.slave.awlen    
    // io.slave.awsize   
    // io.slave.awburst  

    io.slave.wready   := false.B  
    // io.slave.wvalid   
    // io.slave.wdata    
    // io.slave.wstrb    
    // io.slave.wlast    

    // io.slave.bready   
    io.slave.bvalid   := false.B
    io.slave.bresp    := 0.U
    io.slave.bid      := 0.U

    io.slave.arready  := false.B
    // io.slave.arvalid
    // io.slave.araddr   
    // io.slave.arid    
    // io.slave.arlen    
    // io.slave.arsize  
    // io.slave.arburst 

    // io.slave.rready  
    io.slave.rvalid   := false.B
    io.slave.rresp    := false.B
    io.slave.rdata    := 0.U
    io.slave.rlast    := false.B
    io.slave.rid      := 0.U
}

class SimTopSoc extends Module{
    val io = IO(new Bundle{
        val interrupt = Input(Bool())

        val master = new SocAXI4IO
        val slave = Flipped(new SocAXI4IO)

        val sram0 = new SRamIO
        val sram1 = new SRamIO
        val sram2 = new SRamIO
        val sram3 = new SRamIO
        val sram4 = new SRamIO
        val sram5 = new SRamIO
        val sram6 = new SRamIO
        val sram7 = new SRamIO
    })

    val core = Module(new Core)

    // val sram0 = Module(new SRam_1k)
    // val sram1 = Module(new SRam_1k)
    // val sram2 = Module(new SRam_1k)
    // val sram3 = Module(new SRam_1k)
    // val sram4 = Module(new SRam_1k)
    // val sram5 = Module(new SRam_1k)
    // val sram6 = Module(new SRam_1k)
    // val sram7 = Module(new SRam_1k)
    
    // core.io.sram0 <> sram0.io
    // core.io.sram1 <> sram1.io
    // core.io.sram2 <> sram2.io
    // core.io.sram3 <> sram3.io
    // core.io.sram4 <> sram4.io
    // core.io.sram5 <> sram5.io
    // core.io.sram6 <> sram6.io
    // core.io.sram7 <> sram7.io

    /************************* Core-SRam *********************/
    core.io.sram0 <> io.sram0
    core.io.sram1 <> io.sram1
    core.io.sram2 <> io.sram2
    core.io.sram3 <> io.sram3
    core.io.sram4 <> io.sram4
    core.io.sram5 <> io.sram5
    core.io.sram6 <> io.sram6
    core.io.sram7 <> io.sram7
    
    /************************ SoC-AXI *************************/
    core.io.axi.aw.ready    := io.master.awready
    io.master.awvalid       := core.io.axi.aw.valid
    io.master.awaddr        := core.io.axi.aw.bits.addr
    io.master.awid          := core.io.axi.aw.bits.id
    io.master.awlen         := core.io.axi.aw.bits.len
    io.master.awsize        := core.io.axi.aw.bits.size
    io.master.awburst       := core.io.axi.aw.bits.burst

    core.io.axi.w.ready     := io.master.wready    
    io.master.wvalid        := core.io.axi.w.valid
    io.master.wdata         := core.io.axi.w.bits.data
    io.master.wstrb         := core.io.axi.w.bits.strb
    io.master.wlast         := core.io.axi.w.bits.last

    io.master.bready        := core.io.axi.b.ready
    core.io.axi.b.valid     := io.master.bvalid
    core.io.axi.b.bits.resp := io.master.bresp
    core.io.axi.b.bits.id   := io.master.bid

    core.io.axi.ar.ready    := io.master.arready
    io.master.arvalid       := core.io.axi.ar.valid
    io.master.araddr        := core.io.axi.ar.bits.addr
    io.master.arid          := core.io.axi.ar.bits.id
    io.master.arlen         := core.io.axi.ar.bits.len
    io.master.arsize        := core.io.axi.ar.bits.size
    io.master.arburst       := core.io.axi.ar.bits.burst

    io.master.rready        := core.io.axi.r.ready
    core.io.axi.r.valid     := io.master.rvalid
    core.io.axi.r.bits.resp := io.master.rresp
    core.io.axi.r.bits.data := io.master.rdata
    core.io.axi.r.bits.last := io.master.rlast
    core.io.axi.r.bits.id   := io.master.rid

    core.io.axi.r.bits.user := 0.U
    core.io.axi.b.bits.user := 0.U
    
    // 不用的slave端口要置零
    io.slave.awready  := false.B
    // io.slave.awvalid  
    // io.slave.awaddr   
    // io.slave.awid     
    // io.slave.awlen    
    // io.slave.awsize   
    // io.slave.awburst  

    io.slave.wready   := false.B  
    // io.slave.wvalid   
    // io.slave.wdata    
    // io.slave.wstrb    
    // io.slave.wlast    

    // io.slave.bready   
    io.slave.bvalid   := false.B
    io.slave.bresp    := 0.U
    io.slave.bid      := 0.U

    io.slave.arready  := false.B
    // io.slave.arvalid
    // io.slave.araddr   
    // io.slave.arid    
    // io.slave.arlen    
    // io.slave.arsize  
    // io.slave.arburst 

    // io.slave.rready  
    io.slave.rvalid   := false.B
    io.slave.rresp    := false.B
    io.slave.rdata    := 0.U
    io.slave.rlast    := false.B
    io.slave.rid      := 0.U
}
