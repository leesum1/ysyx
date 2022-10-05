`include "sysconfig.v"
// 地址位宽 32,icache<->cpu (数据64位) mem<-->icache(数据128位)
// 连接方式 ram<-->cache<-->cpu
// cache<-->cpu : 地址线宽度:32 数据线宽度:64

// 1. cache 总容量: 4KB (4096Byte)
// 2. cahce 块大小: 64Byte
// 3. cache 块个数: 64个 (64*64Byte==4096Byte)
// 4. 映射方式 直接映射
// 5. 块内地址: 6bit(2^6==64)
// 6. 组号: 6bit（2^6==64）
// 6. tag: 32-6-6 == 20 bit 

module ysyx_041514_icache_top (
    input clk,
    input rst,
    /* cpu<-->cache 端口 */
    input [`ysyx_041514_NPC_ADDR_BUS] preif_raddr_i,  // CPU 的访存信息 
    input [7:0] preif_rmask_i,  // 访存掩码
    input preif_raddr_valid_i,  // 地址是否有效，无效时，停止访问 cache
    output [`ysyx_041514_XLEN_BUS] if_rdata_o,  // icache 返回读数据

    //input  if_rdata_ready_i,  // 是否准备好接收数据
    output if_rdata_valid_o,  // icache 读数据是否准备好(未准备好需要暂停流水线)

    /* cache<-->mem 端口 */
    output [`ysyx_041514_NPC_ADDR_BUS] ram_raddr_icache_o,
    output                             ram_raddr_valid_icache_o,
    output [                      7:0] ram_rmask_icache_o,
    output [                      3:0] ram_rsize_icache_o,
    output [                      7:0] ram_rlen_icache_o,
    input                              ram_rdata_ready_icache_i,
    input  [    `ysyx_041514_XLEN_BUS] ram_rdata_icache_i,
    /* sram */
    output [                      5:0] io_sram4_addr,
    output                             io_sram4_cen,
    output                             io_sram4_wen,
    output [                    127:0] io_sram4_wmask,
    output [                    127:0] io_sram4_wdata,
    input  [                    127:0] io_sram4_rdata,
    output [                      5:0] io_sram5_addr,
    output                             io_sram5_cen,
    output                             io_sram5_wen,
    output [                    127:0] io_sram5_wmask,
    output [                    127:0] io_sram5_wdata,
    input  [                    127:0] io_sram5_rdata,
    output [                      5:0] io_sram6_addr,
    output                             io_sram6_cen,
    output                             io_sram6_wen,
    output [                    127:0] io_sram6_wmask,
    output [                    127:0] io_sram6_wdata,
    input  [                    127:0] io_sram6_rdata,
    output [                      5:0] io_sram7_addr,
    output                             io_sram7_cen,
    output                             io_sram7_wen,
    output [                    127:0] io_sram7_wmask,
    output [                    127:0] io_sram7_wdata,
    input  [                    127:0] io_sram7_rdata
);
  wire [ 5:0] cache_blk_addr;
  wire [ 5:0] cache_line_idx;
  wire [19:0] cache_line_tag;
  assign {cache_line_tag, cache_line_idx, cache_blk_addr} = preif_raddr_i;

  wire icache_hit;
  wire uncache;
  ysyx_041514_uncache_check u_ysyx_041514_uncache_check (
    .addr_check_i       (preif_raddr_i),
    .uncache_valid_o    (uncache)
);

  reg [`ysyx_041514_XLEN_BUS] uncache_rdata;

  /* cache 命中 */
  localparam CACHE_RST = 4'd0;
  localparam CACHE_IDLE = 4'd1;
  localparam CACHE_HIT = 4'd2;
  localparam CACHE_MISS = 4'd3;
  localparam CACHE_MISS2 = 4'd4;
  localparam UNCACHE_READ = 4'd5;

  reg [3:0] icache_state;


  reg [5:0] blk_addr_reg;
  reg [5:0] line_idx_reg;
  reg [19:0] line_tag_reg;
  reg icache_tag_wen;

  reg icache_data_ready;
  // cache<-->mem 端口 
  reg [`ysyx_041514_NPC_ADDR_BUS] _ram_raddr_icache_o;
  reg _ram_raddr_valid_icache_o;
  reg [7:0] _ram_rmask_icache_o;
  reg [3:0] _ram_rsize_icache_o;
  reg [7:0] _ram_rlen_icache_o;
  reg [2:0] burst_count;


  wire ram_r_handshake = _ram_raddr_valid_icache_o & ram_rdata_ready_icache_i;
  wire [2:0] burst_count_plus1 = burst_count + 1;


  always @(posedge clk) begin
    if (rst) begin
      icache_state        <= CACHE_RST;
      blk_addr_reg        <= 0;
      line_idx_reg        <= 0;
      line_tag_reg        <= 0;
      icache_tag_wen      <= 0;
      _ram_rsize_icache_o <= 0;
      _ram_rlen_icache_o  <= 0;
      burst_count         <= 0;
    end else begin
      case (icache_state)
        CACHE_RST: begin
          icache_state <= CACHE_IDLE;
        end
        CACHE_IDLE: begin
          blk_addr_reg   <= cache_blk_addr;
          line_idx_reg   <= cache_line_idx;
          line_tag_reg   <= cache_line_tag;
          icache_tag_wen <= `ysyx_041514_FALSE;
          // cache data 为单端口 ram,不能同时读写
          if (preif_raddr_valid_i && ~icache_tag_wen && ~uncache) begin
            // hit
            if (icache_hit) begin
              // 下一个周期给数据
              //icache_data <= {32'b0, cache_line_regs[cache_line_idx][cache_blk_addr*8+:32]};
              icache_data_ready <= `ysyx_041514_TRUE;
              icache_state <= CACHE_IDLE;
            end else begin  // miss 
              icache_state <= CACHE_MISS;
              icache_data_ready <= `ysyx_041514_FALSE;
              _ram_raddr_icache_o <= {cache_line_tag, cache_line_idx, 6'b0};  // 读地址
              _ram_raddr_valid_icache_o <= `ysyx_041514_TRUE;  // 地址有效
              _ram_rmask_icache_o <= 8'b1111_1111;  // 读掩码
              _ram_rsize_icache_o <= 4'b1000;  // 64bit
              _ram_rlen_icache_o <= 8'd7;  // 突发 8 次
              burst_count <= 0;  // 清空计数器
            end
          end else if (preif_raddr_valid_i && uncache) begin : uncache_rw
            icache_state              <= UNCACHE_READ;
            icache_data_ready         <= `ysyx_041514_FALSE;
            _ram_raddr_icache_o       <= preif_raddr_i;  // 读地址
            _ram_raddr_valid_icache_o <= `ysyx_041514_TRUE;  // 地址有效
            _ram_rmask_icache_o       <= 8'b1111_1111;  // 读掩码
            _ram_rsize_icache_o       <= 4'b0100;  //读大小 32bit,一条指令
            _ram_rlen_icache_o        <= 8'd0;  // 不突发
          end else begin
            icache_data_ready <= `ysyx_041514_FALSE;
          end
        end

        CACHE_MISS: begin
          if (ram_r_handshake) begin  // 在 handshake 时，向 ram 写入数据
            if (burst_count == _ram_rlen_icache_o[2:0]) begin  // 突发传输最后一个数据
              icache_state <= CACHE_IDLE;
              _ram_raddr_valid_icache_o <= `ysyx_041514_FALSE;  // 传输结束
              icache_tag_wen <= `ysyx_041514_TRUE;  // 写 tag 
            end else begin
              burst_count <= burst_count_plus1;
            end
          end
        end
        UNCACHE_READ: begin
          if (ram_r_handshake) begin
            _ram_raddr_valid_icache_o <= `ysyx_041514_FALSE;
            icache_data_ready <= `ysyx_041514_TRUE;  // 完成信号
            uncache_rdata     <= _ram_raddr_icache_o[2]?{32'b0,ram_rdata_icache_i[63:32]}:ram_rdata_icache_i;  // 数据返回
            icache_state <= CACHE_IDLE;
          end
        end

        default: begin
        end
      endcase
    end
  end

  ysyx_041514_icache_tag u_icache_tag (
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



  wire [127:0] icache_wmask = ~burst_count[0]?{64'b0,64'hffff_ffff_ffff_ffff}:{64'hffff_ffff_ffff_ffff,64'b0};
  wire [127:0] icache_wdate = ~burst_count[0]?{64'b0,ram_rdata_icache_i}:{ram_rdata_icache_i,64'b0};
  wire [`ysyx_041514_XLEN_BUS] icache_rdata;
  ysyx_041514_icache_data u_icache_data (
      // .clk                (clk),
      // .rst                (rst),
      .icache_index_i     (cache_line_idx),   //cache_line_idx 使用直接输入数据
      // index
      .icache_blk_addr_i  (blk_addr_reg),     // icache_blk_addr_i 使用寄存器中的数据
      .icache_line_wdata_i(icache_wdate),
      .icache_wmask       (icache_wmask),
      .icache_wen_i       (ram_r_handshake),  // 写入有效
      .burst_count_i      (burst_count),
      .icache_rdata_o     (icache_rdata),
      /* sram */
      .io_sram4_addr      (io_sram4_addr),
      .io_sram4_cen       (io_sram4_cen),
      .io_sram4_wen       (io_sram4_wen),
      .io_sram4_wmask     (io_sram4_wmask),
      .io_sram4_wdata     (io_sram4_wdata),
      .io_sram4_rdata     (io_sram4_rdata),
      .io_sram5_addr      (io_sram5_addr),
      .io_sram5_cen       (io_sram5_cen),
      .io_sram5_wen       (io_sram5_wen),
      .io_sram5_wmask     (io_sram5_wmask),
      .io_sram5_wdata     (io_sram5_wdata),
      .io_sram5_rdata     (io_sram5_rdata),
      .io_sram6_addr      (io_sram6_addr),
      .io_sram6_cen       (io_sram6_cen),
      .io_sram6_wen       (io_sram6_wen),
      .io_sram6_wmask     (io_sram6_wmask),
      .io_sram6_wdata     (io_sram6_wdata),
      .io_sram6_rdata     (io_sram6_rdata),
      .io_sram7_addr      (io_sram7_addr),
      .io_sram7_cen       (io_sram7_cen),
      .io_sram7_wen       (io_sram7_wen),
      .io_sram7_wmask     (io_sram7_wmask),
      .io_sram7_wdata     (io_sram7_wdata),
      .io_sram7_rdata     (io_sram7_rdata)
  );






  // wire [`ysyx_041514_XLEN_BUS] _icache_data_o = {32'b0, icache_line_rdata[blk_addr_reg*8+:32]};

  wire [`ysyx_041514_XLEN_BUS] icache_final_data = uncache ? uncache_rdata : icache_rdata;
  assign if_rdata_o = icache_final_data;


  assign if_rdata_valid_o = icache_data_ready && (icache_state == CACHE_IDLE);
  assign ram_raddr_icache_o = _ram_raddr_icache_o;
  assign ram_raddr_valid_icache_o = _ram_raddr_valid_icache_o;
  assign ram_rmask_icache_o = _ram_rmask_icache_o;
  assign ram_rsize_icache_o = _ram_rsize_icache_o;
  assign ram_rlen_icache_o = _ram_rlen_icache_o;

endmodule

