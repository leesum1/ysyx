`include "sysconfig.v"

// 写入一个周期
// 读取立即返回
module dcache_tag #(
    TAG_LEN = 20,  // tag 长度
    IDX_LEN = 6,   // 组号 长度
    TAG_NUM = 64   // tag 个数
) (
    input                clk,
    input                rst,
    input  [TAG_LEN-1:0] dcache_tag_i,       // tag
    input  [IDX_LEN-1:0] dcache_index_i,     // index
    input                dirty_bit_write_i,  //
    output               dirty_bit_read_o,   //
    output [TAG_LEN-1:0] dcache_tag_o,       // 当前的 tag
    input                write_valid_i,      // 写使能
    output               dcache_hit_o
);

  reg [TAG_LEN-1+1:0] dcache_tag_regs[TAG_NUM-1:0];  // 最高位为脏位

  wire [TAG_LEN-1:0] read_tag;
  wire read_dirty_bit;
  assign {read_dirty_bit, read_tag} = dcache_tag_regs[dcache_index_i];

  wire _dcache_hit = (dcache_tag_i == read_tag);  // hit
  wire _dirty_bit_read = read_dirty_bit;

  assign dcache_hit_o = _dcache_hit;
  assign dcache_tag_o = read_tag;
  assign dirty_bit_read_o = _dirty_bit_read;


  /* 写入逻辑，一个周期写入 */
  integer i;
  always @(posedge clk) begin
    if (rst) begin
      for (i = 0; i < TAG_NUM; i = i + 1) begin
        dcache_tag_regs[i] <= 'b0;
      end
    end else if (write_valid_i) begin
      dcache_tag_regs[dcache_index_i] <= {dirty_bit_write_i, dcache_tag_i};
    end
  end
  //else 保持不变
endmodule
