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
    input                  ram_rdata_ready_dcache_i,
    input  [    `XLEN_BUS] ram_rdata_dcache_i,
    // 写端口
    output [`NPC_ADDR_BUS] ram_waddr_dcache_o,        // 地址
    output                 ram_waddr_valid_dcache_o,  // 地址是否准备好
    output [          7:0] ram_wmask_dcache_o,        // 数据掩码,写入多少位
    input                  ram_wdata_ready_dcache_i,  // 数据是否已经写入
    output [    `XLEN_BUS] ram_wdata_dcache_o         // 写入的数据
);

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

  reg [`NPC_ADDR_BUS] _ram_waddr_dcache_o;
  reg _ram_waddr_valid_dcache_o;
  reg [7:0] _ram_wmask_dcache_o;
  reg [`XLEN_BUS] _ram_wdata_dcache_o;


  reg [127:0] cache_line_temp;
  reg [`XLEN_BUS] uncache_rdata;
  reg dcache_data_wen;


  always @(posedge clk) begin
    if (rst) begin
      dcahce_state <= CACHE_RST;
      blk_addr_reg <= 0;
      line_idx_reg <= 0;
      line_tag_reg <= 0;
      dcache_tag_wen <= 0;
      dcache_data_wen <= 0;
      cache_line_temp <= 0;
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
          cache_line_temp <= 0;
          dcache_wmask <= 0;
          // cache data 为单端口 ram,不能同时读写, uncache 直接访问内存
          if (mem_addr_valid_i && ~dcache_data_wen && ~uncache) begin
            case ({
              dcache_hit, mem_write_valid_i
            })
              2'b11: begin : write_hit  // 同时写入 cache 和 内存
                dcahce_state <= CACHE_WRITE_HIT1;
                dcahce_rdata_ok <= `FALSE;

                // 写内存准备
                _ram_waddr_dcache_o <= mem_addr_i;  // 写地址
                _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
                _ram_wmask_dcache_o <= mem_mask_i;  // 写掩码
                _ram_wdata_dcache_o <= mem_wdata_i;  // 写数据
              end
              2'b10: begin : read_hit
                dcahce_rdata_ok <= `TRUE;
                dcahce_state <= CACHE_IDLE;
              end
              2'b01: begin : write_miss  // write through and write not allocate,直接写入内存，不分配 cache
                dcahce_rdata_ok <= `FALSE;
                dcahce_state <= CACHE_WRITE_MISS;

                _ram_waddr_dcache_o <= mem_addr_i;  // 写地址
                _ram_waddr_valid_dcache_o <= `TRUE;  // 地址有效
                _ram_wmask_dcache_o <= mem_mask_i;  // 写掩码
                _ram_wdata_dcache_o <= mem_wdata_i;  // 写数据
              end
              2'b00: begin : read_miss  // 分配 cache
                dcahce_state <= CACHE_READ_MISS;
                dcahce_rdata_ok <= `FALSE;
                _ram_raddr_dcache_o <= {cache_line_tag, cache_line_idx, 4'b0};  // 读地址
                _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
                _ram_rmask_dcache_o <= 8'b1111_1111;  // 读掩码
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
            end else begin
              dcahce_state <= UNCACHE_READ;
              dcahce_rdata_ok <= `FALSE;
              _ram_raddr_dcache_o <= mem_addr_i;  // 读地址
              _ram_raddr_valid_dcache_o <= `TRUE;  // 地址有效
              _ram_rmask_dcache_o <= mem_mask_i;  // 读掩码
            end

          end else begin
            dcahce_rdata_ok <= `FALSE;
            _ram_raddr_valid_dcache_o <= `FALSE;
            _ram_waddr_valid_dcache_o <= `FALSE;
          end
        end
        CACHE_READ_MISS: begin
          if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin
            cache_line_temp[63:0] <= ram_rdata_dcache_i;  // 临时保存 cache line 部分数据
            _ram_raddr_dcache_o <= {line_tag_reg, line_idx_reg, 4'd8};  // 读地址
            dcahce_state <= CACHE_READ_MISS2;
          end
        end
        CACHE_READ_MISS2: begin
          if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin

            // 从内存中读取的 cache line 缓存
            cache_line_temp[127:64] <= ram_rdata_dcache_i;
            // tag data 写使能,在下一个周期将 cache line 的数据写入 cache 中
            dcache_data_wen <= `TRUE;
            dcache_tag_wen <= `TRUE;
            dcache_wmask <= dcache_wmask_temp;
            _ram_raddr_valid_dcache_o <= `FALSE;
            dcahce_state <= CACHE_IDLE;
          end
        end
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
            // 移动到对应位置上去
            cache_line_temp <= (mem_addr_i[3]) ? {{mem_wdata_i<<{addr_last3,3'b0}}, 64'b0} : {64'b0, {mem_wdata_i<<{addr_last3,3'b0}}};
            // 再写 cache
            dcache_data_wen <= `TRUE;
            dcahce_rdata_ok <= `TRUE;  // 完成信号
            dcache_wmask <= dcache_wmask_temp;
            dcahce_state <= CACHE_IDLE;
          end
        end
        UNCACHE_READ: begin
          if (_ram_raddr_valid_dcache_o & ram_rdata_ready_dcache_i) begin
            _ram_raddr_valid_dcache_o <= `FALSE;
            dcahce_rdata_ok <= `TRUE;  // 完成信号
            uncache_rdata <= ram_rdata_dcache_i;
            dcahce_state <= CACHE_IDLE;
          end
        end
        UNCACHE_WRITE: begin
          if (_ram_waddr_valid_dcache_o & ram_wdata_ready_dcache_i) begin
            _ram_waddr_valid_dcache_o <= `FALSE;
            dcahce_rdata_ok <= `TRUE;  // 完成信号
            dcahce_state <= CACHE_IDLE;
          end
        end
        default: begin
        end
      endcase
    end
  end

  reg [127:0] dcache_wmask_temp;
  reg [127:0] dcache_wmask;

  always @(*) begin
    if (mem_write_valid_i) begin
      dcache_wmask_temp = (mem_addr_i[3]) ? {wmask_bit, 64'b0} : {64'b0, wmask_bit};
    end else begin
      dcache_wmask_temp = 128'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
    end
  end

  reg [63:0] wmask_bit;
  wire [2:0] addr_last3 = mem_addr_i[2:0];

  // wire w_1byte = (mem_mask_i == 8'b0000_0001);
  // wire w_2byte = (mem_mask_i == 8'b0000_0011);
  // wire w_4byte = (mem_mask_i == 8'b0000_1111);
  // wire w_8byte = (mem_mask_i == 8'b1111_1111);
  always @(*) begin
    case (mem_mask_i)
      8'b0000_0001: begin
        case (addr_last3)
          3'd0: wmask_bit = 64'h0000_0000_0000_00ff;
          3'd1: wmask_bit = 64'h0000_0000_0000_ff00;
          3'd2: wmask_bit = 64'h0000_0000_00ff_0000;
          3'd3: wmask_bit = 64'h0000_0000_ff00_0000;
          3'd4: wmask_bit = 64'h0000_00ff_0000_0000;
          3'd5: wmask_bit = 64'h0000_ff00_0000_0000;
          3'd6: wmask_bit = 64'h00ff_0000_0000_0000;
          3'd7: wmask_bit = 64'hff00_0000_0000_0000;
        endcase
      end
      8'b0000_0011: begin
        case (addr_last3)
          3'd0: wmask_bit = 64'h0000_0000_0000_ffff;
          3'd2: wmask_bit = 64'h0000_0000_ffff_0000;
          3'd4: wmask_bit = 64'h0000_ffff_0000_0000;
          3'd6: wmask_bit = 64'hffff_0000_0000_0000;
          default: wmask_bit = 64'h0000_0000_0000_0000;
        endcase
      end
      8'b0000_1111: begin
        // case (addr_last3)
        //   3'd0: wmask_bit = 64'h0000_0000_ffff_ffff;
        //   3'd4: wmask_bit = 64'hffff_ffff_0000_0000;
        //   default: wmask_bit = 64'h0000_0000_0000_0000;
        // endcase
        wmask_bit = (mem_addr_i % 8 == 0) ? 64'h0000_0000_ffff_ffff : 64'hffff_ffff_0000_0000;
      end
      8'b1111_1111: begin
        case (addr_last3)
          3'd0: wmask_bit = 64'hffff_ffff_ffff_ffff;
          default: wmask_bit = 64'h0000_0000_0000_0000;
        endcase
      end
      default: begin
        wmask_bit = 64'h0000_0000_0000_0000;
      end
    endcase
  end


  //dcache_data <= {32'b0, cache_line_regs[cache_line_idx][cache_blk_addr*8+:32]};
  // wire [`XLEN_BUS] _dcache_data_o = {32'b0, dcache_line_rdata[blk_addr_reg*8+:32]};

  reg [`XLEN_BUS] _dcache_data_o;
  always @(*) begin
    case (mem_mask_i)
      8'b0000_0001: begin
        _dcache_data_o = {56'b0, dcache_line_rdata[blk_addr_reg*8+:8]};
      end
      8'b0000_0011: begin
        _dcache_data_o = {48'b0, dcache_line_rdata[blk_addr_reg*8+:16]};
      end
      8'b0000_1111: begin
        _dcache_data_o = {32'b0, dcache_line_rdata[blk_addr_reg*8+:32]};
      end
      8'b1111_1111: begin
        _dcache_data_o = dcache_line_rdata[blk_addr_reg*8+:64];
      end
      default: begin
        _dcache_data_o = 0;
      end
    endcase
  end







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
      .dcache_line_wdata_i(cache_line_temp),
      .dcache_wmask       (dcache_wmask),
      .dcache_wen_i       (dcache_data_wen),
      .dcache_line_rdata_o(dcache_line_rdata)
  );






  // assign mem_rdata_o = _dcache_data_o & {64{mem_data_ready_o}};
  assign mem_rdata_o = (uncache) ? uncache_rdata : _dcache_data_o;

  assign mem_data_ready_o = dcahce_rdata_ok && (dcahce_state == CACHE_IDLE);

  assign ram_raddr_dcache_o = _ram_raddr_dcache_o;
  assign ram_raddr_valid_dcache_o = _ram_raddr_valid_dcache_o;
  assign ram_rmask_dcache_o = _ram_rmask_dcache_o;


  assign ram_waddr_dcache_o = _ram_waddr_dcache_o;
  assign ram_waddr_valid_dcache_o = _ram_waddr_valid_dcache_o;
  assign ram_wmask_dcache_o = _ram_wmask_dcache_o;
  assign ram_wdata_dcache_o = _ram_wdata_dcache_o;

  // output [`NPC_ADDR_BUS] ram_waddr_dcache_o,        // 地址
  // output                 ram_waddr_valid_dcache_o,  // 地址是否准备好
  // output [          7:0] ram_wmask_dcache_o,        // 数据掩码,写入多少位
  // input                  ram_wdata_ready_dcache_i,  // 数据是否已经写入
  // output [    `XLEN_BUS] ram_wdata_dcache_o         // 写入的数据


endmodule

