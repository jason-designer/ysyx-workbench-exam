#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
	uint32_t x = inl(KBD_ADDR);
  	kbd->keydown = x & 0x8000;
	kbd->keycode = x & 0x7fff;
}
