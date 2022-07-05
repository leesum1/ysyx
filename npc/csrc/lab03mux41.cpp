#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vlab03mux41.h>
#include "verilated_vcd_c.h"
#include <nvboard.h>

//声明
static void lab03_nvboard_mux41(void);
extern void nvboard_bind_all_pins(Vlab03mux41 *top);

int main(int argc, char **argv, char **env)
{
    lab03_nvboard_mux41();
    return 0;
}

static Vlab03mux41 top;

static void lab03_nvboard_mux41(void)
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