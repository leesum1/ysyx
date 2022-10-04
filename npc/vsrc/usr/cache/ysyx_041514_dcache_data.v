`include "sysconfig.v"


module ysyx_041514_dcache_data #(
    IDX_LEN = 6,  // 组号 长度
    BLK_LEN = 6,  // 块内地址 长度
    TAG_NUM = 64  // tag 个数
) (
    input clk,
    input rst,
    input [IDX_LEN-1:0] dcache_index_i,  // index
    input [BLK_LEN-1:0] dcache_blk_addr_i,
    input [128-1:0] dcache_line_wdata_i,
    input  [128-1:0] dcache_wmask,
    input [2:0] burst_count_i,
    input dcache_allocate_valid_i,
    input dcache_writeback_valid_i,
    input dcache_wen_i,
    output [`ysyx_041514_XLEN_BUS] dcache_writeback_data_o,
    output [`ysyx_041514_XLEN_BUS]    dcache_rdata_o

);

  reg [`ysyx_041514_XLEN_BUS] dcache_wb_data;
  assign dcache_writeback_data_o = dcache_wb_data;
  always @(*) begin
    case (burst_count_i)
      3'd0: dcache_wb_data = Q00[63:0];
      3'd1: dcache_wb_data = Q00[127:64];
      3'd2: dcache_wb_data = Q01[63:0];
      3'd3: dcache_wb_data = Q01[127:64];
      3'd4: dcache_wb_data = Q10[63:0];
      3'd5: dcache_wb_data = Q10[127:64];
      3'd6: dcache_wb_data = Q11[63:0];
      3'd7: dcache_wb_data = Q11[127:64];
    endcase
  end


  // allocate 分配 cache line 时候片选 高点平有效
  wire allocate_CEN00 = (burst_count_i[2:1] == 2'b00 && dcache_allocate_valid_i);
  wire allocate_CEN01 = (burst_count_i[2:1] == 2'b01 && dcache_allocate_valid_i);
  wire allocate_CEN10 = (burst_count_i[2:1] == 2'b10 && dcache_allocate_valid_i);
  wire allocate_CEN11 = (burst_count_i[2:1] == 2'b11 && dcache_allocate_valid_i);


  // hit 时候 的片选 高点平有效
  wire hit_CEN00 = (dcache_blk_addr_i[5:4] == 2'b00 && ~dcache_allocate_valid_i && ~dcache_writeback_valid_i);
  wire hit_CEN01 = (dcache_blk_addr_i[5:4] == 2'b01 && ~dcache_allocate_valid_i&& ~dcache_writeback_valid_i);
  wire hit_CEN10 = (dcache_blk_addr_i[5:4] == 2'b10 && ~dcache_allocate_valid_i&& ~dcache_writeback_valid_i);
  wire hit_CEN11 = (dcache_blk_addr_i[5:4] == 2'b11 && ~dcache_allocate_valid_i&& ~dcache_writeback_valid_i);


  // 写信号 低电平有效
  wire WEN00 = ~((allocate_CEN00 | hit_CEN00) & dcache_wen_i);
  wire WEN01 = ~((allocate_CEN01 | hit_CEN01) & dcache_wen_i);
  wire WEN10 = ~((allocate_CEN10 | hit_CEN10) & dcache_wen_i);
  wire WEN11 = ~((allocate_CEN11 | hit_CEN11) & dcache_wen_i);




  wire [127:0] Q00, Q01, Q10, Q11;  // 读数据

  wire [127:0] BWEN = ~dcache_wmask;  // 写掩码
  wire [5:0] A = dcache_index_i;  // 写地址
  wire [127:0] D = dcache_line_wdata_i;  // 写数据




  wire [127:0] dcache_ram_data = ({128{hit_CEN00}}&Q00)
                                 | ({128{hit_CEN01}}&Q01)
                                 | ({128{hit_CEN10}}&Q10)
                                 | ({128{hit_CEN11}}&Q11);

  wire [`ysyx_041514_XLEN_BUS] _dcache_rdata_o = {dcache_ram_data[dcache_blk_addr_i[3:0]*8+:64]};
  assign dcache_rdata_o = _dcache_rdata_o;

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


  //   S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW (
  //       .Q   (dcache_line_rdata_o),
  //       .CLK (clk),
  //       .CEN (1'b0), // 低电平有效
  //       .WEN (~dcache_wen_i),
  //       .BWEN(~dcache_wmask),
  //       .A   ({1'b0,dcache_index_i}),
  //       .D   (dcache_line_wdata_i)
  //   );

endmodule
