`include "sysconfig.v"

module dcache_tag #(
    TAG_LEN = 23,  // tag 长度
    IDX_LEN = 5,   // 组号 长度
    TAG_NUM = 32   // tag 个数
) (
    input clk,
    input rst,
    input [TAG_LEN-1:0] dcache_tag_i,  // tag
    input [IDX_LEN-1:0] dcache_index_i,  // index
    input write_valid_i,  // 写使能
    output dcache_hit_o
);
  reg [TAG_LEN-1:0] dcache_tag_regs[TAG_NUM-1:0];

  wire _dcache_hit = (dcache_tag_i == dcache_tag_regs[dcache_index_i]);  // hit


  assign dcache_hit_o = _dcache_hit;


  /* 写入逻辑，一个周期写入 */
  integer i;
  always @(posedge clk) begin
    if (rst) begin
      for (i = 0; i < TAG_NUM; i = i + 1) begin
        dcache_tag_regs[i] <= 'b0;
      end
    end else if (write_valid_i) begin
      dcache_tag_regs[dcache_index_i] <= dcache_tag_i;
    end
  end
  //else 保持不变
endmodule
