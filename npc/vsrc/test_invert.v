module test_invert (
    input  [16-1:0] in,
    output [16-1:0] out
);
  invertTem #(
      .DATA_LEN(16)
  ) u_invertTem (
      .in (in),
      .out(out)
  );
endmodule

module invertTem #(
    DATA_LEN = 1
) (
    input  [DATA_LEN-1:0] in,
    output [DATA_LEN-1:0] out
);
  integer i;
  always @(*) begin
    for (i = 0; i < DATA_LEN; i = i + 1) begin
      out[i] = in[DATA_LEN-1-i];
    end
  end

endmodule
