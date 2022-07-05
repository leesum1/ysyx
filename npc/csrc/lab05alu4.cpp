#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab05alu4.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>

//声明
static void lab05_nvboard_alu4(void);
extern void nvboard_bind_all_pins(Vlab05alu4 *top);

int main(int argc, char **argv, char **env)
{
  lab05_nvboard_alu4();
  return 0;
}

static Vlab05alu4 top;

static void lab05_nvboard_alu4(void)
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