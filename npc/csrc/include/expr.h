#ifndef __EXPR_H__
#define __EXPR_H__

#include <iostream>
#include <regex.h>
#include <vector>

using namespace std;

namespace expr_namespace {
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
    struct rule {
        const char* regex;
        int token_type;
    };

    typedef struct token {
        int type;
        char str[32];
    } Token;
    class Expr {
    private:
        typedef uint64_t word_t;
        /* 正则表达式规则 */
        vector<struct rule> rules = {
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
            {"&&",TK_AND},                  // and
        };
        /* 经过处理后的规则 */
        regex_t re[32];
        Token tokens[32];

        int nr_token = 0;


    private:
        void init_regex();
        bool make_token(char* e);
    public:
        Expr(/* args */);
        ~Expr();
        word_t getResult(char* e, bool* success);
    };
} // namespace expr_namespace


#endif