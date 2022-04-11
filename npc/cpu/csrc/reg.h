#ifndef __REG_H__
#define __REG_H__

#include "common.h"
#include "verilated_dpi.h"

extern uint64_t* cpu_gpr;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r);
extern uint64_t cpu_pc;
extern "C" void read_pc(long long pc);

extern const char *regs[];
void isa_reg_display();
void isa_reg_update(uint64_t pc, uint64_t* gpr);


#endif