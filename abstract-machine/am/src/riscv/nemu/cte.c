#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context* c) {
  if (user_handler) {
    Event ev = { 0 };
    switch (c->mcause) {
    default: ev.event = EVENT_ERROR; break;
    }

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

  printf("__am_asm_trap:%p\n", __am_asm_trap);
  // register event handler
  user_handler = handler;

  return true;
}

Context* kcontext(Area kstack, void (*entry)(void*), void* arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
