import chisel3._
import chisel3.util._

class SocAXI4IO extends Bundle{
  val awready = Input(Bool())
  val awvalid = Output(Bool())
  val awaddr  = Output(UInt(32.W))
  val awid    = Output(UInt(4.W))
  val awlen   = Output(UInt(8.W))
  val awsize  = Output(UInt(3.W))
  val awburst = Output(UInt(2.W))
  
  val wready  = Input(Bool())
  val wvalid  = Output(Bool())
  val wdata   = Output(UInt(64.W))
  val wstrb   = Output(UInt(8.W))
  val wlast   = Output(Bool())
  
  val bready  = Output(Bool())
  val bvalid  = Input(Bool())
  val bresp   = Input(UInt(2.W))
  val bid     = Input(UInt(4.W))

  val arready = Input(Bool())
  val arvalid = Output(Bool())
  val araddr  = Output(UInt(32.W))
  val arid    = Output(UInt(4.W))
  val arlen   = Output(UInt(8.W))
  val arsize  = Output(UInt(3.W))
  val arburst = Output(UInt(2.W))

  val rready  = Output(Bool())
  val rvalid  = Input(Bool())
  val rresp   = Input(UInt(2.W))
  val rdata   = Input(UInt(64.W))
  val rlast   = Input(Bool())
  val rid     = Input(UInt(4.W))
}

trait AxiParameters {
    val AxiAddrWidth = 64
    val AxiDataWidth = 64
    val AxiIdWidth   = 4
    val AxiUserWidth = 4
}

// object AxiParameters extends AxiParameters { }

class AxiA extends Bundle with AxiParameters{
    val len     = Output(UInt(8.W))
    val size    = Output(UInt(3.W))
    val burst   = Output(UInt(2.W))
    val lock    = Output(Bool())
    val cache   = Output(UInt(4.W))
    val qos     = Output(UInt(4.W))
    val addr    = Output(UInt(AxiAddrWidth.W))
    val prot    = Output(UInt(3.W))
    val id      = Output(UInt(AxiIdWidth.W))
    val user    = Output(UInt(AxiUserWidth.W))
}

class AxiW extends Bundle with AxiParameters{
    val data    = Output(UInt(AxiDataWidth.W))
    val strb    = Output(UInt((AxiDataWidth / 8).W))
    val last    = Output(Bool())
}

class AxiB extends Bundle with AxiParameters{
    val resp    = Output(UInt(2.W))
    val id      = Output(UInt(AxiIdWidth.W))
    val user    = Output(UInt(AxiUserWidth.W))
}

class AxiR extends Bundle with AxiParameters{
    val resp    = Output(UInt(2.W))
    val data    = Output(UInt(AxiDataWidth.W))
    val last    = Output(Bool())
    val id      = Output(UInt(AxiIdWidth.W))
    val user    = Output(UInt(AxiUserWidth.W))
}

class AxiIO extends Bundle with AxiParameters{
    val aw      = Decoupled(new AxiA)
    val w       = Decoupled(new AxiW)
    val b       = Flipped(Decoupled(new AxiB))
    val ar      = Decoupled(new AxiA)
    val r       = Flipped(Decoupled(new AxiR))
}


/********************* AXI实现 *****************************/
class AXI extends Module with CacheParameters{
    val io = IO(new Bundle{
        val out = new AxiIO
        val icacheio = Flipped(new ICacheAxiIO)
        val dcacheio = Flipped(new DCacheAxiIO)
        val icacheBypassIO = Flipped(new ICacheBypassAxiIO)
        val dcacheBypassIO = Flipped(new DCacheBypassAxiIO)
    })
    //
    val out = io.out
    val icacheio = io.icacheio
    val dcacheio = io.dcacheio
    val icacheBypassIO = io.icacheBypassIO
    val dcacheBypassIO = io.dcacheBypassIO
    // buffer
    val ibuffer     = RegInit(VecInit(Seq.fill(AxiArLen)(0.U(64.W))))
    val drbuffer    = RegInit(VecInit(Seq.fill(AxiArLen)(0.U(64.W))))
    val icnt        = RegInit(0.U(OffsetWidth.W))
    val drcnt       = RegInit(0.U(OffsetWidth.W))
    val dwcnt       = RegInit(0.U(OffsetWidth.W))
    // state machine define
    val r_idle :: r_iaddr :: r_ihs :: r_idata :: r_idone :: r_daddr :: r_dhs :: r_ddata :: r_ddone :: Nil = Enum(9)
    val w_idle :: w_addr :: w_data :: w_resp :: w_done :: Nil = Enum(5)
    val rstate = RegInit(r_idle)
    val wstate = RegInit(w_idle)
    val r_bypass = RegInit(false.B)
    val w_bypass = RegInit(false.B)

    // read state machine
    switch(rstate){
        is(r_idle){
            when(icacheio.req){
                rstate := r_iaddr
                r_bypass := false.B
            }
            .elsewhen(dcacheio.req){
                rstate := r_daddr
                r_bypass := false.B
            }
            .elsewhen(icacheBypassIO.req){
                rstate := r_iaddr
                r_bypass := true.B
            }
            .elsewhen(dcacheBypassIO.req){
                rstate := r_daddr
                r_bypass := true.B
            }
        }
        // 处理 imem req 
        is(r_iaddr){
            when(out.ar.ready) {rstate := r_ihs}
        }
        is(r_ihs){
            when(out.r.valid) {rstate := r_idata}
        }
        is(r_idata){
            when(out.r.valid && out.r.bits.last) {rstate := r_idone} // 当last的时候才下一步，此时当valid为true才记录数据
        }
        is(r_idone){
            rstate := r_idle
        }
        // 处理 dmem req 
        is(r_daddr){
            when(out.ar.ready) {rstate := r_dhs}
        }
        is(r_dhs){
            when(out.r.valid) {rstate := r_ddata}
        }
        is(r_ddata){
            when(out.r.valid && out.r.bits.last) {rstate := r_ddone}   // 当last的时候才下一步，此时当valid为true才记录数据
        }
        is(r_ddone){
            rstate := r_idle
        }
    }

    // write state machine
    switch(wstate){
        is(w_idle){
            when(dcacheio.weq){
                wstate := w_addr
                w_bypass := false.B
            }
            .elsewhen(dcacheBypassIO.weq){
                wstate := w_addr
                w_bypass := true.B
            }
        }
        is(w_addr){
            when(out.aw.ready) {wstate := w_data}
        }
        is(w_data){
            when(out.w.bits.last && out.w.ready) {wstate := w_resp}
        }
        is(w_resp){
            when(out.b.valid) {wstate := w_done}
        }
        is(w_done){
            when(!out.b.valid) {wstate := w_idle}
        }
    }


    /***********************buffer****************************/
    ibuffer(icnt) := Mux(rstate === r_idata, out.r.bits.data, ibuffer(icnt))
    icnt := Mux(rstate === r_idata, Mux(out.r.valid, icnt + 1.U, icnt), 0.U)        // 当valid时才记录下一个数据
    drbuffer(drcnt) := Mux(rstate === r_ddata, out.r.bits.data, drbuffer(drcnt))
    drcnt := Mux(rstate === r_ddata, Mux(out.r.valid, drcnt + 1.U, drcnt), 0.U)     // 当valid时才记录下一个数据
    dwcnt := Mux(wstate === w_data, Mux(out.w.ready, dwcnt + 1.U, dwcnt), 0.U)      // 当从机ready时才记录下一个数据


    /********************* output buffer ***************************/
    var idata = 0.U(1.W)
    for(i <- 0 to (AxiArLen - 1)) idata = Cat(ibuffer(i), idata)
    idata = idata(AxiArLen * 64 ,1)
    var drdata = 0.U(1.W)
    for(i <- 0 to (AxiArLen - 1)) drdata = Cat(drbuffer(i), drdata)
    drdata = drdata(AxiArLen * 64 ,1)
    /*************** CacheIO/CacheBypassIO signals *****************/
    // icacheio signals---------------------------------------
    // icacheio.req
    // icacheio.addr
    icacheio.valid  := rstate === r_idone && r_bypass === false.B
    icacheio.data   := idata
    // dcacheio signals---------------------------------------
    // dcacheio.req
    // dcacheio.raddr
    dcacheio.rvalid := rstate === r_ddone && r_bypass === false.B
    dcacheio.rdata  := drdata
    dcacheio.wdone  := wstate === w_done && !out.b.valid
    // icacheBypassIO signals---------------------------------
    // icacheBypassIO.req
    // icacheBypassIO.addr
    icacheBypassIO.valid  := rstate === r_idone && r_bypass === true.B
    icacheBypassIO.data   := idata(63, 0)
    // dcacheBypassIO signals---------------------------------
    // dcacheBypassIO.req
    // dcacheBypassIO.raddr
    // dcacheBypassIO.wmask
    dcacheBypassIO.rvalid := rstate === r_ddone && r_bypass === true.B
    dcacheBypassIO.rdata  := drdata(63, 0)
    dcacheBypassIO.wdone  := wstate === w_done && !out.b.valid && w_bypass === true.B


    /********************** AXI signals ***********************/
    val sel_raddr = Cat(rstate === r_iaddr, rstate === r_daddr, r_bypass)
    // Read address channel signals --------------------------
    // out.ar.ready
    out.ar.valid        := rstate === r_iaddr || rstate === r_daddr
    out.ar.bits.addr    := MuxLookup(sel_raddr, 0.U, Array(
        "b100".U -> icacheio.addr,
        "b010".U -> dcacheio.raddr,
        "b101".U -> icacheBypassIO.addr,
        "b011".U -> dcacheBypassIO.raddr,
    ))
    out.ar.bits.prot    := "b000".U
    out.ar.bits.id      := 0.U
    out.ar.bits.user    := 0.U
    out.ar.bits.len     := Mux(r_bypass, 0.U, (AxiArLen - 1).U)
    out.ar.bits.size    := MuxLookup(sel_raddr, 0.U, Array(
        "b100".U -> "b011".U,
        "b010".U -> "b011".U,
        "b101".U -> "b010".U,
        "b011".U -> io.dcacheBypassIO.transfer,
    ))                          //每个beat包含8个字节,icache的bypass则为4B,dcache的bypass为transfer
    out.ar.bits.burst   := "b01".U
    out.ar.bits.lock    := 0.U
    out.ar.bits.cache   := "b0010".U
    out.ar.bits.qos     := 0.U

    // Read data channel signals -----------------------------
    // out.r.valid
    // out.r.resp
    // out.r.data 
    // out.r.last
    // out.r.id
    // out.r.user
    out.r.ready         := rstate === r_idata || rstate === r_ddata

    // write address channel signals -------------------------
    // out.aw.ready
    out.aw.valid        := wstate === w_addr
    out.aw.bits.addr    := Mux(w_bypass, dcacheBypassIO.waddr, dcacheio.waddr)
    out.aw.bits.prot    := "b000".U
    out.aw.bits.id      := 0.U
    out.aw.bits.user    := 0.U
    out.aw.bits.len     := Mux(w_bypass, 0.U, (AxiArLen - 1).U)
    out.aw.bits.size    := Mux(w_bypass, io.dcacheBypassIO.transfer, "b011".U)
    out.aw.bits.burst   := "b01".U
    out.aw.bits.lock    := 0.U
    out.aw.bits.cache   := "b0010".U
    out.aw.bits.qos     := 0.U
    // write data channel signals ----------------------------
    out.w.valid         := wstate === w_data
    out.w.bits.data     := Mux(w_bypass, dcacheBypassIO.wdata, (dcacheio.wdata >> (dwcnt << 6))(63, 0))
    out.w.bits.strb     := Mux(w_bypass, dcacheBypassIO.wmask, "hff".U)
    out.w.bits.last     := Mux(w_bypass, dwcnt === 0.U, dwcnt === (AxiArLen-1).U)
    // resp channel signals ----------------------------------
    out.b.ready         := wstate === w_done
}


