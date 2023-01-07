#ifndef __PERFCOUNTER_H__
#define __PERFCOUNTER_H__

#include <iostream>
#include <string>
#include "simconf.h"
#include "tabulate.hpp"
using namespace std;


class PerfCounter {

public:
    enum  PIPELINE_TYPE {
        PC_GEN,
        IF,
        ID,
        EXE,
        MEM_COMMIT,
        NUM_END
    };
private:
    struct count_item {
        string name;
        uint64_t total_num;
        uint64_t hit_num;
    };

    struct pipeline_item {
        string name;
        uint64_t stall_num;
        uint64_t flush_num;
        uint64_t normal_num;
        uint64_t req_num;
    };

    std::array<string, (uint32_t)(PIPELINE_TYPE::NUM_END)> pipeline_enum_str =
    { "PC_GEN", "IF", "ID", "EXE","MEM&COMMIT" };


    // load_use_valid,
    // alu_mul_div_valid,
    // jump_hazard_valid,
    // trap_stall_valid_wb,
    // ram_stall_valid_mem,
    // ram_stall_valid_if

    
    std::array<string, 6> pipeline_req_str =
    { "ram_req_if",
      "ram_req_mem",
      "trap_req_wb",
      "jump_req_exe",
      "mul_div_req_exe",
      "load_use_req_id" };


public:
    std::array<pipeline_item, (uint32_t)(PIPELINE_TYPE::NUM_END)> pipeline_list;
std::array<uint64_t, 6> pipeline_req_count;
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

        for (size_t i = 0; i < pipeline_list.size(); i++) {
            pipeline_list[i].name = pipeline_enum_str[i];
        }

    }

    void display_counter() {

        tabulate::Table universal_constants;

        universal_constants.format()
            .color(tabulate::Color::cyan)
            .font_style({ tabulate::FontStyle::bold })
            .font_align(tabulate::FontAlign::left);

        universal_constants.add_row({ counter_name,"total num","hit num","unhit num","hit rate" });

        for (auto iter : count_list) {
            universal_constants.add_row({ iter->name,std::to_string(iter->total_num),std::to_string(iter->hit_num),std::to_string(iter->total_num - iter->hit_num),std::to_string((float)((float)iter->hit_num / (float)iter->total_num)) });
        }
        cout << universal_constants << endl;

    }


    void display_pipline() {
        tabulate::Table pipeline_display_table;
        pipeline_display_table.format()
            .color(tabulate::Color::cyan)
            .font_style({ tabulate::FontStyle::bold })
            .font_align(tabulate::FontAlign::left);

        pipeline_display_table.add_row({ "PIPELINE STAGE",
                                         "STALL CLKS",
                                         "FLUSH CLKS",
                                         "NORMAL CLKS" ,
                                         "TOTAL CLKS" });
        for (auto iter : pipeline_list) {
            pipeline_display_table.add_row({ iter.name,std::to_string(iter.stall_num),
                                             std::to_string(iter.flush_num),
                                             std::to_string(iter.normal_num),
                                             std::to_string(iter.normal_num + iter.flush_num + iter.stall_num) });
        }
        cout << pipeline_display_table << endl;
    }

    void display_pipline_req() {
        tabulate::Table pipeline_req_display_table;
        pipeline_req_display_table.format()
            .color(tabulate::Color::cyan)
            .font_style({ tabulate::FontStyle::bold })
            .font_align(tabulate::FontAlign::left);

        pipeline_req_display_table.add_row({ "REQ TYPE",
                                             " NUM" });

        for (size_t i = 0; i < pipeline_req_count.size(); i++) {
            pipeline_req_display_table.add_row({ pipeline_req_str.at(i),std::to_string(pipeline_req_count.at(i)) });
        }

        cout << pipeline_req_display_table << endl;
    }


    void display() {
        display_counter();
        display_pipline();
        display_pipline_req();
    }

    ~PerfCounter() {

    }

};



#endif