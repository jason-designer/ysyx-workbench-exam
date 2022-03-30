#ifndef ARCH_H__
#define ARCH_H__

struct Context {
  // TODO: fix the order of these members to match trap.S
  void *pdir;
  uintptr_t gpr[31];
  uintptr_t mcause;
  uintptr_t mstatus;
  uintptr_t mepc;
};

#define GPR1 gpr[16]  // a7
#define GPR2 gpr[9]   // a0
#define GPR3 gpr[10]  // a1
#define GPR4 gpr[11]  // a2
#define GPRx gpr[9]   // a0
#endif
