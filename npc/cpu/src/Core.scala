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
  val preamu  = Module(new PreAccessMemory)
  val amu     = Module(new AccessMemory)
  val wbu     = Module(new WriteBack)

  val flushdelay       = Module(new JumpFlushDelay)
  val imemrh           = Module(new ImemoryReadHold)
  val cconflict_exereg = Module(new CorrelationConflict)
  val cconflict_memreg = Module(new CorrelationConflict)
  val cconflict_wbreg  = Module(new CorrelationConflict)

  val ifreg   = Module(new IFReg)
  val idreg   = Module(new IDReg)
  val exereg  = Module(new ExeReg)
  val memreg  = Module(new MemReg)
  val wbreg   = Module(new WBReg)
  //
  rfu.io.clk    := clock
  rfu.io.reset  := reset
  //
  preifu.io.jump_en := flushdelay.io.preifu_jump_en
  preifu.io.jump_pc := idu.io.jump_pc
  //ifreg
  ifreg.io.next_pc_in := preifu.io.next_pc
  imemrh.io.raddr := preifu.io.next_pc      //为imem添加ren为false时候的读保持功能
  io.imem.en      := imemrh.io.imem_ren
  io.imem.addr    := imemrh.io.imem_raddr
  //ifu
  ifu.io.pc_in    := ifreg.io.next_pc_out
  ifu.io.inst_in  := io.imem.data
  //idreg
  idreg.io.pc_in   := ifu.io.pc_out
  idreg.io.inst_in := ifu.io.inst_out
  //idu
  flushdelay.io.in := idu.io.jump_en

  idu.io.pc       := idreg.io.pc_out
  idu.io.inst     := idreg.io.inst_out
  idu.io.rs1_data := rfu.io.rs1_data
  idu.io.rs2_data := rfu.io.rs2_data
  //exereg
  exereg.io.pc_in       := idreg.io.pc_out
  exereg.io.inst_in     := idreg.io.inst_out
  exereg.io.rd_en_in    := idu.io.rd_en
  exereg.io.rd_addr_in  := idu.io.rd_addr
  exereg.io.imm_in      := idu.io.imm
  exereg.io.op1_in      := idu.io.op1
  exereg.io.op2_in      := idu.io.op2
  exereg.io.decode_info_in <> idu.io.decode_info
  //ieu
  ieu.io.decode_info <> exereg.io.decode_info_out
  ieu.io.op1 := exereg.io.op1_out
  ieu.io.op2 := exereg.io.op2_out
  ieu.io.pc  := exereg.io.pc_out
  ieu.io.imm := exereg.io.imm_out
  //memreg
  memreg.io.pc_in      := exereg.io.pc_out
  memreg.io.inst_in    := exereg.io.inst_out
  memreg.io.rd_en_in   := exereg.io.rd_en_out
  memreg.io.rd_addr_in := exereg.io.rd_addr_out
  memreg.io.imm_in     := exereg.io.imm_out
  memreg.io.op1_in     := exereg.io.op1_out
  memreg.io.op2_in     := exereg.io.op2_out
  memreg.io.decode_info_in <> exereg.io.decode_info_out

  memreg.io.alu_out_in := ieu.io.alu_out
  memreg.io.bu_out_in  := ieu.io.bu_out
  memreg.io.mdu_out_in := ieu.io.mdu_out
  //preamu
  preamu.io.lu_code := memreg.io.decode_info_out.lu_code
  preamu.io.su_code := memreg.io.decode_info_out.su_code
  preamu.io.op1     := memreg.io.op1_out
  preamu.io.op2     := memreg.io.op2_out
  preamu.io.imm     := memreg.io.imm_out
  //dmem
  io.dmem.ren   := preamu.io.ren
  io.dmem.raddr := preamu.io.raddr
  io.dmem.wen   := preamu.io.wen & memreg.io.pr.valid_out //必须是有效的流水线指令才写入
  io.dmem.waddr := preamu.io.waddr
  io.dmem.wdata := preamu.io.wdata
  io.dmem.wmask := preamu.io.wmask
  //wbreg
  wbreg.io.pc_in      := memreg.io.pc_out
  wbreg.io.inst_in    := memreg.io.inst_out
  wbreg.io.rd_en_in   := memreg.io.rd_en_out
  wbreg.io.rd_addr_in := memreg.io.rd_addr_out
  wbreg.io.alu_out_in := memreg.io.alu_out_out
  wbreg.io.bu_out_in  := memreg.io.bu_out_out
  wbreg.io.mdu_out_in := memreg.io.mdu_out_out
  wbreg.io.fu_code_in := memreg.io.decode_info_out.fu_code
  wbreg.io.lu_code_in := memreg.io.decode_info_out.lu_code
  
  wbreg.io.lu_shift_in := preamu.io.lu_shift
  //amu
  amu.io.lu_code  := wbreg.io.lu_code_out
  amu.io.lu_shift := wbreg.io.lu_shift_out
  amu.io.rdata    := io.dmem.rdata
  //wbu
  wbu.io.fu_code := wbreg.io.fu_code_out
  wbu.io.alu_out := wbreg.io.alu_out_out
  wbu.io.bu_out  := wbreg.io.bu_out_out
  wbu.io.mdu_out := wbreg.io.mdu_out_out
  wbu.io.lu_out  := amu.io.lu_out

  //rfu
  rfu.io.rs1_en   := idu.io.rs1_en
  rfu.io.rs2_en   := idu.io.rs2_en
  rfu.io.rs1_addr := idu.io.rs1_addr
  rfu.io.rs2_addr := idu.io.rs2_addr

  rfu.io.rd_en    := wbreg.io.rd_en_out & wbreg.io.pr.valid_out //必须是有效的流水线指令才写入
  rfu.io.rd_addr  := wbreg.io.rd_addr_out 
  rfu.io.rd_data  := wbu.io.out
  
  //相关性冲突
  cconflict_exereg.io.rs_valid  := idreg.io.pr.valid_out
  cconflict_exereg.io.rd_valid  := exereg.io.pr.valid_out
  cconflict_exereg.io.rs1_en    := idu.io.rs1_en
  cconflict_exereg.io.rs2_en    := idu.io.rs2_en
  cconflict_exereg.io.rs1_addr  := idu.io.rs1_addr
  cconflict_exereg.io.rs2_addr  := idu.io.rs2_addr
  cconflict_exereg.io.rd_en     := exereg.io.rd_en_out
  cconflict_exereg.io.rd_addr   := exereg.io.rd_addr_out

  cconflict_memreg.io.rs_valid  := idreg.io.pr.valid_out
  cconflict_memreg.io.rd_valid  := memreg.io.pr.valid_out
  cconflict_memreg.io.rs1_en    := idu.io.rs1_en
  cconflict_memreg.io.rs2_en    := idu.io.rs2_en
  cconflict_memreg.io.rs1_addr  := idu.io.rs1_addr
  cconflict_memreg.io.rs2_addr  := idu.io.rs2_addr
  cconflict_memreg.io.rd_en     := memreg.io.rd_en_out
  cconflict_memreg.io.rd_addr   := memreg.io.rd_addr_out

  cconflict_wbreg.io.rs_valid   := idreg.io.pr.valid_out
  cconflict_wbreg.io.rd_valid   := wbreg.io.pr.valid_out
  cconflict_wbreg.io.rs1_en     := idu.io.rs1_en
  cconflict_wbreg.io.rs2_en     := idu.io.rs2_en
  cconflict_wbreg.io.rs1_addr   := idu.io.rs1_addr
  cconflict_wbreg.io.rs2_addr   := idu.io.rs2_addr
  cconflict_wbreg.io.rd_en      := wbreg.io.rd_en_out
  cconflict_wbreg.io.rd_addr    := wbreg.io.rd_addr_out

  val stall = cconflict_exereg.io.conflict || cconflict_memreg.io.conflict || cconflict_wbreg.io.conflict
  //熄火的时候: 1.exereg的valid要为false.B
  //          2.preifu维持原值
  //          3.ifreg和idreg维持原值

  //流水线控制
  preifu.io.stall := stall
  flushdelay.io.en := !stall

  ifreg.io.pr.valid_in  := preifu.io.valid
  idreg.io.pr.valid_in  := ifreg.io.pr.valid_out
  exereg.io.pr.valid_in := idreg.io.pr.valid_out && flushdelay.io.exereg_valid && (!stall)
  memreg.io.pr.valid_in := exereg.io.pr.valid_out
  wbreg.io.pr.valid_in  := memreg.io.pr.valid_out
  
  ifreg.io.pr.en  := !stall
  imemrh.io.ren   := !stall
  idreg.io.pr.en  := flushdelay.io.idreg_en && (!stall)
  exereg.io.pr.en := true.B
  memreg.io.pr.en := true.B
  wbreg.io.pr.en  := true.B


  
  //debug
  printf("pc=%x inst=%x valid=%d wen=%d waddr=%d wdata=%x stall=%d\n", wbreg.io.pc_out, wbreg.io.inst_out, wbreg.io.pr.valid_out, wbreg.io.rd_en_out, wbreg.io.rd_addr_out, wbu.io.out, stall)
  //halt
  val halt = Module(new Halt)
  halt.io.clk   := clock
  halt.io.reset := reset
  halt.io.halt  := wbreg.io.inst_out === EBREAK || wbreg.io.inst_out === "h0000006b".U
  //difftest
  val difftest = Module(new Difftest)
  difftest.io.valid := wbreg.io.pr.valid_out
  difftest.io.pc := wbreg.io.pc_out
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

