#include "devicekb.h"
#include "simtop.h"


using namespace Topdevice;
extern Simtop* mysim_p;;

Devicekb::Devicekb(/* args */) {

}
Devicekb::~Devicekb() {

}

void Devicekb::init(const char* name) {
    deviceinfo_t t;
    t.name.append(name);
    t.addr = KBD_ADDR;
    t.len = 4;
    t.isok = true;

    deviceinfo.push_back(t);
}
void Devicekb::write(paddr_t addr, word_t data, uint32_t len) {

}
word_t Devicekb::read(paddr_t addr) {
    int k = AM_KEY_NONE;
    if (!keybuff.empty()) {
        k = keybuff.front();
        keybuff.pop_front();
    }
    return k;
}

void Devicekb::update() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;
            // If a key was pressed
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            uint8_t k = event.key.keysym.scancode;
            bool is_keydown = (event.key.type == SDL_KEYDOWN);
            send_key(k, is_keydown);
            break;
        }
        default: break;
        }
    }
}

void Devicekb::send_key(uint8_t scancode, bool is_keydown) {
    if (keymap[scancode] != 0) {
        int am_code = keymap[scancode] | (is_keydown ? KEYDOWN_MASK : 0);
        keybuff.push_back(am_code);
    }
}