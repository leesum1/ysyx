#ifndef __ITRACE_H__
#define __ITRACE_H__

#include <iostream>
#include <string>
#include <stdint.h>
// #include "ringbuff.hpp"
#include "ringbuff.hpp"
using namespace std;


class Itrace {
private:
    /* data */
    // buffers::ring_buffer<int, 50> instbuff;
public:
    jm::circular_buffer <string, 50> inst_trace;
    Itrace(/* args */);
    void llvmDis();
    ~Itrace();
    void printRecentInst();
};



#endif