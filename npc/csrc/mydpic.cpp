#include <iostream>
#include <verilated_vcd_c.h>
#include <verilated.h>
#include <Vtop.h>
#include "verilated_dpi.h"
#include "simtop.h"

uint64_t* cpu_gpr;
uint64_t cpu_pc;
extern Simtop* mysim_p;
extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
    cpu_gpr = (uint64_t*)(((VerilatedDpiOpenVar*)r)->datap());
}


extern "C" void get_pc(long long pc) {
    cpu_pc = pc;
}


extern "C" void pmem_read(long long raddr, long long* rdata) {
    // 总是读取地址为`raddr & ~0x7ull`的8字节返回给`rdata`
    *rdata = mysim_p->mem->paddr_read(raddr, 8);
    printf("readaddr:%08x\n", raddr);
};
extern "C" void pmem_write(long long waddr, long long wdata, char wmask) {
    // 总是往地址为`waddr & ~0x7ull`的8字节按写掩码`wmask`写入`wdata`
    // `wmask`中每比特表示`wdata`中1个字节的掩码,
    // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
    /* 隐式格式转换很坑 */
    uint32_t temp = (uint8_t)wmask;
    switch (temp) {
    case 1:   mysim_p->mem->paddr_write(waddr, 1, wdata); break; // 0000_0001, 1byte.
    case 3:   mysim_p->mem->paddr_write(waddr, 2, wdata); break; // 0000_0011, 2byte.
    case 15:  mysim_p->mem->paddr_write(waddr, 4, wdata); break; // 0000_1111, 4byte.
    case 255: mysim_p->mem->paddr_write(waddr, 8, wdata);  break; // 1111_1111, 8byte.
    default:  break;
    }
}


