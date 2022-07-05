#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab04ecode83.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>

//声明
static void lab03_nvboard_ecode83(void);
extern void nvboard_bind_all_pins(Vlab04ecode83 *top);

int main(int argc, char **argv, char **env)
{
  lab03_nvboard_ecode83();
  return 0;
}

static Vlab04ecode83 top;

static void lab03_nvboard_ecode83(void)
{
  nvboard_bind_all_pins(&top); //绑定引脚
  nvboard_init();
  while (1)
  {
    nvboard_update(); //更新 NVboard GUI
    top.eval();
  }
  nvboard_quit();
}