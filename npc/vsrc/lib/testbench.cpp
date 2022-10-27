/*
 * @Author: leesum 1255273338@qq.com
 * @Date: 2022-10-27 18:40:34
 * @LastEditors: leesum 1255273338@qq.com
 * @LastEditTime: 2022-10-27 19:38:36
 * @FilePath: /npc/vsrc/lib/testbench.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */




#include "stdio.h"
#include <Vtest.h>

#include "verilated.h"

#include "verilated_fst_c.h" //可选，如果要导出vcd则需要加上




void push(Vtest* top, int data) {

    top->en = rand() % 2;
    top->d = data;
    top->push = 1;
    top->pop = 0;
}

int pop(Vtest* top) {

    top->en = rand() % 2;
    top->pop = 1;
    top->push = 0;
    return top->q;
}

void stake_disable(Vtest* top) {
    top->en = 0;
}

void top_rst(Vtest* top) {
    top->rst = 1;
    top->eval();
    top->rst = 0;
    top->eval();
}


void clk_pos(Vtest* top) {
    top->clk = 1;
}

void clk_neg(Vtest* top) {
    top->clk = 0;
}


int main() {
    VerilatedContext* contextp = new VerilatedContext;
    Vtest* top = new Vtest{ contextp };


    VerilatedFstC* tfp = new VerilatedFstC; //初始化VCD对象指针
    contextp->traceEverOn(true); //打开追踪功能
    top->trace(tfp, 0); //
    tfp->open("wave.vcd"); //设置输出的文件wave.vcd
    int count = 30;
    top_rst(top);
    while (!contextp->gotFinish() && count--) {

        if (rand() % 3) {
            push(top, count);
        }
        else {
            pop(top);
        }
        
        clk_pos(top);
        top->eval();
        tfp->dump(contextp->time()); //dump wave
        contextp->timeInc(1); //推动仿真时间



        clk_neg(top);
        top->eval();
        tfp->dump(contextp->time()); //dump wave
        contextp->timeInc(1); //推动仿真时间



    }


    printf("tset\n");

    delete top;
    tfp->close();
    delete contextp;
    return 0;
}
