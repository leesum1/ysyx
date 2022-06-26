module lab06count100 (
  input            clk  ,
  input            rst  , //高电平
  input            pause, //高电平
  output reg [7:0] Q    ,
  output[7:0] seg1,seg2
);

//计时器功能
  reg [63:0] c    ;
  reg        myclk;
  always @(posedge clk) begin
    if (c>=64'h8ffff) begin
      myclk <= ~myclk;
      c     <= 64'd0;
    end
    else begin
      c <= c+64'd1;
    end
  end

  //暂停功能
  wire [7:0] next,current;
  //+1
  assign next = (pause==1'b1)?Q:(Q+8'd1);
  //自动循环
  assign current = (next>8'd99) ?8'd0:next;
  // D触发器计数
  always @(posedge myclk ) begin
    if (rst) begin
      Q <= 8'd0;
    end
    else begin
      Q <= current;
    end
  end
  //数码管显示功能
  seg100 c100 (Q,seg1,seg2);
endmodule


module seg100 (
  input [7:0] in,
  output[7:0] seg1,seg2
);
  wire [7:0] low,high;
  assign low  = in%10;
  assign high = in/10;

  seg segl (low[3:0],seg1);
  seg segh (high[3:0],seg2);

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
      default : out[7:0]=8'hff;
    endcase
  end
endmodule