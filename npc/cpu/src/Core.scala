import chisel3._
import chisel3.util._
import Instructions._

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

class Core extends Module{
  val io = IO(new Bundle{
    val imem = new ImemIO
    val dmem = new DmemIO
  })

  val preifu  = Module(new PreIFetch)
  val ifu     = Module(new IFetch)
  val idu     = Module(new Decode)
  val ieu     = Module(new Execution)
  val rfu     = Module(new RegFile)

  val flushdelay = Module(new JumpFlushDelay)

  val ifreg   = Module(new IFReg)
  val idreg   = Module(new IDReg)
  // val exereg  = Module(new ExeReg)
  // val memreg  = Module(new MemReg)
  // val wbreg   = Module(new WBReg)
  //
  rfu.io.clk    := clock
  rfu.io.reset  := reset
  //
  preifu.io.jump_en := flushdelay.io.jump_en
  preifu.io.jump_pc := idu.io.jump_pc

  ifreg.io.next_pc_in := preifu.io.next_pc
  io.imem.en          := true.B
  io.imem.addr        := preifu.io.next_pc
  
  ifu.io.pc_in    := ifreg.io.next_pc_out
  ifu.io.inst_in  := io.imem.data

  idreg.io.pc_in   := ifu.io.pc_out
  idreg.io.inst_in := ifu.io.inst_out

  ifreg.io.pr.valid_in := preifu.io.valid
  idreg.io.pr.valid_in := ifreg.io.pr.valid_out
  ifreg.io.pr.en := true.B
  idreg.io.pr.en := flushdelay.io.reg_en

  flushdelay.io.in := idu.io.jump_en


  //
  // ifu.io.imem <> io.imem
  // ifu.io.jump_en := idu.io.jump_en
  // ifu.io.jump_pc := idu.io.jump_pc

  idu.io.pc       := idreg.io.pc_out
  idu.io.inst     := idreg.io.inst_out
  idu.io.decode_info <> ieu.io.decode_info
  idu.io.rs1_data := rfu.io.rs1_data
  idu.io.rs2_data := rfu.io.rs2_data

  ieu.io.op1 := idu.io.op1
  ieu.io.op2 := idu.io.op2
  ieu.io.pc  := idreg.io.pc_out
  ieu.io.imm := idu.io.imm
  ieu.io.dmem <> io.dmem

  rfu.io.rs1_en   := idu.io.rs1_en
  rfu.io.rs2_en   := idu.io.rs2_en
  rfu.io.rd_en    := idu.io.rd_en
  rfu.io.rs1_addr := idu.io.rs1_addr
  rfu.io.rs2_addr := idu.io.rs2_addr
  rfu.io.rd_addr  := idu.io.rd_addr
  rfu.io.rd_data  := ieu.io.out
  

  //debug
  printf("pc=%x inst=%x valid=%d wen=%d waddr=%d wdata=%x\n", idreg.io.pc_out, idreg.io.inst_out, idreg.io.pr.valid_out, idu.io.rd_en, idu.io.rd_addr, ieu.io.out)
  //halt
  val halt = Module(new Halt)
  halt.io.clk   := clock
  halt.io.reset := reset
  halt.io.halt  := idreg.io.inst_out === EBREAK || idreg.io.inst_out === "h0000006b".U

}


class Halt extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk = Input(Clock())
    val reset = Input(Reset())  //csdn的教程错了，是Reset()才对，不是Bool()
    val halt = Input(Bool())
  })
    setInline("Halt.v",
            """
           |import "DPI-C" function void read_halt(input logic halt);
           |
           |module Halt(input clk,
           |            input reset,
           |            input halt);
           |
           |  always @(posedge clk) begin
           |    read_halt(halt);
           |  end
           |endmodule
           |
            """.stripMargin)
}


class DMemory extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk   = Input(Clock())
    val ren   = Input(Bool())
    val raddr = Input(UInt(64.W))
    val rdata = Output(UInt(64.W))
    val wen   = Input(Bool())
    val waddr = Input(UInt(64.W))
    val wdata = Input(UInt(64.W))
    val wmask = Input(UInt(8.W))
  })
    setInline("DMemory.v",
            """
           |import "DPI-C" function void pmem_read(input logic ren, input longint raddr, output longint rdata);
           |import "DPI-C" function void pmem_write(input logic wen, input longint waddr, input longint wdata, input byte wmask);
           |
           |module DMemory(
           |            input  clk,
           |            input  ren,
           |            input  [63:0] raddr,
           |            output [63:0] rdata,
           |            input  wen,
           |            input  [63:0] waddr,
           |            input  [63:0] wdata,
           |            input  [7:0]  wmask);
           |
           |  always @(*) begin
           |    pmem_read(ren, raddr, rdata);
           |    pmem_write(wen, waddr, wdata, wmask);
           |  end
           |
           |endmodule
           |
           |
            """.stripMargin)
}

class IMemory extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk   = Input(Clock())
    val ren   = Input(Bool())
    val raddr = Input(UInt(64.W))
    val rdata = Output(UInt(32.W))
  })
    setInline("IMemory.v",
            """
           |import "DPI-C" function void imem_read(input logic ren, input longint raddr, output int rdata);
           |
           |module IMemory(
           |            input  clk,
           |            input  ren,
           |            input  [63:0] raddr,
           |            output reg [31:0] rdata);
           |
           |  wire [31:0] val; 
           |
           |  always @(*) begin
           |    imem_read(ren, raddr, val);
           |  end
           |  
           |  always @(posedge clk) begin
           |    if (clk) begin
           |      rdata <= val;
           |    end else begin
           |      rdata <= rdata;
           |    end
           |  end
           |
           |endmodule
           |
           |
            """.stripMargin)
}

