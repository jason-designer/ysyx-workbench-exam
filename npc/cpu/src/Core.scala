import chisel3._
import chisel3.util._
import Instructions._

class Core extends Module{
  val io = IO(new Bundle{
    val imem = new ImemIO
    //val dmem = new DmemIO
  })

  val ifu = Module(new IFetch)
  val idu = Module(new Decode)
  val ieu = Module(new Execution)
  val rfu = Module(new RegFile)
  //
  rfu.io.clk    := clock
  rfu.io.reset  := reset
  
  //
  ifu.io.imem <> io.imem
  ifu.io.jump_en := ieu.io.jump_en
  ifu.io.jump_pc := ieu.io.jump_pc

  idu.io.pc       := ifu.io.pc
  idu.io.inst     := ifu.io.inst
  idu.io.decode_info <> ieu.io.decode_info
  idu.io.rs1_data := rfu.io.rs1_data
  idu.io.rs2_data := rfu.io.rs2_data

  ieu.io.op1 := idu.io.op1
  ieu.io.op2 := idu.io.op2
  ieu.io.pc  := ifu.io.pc
  ieu.io.imm := idu.io.imm

  rfu.io.rs1_en   := idu.io.rs1_en
  rfu.io.rs2_en   := idu.io.rs2_en
  rfu.io.rd_en    := idu.io.rd_en
  rfu.io.rs1_addr := idu.io.rs1_addr
  rfu.io.rs2_addr := idu.io.rs2_addr
  rfu.io.rd_addr  := idu.io.rd_addr
  rfu.io.rd_data  := ieu.io.out
  
  //debug
  printf("pc=%x inst=%x wen=%d waddr=%d wdata=%x\n", ifu.io.pc, ifu.io.inst, idu.io.rd_en, idu.io.rd_addr, ieu.io.out)
  //halt
  val halt = Module(new Halt)
  halt.io.clk   := clock
  halt.io.reset := reset
  halt.io.halt  := ifu.io.inst === EBREAK || ifu.io.inst === "h0000006b".U

}


class Halt extends BlackBox with HasBlackBoxInline{
  val io = IO(new Bundle{
    val clk = Input(Clock())
    val reset = Input(Reset())  //csdn的教程错了，是Reset()才对，不是Bool()
    val halt = Input(Bool())
  })
    setInline("Halt.v",
            """
           |import "DPI-C" function void set_halt_ptr(input logic a []);
           |
           |module Halt(input clk,
           |            input reset,
           |            input halt);
           |
           |  reg halt_reg [0:0];
           |  initial set_halt_ptr(halt_reg);
           |
           |  always @(posedge clk) begin
           |    if (reset) begin 
           |      halt_reg[0] <= 1'b0;
           |    end else begin
           |      halt_reg[0] <= halt; // 
           |    end
           |  end
           |endmodule
           |
           |
            """.stripMargin)
}


