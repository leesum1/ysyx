module lab04ecode83 (
  input      [7:0] in    ,
  output reg       inflag,
  output reg [2:0] out   ,
  output     [7:0] seg
);
  always @(*) begin
    inflag   = 1;
    out[2:0] = 3'd0;
    casez (in)
      8'b1zzz_zzzz : out[2:0]=3'd7;
      8'b01zz_zzzz : out[2:0]=3'd6;
      8'b001z_zzzz : out[2:0]=3'd5;
      8'b0001_zzzz : out[2:0]=3'd4;
      8'b0000_1zzz : out[2:0]=3'd3;
      8'b0000_01zz : out[2:0]=3'd2;
      8'b0000_001z : out[2:0]=3'd1;
      8'b0000_0001 : out[2:0]=3'd0;
      8'b0000_0000 : begin out[2:0] = 3'd0;inflag = 0; end
    endcase
  end
  dcode38 seg38 (.in(out), .out(seg));
endmodule

module dcode38 (
  input [2:0] in,
  output[7:0] out
);
//共阳极数码管字符表
  always @(*) begin
    casez (in)
      3'd0    : out[7:0]=8'hc0;
      3'd1    : out[7:0]=8'hf9;
      3'd2    : out[7:0]=8'ha4;
      3'd3    : out[7:0]=8'hb0;
      3'd4    : out[7:0]=8'h99;
      3'd5    : out[7:0]=8'h92;
      3'd6    : out[7:0]=8'h82;
      3'd7    : out[7:0]=8'hf8;
      default : out[7:0]=8'hff;
    endcase
  end
endmodule