`include "./../sysconfig.v"
/* 除法器的设计不能采用双符号位,有符号和无符号不能统一,只能单独计算符号位 */
module alu_div_top (
    // input clk,  //为流水线准备
    // input rst,
    input signed_valid_i,
    input div32_valid_i,
    input [`XLEN-1:0] sr1_data_i,
    input [`XLEN-1:0] sr2_data_i,
    output [`XLEN-1:0] div_out_o,
    output [`XLEN-1:0] rem_out_o
);
  /* 64 位除法 */
  wire signed [`XLEN-1:0] sr1_64_signed = sr1_data_i;
  wire signed [`XLEN-1:0] sr2_64_signed = sr2_data_i;
  // 有符号
  wire signed [`XLEN-1:0] div64_signed = sr1_64_signed / sr2_64_signed;
  wire signed [`XLEN-1:0] rem64_signed = sr1_64_signed % sr2_64_signed;
  // 无符号
  wire [`XLEN-1:0] div64_unsigned = sr1_data_i / sr2_data_i;
  wire [`XLEN-1:0] rem64_unsigned = sr1_data_i % sr2_data_i;
  // 结果
  wire [`XLEN-1:0] div64_result = (signed_valid_i) ? div64_signed : div64_unsigned;
  wire [`XLEN-1:0] rem64_result = (signed_valid_i) ? rem64_signed : rem64_unsigned;

  /* 32 位除法 */
  wire signed [32-1:0] sr1_32_signed = sr1_data_i[31:0];
  wire signed [32-1:0] sr2_32_signed = sr2_data_i[31:0];
  //有符号
  wire signed [32-1:0] div32_signed = sr1_32_signed / sr2_32_signed;
  wire signed [32-1:0] rem32_signed = sr1_32_signed % sr2_32_signed;
  //无符号
  wire [32-1:0] div32_unsigned = sr1_data_i[31:0] / sr2_data_i[31:0];
  wire [32-1:0] rem32_unsigned = sr1_data_i[31:0] % sr2_data_i[31:0];
  //结果
  wire [32-1:0] div32_result = (signed_valid_i) ? div32_signed : div32_unsigned;
  wire [32-1:0] rem32_result = (signed_valid_i) ? rem32_signed : rem32_unsigned;

  // 最终结果
  assign div_out_o = (div32_valid_i) ? {32'b0, div32_result} : div64_result;
  assign rem_out_o = (div32_valid_i) ? {32'b0, rem32_result} : rem64_result;

endmodule
