#include <common.h>
#include "syscall.h"
void do_syscall(Context* c) {
  uintptr_t a[4];
  // 得到系统调用号
  a[0] = c->GPR1;
  panic(" syscall ID = %d", a[0]);
  switch (a[0]) {
  case -1:break;
  case SYS_yield:printf("SYS_yield\n"); yield();c->GPRx = 0; break;
  case SYS_exit:halt(0);
  default: panic("Unhandled syscall ID = %d", a[0]);
  }
}
