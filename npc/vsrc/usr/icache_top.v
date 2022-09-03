`include "sysconfig.v"
// 地址位宽 32,icache<->cpu (数据64位) mem<-->icache(数据128位)
// 连接方式 ram<-->cache<-->cpu
// cache<-->cpu : 地址线宽度:32 数据线宽度:64
// ram<-->cache: 地址线宽度:6  数据线宽度:128 (2^6 * 128bit == 8Kbit,地址线最高位为0,只用 4Kbit)
// 1. cache 总容量: 4Kb (512Byte)
// 2. cahce 块大小: 128Byte
// 3. cache 块个数: 4个 (4*128Byte==512Byte)
// 4. 映射方式 全相连映射
// 5. 块内地址: 7bit(2^7==128)
// 6. tag: 32-7 == 25 bit 
// 7. 有效位: 1bit 脏位: 1bit
// 8. 替换算法: LRU ( 2bit 标记位)

`define CACHE_BLK_MSB 6
`define CACHE_BLK_LSB 0
`define CACHE_TAG_MSB 31
`define CACHE_TAG_LSB 7
`define CACHE_TAG_BIT 25

`define CACHE_LINE_TAG_BUS `CACHE_TAG_BIT-1:0
`define CACHE_LINE_LRU_BUS 26:25
`define CACHE_LINE_DITY_BUS 27
`define CACHE_LINE_VALID_BUS 28


module icache_top (
    input clk,
    input rst,
    input [`NPC_ADDR_BUS] npc_addr_i,  // CPU 的访存信息 
    input [7:0] npc_rmask,  // 访存掩码,为 0 时表示不访存
    output [`XLEN_BUS] icahce_data_o,  // icache 返回读数据
    output icache_ready  // icache 读数据是否准备好(未准备好需要暂停流水线)
);
  // data mask
  wire _1byte_valid = (npc_rmask == 8'b0000_0001);
  wire _2byte_valid = (npc_rmask == 8'b0000_0011);
  wire _4byte_valid = (npc_rmask == 8'b0000_1111);
  wire _8byte_valid = (npc_rmask == 8'b1111_1111);
  wire _read_valid = _1byte_valid | _2byte_valid | _4byte_valid | _8byte_valid;

  // 块内地址
  wire [`CACHE_BLK_MSB:`CACHE_BLK_LSB] _block_addr = npc_addr_i[`CACHE_BLK_MSB:`CACHE_BLK_LSB];
  // TAG 标记
  wire [`CACHE_TAG_MSB:`CACHE_TAG_LSB] _block_tag = npc_addr_i[`CACHE_TAG_MSB:`CACHE_TAG_LSB];
  // 如果 cache miss，需要读取的内存地址
  wire [`NPC_ADDR_BUS] _mem_addr = {_block_tag, 7'b0};

  // tag 与每一个 cache line 比较
  wire _cache_line_0_hit = (_block_tag == _cache_line_0_tagarr_q[`CACHE_LINE_TAG_BUS])&_cache_line_0_tagarr_q[`CACHE_LINE_VALID_BUS];
  wire _cache_line_1_hit = (_block_tag == _cache_line_1_tagarr_q[`CACHE_LINE_TAG_BUS])&_cache_line_1_tagarr_q[`CACHE_LINE_VALID_BUS];
  wire _cache_line_2_hit = (_block_tag == _cache_line_2_tagarr_q[`CACHE_LINE_TAG_BUS])&_cache_line_2_tagarr_q[`CACHE_LINE_VALID_BUS];
  wire _cache_line_3_hit = (_block_tag == _cache_line_3_tagarr_q[`CACHE_LINE_TAG_BUS])&_cache_line_3_tagarr_q[`CACHE_LINE_VALID_BUS];
  // cache 是否命中
  wire _cache_hit = (_cache_line_0_hit | _cache_line_1_hit | _cache_line_2_hit | _cache_line_3_hit);
  wire _cache_miss = !_cache_hit;
  // cache line 是否已满
  wire cache_line_full = _cache_line_0_tagarr_q[`CACHE_LINE_VALID_BUS]&
                         _cache_line_1_tagarr_q[`CACHE_LINE_VALID_BUS]&
                         _cache_line_2_tagarr_q[`CACHE_LINE_VALID_BUS]&
                         _cache_line_3_tagarr_q[`CACHE_LINE_VALID_BUS];





  /****************** cache tagarr 寄存器 ************************/

  wire [29-1:0] _cache_line_0_tagarr_d;
  reg [29-1:0] _cache_line_0_tagarr_q;

  regTemplate #(
      .WIDTH    (29),
      .RESET_VAL(29'b0)
  ) u_cache_line_0 (
      .clk (clk),
      .rst (rst),
      .din (_cache_line_0_tagarr_d),
      .dout(_cache_line_0_tagarr_q),
      .wen (1'b1)
  );

  wire [29-1:0] _cache_line_1_tagarr_d;
  reg  [29-1:0] _cache_line_1_tagarr_q;

  regTemplate #(
      .WIDTH    (29),
      .RESET_VAL(29'b0)
  ) u_cache_line_1 (
      .clk (clk),
      .rst (rst),
      .din (_cache_line_1_tagarr_d),
      .dout(_cache_line_1_tagarr_q),
      .wen (1'b1)
  );


  wire [29-1:0] _cache_line_2_tagarr_d;
  reg  [29-1:0] _cache_line_2_tagarr_q;

  regTemplate #(
      .WIDTH    (29),
      .RESET_VAL(29'b0)
  ) u_cache_line_2 (
      .clk (clk),
      .rst (rst),
      .din (_cache_line_2_tagarr_d),
      .dout(_cache_line_2_tagarr_q),
      .wen (1'b1)
  );

  wire [29-1:0] _cache_line_3_tagarr_d;
  reg  [29-1:0] _cache_line_3_tagarr_q;
  regTemplate #(
      .WIDTH    (29),
      .RESET_VAL(29'b0)
  ) u_cache_line_3 (
      .clk (clk),
      .rst (rst),
      .din (_cache_line_3_tagarr_d),
      .dout(_cache_line_3_tagarr_q),
      .wen (1'b1)
  );











endmodule
