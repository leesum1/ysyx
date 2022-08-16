`include "sysconfig.v"

module ex_mem (
    input clk,
    input rst,

    input wire [    `XLEN-1:0] pc_ex_mem_i,
    input wire [`INST_LEN-1:0] inst_data_ex_mem_i,
    input      [    `XLEN-1:0] exc_alu_data_ex_mem_i,
    input      [    `XLEN-1:0] exc_csr_data_ex_mem_i,
    input                      exc_csr_valid_ex_mem_i,


    output wire [    `XLEN-1:0] pc_ex_mem_o,
    output wire [`INST_LEN-1:0] inst_data_ex_mem_o,
    output      [    `XLEN-1:0] exc_alu_data_ex_mem_o,
    output      [    `XLEN-1:0] exc_csr_data_ex_mem_o,
    output                      exc_csr_valid_ex_mem_o
);

  /* pc 寄存器 */
  wire [`XLEN-1:0] _pc_ex_mem_d = pc_ex_mem_i;
  reg [`XLEN-1:0] _pc_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_pc_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_pc_ex_mem_d),
      .dout(_pc_ex_mem_q),
      .wen (1'b1)
  );
  assign pc_ex_mem_o = _pc_ex_mem_q;


  /* inst_data 寄存器 */
  wire [`INST_LEN-1:0] _inst_data_ex_mem_d = inst_data_ex_mem_i;
  reg [`INST_LEN-1:0] _inst_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`INST_LEN),
      .RESET_VAL(`INST_LEN'b0)  //TODO:默认值未设置
  ) u_inst_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_inst_data_ex_mem_d),
      .dout(_inst_data_ex_mem_q),
      .wen (1'b1)
  );
  assign inst_data_ex_mem_o = _inst_data_ex_mem_q;

  /* exc_alu_data 寄存器 */
  wire [`XLEN-1:0] _exc_alu_data_ex_mem_d = exc_alu_data_ex_mem_i;
  reg [`XLEN-1:0] _exc_alu_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_exc_alu_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_exc_alu_data_ex_mem_d),
      .dout(_exc_alu_data_ex_mem_q),
      .wen (1'b1)
  );
  assign exc_alu_data_ex_mem_o = _exc_alu_data_ex_mem_q;


  /* exc_csr_data 寄存器 */
  wire [`XLEN-1:0] _exc_csr_data_ex_mem_d = exc_csr_data_ex_mem_i;
  reg [`XLEN-1:0] _exc_csr_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_exc_csr_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_exc_csr_data_ex_mem_d),
      .dout(_exc_csr_data_ex_mem_q),
      .wen (1'b1)
  );
  assign exc_csr_data_ex_mem_o = _exc_csr_data_ex_mem_q;

  /* exc_csr_valid 寄存器 */
  wire _exc_csr_valid_ex_mem_d = exc_csr_valid_ex_mem_i;
  reg _exc_csr_valid_ex_mem_q;
  regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(1'b0)  //TODO:默认值未设置
  ) u_exc_csr_valid_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_exc_csr_valid_ex_mem_d),
      .dout(_exc_csr_valid_ex_mem_q),
      .wen (1'b1)
  );
  assign exc_csr_valid_ex_mem_o = _exc_csr_valid_ex_mem_q;


endmodule
