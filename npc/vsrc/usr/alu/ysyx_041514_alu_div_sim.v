`include "sysconfig.v"

// 只用于仿真，为了提高仿真速度
module ysyx_041514_alu_div_sim (
    input clk,
    input rst,
    input div_signed_valid_i,// 有符号树除法
    input div32_valid_i,     // 32 位除法
    input [`ysyx_041514_XLEN-1:0] dividented_i, // 被除数 rs1
    input [`ysyx_041514_XLEN-1:0] divisor_i,// 除数 rs2
    input div_valid_i,
    output [`ysyx_041514_XLEN-1:0] div_data_o,
    output [`ysyx_041514_XLEN-1:0] rem_data_o,
    output div_ready_o
);


  /* 64 位除法 */
  wire signed [`ysyx_041514_XLEN-1:0] sr1_64_signed = dividented_i;
  wire signed [`ysyx_041514_XLEN-1:0] sr2_64_signed = divisor_i;
  // 有符号
  wire signed [`ysyx_041514_XLEN-1:0] div64_signed = sr1_64_signed / sr2_64_signed;
  wire signed [`ysyx_041514_XLEN-1:0] rem64_signed = sr1_64_signed % sr2_64_signed;
  // 无符号
  wire [`ysyx_041514_XLEN-1:0] div64_unsigned = dividented_i / divisor_i;
  wire [`ysyx_041514_XLEN-1:0] rem64_unsigned = dividented_i % divisor_i;
  // 结果
  wire [`ysyx_041514_XLEN-1:0] div64_result = (div_signed_valid_i) ? div64_signed : div64_unsigned;
  wire [`ysyx_041514_XLEN-1:0] rem64_result = (div_signed_valid_i) ? rem64_signed : rem64_unsigned;

  /* 32 位除法 */
  wire signed [32-1:0] sr1_32_signed = dividented_i[31:0];
  wire signed [32-1:0] sr2_32_signed = divisor_i[31:0];
  //有符号
  wire signed [32-1:0] div32_signed = sr1_32_signed / sr2_32_signed;
  wire signed [32-1:0] rem32_signed = sr1_32_signed % sr2_32_signed;
  //无符号
  wire [32-1:0] div32_unsigned = dividented_i[31:0] / divisor_i[31:0];
  wire [32-1:0] rem32_unsigned = dividented_i[31:0] % divisor_i[31:0];
  //结果
  wire [32-1:0] div32_result = (div_signed_valid_i) ? div32_signed : div32_unsigned;
  wire [32-1:0] rem32_result = (div_signed_valid_i) ? rem32_signed : rem32_unsigned;

  // 最终结果
  assign div_data_o = (div32_valid_i) ? {32'b0, div32_result} : div64_result;
  assign rem_data_o = (div32_valid_i) ? {32'b0, rem32_result} : rem64_result;



  reg div_ready;
  always @(posedge clk) begin
    if (rst) begin
      div_ready <= `ysyx_041514_FALSE;
    end else begin
      if (div_valid_i) begin
        div_ready <= `ysyx_041514_TRUE;
      end
      else begin
        div_ready<=`ysyx_041514_FALSE;
      end
    end
  end
assign div_ready_o = div_ready;

endmodule
