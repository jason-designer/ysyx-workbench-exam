#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool res = true;
	if(ref_r->pc != pc) {
		printf("pc different after executing inst at pc = %lx , right = %lx  wrong = %lx  \n", pc, ref_r->pc, pc);
		res=false;
	}
	for(int i=0;i<32;i++){
		if(ref_r->gpr[i] != cpu.gpr[i]){
			printf("gpr[%2d] different after executing inst at pc = %lx , right = %lx  wrong = %lx  \n", i, pc, ref_r->gpr[i], cpu.gpr[i]);
			res=false;
		}
	}
	return res;
}

void isa_difftest_attach() {
}
