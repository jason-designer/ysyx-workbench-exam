#ifndef __DIFFTEST_H__
#define __DIFFTEST_H__

#include "common.h"

typedef struct {
  uint64_t gpr[32];
  uint64_t pc;
} riscv64_CPU_state;
typedef riscv64_CPU_state CPU_state;

extern CPU_state cpu;


#define DIFFTEST_PORT 1234
enum { DIFFTEST_TO_DUT, DIFFTEST_TO_REF };

void difftest_skip_ref();
void init_difftest(char *ref_so_file, uint64_t img_size, int port);
bool difftest_step(uint64_t pc);
bool isa_difftest_checkregs(CPU_state *ref_r, uint64_t pc);
void init_cpu();

#endif
