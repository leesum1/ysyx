`include "sysconfig.v"

// 写入一个周期
// 读取立即返回
module ysyx_041514_icache_tag #(
    TAG_LEN = 20,  // tag 长度
    IDX_LEN = 6,   // 组号 长度
    TAG_NUM = 64   // tag 个数
) (
    input clk,
    input rst,
    input [TAG_LEN-1:0] icache_tag_i,  // tag
    input [IDX_LEN-1:0] icache_index_i,  // index
    input write_valid_i,  // 写使能
    input fencei_valid_i,
    output icache_hit_o
);
  reg [TAG_LEN-1+1:0] icache_tag_regs[TAG_NUM-1:0];  //{valid,tag}


  wire _fencei_valid = fencei_valid_i;
  wire valid_bit;
  wire [TAG_LEN-1:0] tag_read;
  assign {valid_bit, tag_read} = icache_tag_regs[icache_index_i];

  wire _icache_hit = (icache_tag_i == tag_read) & valid_bit;  // hit


  assign icache_hit_o = _icache_hit;


  /* 写入逻辑，一个周期写入 tag */
  integer i;
  always @(posedge clk) begin
    if (rst) begin
      for (i = 0; i < TAG_NUM; i = i + 1) begin
        icache_tag_regs[i][19:0] <= 'b0;
      end
    end else if (write_valid_i) begin
      icache_tag_regs[icache_index_i][19:0] <= icache_tag_i;
    end
  end


  /* valid */
  integer j;
  always @(posedge clk) begin
    if (rst | _fencei_valid) begin
      for (j = 0; j < TAG_NUM; j = j + 1) begin
        icache_tag_regs[j][20] <= 'b0;
      end
    end else if (write_valid_i) begin
      icache_tag_regs[icache_index_i][20] <= 1'b1;
    end
  end

  //else 保持不变
endmodule
