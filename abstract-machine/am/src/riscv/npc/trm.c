#include <am.h>
#include <klib-macros.h>
#include "npc.h" // add by leesum

extern char _heap_start;
int main(const char* args);

extern char _pmem_start;
#define PMEM_SIZE (512 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

/* 串口 */
void putch(char ch) {
    outb(SERIAL_PORT, ch);
}

void halt(int code) {
    npc_trap(code);
    /* 不应该到这里来 */
    while (1);
}

void _trm_init() {
    int ret = main(mainargs);
    halt(ret);
}
