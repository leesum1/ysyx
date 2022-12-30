#ifndef __PERFCOUNTER_H__
#define __PERFCOUNTER_H__

#include <iostream>
#include <string>
#include "simconf.h"
using namespace std;


class PerfCounter {
private:
    string counter_name;
    uint64_t counter = 0;
    uint64_t hit = 0;
public:

    PerfCounter(const char * name) {
        counter_name = name;
    }

    void incr_counter() {
        counter++;
    }

    void decr_counter() {
        counter--;
    }

    void incr_hit() {
        hit++;
    }

    void incr_hit_counter() {
        hit++;
        counter++;
    }

    void decr_hit() {
        hit--;
    }

    void display() {

        cout << COLOR_GREEN << "---------------"<<counter_name<<"-------------------" << endl;
        cout << counter_name << " counter num:" << counter << endl;
        cout << counter_name << " hit num:" << hit << endl;
        cout << counter_name << " unhit num:" << counter - hit << endl;
        cout << counter_name << " hit rate : " << (float)((float)hit / (float)counter) << COLOR_END << endl;
        printf("\n");
    }

    ~PerfCounter() {

    }

};



#endif