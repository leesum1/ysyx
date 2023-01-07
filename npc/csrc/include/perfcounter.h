#ifndef __PERFCOUNTER_H__
#define __PERFCOUNTER_H__

#include <iostream>
#include <string>
#include "simconf.h"
#include "tabulate.hpp"
using namespace std;


class PerfCounter {
private:
    struct count_item {
        string name;
        uint64_t total_num;
        uint64_t hit_num;
    };

public:
    count_item icache{
        .name = "icache"
    };
    count_item dcache{
        .name = "dcache"
    };
    count_item bpu_all{
        .name = "bpu_all"
    };
    count_item bpu_branch{
        .name = "bpu_branch"
    };
    count_item bpu_call{
        .name = "bpu_call"
    };
    count_item bpu_ret{
        .name = "bpu_ret"
    };
    count_item bpu_other_jal{
        .name = "bpu_other_jal"
    };
    count_item bpu_other_jalr{
        .name = "bpu_other_jalr"
    };
private:

    string counter_name;
    vector<count_item*> count_list{
        &icache,
        &dcache,
        &bpu_all,
        &bpu_branch,
        &bpu_call,
        &bpu_ret,
        &bpu_other_jal,
        &bpu_other_jalr
    };




public:

    PerfCounter(const char* name) {
        counter_name = name;
    }

    void display() {

        tabulate::Table universal_constants;

        universal_constants.format()
            .color(tabulate::Color::blue)
            .font_style({tabulate::FontStyle::bold})
            .font_align(tabulate::FontAlign::left);

        universal_constants.add_row({ counter_name,"total num","hit num","unhit num","hit rate" });

        for (auto iter : count_list) {
            universal_constants.add_row({ iter->name,std::to_string(iter->total_num),std::to_string(iter->hit_num),std::to_string(iter->total_num - iter->hit_num),std::to_string((float)((float)iter->hit_num / (float)iter->total_num)) });
        }


        cout << universal_constants << endl;

    }

    ~PerfCounter() {

    }

};



#endif