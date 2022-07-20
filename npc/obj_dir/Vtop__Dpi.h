// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at /home/leesum/ysyx-workbench/npc/vsrc/usr/fetch.v:20:32
    extern void get_pc(long long pc);
    // DPI import at /home/leesum/ysyx-workbench/npc/vsrc/usr/fetch.v:15:32
    extern void pmem_read(long long raddr, long long* rdata);
    // DPI import at /home/leesum/ysyx-workbench/npc/vsrc/usr/memory.v:93:32
    extern void pmem_write(long long waddr, long long wdata, char wmask);
    // DPI import at /home/leesum/ysyx-workbench/npc/vsrc/usr/rv64reg.v:34:32
    extern void set_gpr_ptr(const svOpenArrayHandle a);

#ifdef __cplusplus
}
#endif
