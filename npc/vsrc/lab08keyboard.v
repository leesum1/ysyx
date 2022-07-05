module lab08keyboard (
    input clk,
    input rst,
    input ps2_clk,
    input ps2_data,
    output[7:0] seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8
  );
  reg [7:0] ps2out;
  reg [23:0] ps2segin ;
  reg ps2ready,ps2next,ps2over;
  ps2_keyboard ps2keyboard(.clk(clk),
                           .clrn(~rst), //低电平复位
                           .ps2_clk(ps2_clk),
                           .ps2_data(ps2_data),
                           .data(ps2out),
                           .ready(ps2ready),
                           .nextdata_n(ps2next),
                           .overflow(ps2over)
                          );

  /***************************三段式状态机*******************************/

  parameter stateRead = 4'b0001;
  parameter stateNotify = 4'b0010; //拉低nextdata_n,通知读取完毕
  parameter stateNotify2 = 4'b0100;//拉低nextdata_n,通知读取完毕
  parameter stateIdle = 4'b1000;
  reg [3:0] state_current,state_next;
  //同步状态转移
  always @(posedge clk or posedge rst)
  begin
    if (rst)
    begin
      state_current<=stateIdle;
    end
    else
    begin
      state_current<=state_next;
    end
  end
  //异步改变状态
  always @(*)
  begin
    case (state_current)
      stateIdle:
      begin
        state_next=(ps2ready==1'b1)?stateRead:stateIdle;
      end
      stateRead:
      begin
        state_next=stateNotify;
      end
      stateNotify:
      begin
        state_next=stateNotify2;
      end
      stateNotify2:
      begin
        state_next=stateIdle;
      end
      default:
        state_next=stateIdle;
    endcase
  end
  //每个状态的输出
  always @(posedge clk)
  begin
    case (state_current)
      stateIdle:
      begin
        ps2next<=1;//默认拉高
      end
      stateNotify:
      begin
        ps2next<=0;//总线拉低
      end
      stateNotify2:
      begin
        ps2next<=0;//总线拉低
      end
      stateRead:
      begin
        ps2segin[23:0] <={ps2segin[15:0],ps2out[7:0]};//保存读取的最后三个值
      end
      default:
      begin
        ps2next<=1;//默认拉高
      end
    endcase
  end
  /*********************************************************************/

  /**
  * 如果读取到的最后三个值是 (A,0XF0,A)形式，则是断码，关闭数码管显示
  * (eg:有bug,找了很久没有找出来，程序复位时，segen的值是1，不是0
  * 经过排查，为 if 语句出错，但找不到原因。)
  **/
  reg segen  ; //数码管控制端口
  always @(*)
  begin
    if ((ps2segin[15:8]==8'hf0)
        &&ps2segin[7:0]==ps2segin[23:16])
    begin
      segen = 0;
    end
    else
    begin
      segen = 1;
    end
  end


  /*当按下键盘时，segen = 1,数码管亮
  * 松开键盘时，segen = 0,数码管灭
  * 通过捕获 segen 的上升沿，或下降沿，即可获取按下键盘的次数
  */
  reg [3:0 ]segcountl ,segcounth;
  always @(negedge segen or posedge rst)
  begin
    if (rst)
    begin
      segcountl<=4'b0;
      segcounth<=4'b0;
    end
    else
    begin
      if (segcountl==4'd9)
      begin
        segcounth <= segcounth +4'd1;
        segcountl <= 4'd0;
      end
      else
      begin
        segcountl <= segcountl +4'd1;
      end
    end


  end
  /* 键盘扫描码显示 */
  seg seglow1 (.in(ps2segin[3:0]), .out(seg1),.en(segen ));
  seg seghigh1 (.in(ps2segin[7:4]), .out(seg2),.en(segen));
  /* 键盘 ASCII 码显示 */
  reg  [7:0]ascii;
  toASCII ps2ascii(.addr(ps2segin[7:0]),.val(ascii));

  seg seglow2 (.in(ascii[3:0]), .out(seg3),.en(segen ));
  seg seghigh2 (.in(ascii[7:4]), .out(seg4),.en(segen));

  /* 没有用到，不显示 */
  seg seglow3 (.in(ps2segin[19:16]), .out(seg5),.en(1'd0 ));
  seg seghigh3 (.in(ps2segin[23:20]), .out(seg6),.en(1'd0 ));

  /* 计数显示 */
  seg segnuml (.in(segcountl), .out(seg7),.en(1'd1 ));
  seg seghnumh (.in(segcounth), .out(seg8),.en(1'd1));

endmodule




/* 解析PS2键盘数据 */
module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,
                      ready,nextdata_n,overflow);
  input clk,clrn,ps2_clk,ps2_data;
  input nextdata_n;
  output [7:0] data;
  output reg ready;
  output reg overflow;     // fifo overflow
  // internal signal, for test
  reg [9:0] buffer;        // ps2_data bits
  reg [7:0] fifo[7:0];     // data fifo
  reg [2:0] w_ptr,r_ptr;   // fifo write and read pointers
  reg [3:0] count;  // count ps2_data bits
  // detect falling edge of ps2_clk
  reg [2:0] ps2_clk_sync;

  always @(posedge clk)
  begin
    ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
  end

  wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

  always @(posedge clk)
  begin
    if (clrn == 0)
    begin // reset
      count <= 0;
      w_ptr <= 0;
      r_ptr <= 0;
      overflow <= 0;
      ready<= 0;
    end
    else
    begin
      if ( ready )
      begin // read to output next data
        if(nextdata_n == 1'b0) //read next data
        begin
          r_ptr <= r_ptr + 3'b1;

          if(w_ptr==(r_ptr+1'b1)) //empty
          begin
            ready <= 1'b0;
            //$display("read %x,write%x,ready%x", r_ptr,w_ptr,ready);
          end
        end
      end
      if (sampling)
      begin
        if (count == 4'd10)
        begin
          if ((buffer[0] == 0) &&  // start bit
              (ps2_data)       &&  // stop bit
              (^buffer[9:1]))
          begin      // odd  parity
            fifo[w_ptr] <= buffer[8:1];  // kbd scan code
            w_ptr <= w_ptr+3'b1;
            ready <= 1'b1;
            overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
          end
          count <= 0;     // for next
        end
        else
        begin
          buffer[count] <= ps2_data;  // store ps2_data
          count <= count + 3'b1;
        end
      end
    end
  end
  assign data = fifo[r_ptr]; //always set output data

endmodule



module seg (
    input [3:0] in,
    output[7:0] out,
    input en
  );
  //共阳极数码管字符表
  always @(*)
  begin
    if (en==1'b1)
    begin
      casez (in)
        4'd0    :
          out[7:0]=8'hc0;
        4'd1    :
          out[7:0]=8'hf9;
        4'd2    :
          out[7:0]=8'ha4;
        4'd3    :
          out[7:0]=8'hb0;
        4'd4    :
          out[7:0]=8'h99;
        4'd5    :
          out[7:0]=8'h92;
        4'd6    :
          out[7:0]=8'h82;
        4'd7    :
          out[7:0]=8'hf8;
        4'd8    :
          out[7:0]=8'h80;
        4'd9    :
          out[7:0]=8'h90;
        4'ha    :
          out[7:0]=8'h88;
        4'hb    :
          out[7:0]=8'h83;
        4'hc    :
          out[7:0]=8'hc6;
        4'hd    :
          out[7:0]=8'ha1;
        4'he    :
          out[7:0]=8'h86;
        4'hf    :
          out[7:0]=8'h8e;
        default :
          out[7:0]=8'hff;
      endcase
    end
    else
    begin
      out[7:0]=8'hff;
    end
  end
endmodule


module toASCII (
    input [7:0] addr,
    output reg [7:0] val
  );
  always @(*)
  begin
    case (addr)
      8'h16:
        val=8'd49;
      8'h1e:
        val=8'd50;
      8'h26:
        val=8'd51;
      8'h25:
        val=8'd52;
      8'h2e:
        val=8'd53;
      8'h36:
        val=8'd54;
      8'h3d:
        val=8'd55;
      8'h3e:
        val=8'd56;
      8'h46:
        val=8'd57;
      8'h45:
        val=8'd48;
      8'h15:
        val=8'd97;
      default:
        val=8'hff;
    endcase
  end

endmodule
