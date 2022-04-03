#include <isa.h>
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>


void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  uint8_t* src;
  uint8_t* dst;
  if(direction == DIFFTEST_TO_REF){
    src = (uint8_t*)buf;
    dst = guest_to_host(addr);
  }
  else if(direction == DIFFTEST_TO_DUT){
    src = guest_to_host(addr);
    dst = (uint8_t*)buf;
  }else assert(0);
  for(int i = 0; i < n; i++) dst[i] = src[i];
}

void difftest_regcpy(void *dut, bool direction) {
  CPU_state* src;
  CPU_state* dst;
  if(direction == DIFFTEST_TO_REF){
    src = (CPU_state*)dut;
    dst = &cpu;
  }
  else if(direction == DIFFTEST_TO_DUT){
    src = &cpu;
    dst = (CPU_state*)dut;
  }else assert(0);
  for(int i = 0; i < 32; i++) dst->gpr[i] = src->gpr[i];
  dst->pc = src->pc;
}

void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

void difftest_raise_intr(word_t NO) {
  assert(0);
}

void difftest_init(int port) {
  /* Perform ISA dependent initialization. */
  init_isa();
}
