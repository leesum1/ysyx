#ifndef __EXPRINTERNAL_H
#define __EXPRINTERNAL_H

#include "expr.h"
#include <vector>
#include <stack>
#include <iostream>
namespace expr_namespace {

    class Exprinternal {
    private:
        vector<Token> tokens;
        stack<uint64_t> stackOpre, stackNum;
    public:
        Exprinternal(void* tokens_addr, int num);
        Exprinternal(vector<Token> val);
        ~Exprinternal();
        void printTokens();
        bool isOperator(Token val);
        bool isCompare(Token val);
        bool isPriority(Token val);
        uint64_t calculate();
        void negNum();
        void ref();
        void reg();
        void hex();
        void ParseAll();
        uint64_t run1();
        uint64_t getResult();
        bool getCompareResult(uint64_t leftVal, uint64_t rightVal, Token cmp);
    };
} // namespace name




#endif