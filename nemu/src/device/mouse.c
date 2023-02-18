/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 *PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 *KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 *NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <assert.h>
// #include <cstdint>
#include <stdint.h>
#include <device/map.h>
#include <stdbool.h>
#include <utils.h>

#ifndef CONFIG_TARGET_AM
#include <SDL2/SDL.h>

static uint32_t *mouse_data_port_base = NULL;

static uint32_t mouse_btn = 0;
static uint32_t mouse_x = 0;
static uint32_t mouse_y = 0;

#define MOUSE_KEY_OFFSET 0
#define POSITION_X_OFFSET 8
#define POSITION_Y_OFFSET 12

void send_mouse_event(uint32_t btn, uint32_t x, uint32_t y) {
  mouse_btn = btn;
  mouse_x = x;
  mouse_y = y;
}

static void mouse_data_io_handler(uint32_t offset, int len, bool is_write) {
  assert(!is_write);

  switch (offset) {
  case MOUSE_KEY_OFFSET:
    mouse_data_port_base[0] = mouse_btn;
    break;
  case POSITION_X_OFFSET:
    mouse_data_port_base[2] = mouse_x;
    break;
  case POSITION_Y_OFFSET:
    mouse_data_port_base[3] = mouse_y;
    break;
  default:
  assert(0);
    break;
  };
}

void init_mouse() {
  mouse_data_port_base = (uint32_t *)new_space(16);

  // todo! add MOUSE_ADDR to KCONFIG
  add_mmio_map("Mouse", 0xa0000000 + 0x0000070, mouse_data_port_base, 16,
               mouse_data_io_handler);
}
#endif