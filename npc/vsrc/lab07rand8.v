module lab07rand8 (
  input            clk,
  output reg [7:0] out,
  output[7:0] seg1,seg2
);

  wire newbit; //最新移入的值 X8=X4^X3^X2^X0
  assign newbit = out[0]^out[2]^out[3]^out[4];
  always @(posedge clk) begin
    // 0 特殊处理
    if (out==8'd0) begin
      out <= 8'd1;
    end
    else begin
      out <= {newbit,out[7:1]};
    end
  end
  //数码管显示
  seg seglow (.in(out[3:0]), .out(seg1));
  seg seghigh (.in(out[7:4]), .out(seg2));
endmodule



module seg (
  input [3:0] in,
  output[7:0] out
);
//共阳极数码管字符表
  always @(*) begin
    casez (in)
      4'd0    : out[7:0]=8'hc0;
      4'd1    : out[7:0]=8'hf9;
      4'd2    : out[7:0]=8'ha4;
      4'd3    : out[7:0]=8'hb0;
      4'd4    : out[7:0]=8'h99;
      4'd5    : out[7:0]=8'h92;
      4'd6    : out[7:0]=8'h82;
      4'd7    : out[7:0]=8'hf8;
      4'd8    : out[7:0]=8'h80;
      4'd9    : out[7:0]=8'h90;
      4'ha    : out[7:0]=8'h88;
      4'hb    : out[7:0]=8'h83;
      4'hc    : out[7:0]=8'hc6;
      4'hd    : out[7:0]=8'ha1;
      4'he    : out[7:0]=8'h86;
      4'hf    : out[7:0]=8'h8e;
      default : out[7:0]=8'hff;
    endcase
  end
endmodule