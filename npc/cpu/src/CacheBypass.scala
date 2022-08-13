import chisel3._
import chisel3.util._

class ICacheBypassAxiIO extends Bundle{
    val req     = Output(Bool())
    val addr    = Output(UInt(32.W))
    val valid   = Input(Bool())
    val data    = Input(UInt(64.W))
}

class DCacheBypassAxiIO extends Bundle{
    val req     = Output(Bool())
    val raddr   = Output(UInt(32.W))
    val rvalid  = Input(Bool())
    val rdata   = Input(UInt(64.W))

    val weq     = Output(Bool())
    val waddr   = Output(UInt(32.W))
    val wdata   = Output(UInt(64.W))
    val wmask   = Output(UInt(8.W))
    val wdone   = Input(Bool())

    val transfer = Output(UInt(3.W))
}

class ICacheBypass extends Module{
    val io = IO(new Bundle{
        val imem    = new ICacheIO
        val axi     = new ICacheBypassAxiIO
    })
    // buffer reg
    val addr    = RegInit(0.U(32.W))
    val data   = RegInit(0.U(32.W))
    // state machine define
    val idle :: fetch_data :: update :: Nil = Enum(3)
    val state = RegInit(idle)
    // state machine
    switch(state){
        is(idle){
            when(io.imem.en) {state := fetch_data}
        }
        is(fetch_data){
            when(io.axi.valid) {state := update}
        }
        is(update){
            state := idle
        }
    }
    // update buffer
    addr   := Mux(state === idle && io.imem.en, io.imem.addr, addr)
    data   := Mux(state === update, io.axi.data >> (addr(2, 0) << 3), data)
    // axi output signal
    io.axi.req      := state === fetch_data
    io.axi.addr     := addr & "hfffffffc".U   // 若tranfer的size为4的话，地址要求4对齐
    // dcachebypass output signal
    io.imem.data    := data
    io.imem.ok      := state === idle
}


class DCacheBypass extends Module{
    val io = IO(new Bundle{
        val dmem    = new DCacheIO
        val axi     = new DCacheBypassAxiIO
    })
    // buffer reg
    val op      = RegInit(false.B)
    val addr    = RegInit(0.U(32.W))
    val wdata   = RegInit(0.U(64.W))
    val wmask   = RegInit(0.U(8.W))
    val rdata   = RegInit(0.U(64.W))
    val transfer = RegInit(0.U(3.W))
    // state machine define
    val idle :: fetch_data :: update :: write_data :: Nil = Enum(4)
    val state = RegInit(idle)
    // state machine
    switch(state){
        is(idle){
            when(io.dmem.en && !io.dmem.op) {state := fetch_data}
            .elsewhen(io.dmem.en && io.dmem.op) {state := write_data}
        }
        is(fetch_data){
            when(io.axi.rvalid) {state := update}
        }
        is(update){
            state := idle
        }
        is(write_data){
            when(io.axi.wdone) {state := idle}
        }
    }
    // update buffer
    when(state === idle && io.dmem.en){
        op      := io.dmem.op
        addr    := io.dmem.addr
        wdata   := io.dmem.wdata
        wmask   := io.dmem.wmask
        transfer := io.dmem.transfer
    }
    rdata := Mux(state === update, io.axi.rdata, rdata)
    // axi r output signal
    io.axi.req      := state === fetch_data
    io.axi.raddr    := addr & "hffffffff".U << transfer   // 若tranfer的size为4的话，地址要求4对齐
    // axi w output signal
    io.axi.weq      := state === write_data
    io.axi.waddr    := addr & "hffffffff".U << transfer     // 若tranfer的size为4的话，地址要求4对齐
    io.axi.wdata    := wdata
    io.axi.wmask    := wmask  
    // axi transfer
    io.axi.transfer := transfer
    // dcachebypass output signal
    io.dmem.rdata   := rdata
    io.dmem.ok      := state === idle
}


// icache可以选择不走bypass，而是通过一个转换器将burst取值变为非burst取值
// 这样icache就可以访问外设了
// 做个的原因是外设不走icache的仿真速度会很慢
class ICacheSocAxi extends Module with CacheParameters{
    val io = IO(new Bundle{
        val in = Flipped(new ICacheAxiIO)
        val out0 = new ICacheAxiIO
        val out1 = new ICacheBypassAxiIO
    })
    //
    val times = CacheLineByte / 4
    val cnt_width = OffsetWidth - 2
    //
    val idle :: fetch :: done :: soc_fetch :: soc_done :: soc_all_done :: Nil = Enum(6)
    val state = RegInit(idle)
    //
    val cnt = RegInit(0.U(cnt_width.W))
    val buffer = RegInit(VecInit(Seq.fill(times)(0.U(32.W))))
    //
    switch(state){
        is(idle){
            when(io.in.req && (io.in.addr < "h80000000".U)){state := soc_fetch}
            .elsewhen(io.in.req){state := fetch}
            // when(io.in.req){state := soc_fetch}
        }
        is(fetch){
            when(io.out0.valid){state := done}
        }
        is(done){
            state := idle
        }
        is(soc_fetch){
            when(io.out1.valid){state := soc_done}
        }
        is(soc_done){
            when(cnt === (times - 1).U){state := soc_all_done}
            .otherwise{state := soc_fetch}
        }
        is(soc_all_done){
            state := idle
        }
    }
    //
    when(state === soc_done){buffer(cnt) := io.out1.data}
    var data = 0.U(1.W)
    for(i <- 0 to (times - 1)) data = Cat(buffer(i), data)
    data = data(times * 32, 1)
    //
    when(state === soc_done){cnt := cnt + 1.U}
    .elsewhen(state === soc_all_done){cnt := 0.U}
    .otherwise{cnt := cnt}
    //
    io.out0.req  := state === fetch
    io.out0.addr := io.in.addr
    io.out1.req  := state === soc_fetch
    io.out1.addr := io.in.addr + (cnt << 2.U)
    //
    io.in.valid := state === soc_all_done || state === done
    when(state === done){io.in.data := io.out0.data}
    .elsewhen(state === soc_all_done){io.in.data := data}
    .otherwise{io.in.data := 0.U}
    
}





