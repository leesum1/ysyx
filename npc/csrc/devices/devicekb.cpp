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
    t.len = 8;
    t.isok = true;

    deviceinfo.push_back(t);
}
void Devicekb::write(paddr_t addr, word_t data, uint32_t len) {

}
word_t Devicekb::read(paddr_t addr) {
    int k = 0;
    paddr_t offset = addr - KBD_ADDR;

    // 32bit 寄存器， scancode
    if (offset == 0) {
        if (!scancode_buff.empty()) {
            k = scancode_buff.front();
            scancode_buff.pop_front();
        }
    }
    // 32bit 寄存器
    else if (offset == 4) {
        if (!keycode_buff.empty()) {
            k = keycode_buff.front();
            keycode_buff.pop_front();
        }
    }
    return k;

}

void Devicekb::update() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            mysim_p->showSimPerformance();
            exit(0);
            break;
            // If a key was pressed
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            SDL_Scancode k = event.key.keysym.scancode;
            if (k == SDL_SCANCODE_F1) {
                mysim_p->top_status = mysim_p->TOP_STOP; // 暂停仿真
                mysim_p->showSimPerformance();
            }
            bool is_keydown = (event.key.type == SDL_KEYDOWN);
            send_key(k, is_keydown);

            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode k_temp = SDL_GetKeyFromScancode(k);
                // shift - 组合键 转换为 _
                if ((event.key.keysym.mod & KMOD_SHIFT) && k_temp == SDLK_MINUS) {
                    send_key_ascii(SDLK_UNDERSCORE);
                }
                else {
                    send_key_ascii(k_temp);
                }
            }

            break;
        }
        default: break;
        }
    }
}

void Devicekb::send_key(uint8_t scancode, bool is_keydown) {
    if (keymap[scancode] != 0) {
        int am_code = keymap[scancode] | (is_keydown ? KEYDOWN_MASK : 0);
        scancode_buff.push_back(am_code);
    }
}


void Devicekb::send_key_ascii(SDL_Keycode keycode) {

    // sdl keycode 包含 ascii 以外的内容
    if (keycode <= UINT8_MAX) {
        keycode_buff.push_back(keycode);
    }
}
