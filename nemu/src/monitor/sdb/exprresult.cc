#include <stack>
#include <iostream>
#include <vector>
#include <common.h>

using namespace std;

class Exprresult {
private:
    typedef struct token {
        int type;
        char str[32];
    } Token;
    vector<Token> tokens;
    enum {
        TK_NOTYPE = 256, TK_EQ,
        TK_NUM,
        /* TODO: Add more token types */

    };

    stack<int32_t> stackOpre, stackNum;

public:
    Exprresult(void* tokens_addr, int num);
    ~Exprresult();
    void printTokens();
    bool isOperator(Token val);
    bool isPriority(Token val);
    int32_t calculate();
    void run1();
};




Exprresult::Exprresult(void* tokens_addr, int num) {
    Token* p = (Token*)tokens_addr;
    for (int i = 0; i < num; i++) {
        tokens.push_back(p[i]);
    }
    printTokens();
    //cout << "isPriority:" << isPriority(tokens.at(0)) << endl;
}

Exprresult::~Exprresult() {
    cout << "Exprresult end" << endl;
}

void Exprresult::printTokens() {

    cout << "Exprresult start" << endl;
    for (int i = 0; i < tokens.size(); i++) {
        cout << " str: " << tokens.at(i).str \
            << " type: " << tokens.at(i).type << endl;
    }



}

void Exprresult::run1() {
    bool ret;
    for (int i = 0; i < tokens.size(); i++) {
        ret = isOperator(tokens.at(i));
        if (!ret) {
            DEBUG_L("size:%d\n", tokens.size());
            stackNum.push(atoi(tokens.at(i).str));
            continue;
        }
        // else {
        ret = isPriority(tokens.at(i));
        if (!ret) {
            DEBUG_L("\n");
            stackNum.push(calculate());
        }
        stackOpre.push(tokens.at(i).type);
        // }
    }
    while (!stackOpre.empty()) {
        stackNum.push(calculate());
    }
    cout << "stackNumsize:" << stackNum.size() << endl;
    cout << "calculate:" << stackNum.top() << endl;
    cout << "stackop:" << stackOpre.size() << endl;


}

bool Exprresult::isOperator(Token val) {
    DEBUG_L();
    if (val.type != this->TK_NUM) {
        return true;
    }

    return false;

}

/**
 * @brief () * / + -
 *
 * @param val
 * @return true
 * @return false
 */
bool Exprresult::isPriority(Token val) {

    if (val.type == this->TK_NUM) {
        cout << "please input opra!!!!" << endl;
        return false;
    }
    bool ret = false;
    uint32_t toptype;
    switch (val.type) {
    case '*':
    case '/':
        if (!stackOpre.empty()) {
            toptype = stackOpre.top();
            if ('+' == toptype || '-' == toptype) {
                ret = true;
            }
        }
        break;
    case '+':
    case '-':
    case '(':
        ret = false;
        break;
    default:
        cout << "type undefine!!!!!" << endl;
        break;
    }

    if (stackNum.size() < 2)
        ret = true;
    return ret;
}

int32_t Exprresult::calculate() {
    /* 运算符出栈 */
    uint32_t op = stackOpre.top();
    stackOpre.pop();
    uint32_t numright = stackNum.top();
    stackNum.pop();
    uint32_t numleft = stackNum.top();
    stackNum.pop();

    int32_t result;
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


/* 供外部调用 */
extern "C" void exprcpp(void* tokens_addr, int num) {

    Exprresult test(tokens_addr, num);
    test.run1();
}


