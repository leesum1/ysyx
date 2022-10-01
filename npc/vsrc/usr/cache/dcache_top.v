`include "sysconfig.v"
// 地址位宽 32,dcache<->cpu (数据64位) mem<-->dcache(数据128位)
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

  assign ram_wlen_dcache_o = 0;
  assign ram_rlen_dcache_o = _ram_rlen_dcache_o;

  // uncache 检查

  wire uncache = (mem_addr_i & `MMIO_BASE) == `MMIO_BASE;

  // 块内地址
  wire [3:0] cache_blk_addr = mem_addr_i[3:0];
  // 组号
  wire [8:4] cache_line_idx = mem_addr_i[8:4];
  // TAG 标记 
  wire [31:9] cache_line_tag = mem_addr_i[31:9];


  wire dcache_hit;

  /* cache 命中 */
  localparam CACHE_RST = 4'd0;
  localparam CACHE_IDLE = 4'd1;
  localparam CACHE_READ_HIT = 4'd2;
  localparam CACHE_READ_MISS = 4'd3;
  localparam CACHE_READ_MISS2 = 4'd4;
  localparam CACHE_WRITE_HIT1 = 4'd5;
  localparam CACHE_WRITE_HIT2 = 4'd6;
  localparam CACHE_WRITE_MISS = 4'd7;
  localparam CACHE_WRITE_MISS2 = 4'd8;
  localparam UNCACHE_READ = 4'd9;
  localparam UNCACHE_WRITE = 4'd10;

  reg [3:0] dcahce_state;


  reg [3:0] blk_addr_reg;
  reg [4:0] line_idx_reg;
  reg [22:0] line_tag_reg;
  reg dcache_tag_wen;


  reg dcahce_rdata_ok;
  // cache<-->mem 端口 
  reg [`NPC_ADDR_BUS] _ram_raddr_dcache_o;
  reg _ram_raddr_valid_dcache_o;
  reg [7:0] _ram_rmask_dcache_o;
  reg [3:0] _ram_rsize_dcache_o;

  reg [`NPC_ADDR_BUS] _ram_waddr_dcache_o;
  reg _ram_waddr_valid_dcache_o;
  reg [7:0] _ram_wmask_dcache_o;
  reg [3:0] _ram_wsize_dcache_o;
  reg [7:0] _ram_rlen_dcache_o;
  reg [`XLEN_BUS] _ram_wdata_dcache_o;


  reg [127:0] dcache_wdata_writehit;
  reg [`XLEN_BUS] uncache_rdata;
  reg dcache_data_wen;


  reg [7:0] burst_count;
  wire ram_r_handshake = _ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i;
  wire [7:0] burst_count_plus1 = burst_count + 1;

  always @(posedge clk) begin
    if (rst) begin
      dcahce_state <= CACHE_RST;
      blk_addr_reg <= 0;
      line_idx_reg <= 0;
      line_tag_reg <= 0;
      dcache_tag_wen <= 0;
      dcache_data_wen <= 0;
      dcache_wdata_writehit <= 0;
      _ram_rsize_dcache_o <= 0;
      _ram_wsize_dcache_o <= 0;
      _ram_raddr_valid_dcache_o <= `FALSE;
      _ram_waddr_valid_dcache_o <= `FALSE;

    end else begin
      case (dcahce_state)
        CACHE_RST: begin
          dcahce_state <= CACHE_IDLE;
        end
        CACHE_IDLE: begin
          blk_addr_reg <= cache_blk_addr;
          line_idx_reg <= cache_line_idx;
          line_tag_reg <= cache_line_tag;
          dcache_tag_wen <= `FALSE;
          dcache_data_wen <= 0;
          dcache_wdata_writehit <= 0;
          //dcache_wmask <= 0;
          // cache data 为单端口 ram,不能同时读写, uncache 直接访问内存
          if (mem_addr_valid_i && ~dcache_data_wen && ~uncache && ~dcache_tag_wen) begin
            case ({
              dcache_hit, mem_write_valid_i
            })
              2'b11: begin : write_hit  // 同时写入 cache 和 内存
                dcahce_state              <= CACHE_WRITE_HIT1;
                dcahce_rdata_ok           <= `FALSE;

                // 写内存准备
                _ram_waddr_dcache_o       <= mem_addr_i;  //写地址
                _ram_waddr_valid_dcache_o <= `TRUE;  //地址有效
                _ram_wmask_dcache_o       <= mem_mask_i;  //写掩码
                _ram_wdata_dcache_o       <= mem_wdata_i;  //写数据
                _ram_wsize_dcache_o       <= mem_size_i;  //写大小
                _ram_rlen_dcache_o        <= 8'd0;  // 不突发
              end
              2'b10: begin : read_hit
                dcahce_rdata_ok <= `TRUE;
                dcahce_state <= CACHE_IDLE;
              end
              2'b01: begin : write_miss  // write through and write not allocate,直接写入内存，不分配 cache
                dcahce_rdata_ok           <= `FALSE;
                dcahce_state              <= CACHE_WRITE_MISS;

                _ram_waddr_dcache_o       <= mem_addr_i;  // 写地址
                _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
                _ram_wmask_dcache_o       <= mem_mask_i;  // 写掩码
                _ram_wdata_dcache_o       <= mem_wdata_i;  // 写数据
                _ram_wsize_dcache_o       <= mem_size_i;  //写大小
                _ram_rlen_dcache_o        <= 8'd0;  // 不突发
              end
              2'b00: begin : read_miss  // 分配 cache
                dcahce_state              <= CACHE_READ_MISS;
                dcahce_rdata_ok           <= `FALSE;
                _ram_raddr_dcache_o       <= {cache_line_tag, cache_line_idx, 4'b0};  // 读地址
                _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
                _ram_rmask_dcache_o       <= 8'b1111_1111;  // 读掩码
                _ram_rsize_dcache_o       <= 4'b1000;  //读大小 8byte
                _ram_rlen_dcache_o        <= 8'd1;  // 突发两次
                burst_count               <= 0;  // 清空计数器
              end
            endcase
          end else if (mem_addr_valid_i && uncache) begin : uncache_rw
            // 判断是读还是写
            if (mem_write_valid_i) begin
              dcahce_state <= UNCACHE_WRITE;
              dcahce_rdata_ok <= `FALSE;
              _ram_waddr_dcache_o <= mem_addr_i;  // 写地址
              _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
              _ram_wmask_dcache_o <= mem_mask_i;  // 写掩码
              _ram_wdata_dcache_o <= mem_wdata_i;  // 写数据
              _ram_wsize_dcache_o <= mem_size_i;  //写大小
            end else begin
              dcahce_state <= UNCACHE_READ;
              dcahce_rdata_ok <= `FALSE;
              _ram_raddr_dcache_o <= mem_addr_i;  // 读地址
              _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
              _ram_rmask_dcache_o <= mem_mask_i;  // 读掩码
              _ram_rsize_dcache_o <= mem_size_i;  //读大小
              _ram_rsize_dcache_o <= mem_size_i;  //写大小
            end

          end else begin
            dcahce_rdata_ok <= `FALSE;
            _ram_raddr_valid_dcache_o <= `FALSE;
            _ram_waddr_valid_dcache_o <= `FALSE;
          end
        end

        CACHE_READ_MISS: begin
          if (ram_r_handshake) begin  // 在 handshake 时，向 ram 写入数据
            if (burst_count == _ram_rlen_dcache_o) begin  // 突发传输最后一个数据
              dcahce_state              <= CACHE_IDLE;
              dcache_tag_wen            <= `TRUE;  // 写 tag 
              _ram_raddr_valid_dcache_o <= `FALSE;  // 传输结束
            end else begin
              burst_count <= burst_count_plus1;
            end
          end
        end

        // CACHE_READ_MISS: begin
        //   if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin
        //     dcache_wdata_writehit[63:0] <= ram_rdata_dcache_i;  // 临时保存 cache line 部分数据
        //     _ram_raddr_dcache_o <= {line_tag_reg, line_idx_reg, 4'd8};  // 读地址
        //     dcahce_state <= CACHE_READ_MISS2;
        //   end
        // end
        // CACHE_READ_MISS2: begin
        //   if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin

        //     // 从内存中读取的 cache line 缓存
        //     dcache_wdata_writehit[127:64]   <= ram_rdata_dcache_i;
        //     // tag data 写使能,在下一个周期将 cache line 的数据写入 cache 中
        //     dcache_data_wen           <= `TRUE;
        //     dcache_tag_wen            <= `TRUE;
        //     dcache_wmask              <= ~(128'b0);  // 128 bit 写使能
        //     _ram_raddr_valid_dcache_o <= `FALSE;
        //     dcahce_state              <= CACHE_IDLE;
        //   end
        // end
        CACHE_WRITE_MISS: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin

            _ram_waddr_valid_dcache_o <= `FALSE;
            dcahce_rdata_ok <= `TRUE;  // 完成信号
            dcahce_state <= CACHE_IDLE;
          end
        end

        CACHE_WRITE_HIT1: begin
          // 首先写内存,等待写内存结束
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin
            _ram_waddr_valid_dcache_o <= `FALSE;
            dcahce_state <= CACHE_IDLE;
          end
          dcache_wdata_writehit <= (mem_addr_i[3]) ? {mem_wdata_i, 64'b0} : {64'b0, mem_wdata_i};
          // 再写 cache
          dcache_data_wen <= `TRUE;
          dcahce_rdata_ok <= `TRUE;  // 完成信号
          dcache_wmask_writehit <= (mem_addr_i[3]) ? {wmask_bit, 64'b0} : {64'b0, wmask_bit};
        end
        UNCACHE_READ: begin
          if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin
            _ram_raddr_valid_dcache_o <= `FALSE;
            dcahce_rdata_ok           <= `TRUE;  // 完成信号
            uncache_rdata             <= ram_rdata_dcache_i;  // 数据返回
            dcahce_state              <= CACHE_IDLE;
          end
        end
        UNCACHE_WRITE: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin
            _ram_waddr_valid_dcache_o <= `FALSE;
            dcahce_rdata_ok           <= `TRUE;  // 完成信号
            dcahce_state              <= CACHE_IDLE;
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







  wire [`XLEN_BUS] _dcache_rdata8 = {56'b0, dcache_line_rdata[blk_addr_reg*8+:8]};
  wire [`XLEN_BUS] _dcache_rdata16 = {48'b0, dcache_line_rdata[blk_addr_reg*8+:16]};
  wire [`XLEN_BUS] _dcache_rdata32 = {32'b0, dcache_line_rdata[blk_addr_reg*8+:32]};
  wire [`XLEN_BUS] _dcache_rdata64 = dcache_line_rdata[blk_addr_reg*8+:64];

  
  wire [`XLEN_BUS] _dcache_rdata_o = ({64{mem_size_i[0]}}&_dcache_rdata8)
                                   | ({64{mem_size_i[1]}}&_dcache_rdata16)
                                   | ({64{mem_size_i[2]}}&_dcache_rdata32)
                                   | ({64{mem_size_i[3]}}&_dcache_rdata64);



  wire [127:0] dcache_wmask_readmiss = ~burst_count[0]?{64'b0,64'hffff_ffff_ffff_ffff}:{64'hffff_ffff_ffff_ffff,64'b0};
  wire [127:0] dcache_wdate_readmiss = ~burst_count[0]?{64'b0,ram_rdata_dcache_i}:{ram_rdata_dcache_i,64'b0};

  wire state_readmiss = dcahce_state == CACHE_READ_MISS;
  wire state_writehit = dcahce_state == CACHE_WRITE_HIT1;

  wire [127:0] dcache_wmask = ({128{state_readmiss}}&dcache_wmask_readmiss)
                            | ({128{state_writehit}}&dcache_wmask_writehit);
  wire [127:0] dcache_wdata = ({128{state_readmiss}}&dcache_wdate_readmiss)
                            | ({128{state_writehit}}&dcache_wdata_writehit);
  wire dcache_wwen = (state_readmiss & ram_r_handshake) | (state_writehit & dcache_data_wen);

  dcache_tag u_dcache_tag (
      .clk           (clk),
      .rst           (rst),
      .dcache_tag_i  (cache_line_tag),
      // tag
      .dcache_index_i(cache_line_idx),
      // index
      .write_valid_i (dcache_tag_wen),
      // 写使能
      .dcache_hit_o  (dcache_hit)
  );




  wire [127:0] dcache_line_rdata;

  dcache_data u_dcache_data (
      .clk                (clk),
      .rst                (rst),
      .dcache_index_i     (cache_line_idx),
      // index
      .dcache_blk_addr_i  (cache_blk_addr),
      .dcache_line_wdata_i(dcache_wdata),
      .dcache_wmask       (dcache_wmask),
      .dcache_wen_i       (dcache_wwen),
      .dcache_line_rdata_o(dcache_line_rdata)
  );





  assign mem_rdata_o = (uncache) ? uncache_rdata : _dcache_rdata_o;

  assign mem_data_ready_o = dcahce_rdata_ok && (dcahce_state == CACHE_IDLE);

  assign ram_raddr_dcache_o = _ram_raddr_dcache_o;
  assign ram_raddr_valid_dcache_o = _ram_raddr_valid_dcache_o;
  assign ram_rmask_dcache_o = _ram_rmask_dcache_o;
  assign ram_rsize_dcache_o = _ram_rsize_dcache_o;


  assign ram_waddr_dcache_o = _ram_waddr_dcache_o;
  assign ram_waddr_valid_dcache_o = _ram_waddr_valid_dcache_o;
  assign ram_wmask_dcache_o = _ram_wmask_dcache_o;
  assign ram_wdata_dcache_o = _ram_wdata_dcache_o;
  assign ram_wsize_dcache_o = _ram_wsize_dcache_o;

endmodule

