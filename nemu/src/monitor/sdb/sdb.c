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

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

#include <utils.h>
#include <memory/paddr.h>
static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char *rl_gets()
{
  static char *line_read = NULL;

  if (line_read)
  {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read)
  {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args)
{
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args)
{
  nemu_state.state = NEMU_QUIT; // leesum
  return -1;
}
/**
 * @brief  si [N]
 * 让程序单步执行N条指令后暂停执行,当N没有给出时, 缺省为1
 */
static int
cmd_si(char *args)
{
  int N;
  if (NULL == args)
  {
    N = 1; //默认值 1
  }
  else
  {
    sscanf(args, "%d", &N);
  }
  printf("cpu_exec:%d,\n", N);
  cpu_exec(N);
  return 0;
}
/**
 * @brief info SUBCMD
 * 打印寄存器状态 打印监视点信息
 */
static int cmd_info(char *args)
{
  if (NULL == args)
    return 0;

  char val[20];
  sscanf(args, "%s", val);
  printf("info:%s,\n", val);
  if (0 == strcmp(val, "r"))
  {
    isa_reg_display();
  }

  return 0;
}
/**
 * @brief x N EXPR
 * 求出表达式EXPR的值, 将结果作为起始内存地址,
 * 以十六进制形式输出连续的N个4字节
 */
static int cmd_x(char *args)
{
  if (NULL == args)
    return 0;
  uint64_t addr;
  int32_t len;
  //解析参数
  sscanf(args, "%d %lX", &len, &addr);
  printf("len:%d,addr:0x%lX\n", len, addr);

  int32_t i = 0;
  uint64_t data;
  do
  {
    printf("i=:%d\r\n", i);
    data = paddr_read(addr, 8);
    printf("addr:%lx\t%lx", (addr + i), data);
    i = i + 8;
  } while (i < len);

  return 0;
}

/**
 * @brief p EXPR
 * 求出表达式EXPR的值, EXPR支持的
 * 运算请见调试中的表达式求值小节
 */
static int cmd_p(char *args)
{
  nemu_state.state = NEMU_QUIT; // leesum
  return -1;
}

/**
 * @brief w EXPR
 * 当表达式EXPR的值发生变化时, 暂停程序执行
 */
static int cmd_w(char *args)
{
  nemu_state.state = NEMU_QUIT; // leesum
  return -1;
}

/**
 * @brief d N
 * 删除序号为N的监视点
 */
static int cmd_d(char *args)
{
  nemu_state.state = NEMU_QUIT; // leesum
  return -1;
}

#define NR_CMD ARRLEN(cmd_table)
static int cmd_help(char *args);
static struct
{
  const char *name;
  const char *description;
  int (*handler)(char *);
} cmd_table[] = {
    {"help", "Display informations about all supported commands", cmd_help},
    {"c", "Continue the execution of the program", cmd_c},
    {"q", "Exit NEMU", cmd_q},
    {"si", "execut the program by  N step", cmd_si},
    {"info", "show the information of register or watchpoint", cmd_info},
    {"x", "Calculate the value of the expression EXPR, take the result as the starting memory address\n, \
  and output N consecutive 4 - bytes in hexadecimal form ",
     cmd_x},
    {"p", "Calculate the value of the expression EXPR", cmd_p},
    {"w", "Suspend program execution when the value of the expression EXPR changes", cmd_w},
    {"d", "Delete the watchpoint with sequence number N", cmd_d},

    /* TODO: Add more commands */

};
//需要放在最后
static int cmd_help(char *args)
{
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL)
  {
    /* no argument given */
    for (i = 0; i < NR_CMD; i++)
    {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else
  {
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(arg, cmd_table[i].name) == 0)
      {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode()
{
  is_batch_mode = true;
}

void sdb_mainloop()
{
  if (is_batch_mode)
  {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL;)
  {

    /* str 字符串的结束地址 */
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL)
    {
      continue;
    }

    printf("str_end:%s\n", str_end);
    /* treat the remaining string as the arguments,
     * which may need further parsing
     *  参数args 字符串的结束地址
     * 通过比较结束地址来判断是否有参数
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end)
    {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i++)
    {
      if (strcmp(cmd, cmd_table[i].name) == 0)
      {
        if (cmd_table[i].handler(args) < 0)
        {
          return;
        }
        break;
      }
    }

    if (i == NR_CMD)
    {
      printf("Unknown command '%s'\n", cmd);
    }
  }
}

void init_sdb()
{
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
