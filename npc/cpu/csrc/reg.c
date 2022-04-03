#include "reg.h"

uint64_t *cpu_gpr = NULL;
void set_gpr_ptr(const svOpenArrayHandle r) {
  cpu_gpr = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  int i;
  for(i=0;i<32;i++)
  {
    printf("%3s ",regs[i]);
    printf("0x%016lx  ",cpu_gpr[i]);
    if(i%4==3) printf("\n");
  }
}
