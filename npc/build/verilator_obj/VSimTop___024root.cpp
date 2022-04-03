// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTop.h for the primary calling header

#include "VSimTop___024root.h"
#include "VSimTop__Syms.h"

#include "verilated_dpi.h"

//==========

VL_INLINE_OPT void VSimTop___024root___sequent__TOP__2(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___sequent__TOP__2\n"); );
    // Variables
    CData/*0:0*/ __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v0;
    CData/*4:0*/ __Vdlyvdim0__SimTop__DOT__core__DOT__rfu__DOT__rf__v32;
    CData/*0:0*/ __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v32;
    CData/*0:0*/ __Vdlyvval__SimTop__DOT__core__DOT__halt__DOT__halt_reg__v0;
    QData/*63:0*/ __Vdlyvval__SimTop__DOT__core__DOT__rfu__DOT__rf__v32;
    // Body
    if (vlSelf->reset) {
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i = 0x20U;
    }
    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->reset))))) {
        VL_FWRITEF(0x80000002U,"pc=%x inst=%x wen=%1# waddr=%2# wdata=%x\n",
                   64,(QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)),
                   32,vlSelf->io_imem_data,1,(0x13U 
                                              == (0x707fU 
                                                  & vlSelf->io_imem_data)),
                   5,(0x1fU & (vlSelf->io_imem_data 
                               >> 7U)),64,((0x13U == 
                                            (0x707fU 
                                             & vlSelf->io_imem_data))
                                            ? ((0x13U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->io_imem_data))
                                                ? (
                                                   ((0x13U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->io_imem_data))
                                                     ? 
                                                    (((0x13U 
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
                                                     [
                                                     (0x1fU 
                                                      & (vlSelf->io_imem_data 
                                                         >> 0xfU))])
                                                     : 0ULL) 
                                                   + 
                                                   ((1U 
                                                     == 
                                                     ((0x13U 
                                                       == 
                                                       (0x707fU 
                                                        & vlSelf->io_imem_data)) 
                                                      << 4U))
                                                     ? 
                                                    ((((vlSelf->io_imem_data 
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
                                                : 0ULL)
                                            : 0ULL));
    }
    __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v0 = 0U;
    __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 = 0U;
    __Vdlyvval__SimTop__DOT__core__DOT__halt__DOT__halt_reg__v0 
        = ((~ (IData)(vlSelf->reset)) & (0x100073U 
                                         == vlSelf->io_imem_data));
    if (vlSelf->reset) {
        __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v0 = 1U;
    } else {
        __Vdlyvval__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 
            = ((0x13U == (0x707fU & vlSelf->io_imem_data))
                ? ((0U == (0x1fU & (vlSelf->io_imem_data 
                                    >> 7U))) ? 0ULL
                    : ((0x13U == (0x707fU & vlSelf->io_imem_data))
                        ? vlSelf->SimTop__DOT__core__DOT__ieu__DOT__alu_out
                        : 0ULL)) : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
               [(0x1fU & (vlSelf->io_imem_data >> 7U))]);
        __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 = 1U;
        __Vdlyvdim0__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 
            = (0x1fU & (vlSelf->io_imem_data >> 7U));
    }
    vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg[0U] 
        = __Vdlyvval__SimTop__DOT__core__DOT__halt__DOT__halt_reg__v0;
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc = 
        ((IData)(vlSelf->reset) ? 0x80000000U : vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1);
    if (__Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v0) {
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[1U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[2U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[3U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[4U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[5U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[6U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[7U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[8U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[9U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0xaU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0xbU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0xcU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0xdU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0xeU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0xfU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x10U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x11U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x12U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x13U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x14U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x15U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x16U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x17U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x18U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x19U] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x1aU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x1bU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x1cU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x1dU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x1eU] = 0ULL;
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[0x1fU] = 0ULL;
    }
    if (__Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v32) {
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[__Vdlyvdim0__SimTop__DOT__core__DOT__rfu__DOT__rf__v32] 
            = __Vdlyvval__SimTop__DOT__core__DOT__rfu__DOT__rf__v32;
    }
    vlSelf->io_imem_addr = (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc));
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1 
        = ((IData)(4U) + vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc);
}

VL_INLINE_OPT void VSimTop___024root___combo__TOP__4(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___combo__TOP__4\n"); );
    // Body
    vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9 
        = ((2U == ((0x13U == (0x707fU & vlSelf->io_imem_data)) 
                   << 4U)) ? (((QData)((IData)(((vlSelf->io_imem_data 
                                                 >> 0x1fU)
                                                 ? 0xffffffffU
                                                 : 0U))) 
                               << 0x20U) | (QData)((IData)(
                                                           (0xfffff000U 
                                                            & vlSelf->io_imem_data))))
            : ((4U == ((0x13U == (0x707fU & vlSelf->io_imem_data)) 
                       << 4U)) ? ((((vlSelf->io_imem_data 
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
                                                                 >> 7U))))))))
                : ((8U == ((0x13U == (0x707fU & vlSelf->io_imem_data)) 
                           << 4U)) ? ((((vlSelf->io_imem_data 
                                         >> 0x1fU) ? 0xfffffffffffffULL
                                         : 0ULL) << 0xcU) 
                                      | (QData)((IData)(
                                                        ((0xfe0U 
                                                          & (vlSelf->io_imem_data 
                                                             >> 0x14U)) 
                                                         | (0x1fU 
                                                            & (vlSelf->io_imem_data 
                                                               >> 7U))))))
                    : ((0x10U == ((0x13U == (0x707fU 
                                             & vlSelf->io_imem_data)) 
                                  << 4U)) ? ((((vlSelf->io_imem_data 
                                                >> 0x1fU)
                                                ? 0xfffffffffffffULL
                                                : 0ULL) 
                                              << 0xcU) 
                                             | (QData)((IData)(
                                                               (vlSelf->io_imem_data 
                                                                >> 0x14U))))
                        : 0ULL))));
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT__alu_out 
        = ((0x13U == (0x707fU & vlSelf->io_imem_data))
            ? (((0x13U == (0x707fU & vlSelf->io_imem_data))
                 ? (((0x13U == (0x707fU & vlSelf->io_imem_data)) 
                     | (0U == (0x1fU & (vlSelf->io_imem_data 
                                        >> 0xfU))))
                     ? 0ULL : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                    [(0x1fU & (vlSelf->io_imem_data 
                               >> 0xfU))]) : 0ULL) 
               + ((1U == ((0x13U == (0x707fU & vlSelf->io_imem_data)) 
                          << 4U)) ? ((((vlSelf->io_imem_data 
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
                   : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9))
            : 0ULL);
}

void VSimTop___024root___eval(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clock) & (~ (IData)(vlSelf->__Vclklast__TOP__clock)))) {
        VSimTop___024root___sequent__TOP__2(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    VSimTop___024root___combo__TOP__4(vlSelf);
    // Final
    vlSelf->__Vclklast__TOP__clock = vlSelf->clock;
}

QData VSimTop___024root___change_request_1(VSimTop___024root* vlSelf);

VL_INLINE_OPT QData VSimTop___024root___change_request(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___change_request\n"); );
    // Body
    return (VSimTop___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData VSimTop___024root___change_request_1(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void VSimTop___024root___eval_debug_assertions(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
}
#endif  // VL_DEBUG
