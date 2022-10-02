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

module dcache_top (
    input clk,
    input rst,
    /* cpu<-->cache 端口 */
    input [`NPC_ADDR_BUS] mem_addr_i,  // CPU 的访存信息 
    input [7:0] mem_mask_i,  // 访存掩码
    input [3:0] mem_size_i,
    input mem_addr_valid_i,  // 地址是否有效，无效时，停止访问 cache
    input mem_write_valid_i,  // 1'b1,表示写;1'b0 表示读 
    input [`XLEN_BUS] mem_wdata_i,  // 写数据
    output [`XLEN_BUS] mem_rdata_o,  // dcache 返回读数据
    output mem_data_ready_o,  // dcache 读数据是否准备好(未准备好需要暂停流水线)

    /* dcache<-->mem 端口 */
    // 读端口
    output [`NPC_ADDR_BUS] ram_raddr_dcache_o,
    output                 ram_raddr_valid_dcache_o,
    output [          7:0] ram_rmask_dcache_o,
    output [          3:0] ram_rsize_dcache_o,
    output [          7:0] ram_rlen_dcache_o,
    input                  ram_rdata_ready_dcache_i,
    input  [    `XLEN_BUS] ram_rdata_dcache_i,
    // 写端口
    output [`NPC_ADDR_BUS] ram_waddr_dcache_o,        // 地址
    output                 ram_waddr_valid_dcache_o,  // 地址是否准备好
    output [          7:0] ram_wmask_dcache_o,        // 数据掩码,写入多少位
    output [          3:0] ram_wsize_dcache_o,
    output [          7:0] ram_wlen_dcache_o,         // 突发传输的长度
    input                  ram_wdata_ready_dcache_i,  // 数据是否已经写入
    output [    `XLEN_BUS] ram_wdata_dcache_o         // 写入的数据
);

  assign ram_wlen_dcache_o = _ram_wlen_dcache_o;
  assign ram_rlen_dcache_o = _ram_rlen_dcache_o;

  // uncache 检查

  wire uncache = (mem_addr_i & `MMIO_BASE) == `MMIO_BASE;

  wire [5:0] cache_blk_addr;
  wire [5:0] cache_line_idx;
  wire [19:0] cache_line_tag;
  assign {cache_line_tag, cache_line_idx, cache_blk_addr} = mem_addr_i;


  wire dcache_hit;

  /* cache 命中 */
  localparam CACHE_RST = 4'd0;
  localparam CACHE_IDLE = 4'd1;
  localparam CACHE_READ_HIT = 4'd2;
  localparam CACHE_READ_MISS = 4'd3;
  localparam CACHE_WRITE_BACK = 4'd4;
  localparam CACHE_WRITE_HIT1 = 4'd5;
  localparam CACHE_WRITE_HIT2 = 4'd6;
  localparam CACHE_WRITE_MISS = 4'd7;
  localparam CACHE_WRITE_MISS2 = 4'd8;
  localparam UNCACHE_READ = 4'd9;
  localparam UNCACHE_WRITE = 4'd10;

  reg [3:0] dcache_state;


  reg [5:0] blk_addr_reg;
  reg [5:0] line_idx_reg;
  reg [19:0] line_tag_reg;
  reg dcache_tag_wen;


  reg dcache_data_ready;
  // cache<-->mem 端口 
  reg [`NPC_ADDR_BUS] _ram_raddr_dcache_o;
  reg _ram_raddr_valid_dcache_o;
  reg [7:0] _ram_rmask_dcache_o;
  reg [3:0] _ram_rsize_dcache_o;
  reg [7:0] _ram_rlen_dcache_o;

  reg [`NPC_ADDR_BUS] _ram_waddr_dcache_o;
  reg _ram_waddr_valid_dcache_o;
  reg [7:0] _ram_wmask_dcache_o;
  reg [3:0] _ram_wsize_dcache_o;
  reg [7:0] _ram_wlen_dcache_o;
  reg [`XLEN_BUS] _ram_wdata_dcache_o;


  reg [127:0] dcache_wdata_writehit;
  reg [`XLEN_BUS] uncache_rdata;
  reg dcache_data_wen;
  reg _dirty_bit_write;
  reg dcache_write_hit_valid;


  reg [3:0] burst_count;
  wire [3:0] burst_count_plus1 = burst_count + 1;
  wire ram_r_handshake = _ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i;
  wire ram_w_handshake = _ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i;

  always @(posedge clk) begin
    if (rst) begin
      dcache_state <= CACHE_RST;
      blk_addr_reg <= 0;
      line_idx_reg <= 0;
      line_tag_reg <= 0;
      dcache_tag_wen <= 0;
      dcache_data_wen <= 0;
      _dirty_bit_write <= 0;
      dcache_write_hit_valid <= 0;
      dcache_wdata_writehit <= 0;
      _ram_rsize_dcache_o <= 0;
      _ram_wsize_dcache_o <= 0;
      _ram_rlen_dcache_o <= 0;
      _ram_wlen_dcache_o <= 0;
      _ram_raddr_valid_dcache_o <= `FALSE;
      _ram_waddr_valid_dcache_o <= `FALSE;

    end else begin
      case (dcache_state)
        CACHE_RST: begin
          dcache_state <= CACHE_IDLE;
        end
        CACHE_IDLE: begin
          blk_addr_reg <= cache_blk_addr;
          line_idx_reg <= cache_line_idx;
          line_tag_reg <= cache_line_tag;

          //dcache_wmask <= 0;
          // cache data 为单端口 ram,不能同时读写, uncache 直接访问内存
          if (mem_addr_valid_i && ~dcache_data_wen && ~uncache && ~dcache_tag_wen) begin
            case ({
              dcache_hit, mem_write_valid_i
            })
              2'b11: begin : write_hit  // TODO : 只写入 cache ，不写入内存
                dcache_state <= CACHE_IDLE;
                dcache_data_ready <= `FALSE;

                //写 cache
                dcache_data_wen <= `TRUE;
                dcache_data_ready <= `TRUE;  // 完成信号
                dcache_tag_wen <= `TRUE;
                _dirty_bit_write <= `TRUE;
                dcache_write_hit_valid <= `TRUE;  //写信号
                dcache_wdata_writehit <= (mem_addr_i[3]) ? {mem_wdata_i, 64'b0} : {64'b0, mem_wdata_i};
                dcache_wmask_writehit <= (mem_addr_i[3]) ? {wmask_bit, 64'b0} : {64'b0, wmask_bit};
              end
              2'b10: begin : read_hit
                dcache_data_ready <= `TRUE;
                dcache_state <= CACHE_IDLE;
              end
              //2'b01: begin : write_miss  // write through and write not allocate,直接写入内存，不分配 cache
                // dcache_data_ready         <= `FALSE;
                // dcache_state              <= CACHE_WRITE_MISS;

                // _ram_waddr_dcache_o       <= mem_addr_i;  // 写地址
                // _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
                // _ram_wmask_dcache_o       <= mem_mask_i;  // 写掩码
                // _ram_wdata_dcache_o       <= mem_wdata_i;  // 写数据
                // _ram_wsize_dcache_o       <= mem_size_i;  //写大小
                // _ram_wlen_dcache_o        <= 8'd0;  // 不突发
              //end
              2'b00,2'b01: begin : read_miss  // TODO 分配 cache，需要考虑脏位
                if (dirty_bit_read) begin  // 需要写回
                  dcache_state <= CACHE_WRITE_BACK;
                  dcache_data_ready <= `FALSE;
                  _ram_waddr_dcache_o <= {dcache_tag_read, cache_line_idx, 6'b0};  // 写地址
                  _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
                  _ram_wmask_dcache_o <= 8'b1111_1111;  // 写掩码
                  _ram_wdata_dcache_o <= dcache_writeback_data;  // 写数据
                  _ram_wsize_dcache_o <= 4'b1000;  //写大小 8byte
                  _ram_wlen_dcache_o <= 8'd7;  // 突发 7 次
                  burst_count <= 0;  // 清空计数器
                end else begin
                  dcache_state              <= CACHE_READ_MISS;
                  dcache_data_ready         <= `FALSE;
                  _ram_raddr_dcache_o       <= {cache_line_tag, cache_line_idx, 6'b0};  // 读地址
                  _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
                  _ram_rmask_dcache_o       <= 8'b1111_1111;  // 读掩码
                  _ram_rsize_dcache_o       <= 4'b1000;  //读大小 8byte
                  _ram_rlen_dcache_o        <= 8'd7;  // 突发 7 次
                  burst_count               <= 0;  // 清空计数器
                end
              end
            endcase
          end else if (mem_addr_valid_i && uncache ) begin : uncache_rw
            // 判断是读还是写
            if (mem_write_valid_i) begin
              dcache_state              <= UNCACHE_WRITE;
              dcache_data_ready         <= `FALSE;
              _ram_waddr_dcache_o       <= mem_addr_i;  // 写地址
              _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
              _ram_wmask_dcache_o       <= mem_mask_i;  // 写掩码
              _ram_wdata_dcache_o       <= mem_wdata_i;  // 写数据
              _ram_wsize_dcache_o       <= mem_size_i;  //写大小
              _ram_wlen_dcache_o        <= 8'd0;  // 不突发
            end else begin
              dcache_state              <= UNCACHE_READ;
              dcache_data_ready         <= `FALSE;
              _ram_raddr_dcache_o       <= mem_addr_i;  // 读地址
              _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
              _ram_rmask_dcache_o       <= mem_mask_i;  // 读掩码
              _ram_rsize_dcache_o       <= mem_size_i;  //读大小
              _ram_rsize_dcache_o       <= mem_size_i;  //写大小
              _ram_rlen_dcache_o        <= 8'd0;  // 不突发
            end

          end else begin
            dcache_data_ready <= `FALSE;
            _ram_raddr_valid_dcache_o <= `FALSE;
            _ram_waddr_valid_dcache_o <= `FALSE;
            dcache_tag_wen <= `FALSE;
            dcache_data_wen <= 0;
            _dirty_bit_write <= `FALSE;
            dcache_wdata_writehit <= 0;
            dcache_write_hit_valid <= `FALSE;  //写信号
          end
        end

        CACHE_READ_MISS: begin
          if (ram_r_handshake) begin  // 在 handshake 时，向 ram 写入数据
            if (burst_count[3:0] == _ram_rlen_dcache_o[3:0]) begin  // 突发传输最后一个数据
              dcache_state              <= CACHE_IDLE;
              dcache_tag_wen            <= `TRUE;  // 写 tag 
              _dirty_bit_write          <= `FALSE;
              _ram_raddr_valid_dcache_o <= `FALSE;  // 传输结束
              burst_count               <= 0;
            end else begin
              burst_count <= burst_count_plus1;
            end
          end
        end

        CACHE_WRITE_MISS: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin

            _ram_waddr_valid_dcache_o <= `FALSE;
            dcache_data_ready <= `TRUE;  // 完成信号
            dcache_state <= CACHE_IDLE;
          end
        end

        CACHE_WRITE_BACK: begin
          if (ram_w_handshake) begin
            if (burst_count == 4'd7) begin  // 收到最后一个写响应
              _ram_waddr_valid_dcache_o <= `FALSE;  // 传输结束

              // 写入 cache 中
              dcache_state              <= CACHE_READ_MISS;
              dcache_data_ready         <= `FALSE;
              _ram_raddr_dcache_o       <= {cache_line_tag, cache_line_idx, 6'b0};  // 读地址
              _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
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
            _ram_raddr_valid_dcache_o <= `FALSE;
            dcache_data_ready         <= `TRUE;  // 完成信号
            uncache_rdata             <= ram_rdata_dcache_i;  // 数据返回
            dcache_state              <= CACHE_IDLE;
          end
        end
        UNCACHE_WRITE: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin
            _ram_waddr_valid_dcache_o <= `FALSE;
            dcache_data_ready         <= `TRUE;  // 完成信号
            dcache_state              <= CACHE_IDLE;
          end
        end
        default: begin
        end
      endcase
    end
  end


  reg [127:0] dcache_wmask_writehit;


  wire [63:0] wmask_bit = {
    {8{mem_mask_i[7]}},
    {8{mem_mask_i[6]}},
    {8{mem_mask_i[5]}},
    {8{mem_mask_i[4]}},
    {8{mem_mask_i[3]}},
    {8{mem_mask_i[2]}},
    {8{mem_mask_i[1]}},
    {8{mem_mask_i[0]}}
  };







  // wire [`XLEN_BUS] _dcache_rdata8 = {56'b0, dcache_line_rdata[blk_addr_reg*8+:8]};
  // wire [`XLEN_BUS] _dcache_rdata16 = {48'b0, dcache_line_rdata[blk_addr_reg*8+:16]};
  // wire [`XLEN_BUS] _dcache_rdata32 = {32'b0, dcache_line_rdata[blk_addr_reg*8+:32]};
  // wire [`XLEN_BUS] _dcache_rdata64 = dcache_line_rdata[blk_addr_reg*8+:64];


  // wire [`XLEN_BUS] _dcache_rdata_o = ({64{mem_size_i[0]}}&_dcache_rdata8)
  //                                  | ({64{mem_size_i[1]}}&_dcache_rdata16)
  //                                  | ({64{mem_size_i[2]}}&_dcache_rdata32)
  //                                  | ({64{mem_size_i[3]}}&_dcache_rdata64);



  wire [127:0] dcache_wmask_readmiss = ~burst_count[0]?{64'b0,64'hffff_ffff_ffff_ffff}:{64'hffff_ffff_ffff_ffff,64'b0};
  wire [127:0] dcache_wdate_readmiss = ~burst_count[0]?{64'b0,ram_rdata_dcache_i}:{ram_rdata_dcache_i,64'b0};

  wire state_readmiss = dcache_state == CACHE_READ_MISS;
  wire state_writehit = dcache_write_hit_valid;
  wire state_writeback = dcache_state == CACHE_WRITE_BACK;

  wire [127:0] dcache_wmask = ({128{state_readmiss}}&dcache_wmask_readmiss)
                            | ({128{state_writehit}}&dcache_wmask_writehit);

  wire [127:0] dcache_wdata = ({128{state_readmiss}}&dcache_wdate_readmiss)
                            | ({128{state_writehit}}&dcache_wdata_writehit);


  wire dcache_wwen = (state_readmiss & ram_r_handshake) | (state_writehit & dcache_data_wen);

  wire dirty_bit_read;
  wire dirty_bit_write = _dirty_bit_write;
  wire [19:0] dcache_tag_read;
  dcache_tag u_dcache_tag (
      .clk              (clk),
      .rst              (rst),
      .dcache_tag_i     (cache_line_tag),   // tag
      .dcache_index_i   (cache_line_idx),   // index
      .write_valid_i    (dcache_tag_wen),   // 写使能
      .dcache_tag_o     (dcache_tag_read),
      .dirty_bit_read_o (dirty_bit_read),
      .dirty_bit_write_i(dirty_bit_write),
      .dcache_hit_o     (dcache_hit)
  );


  wire dcache_allocate_valid = state_readmiss;
  wire dcache_writeback_valid = state_writeback;
  wire [`XLEN_BUS] dcache_rdata;
  wire [`XLEN_BUS] dcache_writeback_data;
  dcache_data u_dcache_data (
      .clk                     (clk),
      .rst                     (rst),
      .dcache_index_i          (cache_line_idx),
      // index
      .dcache_blk_addr_i       (cache_blk_addr),
      .dcache_line_wdata_i     (dcache_wdata),
      .dcache_wmask            (dcache_wmask),
      .dcache_wen_i            (dcache_wwen),
      .burst_count_i           (burst_count[2:0]),
      .dcache_allocate_valid_i (dcache_allocate_valid),
      .dcache_writeback_valid_i(dcache_writeback_valid),
      .dcache_writeback_data_o (dcache_writeback_data),
      .dcache_rdata_o          (dcache_rdata)
  );


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

