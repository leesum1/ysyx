#ifndef ARCH_H__
#define ARCH_H__
#include <stdint.h>

struct Context {
  // TODO: fix the order of these members to match trap.S
  uintptr_t mcause, gpr[32], mstatus, mepc;
  void* pdir;
};

#define GPR1 gpr[17] // a7
#define GPR2 gpr[0]
#define GPR3 gpr[0]
#define GPR4 gpr[0]
#define GPRx gpr[0]
#endif
