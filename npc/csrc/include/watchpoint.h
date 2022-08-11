#ifndef ___WATCHPOINT_H__
#define ___WATCHPOINT_H__

#include <stack>
#include <iostream>
#include <vector>
#include <list>
#include <string>


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



#endif