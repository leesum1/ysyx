#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <verilated.h>
#include <Vtop.h>
#include "verilated_vcd_c.h"
#include "simtop.h"
#include "cppreadline/Console.hpp"
#include "mysdb.h"
#include "simMem.h"
#include "simconf.h"


namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

const char* nemu_so_path = "/lib/libnemu.so";
const char* img_path = " ";

Simtop* mysim_p;
int main(int argc, char* argv[]) {

  /* 解析参数 获取镜像路径*/
  for (int i = 0;i < argc;i++) {
    printf("argv:%s\n", argv[i]);
    if (i == 1) {
      img_path = argv[i];
    }
  }

  /* 不知道为什么将 Simtop mysim 声明为全局变量会崩溃(已有思路,全局对象的特性)*/
  mysim_p = new Simtop;
  /* 加载镜像 */
  mysim_p->mem->setImagePath(img_path);
  mysim_p->mem->loadImage();
  mysim_p->reset();

  /* 注册命令 */
  cr::Console c(">:");
  c.registerCommand("info", cmd_info);
  c.registerCommand("x", cmd_x);
  c.registerCommand("si", cmd_si);
  c.registerCommand("c", cmd_c);
  c.registerCommand("p", cmd_p);
  c.registerCommand("help", cmd_help);
  c.registerCommand("w", cmd_w);
  c.registerCommand("d", cmd_d);
  c.registerCommand("sdb", cmd_sdb);
  int retCode;

#ifdef TOP_TRACE
  mysim_p->u_difftest.init(nemu_so_path, mysim_p->mem->getImgSize(), 0);
  c.executeCommand("sdb on difftest");
#endif

#ifdef AUTO_RUN
  //c.executeCommand("c");
#else
  do {
    retCode = c.readLine();
    // We can also change the prompt based on last return value:
    if (retCode == ret::Ok)
      c.setGreeting(">");
    else
      c.setGreeting("!>");
  } while (retCode != ret::Quit);
#endif

  mysim_p->excute(1);
  bool hitgood = mysim_p->npcHitGood();
  delete mysim_p;
  return hitgood;
}




