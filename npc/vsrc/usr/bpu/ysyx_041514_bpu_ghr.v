module ysyx_041514_bpu_ghr #(
    GHR_LEN = 32
) (
    input clk,
    input rst,
    input bpu_update_valid_i,
    input bpu_update_taken_i,
    output [GHR_LEN-1:0] bpu_ghr_data_o
);


  reg [GHR_LEN-1:0] ghr_reg;


  always @(posedge clk) begin
    if (rst) begin
      ghr_reg <= 'd0;
    end else if (bpu_update_valid_i) begin
      ghr_reg <= {ghr_reg[GHR_LEN-1-1:0], bpu_update_taken_i};
    end
  end

  assign bpu_ghr_data_o = ghr_reg;
endmodule
