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
        tracep->chgBit(oldp+69,(vlSelf->clock));
        tracep->chgBit(oldp+70,(vlSelf->reset));
        tracep->chgBit(oldp+71,(vlSelf->io_imem_en));
        tracep->chgQData(oldp+72,(vlSelf->io_imem_addr),64);
        tracep->chgIData(oldp+74,(vlSelf->io_imem_data),32);
        tracep->chgBit(oldp+75,((0x13U == (0x707fU 
                                           & vlSelf->io_imem_data))));
        tracep->chgCData(oldp+76,((0x1fU & (vlSelf->io_imem_data 
                                            >> 0xfU))),5);
        tracep->chgCData(oldp+77,((0x1fU & (vlSelf->io_imem_data 
                                            >> 0x14U))),5);
        tracep->chgCData(oldp+78,((0x1fU & (vlSelf->io_imem_data 
                                            >> 7U))),5);
        tracep->chgQData(oldp+79,((((0x13U == (0x707fU 
                                               & vlSelf->io_imem_data)) 
                                    | (0U == (0x1fU 
                                              & (vlSelf->io_imem_data 
                                                 >> 0xfU))))
                                    ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                   [(0x1fU & (vlSelf->io_imem_data 
                                              >> 0xfU))])),64);
        tracep->chgQData(oldp+81,(((0U == (0x1fU & 
                                           (vlSelf->io_imem_data 
                                            >> 0x14U)))
                                    ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                   [(0x1fU & (vlSelf->io_imem_data 
                                              >> 0x14U))])),64);
        tracep->chgQData(oldp+83,(((0x13U == (0x707fU 
                                              & vlSelf->io_imem_data))
                                    ? (((0x13U == (0x707fU 
                                                   & vlSelf->io_imem_data)) 
                                        | (0U == (0x1fU 
                                                  & (vlSelf->io_imem_data 
                                                     >> 0xfU))))
                                        ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                       [(0x1fU & (vlSelf->io_imem_data 
                                                  >> 0xfU))])
                                    : 0ULL)),64);
        tracep->chgQData(oldp+85,(((1U == ((0x13U == 
                                            (0x707fU 
                                             & vlSelf->io_imem_data)) 
                                           << 4U)) ? 
                                   ((((vlSelf->io_imem_data 
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
                                                                   >> 0x14U))))))))
                                    : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9)),64);
        tracep->chgQData(oldp+87,(((0x13U == (0x707fU 
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
                                           + ((1U == 
                                               ((0x13U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelf->io_imem_data)) 
                                                << 4U))
                                               ? ((
                                                   ((vlSelf->io_imem_data 
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
        tracep->chgBit(oldp+89,((0x100073U == vlSelf->io_imem_data)));
        tracep->chgCData(oldp+90,(((0x13U == (0x707fU 
                                              & vlSelf->io_imem_data)) 
                                   << 4U)),6);
        tracep->chgQData(oldp+91,(((vlSelf->io_imem_data 
                                    >> 0x1fU) ? 0xfffffffffffffULL
                                    : 0ULL)),52);
        tracep->chgSData(oldp+93,((vlSelf->io_imem_data 
                                   >> 0x14U)),12);
        tracep->chgQData(oldp+94,(((((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0xfffffffffffffULL
                                      : 0ULL) << 0xcU) 
                                   | (QData)((IData)(
                                                     (vlSelf->io_imem_data 
                                                      >> 0x14U))))),64);
        tracep->chgCData(oldp+96,((vlSelf->io_imem_data 
                                   >> 0x19U)),7);
        tracep->chgQData(oldp+97,(((((vlSelf->io_imem_data 
                                      >> 0x1fU) ? 0xfffffffffffffULL
                                      : 0ULL) << 0xcU) 
                                   | (QData)((IData)(
                                                     ((0xfe0U 
                                                       & (vlSelf->io_imem_data 
                                                          >> 0x14U)) 
                                                      | (0x1fU 
                                                         & (vlSelf->io_imem_data 
                                                            >> 7U))))))),64);
        tracep->chgQData(oldp+99,(((vlSelf->io_imem_data 
                                    >> 0x1fU) ? 0x7ffffffffffULL
                                    : 0ULL)),43);
        tracep->chgBit(oldp+101,((1U & (vlSelf->io_imem_data 
                                        >> 7U))));
        tracep->chgCData(oldp+102,((0x3fU & (vlSelf->io_imem_data 
                                             >> 0x19U))),6);
        tracep->chgCData(oldp+103,((0xfU & (vlSelf->io_imem_data 
                                            >> 8U))),4);
        tracep->chgQData(oldp+104,(((((vlSelf->io_imem_data 
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
        tracep->chgIData(oldp+106,(((vlSelf->io_imem_data 
                                     >> 0x1fU) ? 0xffffffffU
                                     : 0U)),32);
        tracep->chgIData(oldp+107,((vlSelf->io_imem_data 
                                    >> 0xcU)),20);
        tracep->chgQData(oldp+108,((((QData)((IData)(
                                                     ((vlSelf->io_imem_data 
                                                       >> 0x1fU)
                                                       ? 0xffffffffU
                                                       : 0U))) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (0xfffff000U 
                                                                  & vlSelf->io_imem_data))))),64);
        tracep->chgCData(oldp+110,((0xffU & (vlSelf->io_imem_data 
                                             >> 0xcU))),8);
        tracep->chgBit(oldp+111,((1U & (vlSelf->io_imem_data 
                                        >> 0x14U))));
        tracep->chgSData(oldp+112,((0x3ffU & (vlSelf->io_imem_data 
                                              >> 0x15U))),10);
        tracep->chgQData(oldp+113,(((((vlSelf->io_imem_data 
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
        tracep->chgQData(oldp+115,(((0x13U == (0x707fU 
                                               & vlSelf->io_imem_data))
                                     ? (((0x13U == 
                                          (0x707fU 
                                           & vlSelf->io_imem_data))
                                          ? (((0x13U 
                                               == (0x707fU 
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
                                          : 0ULL) + 
                                        ((1U == ((0x13U 
                                                  == 
                                                  (0x707fU 
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
        tracep->chgQData(oldp+117,((QData)((IData)(
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0xfU))))),64);
        tracep->chgQData(oldp+119,((QData)((IData)(
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0x14U))))),64);
        tracep->chgQData(oldp+121,((QData)((IData)(
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
    }
}
