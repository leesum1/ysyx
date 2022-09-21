`include "sysconfig.v"

// 仲裁模块
module axi_arb (

    // if 访存请求端口（读）
    input [`NPC_ADDR_BUS] if_read_addr_i,  // if 阶段的 read
    input if_raddr_valid_i,  // 是否发起读请求
    input [7:0] if_rmask_i,  // 数据掩码
    input [3:0] if_rsize_i,  // 数据大小
    output [`XLEN_BUS] if_rdata_o,  // 读数据返回mem
    output if_rdata_ready_o,  // 读数据是否有效
    // mem 访存请求端口（读）
    input [`NPC_ADDR_BUS] mem_read_addr_i,  // mem 阶段的 read
    input mem_raddr_valid_i,
    input [7:0] mem_rmask_i,
    input [3:0] mem_rsize_i,  // 数据大小
    output [`XLEN_BUS] mem_rdata_o,
    output mem_rdata_ready_o,
    // mem 访存请求端口（写）,独占
    input [`NPC_ADDR_BUS] mem_write_addr_i,  // mem 阶段的 write
    input mem_write_valid_i,
    input [7:0] mem_wmask_i,
    input [`XLEN_BUS] mem_wdata_i,
    input [3:0] mem_wsize_i,  // 数据大小
    output mem_wdata_ready_o,  // 数据是否已经写入


    /* arb<-->axi */
    // 读通道
    output [`NPC_ADDR_BUS] arb_read_addr_o,
    output arb_raddr_valid_o,  // 是否发起读请求
    output [7:0] arb_rmask_o,  // 数据掩码
    output [3:0] arb_rsize_o,  // 数据大小
    input [`XLEN_BUS] arb_rdata_i,  // 读数据返回mem
    input arb_rdata_ready_i,  // 读数据是否有效
    //写通道
    output [`NPC_ADDR_BUS] arb_write_addr_o,  // mem 阶段的 write
    output arb_write_valid_o,
    output [7:0] arb_wmask_o,
    output [`XLEN_BUS] arb_wdata_o,
    output [3:0] arb_wsize_o,  // 数据大小
    input arb_wdata_ready_i  // 数据是否已经写入
);

  reg if_read_state, mem_read_state;

  // 读通道
  reg [`NPC_ADDR_BUS]  _arb_read_addr_o;
  reg                  _arb_raddr_valid_o;  // 是否发起读请求
  reg [          7:0 ] _arb_rmask_o;  // 数据掩码
  reg [          3:0 ] _arb_rsize_o;



  always @(*) begin
    if (if_raddr_valid_i) begin : if_read
      if_read_state = `TRUE;
      mem_read_state = `FALSE;

      _arb_read_addr_o = if_read_addr_i;
      _arb_raddr_valid_o = if_raddr_valid_i;
      _arb_rmask_o = if_rmask_i;
      _arb_rsize_o = if_rsize_i;
    end else if (mem_raddr_valid_i) begin : mem_read
      if_read_state = `FALSE;
      mem_read_state = `TRUE;

      _arb_read_addr_o = mem_read_addr_i;
      _arb_raddr_valid_o = mem_raddr_valid_i;
      _arb_rmask_o = mem_rmask_i;
      _arb_rsize_o = mem_rsize_i;
    end else begin
      if_read_state = `FALSE;
      mem_read_state = `FALSE;

      _arb_read_addr_o = 0;
      _arb_raddr_valid_o = 0;
      _arb_rmask_o = 0;
      _arb_rsize_o = 0;
    end
  end


  // 读
  assign if_rdata_o = (if_read_state) ? arb_rdata_i : 0;
  assign if_rdata_ready_o = (if_read_state) ? arb_rdata_ready_i : `FALSE;
  assign mem_rdata_o = (mem_read_state) ? arb_rdata_i : 0;
  assign mem_rdata_ready_o = (mem_read_state) ? arb_rdata_ready_i : `FALSE;
  // 写
  assign mem_wdata_ready_o = arb_wdata_ready_i;


  assign arb_read_addr_o = _arb_read_addr_o;
  assign arb_raddr_valid_o = _arb_raddr_valid_o;
  assign arb_rmask_o = _arb_rmask_o;
  assign arb_rsize_o = _arb_rsize_o;

  assign arb_write_addr_o = mem_write_addr_i;
  assign arb_write_valid_o = mem_write_valid_i;
  assign arb_wdata_o = mem_wdata_i;
  assign arb_wmask_o = mem_wmask_i;
  assign arb_wsize_o = mem_wsize_i;

endmodule
