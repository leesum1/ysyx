#include <iostream>
#include <verilated_vcd_c.h>
#include <verilated.h>
#include <Vtop.h>
#include <iomanip>
#include "verilated_dpi.h"



extern uint64_t* cpu_gpr;
extern uint64_t cpu_pc;
class Simtop {
private:
    Vtop* top;
    VerilatedContext* contextp;
    VerilatedVcdC* tfp;
    uint64_t* registerfile;
    uint64_t pc;
public:
    Simtop();
    ~Simtop();
    Vtop* getTop();
    void reset();
    void changeCLK();
    void dampWave();
    void stepCycle();
    const char* getRegName(int idx);
    void printRegisterFile();
    void npcTrap();
};