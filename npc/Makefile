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


ifdef ALL4
IMG_FILE = $(YSYX_DIR)/am-kernels/tests/cpu-tests/build/$(ALL4)-riscv64-npc.bin
endif
ifdef ALL3
IMG_FILE = $(NPC_HOME)/bin/non-output/riscv-tests/$(ALL3)-riscv-tests.bin
endif

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -Wall --cc --exe --build --trace      \
    -Wno-DECLFILENAME -Wno-UNUSED  -Wno-EOFNEWLINE  \
	-Wno-WIDTH -Wno-BLKSEQ -Wno-VARHIDDEN           \
	-v $(VSRC_DIR)/RegFile.v                        \
	-v $(VSRC_DIR)/Halt.v                           \
	-v $(VSRC_DIR)/Memory.v                         \
	-I $(CSRC_DIR)/halt.c                           \
	-I $(CSRC_DIR)/memory.c                         \
	-I $(CSRC_DIR)/reg.c                            \
	-I $(CSRC_DIR)/difftest.c                       \
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


include ../Makefile
