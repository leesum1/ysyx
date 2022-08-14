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


namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

const char* nemu_so_path = "/lib/libnemu.so";
const char* img_path = " ";

Simtop* mysim_p;
int main(int argc, char* argv[]) {

  /* 解析参数 */
  for (int i = 0;i < argc;i++) {
    printf("argv:%s\n", argv[i]);
    if (i == 1) {
      img_path = argv[i];
    }
  }
  /* 不知道为什么将 Simtop mysim 声明为全局变量会崩溃(已有思路,全局对象的特性)*/
  mysim_p = new Simtop;
  /* 加载镜像 */
  mysim_p->mem->imgpath.append(img_path);
  mysim_p->mem->loadImage(mysim_p->mem->imgpath.c_str());

  size_t imgsize = mysim_p->mem->getImgSize(mysim_p->mem->imgpath.c_str());

  mysim_p->reset();
  //mysim_p->u_difftest.init(nemu_so_path, imgsize, 0);
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
  c.registerCommand("sdbon", cmd_sdbon);
  c.registerCommand("sdboff", cmd_sdboff);
  c.registerCommand("sdb", cmd_sdb);
  int retCode;
  do {
    retCode = c.readLine();
    // We can also change the prompt based on last return value:
    if (retCode == ret::Ok)
      c.setGreeting(">");
    else
      c.setGreeting("!>");

    if (retCode == 1) {
      std::cout << "Received error code 1\n";
    }
    else if (retCode == 2) {
      std::cout << "Received error code 2\n";
    }
  } while (retCode != ret::Quit);
  mysim_p->excute(1);
  int hitgood = mysim_p->npcTrap();
  delete mysim_p;
  return hitgood;
}




