#ifndef  __RISCV64_DECODER__
#define  __RISCV64_DECODER__


#include <iostream>
#include <cstdint>

class Riscv64_decoder {
private:
    /* data */

    enum OPCODE_MASK {
        MASK_OPCODE_ERR = 0,
        MASK_LOAD = 0b0000011,
        MASK_STORE = 0b0100011,
        MASK_MADD = 0b1000011,
        MASK_BRANCH = 0b1100011,
        MASK_LOAD_FP = 0b0000111,
        MASK_STORE_FP = 0b0100111,
        MASK_MSUB = 0b1000111,
        MASK_JALR = 0b1100111,
        MASK_custom_0 = 0b0001011,
        MASK_custom_1 = 0b0101011,
        MASK_NMSUB = 0b1001011,
        MASK_MISC_MEM = 0b0001111,
        MASK_AMO = 0b0101111,
        MASK_NMADD = 0b1001111,
        MASK_JAL = 0b1101111,
        MASK_OP_IMM = 0b0010011,
        MASK_OP = 0b0110011,
        MASK_OP_FP = 0b1010011,
        MASK_SYSTEM = 0b1110011,
        MASK_AUIPC = 0b0010111,
        MASK_LUI = 0b0110111,
        MASK_OP_IMM_32 = 0b0011011,
        MASK_OP_32 = 0b0111011,
        MASK_custom_2_rv128 = 0b1011011,
        MASK_custom_3_rv128 = 0b1111011,
    };

    enum OPCODE_TYPE {
        OPCODE_ERR,
        LOAD,
        STORE,
        MADD,
        BRANCH,
        LOAD_FP,
        STORE_FP,
        MSUB,
        JALR,
        custom_0,
        custom_1,
        NMSUB,
        MISC_MEM,
        AMO,
        NMADD,
        JAL,
        OP_IMM,
        OP,
        OP_FP,
        SYSTEM,
        AUIPC,
        LUI,
        OP_IMM_32,
        OP_32,
        custom_2_rv128,
        custom_3_rv128
    };

    uint64_t inst_count[26] = { 0 };

public:
    Riscv64_decoder(/* args */);
    ~Riscv64_decoder();
    uint8_t get_opcode(uint32_t inst_data);
    void perf_inst_count(uint32_t inst_data);
    void display();

};


#endif