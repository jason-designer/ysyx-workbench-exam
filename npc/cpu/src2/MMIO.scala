import chisel3._
import chisel3.util._

class IMMIO extends Module {
    val io = IO(new Bundle {
        val imem = new ICacheIO
        val mem0 = Flipped(new ICacheIO)
        val mem1 = Flipped(new ICacheIO)
    })
    
    val sel = WireInit(0.U)
    val out_ok = WireInit(false.B)
    val out_data = WireInit(0.U(64.W))

    when(!io.mem0.ok){sel := 0.U}
    .elsewhen(!io.mem1.ok){sel := 1.U}
    .otherwise{
        // set mmio address
        when(io.imem.addr < "h80000000".U){sel := 1.U}
        .otherwise{sel := 0.U}
    }

    val sel_r = RegEnable(sel, 0.U, out_ok && io.imem.en)

    io.mem0.en      := Mux(sel === 0.U, io.imem.en, false.B)
    io.mem0.addr    := Mux(sel === 0.U, io.imem.addr, 0.U)
    io.mem1.en      := Mux(sel === 1.U, io.imem.en, false.B)
    io.mem1.addr    := Mux(sel === 1.U, io.imem.addr, 0.U)

    out_ok := MuxLookup(sel_r, 0.U, Array(
        0.U -> io.mem0.ok,
        1.U -> io.mem1.ok,
    ))
    out_data := MuxLookup(sel_r, 0.U, Array(
        0.U -> io.mem0.data,
        1.U -> io.mem1.data,
    ))

    io.imem.ok := out_ok
    io.imem.data := out_data
}

class DMMIO extends Module {
    val io = IO(new Bundle {
        val dmem = new DCacheIO
        val mem0 = Flipped(new DCacheIO)
        val mem1 = Flipped(new DCacheIO)
        val mem2 = Flipped(new DCacheIO)
    })
    
    val sel = WireInit(0.U)
    val out_ok = WireInit(false.B)
    val out_rdata = WireInit(0.U(64.W))

    when(!io.mem0.ok){sel := 0.U}
    .elsewhen(!io.mem1.ok){sel := 1.U}
    .elsewhen(!io.mem2.ok){sel := 2.U}
    .otherwise{
        // set mmio address
        when("h02000000".U <= io.dmem.addr && io.dmem.addr < "h0200c000".U){sel := 1.U}
        .elsewhen(io.dmem.addr < "h80000000".U){sel := 2.U}
        .otherwise{sel := 0.U}
    }

    val sel_r = RegEnable(sel, 0.U, out_ok && io.dmem.en)

    io.mem0.en          := Mux(sel === 0.U, io.dmem.en, false.B)
    io.mem0.op          := Mux(sel === 0.U, io.dmem.op, false.B)
    io.mem0.addr        := Mux(sel === 0.U, io.dmem.addr, 0.U)
    io.mem0.wdata       := Mux(sel === 0.U, io.dmem.wdata, 0.U)
    io.mem0.wmask       := Mux(sel === 0.U, io.dmem.wmask, 0.U)
    io.mem0.transfer    := Mux(sel === 0.U, io.dmem.transfer, 0.U)
    io.mem1.en          := Mux(sel === 1.U, io.dmem.en, false.B)
    io.mem1.op          := Mux(sel === 1.U, io.dmem.op, false.B)
    io.mem1.addr        := Mux(sel === 1.U, io.dmem.addr, 0.U)
    io.mem1.wdata       := Mux(sel === 1.U, io.dmem.wdata, 0.U)
    io.mem1.wmask       := Mux(sel === 1.U, io.dmem.wmask, 0.U)
    io.mem1.transfer    := Mux(sel === 1.U, io.dmem.transfer, 0.U)
    io.mem2.en          := Mux(sel === 2.U, io.dmem.en, false.B)
    io.mem2.op          := Mux(sel === 2.U, io.dmem.op, false.B)
    io.mem2.addr        := Mux(sel === 2.U, io.dmem.addr, 0.U)
    io.mem2.wdata       := Mux(sel === 2.U, io.dmem.wdata, 0.U)
    io.mem2.wmask       := Mux(sel === 2.U, io.dmem.wmask, 0.U)
    io.mem2.transfer    := Mux(sel === 2.U, io.dmem.transfer, 0.U)


    out_ok := MuxLookup(sel_r, 0.U, Array(
        0.U -> io.mem0.ok,
        1.U -> io.mem1.ok,
        2.U -> io.mem2.ok,
    ))
    out_rdata := MuxLookup(sel_r, 0.U, Array(
        0.U -> io.mem0.rdata,
        1.U -> io.mem1.rdata,
        2.U -> io.mem2.rdata,
    ))

    io.dmem.ok := out_ok
    io.dmem.rdata := out_rdata
}

class ClintReg extends Module {
    val io = IO(new Bundle {
        val mem = new DCacheIO
        val set_mtip = Output(Bool())
        val clear_mtip = Output(Bool())
    })
    // 
    val en      = RegNext(io.mem.en,    false.B)
    val op      = RegNext(io.mem.op,    false.B)
    val addr    = RegNext(io.mem.addr,  0.U(64.W))
    val wdata   = RegNext(io.mem.wdata, 0.U(64.W))
    val wmask   = RegNext(io.mem.wmask, 0.U(8.W))

    // define reg
    val mtime = RegInit(0.U(64.W))    
    val mtimecmp = RegInit("h0".U(64.W))
    // process wdata value
    val wm = wmask
    val mask64 = Cat(Fill(8,wm(7)),Fill(8,wm(6)),Fill(8,wm(5)),Fill(8,wm(4)),Fill(8,wm(3)),Fill(8,wm(2)),Fill(8,wm(1)),Fill(8,wm(0)))
    val mtime_update = (mtime & (~mask64)) | (mask64 & wdata)
    val mtimecmp_update = (mtimecmp & (~mask64)) | (mask64 & wdata)
    // 
    val sel = Cat(addr === "h02004000".U, addr === "h0200bff8".U) 
    // update mtime
    // ------------------------------------------------------------------------------------------------
    // 注意！！！！！！！！！！
    // mtime自增太快会导致在跑rtthread的时候，上一个时钟中断还没处理完下一个时钟中断就来了，这样会导致代码跑飞，而且很难从difftest看出
    // 这里即使mtime自增1也是太快了，所以进行了分频. 
    // 也可以把Cache调到4KB，这样运算比较快，就可以mtime自增1了
    // ------------------------------------------------------------------------------------------------
    // val mtime_clk = RegInit(0.U(1.W))
    // mtime_clk := mtime_clk + 1.U
    when(en && op && sel === "b01".U){mtime := mtime_update}
    .otherwise{
        // when(mtime_clk === 0.U){mtime := mtime + "h1".U}
        mtime := mtime + "h1".U
    }
    // update mtimecmp
    when(en && op && sel === "b10".U){mtimecmp := mtimecmp_update}
    .otherwise{mtimecmp := mtimecmp}
    // output
    io.mem.ok := true.B
    when(en && !op){
        io.mem.rdata := MuxLookup(sel, 0.U, Array(
            "b01".U -> mtime,        //mtime
            "b10".U -> mtimecmp,    //mtimecmp
        ))
    }
    .otherwise{io.mem.rdata := 0.U}
    io.set_mtip := !io.clear_mtip && mtimecmp <= mtime  // 有clear的时候，clear优先
    io.clear_mtip := en && op && sel === "b10".U
}

