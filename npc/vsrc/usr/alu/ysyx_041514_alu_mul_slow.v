`include "sysconfig.v"
module ysyx_041514_alu_mul_slow (
    input                            clk,
    input                            rst,
    input                            rs1_signed_valid_i,
    input                            rs2_signed_valid_i,
    input  [  `ysyx_041514_XLEN_BUS] rs1_data_i,
    input  [  `ysyx_041514_XLEN_BUS] rs2_data_i,
    input                            mul_valid_i,
    output                           mul_ready_o,
    output [`ysyx_041514_XLEN*2-1:0] mul_out_o
);






endmodule