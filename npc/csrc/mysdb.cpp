#include "mysdb.h"
#include "stdio.h"
#include "expr.h"
extern Simtop* mysim_p;


unsigned cmd_help(const std::vector<std::string>&) {
    std::cout << "Welcome to the example console. This command does not really\n"
        << "do anything aside from printing this statement. Thus it does\n"
        << "not need to look into the arguments that are passed to it.\n";
    return 0;
}

/**
 * @brief 扫描内存:用法 x 10 0x80000000
 *
 * @param input
 * @return unsigned
 */
unsigned cmd_x(const std::vector<std::string>& input) {

    if (input.size() != 3) {
        // The first element of the input array is always the name of the
        // command as registered in the console.
        std::cout << "Usage: " << input[0] << " x len addr\n";
        // We can return an arbitrary error code, which we can catch later
        // as Console will return it.
        return 1;
    }
    uint32_t len;
    paddr_t addr;
    sscanf(input[1].c_str(), "%d", &len);
    sscanf(input[2].c_str(), "%lx", &addr);
    mysim_p->scanMem(addr, len);
    return 0;
}

/**
 * @brief 单步执行
 *
 * @param input
 * @return unsigned
 */
unsigned cmd_si(const std::vector<std::string>& input) {
    uint32_t n;
    if (input.size() == 2) {
        sscanf(input[1].c_str(), "%d", &n);
        mysim_p->excute(n);
    }
    else {
        mysim_p->excute(1);
    }
    return 0;
}
/**
 * @brief 连续执行
 *
 */
unsigned cmd_c(const std::vector<std::string>& input) {
    if (input.size() != 1) {
        // The first element of the input array is always the name of the
        // command as registered in the console.
        std::cout << "Usage: " << input[0] << " c \n";
        // We can return an arbitrary error code, which we can catch later
        // as Console will return it.
        return 1;
    }
    mysim_p->excute();
    return 0;
}
/**
 * @brief 显示寄存器 r 或者监视点 w
 *
 * @param input
 * @return unsigned
 */
unsigned cmd_info(const std::vector<std::string>& input) {
    if (input.size() != 2) {
        // The first element of the input array is always the name of the
        // command as registered in the console.
        std::cout << "Usage: " << input[0] << " info  w or r\n";
        // We can return an arbitrary error code, which we can catch later
        // as Console will return it.
        return 1;
    }

    char val[20];
    sscanf(input[1].c_str(), "%s", val);
    if (0 == strcmp(val, "r")) {
        mysim_p->printRegisterFile();
    }
    else if (0 == strcmp(val, "w")) {

    }
    return 0;
}

unsigned cmd_p(const std::vector<std::string>& input) {

    string inputall;
    for (size_t i = 1; i < input.size(); i++) {
        inputall.append(input[i]);
    }

    cout << "cmd_p\t" << inputall << endl;

    bool ret;
    static  expr_namespace::Expr* u_expr = new expr_namespace::Expr;
    /* const char * 转 char * */

    char* c = const_cast<char*>(inputall.c_str());
    uint64_t exprret = u_expr->getResult(c, &ret);
    return 0;
}