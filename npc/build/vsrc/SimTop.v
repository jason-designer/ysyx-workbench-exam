module IFetch(
  input         clock,
  input         reset,
  output [63:0] io_imem_addr,
  input  [31:0] io_imem_data,
  output [63:0] io_pc,
  output [31:0] io_inst
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
`endif // RANDOMIZE_REG_INIT
  reg [31:0] pc; // @[IFetch.scala 13:19]
  wire [31:0] _pc_T_1 = pc + 32'h4; // @[IFetch.scala 14:40]
  assign io_imem_addr = {{32'd0}, pc}; // @[IFetch.scala 18:17]
  assign io_pc = {{32'd0}, pc}; // @[IFetch.scala 19:17]
  assign io_inst = io_imem_data; // @[IFetch.scala 20:17]
  always @(posedge clock) begin
    if (reset) begin // @[IFetch.scala 13:19]
      pc <= 32'h80000000; // @[IFetch.scala 13:19]
    end else begin
      pc <= _pc_T_1; // @[IFetch.scala 14:6]
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  pc = _RAND_0[31:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
module Decode(
  input  [31:0] io_inst,
  output        io_decode_info_fu_code,
  output        io_decode_info_alu_code,
  output        io_rs1_en,
  output        io_rs2_en,
  output        io_rd_en,
  output [4:0]  io_rs1_addr,
  output [4:0]  io_rs2_addr,
  output [4:0]  io_rd_addr,
  input  [63:0] io_rs1_data,
  input  [63:0] io_rs2_data,
  output [63:0] io_op1,
  output [63:0] io_op2
);
  wire [31:0] _addi_T = io_inst & 32'h707f; // @[Decode.scala 32:21]
  wire  addi = 32'h13 == _addi_T; // @[Decode.scala 32:21]
  wire [5:0] inst_type = {1'h0,addi,1'h0,3'h0}; // @[Cat.scala 30:58]
  wire [51:0] imm_i_hi = io_inst[31] ? 52'hfffffffffffff : 52'h0; // @[Bitwise.scala 72:12]
  wire [11:0] imm_i_lo = io_inst[31:20]; // @[Decode.scala 55:45]
  wire [63:0] imm_i = {imm_i_hi,imm_i_lo}; // @[Cat.scala 30:58]
  wire [6:0] imm_s_hi_lo = io_inst[31:25]; // @[Decode.scala 56:45]
  wire [4:0] imm_s_lo = io_inst[11:7]; // @[Decode.scala 56:59]
  wire [63:0] imm_s = {imm_i_hi,imm_s_hi_lo,imm_s_lo}; // @[Cat.scala 30:58]
  wire [42:0] imm_b_hi_hi_hi = io_inst[31] ? 43'h7ffffffffff : 43'h0; // @[Bitwise.scala 72:12]
  wire  imm_b_hi_lo = io_inst[7]; // @[Decode.scala 57:55]
  wire [5:0] imm_b_lo_hi_hi = io_inst[30:25]; // @[Decode.scala 57:64]
  wire [3:0] imm_b_lo_hi_lo = io_inst[11:8]; // @[Decode.scala 57:78]
  wire [55:0] imm_b = {imm_b_hi_hi_hi,io_inst[31],imm_b_hi_lo,imm_b_lo_hi_hi,imm_b_lo_hi_lo,1'h0}; // @[Cat.scala 30:58]
  wire [31:0] imm_u_hi_hi = io_inst[31] ? 32'hffffffff : 32'h0; // @[Bitwise.scala 72:12]
  wire [19:0] imm_u_hi_lo = io_inst[31:12]; // @[Decode.scala 58:45]
  wire [63:0] imm_u = {imm_u_hi_hi,imm_u_hi_lo,12'h0}; // @[Cat.scala 30:58]
  wire [7:0] imm_j_hi_lo = io_inst[19:12]; // @[Decode.scala 59:55]
  wire  imm_j_lo_hi_hi = io_inst[20]; // @[Decode.scala 59:69]
  wire [9:0] imm_j_lo_hi_lo = io_inst[30:21]; // @[Decode.scala 59:79]
  wire [63:0] imm_j = {imm_b_hi_hi_hi,io_inst[31],imm_j_hi_lo,imm_j_lo_hi_hi,imm_j_lo_hi_lo,1'h0}; // @[Cat.scala 30:58]
  wire [63:0] _imm_T_3 = 6'h10 == inst_type ? imm_i : 64'h0; // @[Mux.scala 80:57]
  wire [63:0] _imm_T_5 = 6'h8 == inst_type ? imm_s : _imm_T_3; // @[Mux.scala 80:57]
  wire [63:0] _imm_T_7 = 6'h4 == inst_type ? {{8'd0}, imm_b} : _imm_T_5; // @[Mux.scala 80:57]
  wire [63:0] _imm_T_9 = 6'h2 == inst_type ? imm_u : _imm_T_7; // @[Mux.scala 80:57]
  wire [63:0] imm = 6'h1 == inst_type ? imm_j : _imm_T_9; // @[Mux.scala 80:57]
  assign io_decode_info_fu_code = 32'h13 == _addi_T; // @[Decode.scala 32:21]
  assign io_decode_info_alu_code = 32'h13 == _addi_T; // @[Decode.scala 32:21]
  assign io_rs1_en = 32'h13 == _addi_T; // @[Decode.scala 32:21]
  assign io_rs2_en = 1'h0; // @[Decode.scala 79:35]
  assign io_rd_en = 32'h13 == _addi_T; // @[Decode.scala 32:21]
  assign io_rs1_addr = io_inst[19:15]; // @[Decode.scala 74:24]
  assign io_rs2_addr = io_inst[24:20]; // @[Decode.scala 75:24]
  assign io_rd_addr = io_inst[11:7]; // @[Decode.scala 76:24]
  assign io_op1 = io_rs1_en ? io_rs1_data : 64'h0; // @[Decode.scala 83:18]
  assign io_op2 = io_rs2_en ? io_rs2_data : imm; // @[Decode.scala 84:18]
endmodule
module Execution(
  input         io_decode_info_fu_code,
  input         io_decode_info_alu_code,
  input  [63:0] io_op1,
  input  [63:0] io_op2,
  output [63:0] io_out
);
  wire [63:0] _alu_out_T_1 = io_op1 + io_op2; // @[Execution.scala 24:29]
  wire [63:0] alu_out = io_decode_info_alu_code ? _alu_out_T_1 : 64'h0; // @[Mux.scala 80:57]
  assign io_out = io_decode_info_fu_code ? alu_out : 64'h0; // @[Mux.scala 80:57]
endmodule
module Core(
  input         clock,
  input         reset,
  output [63:0] io_imem_addr,
  input  [31:0] io_imem_data
);
  wire  ifu_clock; // @[Core.scala 11:19]
  wire  ifu_reset; // @[Core.scala 11:19]
  wire [63:0] ifu_io_imem_addr; // @[Core.scala 11:19]
  wire [31:0] ifu_io_imem_data; // @[Core.scala 11:19]
  wire [63:0] ifu_io_pc; // @[Core.scala 11:19]
  wire [31:0] ifu_io_inst; // @[Core.scala 11:19]
  wire [31:0] idu_io_inst; // @[Core.scala 12:19]
  wire  idu_io_decode_info_fu_code; // @[Core.scala 12:19]
  wire  idu_io_decode_info_alu_code; // @[Core.scala 12:19]
  wire  idu_io_rs1_en; // @[Core.scala 12:19]
  wire  idu_io_rs2_en; // @[Core.scala 12:19]
  wire  idu_io_rd_en; // @[Core.scala 12:19]
  wire [4:0] idu_io_rs1_addr; // @[Core.scala 12:19]
  wire [4:0] idu_io_rs2_addr; // @[Core.scala 12:19]
  wire [4:0] idu_io_rd_addr; // @[Core.scala 12:19]
  wire [63:0] idu_io_rs1_data; // @[Core.scala 12:19]
  wire [63:0] idu_io_rs2_data; // @[Core.scala 12:19]
  wire [63:0] idu_io_op1; // @[Core.scala 12:19]
  wire [63:0] idu_io_op2; // @[Core.scala 12:19]
  wire  ieu_io_decode_info_fu_code; // @[Core.scala 13:19]
  wire  ieu_io_decode_info_alu_code; // @[Core.scala 13:19]
  wire [63:0] ieu_io_op1; // @[Core.scala 13:19]
  wire [63:0] ieu_io_op2; // @[Core.scala 13:19]
  wire [63:0] ieu_io_out; // @[Core.scala 13:19]
  wire  rfu_clk; // @[Core.scala 14:19]
  wire  rfu_reset; // @[Core.scala 14:19]
  wire  rfu_rs1_en; // @[Core.scala 14:19]
  wire  rfu_rs2_en; // @[Core.scala 14:19]
  wire  rfu_rd_en; // @[Core.scala 14:19]
  wire [4:0] rfu_rs1_addr; // @[Core.scala 14:19]
  wire [4:0] rfu_rs2_addr; // @[Core.scala 14:19]
  wire [4:0] rfu_rd_addr; // @[Core.scala 14:19]
  wire [63:0] rfu_rs1_data; // @[Core.scala 14:19]
  wire [63:0] rfu_rs2_data; // @[Core.scala 14:19]
  wire [63:0] rfu_rd_data; // @[Core.scala 14:19]
  wire  halt_clk; // @[Core.scala 45:20]
  wire  halt_reset; // @[Core.scala 45:20]
  wire  halt_halt; // @[Core.scala 45:20]
  IFetch ifu ( // @[Core.scala 11:19]
    .clock(ifu_clock),
    .reset(ifu_reset),
    .io_imem_addr(ifu_io_imem_addr),
    .io_imem_data(ifu_io_imem_data),
    .io_pc(ifu_io_pc),
    .io_inst(ifu_io_inst)
  );
  Decode idu ( // @[Core.scala 12:19]
    .io_inst(idu_io_inst),
    .io_decode_info_fu_code(idu_io_decode_info_fu_code),
    .io_decode_info_alu_code(idu_io_decode_info_alu_code),
    .io_rs1_en(idu_io_rs1_en),
    .io_rs2_en(idu_io_rs2_en),
    .io_rd_en(idu_io_rd_en),
    .io_rs1_addr(idu_io_rs1_addr),
    .io_rs2_addr(idu_io_rs2_addr),
    .io_rd_addr(idu_io_rd_addr),
    .io_rs1_data(idu_io_rs1_data),
    .io_rs2_data(idu_io_rs2_data),
    .io_op1(idu_io_op1),
    .io_op2(idu_io_op2)
  );
  Execution ieu ( // @[Core.scala 13:19]
    .io_decode_info_fu_code(ieu_io_decode_info_fu_code),
    .io_decode_info_alu_code(ieu_io_decode_info_alu_code),
    .io_op1(ieu_io_op1),
    .io_op2(ieu_io_op2),
    .io_out(ieu_io_out)
  );
  RegFile rfu ( // @[Core.scala 14:19]
    .clk(rfu_clk),
    .reset(rfu_reset),
    .rs1_en(rfu_rs1_en),
    .rs2_en(rfu_rs2_en),
    .rd_en(rfu_rd_en),
    .rs1_addr(rfu_rs1_addr),
    .rs2_addr(rfu_rs2_addr),
    .rd_addr(rfu_rd_addr),
    .rs1_data(rfu_rs1_data),
    .rs2_data(rfu_rs2_data),
    .rd_data(rfu_rd_data)
  );
  Halt halt ( // @[Core.scala 45:20]
    .clk(halt_clk),
    .reset(halt_reset),
    .halt(halt_halt)
  );
  assign io_imem_addr = ifu_io_imem_addr; // @[Core.scala 20:15]
  assign ifu_clock = clock;
  assign ifu_reset = reset;
  assign ifu_io_imem_data = io_imem_data; // @[Core.scala 20:15]
  assign idu_io_inst = ifu_io_inst; // @[Core.scala 25:19]
  assign idu_io_rs1_data = rfu_rs1_data; // @[Core.scala 27:19]
  assign idu_io_rs2_data = rfu_rs2_data; // @[Core.scala 28:19]
  assign ieu_io_decode_info_fu_code = idu_io_decode_info_fu_code; // @[Core.scala 26:22]
  assign ieu_io_decode_info_alu_code = idu_io_decode_info_alu_code; // @[Core.scala 26:22]
  assign ieu_io_op1 = idu_io_op1; // @[Core.scala 30:14]
  assign ieu_io_op2 = idu_io_op2; // @[Core.scala 31:14]
  assign rfu_clk = clock; // @[Core.scala 16:17]
  assign rfu_reset = reset; // @[Core.scala 17:17]
  assign rfu_rs1_en = idu_io_rs1_en; // @[Core.scala 34:19]
  assign rfu_rs2_en = 1'h0; // @[Core.scala 35:19]
  assign rfu_rd_en = idu_io_rd_en; // @[Core.scala 36:19]
  assign rfu_rs1_addr = idu_io_rs1_addr; // @[Core.scala 37:19]
  assign rfu_rs2_addr = idu_io_rs2_addr; // @[Core.scala 38:19]
  assign rfu_rd_addr = idu_io_rd_addr; // @[Core.scala 39:19]
  assign rfu_rd_data = ieu_io_out; // @[Core.scala 40:19]
  assign halt_clk = clock; // @[Core.scala 46:17]
  assign halt_reset = reset; // @[Core.scala 47:17]
  assign halt_halt = ifu_io_inst == 32'h100073; // @[Core.scala 48:32]
  always @(posedge clock) begin
    `ifndef SYNTHESIS
    `ifdef PRINTF_COND
      if (`PRINTF_COND) begin
    `endif
        if (~reset) begin
          $fwrite(32'h80000002,"pc=%x inst=%x wen=%d waddr=%d wdata=%x\n",ifu_io_pc,ifu_io_inst,idu_io_rd_en,
            idu_io_rd_addr,ieu_io_out); // @[Core.scala 43:9]
        end
    `ifdef PRINTF_COND
      end
    `endif
    `endif // SYNTHESIS
  end
endmodule
module SimTop(
  input         clock,
  input         reset,
  output        io_imem_en,
  output [63:0] io_imem_addr,
  input  [31:0] io_imem_data
);
  wire  core_clock; // @[SimTop.scala 27:20]
  wire  core_reset; // @[SimTop.scala 27:20]
  wire [63:0] core_io_imem_addr; // @[SimTop.scala 27:20]
  wire [31:0] core_io_imem_data; // @[SimTop.scala 27:20]
  Core core ( // @[SimTop.scala 27:20]
    .clock(core_clock),
    .reset(core_reset),
    .io_imem_addr(core_io_imem_addr),
    .io_imem_data(core_io_imem_data)
  );
  assign io_imem_en = 1'h1; // @[SimTop.scala 28:11]
  assign io_imem_addr = core_io_imem_addr; // @[SimTop.scala 28:11]
  assign core_clock = clock;
  assign core_reset = reset;
  assign core_io_imem_data = io_imem_data; // @[SimTop.scala 28:11]
endmodule
