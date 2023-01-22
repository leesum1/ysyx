/***************************************************************************************
 * Copyright (c) 2014-2021 Zihao Yu, Nanjing University
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

#include "local-include/csr.h"
#include "macro.h"
#include <device/alarm.h>
#include <device/map.h>
#include <isa.h>
#include <utils.h>

#ifndef CONFIG_HAS_CLINT
#define CONFIG_MTIMECMP_PORT 0x200
#define CONFIG_MTIME_PORT 0x300
#define CONFIG_CLINT_MMIO_BASE 0x200000
#endif

#define CLINT_MTIMECMP (CONFIG_MTIMECMP_PORT / sizeof(clint_base[0]))
#define CLINT_MTIME (CONFIG_MTIME_PORT / sizeof(clint_base[0]))
#define TIMEBASE 10000000ul

static uint64_t *clint_base = NULL;
static uint64_t boot_time = 0;

void update_clint() {

  uint64_t now = get_time() - boot_time;
  clint_base[CLINT_MTIME] = TIMEBASE * now / 1000000;

  mip_t *mip_tmp = (mip_t *)&cpu.csr[mip];

  mip_tmp->bit.mtip = (clint_base[CLINT_MTIME] >= clint_base[CLINT_MTIMECMP]);

  // printf("update_clint\n");
}

uint64_t clint_uptime() {
  update_clint();
  return clint_base[CLINT_MTIME];
}

static void clint_io_handler(uint32_t offset, int len, bool is_write) {
  update_clint();
}

void init_clint(void) {
  clint_base = (uint64_t *)new_space(0x10000);
  add_mmio_map("clint", CONFIG_CLINT_MMIO_BASE, (uint8_t *)clint_base, 0x10000,
               clint_io_handler);

  IFDEF(CONFIG_HAS_CLINT, add_alarm_handle(update_clint));

  boot_time = get_time();
}

word_t do_mtime_trap(word_t dnpc, bool is_ecall) {
  mip_t *mip_tmp = (mip_t *)&cpu.csr[mip];
  mstatus_t *mstatus_tmp = (mstatus_t *)&cpu.csr[mstatus];
  mie_t *mie_tmp = (mie_t *)&cpu.csr[mie];

  IFDEF(CONFIG_DIFFTEST, extern bool get_is_skip_ref();)

  if (mstatus_tmp->bit.mie && mip_tmp->bit.mtip && mie_tmp->bit.mtie &&
      (!is_ecall) && (MUXDEF(CONFIG_DIFFTEST, !get_is_skip_ref(), 1))) {
    mstatus_t *mstatus_temp = (mstatus_t *)&cpu.csr[mstatus];
    mstatus_temp->bit.mpie = mstatus_temp->bit.mie;
    mstatus_temp->bit.mpp = 0b11;
    mstatus_temp->bit.mie = 0;
    cpu.csr[mepc] = dnpc;                // 存放触发异常 pc 的值
    cpu.csr[mcause] = (7 | (1lu << 63)); // 中断号
    // printf("do_mtime_trap:%x\n", dnpc);
    difftest_rise_mtime_trap();
    return cpu.csr[mtvec]; // 返回统一的异常处理程序地址
  }

  return dnpc;
}
