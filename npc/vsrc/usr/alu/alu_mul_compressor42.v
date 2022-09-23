module alu_mul_compressor42 (
    input  wire x0,
    input  wire x1,
    input  wire x2,
    input  wire x3,
    input  wire ci,
    output wire sum,
    output wire co,
    output wire carry
);
  wire _s_temp = x0 ^ x1 ^ x2 ^ x3;
  assign sum = ci ^ _s_temp;
  assign carry = (x0 | x1) & (x2 | x3);
  assign co = (ci & _s_temp) | ~(_s_temp | ~((x0 & x1) | (x2 & x3)));
endmodule
