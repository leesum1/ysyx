`include "sysconfig.v"


module icache_data #(
    IDX_LEN = 5,  // 组号 长度
    BLK_LEN = 4,  // 块内地址 长度
    TAG_NUM = 32  // tag 个数
) (
    input clk,
    input rst,
    input [IDX_LEN-1:0] icache_index_i,  // index
    input [BLK_LEN-1:0] icache_blk_addr_i,
    input [128-1:0] icache_line_wdata_i,
    input  [128-1:0] icache_wmask,
    input icache_wen_i,
    output [128-1:0]    icache_line_rdata_o
);


  S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW (
      .Q   (icache_line_rdata_o),
      .CLK (clk),
      .CEN (1'b0), // 低电平有效
      .WEN (~icache_wen_i),
      .BWEN(~icache_wmask),
      .A   ({1'b0,icache_index_i}),
      .D   (icache_line_wdata_i)
  );


endmodule
