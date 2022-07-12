#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vtop.h>
#include "verilated_vcd_c.h"
#include "simtop.h"

//声明
static Vtop* top;
int main(int argc, char** argv, char** env) {

  Simtop mysim;
  top = mysim.getTop();
  int i = 50;
  mysim.reset();
  while (!top->contextp()->gotFinish()) {
    mysim.stepCycle();
  }
}



