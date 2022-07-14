#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>
#include "../monitor/sdb/sdb.h"

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 10

CPU_state cpu = {.mstatus = 0xa00001800};
uint64_t g_nr_guest_inst = 0;
static uint64_t g_timer = 0; // unit: us
static bool g_print_step = false;

void device_update();

/************************ watchpoint ****************************/
void watchpoint(){
	if(check_watchpoint()) nemu_state.state = NEMU_STOP;
}
/****************************************************************/
/************************ iringbuf ******************************/
// #define IRINGBUF_SIZE 50
// char iringbuf[IRINGBUF_SIZE][30];
// int iring_index = IRINGBUF_SIZE - 1;
// void update_iringbuf(char* log){
//   iring_index++;
//   if(iring_index >= IRINGBUF_SIZE) iring_index = 0;
//   strcpy(iringbuf[iring_index], log);
// }
// void print_iringbuf(){
//   printf("-----------------iringbuf---------------\n");
//   for(int i = 0; i < IRINGBUF_SIZE; i++){
//     if(i == iring_index) printf("---> %s",iringbuf[i]);
//     printf("     %s",iringbuf[i]);
//   }
//   printf("----------------------------------------\n");
// }
/****************************************************************/
/************************ ftrace ******************************/
#include <stdio.h>
#include <elf.h>

typedef struct{
  char* name;
  uint64_t addr_start;
  uint64_t addr_end;
}func_info;
int func_num = 0;
func_info *fc;
int call_times = 0;
// ftrace
char* ftrace_log = "/home/zgs/project/ysyx-workbench/nemu/build/ftrace-log.txt";
FILE* ftrace_fp; 

func_info* decode_elf(char* elf_file_name){
  assert(elf_file_name != NULL);
  FILE *fp;
  // get elf size
  fp = fopen(elf_file_name, "r");
  fseek(fp, 0L, SEEK_END);
  int elf_size = ftell(fp);
  // copy elf file to char *
  char elf[elf_size];
  fseek(fp, 0, SEEK_SET);
  fread(&elf, 1, elf_size, fp);
  fclose(fp);
  // read elf header table
  Elf64_Ehdr ehdr;
  memcpy(&ehdr, elf, sizeof(Elf64_Ehdr));
  // read section header table
  Elf64_Shdr shdr[ehdr.e_shnum];
  memcpy(&shdr, elf + ehdr.e_shoff, sizeof(Elf64_Shdr)*ehdr.e_shnum);
  // find the offset of strtab and symtab
  Elf64_Shdr shdr_sym;
  for(int i = 0; i < ehdr.e_shnum; i++) {
    if(shdr[i].sh_type == SHT_SYMTAB) shdr_sym = shdr[i];
  }
  Elf64_Shdr shdr_str;
  for(int i = 0; i < ehdr.e_shnum; i++) {
    if(shdr[i].sh_type == SHT_STRTAB) {
      shdr_str = shdr[i];
      break;
    }
  }
  // read symtab
  int symtab_num = shdr_sym.sh_size / sizeof(Elf64_Sym);
  Elf64_Sym sym[symtab_num];
  memcpy(&sym, elf + shdr_sym.sh_offset, shdr_sym.sh_size);
  // find FUNC in symtab, find the name of FUNC and the addr of FUNC
  // 计算有多少个FUNC
  for(int i = 0; i < symtab_num; i++) {   
    if(sym[i].st_info == 18)  func_num++; // is FUNC
  }
  // 记录FUNC
  func_info* fc;
  fc = (func_info*)malloc(sizeof(func_info) * func_num);
  for(int i = 0, j = 0; i < symtab_num; i++) {   
    if(sym[i].st_info == 18){   // is FUNC
      fc[j].addr_start = sym[i].st_value;
      fc[j].addr_end = sym[i].st_value + sym[i].st_size; 
      char* str = elf + shdr_str.sh_offset + sym[i].st_name;
      char* name = (char*)malloc(strlen(str) + 1);  // '0'
      strcpy(name, str);
      fc[j].name = name;
      j++;
    }  
  }
  return fc;
}

#define BITS(x, hi, lo) (((x) >> (lo)) & BITMASK((hi) - (lo) + 1)) // similar to x[hi:lo] in verilog
#define SEXT(x, len) ({ struct { int64_t n : len; } __x = { .n = x }; (int64_t)__x.n; })
word_t immj(uint32_t i) { return SEXT(BITS(i, 31, 31), 1) << 20 | (BITS(i, 30, 21) << 1) | (BITS(i, 20, 20) << 11) | (BITS(i, 19, 12) << 12); }
int is_call(uint64_t pc, uint32_t inst){    // return index of fc
  uint64_t imm = immj(inst);
  uint64_t jump_pc = imm + pc;
  if((inst & 0xfff) == 0x0ef){
    int i;
    for(i = 0; i < func_num; i++){
      if(fc[i].addr_start == jump_pc) break;
    }
    if(i < func_num) return i;
  }
  return -1;
}

char* find_func_name(uint64_t addr){    // find func name according to addr
  int i;
  for(i = 0; i < func_num; i++){
    if(fc[i].addr_start <= addr && fc[i].addr_end > addr) return fc[i].name;
  }
  return NULL;
}

void ftrace(uint64_t pc, uint32_t inst){
  if(inst == 0x00008067){
    fprintf(ftrace_fp, "%x: %*cret  [%s]\n", (uint32_t)pc, 2*call_times, ' ', find_func_name(cpu.gpr[1]));
    call_times--;
  }
  int fc_index = is_call(pc, inst);
  if(fc_index != -1){
    call_times++;
    fprintf(ftrace_fp, "%x: %*ccall [%s@%x]\n", (uint32_t)pc, 2*call_times, ' ', fc[fc_index].name, (uint32_t)fc[fc_index].addr_start);
  }
}


/**************************************************************/



static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  if (ITRACE_COND) { log_write("%s\n", _this->logbuf); }
#endif
  ftrace(_this->pc, _this->isa.inst.val);
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));
  IFDEF(CONFIG_WATCHPOINT, watchpoint());
}

static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;
  s->snpc = pc;
  isa_exec_once(s);
  cpu.pc = s->dnpc;
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);
  int ilen = s->snpc - s->pc;
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst.val;
  for (i = 0; i < ilen; i ++) {
    p += snprintf(p, 4, " %02x", inst[i]);
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);
  int space_len = ilen_max - ilen;
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);
  p += space_len;

  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst.val, ilen);
#endif
}

static void execute(uint64_t n) {
  Decode s;
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);
    g_nr_guest_inst ++;
    trace_and_difftest(&s, cpu.pc);
    if (nemu_state.state != NEMU_RUNNING) break;
    IFDEF(CONFIG_DEVICE, device_update());
  }
}

static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%ld", "%'ld")
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");
}

void assert_fail_msg() {
  isa_reg_display();
  statistic();
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  uint64_t timer_start = get_time();

  execute(n);

  uint64_t timer_end = get_time();
  g_timer += timer_end - timer_start;

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_END: case NEMU_ABORT:
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ASNI_FMT("ABORT", ASNI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ASNI_FMT("HIT GOOD TRAP", ASNI_FG_GREEN) :
            ASNI_FMT("HIT BAD TRAP", ASNI_FG_RED))),
          nemu_state.halt_pc);
      // fall through
    case NEMU_QUIT: statistic();
  }
}
