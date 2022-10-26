#ifndef  __SIMTOP_H__
#define  __SIMTOP_H__

#include <iostream>
#include <list>
#include <verilated_vcd_c.h>
#include <verilated.h>
#include "verilated_fst_c.h"
#include <Vtop.h>
#include <iomanip>
#include "verilated_dpi.h"
#include "simMem.h"
#include "simAXI4/simaxi4.h"
#include "watchpoint.h"
#include "expr.h"
#include "difftest.h"
#include "itrace.h"
#include "ringbuff.hpp"


class Simtop {
private:
    Vtop* top;
    VerilatedContext* contextp;
    VerilatedFstC* tfp;
    uint64_t* registerfile;
    uint64_t pc;
    uint64_t clk_count = 0;
    uint64_t commit_count = 0;
    struct inst_t {
        uint64_t inst_pc;
        uint32_t inst_data;
    };
    struct commited_info_t {
        jm::circular_buffer <inst_t, 10> inst;
        jm::circular_buffer <uint64_t, 10> nextpc;
    };

    struct sdbTool_t {
        string name;
        bool isok;
    };
    vector<sdbTool_t> sdbToollist = {
        {"difftest",false},
        {"wp",false},
        {"wave",false},
        {"reg",false},
        {"itrace",false},
        {"mtrace",false},
        {"ftrace",false},
        {"dtrace",false}
    };
private:
    void stepCycle(bool val);
    const char* getRegName(int idx);
    void changeCLK();
    void posedgeCLK();
    void negedgeCLK();
    void dampWave();
public:
    uint64_t mem_pc; // 记录当前访存指令的 PC,用于 difftest device 的 skip 处理 
    uint32_t top_status;
    uint64_t icache_count = 0;
    uint64_t icache_hit_count = 0;
    uint64_t icache_unhit_count = 0;

    uint64_t dcache_count = 0;
    uint64_t dcache_hit_count = 0;
    uint64_t dcache_unhit_count = 0;

    uint64_t bpu_count = 0;
    uint64_t bpu_hit_count = 0;
    enum {
        TOP_STOP,
        TOP_RUNNING
    };
    SimMem* mem;
    SimAxi4* u_axi4;
    Watchpoint u_wp;
    expr_namespace::Expr u_expr;
    Difftest u_difftest;
    Itrace u_itrace;
    commited_info_t commited_list;

    Simtop();
    ~Simtop();
    Vtop* getTop();
    void reset();
    bool npcHitGood();
    uint64_t getRegVal(int idx);
    uint64_t getRegVal(const char* str);
    void setPC(uint64_t val);
    void setGPRregs(uint64_t* ptr);
    void addCommitedInst(uint64_t inst_pc, uint32_t inst_data);
    void printRegisterFile();
    void scanMem(paddr_t addr, uint32_t len);
    void excute(int32_t t);
    void excute();
    void sdbOn(const char* sdbname);
    void sdbOff(const char* sdbname);
    void sdbStatus();
    void sdbRun(void);
    bool isSdbOk(const char* sdbname);
    void showSimPerformance();
};

#endif