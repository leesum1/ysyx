
`define XLEN 64             //cpu 位数
`define INST_LEN 32         //指令长度
`define IMM_LEN 64          //立即数长度
`define REG_NUM 32          //寄存器个数
`define REG_ADDRWIDTH 5     //寄存器地址宽度
`define PC_RESET_ADDR `XLEN'h0000000080000000

/* exc 操作码 */
`define EXCOP_LEN 4

`define EXCOP_ALU `EXCOP_LEN'd0
`define EXCOP_AUIPC `EXCOP_LEN'd1
`define EXCOP_LUI `EXCOP_LEN'd2
`define EXCOP_JAL `EXCOP_LEN'd3
`define EXCOP_JALR `EXCOP_LEN'd4
`define EXCOP_ECALL `EXCOP_LEN'd5
`define EXCOP_EBREAK `EXCOP_LEN'd6
`define EXCOP_REG_REG `EXCOP_LEN'd7
`define EXCOP_REG_IMM `EXCOP_LEN'd8

/* ALU 操作码 */
`define ALUOP_LEN 5

`define ALUOP_ADD `ALUOP_LEN'd0
`define ALUOP_SUB `ALUOP_LEN'd1
/* 逻辑操作 */
`define ALUOP_XOR `ALUOP_LEN'd2
`define ALUOP_OR `ALUOP_LEN'd3
`define ALUOP_AND `ALUOP_LEN'd4
/* 移位操作 */
`define ALUOP_SLL `ALUOP_LEN'd5
`define ALUOP_SRL `ALUOP_LEN'd6
`define ALUOP_SRA `ALUOP_LEN'd7
/* 比较操作 */
`define ALUOP_SLT `ALUOP_LEN'd8
`define ALUOP_SLTU `ALUOP_LEN'd9

`define ALUOP_BEQ `ALUOP_LEN'd10
`define ALUOP_BNE `ALUOP_LEN'd11
`define ALUOP_BLT `ALUOP_LEN'd12
`define ALUOP_BGE `ALUOP_LEN'd13
`define ALUOP_BLTU `ALUOP_LEN'd14
`define ALUOP_BGEU `ALUOP_LEN'd15

/* mem操作码 */
`define MEMOP_LEN 4

/* 读取 */
`define MEMOP_LB `MEMOP_LEN'd0
`define MEMOP_LH `MEMOP_LEN'd1
`define MEMOP_LW `MEMOP_LEN'd2
`define MEMOP_LBU `MEMOP_LEN'd3
`define MEMOP_LHU `MEMOP_LEN'd4
`define MEMOP_LD `MEMOP_LEN'd5
`define MEMOP_LWU `MEMOP_LEN'd6

/* 写入 */
`define MEMOP_SB `MEMOP_LEN'd7
`define MEMOP_SH `MEMOP_LEN'd8
`define MEMOP_SW `MEMOP_LEN'd9
`define MEMOP_SD `MEMOP_LEN'd10

/* writeback 操作码 */
`define WBOP_LEN 4

/* 读取 */
`define WBOP_RD `WBOP_LEN'd0
`define WBOP_NONE `WBOP_LEN'd1





