#include "trap.h"
#include <stdio.h>

long long mul(long long a, long long b) {

    return a * b;
}

const long long src[4] = {
-1,
0xffffffff,
2000,
-3000000
};



int main() {
    long long a, b;
    a = src[0]; b = src[1];
    long long c; //= mul(a, b);
    c = a * b;
    //printf("%lld\n", c);
    check(c == -4294967295);
    return 0;
}