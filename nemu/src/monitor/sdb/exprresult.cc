#include <stack>
#include <iostream>
#include <vector>

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

    stack<uint32_t> stackOpre, stackNum;

public:
    Exprresult(void* tokens_addr, int num);
    ~Exprresult();
    void printTokens();
    bool isOperator(Token val);
    bool isPriority(Token val);
};




Exprresult::Exprresult(void* tokens_addr, int num) {
    Token* p = (Token*)tokens_addr;
    for (int i = 0; i < num; i++) {
        tokens.push_back(p[i]);
    }
    printTokens();
    cout << "isPriority:" << isPriority(tokens.at(0)) << endl;
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

bool Exprresult::isOperator(Token val) {

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
    case '(':
        ret = true;
        break;
        // case ')':
        //     break;
    case '*':
    case '/':
        toptype = stackOpre.top();
        // if ('+' == toptype || '-' == toptype) {
        //     ret = true;
        // }
        break;
    case '+':
    case '-':
        ret = false;
        break;
    default:
        cout << "type undefine!!!!!" << endl;
        break;
    }
    return ret;
}


/* 供外部调用 */
extern "C" void exprcpp(void* tokens_addr, int num) {

    Exprresult test(tokens_addr, num);
}


