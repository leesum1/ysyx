#include <memory.h>

static void* pf = NULL;

void* new_page(size_t nr_page) {

  void* last_pf = pf;
  uintptr_t pf_temp = (uintptr_t)pf;
  pf = (void*)(pf_temp + nr_page * PGSIZE);

  assert((uintptr_t)pf == (pf_temp + nr_page * PGSIZE));
  return last_pf;
}

#ifdef HAS_VME
static void* pg_alloc(int n) {
  return NULL;
}
#endif

void free_page(void* p) {
  panic("not implement yet");
}

/* The brk() system call handler. */
int mm_brk(uintptr_t brk) {
  return 0;
}

void init_mm() {
  pf = (void*)ROUNDUP(heap.start, PGSIZE);
  Log("free physical pages starting from %p", pf);

#ifdef HAS_VME
  vme_init(pg_alloc, free_page);
#endif
}
