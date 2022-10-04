`include "sysconfig.v"


module ysyx_041514_icache_data #(
    IDX_LEN = 6,  // 组号 长度
    BLK_LEN = 6,  // 块内地址 长度
    TAG_NUM = 64  // tag 个数
) (
    input clk,
    input rst,
    input [IDX_LEN-1:0] icache_index_i,  // index
    input [BLK_LEN-1:0] icache_blk_addr_i,
    input [128-1:0] icache_line_wdata_i,
    input  [128-1:0] icache_wmask,
    input [2:0] burst_count_i,
    input icache_wen_i,
    output [`ysyx_041514_XLEN_BUS]    icache_rdata_o
);


  wire WEN00 = ~(burst_count_i[2:1] == 2'b00 && icache_wen_i);  // 片选信号，低电平有效
  wire WEN01 = ~(burst_count_i[2:1] == 2'b01 && icache_wen_i);
  wire WEN10 = ~(burst_count_i[2:1] == 2'b10 && icache_wen_i);
  wire WEN11 = ~(burst_count_i[2:1] == 2'b11 && icache_wen_i);


  wire CEN00 = ~(icache_blk_addr_i[5:4] == 2'b00);
  wire CEN01 = ~(icache_blk_addr_i[5:4] == 2'b01);
  wire CEN10 = ~(icache_blk_addr_i[5:4] == 2'b10);
  wire CEN11 = ~(icache_blk_addr_i[5:4] == 2'b11);

  wire [127:0] Q00, Q01, Q10, Q11;  // 读数据

  wire [127:0] BWEN = ~icache_wmask;  // 写掩码
  wire [5:0] A = icache_index_i;
  wire [127:0] D = icache_line_wdata_i;

  wire [127:0] icache_ram_data = ({128{~CEN00}}&Q00)
                                 | ({128{~CEN01}}&Q01)
                                 | ({128{~CEN10}}&Q10)
                                 | ({128{~CEN11}}&Q11);


  wire [`ysyx_041514_XLEN_BUS] _icache_rdata_o = {32'b0, icache_ram_data[icache_blk_addr_i[3:0]*8+:32]};
  assign icache_rdata_o = _icache_rdata_o;

  S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW00 (
      .Q   (Q00),
      .CLK (clk),
      .CEN (1'b0), // 低电平有效
      .WEN (WEN00),
      .BWEN(BWEN),
      .A   (A),
      .D   (D)
  );
  S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW01 (
      .Q   (Q01),
      .CLK (clk),
      .CEN (1'b0), // 低电平有效
      .WEN (WEN01),
      .BWEN(BWEN),
      .A   (A),
      .D   (D)
  );
  S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW10 (
      .Q   (Q10),
      .CLK (clk),
      .CEN (1'b0), // 低电平有效
      .WEN (WEN10),
      .BWEN(BWEN),
      .A   (A),
      .D   (D)
  );
  S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW11 (
      .Q   (Q11),
      .CLK (clk),
      .CEN (1'b0), // 低电平有效
      .WEN (WEN11),
      .BWEN(BWEN),
      .A   (A),
      .D   (D)
  );


endmodule
