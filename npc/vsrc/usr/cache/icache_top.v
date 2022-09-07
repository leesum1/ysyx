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
    input [`NPC_ADDR_BUS] preif_raddr_i,  // CPU 的访存信息 
    input [7:0] preif_rmask_i,  // 访存掩码
    input preif_raddr_valid_i,  // 地址是否有效，无效时，停止访问 cache
    output preif_raddr_ready_o,  // 成功接收地址时为 1
    output [`XLEN_BUS] if_rdata_o,  // icache 返回读数据

    //input  if_rdata_ready_i,  // 是否准备好接收数据
    output if_rdata_valid_o,  // icache 读数据是否准备好(未准备好需要暂停流水线)

    /* cache<-->mem 端口 */
    output [`NPC_ADDR_BUS] ram_raddr_icache_o,
    output ram_raddr_valid_icache_o,
    output [7:0] ram_rmask_icache_o,
    input ram_rdata_ready_icache_i,
    input [`XLEN_BUS] ram_rdata_icache_i
);

  // 块内地址
  wire [3:0] cache_blk_addr = preif_raddr_i[3:0];
  // 组号
  wire [8:4] cache_line_idx = preif_raddr_i[8:4];
  // TAG 标记 
  wire [31:9] cache_line_tag = preif_raddr_i[31:9];
  // cache line 寄存器组 128bit * 32
  reg [128-1:0] cache_line_regs[32-1:0];
  // cache line 的 tag 数组，与 cache line 一一对应
  reg [23-1:0] cache_tag_regs[32-1:0];


  wire cache_hit = (cache_line_tag == cache_tag_regs[cache_line_idx]);


  /* cache 命中 */
  localparam CACHE_RST = 4'd0;
  localparam CACHE_IDLE = 4'd1;
  localparam CACHE_HIT = 4'd2;
  localparam CACHE_MISS = 4'd3;
  localparam CACHE_MISS2 = 4'd4;

  reg [3:0] icahce_state;

  reg icache_ready;
  reg [`XLEN_BUS] icache_data;
  reg [`NPC_ADDR_BUS] icahce_raddr;  // 缓存地址
  reg [3:0] blk_addr_reg;
  reg [4:0] line_idx_reg;
  reg [22:0] line_tag_reg;

  reg icache_addr_ok;
  reg icahce_rdata_ok;
  // cache<-->mem 端口 
  reg [`NPC_ADDR_BUS] _ram_raddr_icache_o;
  reg _ram_raddr_valid_icache_o;
  reg [7:0] _ram_rmask_icache_o;

  reg [63:0] _cache_line_temp;

  reg busy;



  always @(posedge clk) begin
    if (rst) begin
      icahce_state   <= CACHE_RST;
      icache_addr_ok <= `FALSE;
      blk_addr_reg   <= 0;
      line_idx_reg   <= 0;
      line_tag_reg   <= 0;
      busy <=0;
    end else begin
      case (icahce_state)
        CACHE_RST: begin
          icahce_state   <= CACHE_IDLE;
          icache_addr_ok <= `FALSE;
        end
        CACHE_IDLE: begin
          blk_addr_reg <= cache_blk_addr;
          line_idx_reg <= cache_line_idx;
          line_tag_reg <= cache_line_tag;

          if (preif_raddr_valid_i&(~busy)) begin
            // hit
            if (cache_hit) begin
              // 下一个周期给数据
              icache_data <= {32'b0, cache_line_regs[cache_line_idx][cache_blk_addr*8+:32]};
              icahce_rdata_ok <= `TRUE;
              icahce_state <= CACHE_IDLE;
              busy<=1'b0;
            end else begin  // miss 
              icahce_state <= CACHE_MISS;
              icahce_rdata_ok <= `FALSE;
              _ram_raddr_icache_o <= {cache_line_tag, cache_line_idx, 4'b0};  // 读地址
              _ram_raddr_valid_icache_o <= `TRUE;  // 地址有效
              _ram_rmask_icache_o <= 8'b1111_1111;  // 读掩码
              busy<=1'b1;
            end
          end else begin
            icahce_rdata_ok <= `FALSE;
            _ram_raddr_valid_icache_o <= `FALSE;
          end
        end
        CACHE_MISS: begin
          if (_ram_raddr_valid_icache_o & ram_rdata_ready_icache_i) begin
            _cache_line_temp[63:0] <= ram_rdata_icache_i;  // 临时保存 cache line 部分数据
            _ram_raddr_icache_o <= {line_tag_reg, line_idx_reg, 4'd8};  // 读地址
            icahce_state <= CACHE_MISS2;
          end
        end
        CACHE_MISS2: begin
          if (_ram_raddr_valid_icache_o & ram_rdata_ready_icache_i) begin
            cache_tag_regs[cache_line_idx] <= cache_line_tag;  // 记录 cache tag
            cache_line_regs[cache_line_idx] <= {
              ram_rdata_icache_i, _cache_line_temp[63:0]
            };  // 写入 cache line 中

            _ram_raddr_valid_icache_o <= `FALSE;
            icache_data[31:0] <= {ram_rdata_icache_i, _cache_line_temp[63:0]}[blk_addr_reg*8+:32];
            icahce_rdata_ok <= `TRUE;
            icahce_state <= CACHE_IDLE;
            busy<=1'b0;
          end
        end
        default: begin
        end
      endcase
    end
  end

  assign preif_raddr_ready_o = (icahce_state == CACHE_IDLE) && preif_raddr_valid_i;
  assign if_rdata_o = icache_data;
  assign if_rdata_valid_o = icahce_rdata_ok && (icahce_state == CACHE_IDLE);
  // output [`NPC_ADDR_BUS] ram_raddr_icache_o,
  // output ram_raddr_valid_icache_o,
  // output [7:0] ram_rmask_icache_o,
  assign ram_raddr_icache_o = _ram_raddr_icache_o;
  assign ram_raddr_valid_icache_o = _ram_raddr_valid_icache_o;
  assign ram_rmask_icache_o = _ram_rmask_icache_o;
endmodule
