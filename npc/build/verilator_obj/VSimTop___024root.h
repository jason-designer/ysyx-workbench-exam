// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VSimTop.h for the primary calling header

#ifndef VERILATED_VSIMTOP___024ROOT_H_
#define VERILATED_VSIMTOP___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class VSimTop__Syms;
class VSimTop_VerilatedVcd;
class VSimTop___024unit;


//----------

VL_MODULE(VSimTop___024root) {
  public:
    // CELLS
    VSimTop___024unit* __PVT____024unit;

    // PORTS
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_OUT8(io_imem_en,0,0);
    VL_IN(io_imem_data,31,0);
    VL_OUT64(io_imem_addr,63,0);

    // LOCAL SIGNALS
    IData/*31:0*/ SimTop__DOT__core__DOT__ifu__DOT__pc;
    IData/*31:0*/ SimTop__DOT__core__DOT__ifu__DOT___pc_T_1;
    IData/*31:0*/ SimTop__DOT__core__DOT__rfu__DOT__unnamedblk1__DOT__i;
    QData/*63:0*/ SimTop__DOT__core__DOT__idu__DOT___imm_T_9;
    QData/*63:0*/ SimTop__DOT__core__DOT__ieu__DOT__alu_out;
    VlUnpacked<QData/*63:0*/, 32> SimTop__DOT__core__DOT__rfu__DOT__rf;
    VlUnpacked<CData/*0:0*/, 1> SimTop__DOT__core__DOT__halt__DOT__halt_reg;

    // LOCAL VARIABLES
    CData/*0:0*/ __Vclklast__TOP__clock;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    VSimTop__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(VSimTop___024root);  ///< Copying not allowed
  public:
    VSimTop___024root(const char* name);
    ~VSimTop___024root();

    // INTERNAL METHODS
    void __Vconfigure(VSimTop__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
