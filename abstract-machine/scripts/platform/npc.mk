CFLAGS += -DMAINARGS=\"$(mainargs)\"

VERILOG = verilog

run: image
	$(MAKE) -C $(NPC_HOME) IMG_FILE=$(IMAGE).bin $(VERILOG) run

.PHONY: run sim verilog
