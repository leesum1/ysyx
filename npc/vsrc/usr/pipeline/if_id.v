`include "sysconfig.v"

module if_id (
    input clk,
    input rst,
    //指令地址
    input wire [`XLEN-1:0] pc_if_i,
    //指令内容
    input wire [`INST_LEN-1:0] inst_data_if_i,
    //指令地址
    output wire [`XLEN-1:0] pc_if_id_o,
    //指令内容
    output wire [`INST_LEN-1:0] inst_data_if_id_o
);


  /* pc_if_i 寄存器 */
  wire [`XLEN-1:0] _pc_if_id_d = pc_if_i;
  reg [`XLEN-1:0] _pc_if_id_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_pc_if_id (
      .clk (clk),
      .rst (rst),
      .din (_pc_if_id_d),
      .dout(_pc_if_id_q),
      .wen (1'b0)
  );
  assign pc_if_id_o = _pc_if_id_q;

  /* inst_data_if_i 寄存器 */
  wire [`INST_LEN-1:0] _inst_data_if_id_d = inst_data_if_i;
  reg [`INST_LEN-1:0] _inst_data_if_id_q;
  regTemplate #(
      .WIDTH    (`INST_LEN),
      .RESET_VAL(`INST_LEN'b0)  //TODO:默认值未设置
  ) u_inst_data_if_id (
      .clk (clk),
      .rst (rst),
      .din (_inst_data_if_id_d),
      .dout(_inst_data_if_id_q),
      .wen (1'b0)
  );
  assign inst_data_if_id_o = _inst_data_if_id_q;


endmodule
