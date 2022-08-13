import chisel3._
import chisel3.util._

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
           |  always @(posedge clk) begin
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

class Difftest extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val valid = Input(Bool())
    val pc = Input(UInt(64.W))
  })
  setInline("Difftest.v",
            """
           |import "DPI-C" function void read_difftest_valid(input logic valid);
           |import "DPI-C" function void read_pc(input longint pc);
           |
           |module Difftest(input valid,
           |                input [63:0] pc);
           |
           |  always @(*) begin
           |    read_difftest_valid(valid);
           |    read_pc(pc);
           |  end
           |
           |endmodule
           |
            """.stripMargin)
}

