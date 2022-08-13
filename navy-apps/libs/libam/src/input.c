#include <am.h>
#include <NDL.h>
#include <SDL.h>
#include <stdio.h>
#define KEYDOWN_MASK 0x8000
/* 最高位为 keydown*/
static AM_INPUT_KEYBRD_T read_key(void) {
    AM_INPUT_KEYBRD_T kb = {
        .keycode = 0,
        .keydown = 0
    };

    SDL_Event e;
    uint8_t ret = SDL_PollEvent(&e);
    if (ret) {
        kb.keydown = (e.type == SDL_KEYDOWN);
        kb.keycode = e.key.keysym.sym;
    }
    return kb;
}


void __am_input_keybrd(AM_INPUT_KEYBRD_T* kbd) {
    AM_INPUT_KEYBRD_T tempkb = read_key();
    kbd->keydown = tempkb.keydown;
    kbd->keycode = tempkb.keycode;
}
