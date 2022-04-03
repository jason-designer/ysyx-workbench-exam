// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VSimTop__Syms.h"


void VSimTop___024root__traceChgSub0(VSimTop___024root* vlSelf, VerilatedVcd* tracep);

void VSimTop___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    VSimTop___024root* const __restrict vlSelf = static_cast<VSimTop___024root*>(voidSelf);
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        VSimTop___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void VSimTop___024root__traceChgSub0(VSimTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlWide<4>/*127:0*/ __Vtemp123;
    VlWide<4>/*127:0*/ __Vtemp124;
    VlWide<4>/*127:0*/ __Vtemp125;
    VlWide<4>/*127:0*/ __Vtemp126;
    VlWide<4>/*127:0*/ __Vtemp127;
    VlWide<4>/*127:0*/ __Vtemp137;
    VlWide<4>/*127:0*/ __Vtemp138;
    VlWide<4>/*127:0*/ __Vtemp139;
    VlWide<4>/*127:0*/ __Vtemp140;
    VlWide<4>/*127:0*/ __Vtemp141;
    VlWide<4>/*127:0*/ __Vtemp142;
    VlWide<4>/*127:0*/ __Vtemp143;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
            tracep->chgQData(oldp+0,((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc))),64);
            tracep->chgIData(oldp+2,(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc),32);
            tracep->chgQData(oldp+3,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0]),64);
            tracep->chgQData(oldp+5,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[1]),64);
            tracep->chgQData(oldp+7,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[2]),64);
            tracep->chgQData(oldp+9,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[3]),64);
            tracep->chgQData(oldp+11,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[4]),64);
            tracep->chgQData(oldp+13,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[5]),64);
            tracep->chgQData(oldp+15,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[6]),64);
            tracep->chgQData(oldp+17,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[7]),64);
            tracep->chgQData(oldp+19,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[8]),64);
            tracep->chgQData(oldp+21,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[9]),64);
            tracep->chgQData(oldp+23,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[10]),64);
            tracep->chgQData(oldp+25,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[11]),64);
            tracep->chgQData(oldp+27,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[12]),64);
            tracep->chgQData(oldp+29,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[13]),64);
            tracep->chgQData(oldp+31,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[14]),64);
            tracep->chgQData(oldp+33,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[15]),64);
            tracep->chgQData(oldp+35,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[16]),64);
            tracep->chgQData(oldp+37,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[17]),64);
            tracep->chgQData(oldp+39,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[18]),64);
            tracep->chgQData(oldp+41,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[19]),64);
            tracep->chgQData(oldp+43,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[20]),64);
            tracep->chgQData(oldp+45,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[21]),64);
            tracep->chgQData(oldp+47,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[22]),64);
            tracep->chgQData(oldp+49,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[23]),64);
            tracep->chgQData(oldp+51,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[24]),64);
            tracep->chgQData(oldp+53,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[25]),64);
            tracep->chgQData(oldp+55,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[26]),64);
            tracep->chgQData(oldp+57,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[27]),64);
            tracep->chgQData(oldp+59,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[28]),64);
            tracep->chgQData(oldp+61,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[29]),64);
            tracep->chgQData(oldp+63,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[30]),64);
            tracep->chgQData(oldp+65,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[31]),64);
            tracep->chgIData(oldp+67,(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i),32);
            tracep->chgBit(oldp+68,(vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg[0]));
        }
        if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
            tracep->chgBit(oldp+69,(((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                     | ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                        | ((0x20U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                            ? (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                               >= vlSelf->SimTop__DOT__core__DOT__idu_io_op2)
                                            : ((0x10U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                ? (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36)
                                                : (
                                                   (8U 
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
            tracep->chgCData(oldp+70,(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code),4);
            tracep->chgSData(oldp+71,(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code),16);
            tracep->chgCData(oldp+72,(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code),8);
            tracep->chgBit(oldp+73,(vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en));
            tracep->chgBit(oldp+74,(vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en));
            tracep->chgQData(oldp+75,(vlSelf->SimTop__DOT__core__DOT__idu_io_op1),64);
            tracep->chgQData(oldp+77,(vlSelf->SimTop__DOT__core__DOT__idu_io_op2),64);
            tracep->chgQData(oldp+79,(((1U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                        ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                        : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9)),64);
            tracep->chgBit(oldp+81,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw));
            tracep->chgBit(oldp+82,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw));
            tracep->chgBit(oldp+83,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw));
            tracep->chgBit(oldp+84,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor));
            tracep->chgBit(oldp+85,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or));
            tracep->chgBit(oldp+86,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and));
            tracep->chgBit(oldp+87,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt));
            tracep->chgBit(oldp+88,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu));
            tracep->chgCData(oldp+89,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo),8);
            tracep->chgCData(oldp+90,((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
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
            tracep->chgSData(oldp+91,((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
                                        << 0xfU) | 
                                       (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt) 
                                         << 0xeU) | 
                                        (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and) 
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
            tracep->chgBit(oldp+92,((0U != (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
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
            tracep->chgBit(oldp+93,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r));
            tracep->chgBit(oldp+94,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i));
            tracep->chgBit(oldp+95,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s));
            tracep->chgBit(oldp+96,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b));
            tracep->chgBit(oldp+97,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u));
            tracep->chgCData(oldp+98,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type),6);
            tracep->chgQData(oldp+99,(vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j),64);
            VL_EXTEND_WI(127,1, __Vtemp123, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36));
            VL_EXTEND_WI(127,1, __Vtemp124, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35));
            VL_EXTEND_WQ(127,64, __Vtemp125, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                              & vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
            VL_EXTEND_WQ(127,64, __Vtemp126, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                              | vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
            VL_EXTEND_WQ(127,64, __Vtemp127, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                              ^ vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
            if ((0x8000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))) {
                __Vtemp137[0U] = __Vtemp123[0U];
                __Vtemp137[1U] = __Vtemp123[1U];
                __Vtemp137[2U] = __Vtemp123[2U];
                __Vtemp137[3U] = __Vtemp123[3U];
            } else {
                __Vtemp137[0U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                   ? __Vtemp124[0U]
                                   : ((0x2000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                       ? __Vtemp125[0U]
                                       : ((0x1000U 
                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                           ? __Vtemp126[0U]
                                           : ((0x800U 
                                               == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                               ? __Vtemp127[0U]
                                               : vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U]))));
                __Vtemp137[1U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                   ? __Vtemp124[1U]
                                   : ((0x2000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                       ? __Vtemp125[1U]
                                       : ((0x1000U 
                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                           ? __Vtemp126[1U]
                                           : ((0x800U 
                                               == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                               ? __Vtemp127[1U]
                                               : vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U]))));
                __Vtemp137[2U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                   ? __Vtemp124[2U]
                                   : ((0x2000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                       ? __Vtemp125[2U]
                                       : ((0x1000U 
                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                           ? __Vtemp126[2U]
                                           : ((0x800U 
                                               == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                               ? __Vtemp127[2U]
                                               : vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[2U]))));
                __Vtemp137[3U] = ((0x4000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                   ? __Vtemp124[3U]
                                   : ((0x2000U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                       ? __Vtemp125[3U]
                                       : ((0x1000U 
                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                           ? __Vtemp126[3U]
                                           : ((0x800U 
                                               == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                               ? __Vtemp127[3U]
                                               : vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[3U]))));
            }
            tracep->chgWData(oldp+101,(__Vtemp137),127);
        }
        tracep->chgBit(oldp+105,(vlSelf->clock));
        tracep->chgBit(oldp+106,(vlSelf->reset));
        tracep->chgBit(oldp+107,(vlSelf->io_imem_en));
        tracep->chgQData(oldp+108,(vlSelf->io_imem_addr),64);
        tracep->chgIData(oldp+110,(vlSelf->io_imem_data),32);
        tracep->chgIData(oldp+111,((IData)(((0x80U 
                                             == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                             ? (0xfffffffffffffffeULL 
                                                & vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1)
                                             : ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)) 
                                                + (
                                                   (1U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                                    ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                                    : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9))))),32);
        tracep->chgBit(oldp+112,(((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
                                    | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i)) 
                                   | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u)) 
                                  | (0x6fU == (0x7fU 
                                               & vlSelf->io_imem_data)))));
        tracep->chgCData(oldp+113,((0x1fU & (vlSelf->io_imem_data 
                                             >> 0xfU))),5);
        tracep->chgCData(oldp+114,((0x1fU & (vlSelf->io_imem_data 
                                             >> 0x14U))),5);
        tracep->chgCData(oldp+115,((0x1fU & (vlSelf->io_imem_data 
                                             >> 7U))),5);
        tracep->chgQData(oldp+116,(((1U & ((~ (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en)) 
                                           | (0U == 
                                              (0x1fU 
                                               & (vlSelf->io_imem_data 
                                                  >> 0xfU)))))
                                     ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                    [(0x1fU & (vlSelf->io_imem_data 
                                               >> 0xfU))])),64);
        tracep->chgQData(oldp+118,(((1U & ((~ (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en)) 
                                           | (0U == 
                                              (0x1fU 
                                               & (vlSelf->io_imem_data 
                                                  >> 0x14U)))))
                                     ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                    [(0x1fU & (vlSelf->io_imem_data 
                                               >> 0x14U))])),64);
        VL_EXTEND_WQ(127,64, __Vtemp138, (((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                           | (0x40U 
                                              == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)))
                                           ? (4ULL 
                                              + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                           : 0ULL));
        VL_EXTEND_WI(127,1, __Vtemp139, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36));
        VL_EXTEND_WI(127,1, __Vtemp140, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35));
        VL_EXTEND_WQ(127,64, __Vtemp141, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                          & vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp142, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                          | vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp143, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                          ^ vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        tracep->chgQData(oldp+120,((((QData)((IData)(
                                                     ((2U 
                                                       == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                       ? 
                                                      __Vtemp138[1U]
                                                       : 
                                                      ((1U 
                                                        == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                        ? 
                                                       ((0x8000U 
                                                         == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                         ? 
                                                        __Vtemp139[1U]
                                                         : 
                                                        ((0x4000U 
                                                          == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                          ? 
                                                         __Vtemp140[1U]
                                                          : 
                                                         ((0x2000U 
                                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                           ? 
                                                          __Vtemp141[1U]
                                                           : 
                                                          ((0x1000U 
                                                            == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                            ? 
                                                           __Vtemp142[1U]
                                                            : 
                                                           ((0x800U 
                                                             == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                             ? 
                                                            __Vtemp143[1U]
                                                             : 
                                                            vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U])))))
                                                        : 0U)))) 
                                     << 0x20U) | (QData)((IData)(
                                                                 ((2U 
                                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                                   ? 
                                                                  __Vtemp138[0U]
                                                                   : 
                                                                  ((1U 
                                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                                    ? 
                                                                   ((0x8000U 
                                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                     ? 
                                                                    __Vtemp139[0U]
                                                                     : 
                                                                    ((0x4000U 
                                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                      ? 
                                                                     __Vtemp140[0U]
                                                                      : 
                                                                     ((0x2000U 
                                                                       == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                       ? 
                                                                      __Vtemp141[0U]
                                                                       : 
                                                                      ((0x1000U 
                                                                        == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                        ? 
                                                                       __Vtemp142[0U]
                                                                        : 
                                                                       ((0x800U 
                                                                         == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                         ? 
                                                                        __Vtemp143[0U]
                                                                         : 
                                                                        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U])))))
                                                                    : 0U)))))),64);
        tracep->chgQData(oldp+122,(((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                     ? (0xfffffffffffffffeULL 
                                        & vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1)
                                     : ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)) 
                                        + ((1U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                            ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                            : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9)))),64);
        tracep->chgBit(oldp+124,(((0x100073U == vlSelf->io_imem_data) 
                                  | (0x6bU == vlSelf->io_imem_data))));
        tracep->chgBit(oldp+125,((0x1033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+126,((0x5033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+127,((0x40005033U == (0xfe00707fU 
                                                  & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+128,((0x1013U == (0xfc00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+129,((0x5013U == (0xfc00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+130,((0x40005013U == (0xfc00707fU 
                                                  & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+131,((0x103bU == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+132,((0x503bU == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+133,((0x4000503bU == (0xfe00707fU 
                                                  & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+134,((0x101bU == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+135,((0x501bU == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+136,((0x4000501bU == (0xfe00707fU 
                                                  & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+137,((0x33U == (0xfe00707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+138,((0x3bU == (0xfe00707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+139,((0x13U == (0x707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+140,((0x1bU == (0x707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+141,((0x40000033U == (0xfe00707fU 
                                                  & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+142,((0x4000003bU == (0xfe00707fU 
                                                  & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+143,((0x37U == (0x7fU & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+144,((0x17U == (0x7fU & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+145,((0x4033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+146,((0x6033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+147,((0x7033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+148,((0x4013U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+149,((0x6013U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+150,((0x7013U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+151,((0x2033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+152,((0x3033U == (0xfe00707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+153,((0x2013U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+154,((0x3013U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+155,((0x63U == (0x707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+156,((0x1063U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+157,((0x4063U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+158,((0x5063U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+159,((0x6063U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+160,((0x7063U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+161,((0x6fU == (0x7fU & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+162,((0x67U == (0x707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+163,((3U == (0x707fU & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+164,((0x1003U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+165,((0x2003U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+166,((0x3003U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+167,((0x4003U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+168,((0x5003U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+169,((0x6003U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+170,((0x23U == (0x707fU 
                                            & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+171,((0x1023U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+172,((0x2023U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+173,((0x3023U == (0x707fU 
                                              & vlSelf->io_imem_data))));
        tracep->chgBit(oldp+174,((((0x33U == (0xfe00707fU 
                                              & vlSelf->io_imem_data)) 
                                   | (0x13U == (0x707fU 
                                                & vlSelf->io_imem_data))) 
                                  | (0x37U == (0x7fU 
                                               & vlSelf->io_imem_data)))));
        tracep->chgBit(oldp+175,(((0x3bU == (0xfe00707fU 
                                             & vlSelf->io_imem_data)) 
                                  | (0x1bU == (0x707fU 
                                               & vlSelf->io_imem_data)))));
        tracep->chgBit(oldp+176,(((0x1033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data)) 
                                  | (0x1013U == (0xfc00707fU 
                                                 & vlSelf->io_imem_data)))));
        tracep->chgBit(oldp+177,(((0x5033U == (0xfe00707fU 
                                               & vlSelf->io_imem_data)) 
                                  | (0x5013U == (0xfc00707fU 
                                                 & vlSelf->io_imem_data)))));
        tracep->chgBit(oldp+178,(((0x40005033U == (0xfe00707fU 
                                                   & vlSelf->io_imem_data)) 
                                  | (0x40005013U == 
                                     (0xfc00707fU & vlSelf->io_imem_data)))));
        tracep->chgCData(oldp+179,((((0x5063U == (0x707fU 
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
        tracep->chgCData(oldp+180,((((0x67U == (0x707fU 
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
        tracep->chgCData(oldp+181,((((0x67U == (0x707fU 
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
        tracep->chgBit(oldp+182,((0U != (((0x67U == 
                                           (0x707fU 
                                            & vlSelf->io_imem_data)) 
                                          << 7U) | 
                                         (((0x6fU == 
                                            (0x7fU 
                                             & vlSelf->io_imem_data)) 
                                           << 6U) | 
                                          (((0x7063U 
                                             == (0x707fU 
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
        tracep->chgCData(oldp+183,((((0x6003U == (0x707fU 
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
        tracep->chgBit(oldp+184,((0U != (((0x6003U 
                                           == (0x707fU 
                                               & vlSelf->io_imem_data)) 
                                          << 6U) | 
                                         (((0x5003U 
                                            == (0x707fU 
                                                & vlSelf->io_imem_data)) 
                                           << 5U) | 
                                          (((0x4003U 
                                             == (0x707fU 
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
        tracep->chgCData(oldp+185,((((0x3023U == (0x707fU 
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
        tracep->chgBit(oldp+186,((0U != (((0x3023U 
                                           == (0x707fU 
                                               & vlSelf->io_imem_data)) 
                                          << 3U) | 
                                         (((0x2023U 
                                            == (0x707fU 
                                                & vlSelf->io_imem_data)) 
                                           << 2U) | 
                                          (((0x1023U 
                                             == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                            << 1U) 
                                           | (0x23U 
                                              == (0x707fU 
                                                  & vlSelf->io_imem_data))))))));
        tracep->chgCData(oldp+187,((((0U != (((0x67U 
                                               == (0x707fU 
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
                                     << 1U) | (0U != 
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
        tracep->chgCData(oldp+188,((((0U != (((0x3023U 
                                               == (0x707fU 
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
                                     << 1U) | (0U != 
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
        tracep->chgQData(oldp+189,(((vlSelf->io_imem_data 
                                     >> 0x1fU) ? 0xfffffffffffffULL
                                     : 0ULL)),52);
        tracep->chgSData(oldp+191,((vlSelf->io_imem_data 
                                    >> 0x14U)),12);
        tracep->chgQData(oldp+192,(((((vlSelf->io_imem_data 
                                       >> 0x1fU) ? 0xfffffffffffffULL
                                       : 0ULL) << 0xcU) 
                                    | (QData)((IData)(
                                                      (vlSelf->io_imem_data 
                                                       >> 0x14U))))),64);
        tracep->chgCData(oldp+194,((vlSelf->io_imem_data 
                                    >> 0x19U)),7);
        tracep->chgQData(oldp+195,(((((vlSelf->io_imem_data 
                                       >> 0x1fU) ? 0xfffffffffffffULL
                                       : 0ULL) << 0xcU) 
                                    | (QData)((IData)(
                                                      ((0xfe0U 
                                                        & (vlSelf->io_imem_data 
                                                           >> 0x14U)) 
                                                       | (0x1fU 
                                                          & (vlSelf->io_imem_data 
                                                             >> 7U))))))),64);
        tracep->chgQData(oldp+197,(((vlSelf->io_imem_data 
                                     >> 0x1fU) ? 0x7ffffffffffULL
                                     : 0ULL)),43);
        tracep->chgBit(oldp+199,((1U & (vlSelf->io_imem_data 
                                        >> 7U))));
        tracep->chgCData(oldp+200,((0x3fU & (vlSelf->io_imem_data 
                                             >> 0x19U))),6);
        tracep->chgCData(oldp+201,((0xfU & (vlSelf->io_imem_data 
                                            >> 8U))),4);
        tracep->chgQData(oldp+202,(((((vlSelf->io_imem_data 
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
        tracep->chgIData(oldp+204,(((vlSelf->io_imem_data 
                                     >> 0x1fU) ? 0xffffffffU
                                     : 0U)),32);
        tracep->chgIData(oldp+205,((vlSelf->io_imem_data 
                                    >> 0xcU)),20);
        tracep->chgQData(oldp+206,((((QData)((IData)(
                                                     ((vlSelf->io_imem_data 
                                                       >> 0x1fU)
                                                       ? 0xffffffffU
                                                       : 0U))) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (0xfffff000U 
                                                                  & vlSelf->io_imem_data))))),64);
        tracep->chgCData(oldp+208,((0xffU & (vlSelf->io_imem_data 
                                             >> 0xcU))),8);
        tracep->chgBit(oldp+209,((1U & (vlSelf->io_imem_data 
                                        >> 0x14U))));
        tracep->chgSData(oldp+210,((0x3ffU & (vlSelf->io_imem_data 
                                              >> 0x15U))),10);
        tracep->chgQData(oldp+211,((((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                     | (0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)))
                                     ? (4ULL + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                     : 0ULL)),64);
        tracep->chgQData(oldp+213,((QData)((IData)(
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0xfU))))),64);
        tracep->chgQData(oldp+215,((QData)((IData)(
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0x14U))))),64);
        tracep->chgQData(oldp+217,((QData)((IData)(
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 7U))))),64);
    }
}

void VSimTop___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VSimTop___024root* const __restrict vlSelf = static_cast<VSimTop___024root*>(voidSelf);
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
        vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
        vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    }
}
