#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab06count100.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>

//声明
static void lab06_nvboard_count100(void);
extern void nvboard_bind_all_pins(Vlab06count100 *top);
static Vlab06count100 top;

static void single_cycle()
{
  top.clk = 0;
  top.eval();
  top.clk = 1;
  top.eval();
}

static void reset(int n)
{
  top.rst = 1;
  while (n-- > 0)
    single_cycle();
  top.rst = 0;
}

int main(int argc, char **argv, char **env)
{
  lab06_nvboard_count100();
  return 0;
}

static void lab06_nvboard_count100(void)
{
  nvboard_bind_all_pins(&top); //绑定引脚
  nvboard_init();
  reset(10);
  while (1)
  {
    nvboard_update(); //更新 NVboard GUI
    single_cycle();
  }
  nvboard_quit();
}