#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab08keyboard.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>

//声明
static void lab08_nvboard_keyboard(void);
extern void nvboard_bind_all_pins(Vlab08keyboard *top);
static Vlab08keyboard top;

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
  lab08_nvboard_keyboard();
  return 0;
}

static void lab08_nvboard_keyboard(void)
{
  nvboard_bind_all_pins(&top); //绑定引脚
  nvboard_init();
  reset(100);
  while (1)
  {
    nvboard_update(); //更新 NVboard GUI
    // top.eval();
    single_cycle();
  }
  nvboard_quit();
}