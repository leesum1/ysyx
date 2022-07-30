#include <common.h>
#include "syscall.h"
void do_syscall(Context* c) {
  uintptr_t a[4];

  a[0] = c->GPR1;// 系统调用号
  a[1] = c->GPR2;// 函数参数1
  a[2] = c->GPR3;// 函数参数2
  a[3] = c->GPR4;// 函数参数3

  //printf(" syscall ID = %d\n", a[0]);
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
    halt(c->GPRx);
    break;
  case SYS_write:
    //printf("SYS_write\n");
    if (a[1] == 1 || a[1] == 2) {
      for (int i = 0; i < a[3]; i++) {
        putch(*(char*)(a[2] + i));
      }
      // c->GPRx = a[3];
    }
    else c->GPRx = -1;
    break;

  default:
    panic("Unhandled syscall ID = %d\n", a[0]);
    break;
  }
}
