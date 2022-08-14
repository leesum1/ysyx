`include "./../sysconfig.v"
module alu_mul_top (
    // input clk,  //为流水线准备
    // input rst,
    input rs1_signed_valid_i,
    input rs2_signed_valid_i,
    input [`XLEN-1:0] rs1_data_i,
    input [`XLEN-1:0] rs2_data_i,
    output [`XLEN*2-1:0] mul_out_o
);
  /* 双符号位扩展 */
  wire _rs1_sign = (rs1_signed_valid_i) ? rs1_data_i[`XLEN-1] : 1'b0;
  wire _rs2_sign = (rs2_signed_valid_i) ? rs2_data_i[`XLEN-1] : 1'b0;
  /* 共65位 */
  wire [`XLEN:0] _rs1_65 = {_rs1_sign, rs1_data_i};
  wire [`XLEN:0] _rs2_65 = {_rs2_sign, rs2_data_i};

  wire [`XLEN*2-1:0] _mul_result = _rs1_65 * _rs2_65;
  assign mul_out_o = _mul_result;
endmodule
