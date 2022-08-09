BUILD_DIR = $(NPC_HOME)/build
CSRC_DIR = $(NPC_HOME)/cpu/csrc
VERILATOR_DIR = $(BUILD_DIR)/verilator_obj
VSRC_DIR = $(BUILD_DIR)/vsrc
WAVEFORM_DIR = $(BUILD_DIR)/waveform

YSYX_DIR = $(NPC_HOME)/..


test:
	mill -i __.test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mkdir -p $(VSRC_DIR)
	mill -i __.test.runMain Elaborate -td $(VSRC_DIR)

help:
	mill -i __.test.runMain Elaborate --help

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

.PHONY: test verilog help compile bsp reformat checkformat clean


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
endif

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -Wall --cc --exe --build --trace      \
    -Wno-DECLFILENAME -Wno-UNUSED  -Wno-EOFNEWLINE  \
	-Wno-WIDTH -Wno-BLKSEQ -Wno-VARHIDDEN           \
	-Wno-LATCH                                      \
	-v $(VSRC_DIR)/RegFile.v                        \
	-v $(VSRC_DIR)/Halt.v                           \
	-v $(VSRC_DIR)/DMemory.v                        \
	-v $(VSRC_DIR)/IMemory.v                        \
	-v $(VSRC_DIR)/Difftest.v                       \
	-I $(CSRC_DIR)/**.c                       		\
	-LDFLAGS "-ldl"                                 \
	-CFLAGS " -lasan "                              \
    --top-module SimTop                             \
    --Mdir $(VERILATOR_DIR)                         \
    $(CSRC_DIR)/sim_main.cpp                        \
    $(VSRC_DIR)/SimTop.v 


	mkdir -p $(WAVEFORM_DIR)
	$(VERILATOR_DIR)/VSimTop  $(WAVEFORM_DIR)/sim_main.vcd  $(IMG_FILE)
	

wave:
	gtkwave $(WAVEFORM_DIR)/sim_main.vcd


#更新am-test测试文件

update_am_test:
	mkdir -p bin/am-test
	mkdir -p bin/am-test/hello
	mkdir -p bin/am-test/rtc
	mkdir -p bin/am-test/mario

	cd ../am-kernels/tests/am-tests/ && make ARCH=riscv64-npc mainargs=h
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.bin bin/am-test/hello/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.elf bin/am-test/hello/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.txt bin/am-test/hello/

	cd ../am-kernels/tests/am-tests/ && make ARCH=riscv64-npc mainargs=t
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.bin bin/am-test/rtc/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.elf bin/am-test/rtc/
	cp ../am-kernels/tests/am-tests/build/amtest-riscv64-npc.txt bin/am-test/rtc/

	cd ../fceux-am && make ARCH=riscv64-npc mainargs=mario
	cp ../fceux-am/build/fceux-riscv64-npc.bin bin/am-test/mario/
	cp ../fceux-am/build/fceux-riscv64-npc.elf bin/am-test/mario/
	cp ../fceux-am/build/fceux-riscv64-npc.txt bin/am-test/mario/

include ../Makefile
