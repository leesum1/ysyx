#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab02light.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>

void lab01_nvboard_light(void);
extern void nvboard_bind_all_pins(Vlab02light *top);
int main(int argc, char **argv, char **env)
{
  lab01_nvboard_light();
  return 0;
}

static Vlab02light top;

void single_cycle()
{
  top.clk = 0;
  top.eval();
  top.clk = 1;
  top.eval();
}

void reset(int n)
{
  top.rst = 1;
  while (n-- > 0)
    single_cycle();
  top.rst = 0;
}
void lab01_nvboard_light(void)
{
  nvboard_bind_all_pins(&top); //绑定引脚
  nvboard_init();
  reset(10);
  while (1)
  {
    single_cycle();   //时钟周期更新
    nvboard_update(); //更新 NVboard GUI
  }
  nvboard_quit();
}