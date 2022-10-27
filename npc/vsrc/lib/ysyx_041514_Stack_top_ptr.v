

// 1. 和 Stake 相同，但只维护 stack 指针信息
module ysyx_041514_Stack_top_ptr #(
    DEPTH = 8
) (
    input clk,
    input rst,
    input push,
    input pop,
    output [$clog2(DEPTH) - 1:0] top_ptr_o,
    input en
);

  reg [$clog2(DEPTH) - 1:0] stack_top;
  always @(posedge clk) begin
    if (rst) begin
      stack_top <= 'b0;
    end else if (en) begin
      if (push) begin
        stack_top <= stack_top + 'd1;
      end else if (pop) begin
        stack_top <= stack_top - 'd1;
      end
    end
  end
  assign top_ptr_o = stack_top;
endmodule


