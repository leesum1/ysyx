#include <common.h>
#include "syscall.h"
void do_syscall(Context* c) {
  uintptr_t a[4];
  // 得到系统调用号
  a[0] = c->GPR1;
  a[1] = c->GPRx;
  printf(" syscall ID = %d\n", a[0]);
  switch (a[0]) {
  case -1:
    printf("do nothing\n");
    break;
  case SYS_yield:
    printf("SYS_yield\n");
    yield();c->GPRx = 0;
    break;
  case SYS_exit:
    printf("SYS_exit\n");
    halt(a[1]);
    break;
  default:
    panic("Unhandled syscall ID = %d\n", a[0]);
    break;
  }
}
