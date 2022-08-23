#ifndef  __SIMTOP_H__
#define __SIMTOP_H__

#include <iostream>
#include <list>
#include <verilated_vcd_c.h>
#include <verilated.h>
#include <Vtop.h>
#include <iomanip>
#include "verilated_dpi.h"
#include "simMem.h"
#include "watchpoint.h"
#include "expr.h"
#include "difftest.h"
#include "itrace.h"

extern uint64_t* cpu_gpr;
extern uint64_t cpu_pc;

class Simtop {
private:
    Vtop* top;
    VerilatedContext* contextp;
    VerilatedVcdC* tfp;
    uint64_t* registerfile;
    uint64_t pc;
    uint8_t cpu_commit_valid;


    struct inst_t {
        uint64_t inst_pc;
        uint32_t inst_data;
    };
    struct commited_info_t {
        list<inst_t> inst;
        list<uint64_t>nextpc;
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
    void dampWave();
public:
    uint64_t mem_pc;
    uint32_t top_status;
    enum {
        TOP_STOP,
        TOP_RUNNING
    };
    SimMem* mem;
    Watchpoint u_wp;
    commited_info_t cpu_commit;
    expr_namespace::Expr u_expr;
    Difftest u_difftest;
    Itrace u_itrace;
    Simtop();
    ~Simtop();
    Vtop* getTop();
    void reset();
    int npcTrap();
    uint64_t getRegVal(int idx);
    uint64_t getRegVal(const char* str);
    void setPC(uint64_t val);
    void setCommit_valid(uint8_t val);
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
};

#endif