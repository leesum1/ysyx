
#include "simtop.h"
using namespace std;

const char* regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };

Simtop::Simtop() {
    cout << "SimtopStart!" << endl;
    contextp = new VerilatedContext;
    top = new Vtop;
    tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("sim.vcd");
    top->clk = 0;
    top->rst = 0;
}

Simtop::~Simtop() {
    tfp->close();
    delete tfp;
    delete contextp;
    cout << "SimtopEnd!" << endl;
}

void Simtop::reset() {
    int i = 5;
    top->rst = 1;
    while (i-- > 0) {
        stepCycle();
    }
    top->rst = 0;
}

void Simtop::changeCLK() {
    top->clk = !top->clk;
    top->eval();
}


void Simtop::dampWave() {
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void Simtop::stepCycle() {
    changeCLK();
    dampWave();
    changeCLK();
    dampWave();
    printRegisterFile();
}

const char* Simtop::getRegName(int idx) {
    return regs[idx];
}

void  Simtop::printRegisterFile() {

    this->registerfile = cpu_gpr;
    this->pc = cpu_pc;
    /* 格式化输出 */
    for (size_t i = 0; i < 16; i++) {
        cout << setw(5) << left << getRegName(i)
            << setw(15) << left << hex << registerfile[i]
            << setw(5) << left << getRegName(i + 16)
            << setw(15) << left << registerfile[i + 16]
            << endl;
    }
    cout << "\npc:" << "\t" << hex << cpu_pc << endl;
}


void Simtop::npcTrap() {
    this->registerfile = cpu_gpr;
    this->pc = cpu_pc;
    uint64_t a0 = registerfile[10];
    cout << "a0:" << a0 << endl;
    if (a0 == 0) {
        cout << "PC:" << hex << pc << "\tHIT GOOD" << endl;
    }
    else {
        cout << "PC:" << hex << pc << "\tBAD TRAP" << endl;
    }
}

Vtop* Simtop::getTop() {

    return this->top;
}


