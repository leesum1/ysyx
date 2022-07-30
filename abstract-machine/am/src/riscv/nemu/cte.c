#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

// /*为了代码提示*/
// #include "riscv64-nemu.h"
// typedef struct Context Context;

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context* c) {
  //printf("__am_irq_handle code:%d\n", c->mcause);
  if (user_handler) {
    Event ev = { 0 };
    switch (c->mcause) {
    case  11: ev.event = EVENT_SYSCALL;c->mepc += 4; break; // yield
    default: ev.event = EVENT_ERROR; break;
    }

    // for (size_t i = 0; i < 32; i++) {
    //   printf("%d: %x\n", i, c->gpr[i]);
    // }
    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);
/**
 * @brief 设置异常入口函数地址,在本项目中采用的是 direct 模式
 *
 * @param handler 函数指针
 * @return true
 * @return false
 */
bool cte_init(Context* (*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context* kcontext(Area kstack, void (*entry)(void*), void* arg) {
  return NULL;
}
/**
 * @brief 自陷指令,通过 $a7 寄存器来传递系统调用编号
 *
 */
void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
