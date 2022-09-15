
#include "simtop.h"
#include "simconf.h"

using namespace std;



static const char* regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };

Simtop::Simtop() {
    cout << "SimtopStart!" << endl;
    mem = new SimMem;

    /* 波形数据 */
#ifdef TOP_TRACE
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
#endif
    top = new Vtop;
#ifdef TOP_TRACE
    top->trace(tfp, 0);
    tfp->open("sim.vcd");
#endif
    this->top_status = TOP_RUNNING;
}

Simtop::~Simtop() {
#ifdef TOP_TRACE
    tfp->close();
    delete tfp;
    delete contextp;
#endif
    //delete mem;
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
#ifdef TOP_TRACE
    contextp->timeInc(1);
    tfp->dump(contextp->time());
#endif
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
    changeCLK(); // 上升沿
    /* 上升沿和下降沿都要保存波形数据 */
#ifdef TOP_TRACE
    if (isSdbOk("wave")) {
        this->dampWave();
    }
#endif
    changeCLK();// 下降沿
#ifdef TOP_TRACE
    if (isSdbOk("wave")) {
        this->dampWave();
    }
    /* 提交的时候进行 difftest
     * commited_list.nextpc 和 commited_list.inst，不为空
     * 表示 NPC 指令已经提交，并且得到了下一条提交指令的 pc
     * 分别位于 inst，nextpc 的队首
     */
    while ((!commited_list.nextpc.empty()) && !(commited_list.inst.empty())) {
        setPC(commited_list.nextpc.front());
        // cout << "nextpc" << hex << cpu_commit.nextpc.front()
        //     << "commitpc" << cpu_commit.inst.front().inst_pc << endl;
        sdbRun();
        commited_list.inst.pop_front();
        commited_list.nextpc.pop_front();
    }
#endif
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
    return registerfile[idx];
}
/**
 * @brief 获取寄存器值,名称方式
 *
 * @param str
 * @return uint64_t
 */
uint64_t Simtop::getRegVal(const char* str) {
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
    /* 格式化输出 */
    for (size_t i = 0; i < 16; i++) {
        cout << setw(5) << left << getRegName(i)
            << setw(20) << left << hex << getRegVal(i)
            << setw(5) << left << getRegName(i + 16)
            << setw(20) << left << getRegVal(i + 16)
            << endl;
    }
    cout << "\npc:" << "\t" << hex << this->pc << endl;
}


/**
 * @brief HIT GOOD / BAD TRAP
 *        在程序退出时调用
 */
bool Simtop::npcHitGood() {
    uint64_t a0 = registerfile[10];
    cout << "a0:" << a0 << endl;
    if (a0 == 0) {
        cout << COLOR_GREEN "PC:" << hex << pc << "\tHIT GOOD" COLOR_END << endl;
        return 0;
    }
    else {
        cout << COLOR_RED "PC:" << hex << pc << "\tBAD TRAP" COLOR_END << endl;

    }
    return 1;
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
 * @brief 执行指令,执行次数小于4时,打印寄存器值
 *
 * @param t 执行的次数
 */
void Simtop::excute(int32_t t) {
    bool val;
    val = (t == 1);
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

/**
 * @brief 打开sdb调试工具
 *
 * @param sdbname 工具名称
 */
void Simtop::sdbOn(const char* sdbname) {
    /* 打开所有 sdb 调试工具 */
    if (!strcmp(sdbname, "all")) {
        for (auto& iter : sdbToollist) {
            iter.isok = true;

        }
        return;
    }
    /* 按名字打开 */
    for (auto& iter : sdbToollist) {
        if (sdbname == iter.name) {
            iter.isok = true;
            return;
        }
    }
    cout << "can not find " << sdbname << endl;
}
/**
 * @brief 关闭sdb调试工具
 *
 * @param sdbname 工具名称
 */
void Simtop::sdbOff(const char* sdbname) {
    /* 关闭所有 sdb 调试工具 */
    if (!strcmp(sdbname, "all")) {
        for (auto& iter : sdbToollist) {
            iter.isok = false;

        }
        return;
    }

    for (auto& iter : sdbToollist) {
        if (sdbname == iter.name) {
            iter.isok = false;
            return;
        }
    }
    cout << "can not find " << sdbname << endl;
}

bool Simtop::isSdbOk(const char* sdbname) {
    /* 这种方式便利时, auto iter 为只读, auto & iter 可修改 */
    for (auto& iter : sdbToollist) {
        if (sdbname == iter.name) {
            return iter.isok;
        }
    }
    cout << "can not find " << sdbname << endl;
    return false;
}

void Simtop::sdbStatus() {
    /* 只读遍历 */
    for (auto iter : sdbToollist) {
        cout << setw(8) << iter.name << ": " << setw(4) << iter.isok << endl;
    }
}
/**
 * @brief 调试工具
 *
 */
void Simtop::sdbRun(void) {
    if (isSdbOk("difftest")) {
        this->u_difftest.difftest_step();
    }
    if (!top->rst && isSdbOk("itrace")) {
        u_itrace.llvmDis();
    }
    if (isSdbOk("wp")) {
        this->u_wp.praseAllwp();
    }
    if (isSdbOk("reg")) {
        this->printRegisterFile();
    }
    //TODO:add more
}

/**
 * @brief 设置 PC寄存器的值，按照 nemu，为已提交指令的下一个指令地址
 *
 * @param val
 */
void Simtop::setPC(uint64_t val) {
    this->pc = val;
}
/**
 * @brief 设置通用寄存器组（共32个）
 *
 * @param ptr 通用寄存器组指针
 */
void Simtop::setGPRregs(uint64_t* ptr) {
    this->registerfile = ptr;
}
/**
 * @brief 记录已经提交的指令
 *
 * @param inst_pc 提交指令的 PC
 * @param inst_data 提交指令的内容
 */
void Simtop::addCommitedInst(uint64_t inst_pc, uint32_t inst_data) {

    inst_t temp_inst;
    temp_inst.inst_data = inst_data;
    temp_inst.inst_pc = inst_pc;
    this->commited_list.inst.push_back(temp_inst);
}