// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VSimTop__Syms.h"


void VSimTop___024root__traceInitSub0(VSimTop___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void VSimTop___024root__traceInitTop(VSimTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        VSimTop___024root__traceInitSub0(vlSelf, tracep);
    }
}

void VSimTop___024root__traceInitSub0(VSimTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+106,"clock", false,-1);
        tracep->declBit(c+107,"reset", false,-1);
        tracep->declBit(c+108,"io_imem_en", false,-1);
        tracep->declQuad(c+109,"io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+111,"io_imem_data", false,-1, 31,0);
        tracep->declBit(c+106,"SimTop clock", false,-1);
        tracep->declBit(c+107,"SimTop reset", false,-1);
        tracep->declBit(c+108,"SimTop io_imem_en", false,-1);
        tracep->declQuad(c+109,"SimTop io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop io_imem_data", false,-1, 31,0);
        tracep->declBit(c+106,"SimTop core_clock", false,-1);
        tracep->declBit(c+107,"SimTop core_reset", false,-1);
        tracep->declQuad(c+1,"SimTop core_io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core_io_imem_data", false,-1, 31,0);
        tracep->declBit(c+106,"SimTop core clock", false,-1);
        tracep->declBit(c+107,"SimTop core reset", false,-1);
        tracep->declQuad(c+1,"SimTop core io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core io_imem_data", false,-1, 31,0);
        tracep->declBit(c+106,"SimTop core ifu_clock", false,-1);
        tracep->declBit(c+107,"SimTop core ifu_reset", false,-1);
        tracep->declQuad(c+1,"SimTop core ifu_io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core ifu_io_imem_data", false,-1, 31,0);
        tracep->declQuad(c+1,"SimTop core ifu_io_pc", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core ifu_io_inst", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop core ifu_io_jump_en", false,-1);
        tracep->declBus(c+112,"SimTop core ifu_io_jump_pc", false,-1, 31,0);
        tracep->declBus(c+111,"SimTop core idu_io_inst", false,-1, 31,0);
        tracep->declBus(c+71,"SimTop core idu_io_decode_info_fu_code", false,-1, 3,0);
        tracep->declBus(c+72,"SimTop core idu_io_decode_info_alu_code", false,-1, 15,0);
        tracep->declBus(c+73,"SimTop core idu_io_decode_info_bu_code", false,-1, 7,0);
        tracep->declBit(c+74,"SimTop core idu_io_rs1_en", false,-1);
        tracep->declBit(c+75,"SimTop core idu_io_rs2_en", false,-1);
        tracep->declBit(c+113,"SimTop core idu_io_rd_en", false,-1);
        tracep->declBus(c+114,"SimTop core idu_io_rs1_addr", false,-1, 4,0);
        tracep->declBus(c+115,"SimTop core idu_io_rs2_addr", false,-1, 4,0);
        tracep->declBus(c+116,"SimTop core idu_io_rd_addr", false,-1, 4,0);
        tracep->declQuad(c+117,"SimTop core idu_io_rs1_data", false,-1, 63,0);
        tracep->declQuad(c+119,"SimTop core idu_io_rs2_data", false,-1, 63,0);
        tracep->declQuad(c+76,"SimTop core idu_io_op1", false,-1, 63,0);
        tracep->declQuad(c+78,"SimTop core idu_io_op2", false,-1, 63,0);
        tracep->declQuad(c+80,"SimTop core idu_io_imm", false,-1, 63,0);
        tracep->declBus(c+71,"SimTop core ieu_io_decode_info_fu_code", false,-1, 3,0);
        tracep->declBus(c+72,"SimTop core ieu_io_decode_info_alu_code", false,-1, 15,0);
        tracep->declBus(c+73,"SimTop core ieu_io_decode_info_bu_code", false,-1, 7,0);
        tracep->declQuad(c+76,"SimTop core ieu_io_op1", false,-1, 63,0);
        tracep->declQuad(c+78,"SimTop core ieu_io_op2", false,-1, 63,0);
        tracep->declQuad(c+1,"SimTop core ieu_io_pc", false,-1, 63,0);
        tracep->declQuad(c+80,"SimTop core ieu_io_imm", false,-1, 63,0);
        tracep->declQuad(c+121,"SimTop core ieu_io_out", false,-1, 63,0);
        tracep->declBit(c+70,"SimTop core ieu_io_jump_en", false,-1);
        tracep->declQuad(c+123,"SimTop core ieu_io_jump_pc", false,-1, 63,0);
        tracep->declBit(c+106,"SimTop core rfu_clk", false,-1);
        tracep->declBit(c+107,"SimTop core rfu_reset", false,-1);
        tracep->declBit(c+74,"SimTop core rfu_rs1_en", false,-1);
        tracep->declBit(c+75,"SimTop core rfu_rs2_en", false,-1);
        tracep->declBit(c+113,"SimTop core rfu_rd_en", false,-1);
        tracep->declBus(c+114,"SimTop core rfu_rs1_addr", false,-1, 4,0);
        tracep->declBus(c+115,"SimTop core rfu_rs2_addr", false,-1, 4,0);
        tracep->declBus(c+116,"SimTop core rfu_rd_addr", false,-1, 4,0);
        tracep->declQuad(c+117,"SimTop core rfu_rs1_data", false,-1, 63,0);
        tracep->declQuad(c+119,"SimTop core rfu_rs2_data", false,-1, 63,0);
        tracep->declQuad(c+121,"SimTop core rfu_rd_data", false,-1, 63,0);
        tracep->declBit(c+106,"SimTop core halt_clk", false,-1);
        tracep->declBit(c+107,"SimTop core halt_reset", false,-1);
        tracep->declBit(c+125,"SimTop core halt_halt", false,-1);
        tracep->declBit(c+106,"SimTop core ifu clock", false,-1);
        tracep->declBit(c+107,"SimTop core ifu reset", false,-1);
        tracep->declQuad(c+1,"SimTop core ifu io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core ifu io_imem_data", false,-1, 31,0);
        tracep->declQuad(c+1,"SimTop core ifu io_pc", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core ifu io_inst", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop core ifu io_jump_en", false,-1);
        tracep->declBus(c+112,"SimTop core ifu io_jump_pc", false,-1, 31,0);
        tracep->declBus(c+3,"SimTop core ifu pc", false,-1, 31,0);
        tracep->declBus(c+111,"SimTop core idu io_inst", false,-1, 31,0);
        tracep->declBus(c+71,"SimTop core idu io_decode_info_fu_code", false,-1, 3,0);
        tracep->declBus(c+72,"SimTop core idu io_decode_info_alu_code", false,-1, 15,0);
        tracep->declBus(c+73,"SimTop core idu io_decode_info_bu_code", false,-1, 7,0);
        tracep->declBit(c+74,"SimTop core idu io_rs1_en", false,-1);
        tracep->declBit(c+75,"SimTop core idu io_rs2_en", false,-1);
        tracep->declBit(c+113,"SimTop core idu io_rd_en", false,-1);
        tracep->declBus(c+114,"SimTop core idu io_rs1_addr", false,-1, 4,0);
        tracep->declBus(c+115,"SimTop core idu io_rs2_addr", false,-1, 4,0);
        tracep->declBus(c+116,"SimTop core idu io_rd_addr", false,-1, 4,0);
        tracep->declQuad(c+117,"SimTop core idu io_rs1_data", false,-1, 63,0);
        tracep->declQuad(c+119,"SimTop core idu io_rs2_data", false,-1, 63,0);
        tracep->declQuad(c+76,"SimTop core idu io_op1", false,-1, 63,0);
        tracep->declQuad(c+78,"SimTop core idu io_op2", false,-1, 63,0);
        tracep->declQuad(c+80,"SimTop core idu io_imm", false,-1, 63,0);
        tracep->declBit(c+126,"SimTop core idu sll", false,-1);
        tracep->declBit(c+127,"SimTop core idu srl", false,-1);
        tracep->declBit(c+128,"SimTop core idu sra", false,-1);
        tracep->declBit(c+129,"SimTop core idu slli", false,-1);
        tracep->declBit(c+130,"SimTop core idu srli", false,-1);
        tracep->declBit(c+131,"SimTop core idu srai", false,-1);
        tracep->declBit(c+132,"SimTop core idu sllw", false,-1);
        tracep->declBit(c+133,"SimTop core idu srlw", false,-1);
        tracep->declBit(c+134,"SimTop core idu sraw", false,-1);
        tracep->declBit(c+135,"SimTop core idu slliw", false,-1);
        tracep->declBit(c+136,"SimTop core idu srliw", false,-1);
        tracep->declBit(c+137,"SimTop core idu sraiw", false,-1);
        tracep->declBit(c+138,"SimTop core idu add", false,-1);
        tracep->declBit(c+139,"SimTop core idu addw", false,-1);
        tracep->declBit(c+140,"SimTop core idu addi", false,-1);
        tracep->declBit(c+141,"SimTop core idu addiw", false,-1);
        tracep->declBit(c+142,"SimTop core idu alu_sub", false,-1);
        tracep->declBit(c+143,"SimTop core idu alu_subw", false,-1);
        tracep->declBit(c+144,"SimTop core idu lui", false,-1);
        tracep->declBit(c+145,"SimTop core idu alu_auipc", false,-1);
        tracep->declBit(c+146,"SimTop core idu xor_", false,-1);
        tracep->declBit(c+147,"SimTop core idu or_", false,-1);
        tracep->declBit(c+148,"SimTop core idu and_", false,-1);
        tracep->declBit(c+149,"SimTop core idu xori", false,-1);
        tracep->declBit(c+150,"SimTop core idu ori", false,-1);
        tracep->declBit(c+151,"SimTop core idu andi", false,-1);
        tracep->declBit(c+152,"SimTop core idu slt", false,-1);
        tracep->declBit(c+153,"SimTop core idu sltu", false,-1);
        tracep->declBit(c+154,"SimTop core idu slti", false,-1);
        tracep->declBit(c+155,"SimTop core idu sltiu", false,-1);
        tracep->declBit(c+156,"SimTop core idu beq", false,-1);
        tracep->declBit(c+157,"SimTop core idu bne", false,-1);
        tracep->declBit(c+158,"SimTop core idu blt", false,-1);
        tracep->declBit(c+159,"SimTop core idu bge", false,-1);
        tracep->declBit(c+160,"SimTop core idu bltu", false,-1);
        tracep->declBit(c+161,"SimTop core idu bgeu", false,-1);
        tracep->declBit(c+162,"SimTop core idu jal", false,-1);
        tracep->declBit(c+163,"SimTop core idu jalr", false,-1);
        tracep->declBit(c+164,"SimTop core idu lb", false,-1);
        tracep->declBit(c+165,"SimTop core idu lh", false,-1);
        tracep->declBit(c+166,"SimTop core idu lw", false,-1);
        tracep->declBit(c+167,"SimTop core idu ld", false,-1);
        tracep->declBit(c+168,"SimTop core idu lbu", false,-1);
        tracep->declBit(c+169,"SimTop core idu lhu", false,-1);
        tracep->declBit(c+170,"SimTop core idu lwu", false,-1);
        tracep->declBit(c+171,"SimTop core idu sb", false,-1);
        tracep->declBit(c+172,"SimTop core idu sh", false,-1);
        tracep->declBit(c+173,"SimTop core idu sw", false,-1);
        tracep->declBit(c+174,"SimTop core idu sd", false,-1);
        tracep->declBit(c+175,"SimTop core idu alu_add", false,-1);
        tracep->declBit(c+176,"SimTop core idu alu_addw", false,-1);
        tracep->declBit(c+177,"SimTop core idu alu_sll", false,-1);
        tracep->declBit(c+178,"SimTop core idu alu_srl", false,-1);
        tracep->declBit(c+179,"SimTop core idu alu_sra", false,-1);
        tracep->declBit(c+82,"SimTop core idu alu_sllw", false,-1);
        tracep->declBit(c+83,"SimTop core idu alu_srlw", false,-1);
        tracep->declBit(c+84,"SimTop core idu alu_sraw", false,-1);
        tracep->declBit(c+85,"SimTop core idu alu_xor", false,-1);
        tracep->declBit(c+86,"SimTop core idu alu_or", false,-1);
        tracep->declBit(c+87,"SimTop core idu alu_and", false,-1);
        tracep->declBit(c+88,"SimTop core idu alu_slt", false,-1);
        tracep->declBit(c+89,"SimTop core idu alu_sltu", false,-1);
        tracep->declBus(c+90,"SimTop core idu alu_code_lo", false,-1, 7,0);
        tracep->declBus(c+91,"SimTop core idu alu_code_hi", false,-1, 7,0);
        tracep->declBus(c+92,"SimTop core idu alu_code", false,-1, 15,0);
        tracep->declBit(c+93,"SimTop core idu alu_en", false,-1);
        tracep->declBus(c+180,"SimTop core idu bu_code_lo", false,-1, 3,0);
        tracep->declBus(c+181,"SimTop core idu bu_code_hi", false,-1, 3,0);
        tracep->declBus(c+182,"SimTop core idu bu_code", false,-1, 7,0);
        tracep->declBit(c+183,"SimTop core idu bu_en", false,-1);
        tracep->declBus(c+184,"SimTop core idu lu_code", false,-1, 6,0);
        tracep->declBit(c+185,"SimTop core idu lu_en", false,-1);
        tracep->declBus(c+186,"SimTop core idu su_code", false,-1, 3,0);
        tracep->declBit(c+187,"SimTop core idu su_en", false,-1);
        tracep->declBus(c+188,"SimTop core idu fu_code_lo", false,-1, 1,0);
        tracep->declBus(c+189,"SimTop core idu fu_code_hi", false,-1, 1,0);
        tracep->declBit(c+94,"SimTop core idu type_r", false,-1);
        tracep->declBit(c+95,"SimTop core idu type_i", false,-1);
        tracep->declBit(c+96,"SimTop core idu type_s", false,-1);
        tracep->declBit(c+97,"SimTop core idu type_b", false,-1);
        tracep->declBit(c+98,"SimTop core idu type_u", false,-1);
        tracep->declBus(c+99,"SimTop core idu inst_type", false,-1, 5,0);
        tracep->declQuad(c+190,"SimTop core idu imm_i_hi", false,-1, 51,0);
        tracep->declBus(c+192,"SimTop core idu imm_i_lo", false,-1, 11,0);
        tracep->declQuad(c+193,"SimTop core idu imm_i", false,-1, 63,0);
        tracep->declBus(c+195,"SimTop core idu imm_s_hi_lo", false,-1, 6,0);
        tracep->declBus(c+116,"SimTop core idu imm_s_lo", false,-1, 4,0);
        tracep->declQuad(c+196,"SimTop core idu imm_s", false,-1, 63,0);
        tracep->declQuad(c+198,"SimTop core idu imm_b_hi_hi_hi", false,-1, 42,0);
        tracep->declBit(c+200,"SimTop core idu imm_b_hi_lo", false,-1);
        tracep->declBus(c+201,"SimTop core idu imm_b_lo_hi_hi", false,-1, 5,0);
        tracep->declBus(c+202,"SimTop core idu imm_b_lo_hi_lo", false,-1, 3,0);
        tracep->declQuad(c+203,"SimTop core idu imm_b", false,-1, 55,0);
        tracep->declBus(c+205,"SimTop core idu imm_u_hi_hi", false,-1, 31,0);
        tracep->declBus(c+206,"SimTop core idu imm_u_hi_lo", false,-1, 19,0);
        tracep->declQuad(c+207,"SimTop core idu imm_u", false,-1, 63,0);
        tracep->declBus(c+209,"SimTop core idu imm_j_hi_lo", false,-1, 7,0);
        tracep->declBit(c+210,"SimTop core idu imm_j_lo_hi_hi", false,-1);
        tracep->declBus(c+211,"SimTop core idu imm_j_lo_hi_lo", false,-1, 9,0);
        tracep->declQuad(c+100,"SimTop core idu imm_j", false,-1, 63,0);
        tracep->declQuad(c+80,"SimTop core idu imm", false,-1, 63,0);
        tracep->declBus(c+71,"SimTop core ieu io_decode_info_fu_code", false,-1, 3,0);
        tracep->declBus(c+72,"SimTop core ieu io_decode_info_alu_code", false,-1, 15,0);
        tracep->declBus(c+73,"SimTop core ieu io_decode_info_bu_code", false,-1, 7,0);
        tracep->declQuad(c+76,"SimTop core ieu io_op1", false,-1, 63,0);
        tracep->declQuad(c+78,"SimTop core ieu io_op2", false,-1, 63,0);
        tracep->declQuad(c+1,"SimTop core ieu io_pc", false,-1, 63,0);
        tracep->declQuad(c+80,"SimTop core ieu io_imm", false,-1, 63,0);
        tracep->declQuad(c+121,"SimTop core ieu io_out", false,-1, 63,0);
        tracep->declBit(c+70,"SimTop core ieu io_jump_en", false,-1);
        tracep->declQuad(c+123,"SimTop core ieu io_jump_pc", false,-1, 63,0);
        tracep->declArray(c+102,"SimTop core ieu alu_out", false,-1, 126,0);
        tracep->declQuad(c+212,"SimTop core ieu bu_out", false,-1, 63,0);
        tracep->declBit(c+106,"SimTop core rfu clk", false,-1);
        tracep->declBit(c+107,"SimTop core rfu reset", false,-1);
        tracep->declBit(c+74,"SimTop core rfu rs1_en", false,-1);
        tracep->declBit(c+75,"SimTop core rfu rs2_en", false,-1);
        tracep->declBit(c+113,"SimTop core rfu rd_en", false,-1);
        tracep->declQuad(c+214,"SimTop core rfu rs1_addr", false,-1, 63,0);
        tracep->declQuad(c+216,"SimTop core rfu rs2_addr", false,-1, 63,0);
        tracep->declQuad(c+218,"SimTop core rfu rd_addr", false,-1, 63,0);
        tracep->declQuad(c+117,"SimTop core rfu rs1_data", false,-1, 63,0);
        tracep->declQuad(c+119,"SimTop core rfu rs2_data", false,-1, 63,0);
        tracep->declQuad(c+121,"SimTop core rfu rd_data", false,-1, 63,0);
        {int i; for (i=0; i<32; i++) {
                tracep->declQuad(c+4+i*2,"SimTop core rfu rf", true,(i+0), 63,0);}}
        tracep->declBus(c+68,"SimTop core rfu unnamedblk1 i", false,-1, 31,0);
        tracep->declBit(c+106,"SimTop core halt clk", false,-1);
        tracep->declBit(c+107,"SimTop core halt reset", false,-1);
        tracep->declBit(c+125,"SimTop core halt halt", false,-1);
        {int i; for (i=0; i<1; i++) {
                tracep->declBit(c+69+i*1,"SimTop core halt halt_reg", true,(i+0));}}
    }
}

void VSimTop___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void VSimTop___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void VSimTop___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void VSimTop___024root__traceRegister(VSimTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&VSimTop___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&VSimTop___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&VSimTop___024root__traceCleanup, vlSelf);
    }
}

void VSimTop___024root__traceFullSub0(VSimTop___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void VSimTop___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    VSimTop___024root* const __restrict vlSelf = static_cast<VSimTop___024root*>(voidSelf);
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        VSimTop___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void VSimTop___024root__traceFullSub0(VSimTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlWide<4>/*127:0*/ __Vtemp87;
    VlWide<4>/*127:0*/ __Vtemp88;
    VlWide<4>/*127:0*/ __Vtemp89;
    VlWide<4>/*127:0*/ __Vtemp90;
    VlWide<4>/*127:0*/ __Vtemp91;
    VlWide<4>/*127:0*/ __Vtemp101;
    VlWide<4>/*127:0*/ __Vtemp102;
    VlWide<4>/*127:0*/ __Vtemp103;
    VlWide<4>/*127:0*/ __Vtemp104;
    VlWide<4>/*127:0*/ __Vtemp105;
    VlWide<4>/*127:0*/ __Vtemp106;
    VlWide<4>/*127:0*/ __Vtemp107;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullQData(oldp+1,((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc))),64);
        tracep->fullIData(oldp+3,(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc),32);
        tracep->fullQData(oldp+4,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0]),64);
        tracep->fullQData(oldp+6,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[1]),64);
        tracep->fullQData(oldp+8,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[2]),64);
        tracep->fullQData(oldp+10,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[3]),64);
        tracep->fullQData(oldp+12,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[4]),64);
        tracep->fullQData(oldp+14,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[5]),64);
        tracep->fullQData(oldp+16,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[6]),64);
        tracep->fullQData(oldp+18,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[7]),64);
        tracep->fullQData(oldp+20,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[8]),64);
        tracep->fullQData(oldp+22,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[9]),64);
        tracep->fullQData(oldp+24,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[10]),64);
        tracep->fullQData(oldp+26,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[11]),64);
        tracep->fullQData(oldp+28,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[12]),64);
        tracep->fullQData(oldp+30,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[13]),64);
        tracep->fullQData(oldp+32,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[14]),64);
        tracep->fullQData(oldp+34,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[15]),64);
        tracep->fullQData(oldp+36,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[16]),64);
        tracep->fullQData(oldp+38,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[17]),64);
        tracep->fullQData(oldp+40,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[18]),64);
        tracep->fullQData(oldp+42,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[19]),64);
        tracep->fullQData(oldp+44,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[20]),64);
        tracep->fullQData(oldp+46,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[21]),64);
        tracep->fullQData(oldp+48,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[22]),64);
        tracep->fullQData(oldp+50,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[23]),64);
        tracep->fullQData(oldp+52,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[24]),64);
        tracep->fullQData(oldp+54,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[25]),64);
        tracep->fullQData(oldp+56,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[26]),64);
        tracep->fullQData(oldp+58,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[27]),64);
        tracep->fullQData(oldp+60,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[28]),64);
        tracep->fullQData(oldp+62,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[29]),64);
        tracep->fullQData(oldp+64,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[30]),64);
        tracep->fullQData(oldp+66,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[31]),64);
        tracep->fullIData(oldp+68,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i),32);
        tracep->fullBit(oldp+69,(vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg[0]));
        tracep->fullBit(oldp+70,(((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                  | ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                     | ((0x20U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                         ? (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                            >= vlSelf->SimTop__DOT__core__DOT__idu_io_op2)
                                         : ((0x10U 
                                             == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                             ? (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36)
                                             : ((8U 
                                                 == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                 ? 
                                                VL_GTES_IQQ(1,64,64, vlSelf->SimTop__DOT__core__DOT__idu_io_op1, vlSelf->SimTop__DOT__core__DOT__idu_io_op2)
                                                 : 
                                                ((4U 
                                                  == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                  ? (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35)
                                                  : 
                                                 ((2U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                   ? 
                                                  (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                                   != vlSelf->SimTop__DOT__core__DOT__idu_io_op2)
                                                   : 
                                                  ((1U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                                   & (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                                      == vlSelf->SimTop__DOT__core__DOT__idu_io_op2)))))))))));
        tracep->fullCData(oldp+71,(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code),4);
        tracep->fullSData(oldp+72,(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code),16);
        tracep->fullCData(oldp+73,(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code),8);
        tracep->fullBit(oldp+74,(vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en));
        tracep->fullBit(oldp+75,(vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en));
        tracep->fullQData(oldp+76,(vlSelf->SimTop__DOT__core__DOT__idu_io_op1),64);
        tracep->fullQData(oldp+78,(vlSelf->SimTop__DOT__core__DOT__idu_io_op2),64);
        tracep->fullQData(oldp+80,(((1U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                     ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                     : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9)),64);
        tracep->fullBit(oldp+82,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw));
        tracep->fullBit(oldp+83,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw));
        tracep->fullBit(oldp+84,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw));
        tracep->fullBit(oldp+85,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor));
        tracep->fullBit(oldp+86,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or));
        tracep->fullBit(oldp+87,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and));
        tracep->fullBit(oldp+88,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt));
        tracep->fullBit(oldp+89,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu));
        tracep->fullCData(oldp+90,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo),8);
        tracep->fullCData(oldp+91,((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
                                     << 7U) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt) 
                                                << 6U) 
                                               | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and) 
                                                   << 5U) 
                                                  | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or) 
                                                      << 4U) 
                                                     | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor) 
                                                         << 3U) 
                                                        | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw) 
                                                            << 2U) 
                                                           | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw) 
                                                               << 1U) 
                                                              | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw))))))))),8);
        tracep->fullSData(oldp+92,((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
                                     << 0xfU) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt) 
                                                  << 0xeU) 
                                                 | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and) 
                                                     << 0xdU) 
                                                    | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or) 
                                                        << 0xcU) 
                                                       | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor) 
                                                           << 0xbU) 
                                                          | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw) 
                                                              << 0xaU) 
                                                             | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw) 
                                                                 << 9U) 
                                                                | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw) 
                                                                    << 8U) 
                                                                   | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo)))))))))),16);
        tracep->fullBit(oldp+93,((0U != (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
                                          << 0xfU) 
                                         | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt) 
                                             << 0xeU) 
                                            | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and) 
                                                << 0xdU) 
                                               | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or) 
                                                   << 0xcU) 
                                                  | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor) 
                                                      << 0xbU) 
                                                     | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw) 
                                                         << 0xaU) 
                                                        | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw) 
                                                            << 9U) 
                                                           | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw) 
                                                               << 8U) 
                                                              | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo))))))))))));
        tracep->fullBit(oldp+94,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r));
        tracep->fullBit(oldp+95,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i));
        tracep->fullBit(oldp+96,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s));
        tracep->fullBit(oldp+97,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b));
        tracep->fullBit(oldp+98,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u));
        tracep->fullCData(oldp+99,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type),6);
        tracep->fullQData(oldp+100,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j),64);
        VL_EXTEND_WI(127,1, __Vtemp87, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36));
        VL_EXTEND_WI(127,1, __Vtemp88, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35));
        VL_EXTEND_WQ(127,64, __Vtemp89, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                         & vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp90, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                         | vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp91, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                         ^ vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        if ((0x8000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))) {
            __Vtemp101[0U] = __Vtemp87[0U];
            __Vtemp101[1U] = __Vtemp87[1U];
            __Vtemp101[2U] = __Vtemp87[2U];
            __Vtemp101[3U] = __Vtemp87[3U];
        } else {
            __Vtemp101[0U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                               ? __Vtemp88[0U] : ((0x2000U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp89[0U]
                                                   : 
                                                  ((0x1000U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp90[0U]
                                                    : 
                                                   ((0x800U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp91[0U]
                                                     : 
                                                    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U]))));
            __Vtemp101[1U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                               ? __Vtemp88[1U] : ((0x2000U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp89[1U]
                                                   : 
                                                  ((0x1000U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp90[1U]
                                                    : 
                                                   ((0x800U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp91[1U]
                                                     : 
                                                    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U]))));
            __Vtemp101[2U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                               ? __Vtemp88[2U] : ((0x2000U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp89[2U]
                                                   : 
                                                  ((0x1000U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp90[2U]
                                                    : 
                                                   ((0x800U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp91[2U]
                                                     : 
                                                    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[2U]))));
            __Vtemp101[3U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                               ? __Vtemp88[3U] : ((0x2000U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp89[3U]
                                                   : 
                                                  ((0x1000U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp90[3U]
                                                    : 
                                                   ((0x800U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp91[3U]
                                                     : 
                                                    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[3U]))));
        }
        tracep->fullWData(oldp+102,(__Vtemp101),127);
        tracep->fullBit(oldp+106,(vlSelf->clock));
        tracep->fullBit(oldp+107,(vlSelf->reset));
        tracep->fullBit(oldp+108,(vlSelf->io_imem_en));
        tracep->fullQData(oldp+109,(vlSelf->io_imem_addr),64);
        tracep->fullIData(oldp+111,(vlSelf->io_imem_data),32);
        tracep->fullIData(oldp+112,((IData)(((0x80U 
                                              == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                              ? (0xfffffffffffffffeULL 
                                                 & vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1)
                                              : ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)) 
                                                 + 
                                                 ((1U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                                   ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                                   : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9))))),32);
        tracep->fullBit(oldp+113,(((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
                                     | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i)) 
                                    | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u)) 
                                   | (0x6fU == (0x7fU 
                                                & vlSelf->io_imem_data)))));
        tracep->fullCData(oldp+114,((0x1fU & (vlSelf->io_imem_data 
                                              >> 0xfU))),5);
        tracep->fullCData(oldp+115,((0x1fU & (vlSelf->io_imem_data 
                                              >> 0x14U))),5);
        tracep->fullCData(oldp+116,((0x1fU & (vlSelf->io_imem_data 
                                              >> 7U))),5);
        tracep->fullQData(oldp+117,(((1U & ((~ (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en)) 
                                            | (0U == 
                                               (0x1fU 
                                                & (vlSelf->io_imem_data 
                                                   >> 0xfU)))))
                                      ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                     [(0x1fU & (vlSelf->io_imem_data 
                                                >> 0xfU))])),64);
        tracep->fullQData(oldp+119,(((1U & ((~ (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en)) 
                                            | (0U == 
                                               (0x1fU 
                                                & (vlSelf->io_imem_data 
                                                   >> 0x14U)))))
                                      ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                     [(0x1fU & (vlSelf->io_imem_data 
                                                >> 0x14U))])),64);
        VL_EXTEND_WQ(127,64, __Vtemp102, (((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                           | (0x40U 
                                              == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)))
                                           ? (4ULL 
                                              + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                           : 0ULL));
        VL_EXTEND_WI(127,1, __Vtemp103, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36));
        VL_EXTEND_WI(127,1, __Vtemp104, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35));
        VL_EXTEND_WQ(127,64, __Vtemp105, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                          & vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp106, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                          | vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp107, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                          ^ vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        tracep->fullQData(oldp+121,((((QData)((IData)(
                                                      ((2U 
                                                        == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                        ? 
                                                       __Vtemp102[1U]
                                                        : 
                                                       ((1U 
                                                         == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                         ? 
                                                        ((0x8000U 
                                                          == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                          ? 
                                                         __Vtemp103[1U]
                                                          : 
                                                         ((0x4000U 
                                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                           ? 
                                                          __Vtemp104[1U]
                                                           : 
                                                          ((0x2000U 
                                                            == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                            ? 
                                                           __Vtemp105[1U]
                                                            : 
                                                           ((0x1000U 
                                                             == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                             ? 
                                                            __Vtemp106[1U]
                                                             : 
                                                            ((0x800U 
                                                              == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                              ? 
                                                             __Vtemp107[1U]
                                                              : 
                                                             vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U])))))
                                                         : 0U)))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  ((2U 
                                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                                    ? 
                                                                   __Vtemp102[0U]
                                                                    : 
                                                                   ((1U 
                                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                                     ? 
                                                                    ((0x8000U 
                                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                      ? 
                                                                     __Vtemp103[0U]
                                                                      : 
                                                                     ((0x4000U 
                                                                       == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                       ? 
                                                                      __Vtemp104[0U]
                                                                       : 
                                                                      ((0x2000U 
                                                                        == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                        ? 
                                                                       __Vtemp105[0U]
                                                                        : 
                                                                       ((0x1000U 
                                                                         == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                         ? 
                                                                        __Vtemp106[0U]
                                                                         : 
                                                                        ((0x800U 
                                                                          == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                          ? 
                                                                         __Vtemp107[0U]
                                                                          : 
                                                                         vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U])))))
                                                                     : 0U)))))),64);
        tracep->fullQData(oldp+123,(((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                      ? (0xfffffffffffffffeULL 
                                         & vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1)
                                      : ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)) 
                                         + ((1U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                             ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                             : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9)))),64);
        tracep->fullBit(oldp+125,(((0x100073U == vlSelf->io_imem_data) 
                                   | (0x6bU == vlSelf->io_imem_data))));
        tracep->fullBit(oldp+126,((0x1033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+127,((0x5033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+128,((0x40005033U == (0xfe00707fU 
                                                   & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+129,((0x1013U == (0xfc00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+130,((0x5013U == (0xfc00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+131,((0x40005013U == (0xfc00707fU 
                                                   & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+132,((0x103bU == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+133,((0x503bU == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+134,((0x4000503bU == (0xfe00707fU 
                                                   & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+135,((0x101bU == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+136,((0x501bU == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+137,((0x4000501bU == (0xfe00707fU 
                                                   & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+138,((0x33U == (0xfe00707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+139,((0x3bU == (0xfe00707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+140,((0x13U == (0x707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+141,((0x1bU == (0x707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+142,((0x40000033U == (0xfe00707fU 
                                                   & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+143,((0x4000003bU == (0xfe00707fU 
                                                   & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+144,((0x37U == (0x7fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+145,((0x17U == (0x7fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+146,((0x4033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+147,((0x6033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+148,((0x7033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+149,((0x4013U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+150,((0x6013U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+151,((0x7013U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+152,((0x2033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+153,((0x3033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+154,((0x2013U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+155,((0x3013U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+156,((0x63U == (0x707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+157,((0x1063U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+158,((0x4063U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+159,((0x5063U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+160,((0x6063U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+161,((0x7063U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+162,((0x6fU == (0x7fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+163,((0x67U == (0x707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+164,((3U == (0x707fU & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+165,((0x1003U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+166,((0x2003U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+167,((0x3003U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+168,((0x4003U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+169,((0x5003U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+170,((0x6003U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+171,((0x23U == (0x707fU 
                                             & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+172,((0x1023U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+173,((0x2023U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+174,((0x3023U == (0x707fU 
                                               & vlSelf->io_imem_data))));
        tracep->fullBit(oldp+175,((((0x33U == (0xfe00707fU 
                                               & vlSelf->io_imem_data)) 
                                    | (0x13U == (0x707fU 
                                                 & vlSelf->io_imem_data))) 
                                   | (0x37U == (0x7fU 
                                                & vlSelf->io_imem_data)))));
        tracep->fullBit(oldp+176,(((0x3bU == (0xfe00707fU 
                                              & vlSelf->io_imem_data)) 
                                   | (0x1bU == (0x707fU 
                                                & vlSelf->io_imem_data)))));
        tracep->fullBit(oldp+177,(((0x1033U == (0xfe00707fU 
                                                & vlSelf->io_imem_data)) 
                                   | (0x1013U == (0xfc00707fU 
                                                  & vlSelf->io_imem_data)))));
        tracep->fullBit(oldp+178,(((0x5033U == (0xfe00707fU 
                                                & vlSelf->io_imem_data)) 
                                   | (0x5013U == (0xfc00707fU 
                                                  & vlSelf->io_imem_data)))));
        tracep->fullBit(oldp+179,(((0x40005033U == 
                                    (0xfe00707fU & vlSelf->io_imem_data)) 
                                   | (0x40005013U == 
                                      (0xfc00707fU 
                                       & vlSelf->io_imem_data)))));
        tracep->fullCData(oldp+180,((((0x5063U == (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                      << 3U) | (((0x4063U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                                 << 2U) 
                                                | (((0x1063U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->io_imem_data)) 
                                                    << 1U) 
                                                   | (0x63U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)))))),4);
        tracep->fullCData(oldp+181,((((0x67U == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                      << 3U) | (((0x6fU 
                                                  == 
                                                  (0x7fU 
                                                   & vlSelf->io_imem_data)) 
                                                 << 2U) 
                                                | (((0x7063U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->io_imem_data)) 
                                                    << 1U) 
                                                   | (0x6063U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)))))),4);
        tracep->fullCData(oldp+182,((((0x67U == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                      << 7U) | (((0x6fU 
                                                  == 
                                                  (0x7fU 
                                                   & vlSelf->io_imem_data)) 
                                                 << 6U) 
                                                | (((0x7063U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->io_imem_data)) 
                                                    << 5U) 
                                                   | (((0x6063U 
                                                        == 
                                                        (0x707fU 
                                                         & vlSelf->io_imem_data)) 
                                                       << 4U) 
                                                      | (((0x5063U 
                                                           == 
                                                           (0x707fU 
                                                            & vlSelf->io_imem_data)) 
                                                          << 3U) 
                                                         | (((0x4063U 
                                                              == 
                                                              (0x707fU 
                                                               & vlSelf->io_imem_data)) 
                                                             << 2U) 
                                                            | (((0x1063U 
                                                                 == 
                                                                 (0x707fU 
                                                                  & vlSelf->io_imem_data)) 
                                                                << 1U) 
                                                               | (0x63U 
                                                                  == 
                                                                  (0x707fU 
                                                                   & vlSelf->io_imem_data)))))))))),8);
        tracep->fullBit(oldp+183,((0U != (((0x67U == 
                                            (0x707fU 
                                             & vlSelf->io_imem_data)) 
                                           << 7U) | 
                                          (((0x6fU 
                                             == (0x7fU 
                                                 & vlSelf->io_imem_data)) 
                                            << 6U) 
                                           | (((0x7063U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                               << 5U) 
                                              | (((0x6063U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->io_imem_data)) 
                                                  << 4U) 
                                                 | (((0x5063U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)) 
                                                     << 3U) 
                                                    | (((0x4063U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelf->io_imem_data)) 
                                                        << 2U) 
                                                       | (((0x1063U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelf->io_imem_data)) 
                                                           << 1U) 
                                                          | (0x63U 
                                                             == 
                                                             (0x707fU 
                                                              & vlSelf->io_imem_data))))))))))));
        tracep->fullCData(oldp+184,((((0x6003U == (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                      << 6U) | (((0x5003U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                                 << 5U) 
                                                | (((0x4003U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->io_imem_data)) 
                                                    << 4U) 
                                                   | (((0x3003U 
                                                        == 
                                                        (0x707fU 
                                                         & vlSelf->io_imem_data)) 
                                                       << 3U) 
                                                      | (((0x2003U 
                                                           == 
                                                           (0x707fU 
                                                            & vlSelf->io_imem_data)) 
                                                          << 2U) 
                                                         | (((0x1003U 
                                                              == 
                                                              (0x707fU 
                                                               & vlSelf->io_imem_data)) 
                                                             << 1U) 
                                                            | (3U 
                                                               == 
                                                               (0x707fU 
                                                                & vlSelf->io_imem_data))))))))),7);
        tracep->fullBit(oldp+185,((0U != (((0x6003U 
                                            == (0x707fU 
                                                & vlSelf->io_imem_data)) 
                                           << 6U) | 
                                          (((0x5003U 
                                             == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                            << 5U) 
                                           | (((0x4003U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                               << 4U) 
                                              | (((0x3003U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->io_imem_data)) 
                                                  << 3U) 
                                                 | (((0x2003U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)) 
                                                     << 2U) 
                                                    | (((0x1003U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelf->io_imem_data)) 
                                                        << 1U) 
                                                       | (3U 
                                                          == 
                                                          (0x707fU 
                                                           & vlSelf->io_imem_data)))))))))));
        tracep->fullCData(oldp+186,((((0x3023U == (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                      << 3U) | (((0x2023U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                                 << 2U) 
                                                | (((0x1023U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->io_imem_data)) 
                                                    << 1U) 
                                                   | (0x23U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)))))),4);
        tracep->fullBit(oldp+187,((0U != (((0x3023U 
                                            == (0x707fU 
                                                & vlSelf->io_imem_data)) 
                                           << 3U) | 
                                          (((0x2023U 
                                             == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                            << 2U) 
                                           | (((0x1023U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                               << 1U) 
                                              | (0x23U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelf->io_imem_data))))))));
        tracep->fullCData(oldp+188,((((0U != (((0x67U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                               << 7U) 
                                              | (((0x6fU 
                                                   == 
                                                   (0x7fU 
                                                    & vlSelf->io_imem_data)) 
                                                  << 6U) 
                                                 | (((0x7063U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)) 
                                                     << 5U) 
                                                    | (((0x6063U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelf->io_imem_data)) 
                                                        << 4U) 
                                                       | (((0x5063U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelf->io_imem_data)) 
                                                           << 3U) 
                                                          | (((0x4063U 
                                                               == 
                                                               (0x707fU 
                                                                & vlSelf->io_imem_data)) 
                                                              << 2U) 
                                                             | (((0x1063U 
                                                                  == 
                                                                  (0x707fU 
                                                                   & vlSelf->io_imem_data)) 
                                                                 << 1U) 
                                                                | (0x63U 
                                                                   == 
                                                                   (0x707fU 
                                                                    & vlSelf->io_imem_data)))))))))) 
                                      << 1U) | (0U 
                                                != 
                                                (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
                                                  << 0xfU) 
                                                 | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt) 
                                                     << 0xeU) 
                                                    | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and) 
                                                        << 0xdU) 
                                                       | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or) 
                                                           << 0xcU) 
                                                          | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor) 
                                                              << 0xbU) 
                                                             | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw) 
                                                                 << 0xaU) 
                                                                | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw) 
                                                                    << 9U) 
                                                                   | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw) 
                                                                       << 8U) 
                                                                      | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo)))))))))))),2);
        tracep->fullCData(oldp+189,((((0U != (((0x3023U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                               << 3U) 
                                              | (((0x2023U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->io_imem_data)) 
                                                  << 2U) 
                                                 | (((0x1023U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)) 
                                                     << 1U) 
                                                    | (0x23U 
                                                       == 
                                                       (0x707fU 
                                                        & vlSelf->io_imem_data)))))) 
                                      << 1U) | (0U 
                                                != 
                                                (((0x6003U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->io_imem_data)) 
                                                  << 6U) 
                                                 | (((0x5003U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelf->io_imem_data)) 
                                                     << 5U) 
                                                    | (((0x4003U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelf->io_imem_data)) 
                                                        << 4U) 
                                                       | (((0x3003U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelf->io_imem_data)) 
                                                           << 3U) 
                                                          | (((0x2003U 
                                                               == 
                                                               (0x707fU 
                                                                & vlSelf->io_imem_data)) 
                                                              << 2U) 
                                                             | (((0x1003U 
                                                                  == 
                                                                  (0x707fU 
                                                                   & vlSelf->io_imem_data)) 
                                                                 << 1U) 
                                                                | (3U 
                                                                   == 
                                                                   (0x707fU 
                                                                    & vlSelf->io_imem_data))))))))))),2);
        tracep->fullQData(oldp+190,(((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0xfffffffffffffULL
                                      : 0ULL)),52);
        tracep->fullSData(oldp+192,((vlSelf->io_imem_data 
                                     >> 0x14U)),12);
        tracep->fullQData(oldp+193,(((((vlSelf->io_imem_data 
                                        >> 0x1fU) ? 0xfffffffffffffULL
                                        : 0ULL) << 0xcU) 
                                     | (QData)((IData)(
                                                       (vlSelf->io_imem_data 
                                                        >> 0x14U))))),64);
        tracep->fullCData(oldp+195,((vlSelf->io_imem_data 
                                     >> 0x19U)),7);
        tracep->fullQData(oldp+196,(((((vlSelf->io_imem_data 
                                        >> 0x1fU) ? 0xfffffffffffffULL
                                        : 0ULL) << 0xcU) 
                                     | (QData)((IData)(
                                                       ((0xfe0U 
                                                         & (vlSelf->io_imem_data 
                                                            >> 0x14U)) 
                                                        | (0x1fU 
                                                           & (vlSelf->io_imem_data 
                                                              >> 7U))))))),64);
        tracep->fullQData(oldp+198,(((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0x7ffffffffffULL
                                      : 0ULL)),43);
        tracep->fullBit(oldp+200,((1U & (vlSelf->io_imem_data 
                                         >> 7U))));
        tracep->fullCData(oldp+201,((0x3fU & (vlSelf->io_imem_data 
                                              >> 0x19U))),6);
        tracep->fullCData(oldp+202,((0xfU & (vlSelf->io_imem_data 
                                             >> 8U))),4);
        tracep->fullQData(oldp+203,(((((vlSelf->io_imem_data 
                                        >> 0x1fU) ? 0x7ffffffffffULL
                                        : 0ULL) << 0xdU) 
                                     | (QData)((IData)(
                                                       ((0x1000U 
                                                         & (vlSelf->io_imem_data 
                                                            >> 0x13U)) 
                                                        | ((0x800U 
                                                            & (vlSelf->io_imem_data 
                                                               << 4U)) 
                                                           | ((0x7e0U 
                                                               & (vlSelf->io_imem_data 
                                                                  >> 0x14U)) 
                                                              | (0x1eU 
                                                                 & (vlSelf->io_imem_data 
                                                                    >> 7U))))))))),56);
        tracep->fullIData(oldp+205,(((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0xffffffffU
                                      : 0U)),32);
        tracep->fullIData(oldp+206,((vlSelf->io_imem_data 
                                     >> 0xcU)),20);
        tracep->fullQData(oldp+207,((((QData)((IData)(
                                                      ((vlSelf->io_imem_data 
                                                        >> 0x1fU)
                                                        ? 0xffffffffU
                                                        : 0U))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  (0xfffff000U 
                                                                   & vlSelf->io_imem_data))))),64);
        tracep->fullCData(oldp+209,((0xffU & (vlSelf->io_imem_data 
                                              >> 0xcU))),8);
        tracep->fullBit(oldp+210,((1U & (vlSelf->io_imem_data 
                                         >> 0x14U))));
        tracep->fullSData(oldp+211,((0x3ffU & (vlSelf->io_imem_data 
                                               >> 0x15U))),10);
        tracep->fullQData(oldp+212,((((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                      | (0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)))
                                      ? (4ULL + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                      : 0ULL)),64);
        tracep->fullQData(oldp+214,((QData)((IData)(
                                                    (0x1fU 
                                                     & (vlSelf->io_imem_data 
                                                        >> 0xfU))))),64);
        tracep->fullQData(oldp+216,((QData)((IData)(
                                                    (0x1fU 
                                                     & (vlSelf->io_imem_data 
                                                        >> 0x14U))))),64);
        tracep->fullQData(oldp+218,((QData)((IData)(
                                                    (0x1fU 
                                                     & (vlSelf->io_imem_data 
                                                        >> 7U))))),64);
    }
}
