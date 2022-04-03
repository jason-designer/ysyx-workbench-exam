#include "difftest.h"
#include <dlfcn.h>
#include "memory.h"
#include "reg.h"

CPU_state cpu = {};

void (*ref_difftest_memcpy)(uint64_t addr, void *buf, uint64_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
void (*ref_difftest_raise_intr)(uint64_t NO) = NULL;

static bool is_skip_ref = false;
static int skip_dut_nr_inst = 0;

void difftest_skip_ref() {
  is_skip_ref = true;
  skip_dut_nr_inst = 0;
}

void init_difftest(char *ref_so_file, uint64_t img_size, int port) {
  assert(ref_so_file != NULL);
  
  void *handle;
  handle = (void*)dlopen(ref_so_file, RTLD_LAZY);
  assert(handle);

  ref_difftest_memcpy = (void(*)(uint64_t, void*, uint64_t, bool))dlsym(handle, "difftest_memcpy");
  assert(ref_difftest_memcpy);

  ref_difftest_regcpy = (void (*)(void*, bool))dlsym(handle, "difftest_regcpy");
  assert(ref_difftest_regcpy);

  ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
  assert(ref_difftest_exec);

  ref_difftest_raise_intr = (void (*)(uint64_t))dlsym(handle, "difftest_raise_intr");
  assert(ref_difftest_raise_intr);

  void (*ref_difftest_init)(int) = (void (*)(int))dlsym(handle, "difftest_init");
  assert(ref_difftest_init);

  Log("Differential testing: %s", ASNI_FMT("ON", ASNI_FG_GREEN));
  Log("The result of every instruction will be compared with %s. "
      "This will help you a lot for debugging, but also significantly reduce the performance. "
      "If it is not necessary, you can turn it off in menuconfig.", ref_so_file);

  ref_difftest_init(port);
  ref_difftest_memcpy(RESET_VECTOR, mem, img_size, DIFFTEST_TO_REF);
  ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}


bool difftest_step(uint64_t pc) {
  CPU_state ref_r;

  if (is_skip_ref) {
    // to skip the checking of an instruction, just copy the reg state to reference design
    ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
    is_skip_ref = false;
    return true;
  }

  ref_difftest_exec(1);
  ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);

  return isa_difftest_checkregs(&ref_r, pc);
}


bool isa_difftest_checkregs(CPU_state *ref_r, uint64_t pc) {
  printf("check pc=%lx\n",pc);
  printf("ref-pc=%lx  cpu.pc=%lx\n",ref_r->pc, cpu.pc);
  bool res = true;
	if(ref_r->pc != cpu.pc) {
		printf("pc different after executing inst at pc = %lx , right = %lx  wrong = %lx  \n", pc, ref_r->pc, cpu.pc);
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


