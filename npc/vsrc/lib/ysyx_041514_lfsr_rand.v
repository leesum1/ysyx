module ysyx_041514_lfsr_rand #(
    parameter DEPTH = 32
) (
    input                      clk_i,
    input                      rst_i,
    input                      alloc_i,
    output [$clog2(DEPTH)-1:0] alloc_entry_o
);
  localparam ADDR_W = $clog2(DEPTH);

  reg [ADDR_W-1:0] lfsr_q;

  always @(posedge clk_i) begin
    if (rst_i) lfsr_q <= {ADDR_W{1'b0}};
    else if (alloc_i) begin
      if (lfsr_q == {ADDR_W{1'b1}}) begin
        lfsr_q <= {ADDR_W{1'b0}};
      end else begin
        lfsr_q <= lfsr_q + 1;
      end  //if (lfsr_q == {ADDR_W{1'b1}}) begin
    end  //if (n_rst_i == `RstEnable)
  end  //always @ (posedge clk_i or negedge  n_rst_i) begin

  assign alloc_entry_o = lfsr_q[ADDR_W-1:0];

endmodule
