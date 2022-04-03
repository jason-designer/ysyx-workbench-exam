#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "common.h"

#define RESET_VECTOR 0x80000000
#define MEM_SIZE 0x8000000

extern uint8_t* mem;

uint64_t load_program(char* img_file);
uint64_t read_memory(uint64_t addr, int length);


#endif