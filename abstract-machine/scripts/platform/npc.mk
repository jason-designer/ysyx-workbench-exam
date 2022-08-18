CFLAGS += -DMAINARGS=\"$(mainargs)\"

run: image
	$(MAKE) -C $(NPC_HOME) IMG_FILE=$(IMAGE).bin run

.PHONY: run