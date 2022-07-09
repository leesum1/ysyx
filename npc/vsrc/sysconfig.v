
`define XLEN 64             //cpu 位数
`define INST_LEN 32         //指令长度
`define IMM_LEN 32          //立即数长度
`define REG_NUM 32          //寄存器个数
`define REG_ADDRWIDTH 5     //寄存器地址宽度
`define PC_RESET_ADDR `XLEN'h0000000080000000


`define ALUOP_LEN 4

`define ALUOP_ADD 4'd0
`define ALUOP_SUB 4'd1
/* 移位操作 */
`define ALUOP_SRA 4'd2
`define ALUOP_SRL 4'd3
`define ALUOP_SLL 4'd4
