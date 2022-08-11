#include <stdio.h>
#include "include/fixedptc.h"


int main() {

    fixedpt b = fixedpt_rconst(2);

    fixedpt ceil = fixedpt_ceil(b);
    fixedpt floor = fixedpt_floor(b);
    printf("fixedpt_fracpart:%d\n", fixedpt_fracpart(b));
    printf("floor:%d,val:%f,ceil:%d\n", fixedpt_toint(floor), fixedpt_tofloat(b), fixedpt_toint(ceil));
    return 0;
}