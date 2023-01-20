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

#include "../local-include/csr.h"
#include "stdio.h"
#include <isa.h>

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  // printf("\nisa_raise_intr ok \n");
  mstatus_t *mstatus_temp = (mstatus_t*)&cpu.csr[mstatus];

  // printf("pre dut mstatus:%x\n", cpu.csr[mstatus]);
  mstatus_temp->bit.mpie = mstatus_temp->bit.mie;
  mstatus_temp->bit.mpp = 0b11;
  mstatus_temp->bit.mie = 0;

  cpu.csr[mepc] = epc;  // 存放触发异常 pc 的值
  cpu.csr[mcause] = NO; // 中断号
  // cpu.csr[mstatus] |= 0x1800;
  // cpu.csr[mstatus] = mstatus_temp.all;
  // printf("after dut mstatus:%x\n", cpu.csr[mstatus]);
  return cpu.csr[mtvec]; // 返回统一的异常处理程序地址
}

word_t isa_intr_ret(void) {

  mstatus_t *mstatus_temp = (mstatus_t*)&cpu.csr[mstatus];
  // printf("pre isa_intr_ret mstatus:%x\n", cpu.csr[mstatus]);
  mstatus_temp->bit.mie = mstatus_temp->bit.mpie;
  mstatus_temp->bit.mpp = 0b00;
  mstatus_temp->bit.mpie = 1;

  // printf("after isa_intr_ret mstatus:%x\n", cpu.csr[mstatus]);
  return cpu.csr[mepc]; // 返回统一的异常处理程序地址
}

word_t isa_query_intr() { return INTR_EMPTY; }
