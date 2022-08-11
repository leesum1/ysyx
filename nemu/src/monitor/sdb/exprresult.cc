#include <stack>
#include <iostream>
#include <vector>

extern "C" {
#include <common.h>
#include <isa.h>
#include <memory/vaddr.h>
#include <debug.h>
}
using namespace std;

class Exprresult {
private:
    typedef struct token {
        int type;
        char str[32];
    } Token;

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
    vector<Token> tokens;
    stack<uint64_t> stackOpre, stackNum;
public:
    Exprresult(void* tokens_addr, int num);
    Exprresult(vector<Token> val);
    ~Exprresult();
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
    bool getCompare(uint64_t leftVal, uint64_t rightVal, Token cmp);
};




Exprresult::Exprresult(void* tokens_addr, int num) {
    Token* p = (Token*)tokens_addr;
    for (int i = 0; i < num; i++) {
        tokens.push_back(p[i]);
    }
    ParseAll();
}


Exprresult::Exprresult(vector<Token> val) {
    /* 赋值 */
    tokens.assign(val.begin(), val.end());
    ParseAll();
    printTokens();
}


uint64_t Exprresult::getResult() {
    auto iter = tokens.begin();

    vector<Token> vector_l, vector_r;
    for (; iter != tokens.end(); iter++) {
        if (isCompare(iter.operator*())) {
            /* 以比较运算符为界，分为两个表达式 */
            vector<Token> vector_l(tokens.begin(), iter);
            vector<Token> vector_r(iter + 1, tokens.end());
            Exprresult expl(vector_l);
            Exprresult expr(vector_r);
            uint64_t leftval = expl.run1();
            uint64_t rightval = expr.run1();
            bool ret = getCompare(leftval, rightval, iter.operator*());
            return ret;
        }
    }
    return run1();
}
/* 处理完毕后,所有数据都是 64位 无符号数 */
void Exprresult::ParseAll() {
    printTokens();
    negNum();               //负数处理
    reg();                  //寄存器处理  
    hex();                  //十六进制处理
    ref();                  //指针处理
    printTokens();
}

Exprresult::~Exprresult() {
    //cout << "Exprresult end" << endl;
}

void Exprresult::printTokens() {

    // cout << "Exprresult start" << endl;
    // for (size_t i = 0; i < tokens.size(); i++) {
    //     cout << " str: " << tokens.at(i).str \
    //         << " type: " << tokens.at(i).type << endl;
    // }



}

uint64_t Exprresult::run1() {
    bool ret;
    for (size_t i = 0; i < tokens.size(); i++) {
        /* 跳过无用数据 */
        if (tokens.at(i).type == TK_NOTYPE) {
            continue;
        }
        ret = isOperator(tokens.at(i));
        /* 数字直接入栈 */
        if (!ret) {
            /* 这里的字符串转换函数要匹配 */
            uint64_t data64;
            sscanf(tokens.at(i).str, "%lu", &data64);
            stackNum.push(data64);
            continue;
        }
        /* 优先级低，出栈计算 */
        while (!isPriority(tokens.at(i))) {
            stackNum.push(calculate());
        }
        /* 右括号单独处理 */
        if (tokens.at(i).type == ')') {
            while (stackOpre.top() != '(') {
                stackNum.push(calculate());
            }
            stackOpre.pop();
        }
        /* 不是右括号操作符入栈 */
        else {
            stackOpre.push(tokens.at(i).type);
        }
    }
    /* 剩余数据处理 */
    while (!stackOpre.empty()) {
        stackNum.push(calculate());
    }

    Assert(stackNum.size() == 1 || stackOpre.size() == 0, "stackNum.size:%ld,stackOpre.size%ld", stackNum.size(), stackOpre.size());
    // cout << "stackNumsize:" << stackNum.size() << endl;
    // cout << "stackOpsize:" << stackOpre.size() << endl;
    // cout << "calculate:" << stackNum.top() << endl;

    return stackNum.top();
}

bool Exprresult::isOperator(Token val) {
    if (val.type == '+'
        || val.type == '-'
        || val.type == '*'
        || val.type == '/'
        || val.type == '('
        || val.type == ')') {
        return true;
    }
    return false;

}

/* 比较运算符 */
bool Exprresult::isCompare(Token val) {
    if (val.type == TK_AND
        || val.type == TK_EQ
        || val.type == TK_NEQ) {
        return true;
    }
    return false;
}

bool Exprresult::getCompare(uint64_t leftVal, uint64_t rightVal, Token cmp) {
    bool ret = false;
    switch (cmp.type) {
    case TK_EQ:
        ret = (leftVal == rightVal) ? true : false;
        break;
    case TK_NEQ:
        ret = (leftVal != rightVal) ? true : false;
        break;
    default:
        break;
    }
    return ret;
}

/**
 * @brief () * / + -
 * 优先级高：可直接入栈 优先级低：进行一次calculate
 * @param val
 * @return true : 新加入的操作码优先级高
 * @return false：新加入的操作码优先级低
 */
bool Exprresult::isPriority(Token val) {


    /* 特殊情况处理：操作数少于两个,或者为括号 */
    if ((stackNum.size() < 2)) return true;
    uint32_t toptype;
    toptype = stackOpre.top();
    if (toptype == '(') return true;


    bool ret = false;
    switch (val.type) {
    case '*':
    case '/':
        if (!stackOpre.empty()) {
            if ('+' == toptype || '-' == toptype) {
                ret = true;
            }
        }
        break;
    case '+':
    case '-':
        ret = false;
        break;
    case '(':
    case ')':
        ret = true;
        break;
    default:
        cout << "type undefine!!!!!" << endl;
        break;
    }
    return ret;
}

uint64_t Exprresult::calculate() {
    /* 运算符出栈 */
    uint64_t op = stackOpre.top();
    stackOpre.pop();
    uint64_t numright = stackNum.top();
    stackNum.pop();
    uint64_t numleft = stackNum.top();
    stackNum.pop();

    uint64_t result = 0;;
    switch (op) {
    case '+':
        result = numleft + numright;
        break;
    case '-':
        result = numleft - numright;
        break;
    case '*':
        result = numleft * numright;
        break;
    case '/':
        result = numleft / numright;
        break;
    default:
        cout << "result undefine!!!!!" << endl;
        break;
    }

    return result;
}

/* 处理负号 */
void Exprresult::negNum() {
    uint64_t data, negdata;;
    //https://blog.csdn.net/hechao3225/article/details/55101344
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens.at(i).type == '-') {
            /* 位于头部 是负号 */
            if (i == 0) {
                tokens[i].type = TK_NOTYPE; //标记为无用数据
                /* 重新写入负数 */
                sscanf(tokens[i + 1].str, "%lu", &data);
                negdata = 0 - data;
                sprintf(tokens[i + 1].str, "%lu", negdata);
            }
            /* 前一个是操作符 是符号 */
            else if (isOperator(tokens.at(i - 1))
                && (tokens.at(i - 1).type != ')')) {
                tokens[i].type = TK_NOTYPE;
                sscanf(tokens[i + 1].str, "%lu", &data);
                negdata = 0 - data;
                sprintf(tokens[i + 1].str, "%lu", negdata);
            }
        }
    }
}
/* 处理指针 */
void Exprresult::ref() {

    //https://blog.csdn.net/hechao3225/article/details/55101344
    for (size_t i = 0; i < tokens.size(); i++) {
        /* 区分是乘法还是指针 */
        if (tokens.at(i).type == '*') {
            /* 位于头部是指针 */
            if (i == 0) {
                tokens.at(i).type = TK_DEREF;
            }
            /* 前面是预算符，且不是 ')' 为指针 */
            else if (isOperator(tokens.at(i - 1))
                && (tokens.at(i - 1).type != ')')) {
                tokens.at(i).type = TK_DEREF;
            }
        }
    }

    for (size_t i = 0; i < tokens.size(); i++) {
        uint64_t addr, data;
        if (tokens.at(i).type == TK_DEREF) {
            tokens[i].type = TK_NOTYPE; //标记为无用数据
            if (tokens.at(i + 1).type == TK_NUM) {
                /* 得到地址 */
                sscanf(tokens.at(i + 1).str, "%lu", &addr);
                data = vaddr_read(addr, 8);//读取地址数据
                sprintf(tokens[i + 1].str, "%lu", data);//重新写入数据
            }
        }
    }
}

/* 处理寄存器 */
void Exprresult::reg() {
    //https://blog.csdn.net/hechao3225/article/details/55101344
    for (size_t i = 0; i < tokens.size(); i++) {
        /* 读取寄存器 */
        if (tokens.at(i).type == TK_REG) {
            char* regname = tokens.at(i).str;
            bool ret;
            uint64_t val = isa_reg_str2val(&regname[1], &ret);
            tokens[i].type = TK_NUM;
            sprintf(tokens[i].str, "%lu", val);
        }
    }
}

/* 处理十六进制 */
void Exprresult::hex() {
    uint64_t ret;
    for (size_t i = 0; i < tokens.size(); i++) {
        /* 读取寄存器 */
        if (tokens.at(i).type == TK_HEX) {
            sscanf(tokens.at(i).str, "%lx", &ret);
            sprintf(tokens[i].str, "%lu", ret);
            tokens[i].type = TK_NUM;
        }
    }
}



/* 供外部调用 */
extern "C" uint64_t exprcpp(void* tokens_addr, int num) {

    Exprresult test(tokens_addr, num);

    return test.getResult();
    //return 0;
}


