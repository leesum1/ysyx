#include "difftest.h"
#include "assert.h"
#include "simtop.h"
#include "simconf.h"

extern Simtop* mysim_p;
static const char* regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };
Difftest::Difftest(/* args */) {

    cout << "difftest start" << endl;
}
Difftest::~Difftest() {

    cout << "difftest stop" << endl;
}

/**
 * @brief 初始化 difftest
 *
 * @param ref_so_file 动态链接库文件名称
 * @param img_size 程序镜像大小
 * @param port 未使用
 */
void Difftest::init(const char* ref_so_file, long img_size, int port) {
    assert(ref_so_file != NULL);
    void* handle;
    handle = dlopen(ref_so_file, RTLD_LAZY);
    assert(handle);
    diff_memcpy = (ref_Difftest_memcpy)dlsym(handle, "difftest_memcpy");
    assert(diff_memcpy);
    diff_regcpy = (ref_Difftest_regcpy)dlsym(handle, "difftest_regcpy");
    assert(diff_regcpy);
    diff_exec = (ref_Difftest_exec)dlsym(handle, "difftest_exec");
    assert(diff_exec);
    diff_raise_intr = (ref_Difftest_raise_intr)dlsym(handle, "difftest_raise_intr");
    assert(diff_raise_intr);
    diff_init = (ref_difftest_init)dlsym(handle, "difftest_init");
    assert(diff_init);

    diff_init(port);

    uint64_t membase = mysim_p->mem->getMEMBASE();
    /* 将程序镜像文件拷贝过去 */
    diff_memcpy(membase, mysim_p->mem->guest_to_host(membase), img_size, DIFFTEST_TO_REF);
    CPU_state regs = getDutregs();
    /* 让 dut 和 ref 寄存器初始值一样 */
    regs.pc = 0x80000000;//TODO:先凑合，后面再改
    diff_regcpy(&regs, DIFFTEST_TO_REF);
    cout << COLOR_BLUE "difftest init!" COLOR_END << endl;
}

/**
 * @brief 获取 dut 寄存器组
 *
 * @return Difftest::CPU_state
 */
Difftest::CPU_state Difftest::getDutregs() {
    CPU_state regs;
    for (size_t i = 0; i < 32; i++) {
        regs.gpr[i] = mysim_p->getRegVal(i);
    }
    regs.pc = mysim_p->getRegVal("pc");
    return regs;
}
/**
 * @brief 获取 nemu 寄存器组
 *
 * @return Difftest::CPU_state
 */
Difftest::CPU_state Difftest::getRefregs() {
    CPU_state regs;
    diff_regcpy(&regs, DIFFTEST_TO_DUT);
    return regs;
}
/**
 * @brief 比较 ref 与 dut 的寄存器
 *
 * @param ref
 * @return true 完全相同
 * @return false 不同
 */
bool Difftest::checkregs() {
    bool ret = true;
    CPU_state dutregs = getDutregs();
    CPU_state refregs = getRefregs();
    for (size_t i = 0; i < 32; i++) {
        if (dutregs.gpr[i] != refregs.gpr[i]) {
            cout << "reg err!!" << endl;
            cout << "----------------------------------dutregs----------------------------------" << endl;
            printregs(dutregs);
            cout << "----------------------------------refregs----------------------------------" << endl;
            printregs(refregs);
            return false;
        }
    }
    // TODO,流水线中没有找到好的比较 PC 的方法
    // if (dutregs.pc != refregs.pc) {
    //     cout << "pc:err" << endl;
    //     cout << "----------------------------------dutregs----------------------------------" << endl;
    //     printregs(dutregs);
    //     cout << "----------------------------------refregs----------------------------------" << endl;
    //     printregs(refregs);
    //     return false;
    // }
    return true;
}

const char* Difftest::getRegName(int idx) {
    return regs[idx];
}

/**
 * @brief 格式化打印寄存器
 *
 * @param cpu_regs 寄存器组
 */
void Difftest::printregs(CPU_state& cpu_regs) {
    /* 格式化输出 */
    for (size_t i = 0; i < 16; i++) {
        cout << setw(5) << left << getRegName(i)
            << setw(20) << left << hex << cpu_regs.gpr[i]
            << setw(5) << left << getRegName(i + 16)
            << setw(20) << left << cpu_regs.gpr[i + 16]
            << endl;
    }
    cout << "\npc:" << "\t" << hex << cpu_regs.pc << endl;
}
/**
 * @brief 让 nemu 执行一条指令,并且进行 difftest
 *
 */
void Difftest::difftest_step() {
    /* 寄存器不一样 */

    /* 跳过当前指令的 difftest ,以 dut 为准 */
    CPU_state dutregs = getDutregs();

    if (!skip_pc.empty() && mysim_p->commited_list.inst.front().inst_pc == skip_pc.front()) {
        // printf("is_skip_ref\n");
        // printf("skip_pc:%p\n", (void*)skip_pc.front());
        // printf("next_pc:%p\n", (void*)dutregs.pc);
        diff_regcpy(&dutregs, DIFFTEST_TO_REF);
        skip_pc.pop_front();
        return;
    }

    diff_exec(1);
    if (!checkregs()) {
        /* 停止指令执行 */
        mysim_p->top_status = mysim_p->TOP_STOP;
    }
}

void Difftest::difftest_skip_ref() {
    skip_pc.push_back(mysim_p->mem_pc);
}