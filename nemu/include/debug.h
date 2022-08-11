/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <common.h>
#include <stdio.h>
#include <utils.h>

#define Log(format, ...)                                  \
  _Log(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_BLUE) "\n", \
       __FILE__, __LINE__, __func__, ##__VA_ARGS__)
 //完整的调试信息：设备类型，当前源文件名，当前源函数名，当前源代码行号，格式化输出内容，格式化参数

#define DEBUG_L(format, argent...)  printf(" Node:S, File: "__FILE__                \
                                          ", Func: %s(), Line: %03d: " format "", \
                                          __func__, __LINE__, ##argent) 
//简洁的调试信息：设备类型，当前源函数名，格式化输出内容，格式化参数
#define DEBUG_M(format, argent...) printf(" Node:S, Func: %s(), " format "", __func__, ##argent)
//最简洁的调试信息：格式化输出内容，格式化参数
#define DEBUG_S(format, argent...) printf(" " format "", ##argent)


extern void assert_fail_msg();
#define Assert(cond, format, ...)                                                                   \
  do                                                                                                \
  {                                                                                                 \
    if (!(cond))                                                                                    \
    {                                                                                               \
      MUXDEF(CONFIG_TARGET_AM, printf(ANSI_FMT(format, ANSI_FG_RED) "\n", ##__VA_ARGS__),           \
             (fflush(stdout), fprintf(stderr, ANSI_FMT(format, ANSI_FG_RED) "\n", ##__VA_ARGS__))); \
      IFNDEF(CONFIG_TARGET_AM, extern FILE *log_fp; fflush(log_fp));                                \
      assert_fail_msg();                                                                            \
      assert(cond);                                                                                 \
    }                                                                                               \
  } while (0)

#define panic(format, ...) Assert(0, format, ##__VA_ARGS__)

#define TODO() DEBUG_S("please implement me\n") //panic("please implement me\n")

#endif
