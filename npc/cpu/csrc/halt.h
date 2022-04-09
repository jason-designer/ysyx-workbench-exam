#ifndef __HALT_H__
#define __HALT_H__

#include "common.h"
#include "verilated_dpi.h"

extern uint64_t cpu_halt;
extern "C" void read_halt(unsigned char halt);

#endif