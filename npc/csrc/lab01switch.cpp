#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab01switch.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>
void nvboard_bind_all_pins(Vlab01switch *top);
void lab01_nvboard_switch(void);
// lab01 开关实验
int sim_time = 999; //仿真时间
int main(int argc, char **argv, char **env)
{

    lab01_nvboard_switch();

    return 0;
}

void lab01_switch_sim(int argc, char **argv, char **env)
{
    //打开Verilog顶层文件
    VerilatedContext *contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vlab01switch *top = new Vlab01switch{contextp};

    // 记录波形
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC();
    top->trace(tfp, 0);
    tfp->open("1.vcd");
    //开始仿真
    while (!contextp->gotFinish() && contextp->time() < sim_time)
    {
        //为顶层模块 a b 添加输入
        int a = rand() & 1;
        int b = rand() & 1;
        top->a = a;
        top->b = b;
        //仿真时间+1
        contextp->timeInc(1);
        //开始评估结果
        top->eval();
        //添加波形数据至 VCD 文件中
        tfp->dump(contextp->time());
        //打印结果
        printf("a = %d, b = %d, f = %d\n", a, b, top->f);
        //验证
        assert(top->f == a ^ b);
    }
    top->final();
    //保存文件
    tfp->close();
    delete top;
    delete contextp;
}

static Vlab01switch top;

void lab01_nvboard_switch(void)
{
    nvboard_bind_all_pins(&top); //绑定引脚
    nvboard_init();
    while (1)
    {
        top.eval();       //模拟仿真
        nvboard_update(); //更新 NVboard GUI
    }
}