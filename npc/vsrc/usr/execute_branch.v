`include "sysconfig.v"


module execute_branch (

    input  [  `IMM_LEN-1:0] csr_imm_i,
    input                   csr_imm_valid_i,      // 是否是立即数指令
    input  [     `XLEN-1:0] rs1_data_i,           // rs1 data
    input  [     `XLEN-1:0] csr_data_i,           // 读取的 CSR 数据
    input  [`CSROP_LEN-1:0] csr_op_i,             // csr 操作码
    output [     `XLEN-1:0] csr_exe_data_o,
    output                  csr_exe_data_valid_o
);





endmodule
