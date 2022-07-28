#ifndef __DEVICEVGA_H_
#define __DEVICEVGA_H_

#include "devicebase.h"
#include <SDL2/SDL.h>
namespace Topdevice {

    class Devicevga :public Devicebase {

    private:
#define SCREEN_W 400 //默认 400*300
#define SCREEN_H 300

        struct vga_reg_t {
            uint32_t sreensize; //屏幕大小寄存器
            uint32_t sync;      //同步寄存器
            uint32_t* fbbuff;   //fb 显存
        };

        vga_reg_t vgaregs;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;
        SDL_Thread* update_thread;
        SDL_mutex* fbbuff_lock;
    private:
        void initscreen();
        uint32_t screen_width();
        uint32_t screen_height();
        uint32_t screen_size();
        void vga_update_screen();

    public:
        Devicevga(/* args */);
        virtual  ~Devicevga();
        void update_screen();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void update();
        void init(const char* name);
    };

} // namespace d

#endif