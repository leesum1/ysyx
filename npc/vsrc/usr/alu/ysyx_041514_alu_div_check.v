`include "sysconfig.v"

// ┌───────────────────────┬──────────┬─────────┬──────────┬───────────┬──────────┬──────────┐
// │ Condition             │ Dividend │  Dvisor │  DIVU[W] │   REMU[W] │   DIV[W ]│  REM[W]  │
// ├───────────────────────┼──────────┼─────────┼──────────┼───────────┼──────────┼──────────┤
// │ Division by zero      │    X     │    0    │   2^L-1  │     X     │    -1    │    X     │
// ├───────────────────────┼──────────┼─────────┼──────────┼───────────┼──────────┼──────────┤
// │ Overflow (signed only)│ -2^(L-1) │   -1    │     -    │      -    │  -2^(L-1)│    0     │
// └───────────────────────┴──────────┴─────────┴──────────┴───────────┴──────────┴──────────┘
//  Table 7.1: Semantics for division by zero and division overflow. L is the width of the operation in
//  bits: XLEN for DIV[U] and REM[U], or 32 for DIV[U]W and REM[U]W.
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


  localparam INT64_MIN = 64'd1 << 63;
  localparam INT32_MIN = 32'd1 << 31;
  localparam NEG_ONE = 64'hffff_ffff_ffff_ffff;


  wire src2_eq_zero64 = sr2_data_i == 64'd0;
  wire src2_eq_zero32 = sr2_data_i[31:0] == 32'd0;
  wire src2_eq_neg1 = sr2_data_i == NEG_ONE;
  wire src1_eq_INT64_MIN = sr2_data_i == INT64_MIN;
  wire src1_eq_INT32_MIN = sr2_data_i[31:0] == INT32_MIN;  // TODO 正确存疑


  reg [`ysyx_041514_XLEN-1:0] div_out;
  reg [`ysyx_041514_XLEN-1:0] rem_out;

  reg div_ready;
  always @(*) begin
    div_out   = 'd0;
    rem_out   = 'd0;
    div_ready = 'd0;
    // Division by zero : divw remw
    if (src2_eq_zero32 && div32_valid_i && signed_valid_i) begin
      div_out   = NEG_ONE;
      div_ready = 'd1;
      rem_out   = sr1_data_i;
    end  // Division by zero : divuw remuw
    else if (src2_eq_zero32 && div32_valid_i && !signed_valid_i) begin
      div_out   = 64'hffff_ffff;  // 2^32 -1
      div_ready = 'd1;
      rem_out   = sr1_data_i;
    end  // Division by zero : div rem
    else if (src2_eq_zero64 && !div32_valid_i && signed_valid_i) begin
      div_out   = NEG_ONE;
      div_ready = 'd1;
      rem_out   = sr1_data_i;
    end  // Division by zero : divu remu
    else if (src2_eq_zero64 && !div32_valid_i && !signed_valid_i) begin
      div_out   = 64'hffff_ffff_ffff_ffff;  // 2^64 -1
      div_ready = 'd1;
      rem_out   = sr1_data_i;
    end  //  Overflow (signed only) divw remw
    else if (div32_valid_i && src1_eq_INT32_MIN && src2_eq_neg1 && signed_valid_i) begin
      div_out   = {32'hffff_ffff,INT32_MIN};
      div_ready = 'd1;
      rem_out   = 'd0;
    end  //  Overflow (signed only) div rem
    else if (!div32_valid_i && src1_eq_INT64_MIN && src2_eq_neg1 && signed_valid_i) begin
      div_out   = INT64_MIN;
      div_ready = 'd1;
      rem_out   = 'd0;
    end
  end

  assign div_out_o   = div_out;
  assign rem_out_o   = rem_out;
  assign div_ready_o = div_ready;

endmodule
