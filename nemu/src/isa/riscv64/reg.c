/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <isa.h>
#include "local-include/reg.h"
#include <string.h>

const char* regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };

void isa_reg_display() {
  for (int i = 0; i < 32; i++) {
    /* 打印寄存器名称和内容 */
    printf("%d:%s\t%lx\n", i, reg_name(i, 64), gpr(i));
  }
  /* pc 寄存器 */
  printf("%d:%s\t%lx\n", 33, "pc", cpu.pc);
}

word_t isa_reg_str2val(const char* s, bool* success) {

  word_t val;
  if (!strcmp(s, "pc")) {
    val = cpu.pc;
    *success = 1;
    return val;
  }
  for (int i = 0; i < 32; i++) {
    /*对比寄存器名字*/
    if (!strcmp(s, reg_name(i, 64))) {
      val = gpr(i);
      *success = 1;
      return val;
    }
  }
  *success = 0;
  return -1;
}
