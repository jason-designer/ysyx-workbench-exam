// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTop.h for the primary calling header

#include "VSimTop___024unit.h"
#include "VSimTop__Syms.h"

#include "verilated_dpi.h"

//==========

extern "C" void set_halt_ptr(const svOpenArrayHandle a);

VL_INLINE_OPT void VSimTop___024unit____Vdpiimwrap_set_halt_ptr__Vdpioc2_TOP____024unit(const VlUnpacked<CData/*0:0*/, 1> &a) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VSimTop___024unit____Vdpiimwrap_set_halt_ptr__Vdpioc2_TOP____024unit\n"); );
    // Body
    static const int a__Vopenprops__ulims[2] = {0, 0};
    static const VerilatedVarProps a__Vopenprops(VLVT_UINT8, VLVD_IN, VerilatedVarProps::Packed(), 0, 0, VerilatedVarProps::Unpacked(), 1, a__Vopenprops__ulims);
    VerilatedDpiOpenVar a__Vopenarray (&a__Vopenprops, &a);
    set_halt_ptr(&a__Vopenarray);
}

extern "C" void set_gpr_ptr(const svOpenArrayHandle a);

VL_INLINE_OPT void VSimTop___024unit____Vdpiimwrap_set_gpr_ptr__Vdpioc2_TOP____024unit(const VlUnpacked<QData/*63:0*/, 32> &a) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VSimTop___024unit____Vdpiimwrap_set_gpr_ptr__Vdpioc2_TOP____024unit\n"); );
    // Body
    static const int a__Vopenprops__ulims[2] = {0, 31};
    static const VerilatedVarProps a__Vopenprops(VLVT_UINT64, VLVD_IN, VerilatedVarProps::Packed(), 63, 0, VerilatedVarProps::Unpacked(), 1, a__Vopenprops__ulims);
    VerilatedDpiOpenVar a__Vopenarray (&a__Vopenprops, &a);
    set_gpr_ptr(&a__Vopenarray);
}
