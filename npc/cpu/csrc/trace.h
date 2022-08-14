#ifndef __TRACE_H__
#define __TRACE_H__

#include "common.h"
#include "verilated_dpi.h"

typedef struct {
  bool commit;
  uint64_t pc;
  uint32_t inst;
} CPU_Commit_Info;

extern CPU_Commit_Info commit_info;
extern "C" void commit_info_fetch(unsigned char commit, long long pc, int inst);

typedef struct {
  bool valid;
  uint64_t pc;
  uint32_t inst;
  bool ren;
  uint64_t raddr;
  uint64_t rdata;
  bool wen;
  uint64_t waddr;
  uint64_t wdata;
  uint8_t  wmask;
} Dmem_Info;

extern Dmem_Info dmem_info;
extern "C" void dmem_info_fetch(unsigned char valid, long long pc, int inst, unsigned char ren, long long raddr, long long rdata, unsigned char wen, long long waddr, long long wdata, char wmask);

void iringbuf_init();
void iringbuf_log_once(char* str);
void iringbuf_print();

#endif