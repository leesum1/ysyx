`include "sysconfig.v"





module ysyx_041514_alu_div_check (
    // input clk,
    // input rst,
    input signed_valid_i,
    input div32_valid_i,
    input [`ysyx_041514_XLEN-1:0] sr1_data_i,
    input [`ysyx_041514_XLEN-1:0] sr2_data_i,
    // input div_valid_i,
    output div_ready_o,
    output [`ysyx_041514_XLEN-1:0] div_out_o,
    output [`ysyx_041514_XLEN-1:0] rem_out_o
);


  // if (src2 == 0) {
  //   return -1;
  // } else if (width == 64 && S64(src1) == INT64_MIN && src2 == -1 && sign) {
  //   return INT64_MIN;
  // } else if (width == 32 && S32(src1) == INT32_MIN && src2 == -1 && sign) {
  //   return INT32_MIN;
  // }

  localparam INT64_MIN = 64'd1 << 63;
  localparam INT32_MIN = 64'd1 << 31;
  localparam NEG_ONE = ~64'd0;


  wire src2_eq_zero = sr2_data_i == 'd0;
  wire src2_eq_neg1 = sr2_data_i == NEG_ONE;
  wire src1_eq_INT64_MIN = sr2_data_i == INT64_MIN;
  wire src1_eq_INT32_MIN = sr2_data_i == INT32_MIN; // TODO 正确存疑


  reg [`ysyx_041514_XLEN-1:0] div_out;
  reg [`ysyx_041514_XLEN-1:0] rem_out;

  reg div_ready;
  always @(*) begin
      div_out   = 'd0;
      rem_out   = 'd0;
      div_ready = 'd0;
      if (src2_eq_zero) begin
        div_out   = NEG_ONE;
        div_ready = 'd1;
        rem_out   = sr1_data_i;
      end else if (div32_valid_i && src1_eq_INT32_MIN && src2_eq_neg1 && signed_valid_i) begin
        div_out   = INT32_MIN;
        div_ready = 'd1;
        rem_out   = 'd0;
      end else if (!div32_valid_i && src1_eq_INT64_MIN && src2_eq_neg1 && signed_valid_i) begin
        div_out   = INT64_MIN;
        div_ready = 'd1;
        rem_out   = 'd0;
      end
    end

  assign div_out_o   = div_out;
  assign rem_out_o   = rem_out;
  assign div_ready_o = div_ready;

endmodule
