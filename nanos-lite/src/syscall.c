#include <common.h>
#include <unistd.h>
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
    //printf("SYS_write fd:%d,buff:%p,cout:%d\n", a[1], a[2], a[3]);
    if (a[1] == 1 || a[1] == 2) {
      for (int i = 0; i < a[3]; i++) {
        putch(*(char*)(a[2] + i));
      }
      c->GPRx = a[3];
    }
    else {
      c->GPRx = -1;
    }
    break;
  case SYS_brk:
    printf("SYS_brk a1:%p,a2:%d,a3:%d\n", a[1], a[2], a[3]);
    c->GPRx = -1;
    break;

  default:
    panic("Unhandled syscall ID = %d\n", a[0]);
    break;
  }
}



// void* _sbrk(intptr_t increment) {
//   extern  end;       //set by linker
//   extern  __heap_end;//set by linker
//   static char* heap_end;		/* Previous end of heap or 0 if none */
//   char* prev_heap_end;

//   if (0 == heap_end) {
//     heap_end = &__heap_start;			/* Initialize first time round */
//   }

//   prev_heap_end = heap_end;
//   heap_end += increment;
//   //check
//   if (heap_end < (&__heap_end)) {

//   }
//   else {
//     // errno = ENOMEM;
//     return (char*)-1;
//   }
//   return (void*)prev_heap_end;
// }
