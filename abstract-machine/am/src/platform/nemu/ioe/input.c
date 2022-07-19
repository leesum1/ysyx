#include <am.h>
#include <nemu.h>
#include <stdio.h>
#define KEYDOWN_MASK 0x8000
/* 最高位为 keydown*/
static AM_INPUT_KEYBRD_T read_key(void) {
  AM_INPUT_KEYBRD_T kb;
  uint32_t kbVal = inl(KBD_ADDR);
  kb.keydown = (KEYDOWN_MASK & kbVal) >> 31;
  kb.keycode = (~KEYDOWN_MASK) & kbVal;
  return kb;
}


void __am_input_keybrd(AM_INPUT_KEYBRD_T* kbd) {
  AM_INPUT_KEYBRD_T tempkb = read_key();
  kbd->keydown = tempkb.keydown;
  kbd->keycode = tempkb.keycode;
}
