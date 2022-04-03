cmd_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/isa/riscv64/inst.o := unused

source_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/isa/riscv64/inst.o := src/isa/riscv64/inst.c

deps_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/isa/riscv64/inst.o := \
  src/isa/riscv64/local-include/reg.h \
    $(wildcard include/config/rt/check.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/common.h \
    $(wildcard include/config/target/am.h) \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/macro.h \
  /home/zgs/project/ysyx-workbench/nemu/include/debug.h \
  /home/zgs/project/ysyx-workbench/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/cpu/cpu.h \
  /home/zgs/project/ysyx-workbench/nemu/include/cpu/ifetch.h \
  /home/zgs/project/ysyx-workbench/nemu/include/memory/vaddr.h \
  /home/zgs/project/ysyx-workbench/nemu/include/cpu/decode.h \
    $(wildcard include/config/itrace.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/isa.h \
  /home/zgs/project/ysyx-workbench/nemu/src/isa/riscv64/include/isa-def.h \
  /home/zgs/project/ysyx-workbench/nemu/include/cpu/difftest.h \
    $(wildcard include/config/difftest.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/difftest-def.h \
    $(wildcard include/config/isa/x86.h) \
    $(wildcard include/config/isa/mips32.h) \
    $(wildcard include/config/isa/riscv32.h) \
    $(wildcard include/config/isa/riscv64.h) \

/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/isa/riscv64/inst.o: $(deps_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/isa/riscv64/inst.o)

$(deps_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/isa/riscv64/inst.o):
