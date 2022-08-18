CFLAGS += -DMAINARGS=\"$(mainargs)\"

verilog:
	$(MAKE) -C $(NPC_HOME) IMG_FILE=$(IMAGE).bin verilog

run: image
	$(MAKE) -C $(NPC_HOME) IMG_FILE=$(IMAGE).bin run

.PHONY: run