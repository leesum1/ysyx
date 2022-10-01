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
    output [`XLEN_BUS] if_rdata_o,  // icache 返回读数据

    //input  if_rdata_ready_i,  // 是否准备好接收数据
    output if_rdata_valid_o,  // icache 读数据是否准备好(未准备好需要暂停流水线)

    /* cache<-->mem 端口 */
    output [`NPC_ADDR_BUS] ram_raddr_icache_o,
    output ram_raddr_valid_icache_o,
    output [7:0] ram_rmask_icache_o,
    output [3:0] ram_rsize_icache_o,
    output [7:0] ram_rlen_icache_o,
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
  // reg [128-1:0] cache_line_regs[32-1:0];
  // // cache line 的 tag 数组，与 cache line 一一对应
  // reg [23-1:0] cache_tag_regs[32-1:0];


  //wire cache_hit = (cache_line_tag == cache_tag_regs[cache_line_idx]);
  wire icache_hit;

  /* cache 命中 */
  localparam CACHE_RST = 4'd0;
  localparam CACHE_IDLE = 4'd1;
  localparam CACHE_HIT = 4'd2;
  localparam CACHE_MISS = 4'd3;
  localparam CACHE_MISS2 = 4'd4;

  reg [3:0] icahce_state;


  reg [3:0] blk_addr_reg;
  reg [4:0] line_idx_reg;
  reg [22:0] line_tag_reg;
  reg icache_tag_wen;


  reg icahce_rdata_ok;
  // cache<-->mem 端口 
  reg [`NPC_ADDR_BUS] _ram_raddr_icache_o;
  reg _ram_raddr_valid_icache_o;
  reg [7:0] _ram_rmask_icache_o;
  reg [3:0] _ram_rsize_icache_o;
  reg [7:0] _ram_rlen_icache_o;
  reg [7:0] burst_count;

  reg [127:0] cache_line_temp;
  reg icache_data_wen;


  wire ram_r_handshake = _ram_raddr_valid_icache_o & ram_rdata_ready_icache_i;
  wire [7:0] burst_count_plus1 = burst_count + 1;

  always @(posedge clk) begin
    if (rst) begin
      icahce_state        <= CACHE_RST;
      blk_addr_reg        <= 0;
      line_idx_reg        <= 0;
      line_tag_reg        <= 0;
      icache_tag_wen      <= 0;
      icache_data_wen     <= 0;
      cache_line_temp     <= 0;
      _ram_rsize_icache_o <= 0;
      _ram_rlen_icache_o  <= 0;
      burst_count         <= 0;
    end else begin
      case (icahce_state)
        CACHE_RST: begin
          icahce_state <= CACHE_IDLE;
        end
        CACHE_IDLE: begin
          blk_addr_reg <= cache_blk_addr;
          line_idx_reg <= cache_line_idx;
          line_tag_reg <= cache_line_tag;
          icache_tag_wen <= `FALSE;
          icache_data_wen <= 0;
          cache_line_temp <= 0;
          // cache data 为单端口 ram,不能同时读写
          if (preif_raddr_valid_i && ~icache_tag_wen) begin
            // hit
            if (icache_hit) begin
              // 下一个周期给数据
              //icache_data <= {32'b0, cache_line_regs[cache_line_idx][cache_blk_addr*8+:32]};
              icahce_rdata_ok <= `TRUE;
              icahce_state <= CACHE_IDLE;
            end else begin  // miss 
              icahce_state <= CACHE_MISS;
              icahce_rdata_ok <= `FALSE;
              _ram_raddr_icache_o <= {cache_line_tag, cache_line_idx, 4'b0};  // 读地址
              _ram_raddr_valid_icache_o <= `TRUE;  // 地址有效
              _ram_rmask_icache_o <= 8'b1111_1111;  // 读掩码
              _ram_rsize_icache_o <= 4'b1000;  // 64bit
              _ram_rlen_icache_o <= 8'd1;  // 突发两次
              burst_count <= 0;  // 清空计数器
            end
          end else begin
            icahce_rdata_ok <= `FALSE;
          end
        end
        CACHE_MISS: begin
          if (ram_r_handshake) begin // 在 handshake 时，向 ram 写入数据
            if (burst_count == _ram_rlen_icache_o) begin  // 突发传输最后一个数据
              icahce_state <= CACHE_IDLE;
              icache_tag_wen <= `TRUE; // 写 tag 
              _ram_raddr_valid_icache_o <= `FALSE; // 传输结束
            end else begin
              burst_count <= burst_count_plus1;
            end
          end
        end
        // CACHE_MISS: begin
        //   if (_ram_raddr_valid_icache_o & ram_rdata_ready_icache_i) begin
        //     cache_line_temp[63:0] <= ram_rdata_icache_i;  // 临时保存 cache line 部分数据
        //     _ram_raddr_icache_o <= {line_tag_reg, line_idx_reg, 4'd8};  // 读地址
        //     icahce_state <= CACHE_MISS2;
        //   end
        // end
        // CACHE_MISS2: begin
        //   if (_ram_raddr_valid_icache_o & ram_rdata_ready_icache_i) begin

        //     // 从内存中读取的 cache line 缓存
        //     cache_line_temp[127:64] <= ram_rdata_icache_i;
        //     // tag data 写使能,在下一个周期将 cache line 的数据写入 cache 中
        //     icache_data_wen <= `TRUE;
        //     icache_tag_wen <= `TRUE;

        //     _ram_raddr_valid_icache_o <= `FALSE;
        //     icahce_state <= CACHE_IDLE;
        //   end
        // end
        default: begin
        end
      endcase
    end
  end




  icache_tag u_icache_tag (
      .clk           (clk),
      .rst           (rst),
      .icache_tag_i  (cache_line_tag),
      // tag
      .icache_index_i(cache_line_idx),
      // index
      .write_valid_i (icache_tag_wen),
      // 写使能
      .icache_hit_o  (icache_hit)
  );




  wire [127:0] icache_line_rdata;
  // wire [127:0] icache_wmask = 128'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;  // 高点平有效

  wire [127:0] icache_wmask = ~burst_count[0]?{64'b0,64'hffff_ffff_ffff_ffff}:{64'hffff_ffff_ffff_ffff,64'b0};
  wire [127:0] icache_wdate = ~burst_count[0]?{64'b0,ram_rdata_icache_i}:{ram_rdata_icache_i,64'b0};
  icache_data u_icache_data (
      .clk                (clk),
      .rst                (rst),
      .icache_index_i     (cache_line_idx),
      // index
      .icache_blk_addr_i  (cache_blk_addr),
      .icache_line_wdata_i(icache_wdate),
      .icache_wmask       (icache_wmask),
      .icache_wen_i       (ram_r_handshake),   // 写入有效
      .icache_line_rdata_o(icache_line_rdata)
  );

  //icache_data <= {32'b0, cache_line_regs[cache_line_idx][cache_blk_addr*8+:32]};
  wire [`XLEN_BUS] _icache_data_o = {32'b0, icache_line_rdata[blk_addr_reg*8+:32]};





  assign if_rdata_o = _icache_data_o & {64{if_rdata_valid_o}};

  assign if_rdata_valid_o = icahce_rdata_ok && (icahce_state == CACHE_IDLE);
  assign ram_raddr_icache_o = _ram_raddr_icache_o;
  assign ram_raddr_valid_icache_o = _ram_raddr_valid_icache_o;
  assign ram_rmask_icache_o = _ram_rmask_icache_o;
  assign ram_rsize_icache_o = _ram_rsize_icache_o;
  assign ram_rlen_icache_o = _ram_rlen_icache_o;



endmodule

