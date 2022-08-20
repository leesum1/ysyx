`include "sysconfig.v"

module if_id (
    input clk,
    input rst,
    //指令地址
    input wire [`XLEN_BUS] inst_addr_if_i,
    //指令内容
    input wire [`INST_LEN-1:0] inst_data_if_i,
    input [`TRAP_BUS] trap_bus_if_i,
    //指令地址
    output wire [`XLEN_BUS] inst_addr_if_id_o,
    //指令内容
    output wire [`INST_LEN-1:0] inst_data_if_id_o,
    output [`TRAP_BUS] trap_bus_if_id_o
);


  /* inst_addr_if_i 寄存器 */
  wire [`XLEN-1:0] _inst_addr_if_id_d = inst_addr_if_i;
  reg [`XLEN-1:0] _inst_addr_if_id_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_inst_addr_if_id (
      .clk (clk),
      .rst (rst),
      .din (_inst_addr_if_id_d),
      .dout(_inst_addr_if_id_q),
      .wen (1'b0)
  );
  assign inst_addr_if_id_o = _inst_addr_if_id_q;

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


  /* trap_bus_if_i 寄存器 */
  wire [`TRAP_BUS] _trap_bus_if_id_d = trap_bus_if_i;
  reg [`TRAP_BUS] _trap_bus_if_id_q;
  regTemplate #(
      .WIDTH    (`TRAP_LEN),
      .RESET_VAL(`TRAP_LEN'b0)  //TODO:默认值未设置
  ) u_trap_bus_if_id (
      .clk (clk),
      .rst (rst),
      .din (_trap_bus_if_id_d),
      .dout(_trap_bus_if_id_q),
      .wen (1'b0)
  );
  assign trap_bus_if_id_o = _trap_bus_if_id_q;



endmodule
