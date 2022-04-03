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
    VlWide<4>/*127:0*/ __Vtemp1;
    VlWide<4>/*127:0*/ __Vtemp2;
    VlWide<4>/*127:0*/ __Vtemp3;
    VlWide<4>/*127:0*/ __Vtemp4;
    VlWide<4>/*127:0*/ __Vtemp5;
    VlWide<4>/*127:0*/ __Vtemp6;
    VlWide<4>/*127:0*/ __Vtemp22;
    VlWide<4>/*127:0*/ __Vtemp23;
    VlWide<4>/*127:0*/ __Vtemp24;
    VlWide<4>/*127:0*/ __Vtemp25;
    VlWide<4>/*127:0*/ __Vtemp26;
    VlWide<4>/*127:0*/ __Vtemp27;
    QData/*63:0*/ __Vdlyvval__SimTop__DOT__core__DOT__rfu__DOT__rf__v32;
    // Body
    if (VL_UNLIKELY((1U & (~ (IData)(vlSelf->reset))))) {
        VL_EXTEND_WQ(127,64, __Vtemp1, (((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                         | (0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)))
                                         ? (4ULL + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                         : 0ULL));
        VL_EXTEND_WI(127,1, __Vtemp2, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36));
        VL_EXTEND_WI(127,1, __Vtemp3, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35));
        VL_EXTEND_WQ(127,64, __Vtemp4, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                        & vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp5, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                        | vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp6, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                        ^ vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_FWRITEF(0x80000002U,"pc=%x inst=%x wen=%1# waddr=%2# wdata=%x\n",
                   64,(QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)),
                   32,vlSelf->io_imem_data,1,((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
                                                | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i)) 
                                               | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u)) 
                                              | (0x6fU 
                                                 == 
                                                 (0x7fU 
                                                  & vlSelf->io_imem_data))),
                   5,(0x1fU & (vlSelf->io_imem_data 
                               >> 7U)),64,(((QData)((IData)(
                                                            ((2U 
                                                              == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                              ? 
                                                             __Vtemp1[1U]
                                                              : 
                                                             ((1U 
                                                               == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                               ? 
                                                              ((0x8000U 
                                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                ? 
                                                               __Vtemp2[1U]
                                                                : 
                                                               ((0x4000U 
                                                                 == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                 ? 
                                                                __Vtemp3[1U]
                                                                 : 
                                                                ((0x2000U 
                                                                  == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                  ? 
                                                                 __Vtemp4[1U]
                                                                  : 
                                                                 ((0x1000U 
                                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                   ? 
                                                                  __Vtemp5[1U]
                                                                   : 
                                                                  ((0x800U 
                                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                    ? 
                                                                   __Vtemp6[1U]
                                                                    : 
                                                                   vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U])))))
                                                               : 0U)))) 
                                            << 0x20U) 
                                           | (QData)((IData)(
                                                             ((2U 
                                                               == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                               ? 
                                                              __Vtemp1[0U]
                                                               : 
                                                              ((1U 
                                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                                ? 
                                                               ((0x8000U 
                                                                 == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                 ? 
                                                                __Vtemp2[0U]
                                                                 : 
                                                                ((0x4000U 
                                                                  == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                  ? 
                                                                 __Vtemp3[0U]
                                                                  : 
                                                                 ((0x2000U 
                                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                   ? 
                                                                  __Vtemp4[0U]
                                                                   : 
                                                                  ((0x1000U 
                                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                    ? 
                                                                   __Vtemp5[0U]
                                                                    : 
                                                                   ((0x800U 
                                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                                     ? 
                                                                    __Vtemp6[0U]
                                                                     : 
                                                                    vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U])))))
                                                                : 0U))))));
    }
    if (vlSelf->reset) {
        vlSelf->SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i = 0x20U;
    }
    __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v0 = 0U;
    __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 = 0U;
    __Vdlyvval__SimTop__DOT__core__DOT__halt__DOT__halt_reg__v0 
        = ((~ (IData)(vlSelf->reset)) & ((0x100073U 
                                          == vlSelf->io_imem_data) 
                                         | (0x6bU == vlSelf->io_imem_data)));
    if (vlSelf->reset) {
        __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v0 = 1U;
    } else {
        VL_EXTEND_WQ(127,64, __Vtemp22, (((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                          | (0x40U 
                                             == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)))
                                          ? (4ULL + (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc)))
                                          : 0ULL));
        VL_EXTEND_WI(127,1, __Vtemp23, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36));
        VL_EXTEND_WI(127,1, __Vtemp24, (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_35));
        VL_EXTEND_WQ(127,64, __Vtemp25, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                         & vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp26, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                         | vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        VL_EXTEND_WQ(127,64, __Vtemp27, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                         ^ vlSelf->SimTop__DOT__core__DOT__idu_io_op2));
        __Vdlyvval__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 
            = (((((IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_r) 
                  | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_i)) 
                 | (IData)(vlSelf->SimTop__DOT__core__DOT__idu__DOT__type_u)) 
                | (0x6fU == (0x7fU & vlSelf->io_imem_data)))
                ? ((0U == (0x1fU & (vlSelf->io_imem_data 
                                    >> 7U))) ? 0ULL
                    : (((QData)((IData)(((2U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                          ? __Vtemp22[1U]
                                          : ((1U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                              ? ((0x8000U 
                                                  == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                  ? 
                                                 __Vtemp23[1U]
                                                  : 
                                                 ((0x4000U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp24[1U]
                                                   : 
                                                  ((0x2000U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp25[1U]
                                                    : 
                                                   ((0x1000U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp26[1U]
                                                     : 
                                                    ((0x800U 
                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                      ? 
                                                     __Vtemp27[1U]
                                                      : 
                                                     vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U])))))
                                              : 0U)))) 
                        << 0x20U) | (QData)((IData)(
                                                    ((2U 
                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                      ? 
                                                     __Vtemp22[0U]
                                                      : 
                                                     ((1U 
                                                       == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_fu_code))
                                                       ? 
                                                      ((0x8000U 
                                                        == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                        ? 
                                                       __Vtemp23[0U]
                                                        : 
                                                       ((0x4000U 
                                                         == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                         ? 
                                                        __Vtemp24[0U]
                                                         : 
                                                        ((0x2000U 
                                                          == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                          ? 
                                                         __Vtemp25[0U]
                                                          : 
                                                         ((0x1000U 
                                                           == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                           ? 
                                                          __Vtemp26[0U]
                                                           : 
                                                          ((0x800U 
                                                            == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                            ? 
                                                           __Vtemp27[0U]
                                                            : 
                                                           vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U])))))
                                                       : 0U))))))
                : vlSelf->SimTop__DOT__core__DOT__rfu__DOT__rf
               [(0x1fU & (vlSelf->io_imem_data >> 7U))]);
        __Vdlyvset__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 = 1U;
        __Vdlyvdim0__SimTop__DOT__core__DOT__rfu__DOT__rf__v32 
            = (0x1fU & (vlSelf->io_imem_data >> 7U));
    }
    vlSelf->SimTop__DOT__core__DOT__halt__DOT__halt_reg[0U] 
        = __Vdlyvval__SimTop__DOT__core__DOT__halt__DOT__halt_reg__v0;
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
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc = 
        ((IData)(vlSelf->reset) ? 0x80000000U : (((0x80U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                                  | ((0x40U 
                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code)) 
                                                     | ((0x20U 
                                                         == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                         ? 
                                                        (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                                         >= vlSelf->SimTop__DOT__core__DOT__idu_io_op2)
                                                         : 
                                                        ((0x10U 
                                                          == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                          ? (IData)(vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_36)
                                                          : 
                                                         ((8U 
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
                                                                == vlSelf->SimTop__DOT__core__DOT__idu_io_op2)))))))))
                                                  ? (IData)(
                                                            ((0x80U 
                                                              == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_bu_code))
                                                              ? 
                                                             (0xfffffffffffffffeULL 
                                                              & vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_1)
                                                              : vlSelf->SimTop__DOT__core__DOT__ieu__DOT___bu_jump_pc_T_5))
                                                  : vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1));
    vlSelf->io_imem_addr = (QData)((IData)(vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc));
    vlSelf->SimTop__DOT__core__DOT__ifu__DOT___pc_T_1 
        = ((IData)(4U) + vlSelf->SimTop__DOT__core__DOT__ifu__DOT__pc);
}

VL_INLINE_OPT void VSimTop___024root___combo__TOP__3(VSimTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VSimTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTop___024root___combo__TOP__3\n"); );
    // Variables
    VlWide<4>/*127:0*/ __Vtemp44;
    VlWide<4>/*127:0*/ __Vtemp45;
    VlWide<4>/*127:0*/ __Vtemp46;
    VlWide<4>/*127:0*/ __Vtemp47;
    VlWide<4>/*127:0*/ __Vtemp48;
    VlWide<4>/*127:0*/ __Vtemp49;
    VlWide<4>/*127:0*/ __Vtemp50;
    VlWide<4>/*127:0*/ __Vtemp51;
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
    VL_EXTEND_WI(127,32, __Vtemp44, ((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op1) 
                                     >> (0x1fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WI(127,32, __Vtemp45, ((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op1) 
                                     >> (0x1fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WQ(127,63, __Vtemp46, (0x7fffffffffffffffULL 
                                     & ((QData)((IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op1)) 
                                        << (0x1fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2)))));
    VL_EXTEND_WQ(127,64, __Vtemp47, VL_SHIFTRS_QQI(64,64,6, vlSelf->SimTop__DOT__core__DOT__idu_io_op1, 
                                                   (0x3fU 
                                                    & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WQ(127,64, __Vtemp48, (vlSelf->SimTop__DOT__core__DOT__idu_io_op1 
                                     >> (0x3fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2))));
    VL_EXTEND_WQ(127,64, __Vtemp49, vlSelf->SimTop__DOT__core__DOT__idu_io_op1);
    VL_SHIFTL_WWI(127,127,6, __Vtemp50, __Vtemp49, 
                  (0x3fU & (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_op2)));
    VL_EXTEND_WQ(127,64, __Vtemp51, ((0x10U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
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
            = __Vtemp44[0U];
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U] 
            = __Vtemp44[1U];
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[2U] 
            = __Vtemp44[2U];
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[3U] 
            = (0x7fffffffU & __Vtemp44[3U]);
    } else {
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[0U] 
            = ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                ? __Vtemp45[0U] : ((0x100U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                    ? __Vtemp46[0U]
                                    : ((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                        ? __Vtemp47[0U]
                                        : ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                            ? __Vtemp48[0U]
                                            : ((0x20U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                ? __Vtemp50[0U]
                                                : __Vtemp51[0U])))));
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[1U] 
            = ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                ? __Vtemp45[1U] : ((0x100U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                    ? __Vtemp46[1U]
                                    : ((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                        ? __Vtemp47[1U]
                                        : ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                            ? __Vtemp48[1U]
                                            : ((0x20U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                ? __Vtemp50[1U]
                                                : __Vtemp51[1U])))));
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[2U] 
            = ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                ? __Vtemp45[2U] : ((0x100U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                    ? __Vtemp46[2U]
                                    : ((0x80U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                        ? __Vtemp47[2U]
                                        : ((0x40U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                            ? __Vtemp48[2U]
                                            : ((0x20U 
                                                == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                ? __Vtemp50[2U]
                                                : __Vtemp51[2U])))));
        vlSelf->SimTop__DOT__core__DOT__ieu__DOT___alu_out_T_58[3U] 
            = (0x7fffffffU & ((0x200U == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                               ? __Vtemp45[3U] : ((0x100U 
                                                   == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                   ? 
                                                  __Vtemp46[3U]
                                                   : 
                                                  ((0x80U 
                                                    == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                    ? 
                                                   __Vtemp47[3U]
                                                    : 
                                                   ((0x40U 
                                                     == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                     ? 
                                                    __Vtemp48[3U]
                                                     : 
                                                    ((0x20U 
                                                      == (IData)(vlSelf->SimTop__DOT__core__DOT__idu_io_decode_info_alu_code))
                                                      ? 
                                                     __Vtemp50[3U]
                                                      : 
                                                     __Vtemp51[3U]))))));
    }
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
    VSimTop___024root___combo__TOP__3(vlSelf);
    vlSelf->__Vm_traceActivity[2U] = 1U;
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
