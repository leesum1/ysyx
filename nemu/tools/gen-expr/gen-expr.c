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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
// this should be enough
static char buf[65536] = {};
static char* bufindex = buf;
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char* code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned  int result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

#define DEBUG_S(format, argent...) //printf("" format "", ##argent)

static void gen_num() {
  char str[32];
  /* 随机插入空格 */
  sprintf(str, "%*d", rand() % 4, (rand() % 20 - 10));
  DEBUG_S("size:%ld,num:%s\n", strlen(str), str);
  strcpy(bufindex, str);
  bufindex += strlen(str);
  DEBUG_S("bufindex,%p\n", bufindex);
  DEBUG_S("buff:%s\n", buf);
}


static void gen(char symbol) {
  char str[32];
  sprintf(str, "%*c", rand() % 4, symbol);
  DEBUG_S("size:%ld,num:%s\n", strlen(str), str);
  strcpy(bufindex, str);
  bufindex += strlen(str);
  DEBUG_S("bufindex,%p\n", bufindex);
  DEBUG_S("buff:%s\n", buf);
}

// +-*/
static void gen_rand_op() {
  char op;
  /* 不要除法 */
  switch (rand() % 4) {
  case 0:
    op = '+';
    break;
  case 1:
    op = '-';
    break;
  case 2:
    op = '*';
    break;
  case 3:
    op = '/';
    break;
  default:
    break;
  }
  char str[32];
  sprintf(str, "%*c", rand() % 4, op);
  DEBUG_S("size:%ld,num:%s\n", strlen(str), str);
  strcpy(bufindex, str);
  bufindex += strlen(str);
  DEBUG_S("bufindex,%p\n", bufindex);
  DEBUG_S("buff:%s\n", buf);
}


static void gen_rand_expr() {
  int choose = rand() % 3;
  /* 表达式长度超过20后，强制选择 0 路线，不进行递归调用 */
  if (strlen(buf) > 20) {
    choose = 0;
  }
  switch (choose) {
  case 0: gen_num();gen_rand_op();gen_num(); break;
  case 1: gen('('); gen_rand_expr(); gen(')'); break;
  default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
}


int main(int argc, char* argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i++) {
    //memset(buf, 0, sizeof(buf));
    buf[0] = '\0';
    bufindex = buf;
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE* fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);
    /* 添加 Werror 将除0警告转换成错误,导致编译失败*/
    int ret = system("gcc -Werror /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) {
      //printf("错误：-Wdiv-by-zero\r\n");
      continue;
    }

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);
    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);
    printf("%d %s\n", result, buf);
  }
  return 0;
}
