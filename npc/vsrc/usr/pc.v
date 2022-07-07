`include "sysconfig.v"
module pc (
    input wire clk,
    input wire rst,
    output reg [`XLEN-1:0] pc_out
);
  wire [`XLEN-1:0] _pc_in;
  reg  [`XLEN-1:0] _pc_out;
  // pc自增4
  assign _pc_in = _pc_out + 4;

  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`PC_RESET_ADDR)
  ) u_regpc (
      .clk (clk),
      .rst (rst),
      .din (_pc_in),
      .dout(_pc_out),
      .wen (1)
  );

  assign pc_out = _pc_out;
endmodule
