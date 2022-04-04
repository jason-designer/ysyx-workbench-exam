#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "common.h"
#include "verilated_dpi.h"

#define RESET_VECTOR 0x80000000
#define MEM_SIZE 0x8000000

extern uint8_t* mem;

uint64_t load_program(char* img_file);
uint64_t read_memory(uint64_t addr, int length);
extern "C" void pmem_read(unsigned char ren, long long raddr, long long *rdata);
extern "C" void pmem_write(unsigned char wen, long long waddr, long long wdata, char wmask);


#endif