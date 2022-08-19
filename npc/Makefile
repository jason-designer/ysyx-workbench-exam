BUILD_DIR 		= $(NPC_HOME)/build
CSRC_DIR 		= $(NPC_HOME)/cpu/csrc
VERILATOR_DIR	= $(BUILD_DIR)/verilator_obj
VSRC_DIR 		= $(BUILD_DIR)/vsrc
WAVEFORM_DIR 	= $(BUILD_DIR)/waveform
DIFF_DIR		= $(NPC_HOME)/diff-so

YSYX_DIR 		= $(NPC_HOME)/..


test:
	mill -i __.test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mkdir -p $(VSRC_DIR)
	mill -i __.test.runMain TopMain -td $(VSRC_DIR)

help:
	mill -i __.test.runMain TopMain --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

clean:
	-rm -rf $(BUILD_DIR)



# img_file
ALL3_TEST_FILE = $(shell find $(NPC_HOME)/bin/non-output/riscv-tests/ -name "*-riscv-tests.bin")
ALL4_TEST_FILE = $(shell find $(YSYX_DIR)/am-kernels/tests/cpu-tests/build/ -name "*-riscv64-npc.bin")
ifdef ALL4
IMG_FILE = $(YSYX_DIR)/am-kernels/tests/cpu-tests/build/$(ALL4)-riscv64-npc.bin
endif
ifdef ALL3
IMG_FILE = $(NPC_HOME)/bin/non-output/riscv-tests/$(ALL3)-riscv-tests.bin
endif
ifdef SIMALL
IMG_FILE = $(ALL3_TEST_FILE) $(ALL4_TEST_FILE)
endif

ifdef ALL
IMG_FILE = $(NPC_HOME)/bin/$(ALL)
ifeq ($(ALL),h)
IMG_FILE = $(NPC_HOME)/bin/am-test/hello/amtest-riscv64-npc.bin
endif
ifeq ($(ALL),t)
IMG_FILE = $(NPC_HOME)/bin/am-test/rtc/amtest-riscv64-npc.bin
endif
ifeq ($(ALL),k)
IMG_FILE = $(NPC_HOME)/bin/am-test/keyboard/amtest-riscv64-npc.bin
endif
ifeq ($(ALL),v)
IMG_FILE = $(NPC_HOME)/bin/am-test/video/amtest-riscv64-npc.bin
endif
ifeq ($(ALL),mario)
IMG_FILE = $(NPC_HOME)/bin/am-test/mario/fceux-riscv64-npc.bin
endif
ifeq ($(ALL),nanos)
IMG_FILE = $(NPC_HOME)/bin/nanos_lite/nanos-lite-riscv64-npc.bin
endif

endif


# project source
# VSRCS = $(shell find $(abspath $(VSRC_DIR)) -name "*.v")
CSRCS = $(shell find $(abspath $(CSRC_DIR)) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
VSRCS = $(shell find $(abspath $(VSRC_DIR)) -name "*.v" -not -name "SimTop.v")

CFLAGS += -g
# CFLAGS += -O0
CFLAGS += -lasan
CFLAGS += $(shell llvm-config --cxxflags)

LDFLAGS += -ldl
LDFLAGS += -lSDL2 -lSDL2_image 
LDFLAGS += $(shell llvm-config --libs)

# DIFF_TEST = $(DIFF_DIR)/riscv64-nemu-interpreter-so
DIFF_TEST = $(DIFF_DIR)/riscv64-spike-so

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -Wall --cc --exe --build --trace 		\
    -Wno-DECLFILENAME -Wno-UNUSED  -Wno-EOFNEWLINE  \
	-Wno-WIDTH -Wno-BLKSEQ -Wno-VARHIDDEN           \
	-Wno-LATCH -Wno-UNOPTFLAT                    	\
	-I $(VSRCS)                                     \
	-I $(CSRCS)                                     \
	$(addprefix -CFLAGS , -O0 $(CFLAGS)) 			\
	$(addprefix -LDFLAGS , $(LDFLAGS)) 				\
    --top-module SimTop                             \
    --Mdir $(VERILATOR_DIR)                         \
    $(CSRC_DIR)/sim_main.cpp                        \
    $(VSRC_DIR)/SimTop.v 

run: sim
	mkdir -p $(WAVEFORM_DIR)
	$(VERILATOR_DIR)/VSimTop  $(WAVEFORM_DIR)/sim_main.vcd $(DIFF_TEST) $(IMG_FILE)

gdb: sim
	mkdir -p $(WAVEFORM_DIR)
	gdb -tui --args $(VERILATOR_DIR)/VSimTop $(WAVEFORM_DIR)/sim_main.vcd $(DIFF_TEST) $(IMG_FILE)

wave:
	gtkwave $(WAVEFORM_DIR)/sim_main.vcd


#更新am-test测试文件

update_am_test:
	mkdir -p bin/am-test
	mkdir -p bin/am-test/hello
	mkdir -p bin/am-test/rtc
	mkdir -p bin/am-test/keyboard
	mkdir -p bin/am-test/video
	mkdir -p bin/am-test/mario

	cd ../am-kernels/tests/am-tests/ && make ARCH=riscv64-npc mainargs=h
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.bin bin/am-test/hello/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.elf bin/am-test/hello/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.txt bin/am-test/hello/

	cd ../am-kernels/tests/am-tests/ && make ARCH=riscv64-npc mainargs=t
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.bin bin/am-test/rtc/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.elf bin/am-test/rtc/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.txt bin/am-test/rtc/

	cd ../am-kernels/tests/am-tests/ && make ARCH=riscv64-npc mainargs=k
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.bin bin/am-test/keyboard/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.elf bin/am-test/keyboard/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.txt bin/am-test/keyboard/

	cd ../am-kernels/tests/am-tests/ && make ARCH=riscv64-npc mainargs=v
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.bin bin/am-test/video/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.elf bin/am-test/video/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.txt bin/am-test/video/

	cd ../fceux-am && make ARCH=riscv64-npc mainargs=mario
	cp ../fceux-am/build/fceux-riscv64-npc.bin bin/am-test/mario/
	cp ../fceux-am/build/fceux-riscv64-npc.elf bin/am-test/mario/
	cp ../fceux-am/build/fceux-riscv64-npc.txt bin/am-test/mario/

update_nanos_lite:
	mkdir -p bin/nanos_lite

	cd ../nanos-lite/ && make ARCH=riscv64-npc update
	cd ../nanos-lite/ && make ARCH=riscv64-npc
	cp ../nanos-lite/build/nanos-lite-riscv64-npc.bin bin/nanos_lite/
	cp ../nanos-lite/build/nanos-lite-riscv64-npc.elf bin/nanos_lite/
	cp ../nanos-lite/build/nanos-lite-riscv64-npc.txt bin/nanos_lite/


.PHONY: test verilog help compile bsp reformat checkformat clean sim run gdb wave update_am_test update_nanos_lite
include ../Makefile
