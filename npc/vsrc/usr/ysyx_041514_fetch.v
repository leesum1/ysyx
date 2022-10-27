
`include "sysconfig.v"
/**
* 取指模块
* 组合逻辑电路,仅仅起到传递作用,PC寄存器位于 IF/ID 
*/
module ysyx_041514_fetch (
    input clk,
    input rst,
    input [5:0] stall_valid_i,  // 保持当前数据，不接受新的数据
    input [5:0] flush_valid_i,  // 清空当前数据（nop），不接受新的数据
    input [$clog2(8) - 1:0] redirect_ras_ptr_i,
    input redirect_ras_ptr_valid_i,

    input [`ysyx_041514_XLEN_BUS] inst_addr_i,  // from pc_reg
    input if_rdata_valid_i,  // 读数据是否准备好
    input [`ysyx_041514_XLEN_BUS] if_rdata_i,

    /* bpu */
    // output [`ysyx_041514_XLEN_BUS] bpu_pc_o,
    output [`ysyx_041514_XLEN_BUS] bpu_pc_op1_o,
    output [`ysyx_041514_XLEN_BUS] bpu_pc_op2_o,
    output bpu_pc_valid_o,
    /* stall req */
    output ram_stall_valid_if_o,  // if 阶段访存暂停
    /* to if/id */
    output [`ysyx_041514_XLEN_BUS] inst_addr_o,
    output [`ysyx_041514_INST_LEN-1:0] inst_data_o,
    output [`ysyx_041514_TRAP_BUS] trap_bus_o
);


  assign inst_addr_o = inst_addr_i;

  // 选择读取数据
  //wire [`ysyx_041514_NPC_ADDR_BUS] _inst_data = (if_rdata_valid_i) ? if_rdata_i[31:0] : `ysyx_041514_INST_NOP;
  wire [`ysyx_041514_NPC_ADDR_BUS] _inst_data = if_rdata_i[31:0];

  // 若 icache 数据没有准备好,发出 stall 请求,暂停流水线
  wire _ram_stall = (!if_rdata_valid_i);

  assign ram_stall_valid_if_o = _ram_stall;
  assign inst_data_o = _inst_data;


  /* bpu */

  ysyx_041514_bpu_top u_ysyx_041514_bpu_top (
      .clk                     (clk),
      .rst                     (rst),
      .flush_valid_i           (flush_valid_i),
      .stall_valid_i           (stall_valid_i),
      .redirect_ras_ptr_i      (redirect_ras_ptr_i),
      .redirect_ras_ptr_valid_i(redirect_ras_ptr_valid_i),
      .inst_data_i             ({32'b0, _inst_data}),
      .pc_if_i                 (inst_addr_i),
      .bpu_pc_op1_o            (bpu_pc_op1_o),
      .bpu_pc_op2_o            (bpu_pc_op2_o),
      .bpu_pc_valid_o          (bpu_pc_valid_o)
  );

  /***********************TRAP**********************/
  wire _Instruction_address_misaligned = `ysyx_041514_FALSE;
  wire _Instruction_access_fault = `ysyx_041514_FALSE;
  wire _Instruction_page_fault = `ysyx_041514_FALSE;

  reg [`ysyx_041514_TRAP_BUS] _if_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `ysyx_041514_TRAP_LEN; i = i + 1) begin
      if (i == `ysyx_041514_TRAP_INST_ADDR_MISALIGNED) begin
        _if_trap_bus[i] = _Instruction_address_misaligned;
      end else if (i == `ysyx_041514_TRAP_INST_ACCESS_FAULT) begin
        _if_trap_bus[i] = _Instruction_access_fault;
      end else if (i == `ysyx_041514_TRAP_INST_PAGE_FAULT) begin
        _if_trap_bus[i] = _Instruction_page_fault;
      end else begin
        _if_trap_bus[i] = `ysyx_041514_FALSE;
      end
    end
  end
  assign trap_bus_o = _if_trap_bus;


endmodule
