module IFetch(
  input         clock,
  input         reset,
  output [63:0] io_imem_addr,
  input  [31:0] io_imem_data,
  output [63:0] io_pc,
  output [31:0] io_inst,
  input         io_jump_en,
  input  [31:0] io_jump_pc
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
    end else if (io_jump_en) begin // @[IFetch.scala 14:12]
      pc <= io_jump_pc;
    end else begin
      pc <= _pc_T_1;
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
  output [3:0]  io_decode_info_fu_code,
  output [15:0] io_decode_info_alu_code,
  output [7:0]  io_decode_info_bu_code,
  output        io_rs1_en,
  output        io_rs2_en,
  output        io_rd_en,
  output [4:0]  io_rs1_addr,
  output [4:0]  io_rs2_addr,
  output [4:0]  io_rd_addr,
  input  [63:0] io_rs1_data,
  input  [63:0] io_rs2_data,
  output [63:0] io_op1,
  output [63:0] io_op2,
  output [63:0] io_imm
);
  wire [31:0] _sll_T = io_inst & 32'hfe00707f; // @[Decode.scala 36:20]
  wire  sll = 32'h1033 == _sll_T; // @[Decode.scala 36:20]
  wire  srl = 32'h5033 == _sll_T; // @[Decode.scala 37:20]
  wire  sra = 32'h40005033 == _sll_T; // @[Decode.scala 38:20]
  wire [31:0] _slli_T = io_inst & 32'hfc00707f; // @[Decode.scala 39:21]
  wire  slli = 32'h1013 == _slli_T; // @[Decode.scala 39:21]
  wire  srli = 32'h5013 == _slli_T; // @[Decode.scala 40:21]
  wire  srai = 32'h40005013 == _slli_T; // @[Decode.scala 41:21]
  wire  sllw = 32'h103b == _sll_T; // @[Decode.scala 42:21]
  wire  srlw = 32'h503b == _sll_T; // @[Decode.scala 43:21]
  wire  sraw = 32'h4000503b == _sll_T; // @[Decode.scala 44:21]
  wire  slliw = 32'h101b == _sll_T; // @[Decode.scala 45:22]
  wire  srliw = 32'h501b == _sll_T; // @[Decode.scala 46:22]
  wire  sraiw = 32'h4000501b == _sll_T; // @[Decode.scala 47:22]
  wire  add = 32'h33 == _sll_T; // @[Decode.scala 49:24]
  wire  addw = 32'h3b == _sll_T; // @[Decode.scala 50:24]
  wire [31:0] _addi_T = io_inst & 32'h707f; // @[Decode.scala 51:24]
  wire  addi = 32'h13 == _addi_T; // @[Decode.scala 51:24]
  wire  addiw = 32'h1b == _addi_T; // @[Decode.scala 52:24]
  wire  alu_sub = 32'h40000033 == _sll_T; // @[Decode.scala 53:24]
  wire  alu_subw = 32'h4000003b == _sll_T; // @[Decode.scala 54:24]
  wire [31:0] _lui_T = io_inst & 32'h7f; // @[Decode.scala 55:24]
  wire  lui = 32'h37 == _lui_T; // @[Decode.scala 55:24]
  wire  alu_auipc = 32'h17 == _lui_T; // @[Decode.scala 56:24]
  wire  xor_ = 32'h4033 == _sll_T; // @[Decode.scala 58:24]
  wire  or_ = 32'h6033 == _sll_T; // @[Decode.scala 59:24]
  wire  and_ = 32'h7033 == _sll_T; // @[Decode.scala 60:24]
  wire  xori = 32'h4013 == _addi_T; // @[Decode.scala 61:24]
  wire  ori = 32'h6013 == _addi_T; // @[Decode.scala 62:24]
  wire  andi = 32'h7013 == _addi_T; // @[Decode.scala 63:24]
  wire  slt = 32'h2033 == _sll_T; // @[Decode.scala 65:24]
  wire  sltu = 32'h3033 == _sll_T; // @[Decode.scala 66:24]
  wire  slti = 32'h2013 == _addi_T; // @[Decode.scala 67:24]
  wire  sltiu = 32'h3013 == _addi_T; // @[Decode.scala 68:24]
  wire  beq = 32'h63 == _addi_T; // @[Decode.scala 70:24]
  wire  bne = 32'h1063 == _addi_T; // @[Decode.scala 71:24]
  wire  blt = 32'h4063 == _addi_T; // @[Decode.scala 72:24]
  wire  bge = 32'h5063 == _addi_T; // @[Decode.scala 73:24]
  wire  bltu = 32'h6063 == _addi_T; // @[Decode.scala 74:24]
  wire  bgeu = 32'h7063 == _addi_T; // @[Decode.scala 75:24]
  wire  jal = 32'h6f == _lui_T; // @[Decode.scala 77:24]
  wire  jalr = 32'h67 == _addi_T; // @[Decode.scala 78:24]
  wire  lb = 32'h3 == _addi_T; // @[Decode.scala 80:24]
  wire  lh = 32'h1003 == _addi_T; // @[Decode.scala 81:24]
  wire  lw = 32'h2003 == _addi_T; // @[Decode.scala 82:24]
  wire  ld = 32'h3003 == _addi_T; // @[Decode.scala 83:24]
  wire  lbu = 32'h4003 == _addi_T; // @[Decode.scala 84:24]
  wire  lhu = 32'h5003 == _addi_T; // @[Decode.scala 85:24]
  wire  lwu = 32'h6003 == _addi_T; // @[Decode.scala 86:24]
  wire  sb = 32'h23 == _addi_T; // @[Decode.scala 88:24]
  wire  sh = 32'h1023 == _addi_T; // @[Decode.scala 89:24]
  wire  sw = 32'h2023 == _addi_T; // @[Decode.scala 90:24]
  wire  sd = 32'h3023 == _addi_T; // @[Decode.scala 91:24]
  wire  alu_add = add | addi | lui; // @[Decode.scala 95:33]
  wire  alu_addw = addw | addiw; // @[Decode.scala 96:26]
  wire  alu_sll = sll | slli; // @[Decode.scala 101:26]
  wire  alu_srl = srl | srli; // @[Decode.scala 102:26]
  wire  alu_sra = sra | srai; // @[Decode.scala 103:26]
  wire  alu_sllw = sllw | slliw; // @[Decode.scala 104:26]
  wire  alu_srlw = srlw | srliw; // @[Decode.scala 105:26]
  wire  alu_sraw = sraw | sraiw; // @[Decode.scala 106:26]
  wire  alu_xor = xor_ | xori; // @[Decode.scala 108:26]
  wire  alu_or = or_ | ori; // @[Decode.scala 109:26]
  wire  alu_and = and_ | andi; // @[Decode.scala 110:26]
  wire  alu_slt = slt | slti; // @[Decode.scala 112:26]
  wire  alu_sltu = sltu | sltiu; // @[Decode.scala 113:26]
  wire [7:0] alu_code_lo = {alu_sra,alu_srl,alu_sll,alu_auipc,alu_subw,alu_sub,alu_addw,alu_add}; // @[Cat.scala 30:58]
  wire [7:0] alu_code_hi = {alu_sltu,alu_slt,alu_and,alu_or,alu_xor,alu_sraw,alu_srlw,alu_sllw}; // @[Cat.scala 30:58]
  wire [15:0] alu_code = {alu_sltu,alu_slt,alu_and,alu_or,alu_xor,alu_sraw,alu_srlw,alu_sllw,alu_code_lo}; // @[Cat.scala 30:58]
  wire  alu_en = alu_code != 16'h0; // @[Decode.scala 116:29]
  wire [3:0] bu_code_lo = {bge,blt,bne,beq}; // @[Cat.scala 30:58]
  wire [3:0] bu_code_hi = {jalr,jal,bgeu,bltu}; // @[Cat.scala 30:58]
  wire [7:0] bu_code = {jalr,jal,bgeu,bltu,bge,blt,bne,beq}; // @[Cat.scala 30:58]
  wire  bu_en = bu_code != 8'h0; // @[Decode.scala 119:27]
  wire [6:0] lu_code = {lwu,lhu,lbu,ld,lw,lh,lb}; // @[Cat.scala 30:58]
  wire  lu_en = lu_code != 7'h0; // @[Decode.scala 122:27]
  wire [3:0] su_code = {sd,sw,sh,sb}; // @[Cat.scala 30:58]
  wire  su_en = su_code != 4'h0; // @[Decode.scala 125:27]
  wire [1:0] fu_code_lo = {bu_en,alu_en}; // @[Cat.scala 30:58]
  wire [1:0] fu_code_hi = {su_en,lu_en}; // @[Cat.scala 30:58]
  wire  _type_r_T_5 = sll | srl | sra | sllw | srlw | sraw | add; // @[Decode.scala 130:70]
  wire  _type_r_T_9 = _type_r_T_5 | addw | alu_sub | alu_subw | xor_; // @[Decode.scala 131:52]
  wire  _type_r_T_12 = _type_r_T_9 | or_ | and_ | slt; // @[Decode.scala 132:43]
  wire  type_r = _type_r_T_12 | sltu | jalr; // @[Decode.scala 133:35]
  wire  _type_i_T_5 = slli | srli | srai | slliw | srliw | sraiw | addi; // @[Decode.scala 135:70]
  wire  _type_i_T_7 = _type_i_T_5 | addiw | xori; // @[Decode.scala 136:35]
  wire  _type_i_T_10 = _type_i_T_7 | ori | andi | slti; // @[Decode.scala 137:43]
  wire  _type_i_T_12 = _type_i_T_10 | sltiu | lb; // @[Decode.scala 138:35]
  wire  type_i = _type_i_T_12 | lh | lw | ld | lbu | lhu | lwu; // @[Decode.scala 139:70]
  wire  type_s = sb | sh | sw | sd; // @[Decode.scala 140:43]
  wire  type_b = beq | bne | blt | bge | bltu | bgeu; // @[Decode.scala 141:61]
  wire  type_u = lui | alu_auipc; // @[Decode.scala 142:26]
  wire [5:0] inst_type = {type_r,type_i,type_s,type_b,type_u,jal}; // @[Cat.scala 30:58]
  wire [51:0] imm_i_hi = io_inst[31] ? 52'hfffffffffffff : 52'h0; // @[Bitwise.scala 72:12]
  wire [11:0] imm_i_lo = io_inst[31:20]; // @[Decode.scala 148:45]
  wire [63:0] imm_i = {imm_i_hi,imm_i_lo}; // @[Cat.scala 30:58]
  wire [6:0] imm_s_hi_lo = io_inst[31:25]; // @[Decode.scala 149:45]
  wire [4:0] imm_s_lo = io_inst[11:7]; // @[Decode.scala 149:59]
  wire [63:0] imm_s = {imm_i_hi,imm_s_hi_lo,imm_s_lo}; // @[Cat.scala 30:58]
  wire [42:0] imm_b_hi_hi_hi = io_inst[31] ? 43'h7ffffffffff : 43'h0; // @[Bitwise.scala 72:12]
  wire  imm_b_hi_lo = io_inst[7]; // @[Decode.scala 150:55]
  wire [5:0] imm_b_lo_hi_hi = io_inst[30:25]; // @[Decode.scala 150:64]
  wire [3:0] imm_b_lo_hi_lo = io_inst[11:8]; // @[Decode.scala 150:78]
  wire [55:0] imm_b = {imm_b_hi_hi_hi,io_inst[31],imm_b_hi_lo,imm_b_lo_hi_hi,imm_b_lo_hi_lo,1'h0}; // @[Cat.scala 30:58]
  wire [31:0] imm_u_hi_hi = io_inst[31] ? 32'hffffffff : 32'h0; // @[Bitwise.scala 72:12]
  wire [19:0] imm_u_hi_lo = io_inst[31:12]; // @[Decode.scala 151:45]
  wire [63:0] imm_u = {imm_u_hi_hi,imm_u_hi_lo,12'h0}; // @[Cat.scala 30:58]
  wire [7:0] imm_j_hi_lo = io_inst[19:12]; // @[Decode.scala 152:55]
  wire  imm_j_lo_hi_hi = io_inst[20]; // @[Decode.scala 152:69]
  wire [9:0] imm_j_lo_hi_lo = io_inst[30:21]; // @[Decode.scala 152:79]
  wire [63:0] imm_j = {imm_b_hi_hi_hi,io_inst[31],imm_j_hi_lo,imm_j_lo_hi_hi,imm_j_lo_hi_lo,1'h0}; // @[Cat.scala 30:58]
  wire [63:0] _imm_T_3 = 6'h10 == inst_type ? imm_i : 64'h0; // @[Mux.scala 80:57]
  wire [63:0] _imm_T_5 = 6'h8 == inst_type ? imm_s : _imm_T_3; // @[Mux.scala 80:57]
  wire [63:0] _imm_T_7 = 6'h4 == inst_type ? {{8'd0}, imm_b} : _imm_T_5; // @[Mux.scala 80:57]
  wire [63:0] _imm_T_9 = 6'h2 == inst_type ? imm_u : _imm_T_7; // @[Mux.scala 80:57]
  wire [63:0] imm = 6'h1 == inst_type ? imm_j : _imm_T_9; // @[Mux.scala 80:57]
  wire  _io_rs1_en_T = type_r | type_i; // @[Decode.scala 173:25]
  assign io_decode_info_fu_code = {fu_code_hi,fu_code_lo}; // @[Cat.scala 30:58]
  assign io_decode_info_alu_code = {alu_code_hi,alu_code_lo}; // @[Cat.scala 30:58]
  assign io_decode_info_bu_code = {bu_code_hi,bu_code_lo}; // @[Cat.scala 30:58]
  assign io_rs1_en = type_r | type_i | type_s | type_b; // @[Decode.scala 173:45]
  assign io_rs2_en = type_r | type_s | type_b; // @[Decode.scala 174:35]
  assign io_rd_en = _io_rs1_en_T | type_u | jal; // @[Decode.scala 175:45]
  assign io_rs1_addr = io_inst[19:15]; // @[Decode.scala 169:24]
  assign io_rs2_addr = io_inst[24:20]; // @[Decode.scala 170:24]
  assign io_rd_addr = io_inst[11:7]; // @[Decode.scala 171:24]
  assign io_op1 = io_rs1_en ? io_rs1_data : 64'h0; // @[Decode.scala 177:18]
  assign io_op2 = io_rs2_en ? io_rs2_data : imm; // @[Decode.scala 178:18]
  assign io_imm = 6'h1 == inst_type ? imm_j : _imm_T_9; // @[Mux.scala 80:57]
endmodule
module Execution(
  input  [3:0]  io_decode_info_fu_code,
  input  [15:0] io_decode_info_alu_code,
  input  [7:0]  io_decode_info_bu_code,
  input  [63:0] io_op1,
  input  [63:0] io_op2,
  input  [63:0] io_pc,
  input  [63:0] io_imm,
  output [63:0] io_out,
  output        io_jump_en,
  output [63:0] io_jump_pc
);
  wire [63:0] _alu_out_T_1 = io_op1 + io_op2; // @[Execution.scala 29:39]
  wire [63:0] _alu_out_T_6 = io_op1 - io_op2; // @[Execution.scala 31:39]
  wire [63:0] _alu_out_T_11 = io_op2 + io_pc; // @[Execution.scala 33:39]
  wire [126:0] _GEN_0 = {{63'd0}, io_op1}; // @[Execution.scala 34:39]
  wire [126:0] _alu_out_T_13 = _GEN_0 << io_op2[5:0]; // @[Execution.scala 34:39]
  wire [63:0] _alu_out_T_15 = io_op1 >> io_op2[5:0]; // @[Execution.scala 35:39]
  wire [63:0] _alu_out_T_16 = io_op1; // @[Execution.scala 36:45]
  wire [63:0] _alu_out_T_19 = $signed(io_op1) >>> io_op2[5:0]; // @[Execution.scala 36:68]
  wire [62:0] _GEN_1 = {{31'd0}, io_op1[31:0]}; // @[Execution.scala 37:46]
  wire [62:0] _alu_out_T_22 = _GEN_1 << io_op2[4:0]; // @[Execution.scala 37:46]
  wire [31:0] _alu_out_T_25 = io_op1[31:0] >> io_op2[4:0]; // @[Execution.scala 38:46]
  wire [31:0] _alu_out_T_29 = _alu_out_T_16[31:0] >> io_op2[4:0]; // @[Execution.scala 39:55]
  wire [63:0] _alu_out_T_30 = io_op1 ^ io_op2; // @[Execution.scala 40:39]
  wire [63:0] _alu_out_T_31 = io_op1 | io_op2; // @[Execution.scala 41:39]
  wire [63:0] _alu_out_T_32 = io_op1 & io_op2; // @[Execution.scala 42:39]
  wire  _alu_out_T_35 = $signed(io_op1) < $signed(io_op2); // @[Execution.scala 43:48]
  wire  _alu_out_T_36 = io_op1 < io_op2; // @[Execution.scala 44:39]
  wire [63:0] _alu_out_T_38 = 16'h1 == io_decode_info_alu_code ? _alu_out_T_1 : 64'h0; // @[Mux.scala 80:57]
  wire [63:0] _alu_out_T_40 = 16'h2 == io_decode_info_alu_code ? {{32'd0}, _alu_out_T_1[31:0]} : _alu_out_T_38; // @[Mux.scala 80:57]
  wire [63:0] _alu_out_T_42 = 16'h4 == io_decode_info_alu_code ? _alu_out_T_6 : _alu_out_T_40; // @[Mux.scala 80:57]
  wire [63:0] _alu_out_T_44 = 16'h8 == io_decode_info_alu_code ? {{32'd0}, _alu_out_T_6[31:0]} : _alu_out_T_42; // @[Mux.scala 80:57]
  wire [63:0] _alu_out_T_46 = 16'h10 == io_decode_info_alu_code ? _alu_out_T_11 : _alu_out_T_44; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_48 = 16'h20 == io_decode_info_alu_code ? _alu_out_T_13 : {{63'd0}, _alu_out_T_46}; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_50 = 16'h40 == io_decode_info_alu_code ? {{63'd0}, _alu_out_T_15} : _alu_out_T_48; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_52 = 16'h80 == io_decode_info_alu_code ? {{63'd0}, _alu_out_T_19} : _alu_out_T_50; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_54 = 16'h100 == io_decode_info_alu_code ? {{64'd0}, _alu_out_T_22} : _alu_out_T_52; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_56 = 16'h200 == io_decode_info_alu_code ? {{95'd0}, _alu_out_T_25} : _alu_out_T_54; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_58 = 16'h400 == io_decode_info_alu_code ? {{95'd0}, _alu_out_T_29} : _alu_out_T_56; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_60 = 16'h800 == io_decode_info_alu_code ? {{63'd0}, _alu_out_T_30} : _alu_out_T_58; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_62 = 16'h1000 == io_decode_info_alu_code ? {{63'd0}, _alu_out_T_31} : _alu_out_T_60; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_64 = 16'h2000 == io_decode_info_alu_code ? {{63'd0}, _alu_out_T_32} : _alu_out_T_62; // @[Mux.scala 80:57]
  wire [126:0] _alu_out_T_66 = 16'h4000 == io_decode_info_alu_code ? {{126'd0}, _alu_out_T_35} : _alu_out_T_64; // @[Mux.scala 80:57]
  wire [126:0] alu_out = 16'h8000 == io_decode_info_alu_code ? {{126'd0}, _alu_out_T_36} : _alu_out_T_66; // @[Mux.scala 80:57]
  wire  _bu_out_T = io_decode_info_bu_code == 8'h80; // @[Execution.scala 47:30]
  wire [63:0] _bu_out_T_4 = io_pc + 64'h4; // @[Execution.scala 47:81]
  wire [63:0] bu_out = io_decode_info_bu_code == 8'h80 | io_decode_info_bu_code == 8'h40 ? _bu_out_T_4 : 64'h0; // @[Execution.scala 47:21]
  wire [63:0] _bu_jump_pc_T_3 = _alu_out_T_1 & 64'hfffffffffffffffe; // @[Execution.scala 48:66]
  wire [63:0] _bu_jump_pc_T_5 = io_pc + io_imm; // @[Execution.scala 48:95]
  wire  _bu_jump_en_T = io_op1 == io_op2; // @[Execution.scala 50:31]
  wire  _bu_jump_en_T_1 = io_op1 != io_op2; // @[Execution.scala 51:31]
  wire  _bu_jump_en_T_7 = $signed(io_op1) >= $signed(io_op2); // @[Execution.scala 53:41]
  wire  _bu_jump_en_T_9 = io_op1 >= io_op2; // @[Execution.scala 55:32]
  wire  _bu_jump_en_T_13 = 8'h2 == io_decode_info_bu_code ? _bu_jump_en_T_1 : 8'h1 == io_decode_info_bu_code &
    _bu_jump_en_T; // @[Mux.scala 80:57]
  wire  _bu_jump_en_T_15 = 8'h4 == io_decode_info_bu_code ? _alu_out_T_35 : _bu_jump_en_T_13; // @[Mux.scala 80:57]
  wire  _bu_jump_en_T_17 = 8'h8 == io_decode_info_bu_code ? _bu_jump_en_T_7 : _bu_jump_en_T_15; // @[Mux.scala 80:57]
  wire  _bu_jump_en_T_19 = 8'h10 == io_decode_info_bu_code ? _alu_out_T_36 : _bu_jump_en_T_17; // @[Mux.scala 80:57]
  wire  _bu_jump_en_T_21 = 8'h20 == io_decode_info_bu_code ? _bu_jump_en_T_9 : _bu_jump_en_T_19; // @[Mux.scala 80:57]
  wire [126:0] _io_out_T_1 = 4'h1 == io_decode_info_fu_code ? alu_out : 127'h0; // @[Mux.scala 80:57]
  wire [126:0] _io_out_T_3 = 4'h2 == io_decode_info_fu_code ? {{63'd0}, bu_out} : _io_out_T_1; // @[Mux.scala 80:57]
  assign io_out = _io_out_T_3[63:0]; // @[Execution.scala 64:12]
  assign io_jump_en = 8'h80 == io_decode_info_bu_code | (8'h40 == io_decode_info_bu_code | _bu_jump_en_T_21); // @[Mux.scala 80:57]
  assign io_jump_pc = _bu_out_T ? _bu_jump_pc_T_3 : _bu_jump_pc_T_5; // @[Execution.scala 48:25]
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
  wire  ifu_io_jump_en; // @[Core.scala 11:19]
  wire [31:0] ifu_io_jump_pc; // @[Core.scala 11:19]
  wire [31:0] idu_io_inst; // @[Core.scala 12:19]
  wire [3:0] idu_io_decode_info_fu_code; // @[Core.scala 12:19]
  wire [15:0] idu_io_decode_info_alu_code; // @[Core.scala 12:19]
  wire [7:0] idu_io_decode_info_bu_code; // @[Core.scala 12:19]
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
  wire [63:0] idu_io_imm; // @[Core.scala 12:19]
  wire [3:0] ieu_io_decode_info_fu_code; // @[Core.scala 13:19]
  wire [15:0] ieu_io_decode_info_alu_code; // @[Core.scala 13:19]
  wire [7:0] ieu_io_decode_info_bu_code; // @[Core.scala 13:19]
  wire [63:0] ieu_io_op1; // @[Core.scala 13:19]
  wire [63:0] ieu_io_op2; // @[Core.scala 13:19]
  wire [63:0] ieu_io_pc; // @[Core.scala 13:19]
  wire [63:0] ieu_io_imm; // @[Core.scala 13:19]
  wire [63:0] ieu_io_out; // @[Core.scala 13:19]
  wire  ieu_io_jump_en; // @[Core.scala 13:19]
  wire [63:0] ieu_io_jump_pc; // @[Core.scala 13:19]
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
  wire  halt_clk; // @[Core.scala 46:20]
  wire  halt_reset; // @[Core.scala 46:20]
  wire  halt_halt; // @[Core.scala 46:20]
  IFetch ifu ( // @[Core.scala 11:19]
    .clock(ifu_clock),
    .reset(ifu_reset),
    .io_imem_addr(ifu_io_imem_addr),
    .io_imem_data(ifu_io_imem_data),
    .io_pc(ifu_io_pc),
    .io_inst(ifu_io_inst),
    .io_jump_en(ifu_io_jump_en),
    .io_jump_pc(ifu_io_jump_pc)
  );
  Decode idu ( // @[Core.scala 12:19]
    .io_inst(idu_io_inst),
    .io_decode_info_fu_code(idu_io_decode_info_fu_code),
    .io_decode_info_alu_code(idu_io_decode_info_alu_code),
    .io_decode_info_bu_code(idu_io_decode_info_bu_code),
    .io_rs1_en(idu_io_rs1_en),
    .io_rs2_en(idu_io_rs2_en),
    .io_rd_en(idu_io_rd_en),
    .io_rs1_addr(idu_io_rs1_addr),
    .io_rs2_addr(idu_io_rs2_addr),
    .io_rd_addr(idu_io_rd_addr),
    .io_rs1_data(idu_io_rs1_data),
    .io_rs2_data(idu_io_rs2_data),
    .io_op1(idu_io_op1),
    .io_op2(idu_io_op2),
    .io_imm(idu_io_imm)
  );
  Execution ieu ( // @[Core.scala 13:19]
    .io_decode_info_fu_code(ieu_io_decode_info_fu_code),
    .io_decode_info_alu_code(ieu_io_decode_info_alu_code),
    .io_decode_info_bu_code(ieu_io_decode_info_bu_code),
    .io_op1(ieu_io_op1),
    .io_op2(ieu_io_op2),
    .io_pc(ieu_io_pc),
    .io_imm(ieu_io_imm),
    .io_out(ieu_io_out),
    .io_jump_en(ieu_io_jump_en),
    .io_jump_pc(ieu_io_jump_pc)
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
  Halt halt ( // @[Core.scala 46:20]
    .clk(halt_clk),
    .reset(halt_reset),
    .halt(halt_halt)
  );
  assign io_imem_addr = ifu_io_imem_addr; // @[Core.scala 20:15]
  assign ifu_clock = clock;
  assign ifu_reset = reset;
  assign ifu_io_imem_data = io_imem_data; // @[Core.scala 20:15]
  assign ifu_io_jump_en = ieu_io_jump_en; // @[Core.scala 21:18]
  assign ifu_io_jump_pc = ieu_io_jump_pc[31:0]; // @[Core.scala 22:18]
  assign idu_io_inst = ifu_io_inst; // @[Core.scala 25:19]
  assign idu_io_rs1_data = rfu_rs1_data; // @[Core.scala 27:19]
  assign idu_io_rs2_data = rfu_rs2_data; // @[Core.scala 28:19]
  assign ieu_io_decode_info_fu_code = idu_io_decode_info_fu_code; // @[Core.scala 26:22]
  assign ieu_io_decode_info_alu_code = idu_io_decode_info_alu_code; // @[Core.scala 26:22]
  assign ieu_io_decode_info_bu_code = idu_io_decode_info_bu_code; // @[Core.scala 26:22]
  assign ieu_io_op1 = idu_io_op1; // @[Core.scala 30:14]
  assign ieu_io_op2 = idu_io_op2; // @[Core.scala 31:14]
  assign ieu_io_pc = ifu_io_pc; // @[Core.scala 32:14]
  assign ieu_io_imm = idu_io_imm; // @[Core.scala 33:14]
  assign rfu_clk = clock; // @[Core.scala 16:17]
  assign rfu_reset = reset; // @[Core.scala 17:17]
  assign rfu_rs1_en = idu_io_rs1_en; // @[Core.scala 35:19]
  assign rfu_rs2_en = idu_io_rs2_en; // @[Core.scala 36:19]
  assign rfu_rd_en = idu_io_rd_en; // @[Core.scala 37:19]
  assign rfu_rs1_addr = idu_io_rs1_addr; // @[Core.scala 38:19]
  assign rfu_rs2_addr = idu_io_rs2_addr; // @[Core.scala 39:19]
  assign rfu_rd_addr = idu_io_rd_addr; // @[Core.scala 40:19]
  assign rfu_rd_data = ieu_io_out; // @[Core.scala 41:19]
  assign halt_clk = clock; // @[Core.scala 47:17]
  assign halt_reset = reset; // @[Core.scala 48:17]
  assign halt_halt = ifu_io_inst == 32'h100073 | ifu_io_inst == 32'h6b; // @[Core.scala 49:43]
  always @(posedge clock) begin
    `ifndef SYNTHESIS
    `ifdef PRINTF_COND
      if (`PRINTF_COND) begin
    `endif
        if (~reset) begin
          $fwrite(32'h80000002,"pc=%x inst=%x wen=%d waddr=%d wdata=%x\n",ifu_io_pc,ifu_io_inst,idu_io_rd_en,
            idu_io_rd_addr,ieu_io_out); // @[Core.scala 44:9]
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
