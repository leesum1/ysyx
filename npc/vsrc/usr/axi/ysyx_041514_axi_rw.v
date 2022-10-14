
`include "sysconfig.v"


module ysyx_041514_axi_rw #(
    parameter RW_DATA_WIDTH  = 64,
    parameter RW_ADDR_WIDTH  = 32,
    parameter AXI_DATA_WIDTH = 64,
    parameter AXI_ADDR_WIDTH = 32,
    parameter AXI_ID_WIDTH   = 4,
    parameter AXI_STRB_WIDTH = AXI_DATA_WIDTH / 8,
    parameter AXI_USER_WIDTH = 1
) (
    input clock,
    input reset,

    /* arb<-->axi */
    // 读通道
    input [`ysyx_041514_NPC_ADDR_BUS] arb_read_addr_i,
    input arb_raddr_valid_i,  // 是否发起读请求
    input [7:0] arb_rmask_i,  // 数据掩码
    input [3:0] arb_rsize_i,
    input [7:0] arb_rlen_i,  // 突发传输大小
    output [`ysyx_041514_XLEN_BUS] arb_rdata_o,  // 读数据返回mem
    output arb_rdata_ready_o,  // 读数据是否有效
    output arb_rlast_o,
    //写通道
    input [`ysyx_041514_NPC_ADDR_BUS] arb_write_addr_i,  // mem 阶段的 write
    input arb_write_valid_i,
    input [7:0] arb_wmask_i,
    input [3:0] arb_wsize_i,
    input [7:0] arb_wlen_i,  // 突发传输大小
    input [`ysyx_041514_XLEN_BUS] arb_wdata_i,
    output arb_wdata_ready_o,  // 数据是否已经写入

    /* axi master */
    // Advanced eXtensible Interface
    // 写地址
    input                         axi_aw_ready_i,
    output                        axi_aw_valid_o,
    output [  AXI_ADDR_WIDTH-1:0] axi_aw_addr_o,
    output [                 2:0] axi_aw_prot_o,
    output [    AXI_ID_WIDTH-1:0] axi_aw_id_o,
    output [  AXI_USER_WIDTH-1:0] axi_aw_user_o,
    output [                 7:0] axi_aw_len_o,
    output [                 2:0] axi_aw_size_o,
    output [                 1:0] axi_aw_burst_o,
    output                        axi_aw_lock_o,
    output [                 3:0] axi_aw_cache_o,
    output [                 3:0] axi_aw_qos_o,
    output [                 3:0] axi_aw_region_o,
    //写数据
    input                         axi_w_ready_i,
    output                        axi_w_valid_o,
    output [  AXI_DATA_WIDTH-1:0] axi_w_data_o,
    output [AXI_DATA_WIDTH/8-1:0] axi_w_strb_o,
    output                        axi_w_last_o,
    output [  AXI_USER_WIDTH-1:0] axi_w_user_o,
    //写响应
    output                        axi_b_ready_o,
    input                         axi_b_valid_i,
    input  [                 1:0] axi_b_resp_i,
    input  [    AXI_ID_WIDTH-1:0] axi_b_id_i,
    input  [  AXI_USER_WIDTH-1:0] axi_b_user_i,
    //读地址
    input                         axi_ar_ready_i,
    output                        axi_ar_valid_o,
    output [  AXI_ADDR_WIDTH-1:0] axi_ar_addr_o,
    output [                 2:0] axi_ar_prot_o,
    output [    AXI_ID_WIDTH-1:0] axi_ar_id_o,
    output [  AXI_USER_WIDTH-1:0] axi_ar_user_o,
    output [                 7:0] axi_ar_len_o,
    output [                 2:0] axi_ar_size_o,
    output [                 1:0] axi_ar_burst_o,
    output                        axi_ar_lock_o,
    output [                 3:0] axi_ar_cache_o,
    output [                 3:0] axi_ar_qos_o,
    output [                 3:0] axi_ar_region_o,
    //读数据
    output                        axi_r_ready_o,
    input                         axi_r_valid_i,
    input  [                 1:0] axi_r_resp_i,
    input  [  AXI_DATA_WIDTH-1:0] axi_r_data_i,
    input                         axi_r_last_i,
    input  [    AXI_ID_WIDTH-1:0] axi_r_id_i,
    input  [  AXI_USER_WIDTH-1:0] axi_r_user_i
);
// 寄存器已复位


  //握手信号
  wire axi_ar_handshake = axi_ar_valid_o & axi_ar_ready_i;
  wire axi_aw_handshake = axi_aw_valid_o & axi_aw_ready_i;
  wire axi_r_handshake = axi_r_valid_i & axi_r_ready_o;
  wire axi_w_handshake = axi_w_valid_o & axi_w_ready_i;
  wire axi_b_handshake = axi_b_valid_i & axi_b_ready_o;


  // ------------------State Machine------------------TODO

  /************************ 写通道状态切换 ************************/
  localparam AXI_WSTATE_LEN = 3;
  localparam AXI_WRST = 3'd0;
  localparam AXI_WIDLE = 3'd1;
  localparam AXI_WADDR_WDATA = 3'd2;  // axi4  写地址写数据同时发送
  localparam AXI_WADDR_FINISH_BURST = 3'd3;  // 写地址握手
  localparam AXI_WDATA_VALID_BURST = 3'd4;  // 写数据有效
  localparam AXI_WDATA_HANDSHAKE_BURST = 3'd5;  // 突写数据握手
  localparam AXI_WDATA_FINISH_BURST = 3'd6;  // 突发传输结束


  wire [2:0 ]to_aw_size = ({3{arb_wsize_i[0]}}&`ysyx_041514_AXI_SIZE_BYTES_1)
                             | ({3{arb_wsize_i[1]}}&`ysyx_041514_AXI_SIZE_BYTES_2)
                             | ({3{arb_wsize_i[2]}}&`ysyx_041514_AXI_SIZE_BYTES_4)
                             | ({3{arb_wsize_i[3]}}&`ysyx_041514_AXI_SIZE_BYTES_8);


  reg [AXI_WSTATE_LEN-1:0] axi_wstate;
  reg _arb_wdata_ready_o;

  // 写地址缓存
  reg [`ysyx_041514_NPC_ADDR_BUS] aw_addr;
  reg aw_valid;
  reg [7:0] aw_len;  // 突发长度 Aysyx_041514_XLEN[7:0] + 1,0 表示不突发
  reg [2:0] aw_size;  // 突发大小 = 2^AxSIZE 
  // 写数据缓存
  // reg [`ysyx_041514_XLEN_BUS] w_data;
  reg [7:0] w_strb;
  reg w_valid;
  reg w_last;

  // 写响应缓存
  reg b_ready;


  reg [2:0] burst_count;
  wire [2:0] burst_count_plus1 = burst_count + 1;

  always @(posedge clock) begin
    if (reset) begin
      axi_wstate <= AXI_WRST;
      aw_valid <= `ysyx_041514_FALSE;
      w_valid <= `ysyx_041514_FALSE;
      w_last <= `ysyx_041514_FALSE;
      b_ready <= `ysyx_041514_FALSE;
      w_strb <= 0;
      aw_size <= 0;
      aw_addr <= 0;
      aw_len <= 0;
      burst_count <= 0;
      _arb_wdata_ready_o <= `ysyx_041514_FALSE;
    end else begin
      case (axi_wstate)
        AXI_WRST: begin
          axi_wstate <= AXI_WIDLE;
        end
        AXI_WIDLE: begin
          _arb_wdata_ready_o <= `ysyx_041514_FALSE;
          if (arb_write_valid_i & ~_arb_wdata_ready_o) begin : arb_write
            if (arb_wlen_i == 8'b0) begin  // 不是突发传输，地址和数据一起到
              // 同时写数据和地址
              /* aw 通道 */
              axi_wstate <= AXI_WADDR_WDATA;
              aw_valid <= `ysyx_041514_TRUE;
              aw_addr <= arb_write_addr_i;
              aw_len <= arb_wlen_i;  // 无突发
              aw_size <= to_aw_size;
              /* w 通道 */
              w_valid <= `ysyx_041514_TRUE;
              w_last <= `ysyx_041514_TRUE;  // 只有一个数据
              //对于Narrow Burst，无论是读写请求，数据都出现在[RW]DATA对应访问地址%总线宽度的位置
              // wstrb wdata 与 data bus 的对齐处理在 mem 阶段处理
              w_strb <= arb_wmask_i;
              // w_data <= arb_wdata_i;
              /* b 通道 */
              b_ready <= `ysyx_041514_TRUE;  // 默认为高
            end else begin  // 突发传输，先写地址，再写数据
              /* aw 通道 */
              axi_wstate <= AXI_WADDR_FINISH_BURST;
              aw_valid <= `ysyx_041514_TRUE;
              aw_addr <= arb_write_addr_i;
              aw_len <= arb_wlen_i;  // 突发传输
              aw_size <= to_aw_size;
              /* b 通道 */
              b_ready <= `ysyx_041514_TRUE;  // 默认为高

              burst_count <= 0;
            end
          end else begin
            axi_wstate <= AXI_WIDLE;
            aw_valid <= `ysyx_041514_FALSE;
            w_valid <= `ysyx_041514_FALSE;
            w_last <= `ysyx_041514_FALSE;
          end
        end
        AXI_WADDR_WDATA: begin
          if (axi_aw_handshake) begin
            aw_valid <= `ysyx_041514_FALSE;  // 握手成功后拉低 valid
          end
          if (axi_w_handshake) begin
            w_valid <= `ysyx_041514_FALSE;  // 握手成功后拉低 valid
            w_last  <= `ysyx_041514_FALSE;  // wlast 与 wvalid 一同拉低
          end
          if (axi_b_handshake) begin
            axi_wstate <= AXI_WIDLE;  // 一次写事务结束
            b_ready <= `ysyx_041514_FALSE;  // todo:为低表示一次写事务完毕,测试使用
            _arb_wdata_ready_o <= `ysyx_041514_TRUE;  // 通知 arb 写完成
          end

        end
        AXI_WADDR_FINISH_BURST: begin
          if (axi_aw_handshake) begin
            aw_valid   <= `ysyx_041514_FALSE;  // 握手成功后拉低 valid
            axi_wstate <= AXI_WDATA_VALID_BURST;
          end
        end
        AXI_WDATA_VALID_BURST: begin
          /* w 通道 */
          w_valid <= `ysyx_041514_TRUE;
          w_strb <= arb_wmask_i;  // 第一个数据
          // w_data <= arb_wdata_i;
          _arb_wdata_ready_o <= `ysyx_041514_FALSE;
          if (burst_count == 3'd7) begin  // 最后一个数据，last 有效
            w_last <= `ysyx_041514_TRUE;
          end

          axi_wstate <= AXI_WDATA_HANDSHAKE_BURST;
        end
        AXI_WDATA_HANDSHAKE_BURST: begin
          if (axi_w_handshake) begin
            w_valid <= `ysyx_041514_FALSE;  // 握手成功后拉低 valid
            w_last <= `ysyx_041514_FALSE;
            _arb_wdata_ready_o <= `ysyx_041514_TRUE;  // 通知 arb 写完成
            burst_count <= burst_count_plus1;
            if (w_last) begin
              axi_wstate  <= AXI_WDATA_FINISH_BURST;
              burst_count <= 0;
            end else begin
              axi_wstate <= AXI_WDATA_VALID_BURST;
            end
          end
        end
        AXI_WDATA_FINISH_BURST: begin
          _arb_wdata_ready_o <= `ysyx_041514_FALSE;
          if (axi_b_handshake) begin
            b_ready <= `ysyx_041514_FALSE;
            axi_wstate <= AXI_WIDLE;
          end
        end
        default: begin
          axi_wstate <= AXI_WIDLE;
        end
      endcase
    end
  end

  /************************ 读通道状态切换 ************************/
  localparam AXI_RSTATE_LEN = 3;
  localparam AXI_RRST = 3'd0;
  localparam AXI_RIDLE = 3'd1;
  localparam AXI_RADDR = 3'd2;
  localparam AXI_RDATA = 3'd3;


  wire [2:0 ]to_ar_size = ({3{arb_rsize_i[0]}}&`ysyx_041514_AXI_SIZE_BYTES_1)
                             | ({3{arb_rsize_i[1]}}&`ysyx_041514_AXI_SIZE_BYTES_2)
                             | ({3{arb_rsize_i[2]}}&`ysyx_041514_AXI_SIZE_BYTES_4)
                             | ({3{arb_rsize_i[3]}}&`ysyx_041514_AXI_SIZE_BYTES_8);


  reg [AXI_RSTATE_LEN-1:0] axi_rstate;
  reg _arb_rdata_ready_o;
  reg [`ysyx_041514_XLEN_BUS] _arb_rdata_o;
  reg _arb_rlast_o;

  reg ar_valid;
  reg [AXI_ADDR_WIDTH-1:0] ar_addr;
  reg [2:0] ar_size;  // 突发大小 = 2^AxSIZE 
  reg [7:0] ar_len;  // 突发长度 Aysyx_041514_XLEN[7:0] + 1,0 表示不突发

  reg r_ready;

  always @(posedge clock) begin
    if (reset) begin
      axi_rstate <= AXI_RRST;
      ar_valid <= `ysyx_041514_FALSE;
      ar_addr <= 0;
      ar_len <= 0;
      ar_size <= 0;
      _arb_rlast_o <= 0;
      _arb_rdata_o <= 0;
      r_ready <= `ysyx_041514_FALSE;
      _arb_rdata_ready_o <= `ysyx_041514_FALSE;
    end else begin
      case (axi_rstate)
        AXI_RRST: begin
          axi_rstate <= AXI_RIDLE;
        end
        AXI_RIDLE: begin
          _arb_rdata_ready_o <= `ysyx_041514_FALSE;
          _arb_rlast_o <= 0;
          // arb_raddr_valid_i & ~_arb_rdata_ready_o 为 arb 发出了读请求，且当前周期不为读数据返回周期
          // 当 _arb_rdata_ready_o = `ysyx_041514_TRUE 时，读数据返回，且 下一个读地址在下一个周期才会来到
          // 避免重复度读请求，_arb_rdata_ready_o = `ysyx_041514_TRUE 时，不能发生读请求
          if (arb_raddr_valid_i & ~_arb_rdata_ready_o) begin
            axi_rstate <= AXI_RADDR;
            /* ar 通道 */
            // cache miss 时,或者访问外设时,地址一定时对齐的
            ar_addr <= arb_read_addr_i;
            ar_valid <= `ysyx_041514_TRUE;
            ar_size <= to_ar_size;
            ar_len <= arb_rlen_i;  // 支持突发传输
          end else begin
            axi_rstate <= AXI_RIDLE;
          end
        end
        AXI_RADDR: begin : wait_for_ar_handshake
          if (axi_ar_handshake) begin : wait_for_ar_handshake
            axi_rstate <= AXI_RDATA;
            ar_valid <= `ysyx_041514_FALSE;  // 地址握手成功后拉低
            r_ready <= `ysyx_041514_TRUE;  // 准备接收读数据
          end
        end
        AXI_RDATA: begin  // 支持突发传输
          if (axi_r_handshake) begin : wait_for_r_handshake
            if (axi_r_last_i) begin  // 最后一个数据传输完成
              axi_rstate <= AXI_RIDLE;
              _arb_rlast_o <= `ysyx_041514_TRUE;
              r_ready <= `ysyx_041514_FALSE;  // 数据握手成功后拉低
            end
            _arb_rdata_o <= axi_r_data_i;
            _arb_rdata_ready_o <= `ysyx_041514_TRUE;
          end else begin  // 没有接收到数据
            _arb_rdata_ready_o <= `ysyx_041514_FALSE;
          end
        end
        default: begin
          axi_rstate <= AXI_RIDLE;
        end
      endcase
    end
  end

  /********************类 sram 接口数据返回**************************/

  assign arb_rdata_o = _arb_rdata_o;
  assign arb_rdata_ready_o = _arb_rdata_ready_o;
  assign arb_rlast_o = _arb_rlast_o;
  assign arb_wdata_ready_o = _arb_wdata_ready_o;


  // ------------------Write Transaction------------------

  wire [  AXI_ID_WIDTH-1:0] axi_id = {AXI_ID_WIDTH{1'b0}};
  wire [AXI_USER_WIDTH-1:0] axi_user = {AXI_USER_WIDTH{1'b0}};

  // 写地址通道  ��下没有备注初始化信号的都可能是你需要产生和用到的
  assign axi_aw_valid_o = aw_valid;
  assign axi_aw_addr_o = aw_addr;
  assign axi_aw_prot_o    = `ysyx_041514_AXI_PROT_UNPRIVILEGED_ACCESS | `ysyx_041514_AXI_PROT_SECURE_ACCESS | `ysyx_041514_AXI_PROT_DATA_ACCESS;  //初始化信号即可
  assign axi_aw_id_o = axi_id;  //初始化信号即可
  assign axi_aw_user_o = axi_user;  //初始化信号即可
  assign axi_aw_len_o = aw_len;
  assign axi_aw_size_o = aw_size;
  assign axi_aw_burst_o = `ysyx_041514_AXI_BURST_TYPE_INCR;
  assign axi_aw_lock_o = 1'b0;  //初始化信号即可
  assign axi_aw_cache_o = `ysyx_041514_AXI_AWCACHE_WRITE_BACK_READ_AND_WRITE_ALLOCATE;  //初始化信号即可
  assign axi_aw_qos_o = 4'h0;  //初始化信号即可
  assign axi_aw_region_o = 4'h0;  //初始化信号即可

  // 写数据通道
  assign axi_w_valid_o = w_valid;
  assign axi_w_data_o = arb_wdata_i;  // 直接使用原始数据，不经过寄存器
  assign axi_w_strb_o = w_strb;
  assign axi_w_last_o = w_last;
  assign axi_w_user_o = axi_user;  //初始化信号即可

  // 写应答通道
  assign axi_b_ready_o = b_ready;

  // ------------------Read Transaction------------------



  // Read address channel signals
  assign axi_ar_valid_o = ar_valid;  // leesum
  assign axi_ar_addr_o = ar_addr;  // leesum
  assign axi_ar_prot_o    = `ysyx_041514_AXI_PROT_UNPRIVILEGED_ACCESS | `ysyx_041514_AXI_PROT_SECURE_ACCESS | `ysyx_041514_AXI_PROT_DATA_ACCESS;  //初始化信号即可
  assign axi_ar_id_o = axi_id;  //初始化信号即可                        
  assign axi_ar_user_o = axi_user;  //初始化信号即可
  assign axi_ar_len_o = ar_len;  // leesum
  assign axi_ar_size_o = ar_size;  // leesum
  assign axi_ar_burst_o = `ysyx_041514_AXI_BURST_TYPE_INCR;
  assign axi_ar_lock_o = 1'b0;  //初始化信号即可
  assign axi_ar_cache_o   = `ysyx_041514_AXI_ARCACHE_NORMAL_NON_CACHEABLE_NON_BUFFERABLE;                                 //初始化信号即可
  assign axi_ar_qos_o = 4'h0;  //初始化信号即可
  assign axi_ar_region_o = 4'h0;

  // Read data channel signals
  assign axi_r_ready_o = r_ready;  //leesum

endmodule
