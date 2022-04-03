cmd_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/device/device.o := unused

source_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/device/device.o := src/device/device.c

deps_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/device/device.o := \
    $(wildcard include/config/target/am.h) \
    $(wildcard include/config/has/vga.h) \
    $(wildcard include/config/has/keyboard.h) \
    $(wildcard include/config/has/serial.h) \
    $(wildcard include/config/has/timer.h) \
    $(wildcard include/config/has/audio.h) \
    $(wildcard include/config/has/disk.h) \
    $(wildcard include/config/has/sdcard.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/common.h \
    $(wildcard include/config/mbase.h) \
    $(wildcard include/config/msize.h) \
    $(wildcard include/config/isa64.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/macro.h \
  /home/zgs/project/ysyx-workbench/nemu/include/debug.h \
  /home/zgs/project/ysyx-workbench/nemu/include/utils.h \
    $(wildcard include/config/target/native/elf.h) \
  /home/zgs/project/ysyx-workbench/nemu/include/device/alarm.h \

/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/device/device.o: $(deps_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/device/device.o)

$(deps_/home/zgs/project/ysyx-workbench/nemu/build/obj-riscv64-nemu-interpreter/src/device/device.o):
