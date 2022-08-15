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

class ITrace extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk = Input(Clock())
    val reset = Input(Reset())  

    val commit = Input(Bool())
    val pc = Input(UInt(64.W))
    val inst = Input(UInt(32.W))

    val ren   = Input(Bool())
    val raddr = Input(UInt(64.W))

    val wen   = Input(Bool())
    val waddr = Input(UInt(64.W))
  })
  setInline("ITrace.v",
          """
          |import "DPI-C" function void commit_info_fetch(input logic commit, input longint pc, input int inst, input logic ren, input longint raddr, input logic wen, input longint waddr);
          |
          |module ITrace( input clk,
          |               input reset,
          |               input commit,
          |               input [63:0] pc,            
          |               input [31:0] inst,
          |               input ren,                  
          |               input [63:0] raddr,                            
          |               input wen,                  
          |               input [63:0] waddr);                
          |
          |  always @(*) begin
          |    commit_info_fetch(commit, pc, inst, ren, raddr, wen, waddr);
          |  end
          |endmodule
          |
          """.stripMargin)
}

class MTrace extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk   = Input(Clock())
    val reset = Input(Reset())  

    val valid = Input(Bool())
    val pc    = Input(UInt(64.W))
    val inst  = Input(UInt(32.W))

    val ren   = Input(Bool())
    val raddr = Input(UInt(64.W))
    val rdata = Input(UInt(64.W))

    val wen   = Input(Bool())
    val waddr = Input(UInt(64.W))
    val wdata = Input(UInt(64.W))
    val wmask = Input(UInt(8.W))
  })
  setInline("MTrace.v",
          """
          |import "DPI-C" function void dmem_info_fetch(input logic valid, input longint pc, input int inst, input logic ren, input longint raddr, input longint rdata, input logic wen, input longint waddr, input longint wdata, input byte wmask);
          |
          |module MTrace( input clk,
          |               input reset,
          |               input valid,
          |               input [63:0] pc,            
          |               input [31:0] inst,
          |               input ren,                  
          |               input [63:0] raddr,                 
          |               input [63:0] rdata,                
          |               input wen,                  
          |               input [63:0] waddr,                 
          |               input [63:0] wdata,                 
          |               input [7:0]  wmask );
          |
          |  always @(*) begin
          |    dmem_info_fetch(valid, pc, inst, ren, raddr, rdata, wen, waddr, wdata, wmask);
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

class IMemory_syn extends Module{
  val io = IO(new Bundle{
    val ren   = Input(Bool())
    val raddr = Input(UInt(64.W))
    val rdata = Output(UInt(32.W))
  })
    val raddr = RegEnable(io.raddr, 0.U, io.ren)
    val clk = RegNext(clock.asBool(), false.B)
    val imem = Module(new IMemory_asy)
    imem.io.clk := clock
    imem.io.ren := true.B
    imem.io.raddr := raddr
    io.rdata := imem.io.rdata
}

class IMemory_asy extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk   = Input(Clock())
    val ren   = Input(Bool())
    val raddr = Input(UInt(64.W))
    val rdata = Output(UInt(32.W))
  })
    setInline("IMemory_asy.v",
            """
           |import "DPI-C" function void imem_read(input logic clk, input logic ren, input longint raddr, output int rdata);
           |
           |module IMemory_asy(
           |            input  clk,
           |            input  ren,
           |            input  [63:0] raddr,
           |            output [31:0] rdata);
           |  
           |  always @(*) begin
           |    imem_read(clk, ren, raddr, rdata);
           |  end
           |
           |endmodule
           |
            """.stripMargin)
}


// 会让reg变成wire
// class IMemory extends BlackBox with HasBlackBoxInline{
//   val io = IO(new Bundle{
//     val clk   = Input(Clock())
//     val ren   = Input(Bool())
//     val raddr = Input(UInt(64.W))
//     val rdata = Output(UInt(32.W))
//   })
//     setInline("IMemory.v",
//             """
//            |import "DPI-C" function void imem_read(input logic ren, input longint raddr, output int rdata);
//            |
//            |module IMemory(
//            |            input  clk,
//            |            input  ren,
//            |            input  [63:0] raddr,
//            |            output [31:0] rdata);
//            |
//            |  wire [31:0] val; 
//            |
//            |  always @(*) begin
//            |    
//            |  end
//            |  
//            |  always @(posedge clk) begin
//            |    imem_read(ren, raddr, rdata);
//            |  end
//            |
//            |endmodule
//            |
//            |
//             """.stripMargin)
// }
