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

#include <stack>
#include <iostream>
#include <vector>
#include <list>
#include <string>

extern "C" {
#include "sdb.h"
#include "utils.h"
}

using namespace std;

class Watchpoint {
private:
#define WPNUM 32
  struct wpdata {
    uint32_t NO;  //序号
    string exp;   //表达式
  };
  list<wpdata> wp_pool;
  bool numflag[WPNUM]; //标记数组，自动分配序号
public:
  Watchpoint(/* args */);
  ~Watchpoint();
  bool newWp(string exp);
  bool delWp(uint32_t NO);
  uint32_t getNum();
  bool delNum(uint32_t NO);
  void praseAllwp();
  void showAllwp();
  void printwp();
};
/**
 * @brief 标记数组清空
 *
 */
Watchpoint::Watchpoint(/* args */) {

  for (uint32_t i = 0; i < WPNUM; i++) {
    numflag[i] = false;
  }
  cout << "Watchpoint init" << endl;
}

Watchpoint::~Watchpoint() {
  cout << "Watchpoint deinit" << endl;
}


/**
 * @brief 创建新的监视点
 *
 * @param exp 监视点表达式
 * @return true
 * @return false
 */
bool Watchpoint::newWp(string exp) {
  wpdata newdata;
  newdata.NO = getNum();
  if (newdata.NO == WPNUM) {
    return false;
  }
  newdata.exp = exp;
  wp_pool.emplace_back(newdata);
  printwp();
  return true;
}
/**
 * @brief 删除监视点
 *
 * @param NO 监视点序号
 * @return true
 * @return false
 */
bool Watchpoint::delWp(uint32_t NO) {
  for (auto it = wp_pool.begin(); it != wp_pool.end();) {
    if (it.operator->()->NO == NO) {
      delNum(it.operator->()->NO);//删除序号
      wp_pool.erase(it++);        // 删除节点，并到下一个节点
      printwp();
      return true;
    }
    else {
      it++;
    }
  }
  return false;
}

/**
 * @brief 获取一个未使用的序号
 *
 * @return uint32_t
 */
uint32_t Watchpoint::getNum() {
  for (uint32_t i = 0; i < WPNUM; i++) {
    if (numflag[i] == false) {
      numflag[i] = true;
      return i;
    }
  }
  return WPNUM;
}
/**
 * @brief 删除一个序号
 *
 * @param NO
 * @return true
 * @return false
 */
bool Watchpoint::delNum(uint32_t NO) {

  if (numflag[NO] == true) {
    numflag[NO] = false;
    return true;
  }
  return false;
}

/**
 * @brief 打印所有的监视点表达式
 *
 */
void Watchpoint::printwp() {

  for (auto it = wp_pool.begin(); it != wp_pool.end();it++) {
    cout << "NUM: " << it.operator*().NO << "\twpexp: " << it.operator*().exp << endl;
  }
}

/**
 * @brief 解析所有的监视点
 *
 */
void Watchpoint::praseAllwp() {

  bool ret;
  uint64_t exprResult;
  for (auto it = wp_pool.begin(); it != wp_pool.end();it++) {
    exprResult = expr((char*)it.operator*().exp.c_str(), &ret);
    if (true == exprResult) {
      nemu_state.state = NEMU_STOP;
      cout << "NUM:" << it.operator*().NO <<
        "\twpexp: " << it.operator*().exp <<
        "\texprResult" << exprResult << endl;
    }
  }
}
/**
 * @brief 打印所有的监视点表达式,并解析结果
 *
 */
void Watchpoint::showAllwp() {
  bool ret;
  uint64_t exprResult;
  for (auto it = wp_pool.begin(); it != wp_pool.end();it++) {
    exprResult = expr((char*)it.operator*().exp.c_str(), &ret);
    cout << "NUM:" << it.operator*().NO <<
      "\twpexp:" << it.operator*().exp <<
      "\texprResult" << exprResult << endl;
  }
}



/* 供c函数调用 */
static Watchpoint wp;
extern "C" {

  void new_wp(char* str) {
    string temp(str);
    wp.newWp(temp);
  }

  void free_wp(uint32_t NO) {
    wp.delWp(NO);
  }

  void show_wp() {
    wp.showAllwp();
  }

  void prase_wp() {
    wp.praseAllwp();
  }
}




