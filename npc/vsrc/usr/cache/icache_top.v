`include "sysconfig.v"
// 地址位宽 32,icache<->cpu (数据64位) mem<-->icache(数据128位)
// 连接方式 ram<-->cache<-->cpu
// cache<-->cpu : 地址线宽度:32 数据线宽度:64
// ram<-->cache: 地址线宽度:6  数据线宽度:128 (2^6 * 128bit == 8Kbit,地址线最高位为0,只用 4Kbit)
// 1. cache 总容量: 4Kb (512Byte)
// 2. cahce 块大小: 16Byte
// 3. cache 块个数: 32个 (32*16Byte==512Byte)
// 4. 映射方式 直接映射
// 5. 块内地址: 4bit(2^4==16)
// 6. 组号: 5bit（2^5==32）
// 6. tag: 32-4-5 == 23 bit 



module icache_top (
    input clk,
    input rst,
    /* cpu<-->cache 端口 */
    input [`NPC_ADDR_BUS] if_raddr_i,  // CPU 的访存信息 
    input [7:0] if_rmask_i,  // 访存掩码
    input if_raddr_valid_i,  // 地址是否有效，无效时，停止访问 cache
    output [`XLEN_BUS] icahce_data_o,  // icache 返回读数据
    output icache_ready_o,  // icache 读数据是否准备好(未准备好需要暂停流水线)
    /* cache<-->mem 端口 */
    output [`NPC_ADDR_BUS] ram_raddr_icache_o,
    output ram_raddr_valid_icache_o,
    output [7:0] ram_rmask_icache_o,
    input ram_rdata_ready_icache_i,
    input [`XLEN_BUS] ram_rdata_icache_i
);

  // 块内地址
  wire [3:0] cache_blk_addr = if_raddr_i[3:0];
  // 组号
  wire [8:4] cache_line_idx = if_raddr_i[8:4];
  // TAG 标记 
  wire [31:9] cache_line_tag = if_raddr_i[31:9];


  // cache line 寄存器组 128bit * 32
  reg [128-1:0] cache_line_regs[32-1:0];
  // cache line 的 tag 数组，与 cache line 一一对应
  reg [23-1:0] cache_tag_regs[32-1:0];



  wire cache_hit = (cache_line_tag == cache_tag_regs[cache_line_idx]);
  wire cache_miss = !cache_hit;

  // always @(posedge clk) begin
  //   if (rst) begin
  //     cache_hit <= `FALSE;
  //   end else if (cache_line_tag == cache_tag_regs[cache_line_idx]) begin
  //     cache_hit <= `TRUE;
  //   end
  // end




  /* cache 命中 */
  localparam CACHE_HIT_RST = 4'd0;
  localparam CACHE_HIT_IDLE = 4'd1;
  localparam CACHE_HIT_MEM1 = 4'd2;
  localparam CACHE_HIT_MEM2 = 4'd3;
  localparam CACHE_HIT_MEM3 = 4'd4;

  reg [3:0] hit_state;
  reg icache_ready;
  reg [`XLEN_BUS] icache_data;
  reg [`NPC_ADDR_BUS] icahce_raddr;  // 缓存地址

  // reg [3:0] hit_cache_blk_addr;
  // reg [8:4] hit_cache_line_idx;
  // reg [31:9] hit_cache_line_tag;


  always @(posedge clk) begin
    if (rst) begin
      hit_state <= CACHE_HIT_RST;
      icache_data <= `XLEN'b0;
      icache_ready <= `FALSE;
      icahce_raddr <= 32'b0;
    end else begin
      case (hit_state)
        CACHE_HIT_RST: begin
          hit_state <= CACHE_HIT_IDLE;
        end
        CACHE_HIT_IDLE: begin
          if (if_raddr_valid_i & cache_hit) begin
            hit_state <= CACHE_HIT_MEM1;
            icache_ready <= `FALSE;
            icahce_raddr <= if_raddr_i;
            // cache line 位于 同步 ram中
            // 发出读地址,在下一个周期获取到 cache line 数据
          end else begin
            hit_state <= CACHE_HIT_IDLE;
            icahce_raddr <= 32'b0;
            icache_ready <= `FALSE;
          end
        end
        // 获取到 cache line 数据
        CACHE_HIT_MEM1: begin
          if (if_raddr_valid_i & cache_hit && icahce_raddr == if_raddr_i) begin
            //if (if_raddr_valid_i & cache_hit) begin
            hit_state <= CACHE_HIT_IDLE;
            icache_ready <= `TRUE;
            icache_data <= {32'b0, cache_line_regs[icahce_raddr[8:4]][icahce_raddr[3:0]*8+:32]};
          end else begin
            icache_ready <= `FALSE;
            icache_data <= `XLEN'b0;
            hit_state <= CACHE_HIT_IDLE;
          end
        end
        default: begin
        end
      endcase
    end
  end

  assign icache_ready_o = icache_ready;
  assign icahce_data_o  = icache_data;



  // always @(posedge clk) begin
  //   if (rst) begin
  //     _cache_ready_o <= `FALSE;
  //     _cache_data_o  <= `XLEN'b0;
  //   end else begin
  //     if (if_raddr_valid_i & cache_hit & ~_cache_ready_o) begin
  //       // 一条指令 4byte
  //       _cache_data_o  <= {32'b0, cache_line_regs[cache_line_idx][cache_blk_addr*8+:32]};
  //       _cache_ready_o <= `TRUE;
  //     end else begin
  //       _cache_ready_o <= `FALSE;
  //       _cache_data_o  <= `XLEN'b0;
  //     end
  //   end
  // end

  // assign icahce_data_o  = _cache_data_o;
  // assign icache_ready_o = _cache_ready_o;


  /* cache 未命中 */
  localparam CACHE_MISS_RST = 4'd0;
  localparam CACHE_MISS_IDLE = 4'd1;
  localparam CACHE_MISS_MEM1 = 4'd2;
  localparam CACHE_MISS_MEM2 = 4'd3;
  localparam CACHE_MISS_MEM3 = 4'd4;

  reg [3:0] miss_state;

  // cache<-->mem 端口 
  reg [`NPC_ADDR_BUS] _ram_raddr_icache_o;
  reg _ram_raddr_valid_icache_o;
  reg [7:0] _ram_rmask_icache_o;
  // reg ram_rdata_ready_icache_i,
  // reg ram_rdata_valid_icache_i
  reg [127:0] _cache_line_temp;
  // cache line 在 mem 中的基地址
  wire [`NPC_ADDR_BUS] _cache_line_base_addr = {if_raddr_i[31:4], 4'b0};
  wire [`NPC_ADDR_BUS] _cache_line_base_addr_p8 = {if_raddr_i[31:4], 4'd8};


  always @(posedge clk) begin
    if (rst) begin
      _ram_raddr_valid_icache_o <= `FALSE;
      _ram_raddr_icache_o <= 32'b0;
      _ram_rmask_icache_o <= 8'b0;
      _cache_line_temp <= 128'b0;
      miss_state <= CACHE_MISS_RST;
    end else begin
      // cache miss

      case (miss_state)
        // 复位状态
        CACHE_MISS_RST: begin
          miss_state <= CACHE_MISS_IDLE;
        end
        // 等待 cache miss
        CACHE_MISS_IDLE: begin
          _cache_line_temp <= 128'b0;
          if (cache_miss & if_raddr_valid_i) begin
            _ram_raddr_icache_o <= _cache_line_base_addr;  // 读地址
            _ram_raddr_valid_icache_o <= `TRUE;  // 地址有效
            _ram_rmask_icache_o <= 8'b1111_1111;  // 读掩码
            miss_state <= CACHE_MISS_MEM1;
          end else begin
            _ram_raddr_icache_o <= 32'b0;
            _ram_raddr_valid_icache_o <= `FALSE;  // 地址无效
            _ram_rmask_icache_o <= 8'b0;
            miss_state <= CACHE_MISS_IDLE;
          end
        end
        // 第一次读 mem 64bit
        CACHE_MISS_MEM1: begin
          if (cache_miss & if_raddr_valid_i) begin
            // mem 读数据准备好
            if (_ram_raddr_valid_icache_o & ram_rdata_ready_icache_i) begin
              _cache_line_temp[63:0] <= ram_rdata_icache_i;  // 临时保存 cache line 部分数据

              _ram_raddr_icache_o <= _cache_line_base_addr_p8;  // 读地址
              _ram_raddr_valid_icache_o <= `TRUE;  // 地址有效
              _ram_rmask_icache_o <= 8'b1111_1111;  // 读掩码
              miss_state <= CACHE_MISS_MEM2;
            end
          end else begin
            _ram_raddr_icache_o <= 32'b0;
            _ram_raddr_valid_icache_o <= `FALSE;  // 地址无效
            _ram_rmask_icache_o <= 8'b0;
            miss_state <= CACHE_MISS_IDLE;
          end
        end
        CACHE_MISS_MEM2: begin
          if (cache_miss & if_raddr_valid_i) begin
            // mem 读数据准备好
            if (_ram_raddr_valid_icache_o & ram_rdata_ready_icache_i) begin
              _cache_line_temp[127:64] <= ram_rdata_icache_i;  // 临时保存 cache line 部分数据
              cache_tag_regs[cache_line_idx] <= cache_line_tag;  // 记录 cache tag
              cache_line_regs[cache_line_idx] <= {
                ram_rdata_icache_i, _cache_line_temp[63:0]
              };  // 写入 cache line 中

              // 返回 IDLE 状态
              _ram_raddr_icache_o <= 32'b0;
              _ram_raddr_valid_icache_o <= `FALSE;  // 地址无效
              _ram_rmask_icache_o <= 8'b0;
              miss_state <= CACHE_MISS_IDLE;
            end
          end else begin
            // 返回 IDLE 状态
            _ram_raddr_icache_o <= 32'b0;
            _ram_raddr_valid_icache_o <= `FALSE;  // 地址无效
            _ram_rmask_icache_o <= 8'b0;
            miss_state <= CACHE_MISS_IDLE;
          end
        end
        default: begin
        end
      endcase
    end
  end

  assign ram_raddr_icache_o = _ram_raddr_icache_o;
  assign ram_raddr_valid_icache_o = _ram_raddr_valid_icache_o;
  assign ram_rmask_icache_o = _ram_rmask_icache_o;

endmodule
