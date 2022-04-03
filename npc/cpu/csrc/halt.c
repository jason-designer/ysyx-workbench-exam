#include "halt.h"

uint64_t *cpu_halt = NULL;
void set_halt_ptr(const svOpenArrayHandle r) {
  cpu_halt = (uint64_t *)(((VerilatedDpiOpenVar*)r)->datap());
}


