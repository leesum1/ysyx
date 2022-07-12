module test_invert (
    input [16-1:0] in1,
    in2,
    in3,
    in4,
    output [16-1:0] out,
    input wire _S_type,
    _B_type,
    _U_type,
    _I_type,
    _test_type
);
  // invertTem #(
  //     .DATA_LEN(16)
  // ) u_invertTem (
  //     .in (in),
  //     .out(out)
  // );

  // assign out = (_I_type) ? in4 : (_S_type) ? in1 : (_B_type) ? in2 : (_U_type) ? in3 : 16'b0;
  assign out = ({16{_I_type|_test_type}} & in1) |
               ({16{_U_type}} & in2) |
               ({16{_B_type}} & in3) |
               ({16{_S_type}} & in4);
  // assign out = _imm_data;
endmodule

// module invertTem #(
//     DATA_LEN = 1
// ) (
//     input  [DATA_LEN-1:0] in,
//     output [DATA_LEN-1:0] out
// );
//   integer i;
//   always @(*) begin
//     for (i = 0; i < DATA_LEN; i = i + 1) begin
//       out[i] = in[DATA_LEN-1-i];
//     end
//   end

// endmodule
