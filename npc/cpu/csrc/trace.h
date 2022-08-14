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
extern "C" void commit_info_read(unsigned char commit, long long pc, int inst);

#endif