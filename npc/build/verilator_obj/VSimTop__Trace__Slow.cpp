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
        tracep->declBit(c+70,"clock", false,-1);
        tracep->declBit(c+71,"reset", false,-1);
        tracep->declBit(c+72,"io_imem_en", false,-1);
        tracep->declQuad(c+73,"io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+75,"io_imem_data", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop clock", false,-1);
        tracep->declBit(c+71,"SimTop reset", false,-1);
        tracep->declBit(c+72,"SimTop io_imem_en", false,-1);
        tracep->declQuad(c+73,"SimTop io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop io_imem_data", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop core_clock", false,-1);
        tracep->declBit(c+71,"SimTop core_reset", false,-1);
        tracep->declQuad(c+1,"SimTop core_io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop core_io_imem_data", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop core clock", false,-1);
        tracep->declBit(c+71,"SimTop core reset", false,-1);
        tracep->declQuad(c+1,"SimTop core io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop core io_imem_data", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop core ifu_clock", false,-1);
        tracep->declBit(c+71,"SimTop core ifu_reset", false,-1);
        tracep->declQuad(c+1,"SimTop core ifu_io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop core ifu_io_imem_data", false,-1, 31,0);
        tracep->declQuad(c+1,"SimTop core ifu_io_pc", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop core ifu_io_inst", false,-1, 31,0);
        tracep->declBus(c+75,"SimTop core idu_io_inst", false,-1, 31,0);
        tracep->declBit(c+76,"SimTop core idu_io_decode_info_fu_code", false,-1);
        tracep->declBit(c+76,"SimTop core idu_io_decode_info_alu_code", false,-1);
        tracep->declBit(c+76,"SimTop core idu_io_rs1_en", false,-1);
        tracep->declBit(c+124,"SimTop core idu_io_rs2_en", false,-1);
        tracep->declBit(c+76,"SimTop core idu_io_rd_en", false,-1);
        tracep->declBus(c+77,"SimTop core idu_io_rs1_addr", false,-1, 4,0);
        tracep->declBus(c+78,"SimTop core idu_io_rs2_addr", false,-1, 4,0);
        tracep->declBus(c+79,"SimTop core idu_io_rd_addr", false,-1, 4,0);
        tracep->declQuad(c+80,"SimTop core idu_io_rs1_data", false,-1, 63,0);
        tracep->declQuad(c+82,"SimTop core idu_io_rs2_data", false,-1, 63,0);
        tracep->declQuad(c+84,"SimTop core idu_io_op1", false,-1, 63,0);
        tracep->declQuad(c+86,"SimTop core idu_io_op2", false,-1, 63,0);
        tracep->declBit(c+76,"SimTop core ieu_io_decode_info_fu_code", false,-1);
        tracep->declBit(c+76,"SimTop core ieu_io_decode_info_alu_code", false,-1);
        tracep->declQuad(c+84,"SimTop core ieu_io_op1", false,-1, 63,0);
        tracep->declQuad(c+86,"SimTop core ieu_io_op2", false,-1, 63,0);
        tracep->declQuad(c+88,"SimTop core ieu_io_out", false,-1, 63,0);
        tracep->declBit(c+70,"SimTop core rfu_clk", false,-1);
        tracep->declBit(c+71,"SimTop core rfu_reset", false,-1);
        tracep->declBit(c+76,"SimTop core rfu_rs1_en", false,-1);
        tracep->declBit(c+124,"SimTop core rfu_rs2_en", false,-1);
        tracep->declBit(c+76,"SimTop core rfu_rd_en", false,-1);
        tracep->declBus(c+77,"SimTop core rfu_rs1_addr", false,-1, 4,0);
        tracep->declBus(c+78,"SimTop core rfu_rs2_addr", false,-1, 4,0);
        tracep->declBus(c+79,"SimTop core rfu_rd_addr", false,-1, 4,0);
        tracep->declQuad(c+80,"SimTop core rfu_rs1_data", false,-1, 63,0);
        tracep->declQuad(c+82,"SimTop core rfu_rs2_data", false,-1, 63,0);
        tracep->declQuad(c+88,"SimTop core rfu_rd_data", false,-1, 63,0);
        tracep->declBit(c+70,"SimTop core halt_clk", false,-1);
        tracep->declBit(c+71,"SimTop core halt_reset", false,-1);
        tracep->declBit(c+90,"SimTop core halt_halt", false,-1);
        tracep->declBit(c+70,"SimTop core ifu clock", false,-1);
        tracep->declBit(c+71,"SimTop core ifu reset", false,-1);
        tracep->declQuad(c+1,"SimTop core ifu io_imem_addr", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop core ifu io_imem_data", false,-1, 31,0);
        tracep->declQuad(c+1,"SimTop core ifu io_pc", false,-1, 63,0);
        tracep->declBus(c+75,"SimTop core ifu io_inst", false,-1, 31,0);
        tracep->declBus(c+3,"SimTop core ifu pc", false,-1, 31,0);
        tracep->declBus(c+75,"SimTop core idu io_inst", false,-1, 31,0);
        tracep->declBit(c+76,"SimTop core idu io_decode_info_fu_code", false,-1);
        tracep->declBit(c+76,"SimTop core idu io_decode_info_alu_code", false,-1);
        tracep->declBit(c+76,"SimTop core idu io_rs1_en", false,-1);
        tracep->declBit(c+124,"SimTop core idu io_rs2_en", false,-1);
        tracep->declBit(c+76,"SimTop core idu io_rd_en", false,-1);
        tracep->declBus(c+77,"SimTop core idu io_rs1_addr", false,-1, 4,0);
        tracep->declBus(c+78,"SimTop core idu io_rs2_addr", false,-1, 4,0);
        tracep->declBus(c+79,"SimTop core idu io_rd_addr", false,-1, 4,0);
        tracep->declQuad(c+80,"SimTop core idu io_rs1_data", false,-1, 63,0);
        tracep->declQuad(c+82,"SimTop core idu io_rs2_data", false,-1, 63,0);
        tracep->declQuad(c+84,"SimTop core idu io_op1", false,-1, 63,0);
        tracep->declQuad(c+86,"SimTop core idu io_op2", false,-1, 63,0);
        tracep->declBit(c+76,"SimTop core idu addi", false,-1);
        tracep->declBus(c+91,"SimTop core idu inst_type", false,-1, 5,0);
        tracep->declQuad(c+92,"SimTop core idu imm_i_hi", false,-1, 51,0);
        tracep->declBus(c+94,"SimTop core idu imm_i_lo", false,-1, 11,0);
        tracep->declQuad(c+95,"SimTop core idu imm_i", false,-1, 63,0);
        tracep->declBus(c+97,"SimTop core idu imm_s_hi_lo", false,-1, 6,0);
        tracep->declBus(c+79,"SimTop core idu imm_s_lo", false,-1, 4,0);
        tracep->declQuad(c+98,"SimTop core idu imm_s", false,-1, 63,0);
        tracep->declQuad(c+100,"SimTop core idu imm_b_hi_hi_hi", false,-1, 42,0);
        tracep->declBit(c+102,"SimTop core idu imm_b_hi_lo", false,-1);
        tracep->declBus(c+103,"SimTop core idu imm_b_lo_hi_hi", false,-1, 5,0);
        tracep->declBus(c+104,"SimTop core idu imm_b_lo_hi_lo", false,-1, 3,0);
        tracep->declQuad(c+105,"SimTop core idu imm_b", false,-1, 55,0);
        tracep->declBus(c+107,"SimTop core idu imm_u_hi_hi", false,-1, 31,0);
        tracep->declBus(c+108,"SimTop core idu imm_u_hi_lo", false,-1, 19,0);
        tracep->declQuad(c+109,"SimTop core idu imm_u", false,-1, 63,0);
        tracep->declBus(c+111,"SimTop core idu imm_j_hi_lo", false,-1, 7,0);
        tracep->declBit(c+112,"SimTop core idu imm_j_lo_hi_hi", false,-1);
        tracep->declBus(c+113,"SimTop core idu imm_j_lo_hi_lo", false,-1, 9,0);
        tracep->declQuad(c+114,"SimTop core idu imm_j", false,-1, 63,0);
        tracep->declQuad(c+86,"SimTop core idu imm", false,-1, 63,0);
        tracep->declBit(c+76,"SimTop core ieu io_decode_info_fu_code", false,-1);
        tracep->declBit(c+76,"SimTop core ieu io_decode_info_alu_code", false,-1);
        tracep->declQuad(c+84,"SimTop core ieu io_op1", false,-1, 63,0);
        tracep->declQuad(c+86,"SimTop core ieu io_op2", false,-1, 63,0);
        tracep->declQuad(c+88,"SimTop core ieu io_out", false,-1, 63,0);
        tracep->declQuad(c+116,"SimTop core ieu alu_out", false,-1, 63,0);
        tracep->declBit(c+70,"SimTop core rfu clk", false,-1);
        tracep->declBit(c+71,"SimTop core rfu reset", false,-1);
        tracep->declBit(c+76,"SimTop core rfu rs1_en", false,-1);
        tracep->declBit(c+124,"SimTop core rfu rs2_en", false,-1);
        tracep->declBit(c+76,"SimTop core rfu rd_en", false,-1);
        tracep->declQuad(c+118,"SimTop core rfu rs1_addr", false,-1, 63,0);
        tracep->declQuad(c+120,"SimTop core rfu rs2_addr", false,-1, 63,0);
        tracep->declQuad(c+122,"SimTop core rfu rd_addr", false,-1, 63,0);
        tracep->declQuad(c+80,"SimTop core rfu rs1_data", false,-1, 63,0);
        tracep->declQuad(c+82,"SimTop core rfu rs2_data", false,-1, 63,0);
        tracep->declQuad(c+88,"SimTop core rfu rd_data", false,-1, 63,0);
        {int i; for (i=0; i<32; i++) {
                tracep->declQuad(c+4+i*2,"SimTop core rfu rf", true,(i+0), 63,0);}}
        tracep->declBus(c+68,"SimTop core rfu unnamedblk1 i", false,-1, 31,0);
        tracep->declBit(c+70,"SimTop core halt clk", false,-1);
        tracep->declBit(c+71,"SimTop core halt reset", false,-1);
        tracep->declBit(c+90,"SimTop core halt halt", false,-1);
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
        tracep->fullBit(oldp+70,(vlSelf->clock));
        tracep->fullBit(oldp+71,(vlSelf->reset));
        tracep->fullBit(oldp+72,(vlSelf->io_imem_en));
        tracep->fullQData(oldp+73,(vlSelf->io_imem_addr),64);
        tracep->fullIData(oldp+75,(vlSelf->io_imem_data),32);
        tracep->fullBit(oldp+76,((0x13U == (0x707fU 
                                            & vlSelf->io_imem_data))));
        tracep->fullCData(oldp+77,((0x1fU & (vlSelf->io_imem_data 
                                             >> 0xfU))),5);
        tracep->fullCData(oldp+78,((0x1fU & (vlSelf->io_imem_data 
                                             >> 0x14U))),5);
        tracep->fullCData(oldp+79,((0x1fU & (vlSelf->io_imem_data 
                                             >> 7U))),5);
        tracep->fullQData(oldp+80,((((0x13U == (0x707fU 
                                                & vlSelf->io_imem_data)) 
                                     | (0U == (0x1fU 
                                               & (vlSelf->io_imem_data 
                                                  >> 0xfU))))
                                     ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                    [(0x1fU & (vlSelf->io_imem_data 
                                               >> 0xfU))])),64);
        tracep->fullQData(oldp+82,(((0U == (0x1fU & 
                                            (vlSelf->io_imem_data 
                                             >> 0x14U)))
                                     ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                    [(0x1fU & (vlSelf->io_imem_data 
                                               >> 0x14U))])),64);
        tracep->fullQData(oldp+84,(((0x13U == (0x707fU 
                                               & vlSelf->io_imem_data))
                                     ? (((0x13U == 
                                          (0x707fU 
                                           & vlSelf->io_imem_data)) 
                                         | (0U == (0x1fU 
                                                   & (vlSelf->io_imem_data 
                                                      >> 0xfU))))
                                         ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                        [(0x1fU & (vlSelf->io_imem_data 
                                                   >> 0xfU))])
                                     : 0ULL)),64);
        tracep->fullQData(oldp+86,(((1U == ((0x13U 
                                             == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                            << 4U))
                                     ? ((((vlSelf->io_imem_data 
                                           >> 0x1fU)
                                           ? 0x7ffffffffffULL
                                           : 0ULL) 
                                         << 0x15U) 
                                        | (QData)((IData)(
                                                          ((0x100000U 
                                                            & (vlSelf->io_imem_data 
                                                               >> 0xbU)) 
                                                           | ((0xff000U 
                                                               & vlSelf->io_imem_data) 
                                                              | ((0x800U 
                                                                  & (vlSelf->io_imem_data 
                                                                     >> 9U)) 
                                                                 | (0x7feU 
                                                                    & (vlSelf->io_imem_data 
                                                                       >> 0x14U))))))))
                                     : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9)),64);
        tracep->fullQData(oldp+88,(((0x13U == (0x707fU 
                                               & vlSelf->io_imem_data))
                                     ? ((0x13U == (0x707fU 
                                                   & vlSelf->io_imem_data))
                                         ? (((0x13U 
                                              == (0x707fU 
                                                  & vlSelf->io_imem_data))
                                              ? (((0x13U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->io_imem_data)) 
                                                  | (0U 
                                                     == 
                                                     (0x1fU 
                                                      & (vlSelf->io_imem_data 
                                                         >> 0xfU))))
                                                  ? 0ULL
                                                  : 
                                                 vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                                 [(0x1fU 
                                                   & (vlSelf->io_imem_data 
                                                      >> 0xfU))])
                                              : 0ULL) 
                                            + ((1U 
                                                == 
                                                ((0x13U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                                 << 4U))
                                                ? (
                                                   (((vlSelf->io_imem_data 
                                                      >> 0x1fU)
                                                      ? 0x7ffffffffffULL
                                                      : 0ULL) 
                                                    << 0x15U) 
                                                   | (QData)((IData)(
                                                                     ((0x100000U 
                                                                       & (vlSelf->io_imem_data 
                                                                          >> 0xbU)) 
                                                                      | ((0xff000U 
                                                                          & vlSelf->io_imem_data) 
                                                                         | ((0x800U 
                                                                             & (vlSelf->io_imem_data 
                                                                                >> 9U)) 
                                                                            | (0x7feU 
                                                                               & (vlSelf->io_imem_data 
                                                                                >> 0x14U))))))))
                                                : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9))
                                         : 0ULL) : 0ULL)),64);
        tracep->fullBit(oldp+90,((0x100073U == vlSelf->io_imem_data)));
        tracep->fullCData(oldp+91,(((0x13U == (0x707fU 
                                               & vlSelf->io_imem_data)) 
                                    << 4U)),6);
        tracep->fullQData(oldp+92,(((vlSelf->io_imem_data 
                                     >> 0x1fU) ? 0xfffffffffffffULL
                                     : 0ULL)),52);
        tracep->fullSData(oldp+94,((vlSelf->io_imem_data 
                                    >> 0x14U)),12);
        tracep->fullQData(oldp+95,(((((vlSelf->io_imem_data 
                                       >> 0x1fU) ? 0xfffffffffffffULL
                                       : 0ULL) << 0xcU) 
                                    | (QData)((IData)(
                                                      (vlSelf->io_imem_data 
                                                       >> 0x14U))))),64);
        tracep->fullCData(oldp+97,((vlSelf->io_imem_data 
                                    >> 0x19U)),7);
        tracep->fullQData(oldp+98,(((((vlSelf->io_imem_data 
                                       >> 0x1fU) ? 0xfffffffffffffULL
                                       : 0ULL) << 0xcU) 
                                    | (QData)((IData)(
                                                      ((0xfe0U 
                                                        & (vlSelf->io_imem_data 
                                                           >> 0x14U)) 
                                                       | (0x1fU 
                                                          & (vlSelf->io_imem_data 
                                                             >> 7U))))))),64);
        tracep->fullQData(oldp+100,(((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0x7ffffffffffULL
                                      : 0ULL)),43);
        tracep->fullBit(oldp+102,((1U & (vlSelf->io_imem_data 
                                         >> 7U))));
        tracep->fullCData(oldp+103,((0x3fU & (vlSelf->io_imem_data 
                                              >> 0x19U))),6);
        tracep->fullCData(oldp+104,((0xfU & (vlSelf->io_imem_data 
                                             >> 8U))),4);
        tracep->fullQData(oldp+105,(((((vlSelf->io_imem_data 
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
        tracep->fullIData(oldp+107,(((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0xffffffffU
                                      : 0U)),32);
        tracep->fullIData(oldp+108,((vlSelf->io_imem_data 
                                     >> 0xcU)),20);
        tracep->fullQData(oldp+109,((((QData)((IData)(
                                                      ((vlSelf->io_imem_data 
                                                        >> 0x1fU)
                                                        ? 0xffffffffU
                                                        : 0U))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  (0xfffff000U 
                                                                   & vlSelf->io_imem_data))))),64);
        tracep->fullCData(oldp+111,((0xffU & (vlSelf->io_imem_data 
                                              >> 0xcU))),8);
        tracep->fullBit(oldp+112,((1U & (vlSelf->io_imem_data 
                                         >> 0x14U))));
        tracep->fullSData(oldp+113,((0x3ffU & (vlSelf->io_imem_data 
                                               >> 0x15U))),10);
        tracep->fullQData(oldp+114,(((((vlSelf->io_imem_data 
                                        >> 0x1fU) ? 0x7ffffffffffULL
                                        : 0ULL) << 0x15U) 
                                     | (QData)((IData)(
                                                       ((0x100000U 
                                                         & (vlSelf->io_imem_data 
                                                            >> 0xbU)) 
                                                        | ((0xff000U 
                                                            & vlSelf->io_imem_data) 
                                                           | ((0x800U 
                                                               & (vlSelf->io_imem_data 
                                                                  >> 9U)) 
                                                              | (0x7feU 
                                                                 & (vlSelf->io_imem_data 
                                                                    >> 0x14U))))))))),64);
        tracep->fullQData(oldp+116,(((0x13U == (0x707fU 
                                                & vlSelf->io_imem_data))
                                      ? (((0x13U == 
                                           (0x707fU 
                                            & vlSelf->io_imem_data))
                                           ? (((0x13U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                               | (0U 
                                                  == 
                                                  (0x1fU 
                                                   & (vlSelf->io_imem_data 
                                                      >> 0xfU))))
                                               ? 0ULL
                                               : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                              [(0x1fU 
                                                & (vlSelf->io_imem_data 
                                                   >> 0xfU))])
                                           : 0ULL) 
                                         + ((1U == 
                                             ((0x13U 
                                               == (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                              << 4U))
                                             ? ((((vlSelf->io_imem_data 
                                                   >> 0x1fU)
                                                   ? 0x7ffffffffffULL
                                                   : 0ULL) 
                                                 << 0x15U) 
                                                | (QData)((IData)(
                                                                  ((0x100000U 
                                                                    & (vlSelf->io_imem_data 
                                                                       >> 0xbU)) 
                                                                   | ((0xff000U 
                                                                       & vlSelf->io_imem_data) 
                                                                      | ((0x800U 
                                                                          & (vlSelf->io_imem_data 
                                                                             >> 9U)) 
                                                                         | (0x7feU 
                                                                            & (vlSelf->io_imem_data 
                                                                               >> 0x14U))))))))
                                             : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9))
                                      : 0ULL)),64);
        tracep->fullQData(oldp+118,((QData)((IData)(
                                                    (0x1fU 
                                                     & (vlSelf->io_imem_data 
                                                        >> 0xfU))))),64);
        tracep->fullQData(oldp+120,((QData)((IData)(
                                                    (0x1fU 
                                                     & (vlSelf->io_imem_data 
                                                        >> 0x14U))))),64);
        tracep->fullQData(oldp+122,((QData)((IData)(
                                                    (0x1fU 
                                                     & (vlSelf->io_imem_data 
                                                        >> 7U))))),64);
        tracep->fullBit(oldp+124,(0U));
    }
}
