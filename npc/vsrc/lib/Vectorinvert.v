module Vectorinvert #(
    DATA_LEN = 1
) (
    input [DATA_LEN-1:0] in,
    output reg [DATA_LEN-1:0] out
);
  integer i;
  always @(*) begin
    for (i = 0; i < DATA_LEN; i = i + 1) begin
      out[i] = in[DATA_LEN-1-i];
    end
  end

endmodule
