#ifndef __Difftest_H__
#define __Difftest_H__

#include <dlfcn.h>
#include <iostream>

using namespace std;

class Difftest {


private:
    struct CPU_state {
        uint64_t gpr;
        uint64_t pc;
    };
    /* 函数指针 */
    void (*ref_Difftest_memcpy)(uint32_t addr, void* buf, size_t n, bool direction) = NULL;
    void (*ref_Difftest_regcpy)(void* dut, bool direction) = NULL;
    void (*ref_Difftest_exec)(uint64_t n) = NULL;
    void (*ref_Difftest_raise_intr)(uint64_t NO) = NULL;
public:
    Difftest(/* args */);
    ~Difftest();
    void init(char* ref_so_file, long img_size, int port);
    void checkregs();
    void difftest_step();
};

#endif