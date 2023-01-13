#include "riscv64_decoder.h"
#include "tabulate.hpp"
#include "simtop.h"
#include <assert.h>


static const char* inst_type_names[] = {
"OPCODE_ERR", "LOAD", "STORE", "MADD", "BRANCH", "LOAD_FP", "STORE_FP", "MSUB",
"JALR", "custom_0", "custom_1", "NMSUB", "MISC_MEM", "AMO", "NMADD", "JAL",
"OP_IMM", "OP", "OP_FP", "SYSTEM", "AUIPC", "LUI", "OP_IMM_32", "OP_32",
"custom_2_rv128", "custom_3_rv128" };



extern Simtop* mysim_p;

Riscv64_decoder::Riscv64_decoder(/* args */) {
}

Riscv64_decoder::~Riscv64_decoder() {
}

uint8_t Riscv64_decoder::get_opcode(uint32_t inst_data) {

    uint8_t opcode = inst_data & 0x7f;

    return opcode;
}

void Riscv64_decoder::perf_inst_count(uint32_t inst_data) {


    uint8_t opcode = get_opcode(inst_data);

    switch (opcode) {
    case OPCODE_MASK::MASK_LOAD:
        inst_count[OPCODE_TYPE::LOAD]++;
        break;
    case OPCODE_MASK::MASK_STORE:
        inst_count[OPCODE_TYPE::STORE]++;
        break;
    case OPCODE_MASK::MASK_MADD:
        inst_count[OPCODE_TYPE::MADD]++;
        break;
    case OPCODE_MASK::MASK_BRANCH:
        inst_count[OPCODE_TYPE::BRANCH]++;
        break;
    case OPCODE_MASK::MASK_LOAD_FP:
        inst_count[OPCODE_TYPE::LOAD_FP]++;
        break;
    case OPCODE_MASK::MASK_STORE_FP:
        inst_count[OPCODE_TYPE::STORE_FP]++;
        break;
    case OPCODE_MASK::MASK_MSUB:
        inst_count[OPCODE_TYPE::MSUB]++;
        break;
    case OPCODE_MASK::MASK_JALR:
        inst_count[OPCODE_TYPE::JALR]++;
        break;
    case OPCODE_MASK::MASK_custom_0:
        inst_count[OPCODE_TYPE::custom_0]++;
        break;
    case OPCODE_MASK::MASK_custom_1:
        inst_count[OPCODE_TYPE::custom_1]++;
        break;
    case OPCODE_MASK::MASK_NMSUB:
        inst_count[OPCODE_TYPE::NMSUB]++;
        break;
    case OPCODE_MASK::MASK_MISC_MEM:
        inst_count[OPCODE_TYPE::MISC_MEM]++;
        break;
    case OPCODE_MASK::MASK_AMO:
        inst_count[OPCODE_TYPE::AMO]++;
        break;
    case OPCODE_MASK::MASK_NMADD:
        inst_count[OPCODE_TYPE::NMADD]++;
        break;

    case OPCODE_MASK::MASK_JAL:
        inst_count[OPCODE_TYPE::JAL]++;
        break;
    case OPCODE_MASK::MASK_OP_IMM:
        inst_count[OPCODE_TYPE::OP_IMM]++;
        break;
    case OPCODE_MASK::MASK_OP:
        inst_count[OPCODE_TYPE::OP]++;
        break;
    case OPCODE_MASK::MASK_OP_FP:
        inst_count[OPCODE_TYPE::OP_FP]++;
        break;
    case OPCODE_MASK::MASK_SYSTEM:
        inst_count[OPCODE_TYPE::SYSTEM]++;
        break;
    case OPCODE_MASK::MASK_AUIPC:
        inst_count[OPCODE_TYPE::AUIPC]++;
        break;
    case OPCODE_MASK::MASK_LUI:
        inst_count[OPCODE_TYPE::LUI]++;
        break;
    case OPCODE_MASK::MASK_OP_IMM_32:
        inst_count[OPCODE_TYPE::OP_IMM_32]++;
        break;
    case OPCODE_MASK::MASK_OP_32:
        inst_count[OPCODE_TYPE::OP_32]++;
        break;
    default:
        printf("unkown opcode %x\n", opcode);
        mysim_p->top_status = mysim_p->TOP_STOP;
        break;
    }
}

void Riscv64_decoder::display() {

    printf("\n");
    uint64_t inst_all = 0;
    for (size_t i = 0; i < 26; i++) {
        inst_all += inst_count[i];
    }

    tabulate::Table universal_constants;

    universal_constants.format()
        .color(tabulate::Color::cyan)
        .font_style({ tabulate::FontStyle::bold })
        .font_align(tabulate::FontAlign::left);

    universal_constants.add_row({ "INST TYPE","NUMBER","PERCENTAGE" ," ","INST TYPE","NUMBER","PERCENTAGE" });
    for (size_t i = 0; i < 26 / 2; i++) {
        universal_constants.add_row({ inst_type_names[i],std::to_string(inst_count[i]),std::to_string((float)(inst_count[i] * 100) / (float)inst_all)," ",
                                      inst_type_names[i + 13],std::to_string(inst_count[i + 13]),std::to_string((float)(inst_count[i + 13] * 100) / (float)inst_all) });
    }
    std::cout << universal_constants << std::endl;

}