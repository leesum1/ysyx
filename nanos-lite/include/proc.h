#ifndef __PROC_H__
#define __PROC_H__

#include <common.h>
#include <memory.h>

#define STACK_SIZE (8 * PGSIZE)

typedef union {
  uint8_t stack[STACK_SIZE] PG_ALIGN;
  struct {
    Context* cp;
    AddrSpace as;
    // we do not free memory, so use `max_brk' to determine when to call _map()
    uintptr_t max_brk;
  };
} PCB;

extern PCB* current;


extern void naive_uload(PCB* pcb, const char* filename);
extern void context_kload(PCB* pcb_p, void (*entry)(void*), void* arg);
extern void context_uload(PCB* pcb_p, const char* filename);

extern Context* schedule(Context* prev);
#endif
