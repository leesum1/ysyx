
`define XLEN 64             //cpu 位数
`define INST_LEN 32         //指令长度
`define IMM_LEN 64          //立即数长度
`define REG_NUM 32          //寄存器个数
`define REG_ADDRWIDTH 5     //寄存器地址宽度
`define PC_RESET_ADDR `XLEN'h0000000080000000



`define INST_NOP 32'h00000013           //ADDI x0, x0, 0
`define TRUE 1'b1
`define FALSE 1'b0

/* BUS */
`define XLEN_BUS `XLEN-1:0


/* exc 操作码 */
`define EXCOP_LEN 5

`define EXCOP_NONE `EXCOP_LEN'd0
`define EXCOP_AUIPC `EXCOP_LEN'd1
`define EXCOP_LUI `EXCOP_LEN'd2
`define EXCOP_JAL `EXCOP_LEN'd3
`define EXCOP_JALR `EXCOP_LEN'd4
`define EXCOP_LOAD `EXCOP_LEN'd5
`define EXCOP_STORE `EXCOP_LEN'd6
`define EXCOP_BRANCH `EXCOP_LEN'd7
`define EXCOP_OPIMM `EXCOP_LEN'd8
`define EXCOP_OPIMM32 `EXCOP_LEN'd9
`define EXCOP_OP `EXCOP_LEN'd10
`define EXCOP_OP32 `EXCOP_LEN'd11
`define EXCOP_CSR `EXCOP_LEN'd12

`define EXCOP_EBREAK `EXCOP_LEN'd13


/* ALU 操作码 */
`define ALUOP_LEN 6

`define ALUOP_NONE `ALUOP_LEN'd0
`define ALUOP_ADD `ALUOP_LEN'd1
`define ALUOP_SUB `ALUOP_LEN'd2
/* 逻辑操作 */
`define ALUOP_XOR `ALUOP_LEN'd3
`define ALUOP_OR `ALUOP_LEN'd4
`define ALUOP_AND `ALUOP_LEN'd5
/* 移位操作 */
`define ALUOP_SLL `ALUOP_LEN'd6
`define ALUOP_SRL `ALUOP_LEN'd7
`define ALUOP_SRA `ALUOP_LEN'd8
//忽略高32位的移位操作
`define ALUOP_SLLW `ALUOP_LEN'd9
`define ALUOP_SRLW `ALUOP_LEN'd10
`define ALUOP_SRAW `ALUOP_LEN'd11
/* 比较操作 */
`define ALUOP_SLT `ALUOP_LEN'd12
`define ALUOP_SLTU `ALUOP_LEN'd13

`define ALUOP_BEQ `ALUOP_LEN'd14
`define ALUOP_BNE `ALUOP_LEN'd15
`define ALUOP_BLT `ALUOP_LEN'd16
`define ALUOP_BGE `ALUOP_LEN'd17
`define ALUOP_BLTU `ALUOP_LEN'd18
`define ALUOP_BGEU `ALUOP_LEN'd19

/* 乘除法 */
`define ALUOP_MUL `ALUOP_LEN'd20
`define ALUOP_MULH `ALUOP_LEN'd21
`define ALUOP_MULHSU `ALUOP_LEN'd22
`define ALUOP_MULHU `ALUOP_LEN'd23
`define ALUOP_MULW `ALUOP_LEN'd24

`define ALUOP_DIV `ALUOP_LEN'd25
`define ALUOP_DIVU `ALUOP_LEN'd26
`define ALUOP_REM `ALUOP_LEN'd27
`define ALUOP_REMU `ALUOP_LEN'd28
`define ALUOP_DIVW `ALUOP_LEN'd29
`define ALUOP_DIVUW `ALUOP_LEN'd30
`define ALUOP_REMW `ALUOP_LEN'd31
`define ALUOP_REMUW `ALUOP_LEN'd32

/* mem操作码 */
`define MEMOP_LEN 4

/* 读取 */

`define MEMOP_NONE `MEMOP_LEN'd0 //空操作

`define MEMOP_LB `MEMOP_LEN'd1
`define MEMOP_LH `MEMOP_LEN'd2
`define MEMOP_LW `MEMOP_LEN'd3
`define MEMOP_LBU `MEMOP_LEN'd4
`define MEMOP_LHU `MEMOP_LEN'd5
`define MEMOP_LD `MEMOP_LEN'd6
`define MEMOP_LWU `MEMOP_LEN'd7

/* 写入 */
`define MEMOP_SB `MEMOP_LEN'd8
`define MEMOP_SH `MEMOP_LEN'd9
`define MEMOP_SW `MEMOP_LEN'd10
`define MEMOP_SD `MEMOP_LEN'd11


/* writeback 操作码 */
`define WBOP_LEN 4

/* 读取 */
`define WBOP_RD `WBOP_LEN'd0
`define WBOP_NONE `WBOP_LEN'd1

/* PC操作码 */
`define PCOP_LEN 4

`define PCOP_NONE `PCOP_LEN'd0 //空操作
`define PCOP_BRANCH `PCOP_LEN'd1
`define PCOP_JAL `PCOP_LEN'd2
`define PCOP_JALR `PCOP_LEN'd3
`define PCOP_INC4 `PCOP_LEN'd4
`define PCOP_TRAP `PCOP_LEN'd5


/*************CSR************/

`define CSROP_LEN 3


`define CSROP_NONE `CSROP_LEN'd0
`define CSROP_READ `CSROP_LEN'd1
`define CSROP_WRITE `CSROP_LEN'd2
`define CSROP_SET `CSROP_LEN'd3
`define CSROP_CLEAR `CSROP_LEN'd4


//寄存器地址
`define CSR_REG_ADDRWIDTH 12
//Machine Trap Setup
`define CSR_MSTATUS 12'h300
`define CSR_MISA 12'h301
`define CSR_MEDELEG 12'h302
`define CSR_MIDELEG 12'h303
`define CSR_MIE 12'h304
`define CSR_MTVEC 12'h305
`define CSR_MCOUNTEREN 12'h306
//Machine Trap Handling
`define CSR_MSCRATCH 12'h340
`define CSR_MEPC 12'h341
`define CSR_MCAUSE 12'h342
`define CSR_MTVAL 12'h343
`define CSR_MIP 12'h344
`define CSR_MTINST 12'h34a
`define CSR_MTVAL2 12'h34b


`define CSR_MSTATUS_DEFAULT `XLEN'ha00001800

/**********tarp**********/




`define TRAP_INST_ADDR_MISALIGNED 0
`define TRAP_INST_ACCESS_FAULT 1
`define TRAP_ILLEGAL_INST 2
`define TRAP_BREAKPOINT 3
`define TRAP_LOAD_ADDR_MISALIGNED 4
`define TRAP_LOAD_ACCESS_FAULT 5
`define TRAP_STORE_ADDR_MISALIGNED 6
`define TRAP_STORE_ACCESS_FAULT 7
`define TRAP_ECALL_U 8
`define TRAP_ECALL_S 9 
`define TRAP_RESERVED0 10 
`define TRAP_ECALL_M 11
`define TRAP_INST_PAGE_FAULT 12
`define TRAP_LOAD_PAGE_FAULT 13
`define TRAP_RESERVED1 14
`define TRAP_STORE_PAGE_FAULT 15
`define TRAP_MRET 16 // 把 MRET 当成 trap
`define TRAP_EBREAK 17 // 把 EBREAK 当成 trap
`define TRAP_ECALL 18 // 把 ECALL 当成 trap

`define TRAP_LEN 19
`define TRAP_BUS `TRAP_LEN-1:0



//PC,IF_ID, ID_EX, EX_MEM, MEM_WB
`define CTRLBUS_PC 0
`define CTRLBUS_IF_ID 1
`define CTRLBUS_ID_EX 2
`define CTRLBUS_EX_MEM 3
`define CTRLBUS_MEM_WB 4










