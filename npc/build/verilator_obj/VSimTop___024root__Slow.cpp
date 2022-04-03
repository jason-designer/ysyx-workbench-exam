// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTop.h for the primary calling header

#include "VSimTop___024root.h"
#include "VSimTop__Syms.h"

#include "verilated_dpi.h"

//==========


void VSimTop___024root___ctor_var_reset(VSimTop___024root* vlSelf);

VSimTop___024root::VSimTop___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    VSimTop___024root___ctor_var_reset(this);
}

void VSimTop___024root::__Vconfigure(VSimTop__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

VSimTop___024root::~VSimTop___024root() {
}

void VSimTop___024unit____Vdpiimwrap_set_gpr_ptr__Vdpioc2_TOP____024unit(const VlUnpacked<QData/*63:0*/, 32> &a);
void VSimTop___024unit____Vdpiimwrap_set_halt_ptr__Vdpioc2_TOP____024unit(const VlUnpacked<CData/*0:0*/, 1> &a);

void VSimTop___024root___initial__TOP__1(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___initial__TOP__1\n"); );
    // Body
    vlSelf->io_imem_en = 1U;
    VSimTop___024unit____Vdpiimwrap_set_gpr_ptr__Vdpioc2_TOP____024unit(vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf);
    VSimTop___024unit____Vdpiimwrap_set_halt_ptr__Vdpioc2_TOP____024unit(vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg);
}

void VSimTop___024root___settle__TOP__3(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___settle__TOP__3\n"); );
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
    vlSelf->io_imem_addr = (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc));
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1 
        = ((IData)(4U) + vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc);
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

void VSimTop___024root___eval_initial(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___eval_initial\n"); );
    // Body
    VSimTop___024root___initial__TOP__1(vlSelf);
    vlSelf->__Vclklast__TOP__clock = vlSelf->clock;
}

void VSimTop___024root___eval_settle(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___eval_settle\n"); );
    // Body
    VSimTop___024root___settle__TOP__3(vlSelf);
}

void VSimTop___024root___final(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___final\n"); );
}

void VSimTop___024root___ctor_var_reset(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_imem_en = VL_RAND_RESET_I(1);
    vlSelf->io_imem_addr = VL_RAND_RESET_Q(64);
    vlSelf->io_imem_data = VL_RAND_RESET_I(32);
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1 = VL_RAND_RESET_I(32);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9 = VL_RAND_RESET_Q(64);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT__alu_out = VL_RAND_RESET_Q(64);
    for (int __Vi0=0; __Vi0<32; ++__Vi0) {
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<1; ++__Vi0) {
        vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}
