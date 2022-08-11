#ifndef __ITRACE_H__
#define __ITRACE_H__

#include <iostream>
//#include "ringbuff.h"
using namespace std;


class Itrace {
private:
    /* data */
    // buffers::ring_buffer<int, 50> instbuff;
public:
    Itrace(/* args */);
    void llvmDis();
    ~Itrace();
};



#endif