`include "sysconfig.v"


module ysyx_041514_data_buff (
    input clk,
    input rst,
    input [5:0] flush_i,
    input [5:0] stall_i,

    /* 乘法器数据缓存 */
    input [`ysyx_041514_XLEN_BUS] alu_data_i,
    input alu_data_ready_i,
    output alu_data_buff_valid_o,
    output [`ysyx_041514_XLEN_BUS] alu_data_buff_o,

    /* fencei ready 缓存 */
    input  mem_fencei_ready_i,
    output mem_fencei_ready_buff_o,
    output mem_fencei_buff_valid_o,

    /* mem 读数据缓存 */
    input                          mem_data_ready_i,
    input  [`ysyx_041514_XLEN-1:0] mem_data_mem_i,      //访存阶段的数据
    output                         rdata_buff_valid_o,
    output [`ysyx_041514_XLEN_BUS] rdata_buff_o
);
// 寄存器已复位

  reg [`ysyx_041514_XLEN_BUS] alu_data_buff;
  reg alu_data_buff_valid;

  always @(posedge clk) begin
    if (rst) begin
      alu_data_buff_valid <= `ysyx_041514_FALSE;
      alu_data_buff <= 'b0;
    end else if (alu_data_ready_i&stall_i[`ysyx_041514_CTRLBUS_ID_EX]) begin  // 接收到数据时，缓存起来
      alu_data_buff_valid <= `ysyx_041514_TRUE;  // 缓存数据有效
      alu_data_buff       <= alu_data_i;  // 记录读取的数据
    end else if ((~stall_i[`ysyx_041514_CTRLBUS_ID_EX])&alu_data_buff_valid) begin  // mem 阶段 stall 时，保持缓存不变
      alu_data_buff_valid <= `ysyx_041514_FALSE;  // 流水线不阻塞，缓存清空
      alu_data_buff <= 'b0;
    end
    // else 保持不变
  end
  assign alu_data_buff_o = alu_data_buff;
  assign alu_data_buff_valid_o = alu_data_buff_valid;




  reg [`ysyx_041514_XLEN_BUS] rdata_buff;
  reg rdata_buff_valid;

  always @(posedge clk) begin
    if (rst) begin
      rdata_buff_valid <= `ysyx_041514_FALSE;
      rdata_buff <= 'b0;

    end else if (mem_data_ready_i & stall_i[`ysyx_041514_CTRLBUS_EX_MEM]) begin  // 接收到数据时，缓存起来
      rdata_buff_valid <= `ysyx_041514_TRUE;  // 缓存数据有效
      rdata_buff       <= mem_data_mem_i;  // 记录读取的数据
    end else if ((~stall_i[`ysyx_041514_CTRLBUS_EX_MEM])&rdata_buff_valid) begin  // mem 阶段 stall 时，保持缓存不变
      rdata_buff_valid <= `ysyx_041514_FALSE;  // 流水线不阻塞，缓存清空
      rdata_buff <= 'b0;
    end
    // else 保持不变
  end

  assign rdata_buff_valid_o = rdata_buff_valid;
  assign rdata_buff_o = rdata_buff;


  reg mem_fencei_ready_buff;
  reg mem_fencei_buff_valid;

  always @(posedge clk) begin
    if (rst) begin
      mem_fencei_buff_valid <= `ysyx_041514_FALSE;
      mem_fencei_ready_buff <= 'b0;

    end else if (mem_fencei_ready_i & stall_i[`ysyx_041514_CTRLBUS_EX_MEM]) begin  // 1. 接收到数据，且 mem 阶段 stall 时，缓存数据
      mem_fencei_buff_valid <= `ysyx_041514_TRUE;  // 缓存数据有效
      mem_fencei_ready_buff <= mem_fencei_ready_i;  // 记录读取的数据
    end else if ((~stall_i[`ysyx_041514_CTRLBUS_EX_MEM])&mem_fencei_buff_valid) begin  // 2. mem 阶段不是 stall 时，清空缓存
      mem_fencei_buff_valid <= `ysyx_041514_FALSE;  // 流水线不阻塞，缓存清空
      mem_fencei_ready_buff <= 'b0;
    end
    // else 保持不变
  end

  assign mem_fencei_ready_buff_o = mem_fencei_ready_buff;
  assign mem_fencei_buff_valid_o = mem_fencei_buff_valid;





endmodule
