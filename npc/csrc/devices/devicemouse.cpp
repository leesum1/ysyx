#include "devicemouse.h"
#include <SDL_mouse.h>
#include "devicebase.h"
#include <cstdint>

using namespace Topdevice;

Devicemouse::Devicemouse(/* args */) {}
Devicemouse::~Devicemouse() {}

void Devicemouse::init(const char *name) {
  deviceinfo_t t;
  t.name.append(name);
  t.addr = MOUSE_ADDR;
  t.len = 16;
  t.isok = true;

  deviceinfo.push_back(t);
}
void Devicemouse::write(paddr_t addr, word_t data, uint32_t len) {}
word_t Devicemouse::read(paddr_t addr) {
  uint64_t offset = addr - MOUSE_ADDR;
  word_t r_data = 0;

  switch (offset) {
  case MOUSE_KEY_OFFSET:
    r_data = mouse_btn_state;
    break;
  case POSITION_X_OFFSET:
    r_data = mouse_x;
    break;
  case POSITION_Y_OFFSET:
    r_data = mouse_y;
    break;
  default:
    break;
  };

  return r_data;
}

void Devicemouse::update() {
  int sdl_x, sdl_y;
  uint32_t mouse_btn = SDL_GetMouseState(&sdl_x, &sdl_y);
  this->mouse_btn_state = mouse_btn;
  this->mouse_x = sdl_x / 2;
  this->mouse_y = sdl_y / 2;
}