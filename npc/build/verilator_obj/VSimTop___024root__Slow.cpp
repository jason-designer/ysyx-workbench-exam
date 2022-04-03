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

void VSimTop___024root___settle__TOP__4(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___settle__TOP__4\n"); );
    // Variables
    VlWide<4>/*127:0*/ __Vtemp66;
    VlWide<4>/*127:0*/ __Vtemp67;
    VlWide<4>/*127:0*/ __Vtemp68;
    VlWide<4>/*127:0*/ __Vtemp69;
    VlWide<4>/*127:0*/ __Vtemp70;
    VlWide<4>/*127:0*/ __Vtemp71;
    VlWide<4>/*127:0*/ __Vtemp72;
    VlWide<4>/*127:0*/ __Vtemp73;
    QData/*63:0*/ SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_6;
    // Body
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw 
        = ((0x103bU == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x101bU == (0xfe00707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw 
        = ((0x503bU == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x501bU == (0xfe00707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw 
        = ((0x4000503bU == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x4000501bU == (0xfe00707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor 
        = ((0x4033U == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x4013U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or 
        = ((0x6033U == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x6013U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and 
        = ((0x7033U == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x7013U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt 
        = ((0x2033U == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x2013U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu 
        = ((0x3033U == (0xfe00707fU & vlSelf->io_imem_data)) 
           | (0x3013U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo 
        = ((((0x40005033U == (0xfe00707fU & vlSelf->io_imem_data)) 
             | (0x40005013U == (0xfc00707fU & vlSelf->io_imem_data))) 
            << 7U) | ((((0x5033U == (0xfe00707fU & vlSelf->io_imem_data)) 
                        | (0x5013U == (0xfc00707fU 
                                       & vlSelf->io_imem_data))) 
                       << 6U) | ((((0x1033U == (0xfe00707fU 
                                                & vlSelf->io_imem_data)) 
                                   | (0x1013U == (0xfc00707fU 
                                                  & vlSelf->io_imem_data))) 
                                  << 5U) | (((0x17U 
                                              == (0x7fU 
                                                  & vlSelf->io_imem_data)) 
                                             << 4U) 
                                            | (((0x4000003bU 
                                                 == 
                                                 (0xfe00707fU 
                                                  & vlSelf->io_imem_data)) 
                                                << 3U) 
                                               | (((0x40000033U 
                                                    == 
                                                    (0xfe00707fU 
                                                     & vlSelf->io_imem_data)) 
                                                   << 2U) 
                                                  | ((((0x3bU 
                                                        == 
                                                        (0xfe00707fU 
                                                         & vlSelf->io_imem_data)) 
                                                       | (0x1bU 
                                                          == 
                                                          (0x707fU 
                                                           & vlSelf->io_imem_data))) 
                                                      << 1U) 
                                                     | (((0x33U 
                                                          == 
                                                          (0xfe00707fU 
                                                           & vlSelf->io_imem_data)) 
                                                         | (0x13U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelf->io_imem_data))) 
                                                        | (0x37U 
                                                           == 
                                                           (0x7fU 
                                                            & vlSelf->io_imem_data))))))))));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j 
        = ((((vlSelf->io_imem_data >> 0x1fU) ? 0x7ffffffffffULL
              : 0ULL) << 0x15U) | (QData)((IData)((
                                                   (0x100000U 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0xbU)) 
                                                   | ((0xff000U 
                                                       & vlSelf->io_imem_data) 
                                                      | ((0x800U 
                                                          & (vlSelf->io_imem_data 
                                                             >> 9U)) 
                                                         | (0x7feU 
                                                            & (vlSelf->io_imem_data 
                                                               >> 0x14U))))))));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s 
        = ((((0x23U == (0x707fU & vlSelf->io_imem_data)) 
             | (0x1023U == (0x707fU & vlSelf->io_imem_data))) 
            | (0x2023U == (0x707fU & vlSelf->io_imem_data))) 
           | (0x3023U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b 
        = ((((((0x63U == (0x707fU & vlSelf->io_imem_data)) 
               | (0x1063U == (0x707fU & vlSelf->io_imem_data))) 
              | (0x4063U == (0x707fU & vlSelf->io_imem_data))) 
             | (0x5063U == (0x707fU & vlSelf->io_imem_data))) 
            | (0x6063U == (0x707fU & vlSelf->io_imem_data))) 
           | (0x7063U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u 
        = ((0x37U == (0x7fU & vlSelf->io_imem_data)) 
           | (0x17U == (0x7fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i 
        = ((((((((((((((((((((0x1013U == (0xfc00707fU 
                                          & vlSelf->io_imem_data)) 
                             | (0x5013U == (0xfc00707fU 
                                            & vlSelf->io_imem_data))) 
                            | (0x40005013U == (0xfc00707fU 
                                               & vlSelf->io_imem_data))) 
                           | (0x101bU == (0xfe00707fU 
                                          & vlSelf->io_imem_data))) 
                          | (0x501bU == (0xfe00707fU 
                                         & vlSelf->io_imem_data))) 
                         | (0x4000501bU == (0xfe00707fU 
                                            & vlSelf->io_imem_data))) 
                        | (0x13U == (0x707fU & vlSelf->io_imem_data))) 
                       | (0x1bU == (0x707fU & vlSelf->io_imem_data))) 
                      | (0x4013U == (0x707fU & vlSelf->io_imem_data))) 
                     | (0x6013U == (0x707fU & vlSelf->io_imem_data))) 
                    | (0x7013U == (0x707fU & vlSelf->io_imem_data))) 
                   | (0x2013U == (0x707fU & vlSelf->io_imem_data))) 
                  | (0x3013U == (0x707fU & vlSelf->io_imem_data))) 
                 | (3U == (0x707fU & vlSelf->io_imem_data))) 
                | (0x1003U == (0x707fU & vlSelf->io_imem_data))) 
               | (0x2003U == (0x707fU & vlSelf->io_imem_data))) 
              | (0x3003U == (0x707fU & vlSelf->io_imem_data))) 
             | (0x4003U == (0x707fU & vlSelf->io_imem_data))) 
            | (0x5003U == (0x707fU & vlSelf->io_imem_data))) 
           | (0x6003U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r 
        = ((((((((((((((((0x1033U == (0xfe00707fU & vlSelf->io_imem_data)) 
                         | (0x5033U == (0xfe00707fU 
                                        & vlSelf->io_imem_data))) 
                        | (0x40005033U == (0xfe00707fU 
                                           & vlSelf->io_imem_data))) 
                       | (0x103bU == (0xfe00707fU & vlSelf->io_imem_data))) 
                      | (0x503bU == (0xfe00707fU & vlSelf->io_imem_data))) 
                     | (0x4000503bU == (0xfe00707fU 
                                        & vlSelf->io_imem_data))) 
                    | (0x33U == (0xfe00707fU & vlSelf->io_imem_data))) 
                   | (0x3bU == (0xfe00707fU & vlSelf->io_imem_data))) 
                  | (0x40000033U == (0xfe00707fU & vlSelf->io_imem_data))) 
                 | (0x4000003bU == (0xfe00707fU & vlSelf->io_imem_data))) 
                | (0x4033U == (0xfe00707fU & vlSelf->io_imem_data))) 
               | (0x6033U == (0xfe00707fU & vlSelf->io_imem_data))) 
              | (0x7033U == (0xfe00707fU & vlSelf->io_imem_data))) 
             | (0x2033U == (0xfe00707fU & vlSelf->io_imem_data))) 
            | (0x3033U == (0xfe00707fU & vlSelf->io_imem_data))) 
           | (0x67U == (0x707fU & vlSelf->io_imem_data)));
    vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code 
        = ((((0x67U == (0x707fU & vlSelf->io_imem_data)) 
             << 7U) | (((0x6fU == (0x7fU & vlSelf->io_imem_data)) 
                        << 6U) | (((0x7063U == (0x707fU 
                                                & vlSelf->io_imem_data)) 
                                   << 5U) | ((0x6063U 
                                              == (0x707fU 
                                                  & vlSelf->io_imem_data)) 
                                             << 4U)))) 
           | (((0x5063U == (0x707fU & vlSelf->io_imem_data)) 
               << 3U) | (((0x4063U == (0x707fU & vlSelf->io_imem_data)) 
                          << 2U) | (((0x1063U == (0x707fU 
                                                  & vlSelf->io_imem_data)) 
                                     << 1U) | (0x63U 
                                               == (0x707fU 
                                                   & vlSelf->io_imem_data))))));
    vlSelf->io_imem_addr = (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc));
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1 
        = ((IData)(4U) + vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc);
    vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code 
        = ((((0U != (((0x3023U == (0x707fU & vlSelf->io_imem_data)) 
                      << 3U) | (((0x2023U == (0x707fU 
                                              & vlSelf->io_imem_data)) 
                                 << 2U) | (((0x1023U 
                                             == (0x707fU 
                                                 & vlSelf->io_imem_data)) 
                                            << 1U) 
                                           | (0x23U 
                                              == (0x707fU 
                                                  & vlSelf->io_imem_data)))))) 
             << 3U) | ((0U != (((0x6003U == (0x707fU 
                                             & vlSelf->io_imem_data)) 
                                << 6U) | (((0x5003U 
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
                                                        & vlSelf->io_imem_data))))))))) 
                       << 2U)) | (((0U != (((0x67U 
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
                                                                   | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo))))))))))));
    vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code 
        = (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu) 
            << 0xfU) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt) 
                         << 0xeU) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and) 
                                      << 0xdU) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or) 
                                                   << 0xcU) 
                                                  | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor) 
                                                      << 0xbU) 
                                                     | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw) 
                                                         << 0xaU) 
                                                        | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw) 
                                                            << 9U) 
                                                           | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw) 
                                                               << 8U) 
                                                              | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo)))))))));
    vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en = 
        ((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
           | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i)) 
          | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s)) 
         | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b));
    vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en = 
        (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
          | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s)) 
         | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b));
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type 
        = (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
            << 5U) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i) 
                       << 4U) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s) 
                                  << 3U) | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b) 
                                             << 2U) 
                                            | (((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u) 
                                                << 1U) 
                                               | (0x6fU 
                                                  == 
                                                  (0x7fU 
                                                   & vlSelf->io_imem_data)))))));
    vlSelf->SimTop__DOT__core__DOT__idu_io_op1 = ((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en)
                                                   ? 
                                                  ((1U 
                                                    & ((~ (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en)) 
                                                       | (0U 
                                                          == 
                                                          (0x1fU 
                                                           & (vlSelf->io_imem_data 
                                                              >> 0xfU)))))
                                                    ? 0ULL
                                                    : 
                                                   vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                                   [
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0xfU))])
                                                   : 0ULL);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9 
        = ((2U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
            ? (((QData)((IData)(((vlSelf->io_imem_data 
                                  >> 0x1fU) ? 0xffffffffU
                                  : 0U))) << 0x20U) 
               | (QData)((IData)((0xfffff000U & vlSelf->io_imem_data))))
            : ((4U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                ? ((((vlSelf->io_imem_data >> 0x1fU)
                      ? 0x7ffffffffffULL : 0ULL) << 0xdU) 
                   | (QData)((IData)(((0x1000U & (vlSelf->io_imem_data 
                                                  >> 0x13U)) 
                                      | ((0x800U & 
                                          (vlSelf->io_imem_data 
                                           << 4U)) 
                                         | ((0x7e0U 
                                             & (vlSelf->io_imem_data 
                                                >> 0x14U)) 
                                            | (0x1eU 
                                               & (vlSelf->io_imem_data 
                                                  >> 7U))))))))
                : ((8U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                    ? ((((vlSelf->io_imem_data >> 0x1fU)
                          ? 0xfffffffffffffULL : 0ULL) 
                        << 0xcU) | (QData)((IData)(
                                                   ((0xfe0U 
                                                     & (vlSelf->io_imem_data 
                                                        >> 0x14U)) 
                                                    | (0x1fU 
                                                       & (vlSelf->io_imem_data 
                                                          >> 7U))))))
                    : ((0x10U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                        ? ((((vlSelf->io_imem_data 
                              >> 0x1fU) ? 0xfffffffffffffULL
                              : 0ULL) << 0xcU) | (QData)((IData)(
                                                                 (vlSelf->io_imem_data 
                                                                  >> 0x14U))))
                        : 0ULL))));
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___bu_jump_pc_T_5 
        = ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)) 
           + ((1U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
               ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
               : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9));
    vlSelf->SimTop__DOT__core__DOT__idu_io_op2 = ((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en)
                                                   ? 
                                                  ((1U 
                                                    & ((~ (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en)) 
                                                       | (0U 
                                                          == 
                                                          (0x1fU 
                                                           & (vlSelf->io_imem_data 
                                                              >> 0x14U)))))
                                                    ? 0ULL
                                                    : 
                                                   vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
                                                   [
                                                   (0x1fU 
                                                    & (vlSelf->io_imem_data 
                                                       >> 0x14U))])
                                                   : 
                                                  ((1U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type))
                                                    ? vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j
                                                    : vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9));
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35 
        = VL_LTS_IQQ(1,64,64, vlSelf->SimTop__DOT__core__DOT__idu_io_op1, vlSelf->SimTop__DOT__core__DOT__idu_io_op2);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36 
        = (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
           < vlSelf->SimTop__DOT__core__DOT__idu_io_op2);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1 
        = (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
           + vlSelf->SimTop__DOT__core__DOT__idu_io_op2);
    SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_6 
        = (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
           - vlSelf->SimTop__DOT__core__DOT__idu_io_op2);
    VL_EXTEND_WI(127,32, __Vtemp66, ((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op1) 
                                     >> (0x1fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WI(127,32, __Vtemp67, ((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op1) 
                                     >> (0x1fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WQ(127,63, __Vtemp68, (0x7fffffffffffffffULL 
                                     & ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op1)) 
                                        << (0x1fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2)))));
    VL_EXTEND_WQ(127,64, __Vtemp69, VL_SHIFTRS_QQI(64,64,6, vlSelf->SimTop__DOT__core__DOT__idu_io_op1, 
                                                   (0x3fU 
                                                    & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WQ(127,64, __Vtemp70, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                     >> (0x3fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WQ(127,64, __Vtemp71, vlSelf->SimTop__DOT__core__DOT__idu_io_op1);
    VL_SHIFTL_WWI(127,127,6, __Vtemp72, __Vtemp71, 
                  (0x3fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2)));
    VL_EXTEND_WQ(127,64, __Vtemp73, ((0x10U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                      ? (vlSelf->SimTop__DOT__core__DOT__idu_io_op2 
                                         + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                      : ((8U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                          ? (QData)((IData)(SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_6))
                                          : ((4U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                              ? SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_6
                                              : ((2U 
                                                  == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                  ? (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1))
                                                  : 
                                                 ((1U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1
                                                   : 0ULL))))));
    if ((0x400U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))) {
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U] 
            = __Vtemp66[0U];
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U] 
            = __Vtemp66[1U];
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[2U] 
            = __Vtemp66[2U];
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[3U] 
            = (0x7fffffffU & __Vtemp66[3U]);
    } else {
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U] 
            = ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                ? __Vtemp67[0U] : ((0x100U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                    ? __Vtemp68[0U]
                                    : ((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                        ? __Vtemp69[0U]
                                        : ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                            ? __Vtemp70[0U]
                                            : ((0x20U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                ? __Vtemp72[0U]
                                                : __Vtemp73[0U])))));
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U] 
            = ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                ? __Vtemp67[1U] : ((0x100U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                    ? __Vtemp68[1U]
                                    : ((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                        ? __Vtemp69[1U]
                                        : ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                            ? __Vtemp70[1U]
                                            : ((0x20U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                ? __Vtemp72[1U]
                                                : __Vtemp73[1U])))));
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[2U] 
            = ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                ? __Vtemp67[2U] : ((0x100U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                    ? __Vtemp68[2U]
                                    : ((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                        ? __Vtemp69[2U]
                                        : ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                            ? __Vtemp70[2U]
                                            : ((0x20U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                ? __Vtemp72[2U]
                                                : __Vtemp73[2U])))));
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[3U] 
            = (0x7fffffffU & ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                               ? __Vtemp67[3U] : ((0x100U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp68[3U]
                                                   : 
                                                  ((0x80U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp69[3U]
                                                    : 
                                                   ((0x40U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp70[3U]
                                                     : 
                                                    ((0x20U 
                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                      ? 
                                                     __Vtemp72[3U]
                                                      : 
                                                     __Vtemp73[3U]))))));
    }
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
    VSimTop___024root___settle__TOP__4(vlSelf);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
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
    vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code = VL_RAND_RESET_I(4);
    vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code = VL_RAND_RESET_I(16);
    vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code = VL_RAND_RESET_I(8);
    vlSelf->SimTop__DOT__core__DOT__idu_io_rs1_en = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu_io_rs2_en = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu_io_op1 = VL_RAND_RESET_Q(64);
    vlSelf->SimTop__DOT__core__DOT__idu_io_op2 = VL_RAND_RESET_Q(64);
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1 = VL_RAND_RESET_I(32);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sllw = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_srlw = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sraw = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_xor = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_or = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_and = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_slt = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_sltu = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__alu_code_lo = VL_RAND_RESET_I(8);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_s = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_b = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__inst_type = VL_RAND_RESET_I(6);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT__imm_j = VL_RAND_RESET_Q(64);
    vlSelf->SimTop__DOT__core__DOT__idu__DOT___imm_T_9 = VL_RAND_RESET_Q(64);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1 = VL_RAND_RESET_Q(64);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35 = VL_RAND_RESET_I(1);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36 = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(127, vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58);
    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___bu_jump_pc_T_5 = VL_RAND_RESET_Q(64);
    for (int __Vi0=0; __Vi0<32; ++__Vi0) {
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<1; ++__Vi0) {
        vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0=0; __Vi0<3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}
