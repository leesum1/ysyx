#include <iostream>
#include <verilated_vcd_c.h>
#include <verilated.h>
#include <Vtop.h>
#include "verilated_dpi.h"



extern uint64_t* cpu_gpr;

class Simtop {
private:
    Vtop* top;
    VerilatedContext* contextp;
    VerilatedVcdC* tfp;
    uint64_t* registerfile;
public:
    Simtop();
    ~Simtop();
    Vtop* getTop();
    void reset();
    void changeCLK();
    void dampWave();
    void stepCycle();
    void printRegisterFile();
};