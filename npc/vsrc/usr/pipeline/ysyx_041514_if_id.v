`include "sysconfig.v"

module ysyx_041514_if_id (
    input clk,
    input rst,
    input [5:0] stall_valid_i,  // 保持当前数据，不接受新的数据
    input [5:0] flush_valid_i,  // 清空当前数据（nop），不接受新的数据

    //指令地址
    input wire [`ysyx_041514_XLEN_BUS] inst_addr_if_i,
    //指令内容
    input wire [`ysyx_041514_INST_LEN-1:0] inst_data_if_i,
    input [`ysyx_041514_TRAP_BUS] trap_bus_if_i,
    //指令地址
    output wire [`ysyx_041514_XLEN_BUS] inst_addr_if_id_o,
    //指令内容
    output wire [`ysyx_041514_INST_LEN-1:0] inst_data_if_id_o,
    output [`ysyx_041514_TRAP_BUS] trap_bus_if_id_o
);
  // 保持时，写失效

  wire reg_wen = !stall_valid_i[`ysyx_041514_CTRLBUS_IF_ID];
  wire _flush_valid = flush_valid_i[`ysyx_041514_CTRLBUS_IF_ID] | (inst_addr_if_i == `ysyx_041514_PC_RESET_ADDR - 'd4);
  wire reg_rst = rst | _flush_valid;


  /* inst_addr_if_i 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _inst_addr_if_id_d = inst_addr_if_i;
  wire [`ysyx_041514_XLEN-1:0] _inst_addr_if_id_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_inst_addr_if_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_inst_addr_if_id_d),
      .dout(_inst_addr_if_id_q),
      .wen (reg_wen)
  );
  assign inst_addr_if_id_o = _inst_addr_if_id_q;

  /* inst_data_if_i 寄存器 */
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_if_id_d = inst_data_if_i;
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_if_id_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_INST_LEN),
      .RESET_VAL(`ysyx_041514_INST_NOP)
  ) u_inst_data_if_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_inst_data_if_id_d),
      .dout(_inst_data_if_id_q),
      .wen (reg_wen)
  );
  assign inst_data_if_id_o = _inst_data_if_id_q;


  /* trap_bus_if_i 寄存器 */
  wire [`ysyx_041514_TRAP_BUS] _trap_bus_if_id_d = trap_bus_if_i;
  wire [`ysyx_041514_TRAP_BUS] _trap_bus_if_id_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_TRAP_LEN),
      .RESET_VAL(`ysyx_041514_TRAP_LEN'b0)
  ) u_trap_bus_if_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_trap_bus_if_id_d),
      .dout(_trap_bus_if_id_q),
      .wen (reg_wen)
  );
  assign trap_bus_if_id_o = _trap_bus_if_id_q;


endmodule
