// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at //home/zgs/project/ysyx-workbench/npc/build/vsrc/RegFile.v:2:30
    extern void set_gpr_ptr(const svOpenArrayHandle a);
    // DPI import at //home/zgs/project/ysyx-workbench/npc/build/vsrc/Halt.v:2:30
    extern void set_halt_ptr(const svOpenArrayHandle a);

#ifdef __cplusplus
}
#endif
