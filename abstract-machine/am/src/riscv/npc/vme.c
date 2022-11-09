#include <am.h>
#include <klib.h>

bool vme_init(void* (*pgalloc_f)(int), void (*pgfree_f)(void*)) {
  return false;
}

void protect(AddrSpace *as) {
}

void unprotect(AddrSpace *as) {
}

void map(AddrSpace *as, void *va, void *pa, int prot) {
}

Context* ucontext(AddrSpace* as, Area kstack, void* entry) {

  printf("kstack.end:%p,kstack.start:%p,size:%d\n", kstack.end, kstack.start, kstack.end - kstack.start + 1);
  Context* p = (Context*)(kstack.end - sizeof(Context) + 1);
  memset(p, 0, sizeof(Context));

  printf("Context size:%d\n", (kstack.end - (void*)p + 1));
  assert((kstack.end - (void*)p + 1) == sizeof(Context));

  printf("entry:%p\n", entry);
  p->gpr[10] = (uintptr_t)heap.end;
  p->mepc = (uintptr_t)entry;   // mret 后，进入 entry

  p->mstatus = 0xa00001800; // for difftest

  return p;
}
