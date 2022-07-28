`include "./../sysconfig.v"
module alu_div_top (
    // input clk,  //为流水线准备
    // input rst,
    // input is_sr1_signed,
    // input is_sr2_signed,
    input issigned,
    input isdivw,
    input [`XLEN-1:0] sr1_data,
    input [`XLEN-1:0] sr2_data,
    output [`XLEN-1:0] div_result,
    output [`XLEN-1:0] rem_result
);
  /* 64 位除法 */
  wire signed [`XLEN-1:0] sr1_64_signed = sr1_data;
  wire signed [`XLEN-1:0] sr2_64_signed = sr2_data;

  wire signed [`XLEN-1:0] div64_signed = sr1_64_signed / sr2_64_signed;
  wire signed [`XLEN-1:0] rem64_signed = sr1_64_signed % sr2_64_signed;

  wire [`XLEN-1:0] div64_unsigned = sr1_data / sr2_data;
  wire [`XLEN-1:0] rem64_unsigned = sr1_data % sr2_data;
  wire [`XLEN-1:0] div64_result = (issigned) ? div64_signed : div64_unsigned;
  wire [`XLEN-1:0] rem64_result = (issigned) ? div64_signed : rem64_unsigned;

  /* 32 位除法 */
  wire signed [32-1:0] sr1_32_signed = sr1_data[31:0];
  wire signed [32-1:0] sr2_32_signed = sr2_data[31:0];

  wire signed [32-1:0] div32_signed = sr1_32_signed / sr2_32_signed;
  wire signed [32-1:0] rem32_signed = sr1_32_signed % sr2_32_signed;

  wire [32-1:0] div32_unsigned = sr1_data[31:0] / sr2_data[31:0];
  wire [32-1:0] rem32_unsigned = sr1_data[31:0] % sr2_data[31:0];

  wire [32-1:0] div32_result = (issigned) ? div32_signed : div32_unsigned;
  wire [32-1:0] rem32_result = (issigned) ? rem32_signed : rem32_unsigned;

  assign div_result = (isdivw) ? {32'b0, div32_result} : div64_result;
  assign rem_result = (isdivw) ? {32'b0, rem32_result} : rem64_result;

endmodule
