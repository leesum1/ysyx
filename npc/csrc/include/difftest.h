#ifndef __Difftest_H__
#define __Difftest_H__

#include <dlfcn.h>
#include <iostream>

using namespace std;

class Difftest {


private:
    struct CPU_state {
        uint64_t gpr[32];
        uint64_t pc;
    };
    enum {
        DIFFTEST_TO_DUT,
        DIFFTEST_TO_REF
    };
    /* 函数指针 */
    typedef void (*ref_Difftest_memcpy)(uint32_t addr, void* buf, size_t n, bool direction);
    typedef void (*ref_Difftest_regcpy)(void* dut, bool direction);
    typedef void (*ref_Difftest_exec)(uint64_t n);
    typedef void (*ref_Difftest_raise_intr)(uint64_t NO);
    typedef void (*ref_difftest_init)(int);

    ref_Difftest_memcpy diff_memcpy;
    ref_Difftest_regcpy diff_regcpy;
    ref_Difftest_exec diff_exec;
    ref_Difftest_raise_intr diff_raise_intr;
    ref_difftest_init diff_init;
    volatile bool is_skip_ref = false;
public:
    Difftest(/* args */);
    ~Difftest();
    void init(const char* ref_so_file, long img_size, int port);
    CPU_state getDutregs();
    CPU_state getRefregs();
    bool checkregs();
    void difftest_step();
    void difftest_skip_ref();
    void printregs(CPU_state& cpu_regs);
    const char* getRegName(int idx);
};

#endif