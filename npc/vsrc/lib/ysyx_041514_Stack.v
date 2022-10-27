


module ysyx_041514_Stack #(
    WIDTH = 32,
    DEPTH = 8
) (
    input clk,
    input rst,
    input [$clog2(DEPTH) - 1:0] new_top_prt,
    input new_top_ptr_valid,
    output [WIDTH - 1:0] q,
    input [WIDTH - 1:0] d,
    input push,
    input pop,
    input en
);

  reg [$clog2(DEPTH) - 1:0] stack_top;

  reg [WIDTH - 1:0] stack_buff[DEPTH-1:0];

  always @(posedge clk) begin
    if (rst) begin
      stack_top <= 'b0;
    end else if (new_top_ptr_valid) begin
      stack_top <= new_top_prt;
    end else if (en) begin
      if (push) begin
        stack_top <= stack_top + 'd1;
        stack_buff[stack_top] <= d;
      end else if (pop) begin
        stack_top <= stack_top - 'd1;
      end
    end
  end

  assign q = stack_buff[stack_top-1];


endmodule


