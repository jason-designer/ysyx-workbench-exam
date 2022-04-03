;buildInfoPackage: chisel3, version: 3.4.3, scalaVersion: 2.12.12, sbtVersion: 1.3.10
circuit SimTop : 
  module IFetch : 
    input clock : Clock
    input reset : Reset
    output io : {imem : {en : UInt<1>, addr : UInt<64>, flip data : UInt<32>}, pc : UInt<64>, inst : UInt<32>, flip jump_en : UInt<1>, flip jump_pc : UInt<32>}
    
    reg pc : UInt<32>, clock with : (reset => (reset, UInt<32>("h080000000"))) @[IFetch.scala 13:19]
    node _pc_T = add(pc, UInt<3>("h04")) @[IFetch.scala 14:40]
    node _pc_T_1 = tail(_pc_T, 1) @[IFetch.scala 14:40]
    node _pc_T_2 = mux(io.jump_en, io.jump_pc, _pc_T_1) @[IFetch.scala 14:12]
    pc <= _pc_T_2 @[IFetch.scala 14:6]
    io.imem.en <= UInt<1>("h01") @[IFetch.scala 17:17]
    io.imem.addr <= pc @[IFetch.scala 18:17]
    io.pc <= pc @[IFetch.scala 19:17]
    io.inst <= io.imem.data @[IFetch.scala 20:17]
    
  module Decode : 
    input clock : Clock
    input reset : Reset
    output io : {flip pc : UInt<64>, flip inst : UInt<32>, decode_info : {fu_code : UInt, alu_code : UInt}, rs1_en : UInt<1>, rs2_en : UInt<1>, rd_en : UInt<1>, rs1_addr : UInt<5>, rs2_addr : UInt<5>, rd_addr : UInt<5>, flip rs1_data : UInt<64>, flip rs2_data : UInt<64>, op1 : UInt<64>, op2 : UInt<64>, op3 : UInt<64>}
    
    node _addi_T = and(io.inst, UInt<15>("h0707f")) @[Decode.scala 32:21]
    node addi = eq(UInt<5>("h013"), _addi_T) @[Decode.scala 32:21]
    node alu_en = neq(addi, UInt<1>("h00")) @[Decode.scala 39:27]
    node inst_type_lo_hi = cat(UInt<1>("h00"), UInt<1>("h00")) @[Cat.scala 30:58]
    node inst_type_lo = cat(inst_type_lo_hi, UInt<1>("h00")) @[Cat.scala 30:58]
    node inst_type_hi_hi = cat(UInt<1>("h00"), addi) @[Cat.scala 30:58]
    node inst_type_hi = cat(inst_type_hi_hi, UInt<1>("h00")) @[Cat.scala 30:58]
    node inst_type = cat(inst_type_hi, inst_type_lo) @[Cat.scala 30:58]
    node _imm_i_T = bits(io.inst, 31, 31) @[Decode.scala 55:34]
    node _imm_i_T_1 = bits(_imm_i_T, 0, 0) @[Bitwise.scala 72:15]
    node imm_i_hi = mux(_imm_i_T_1, UInt<52>("h0fffffffffffff"), UInt<52>("h00")) @[Bitwise.scala 72:12]
    node imm_i_lo = bits(io.inst, 31, 20) @[Decode.scala 55:45]
    node imm_i = cat(imm_i_hi, imm_i_lo) @[Cat.scala 30:58]
    node _imm_s_T = bits(io.inst, 31, 31) @[Decode.scala 56:34]
    node _imm_s_T_1 = bits(_imm_s_T, 0, 0) @[Bitwise.scala 72:15]
    node imm_s_hi_hi = mux(_imm_s_T_1, UInt<52>("h0fffffffffffff"), UInt<52>("h00")) @[Bitwise.scala 72:12]
    node imm_s_hi_lo = bits(io.inst, 31, 25) @[Decode.scala 56:45]
    node imm_s_lo = bits(io.inst, 11, 7) @[Decode.scala 56:59]
    node imm_s_hi = cat(imm_s_hi_hi, imm_s_hi_lo) @[Cat.scala 30:58]
    node imm_s = cat(imm_s_hi, imm_s_lo) @[Cat.scala 30:58]
    node _imm_b_T = bits(io.inst, 31, 31) @[Decode.scala 57:34]
    node _imm_b_T_1 = bits(_imm_b_T, 0, 0) @[Bitwise.scala 72:15]
    node imm_b_hi_hi_hi = mux(_imm_b_T_1, UInt<43>("h07ffffffffff"), UInt<43>("h00")) @[Bitwise.scala 72:12]
    node imm_b_hi_hi_lo = bits(io.inst, 31, 31) @[Decode.scala 57:45]
    node imm_b_hi_lo = bits(io.inst, 7, 7) @[Decode.scala 57:55]
    node imm_b_lo_hi_hi = bits(io.inst, 30, 25) @[Decode.scala 57:64]
    node imm_b_lo_hi_lo = bits(io.inst, 11, 8) @[Decode.scala 57:78]
    node imm_b_lo_hi = cat(imm_b_lo_hi_hi, imm_b_lo_hi_lo) @[Cat.scala 30:58]
    node imm_b_lo = cat(imm_b_lo_hi, UInt<1>("h00")) @[Cat.scala 30:58]
    node imm_b_hi_hi = cat(imm_b_hi_hi_hi, imm_b_hi_hi_lo) @[Cat.scala 30:58]
    node imm_b_hi = cat(imm_b_hi_hi, imm_b_hi_lo) @[Cat.scala 30:58]
    node imm_b = cat(imm_b_hi, imm_b_lo) @[Cat.scala 30:58]
    node _imm_u_T = bits(io.inst, 31, 31) @[Decode.scala 58:34]
    node _imm_u_T_1 = bits(_imm_u_T, 0, 0) @[Bitwise.scala 72:15]
    node imm_u_hi_hi = mux(_imm_u_T_1, UInt<32>("h0ffffffff"), UInt<32>("h00")) @[Bitwise.scala 72:12]
    node imm_u_hi_lo = bits(io.inst, 31, 12) @[Decode.scala 58:45]
    node imm_u_lo = mux(UInt<1>("h00"), UInt<12>("h0fff"), UInt<12>("h00")) @[Bitwise.scala 72:12]
    node imm_u_hi = cat(imm_u_hi_hi, imm_u_hi_lo) @[Cat.scala 30:58]
    node imm_u = cat(imm_u_hi, imm_u_lo) @[Cat.scala 30:58]
    node _imm_j_T = bits(io.inst, 31, 31) @[Decode.scala 59:34]
    node _imm_j_T_1 = bits(_imm_j_T, 0, 0) @[Bitwise.scala 72:15]
    node imm_j_hi_hi_hi = mux(_imm_j_T_1, UInt<43>("h07ffffffffff"), UInt<43>("h00")) @[Bitwise.scala 72:12]
    node imm_j_hi_hi_lo = bits(io.inst, 31, 31) @[Decode.scala 59:45]
    node imm_j_hi_lo = bits(io.inst, 19, 12) @[Decode.scala 59:55]
    node imm_j_lo_hi_hi = bits(io.inst, 20, 20) @[Decode.scala 59:69]
    node imm_j_lo_hi_lo = bits(io.inst, 30, 21) @[Decode.scala 59:79]
    node imm_j_lo_hi = cat(imm_j_lo_hi_hi, imm_j_lo_hi_lo) @[Cat.scala 30:58]
    node imm_j_lo = cat(imm_j_lo_hi, UInt<1>("h00")) @[Cat.scala 30:58]
    node imm_j_hi_hi = cat(imm_j_hi_hi_hi, imm_j_hi_hi_lo) @[Cat.scala 30:58]
    node imm_j_hi = cat(imm_j_hi_hi, imm_j_hi_lo) @[Cat.scala 30:58]
    node imm_j = cat(imm_j_hi, imm_j_lo) @[Cat.scala 30:58]
    node _imm_T = eq(UInt<6>("h020"), inst_type) @[Mux.scala 80:60]
    node _imm_T_1 = mux(_imm_T, UInt<1>("h00"), UInt<1>("h00")) @[Mux.scala 80:57]
    node _imm_T_2 = eq(UInt<5>("h010"), inst_type) @[Mux.scala 80:60]
    node _imm_T_3 = mux(_imm_T_2, imm_i, _imm_T_1) @[Mux.scala 80:57]
    node _imm_T_4 = eq(UInt<4>("h08"), inst_type) @[Mux.scala 80:60]
    node _imm_T_5 = mux(_imm_T_4, imm_s, _imm_T_3) @[Mux.scala 80:57]
    node _imm_T_6 = eq(UInt<3>("h04"), inst_type) @[Mux.scala 80:60]
    node _imm_T_7 = mux(_imm_T_6, imm_b, _imm_T_5) @[Mux.scala 80:57]
    node _imm_T_8 = eq(UInt<2>("h02"), inst_type) @[Mux.scala 80:60]
    node _imm_T_9 = mux(_imm_T_8, imm_u, _imm_T_7) @[Mux.scala 80:57]
    node _imm_T_10 = eq(UInt<1>("h01"), inst_type) @[Mux.scala 80:60]
    node imm = mux(_imm_T_10, imm_j, _imm_T_9) @[Mux.scala 80:57]
    io.decode_info.fu_code <= alu_en @[Decode.scala 71:29]
    io.decode_info.alu_code <= addi @[Decode.scala 72:29]
    node _io_rs1_addr_T = bits(io.inst, 19, 15) @[Decode.scala 74:24]
    io.rs1_addr <= _io_rs1_addr_T @[Decode.scala 74:17]
    node _io_rs2_addr_T = bits(io.inst, 24, 20) @[Decode.scala 75:24]
    io.rs2_addr <= _io_rs2_addr_T @[Decode.scala 75:17]
    node _io_rd_addr_T = bits(io.inst, 11, 7) @[Decode.scala 76:24]
    io.rd_addr <= _io_rd_addr_T @[Decode.scala 76:17]
    node _io_rs1_en_T = or(UInt<1>("h00"), addi) @[Decode.scala 78:25]
    node _io_rs1_en_T_1 = or(_io_rs1_en_T, UInt<1>("h00")) @[Decode.scala 78:35]
    node _io_rs1_en_T_2 = or(_io_rs1_en_T_1, UInt<1>("h00")) @[Decode.scala 78:45]
    io.rs1_en <= _io_rs1_en_T_2 @[Decode.scala 78:15]
    node _io_rs2_en_T = or(UInt<1>("h00"), UInt<1>("h00")) @[Decode.scala 79:25]
    node _io_rs2_en_T_1 = or(_io_rs2_en_T, UInt<1>("h00")) @[Decode.scala 79:35]
    io.rs2_en <= _io_rs2_en_T_1 @[Decode.scala 79:15]
    node _io_rd_en_T = or(UInt<1>("h00"), addi) @[Decode.scala 80:25]
    node _io_rd_en_T_1 = or(_io_rd_en_T, UInt<1>("h00")) @[Decode.scala 80:35]
    node _io_rd_en_T_2 = or(_io_rd_en_T_1, UInt<1>("h00")) @[Decode.scala 80:45]
    io.rd_en <= _io_rd_en_T_2 @[Decode.scala 80:15]
    node _io_op1_T = mux(io.rs1_en, io.rs1_data, UInt<1>("h00")) @[Decode.scala 83:18]
    io.op1 <= _io_op1_T @[Decode.scala 83:12]
    node _io_op2_T = mux(io.rs2_en, io.rs2_data, imm) @[Decode.scala 84:18]
    io.op2 <= _io_op2_T @[Decode.scala 84:12]
    io.op3 <= UInt<1>("h00") @[Decode.scala 85:12]
    
  module Execution : 
    input clock : Clock
    input reset : Reset
    output io : {flip decode_info : {fu_code : UInt, alu_code : UInt}, flip op1 : UInt<64>, flip op2 : UInt<64>, flip op3 : UInt<64>, out : UInt<64>, jump_en : UInt<1>, jump_pc : UInt<64>}
    
    node _alu_out_T = add(io.op1, io.op2) @[Execution.scala 24:29]
    node _alu_out_T_1 = tail(_alu_out_T, 1) @[Execution.scala 24:29]
    node _alu_out_T_2 = eq(UInt<1>("h01"), io.decode_info.alu_code) @[Mux.scala 80:60]
    node alu_out = mux(_alu_out_T_2, _alu_out_T_1, UInt<1>("h00")) @[Mux.scala 80:57]
    node _io_out_T = eq(UInt<1>("h01"), io.decode_info.fu_code) @[Mux.scala 80:60]
    node _io_out_T_1 = mux(_io_out_T, alu_out, UInt<1>("h00")) @[Mux.scala 80:57]
    io.out <= _io_out_T_1 @[Execution.scala 29:12]
    io.jump_en <= UInt<1>("h00") @[Execution.scala 32:16]
    io.jump_pc <= UInt<1>("h00") @[Execution.scala 33:16]
    
  extmodule RegFile : 
    input clk : Clock
    input reset : Reset
    input rs1_en : UInt<1>
    input rs2_en : UInt<1>
    input rd_en : UInt<1>
    input rs1_addr : UInt<5>
    input rs2_addr : UInt<5>
    input rd_addr : UInt<5>
    output rs1_data : UInt<64>
    output rs2_data : UInt<64>
    input rd_data : UInt<64>
    
    defname = RegFile
    
    
  extmodule Halt : 
    input clk : Clock
    input reset : Reset
    input halt : UInt<1>
    
    defname = Halt
    
    
  module Core : 
    input clock : Clock
    input reset : Reset
    output io : {imem : {en : UInt<1>, addr : UInt<64>, flip data : UInt<32>}}
    
    inst ifu of IFetch @[Core.scala 11:19]
    ifu.clock <= clock
    ifu.reset <= reset
    inst idu of Decode @[Core.scala 12:19]
    idu.clock <= clock
    idu.reset <= reset
    inst ieu of Execution @[Core.scala 13:19]
    ieu.clock <= clock
    ieu.reset <= reset
    inst rfu of RegFile @[Core.scala 14:19]
    rfu.rd_data is invalid
    rfu.rs2_data is invalid
    rfu.rs1_data is invalid
    rfu.rd_addr is invalid
    rfu.rs2_addr is invalid
    rfu.rs1_addr is invalid
    rfu.rd_en is invalid
    rfu.rs2_en is invalid
    rfu.rs1_en is invalid
    rfu.reset is invalid
    rfu.clk is invalid
    rfu.clk <= clock @[Core.scala 16:17]
    rfu.reset <= reset @[Core.scala 17:17]
    ifu.io.imem.data <= io.imem.data @[Core.scala 20:15]
    io.imem.addr <= ifu.io.imem.addr @[Core.scala 20:15]
    io.imem.en <= ifu.io.imem.en @[Core.scala 20:15]
    ifu.io.jump_en <= ieu.io.jump_en @[Core.scala 21:18]
    ifu.io.jump_pc <= ieu.io.jump_pc @[Core.scala 22:18]
    idu.io.pc <= ifu.io.pc @[Core.scala 24:19]
    idu.io.inst <= ifu.io.inst @[Core.scala 25:19]
    ieu.io.decode_info.alu_code <= idu.io.decode_info.alu_code @[Core.scala 26:22]
    ieu.io.decode_info.fu_code <= idu.io.decode_info.fu_code @[Core.scala 26:22]
    idu.io.rs1_data <= rfu.rs1_data @[Core.scala 27:19]
    idu.io.rs2_data <= rfu.rs2_data @[Core.scala 28:19]
    ieu.io.op1 <= idu.io.op1 @[Core.scala 30:14]
    ieu.io.op2 <= idu.io.op2 @[Core.scala 31:14]
    ieu.io.op3 <= idu.io.op3 @[Core.scala 32:14]
    rfu.rs1_en <= idu.io.rs1_en @[Core.scala 34:19]
    rfu.rs2_en <= idu.io.rs2_en @[Core.scala 35:19]
    rfu.rd_en <= idu.io.rd_en @[Core.scala 36:19]
    rfu.rs1_addr <= idu.io.rs1_addr @[Core.scala 37:19]
    rfu.rs2_addr <= idu.io.rs2_addr @[Core.scala 38:19]
    rfu.rd_addr <= idu.io.rd_addr @[Core.scala 39:19]
    rfu.rd_data <= ieu.io.out @[Core.scala 40:19]
    node _T = asUInt(reset) @[Core.scala 43:9]
    node _T_1 = eq(_T, UInt<1>("h00")) @[Core.scala 43:9]
    when _T_1 : @[Core.scala 43:9]
      printf(clock, UInt<1>(1), "pc=%x inst=%x wen=%d waddr=%d wdata=%x\n", ifu.io.pc, ifu.io.inst, idu.io.rd_en, idu.io.rd_addr, ieu.io.out) @[Core.scala 43:9]
      skip @[Core.scala 43:9]
    inst halt of Halt @[Core.scala 45:20]
    halt.halt is invalid
    halt.reset is invalid
    halt.clk is invalid
    halt.clk <= clock @[Core.scala 46:17]
    halt.reset <= reset @[Core.scala 47:17]
    node _halt_io_halt_T = eq(ifu.io.inst, UInt<21>("h0100073")) @[Core.scala 48:32]
    halt.halt <= _halt_io_halt_T @[Core.scala 48:17]
    
  module SimTop : 
    input clock : Clock
    input reset : UInt<1>
    output io : {imem : {en : UInt<1>, addr : UInt<64>, flip data : UInt<32>}}
    
    inst core of Core @[SimTop.scala 27:20]
    core.clock <= clock
    core.reset <= reset
    core.io.imem.data <= io.imem.data @[SimTop.scala 28:11]
    io.imem.addr <= core.io.imem.addr @[SimTop.scala 28:11]
    io.imem.en <= core.io.imem.en @[SimTop.scala 28:11]
    
