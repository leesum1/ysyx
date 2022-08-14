`include "./../sysconfig.v"


module execute_csr (

    input  [  `IMM_LEN-1:0] csr_imm_i,
    input                   csr_imm_valid_i,      // 是否是立即数指令
    input  [     `XLEN-1:0] rs1_data_i,           // rs1 data
    input  [     `XLEN-1:0] csr_data_i,           // 读取的 CSR 数据
    input  [`CSROP_LEN-1:0] csr_op_i,             // csr 操作码
    output [     `XLEN-1:0] csr_exe_data_o,
    output                  csr_exe_data_valid_o
);

  wire _csr_write = (csr_op_i == `CSROP_WRITE);
  wire _csr_set = (csr_op_i == `CSROP_SET);
  wire _csr_clear = (csr_op_i == `CSROP_CLEAR);
  wire _csr_read = (csr_op_i == `CSROP_READ);
  wire _csr_none = (csr_op_i == `CSROP_NONE);

  /* CSR 不同操作的结果 */
  wire [`XLEN-1:0] _csr_op1 = csr_data_i;
  wire [`XLEN-1:0] _csr_op2 = csr_imm_valid_i ? csr_imm_i : rs1_data_i;

  wire [`XLEN-1:0] _csr_write_result = _csr_op2;
  wire [`XLEN-1:0] _csr_set_result = _csr_op1 | _csr_op2;
  wire [`XLEN-1:0] _csr_clear_result = _csr_op1 & (~_csr_op2);
  wire [`XLEN-1:0] _csr_read_result = _csr_op1;

  wire [`XLEN-1:0] _csr_exe_data_o= ({`XLEN{_csr_write}}&_csr_write_result)|
                                    ({`XLEN{_csr_set}}&_csr_set_result)|
                                    ({`XLEN{_csr_clear}}&_csr_clear_result)|
                                    ({`XLEN{_csr_read}}&_csr_read_result);


  assign csr_exe_data_o = _csr_exe_data_o;
  assign csr_exe_data_valid_o = ~(_csr_none | _csr_read);  // 读取不写回
endmodule
