#include <proc.h>

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB* current = NULL;

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void* arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%p' for the %dth time!", (uintptr_t)arg, j);
    j++;
    yield();
  }
}


void context_kload(PCB* pcb_p, void (*entry)(void*), void* arg) {


  // pcb_p->stack

  pcb_p->cp = kcontext(RANGE(pcb_p->stack, pcb_p->stack + STACK_SIZE - 1), entry, arg);

}


void init_proc() {
  context_kload(&pcb[0], hello_fun, NULL);
  switch_boot_pcb();

  // Log("Initializing processes...");

  // // load program here
  // naive_uload(NULL, "/bin/menu");
}

Context* schedule(Context* prev) {
  // save the context pointer
  current->cp = prev;

  // always select pcb[0] as the new process
  current = &pcb[0];

  // then return the new context
  return current->cp;

}
