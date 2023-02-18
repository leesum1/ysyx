#ifndef __Devicemouse_H_
#define __Devicemouse_H_

#include "devicebase.h"
#include <cstdint>

namespace Topdevice {

class Devicemouse : public Devicebase {
private:
#define MOUSE_KEY_OFFSET 0
#define POSITION_X_OFFSET 8
#define POSITION_Y_OFFSET 12
  uint32_t mouse_btn_state = 0;
  uint32_t mouse_x = 0;
  uint32_t mouse_y = 0;

public:
  Devicemouse(/* args */);
  virtual ~Devicemouse();
  void write(paddr_t addr, word_t data, uint32_t len);
  word_t read(paddr_t addr);
  void init(const char *name);
  void update();
};

} // namespace Topdevice

#endif