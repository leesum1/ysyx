`include "./../sysconfig.v"
module alu_mul_top (
    // input clk,  //为流水线准备
    // input rst,
    input is_sr1_signed,
    input is_sr2_signed,
    input [`XLEN-1:0] sr1_data,
    input [`XLEN-1:0] sr2_data,
    output [`XLEN*2-1:0] mul_result
);
  /* 双符号位扩展 */
  wire _sr1_sign = (is_sr1_signed) ? sr1_data[`XLEN-1] : 1'b0;
  wire _sr2_sign = (is_sr2_signed) ? sr2_data[`XLEN-1] : 1'b0;
  /* 共65位 */
  wire [`XLEN:0] _sr1_65 = {_sr1_sign, sr1_data};
  wire [`XLEN:0] _sr2_65 = {_sr2_sign, sr2_data};

  wire [`XLEN*2-1:0] _mul_result = _sr1_65 * _sr2_65;
  assign mul_result = _mul_result;
endmodule
