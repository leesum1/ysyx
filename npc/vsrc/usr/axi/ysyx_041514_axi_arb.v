`include "sysconfig.v"

// 仲裁模块
module ysyx_041514_axi_arb (
    input clk,
    input rst,

    // if 访存请求端口（读）
    input [`ysyx_041514_NPC_ADDR_BUS] if_read_addr_i,  // if 阶段的 read
    input if_raddr_valid_i,  // 是否发起读请求
    input [7:0] if_rmask_i,  // 数据掩码
    input [3:0] if_rsize_i,  // 数据大小
    input [7:0] if_rlen_i,
    output [`ysyx_041514_XLEN_BUS] if_rdata_o,  // 读数据返回mem
    output if_rdata_ready_o,  // 读数据是否有效
    // mem 访存请求端口（读）
    input [`ysyx_041514_NPC_ADDR_BUS] mem_read_addr_i,  // mem 阶段的 read
    input mem_raddr_valid_i,
    input [7:0] mem_rmask_i,
    input [3:0] mem_rsize_i,  // 数据大小
    input [7:0] mem_rlen_i,
    output [`ysyx_041514_XLEN_BUS] mem_rdata_o,
    output mem_rdata_ready_o,
    input arb_rlast_i,
    // mem 访存请求端口（写）,独占
    input [`ysyx_041514_NPC_ADDR_BUS] mem_write_addr_i,  // mem 阶段的 write
    input mem_write_valid_i,
    input [7:0] mem_wmask_i,
    input [`ysyx_041514_XLEN_BUS] mem_wdata_i,
    input [3:0] mem_wsize_i,  // 数据大小
    input [7:0] mem_wlen_i,
    output mem_wdata_ready_o,  // 数据是否已经写入


    /* arb<-->axi */
    // 读通道
    output [`ysyx_041514_NPC_ADDR_BUS] arb_read_addr_o,
    output arb_raddr_valid_o,  // 是否发起读请求
    output [7:0] arb_rmask_o,  // 数据掩码
    output [3:0] arb_rsize_o,  // 数据大小
    output [7:0] arb_rlen_o,
    input [`ysyx_041514_XLEN_BUS] arb_rdata_i,  // 读数据返回mem
    input arb_rdata_ready_i,  // 读数据是否有效
    //写通道
    output [`ysyx_041514_NPC_ADDR_BUS] arb_write_addr_o,  // mem 阶段的 write
    output arb_write_valid_o,
    output [7:0] arb_wmask_o,
    output [`ysyx_041514_XLEN_BUS] arb_wdata_o,
    output [3:0] arb_wsize_o,  // 数据大小
    output [7:0] arb_wlen_o,
    input arb_wdata_ready_i  // 数据是否已经写入
);



  localparam ARB_IDLE = 2'd0;
  localparam IF_READ_STATE = 2'd1;
  localparam MEM_READ_STATE = 2'd2;

  // 读通道
  reg [`ysyx_041514_NPC_ADDR_BUS]  _arb_read_addr_o;
  reg                              _arb_raddr_valid_o;  // 是否发起读请求
  reg [                      7:0 ] _arb_rmask_o;  // 数据掩码
  reg [                      3:0 ] _arb_rsize_o;
  reg [                      7:0 ] _arb_rlen_o;  // 突发大小


  reg [                      1:0 ] arb_state;

  always @(posedge clk) begin
    if (rst) begin
      arb_state <= ARB_IDLE;
      _arb_read_addr_o <= 0;
      _arb_raddr_valid_o <= 0;
      _arb_rmask_o <= 0;
      _arb_rsize_o <= 0;
      _arb_rlen_o <= 0;
    end else begin
      case (arb_state)
        ARB_IDLE: begin
          if (mem_raddr_valid_i) begin
            arb_state <= MEM_READ_STATE;
            _arb_read_addr_o <= mem_read_addr_i;
            _arb_raddr_valid_o <= mem_raddr_valid_i;
            _arb_rmask_o <= mem_rmask_i;
            _arb_rsize_o <= mem_rsize_i;
            _arb_rlen_o <= mem_rlen_i;
          end else if (if_raddr_valid_i) begin
            arb_state <= IF_READ_STATE;
            _arb_read_addr_o <= if_read_addr_i;
            _arb_raddr_valid_o <= if_raddr_valid_i;
            _arb_rmask_o <= if_rmask_i;
            _arb_rsize_o <= if_rsize_i;
            _arb_rlen_o <= if_rlen_i;
          end
          // if (if_raddr_valid_i) begin
          //   arb_state <= IF_READ_STATE;
          //   _arb_read_addr_o <= if_read_addr_i;
          //   _arb_raddr_valid_o <= if_raddr_valid_i;
          //   _arb_rmask_o <= if_rmask_i;
          //   _arb_rsize_o <= if_rsize_i;
          //   _arb_rlen_o <= if_rlen_i;
          // end else if (mem_raddr_valid_i) begin
          //   arb_state <= MEM_READ_STATE;
          //   _arb_read_addr_o <= mem_read_addr_i;
          //   _arb_raddr_valid_o <= mem_raddr_valid_i;
          //   _arb_rmask_o <= mem_rmask_i;
          //   _arb_rsize_o <= mem_rsize_i;
          //   _arb_rlen_o <= mem_rlen_i;
          // end
        end
        MEM_READ_STATE: begin
          if (arb_rlast_i) begin
            arb_state <= ARB_IDLE;
            _arb_raddr_valid_o <= `ysyx_041514_FALSE;
          end

        end
        IF_READ_STATE: begin
          if (arb_rlast_i) begin
            arb_state <= ARB_IDLE;
            _arb_raddr_valid_o <= `ysyx_041514_FALSE;
          end
        end
        default: begin
        end
      endcase
    end
  end


  wire if_read_state = arb_state == IF_READ_STATE;
  wire mem_read_state = arb_state == MEM_READ_STATE;


  // 读响应
  assign if_rdata_o = (if_read_state) ? arb_rdata_i : 0;
  assign if_rdata_ready_o = (if_read_state) ? arb_rdata_ready_i : `ysyx_041514_FALSE;
  assign mem_rdata_o = (mem_read_state) ? arb_rdata_i : 0;
  assign mem_rdata_ready_o = (mem_read_state) ? arb_rdata_ready_i : `ysyx_041514_FALSE;
  // 写响应
  assign mem_wdata_ready_o = arb_wdata_ready_i;


  // 读
  assign arb_read_addr_o = _arb_read_addr_o;
  assign arb_raddr_valid_o = _arb_raddr_valid_o;
  assign arb_rmask_o = _arb_rmask_o;
  assign arb_rsize_o = _arb_rsize_o;
  assign arb_rlen_o = _arb_rlen_o;
  // 写
  assign arb_write_addr_o = mem_write_addr_i;
  assign arb_write_valid_o = mem_write_valid_i;
  assign arb_wdata_o = mem_wdata_i;
  assign arb_wmask_o = mem_wmask_i;
  assign arb_wsize_o = mem_wsize_i;
  assign arb_wlen_o = mem_wlen_i;

endmodule
