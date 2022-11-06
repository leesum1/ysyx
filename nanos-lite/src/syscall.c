#include <common.h>
#include <unistd.h>
#include <sys/time.h>
#include "syscall.h"
#include <fs.h>
#include <proc.h>
#define STRACE

void do_syscall(Context* c) {
  uintptr_t a[4];

  a[0] = c->GPR1;// 系统调用号
  a[1] = c->GPR2;// 函数参数1
  a[2] = c->GPR3;// 函数参数2
  a[3] = c->GPR4;// 函数参数3

  //printf(" syscall ID = %d\n", a[0]);
  switch (a[0]) {
  case -1:
#ifdef STRACE
    printf("do nothing\n");
#endif
    break;
  case SYS_yield:
#ifdef STRACE
    printf("SYS_yield\n");
#endif
    yield();c->GPRx = 0;
    break;
  case SYS_exit:
#ifdef STRACE
    printf("SYS_exit\n");
#endif
    naive_uload(NULL, "/bin/menu");
    halt(a[1]);
    break;
  case SYS_write:
#ifdef STRACE
    printf("SYS_write fd:%d,buff:%p,cout:%d\n", a[1], a[2], a[3]);
#endif
    c->GPRx = fs_write(a[1], (void*)a[2], a[3]);
    break;
  case SYS_brk:
#ifdef STRACE
    printf("SYS_brk a1:%p,a2:%d,a3:%d\n", a[1], a[2], a[3]);
#endif
    //extern char etext, edata, end;
    //TODO:    修改end地址
    c->GPRx = 0;
    break;
  case SYS_read:
#ifdef STRACE
    printf("SYS_read a1:%d,a2:%p,a3:%d\n", a[1], a[2], a[3]);
#endif
    c->GPRx = fs_read(a[1], (void*)a[2], a[3]);
    break;
  case SYS_open:
#ifdef STRACE
    printf("SYS_open a1:%s,a2:%d,a3:%d\n", a[1], a[2], a[3]);
#endif
    c->GPRx = fs_open((const char*)a[1], a[2], a[3]);
    break;

  case SYS_lseek:
#ifdef STRACE
    printf("SYS_lseek a1:%d,a2:%d,a3:%d\n", a[1], a[2], a[3]);
#endif
    c->GPRx = fs_lseek(a[1], a[2], a[3]);
    break;

  case SYS_close:
#ifdef STRACE
    printf("SYS_close a1:%d,a2:%d,a3:%d\n", a[1], a[2], a[3]);
#endif
    c->GPRx = fs_close(a[1]);
    break;
  case SYS_gettimeofday:
#ifdef STRACE
    printf("SYS_gettimeofday a1:%d,a2:%d,a3:%d\n", a[1], a[2], a[3]);
#endif
    {
      struct timeval* tv = (struct timeval*)a[1];
      //struct timezone* tz = (struct timezone*)a[2]; // 没有设置时区
      uint64_t us = io_read(AM_TIMER_UPTIME).us;
      tv->tv_sec = us / 1000000;
      tv->tv_usec = us % 1000000;
    }
    c->GPRx = 0;
    break;
  case SYS_execve:
#ifdef STRACE
    printf("SYS_execve a1:%s,a2:%d,a3:%d\n", a[1], a[2], a[3]);
#endif
    naive_uload(NULL, (char*)a[1]);
    break;
  default:
    panic("Unhandled syscall ID = %d\n", a[0]);
    break;
  }
}

