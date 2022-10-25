`include "sysconfig.v"
// 地址位宽 32,dcache<->cpu (数据64位) mem<-->dcache(数据128位)
// 连接方式 ram<-->cache<-->cpu
// cache<-->cpu : 地址线宽度:32 数据线宽度:64
/* 改造后的 dcache */
// 1. cache 总容量: 4KB (4096Byte)
// 2. cache 块大小: 64Byte
// 3. cache 块个数: 64个 (64*64Byte==4096Byte)
// 4. 映射方式 直接映射
// 5. 块内地址: 6bit(2^6==64)
// 6. 组号: 6bit（2^6==64）
// 6. tag: 32-6-6 == 20 bit 

module ysyx_041514_dcache_top (
    input clk,
    input rst,
    input mem_fencei_valid_i,
    output mem_fencei_ready_o,
    /* cpu<-->cache 端口 */
    input [`ysyx_041514_NPC_ADDR_BUS] mem_addr_i,  // CPU 的访存信息 
    input [7:0] mem_mask_i,  // 访存掩码
    input [3:0] mem_size_i,
    input mem_addr_valid_i,  // 地址是否有效，无效时，停止访问 cache
    input mem_write_valid_i,  // 1'b1,表示写;1'b0 表示读 
    input [`ysyx_041514_XLEN_BUS] mem_wdata_i,  // 写数据
    output [`ysyx_041514_XLEN_BUS] mem_rdata_o,  // dcache 返回读数据
    output mem_data_ready_o,  // dcache 读数据是否准备好(未准备好需要暂停流水线)

    /* dcache<-->mem 端口 */
    // 读端口
    output [`ysyx_041514_NPC_ADDR_BUS] ram_raddr_dcache_o,
    output                             ram_raddr_valid_dcache_o,
    output [                      7:0] ram_rmask_dcache_o,
    output [                      3:0] ram_rsize_dcache_o,
    output [                      7:0] ram_rlen_dcache_o,
    input                              ram_rdata_ready_dcache_i,
    input  [    `ysyx_041514_XLEN_BUS] ram_rdata_dcache_i,
    // 写端口
    output [`ysyx_041514_NPC_ADDR_BUS] ram_waddr_dcache_o,        // 地址
    output                             ram_waddr_valid_dcache_o,  // 地址是否准备好
    output [                      7:0] ram_wmask_dcache_o,        // 数据掩码,写入多少位
    output [                      3:0] ram_wsize_dcache_o,
    output [                      7:0] ram_wlen_dcache_o,         // 突发传输的长度
    input                              ram_wdata_ready_dcache_i,  // 数据是否已经写入
    output [    `ysyx_041514_XLEN_BUS] ram_wdata_dcache_o,        // 写入的数据


    /* sram */
    output [  5:0] io_sram0_addr,
    output         io_sram0_cen,
    output         io_sram0_wen,
    output [127:0] io_sram0_wmask,
    output [127:0] io_sram0_wdata,
    input  [127:0] io_sram0_rdata,
    output [  5:0] io_sram1_addr,
    output         io_sram1_cen,
    output         io_sram1_wen,
    output [127:0] io_sram1_wmask,
    output [127:0] io_sram1_wdata,
    input  [127:0] io_sram1_rdata,
    output [  5:0] io_sram2_addr,
    output         io_sram2_cen,
    output         io_sram2_wen,
    output [127:0] io_sram2_wmask,
    output [127:0] io_sram2_wdata,
    input  [127:0] io_sram2_rdata,
    output [  5:0] io_sram3_addr,
    output         io_sram3_cen,
    output         io_sram3_wen,
    output [127:0] io_sram3_wmask,
    output [127:0] io_sram3_wdata,
    input  [127:0] io_sram3_rdata
);
  // 寄存器已复位

`ifndef ysyx_041514_YSYX_SOC
  import "DPI-C" function void dcache_hit_count();
  import "DPI-C" function void dcache_unhit_count();
`endif


  // uncache 检查
  wire uncache;
  ysyx_041514_uncache_check u_ysyx_041514_uncache_check1 (
      .addr_check_i   (mem_addr_i),
      .uncache_valid_o(uncache)
  );


  wire fencei_valid = mem_fencei_valid_i;

  wire [5:0] cache_blk_addr;
  wire [5:0] cache_line_idx;
  wire [19:0] cache_line_tag;
  assign {cache_line_tag, cache_line_idx, cache_blk_addr} = mem_addr_i;


  wire dcache_hit;
  wire [63:0] wmask_bit;
  wire dirty_bit_read;
  wire [19:0] dcache_tag_read;
  wire [`ysyx_041514_XLEN_BUS] dcache_writeback_data;

  /* cache 命中 */
  localparam CACHE_RST = 4'd0;
  localparam CACHE_IDLE = 4'd1;
  localparam CACHE_FENCEI = 4'd2;
  localparam CACHE_MISS_ALLOCATE = 4'd3;
  localparam CACHE_WRITE_BACK = 4'd4;
  localparam CACHE_FENCEI_WRITE_BACK = 4'd5;
  localparam CACHE_FENCEI_WAIT = 4'd6;
  localparam CACHE_WRITE_MISS = 4'd7;
  localparam UNCACHE_READ = 4'd8;
  localparam UNCACHE_WRITE = 4'd9;

  reg [3:0] dcache_state;


  reg [5:0] blk_addr_reg;

  // reg [19:0] line_tag_reg;
  reg dcache_tag_wen;


  reg dcache_data_ready;
  // cache<-->mem 端口 
  reg [`ysyx_041514_NPC_ADDR_BUS] _ram_raddr_dcache_o;
  reg _ram_raddr_valid_dcache_o;
  reg [7:0] _ram_rmask_dcache_o;
  reg [3:0] _ram_rsize_dcache_o;
  reg [7:0] _ram_rlen_dcache_o;

  reg [`ysyx_041514_NPC_ADDR_BUS] _ram_waddr_dcache_o;
  reg _ram_waddr_valid_dcache_o;
  reg [7:0] _ram_wmask_dcache_o;
  reg [3:0] _ram_wsize_dcache_o;
  reg [7:0] _ram_wlen_dcache_o;
  reg [`ysyx_041514_XLEN_BUS] _ram_wdata_dcache_o;


  reg [127:0] dcache_wdata_writehit;
  reg [`ysyx_041514_XLEN_BUS] uncache_rdata;
  reg dcache_data_wen;
  reg _dirty_bit_write;
  reg dcache_write_hit_valid;
  reg fencei_ready;

  reg [127:0] dcache_wmask_writehit;


  reg [3:0] burst_count;
  wire [3:0] burst_count_plus1 = burst_count + 1;
  reg [6:0] fencei_count;
  wire [5:0] fencei_line_idx = fencei_count[5:0];
  wire [6:0] fencei_count_plus1 = fencei_count + 1;
  reg _dirty_flush;
  wire ram_r_handshake = _ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i;
  wire ram_w_handshake = _ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i;

  always @(posedge clk) begin
    if (rst) begin
      dcache_state <= CACHE_RST;
      burst_count <= 0;
      fencei_count <= 0;
      blk_addr_reg <= 0;
      //line_tag_reg <= 0;
      dcache_tag_wen <= 0;
      dcache_data_wen <= 0;
      _dirty_bit_write <= 0;
      _dirty_flush <= 0;
      fencei_ready <= 0;
      dcache_write_hit_valid <= 0;
      dcache_wdata_writehit <= 0;
      _ram_rsize_dcache_o <= 0;
      _ram_wsize_dcache_o <= 0;
      _ram_rlen_dcache_o <= 0;
      _ram_wlen_dcache_o <= 0;
      uncache_rdata <= 0;
      _ram_wdata_dcache_o <= 0;
      _ram_waddr_dcache_o <= 0;
      _ram_rmask_dcache_o <= 0;
      dcache_data_ready <= 0;
      _ram_raddr_valid_dcache_o <= `ysyx_041514_FALSE;
      _ram_waddr_valid_dcache_o <= `ysyx_041514_FALSE;
      dcache_wmask_writehit <= 0;
      _ram_raddr_dcache_o <= 0;
      _ram_wmask_dcache_o <= 0;

    end else begin
      case (dcache_state)
        CACHE_RST: begin
          dcache_state <= CACHE_IDLE;
        end
        CACHE_IDLE: begin
          blk_addr_reg <= cache_blk_addr;
          // line_tag_reg <= cache_line_tag;
          fencei_ready <= 0;
          _dirty_flush <= `ysyx_041514_FALSE;
          //dcache_wmask <= 0;
          // cache data 为单端口 ram,不能同时读写, uncache 直接访问内存
          if (mem_addr_valid_i && ~dcache_data_wen && ~uncache && ~dcache_tag_wen) begin
            case ({
              dcache_hit, mem_write_valid_i
            })
              2'b11: begin : write_hit  // TODO : 只写入 cache ，不写入内存
`ifndef ysyx_041514_YSYX_SOC
                dcache_hit_count();
`endif
                dcache_state <= CACHE_IDLE;
                //写 cache
                dcache_data_wen <= `ysyx_041514_TRUE;
                dcache_data_ready <= `ysyx_041514_TRUE;  // 完成信号
                dcache_tag_wen <= `ysyx_041514_TRUE;
                _dirty_bit_write <= `ysyx_041514_TRUE;  // 标记为脏
                dcache_write_hit_valid <= `ysyx_041514_TRUE;  //写信号
                dcache_wdata_writehit <= (mem_addr_i[3]) ? {mem_wdata_i, 64'b0} : {64'b0, mem_wdata_i};
                dcache_wmask_writehit <= (mem_addr_i[3]) ? {wmask_bit, 64'b0} : {64'b0, wmask_bit};
              end
              2'b10: begin : read_hit
`ifndef ysyx_041514_YSYX_SOC
                dcache_hit_count();
`endif
                dcache_data_ready <= `ysyx_041514_TRUE;
                dcache_state <= CACHE_IDLE;
              end
              2'b00, 2'b01: begin : miss_allocate  // miss 时 分配 cache，需要考虑脏位
`ifndef ysyx_041514_YSYX_SOC
                dcache_unhit_count();
`endif
                if (dirty_bit_read) begin  // 需要写回
                  dcache_state <= CACHE_WRITE_BACK;
                  dcache_data_ready <= `ysyx_041514_FALSE;
                  _ram_waddr_dcache_o <= {dcache_tag_read, cache_line_idx, 6'b0};  // 写地址
                  _ram_waddr_valid_dcache_o <= `ysyx_041514_TRUE;  // 地址有效
                  _ram_wmask_dcache_o <= 8'b1111_1111;  // 写掩码
                  _ram_wdata_dcache_o <= dcache_writeback_data;  // 写数据
                  _ram_wsize_dcache_o <= 4'b1000;  //写大小 8byte
                  _ram_wlen_dcache_o <= 8'd7;  // 突发 7 次
                  burst_count <= 0;  // 清空计数器
                end else begin  // 不需要写回
                  dcache_state              <= CACHE_MISS_ALLOCATE;
                  dcache_data_ready         <= `ysyx_041514_FALSE;
                  _ram_raddr_dcache_o       <= {cache_line_tag, cache_line_idx, 6'b0};  // 读地址
                  _ram_raddr_valid_dcache_o <= `ysyx_041514_TRUE;  // 地址有效
                  _ram_rmask_dcache_o       <= 8'b1111_1111;  // 读掩码
                  _ram_rsize_dcache_o       <= 4'b1000;  //读大小 8byte
                  _ram_rlen_dcache_o        <= 8'd7;  // 突发 7 次
                  burst_count               <= 0;  // 清空计数器
                end
              end
            endcase
          end else if (mem_addr_valid_i && uncache) begin : uncache_rw
            // 判断是读还是写
            if (mem_write_valid_i) begin
              dcache_state              <= UNCACHE_WRITE;
              dcache_data_ready         <= `ysyx_041514_FALSE;
              _ram_waddr_dcache_o       <= mem_addr_i;  // 写地址
              _ram_waddr_valid_dcache_o <= `ysyx_041514_TRUE;  // 地址有效
              _ram_wmask_dcache_o       <= 8'b1111_1111;  // 写掩码
              _ram_wdata_dcache_o       <= mem_wdata_i;  // 写数据
              _ram_wsize_dcache_o       <= mem_size_i;  //写大小
              _ram_wlen_dcache_o        <= 8'd0;  // 不突发
            end else begin
              dcache_state              <= UNCACHE_READ;
              dcache_data_ready         <= `ysyx_041514_FALSE;
              _ram_raddr_dcache_o       <= mem_addr_i;  // 读地址
              _ram_raddr_valid_dcache_o <= `ysyx_041514_TRUE;  // 地址有效
              _ram_rmask_dcache_o       <= 8'b1111_1111;  // 读掩码
              _ram_rsize_dcache_o       <= mem_size_i;  //读大小
              _ram_rlen_dcache_o        <= 8'd0;  // 不突发
            end

          end else if (fencei_valid) begin
            dcache_data_ready <= `ysyx_041514_FALSE;
            dcache_state <= CACHE_FENCEI_WAIT;
            fencei_count <= 0;
          end else begin
            dcache_data_ready <= `ysyx_041514_FALSE;
            _ram_raddr_valid_dcache_o <= `ysyx_041514_FALSE;
            _ram_waddr_valid_dcache_o <= `ysyx_041514_FALSE;
            dcache_tag_wen <= `ysyx_041514_FALSE;
            dcache_data_wen <= 0;
            _dirty_bit_write <= `ysyx_041514_FALSE;
            dcache_wdata_writehit <= 0;
            dcache_write_hit_valid <= `ysyx_041514_FALSE;  //写信号
          end
        end

        CACHE_MISS_ALLOCATE: begin
          if (ram_r_handshake) begin  // 在 handshake 时，向 ram 写入数据
            if (burst_count[3:0] == _ram_rlen_dcache_o[3:0]) begin  // 突发传输最后一个数据
              dcache_state              <= CACHE_IDLE;
              dcache_tag_wen            <= `ysyx_041514_TRUE;  // 写 tag 
              _dirty_bit_write          <= `ysyx_041514_FALSE;
              _ram_raddr_valid_dcache_o <= `ysyx_041514_FALSE;  // 传输结束
              burst_count               <= 0;
            end else begin
              burst_count <= burst_count_plus1;
            end
          end
        end

        CACHE_WRITE_MISS: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin

            _ram_waddr_valid_dcache_o <= `ysyx_041514_FALSE;
            dcache_data_ready <= `ysyx_041514_TRUE;  // 完成信号
            dcache_state <= CACHE_IDLE;
          end
        end

        CACHE_WRITE_BACK: begin
          if (ram_w_handshake) begin
            if (burst_count == 4'd7) begin  // 收到最后一个写响应
              _ram_waddr_valid_dcache_o <= `ysyx_041514_FALSE;  // 传输结束

              // 写入 cache 中
              dcache_state              <= CACHE_MISS_ALLOCATE;
              dcache_data_ready         <= `ysyx_041514_FALSE;
              _ram_raddr_dcache_o       <= {cache_line_tag, cache_line_idx, 6'b0};  // 读地址
              _ram_raddr_valid_dcache_o <= `ysyx_041514_TRUE;  // 地址有效
              _ram_rmask_dcache_o       <= 8'b1111_1111;  // 读掩码
              _ram_rsize_dcache_o       <= 4'b1000;  //读大小 8byte
              _ram_rlen_dcache_o        <= 8'd7;  // 突发 7 次
              burst_count               <= 0;  // 清空计数器
            end else begin
              burst_count <= burst_count_plus1;
              _ram_wdata_dcache_o <= dcache_writeback_data;  // 更新写数据
            end
          end
        end
        UNCACHE_READ: begin
          if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin
            _ram_raddr_valid_dcache_o <= `ysyx_041514_FALSE;
            dcache_data_ready <= `ysyx_041514_TRUE;  // 完成信号
            uncache_rdata <= ram_rdata_dcache_i >> {blk_addr_reg[2:0], 3'b0};  // 数据返回
            dcache_state <= CACHE_IDLE;
          end
        end
        UNCACHE_WRITE: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin
            _ram_waddr_valid_dcache_o <= `ysyx_041514_FALSE;
            dcache_data_ready         <= `ysyx_041514_TRUE;  // 完成信号
            dcache_state              <= CACHE_IDLE;
          end
        end

        CACHE_FENCEI: begin
          if (dirty_bit_read) begin
            dcache_state <= CACHE_FENCEI_WRITE_BACK;
            dcache_data_ready <= `ysyx_041514_FALSE;
            _ram_waddr_dcache_o <= {dcache_tag_read, fencei_line_idx, 6'b0};  // 写地址
            _ram_waddr_valid_dcache_o <= `ysyx_041514_TRUE;  // 地址有效
            _ram_wmask_dcache_o <= 8'b1111_1111;  // 写掩码
            _ram_wdata_dcache_o <= dcache_writeback_data;  // 写数据
            _ram_wsize_dcache_o <= 4'b1000;  //写大小 8byte
            _ram_wlen_dcache_o <= 8'd7;  // 突发 7 次
            burst_count <= 0;  // 清空计数器
          end else begin
            fencei_count <= fencei_count_plus1;
            dcache_state <= CACHE_FENCEI_WAIT;
          end
        end
        CACHE_FENCEI_WRITE_BACK: begin
          if (ram_w_handshake) begin
            if (burst_count == 4'd7) begin  // 收到最后一个写响应
              _ram_waddr_valid_dcache_o <= `ysyx_041514_FALSE;  // 传输结束
              dcache_state              <= CACHE_FENCEI_WAIT;
              fencei_count              <= fencei_count_plus1;

            end else begin
              burst_count <= burst_count_plus1;
              _ram_wdata_dcache_o <= dcache_writeback_data;  // 更新写数据
            end
          end
        end
        CACHE_FENCEI_WAIT: begin
          dcache_tag_wen <= `ysyx_041514_FALSE;  // 写 tag 
          if (fencei_count == 'd64) begin
            dcache_state <= CACHE_IDLE;
            _dirty_flush <= `ysyx_041514_TRUE;
            fencei_ready <= `ysyx_041514_TRUE;
            fencei_count <= 0;
          end else begin
            dcache_state <= CACHE_FENCEI;
          end
        end
        default: begin
        end
      endcase
    end
  end



  assign wmask_bit = {
    {8{mem_mask_i[7]}},
    {8{mem_mask_i[6]}},
    {8{mem_mask_i[5]}},
    {8{mem_mask_i[4]}},
    {8{mem_mask_i[3]}},
    {8{mem_mask_i[2]}},
    {8{mem_mask_i[1]}},
    {8{mem_mask_i[0]}}
  };



  wire [127:0] dcache_wmask_readmiss = ~burst_count[0]?{64'b0,64'hffff_ffff_ffff_ffff}:{64'hffff_ffff_ffff_ffff,64'b0};
  wire [127:0] dcache_wdate_readmiss = ~burst_count[0]?{64'b0,ram_rdata_dcache_i}:{ram_rdata_dcache_i,64'b0};

  wire state_readmiss = dcache_state == CACHE_MISS_ALLOCATE;
  wire state_writehit = dcache_write_hit_valid;
  wire state_writeback = dcache_state == CACHE_WRITE_BACK;

  wire [127:0] dcache_wmask = ({128{state_readmiss}}&dcache_wmask_readmiss)
                            | ({128{state_writehit}}&dcache_wmask_writehit);

  wire [127:0] dcache_wdata = ({128{state_readmiss}}&dcache_wdate_readmiss)
                            | ({128{state_writehit}}&dcache_wdata_writehit);


  wire dcache_wwen = (state_readmiss & ram_r_handshake) | (state_writehit & dcache_data_wen);


  wire dirty_bit_write = _dirty_bit_write;
  wire [19:0] dcache_tag_write = cache_line_tag;

  wire dirty_flush = _dirty_flush;

  wire dcache_allocate_valid = state_readmiss;
  wire dcache_writeback_valid = state_writeback | mem_fencei_valid_i;
  wire dcache_fencei_valid = mem_fencei_valid_i;

  wire [5:0] dcache_index = dcache_fencei_valid ? fencei_line_idx : cache_line_idx;

  wire [`ysyx_041514_XLEN_BUS] dcache_rdata;
  ysyx_041514_dcache_tag u_dcache_tag (
      .clk              (clk),
      .rst              (rst),
      .dcache_tag_i     (dcache_tag_write),  // tag
      .dcache_index_i   (dcache_index),      // index
      .write_valid_i    (dcache_tag_wen),    // 写使能
      .dcache_tag_o     (dcache_tag_read),
      .dirty_bit_read_o (dirty_bit_read),
      .dirty_bit_write_i(dirty_bit_write),
      .dirty_flush_i    (dirty_flush),
      .dcache_hit_o     (dcache_hit)
  );

  ysyx_041514_dcache_data u_dcache_data (
      // .clk                     (clk),
      // .rst                     (rst),
      .dcache_index_i          (dcache_index),
      // index
      .dcache_blk_addr_i       (cache_blk_addr),
      .dcache_line_wdata_i     (dcache_wdata),
      .dcache_wmask            (dcache_wmask),
      .dcache_wen_i            (dcache_wwen),
      .burst_count_i           (burst_count[2:0]),
      .dcache_allocate_valid_i (dcache_allocate_valid),
      .dcache_writeback_valid_i(dcache_writeback_valid),
      .dcache_writeback_data_o (dcache_writeback_data),
      .dcache_rdata_o          (dcache_rdata),
      /* sram */
      .io_sram0_addr           (io_sram0_addr),
      .io_sram0_cen            (io_sram0_cen),
      .io_sram0_wen            (io_sram0_wen),
      .io_sram0_wmask          (io_sram0_wmask),
      .io_sram0_wdata          (io_sram0_wdata),
      .io_sram0_rdata          (io_sram0_rdata),
      .io_sram1_addr           (io_sram1_addr),
      .io_sram1_cen            (io_sram1_cen),
      .io_sram1_wen            (io_sram1_wen),
      .io_sram1_wmask          (io_sram1_wmask),
      .io_sram1_wdata          (io_sram1_wdata),
      .io_sram1_rdata          (io_sram1_rdata),
      .io_sram2_addr           (io_sram2_addr),
      .io_sram2_cen            (io_sram2_cen),
      .io_sram2_wen            (io_sram2_wen),
      .io_sram2_wmask          (io_sram2_wmask),
      .io_sram2_wdata          (io_sram2_wdata),
      .io_sram2_rdata          (io_sram2_rdata),
      .io_sram3_addr           (io_sram3_addr),
      .io_sram3_cen            (io_sram3_cen),
      .io_sram3_wen            (io_sram3_wen),
      .io_sram3_wmask          (io_sram3_wmask),
      .io_sram3_wdata          (io_sram3_wdata),
      .io_sram3_rdata          (io_sram3_rdata)
  );



  assign ram_wlen_dcache_o = _ram_wlen_dcache_o;
  assign ram_rlen_dcache_o = _ram_rlen_dcache_o;
  assign mem_fencei_ready_o = fencei_ready;



  assign mem_rdata_o = (uncache) ? uncache_rdata : dcache_rdata;

  assign mem_data_ready_o = dcache_data_ready && (dcache_state == CACHE_IDLE);

  assign ram_raddr_dcache_o = _ram_raddr_dcache_o;
  assign ram_raddr_valid_dcache_o = _ram_raddr_valid_dcache_o;
  assign ram_rmask_dcache_o = _ram_rmask_dcache_o;
  assign ram_rsize_dcache_o = _ram_rsize_dcache_o;


  assign ram_waddr_dcache_o = _ram_waddr_dcache_o;
  assign ram_waddr_valid_dcache_o = _ram_waddr_valid_dcache_o;
  assign ram_wmask_dcache_o = _ram_wmask_dcache_o;
  assign ram_wdata_dcache_o = dcache_writeback_valid ? dcache_writeback_data : _ram_wdata_dcache_o;
  assign ram_wsize_dcache_o = _ram_wsize_dcache_o;

endmodule
