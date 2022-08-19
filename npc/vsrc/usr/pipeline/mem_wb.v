`include "sysconfig.v"

module mem_wb (
    input clk,
    input rst,
    //指令地址
    input wire [`XLEN-1:0] pc_mem_wb_i,
    //指令内容
    input wire [`INST_LEN-1:0] inst_data_mem_wb_i,

    input [`XLEN-1:0] exc_alu_data_mem_wb_i,  //执行阶段的数据
    input [`XLEN-1:0] mem_data_mem_wb_i,      //访存阶段的数据
    input             load_valid_mem_wb_i,    //是否是访存阶段的数据

    //指令地址
    output wire [    `XLEN-1:0] pc_mem_wb_o,
    //指令内容
    output wire [`INST_LEN-1:0] inst_data_mem_wb_o,
    output      [    `XLEN-1:0] exc_alu_data_mem_wb_o,  //执行阶段的数据
    output      [    `XLEN-1:0] mem_data_mem_wb_o,      //访存阶段的数据
    output                      load_valid_mem_wb_o     //是否是访存阶段的数据
);


  /* pc寄存器 */
  wire [`XLEN-1:0] _pc_mem_wb_d = pc_mem_wb_i;
  reg [`XLEN-1:0] _pc_mem_wb_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_pc_mem_wb (
      .clk (clk),
      .rst (rst),
      .din (_pc_mem_wb_d),
      .dout(_pc_mem_wb_q),
      .wen (1'b1)
  );
  assign pc_mem_wb_o = _pc_mem_wb_q;

  /* inst_data寄存器 */
  wire [`INST_LEN-1:0] _inst_data_mem_wb_d = inst_data_mem_wb_i;
  reg [`INST_LEN-1:0] _inst_data_mem_wb_q;
  regTemplate #(
      .WIDTH    (`INST_LEN),
      .RESET_VAL(`INST_LEN'b0)  //TODO:默认值未设置
  ) u_inst_data_mem_wb (
      .clk (clk),
      .rst (rst),
      .din (_inst_data_mem_wb_d),
      .dout(_inst_data_mem_wb_q),
      .wen (1'b1)
  );
  assign inst_data_mem_wb_o = _inst_data_mem_wb_q;


  /* exc_alu_data寄存器 */
  wire [`XLEN-1:0] _exc_alu_data_mem_wb_d = exc_alu_data_mem_wb_i;
  reg [`XLEN-1:0] _exc_alu_data_mem_wb_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_exc_alu_data_mem_wb (
      .clk (clk),
      .rst (rst),
      .din (_exc_alu_data_mem_wb_d),
      .dout(_exc_alu_data_mem_wb_q),
      .wen (1'b1)
  );
  assign exc_alu_data_mem_wb_o = _exc_alu_data_mem_wb_q;

  /* mem_data寄存器 */
  wire [`XLEN-1:0] _mem_data_mem_wb_d = mem_data_mem_wb_i;
  reg [`XLEN-1:0] _mem_data_mem_wb_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_mem_data_mem_wb (
      .clk (clk),
      .rst (rst),
      .din (_mem_data_mem_wb_d),
      .dout(_mem_data_mem_wb_q),
      .wen (1'b1)
  );
  assign mem_data_mem_wb_o = _mem_data_mem_wb_q;


  /* load_valid寄存器 */
  wire _load_valid_mem_wb_d = load_valid_mem_wb_i;
  reg _load_valid_mem_wb_q;
  regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(1'b0)  //TODO:默认值未设置
  ) u_load_valid_mem_wb (
      .clk (clk),
      .rst (rst),
      .din (_load_valid_mem_wb_d),
      .dout(_load_valid_mem_wb_q),
      .wen (1'b1)
  );
  assign load_valid_mem_wb_o = _load_valid_mem_wb_q;



endmodule
