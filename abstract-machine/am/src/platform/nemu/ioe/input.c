#include <am.h>
#include <nemu.h>
#include <stdio.h>
#define KEYDOWN_MASK 0x8000

// static AM_INPUT_KEYBRD_T read_key(void) {
//   AM_INPUT_KEYBRD_T kb;
//   uint32_t kbVal = inl(KBD_ADDR);
//   printf("key:%d\n", kbVal);
//   kb.keydown = (KEYDOWN_MASK & kbVal) >> 31;
//   kb.keycode = (~KEYDOWN_MASK) & kbVal;
//   return kb;
// }


void __am_input_keybrd(AM_INPUT_KEYBRD_T* kbd) {
  int code = inl(KBD_ADDR);
  kbd->keydown = (code & KEYDOWN_MASK ? true : false);
  kbd->keycode = code & ~KEYDOWN_MASK;
}
