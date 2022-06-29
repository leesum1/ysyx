#include <stack>
#include <iostream>
#include <vector>

using namespace std;

class exprresult {
private:
    typedef struct token {
        int type;
        char str[32];
    } Token;
    vector<Token> tokens;

public:
    exprresult(void* tokens_addr, int num);
    ~exprresult();
    void printTokens();
};


exprresult::exprresult(void* tokens_addr, int num) {
    Token* p = (Token*)tokens_addr;
    for (int i = 0; i < num; i++) {
        tokens.push_back(p[i]);
    }
    printTokens();
}

exprresult::~exprresult() {
}

void exprresult::printTokens() {

    for (int i = 0; i < tokens.size(); i++) {
        cout << "str:" << tokens.at(i).str \
            << "type:" << tokens.at(i).str << endl;
    }

}


extern "C" void exprcpp(void* tokens_addr, int num) {

    exprresult test(tokens_addr, num);
}


