
#include "simtop.h"
using namespace std;

const char* regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };

Simtop::Simtop() {
    cout << "SimtopStart!" << endl;
    mem = new SimMem;
    contextp = new VerilatedContext;
    top = new Vtop;
    tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("sim.vcd");

    this->top_status = TOP_RUNNING;
}

Simtop::~Simtop() {
    tfp->close();
    delete tfp;
    delete top;
    cout << "SimtopEnd!" << endl;
}

void Simtop::reset() {
    int i = 5;
    top->rst = 1;
    while (i-- > 0) {
        stepCycle(false);
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

/**
 * @brief cpu 时钟跳动一个周期(一个上升沿和一个下降沿)
 *
 * @param val 是否打印寄存器值
 */
void Simtop::stepCycle(bool val) {
    if (top_status != TOP_RUNNING) {
        return;
    }

    changeCLK();
    dampWave();
    changeCLK();
    dampWave();
    if (val) {
        printRegisterFile();
    }
    if (1) {
        this->u_wp.praseAllwp();
    }

}

const char* Simtop::getRegName(int idx) {
    return regs[idx];
}

/**
 * @brief 获取寄存器值,下表方式
 *
 * @param idx
 * @return uint64_t
 */
uint64_t Simtop::getRegVal(int idx) {
    this->registerfile = cpu_gpr;
    return registerfile[idx];
}
/**
 * @brief 获取寄存器值,名称方式
 *
 * @param str
 * @return uint64_t
 */
uint64_t Simtop::getRegVal(const char* str) {
    this->registerfile = cpu_gpr;
    this->pc = cpu_pc;
    uint64_t val;
    if (!strcmp(str, "pc")) {
        val = this->pc;
        return val;
    }
    for (int i = 0; i < 32; i++) {
        /*对比寄存器名字*/
        if (!strcmp(str, regs[i])) {
            val = registerfile[i];
            return val;
        }
    }
    return -1;
}
/**
 * @brief 打印所有寄存器的值,包括pc
 *
 */
void  Simtop::printRegisterFile() {

    this->registerfile = cpu_gpr;
    this->pc = cpu_pc;
    /* 格式化输出 */
    for (size_t i = 0; i < 16; i++) {
        cout << setw(5) << left << getRegName(i)
            << setw(15) << left << hex << getRegVal(i)
            << setw(5) << left << getRegName(i + 16)
            << setw(15) << left << getRegVal(i + 16)
            << endl;
    }
    cout << "\npc:" << "\t" << hex << cpu_pc << endl;
}


/**
 * @brief HIT GOOD / BAD TRAP
 * 在程序退出时调用
 */
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

/**
 * @brief 扫描内存并显示
 *
 * @param addr 地址 16进制
 * @param len 长度
 */
void Simtop::scanMem(paddr_t addr, uint32_t len) {

    /* 每次读取 4byte */
    for (size_t i = 0; i < len; i++) {
        printf("addr:0x%08lx\tData: %08lx\n", addr,
            mem->paddr_read(addr, 4));
        addr += 4;
    }
}
/**
 * @brief 执行指令,执行次数效于4时,打印寄存器值
 *
 * @param t 执行的次数
 */
void Simtop::excute(int32_t t) {
    bool val;
    val = (t > 4) ? false : true;
    top_status = TOP_RUNNING;
    while ((!top->contextp()->gotFinish()) && (t--)) {
        if (top_status != TOP_RUNNING) {
            cout << "top_status:STOP" << endl;
            break;
        }
        stepCycle(val);
    }
}
/**
 * @brief 连续运行,直到退出
 *
 */
void Simtop::excute() {
    top_status = TOP_RUNNING;
    while ((!top->contextp()->gotFinish())) {
        if (top_status != TOP_RUNNING) {
            cout << "top_status:STOP" << endl;
            break;
        }
        stepCycle(false);
    }
}
Vtop* Simtop::getTop() {

    return this->top;
}


