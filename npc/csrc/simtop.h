#include <iostream>
#include <verilated_vcd_c.h>
#include <verilated.h>
#include <Vtop.h>

class Simtop {
private:
    Vtop* top;
    VerilatedContext* contextp;
    VerilatedVcdC* tfp;
public:
    Simtop();
    ~Simtop();
    Vtop* getTop();
    void reset();
    void changeCLK();
    void dampWave();
};