#ifndef __REG_H__
#define __REG_H__

#include "common.h"
#include "verilated_dpi.h"

extern uint64_t* cpu_gpr;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r);

extern const char *regs[];
void isa_reg_display();



#endif