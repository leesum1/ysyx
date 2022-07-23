module alu_mul_compressor52 (
    input  x0,
    input  x1,
    input  x2,
    input  x3,
    input  x4,
    input  cin0,
    input  cin1,
    output cout0,
    output cout1,
    output sum,
    output carry
);
  wire _x0_x1_xor = x0 ^ x1;
  wire _x3_x4_xor = x3 ^ x4;
  wire _x0_x1_x2_x3_x4_cin0_xor = _x0_x1_xor ^ x2 ^ _x3_x4_xor ^ cin0;
  assign cout0 = (_x0_x1_xor) ? x2 : x0;
  assign cout1 = (_x3_x4_xor) ? _x0_x1_xor : x3;
  assign carry = (_x0_x1_x2_x3_x4_cin0_xor) ? cin1 : _x3_x4_xor;
  assign sum   = _x0_x1_x2_x3_x4_cin0_xor ^ cin1;
endmodule
