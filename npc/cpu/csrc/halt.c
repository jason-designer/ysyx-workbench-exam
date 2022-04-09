#include "halt.h"

uint64_t cpu_halt = NULL;
void read_halt(unsigned char halt) {
  cpu_halt = halt;
}


