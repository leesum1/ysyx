#ifndef __DEVICEKB_H_
#define __DEVICEKB_H_

#include "devicebase.h"
#include <SDL2/SDL.h>
#include "ringbuff.hpp"

namespace Topdevice {

    class Devicekb :public Devicebase {
        // Input
#define AM_KEYS(_) \
  _(ESCAPE) _(F1) _(F2) _(F3) _(F4) _(F5) _(F6) _(F7) _(F8) _(F9) _(F10) _(F11) _(F12) \
  _(GRAVE) _(1) _(2) _(3) _(4) _(5) _(6) _(7) _(8) _(9) _(0) _(MINUS) _(EQUALS) _(BACKSPACE) \
  _(TAB) _(Q) _(W) _(E) _(R) _(T) _(Y) _(U) _(I) _(O) _(P) _(LEFTBRACKET) _(RIGHTBRACKET) _(BACKSLASH) \
  _(CAPSLOCK) _(A) _(S) _(D) _(F) _(G) _(H) _(J) _(K) _(L) _(SEMICOLON) _(APOSTROPHE) _(RETURN) \
  _(LSHIFT) _(Z) _(X) _(C) _(V) _(B) _(N) _(M) _(COMMA) _(PERIOD) _(SLASH) _(RSHIFT) \
  _(LCTRL) _(APPLICATION) _(LALT) _(SPACE) _(RALT) _(RCTRL) \
  _(UP) _(DOWN) _(LEFT) _(RIGHT) _(INSERT) _(DELETE) _(HOME) _(END) _(PAGEUP) _(PAGEDOWN)

#define AM_KEY_NAMES(key) AM_KEY_##key,
        enum {
            AM_KEY_NONE = 0,
            AM_KEYS(AM_KEY_NAMES)
        };

#define XX(k) [SDL_SCANCODE_##k] = AM_KEY_##k,
#define KEYDOWN_MASK 0x8000

    private:
        /* 提取自 native 的键盘映关系,cpp 中不支持数组乱序初始化,无奈之举 */
        int keymap[256] = { 0,0,0,0,43,60,58,45,31,46,47,48,36,49,50,51,62,61,37,38,
                            29,32,44,33,35,59,30,57,34,56,15,16,17,18,19,20,21,22,23,
                            24,54,1,27,28,70,25,26,39,40,41,0,52,53,14,63,64,65,42,2,
                            3,4,5,6,7,8,9,10,11,12,13,0,0,0,77,79,81,78,80,82,76,75,74,
                            73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,68,0,0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,67,55,69,0,72,
                            66,71,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
        jm::circular_buffer<int, 512> keybuff; //环形缓冲区
        SDL_Event event;
    public:
        Devicekb(/* args */);
        virtual  ~Devicekb();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void update();
        void init(const char* name);
        void send_key(uint8_t scancode, bool is_keydown);
    };

} // namespace d

#endif