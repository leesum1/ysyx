`include "sysconfig.v"


module dcache_data #(
    IDX_LEN = 5,  // 组号 长度
    BLK_LEN = 4,  // 块内地址 长度
    TAG_NUM = 32  // tag 个数
) (
    input clk,
    input rst,
    input [IDX_LEN-1:0] dcache_index_i,  // index
    input [BLK_LEN-1:0] dcache_blk_addr_i,
    input [128-1:0] dcache_line_wdata_i,
    input  [128-1:0] dcache_wmask,
    input dcache_wen_i,
    output [128-1:0]    dcache_line_rdata_o
);


  S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW (
      .Q   (dcache_line_rdata_o),
      .CLK (clk),
      .CEN (1'b0), // 低电平有效
      .WEN (~dcache_wen_i),
      .BWEN(~dcache_wmask),
      .A   ({1'b0,dcache_index_i}),
      .D   (dcache_line_wdata_i)
  );

endmodule
