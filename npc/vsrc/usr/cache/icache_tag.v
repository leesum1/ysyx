`include "sysconfig.v"

module icache_tag #(
    TAG_LEN = 23,  // tag 长度
    IDX_LEN = 5,   // 组号 长度
    TAG_NUM = 32   // tag 个数
) (
    input clk,
    input rst,
    input [TAG_LEN-1:0] icache_tag_i,  // tag
    input [IDX_LEN-1:0] icache_index_i,  // index
    input write_valid_i,  // 写使能
    output icache_hit_o
);
  reg [TAG_LEN-1:0] icache_tag_regs[TAG_NUM-1:0];

  wire _icache_hit = (icache_tag_i == icache_tag_regs[icache_index_i]);  // hit


  assign icache_hit_o = _icache_hit;


  /* 写入逻辑，一个周期写入 */
  integer i;
  always @(posedge clk) begin
    if (rst) begin
      for (i = 0; i < TAG_NUM; i = i + 1) begin
        icache_tag_regs[i] <= 'b0;
      end
    end else if (write_valid_i) begin
      icache_tag_regs[icache_index_i] <= icache_tag_i;
    end
  end
  //else 保持不变
endmodule
