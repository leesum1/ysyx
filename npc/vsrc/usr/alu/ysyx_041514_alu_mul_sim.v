`include "sysconfig.v"

// 只用于仿真，为了提高仿真速度
module ysyx_041514_alu_mul_sim (
    input                clk,
    input                rst,
    input                rs1_signed_valid_i,
    input                rs2_signed_valid_i,
    input  [  `ysyx_041514_XLEN_BUS] rs1_data_i,
    input  [  `ysyx_041514_XLEN_BUS] rs2_data_i,
    input                mul_valid_i,
    output               mul_ready_o,
    output [`ysyx_041514_XLEN*2-1:0] mul_out_o

);

  /* 双符号位扩展 */
  wire _rs1_sign = (rs1_signed_valid_i) ? rs1_data_i[`ysyx_041514_XLEN-1] : 1'b0;
  wire _rs2_sign = (rs2_signed_valid_i) ? rs2_data_i[`ysyx_041514_XLEN-1] : 1'b0;
  /* 共65位 */
  wire [`ysyx_041514_XLEN:0] _rs1_65 = {_rs1_sign, rs1_data_i};
  wire [`ysyx_041514_XLEN:0] _rs2_65 = {_rs2_sign, rs2_data_i};

  wire [`ysyx_041514_XLEN*2-1:0] _mul_result = _rs1_65 * _rs2_65;
  assign mul_out_o = _mul_result;

  reg mul_ready;
  always @(posedge clk) begin
    if (rst) begin
      mul_ready <= `ysyx_041514_FALSE;
    end else begin
      if (mul_valid_i) begin
        mul_ready <= `ysyx_041514_TRUE;
      end
      else begin
        mul_ready<=`ysyx_041514_FALSE;
      end
    end
  end
assign mul_ready_o = mul_ready;

endmodule


