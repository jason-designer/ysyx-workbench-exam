#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
  printf(" pc 0x%016lx\n",cpu.pc);
  int i;
  for(i=0;i<32;i++)
  {
    printf("%3s ",regs[i]);
    printf("0x%016lx  ",cpu.gpr[i]);
    if(i%4==3) printf("\n");
  }
  printf("mtvec  :%016lx\n",cpu.mtvec);
  printf("mepc   :%016lx\n",cpu.mepc);
  printf("mstatus:%016lx\n",cpu.mstatus);
	printf("mcause :%016lx\n",cpu.mcause);
  return;
}

word_t isa_reg_str2val(const char *s, bool *success) {
  int i;
  if(strcmp(s+1,"pc")==0){
		*success=1;
		return cpu.pc;
	}
  for(i=0;i<32;i++){
    if(strcmp(regs[i],s+1)==0) break;
  }
  if(i==32){
    printf("can not find reg'name!!! string wrong, check it\n");
    *success=0;
    return 0;
  }
  else{
    *success = true;
    return cpu.gpr[i];
  }
}
