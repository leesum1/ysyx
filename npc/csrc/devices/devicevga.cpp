#include "devicevga.h"

#include "assert.h"
using namespace Topdevice;


static int thread_func(void* ptr) {
    Devicevga* vga_p = (Devicevga*)ptr;
    while (1) {
        SDL_Delay(20);
        vga_p->update_screen();
    }
}

Devicevga::Devicevga(/* args */) {

}
Devicevga::~Devicevga() {
    delete vgaregs.fbbuff;
}

void Devicevga::init(const char* name) {

    /* 两块地址空间名称 */
    string ctrName(name);
    ctrName += "_ctr";
    string fbName(name);
    fbName += "_fb";

    deviceinfo_t t;
    t.name.append(ctrName);
    t.addr = VGACTL_ADDR;
    t.len = 8;
    t.isok = true;
    deviceinfo.push_back(t);

    t.name.clear();
    t.name.append(ctrName);
    t.addr = FB_ADDR;
    t.len = screen_size();
    t.isok = true;
    deviceinfo.push_back(t);

    initscreen();
}
void Devicevga::write(paddr_t addr, word_t data, uint32_t len) {
    paddr_t offset;
    /* 控制寄存器 */
    if (atRange(deviceinfo.at(0).addr, deviceinfo.at(0).addr + deviceinfo.at(0).len - 1, addr)) {
        offset = addr - deviceinfo.at(0).addr;
        assert(offset == 0 || offset == 4);
        if (0 == offset) {
            vgaregs.sreensize = (uint32_t)data;
        }
        else {
            vgaregs.sync = (uint32_t)data;
            //vga_update_screen();
        }
    }
    /* fb 缓存 */
    else if (atRange(deviceinfo.at(1).addr, deviceinfo.at(1).addr + deviceinfo.at(1).len - 1, addr)) {
        offset = addr - deviceinfo.at(1).addr + (paddr_t)vgaregs.fbbuff;

        switch (len) {
        case 4:
            *(uint32_t*)offset = (uint32_t)data;
            break;
        case 8:
            *(uint64_t*)offset = (uint64_t)data;
            break;
        default:
            printf("len:%d\n", len);
            assert(0);
            break;
        }
    }
}
word_t Devicevga::read(paddr_t addr) {
    word_t data;
    paddr_t offset;
    /* 控制寄存器 */
    if (atRange(deviceinfo.at(0).addr, deviceinfo.at(0).addr + deviceinfo.at(0).len - 1, addr)) {
        offset = addr - deviceinfo.at(0).addr;
        assert(offset == 0 || offset == 4);
        if (0 == offset) {
            data = vgaregs.sreensize;
        }
        else {
            data = vgaregs.sync;
        }
    }
    /* fb 缓存 */
    else if (atRange(deviceinfo.at(1).addr, deviceinfo.at(1).addr + deviceinfo.at(1).len - 1, addr)) {
        offset = addr - deviceinfo.at(1).addr;
        data = *(vgaregs.fbbuff + offset);
    }

    return data;
}


void Devicevga::initscreen() {
    SDL_Window* window = NULL;
    char title[128] = "riscv64-npc";

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        SCREEN_W * 2,
        SCREEN_H * 2,
        0, &window, &renderer);
    SDL_SetWindowTitle(window, title);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC, SCREEN_W, SCREEN_H);

    uint32_t buffsize = screen_size();
    vgaregs.fbbuff = new uint32_t[buffsize];

    fbbuff_lock = SDL_CreateMutex();

}


uint32_t Devicevga::screen_width() {
    return SCREEN_W;
}

uint32_t Devicevga::screen_height() {
    return SCREEN_H;
}

uint32_t Devicevga::screen_size() {
    return screen_width() * screen_height() * sizeof(uint32_t);
}



void Devicevga::update_screen() {

    SDL_UpdateTexture(texture, NULL, vgaregs.fbbuff, SCREEN_W * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Devicevga::vga_update_screen() {
    // TODO: call `update_screen()` when the sync register is non-zero,
    // then zero out the sync register
    if (vgaregs.sync) {
        update_screen();
        vgaregs.sync = 0;
    }
}
void Devicevga::update() {
    vga_update_screen();
}



