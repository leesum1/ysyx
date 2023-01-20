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

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>


#include <string.h>
#include <stdio.h>

 /* 与 cpp 中的枚举一致 */
enum {
  TK_NOTYPE = 256,
  TK_EQ,     // ==
  TK_NEQ,    // !=
  TK_AND,    // && 与
  TK_NUM,    // 数字
  TK_DEREF,  //指针解引用 *
  TK_HEX,    // 0x开头，十六进制
  TK_REG     // 以"$"开头 寄存器
  /* TODO: Add more token types */
};

static struct rule {
  const char* regex;
  int token_type;
} rules[] = {
  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   * + 、 * 、（、） 在正则表达式中有特殊含义
    */
  {" +", TK_NOTYPE},              // spaces
  {"\\(", '('},                   // left brackets
  {"\\)", ')'},                   // right brackets
  {"\\*", '*'},                   // multi
  {"/", '/'},                     // div
  {"\\+", '+'},                   // plus
  {"-", '-'},                     // minus
  {"==", TK_EQ},                  // equal
  {"!=", TK_NEQ},                 // not equal
  {"0[xX][0-9a-fA-F]+",TK_HEX},   // hex ,十六进制识别必须在十进制前面
  {"\\$[a-zA-z]+[0-9]*",TK_REG},  // reg
  {"[0-9]+", TK_NUM},             // num
  {"&&"},                         // and
};

/* 规则数组的长度 */
#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }

}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[200] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool make_token(char* e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char* substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        //Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        // i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;
        /* 记录匹配规则,空格除外 */
        if (rules[i].token_type != TK_NOTYPE) {
          sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
          tokens[nr_token].type = rules[i].token_type;
          // DEBUG_M("tokens->str:%s,tpye:%d,index:%d\n", tokens[nr_token].str, 
          //   tokens[nr_token].type, nr_token);
          nr_token++;
        }
        break;
      }
    }
    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

word_t expr(char* e, bool* success) {
  if (!make_token(e)) {
    Assert(*success == false, "make_token fail!\n");
    return 0;
  }
  extern uint64_t exprcpp(void* tokens_addr, int num);
  uint64_t result = exprcpp(tokens, nr_token);

  return result;
}



/* 表达式测试 */
void expr_test(void) {
  bool ret;
  uint64_t testinput, testoutput;
  FILE* fp = fopen("/home/leesum/ysyx-workbench/nemu/tools/gen-expr/input", "r");
  if (fp == NULL) {
    printf("Fail to open file!\n");
    exit(0);  //退出程序（结束程序）
  }
  char buf[1024];
  /* 读取每一行
   * 换行键被坑了
   * fgets函数，会默认添加换行\n,导致字符串结尾是 \n\0"
   */
  while (fgets(buf, sizeof(buf), fp) != NULL) {

    char* find = strchr(buf, '\n');  //找出data中的"\n"
    if (find)
      *find = '\0';   //替换
    /* 参考nemu读取命令的代码 */
    char* cmd = strtok(buf, " ");
    char* args = cmd + strlen(cmd) + 1;

    int temp;
    sscanf(cmd, "%d", &temp);
    testinput = temp;
    testoutput = expr(args, &ret);
    Assert(testinput == testoutput, "input:%lu,output:%lu", testinput, testoutput);
  }
  fclose(fp);
}

