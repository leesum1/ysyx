`include "sysconfig.v"


module data_buff (
    input clk,
    input rst,
    input [5:0] flush_i,
    input [5:0] stall_i,

    /* 乘法器数据缓存 */
    input [`XLEN_BUS] alu_data_i,
    input alu_data_ready_i,
    output alu_data_buff_valid_o,
    output [`XLEN_BUS] alu_data_buff_o
);


  reg [`XLEN_BUS] alu_data_buff;
  reg alu_data_buff_valid;

  always @(posedge clk) begin
    if (rst) begin
      alu_data_buff_valid <= `FALSE;
      alu_data_buff <= 'b0;
    end else if (alu_data_ready_i&stall_i[`CTRLBUS_ID_EX]) begin  // 接收到数据时，缓存起来
      alu_data_buff_valid <= `TRUE;  // 缓存数据有效
      alu_data_buff       <= alu_data_i;  // 记录读取的数据
    end else if ((~stall_i[`CTRLBUS_ID_EX])&alu_data_buff_valid) begin  // mem 阶段 stall 时，保持缓存不变
      alu_data_buff_valid <= `FALSE;  // 流水线不阻塞，缓存清空
      alu_data_buff <= 'b0;
    end
    // else 保持不变
  end
  assign alu_data_buff_o = alu_data_buff;
  assign alu_data_buff_valid_o = alu_data_buff_valid;

endmodule
