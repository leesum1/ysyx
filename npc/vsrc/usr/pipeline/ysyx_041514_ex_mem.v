`include "sysconfig.v"

module ysyx_041514_ex_mem (
    input clk,
    input rst,
    input [5:0] flush_valid_i,
    input [5:0] stall_valid_i,

    input [             `ysyx_041514_XLEN_BUS] pc_ex_mem_i,
    input [         `ysyx_041514_INST_LEN-1:0] inst_data_ex_mem_i,
    // input [             `ysyx_041514_XLEN_BUS] imm_data_ex_mem_i,
    input [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_ex_mem_i,
    // input [             `ysyx_041514_XLEN_BUS] rs1_data_ex_mem_i,
    input [             `ysyx_041514_XLEN_BUS] rs2_data_ex_mem_i,
    input [             `ysyx_041514_XLEN_BUS] alu_data_ex_mem_i,
    input [             `ysyx_041514_XLEN_BUS] csr_writedata_ex_mem_i,   // CSR 写回数据
    input                                      csr_writevalid_ex_mem_i,  // CSR 写回使能
    input [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_ex_mem_i,        // CSR 写回地址
    // input [         `ysyx_041514_PCOP_LEN-1:0] pc_op_ex_mem_i,
    input [        `ysyx_041514_MEMOP_LEN-1:0] mem_op_ex_mem_i,

    /* TARP 总线 */
    input [`ysyx_041514_TRAP_BUS] trap_bus_ex_mem_i,


    output [             `ysyx_041514_XLEN_BUS] pc_ex_mem_o,
    output [         `ysyx_041514_INST_LEN-1:0] inst_data_ex_mem_o,
    // output [             `ysyx_041514_XLEN_BUS] imm_data_ex_mem_o,
    output [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_ex_mem_o,
    // output [             `ysyx_041514_XLEN_BUS] rs1_data_ex_mem_o,
    output [             `ysyx_041514_XLEN_BUS] rs2_data_ex_mem_o,
    output [             `ysyx_041514_XLEN_BUS] alu_data_ex_mem_o,
    output [             `ysyx_041514_XLEN_BUS] csr_writedata_ex_mem_o,
    output                                      csr_writevalid_ex_mem_o,
    output [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_ex_mem_o,        // CSR 写回地址
    // output [         `ysyx_041514_PCOP_LEN-1:0] pc_op_ex_mem_o,
    output [        `ysyx_041514_MEMOP_LEN-1:0] mem_op_ex_mem_o,

    /* TARP 总线 */
    output [`ysyx_041514_TRAP_BUS] trap_bus_ex_mem_o
);

  wire reg_wen = !stall_valid_i[`ysyx_041514_CTRLBUS_EX_MEM];
  wire _flush_valid = flush_valid_i[`ysyx_041514_CTRLBUS_EX_MEM];
  wire reg_rst = rst | _flush_valid;

  /* pc 寄存器 */
  wire [`ysyx_041514_XLEN_BUS] _pc_ex_mem_d = pc_ex_mem_i;
  wire [`ysyx_041514_XLEN_BUS] _pc_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_pc_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_pc_ex_mem_d),
      .dout(_pc_ex_mem_q),
      .wen (reg_wen)
  );
  assign pc_ex_mem_o = _pc_ex_mem_q;


  /* inst_data 寄存器 */
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_ex_mem_d = inst_data_ex_mem_i;
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_INST_LEN),
      .RESET_VAL(`ysyx_041514_INST_NOP)
  ) u_inst_data_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_inst_data_ex_mem_d),
      .dout(_inst_data_ex_mem_q),
      .wen (reg_wen)
  );
  assign inst_data_ex_mem_o = _inst_data_ex_mem_q;




  /* rd_idx 寄存器 */
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rd_idx_ex_mem_d = rd_idx_ex_mem_i;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rd_idx_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_REG_ADDRWIDTH),
      .RESET_VAL(`ysyx_041514_REG_ADDRWIDTH'b0)
  ) u_rd_idx_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_rd_idx_ex_mem_d),
      .dout(_rd_idx_ex_mem_q),
      .wen (reg_wen)
  );
  assign rd_idx_ex_mem_o = _rd_idx_ex_mem_q;



  /* rs2_data 寄存器 */
  wire [`ysyx_041514_XLEN_BUS] _rs2_data_ex_mem_d = rs2_data_ex_mem_i;
  wire [`ysyx_041514_XLEN_BUS] _rs2_data_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_rs2_data_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_rs2_data_ex_mem_d),
      .dout(_rs2_data_ex_mem_q),
      .wen (reg_wen)
  );
  assign rs2_data_ex_mem_o = _rs2_data_ex_mem_q;



  /* alu_data 寄存器 */
  wire [`ysyx_041514_XLEN_BUS] _alu_data_ex_mem_d = alu_data_ex_mem_i;
  wire [`ysyx_041514_XLEN_BUS] _alu_data_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_alu_data_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_alu_data_ex_mem_d),
      .dout(_alu_data_ex_mem_q),
      .wen (reg_wen)
  );
  assign alu_data_ex_mem_o = _alu_data_ex_mem_q;


  /* csr_writedata 寄存器 */
  wire [`ysyx_041514_XLEN_BUS] _csr_writedata_ex_mem_d = csr_writedata_ex_mem_i;
  wire [`ysyx_041514_XLEN_BUS] _csr_writedata_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_csr_writedata_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_writedata_ex_mem_d),
      .dout(_csr_writedata_ex_mem_q),
      .wen (reg_wen)
  );
  assign csr_writedata_ex_mem_o = _csr_writedata_ex_mem_q;

  /* csr_writevalid 寄存器 */
  wire _csr_writevalid_ex_mem_d = csr_writevalid_ex_mem_i;
  wire _csr_writevalid_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_csr_writevalid_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_writevalid_ex_mem_d),
      .dout(_csr_writevalid_ex_mem_q),
      .wen (reg_wen)
  );
  assign csr_writevalid_ex_mem_o = _csr_writevalid_ex_mem_q;


  /* csr_addr 寄存器 */
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_addr_ex_mem_d = csr_addr_ex_mem_i;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_addr_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_CSR_REG_ADDRWIDTH),
      .RESET_VAL(`ysyx_041514_CSR_REG_ADDRWIDTH'b0)  //TODO:默认值未设置
  ) u_csr_addr_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_addr_ex_mem_d),
      .dout(_csr_addr_ex_mem_q),
      .wen (reg_wen)
  );
  assign csr_addr_ex_mem_o = _csr_addr_ex_mem_q;




  /* mem_op 寄存器 */
  wire [`ysyx_041514_MEMOP_LEN-1:0] _mem_op_ex_mem_d = mem_op_ex_mem_i;
  wire [`ysyx_041514_MEMOP_LEN-1:0] _mem_op_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_MEMOP_LEN),
      .RESET_VAL(`ysyx_041514_MEMOP_NONE)  //TODO:默认值未设置
  ) u_mem_op_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_mem_op_ex_mem_d),
      .dout(_mem_op_ex_mem_q),
      .wen (reg_wen)
  );
  assign mem_op_ex_mem_o = _mem_op_ex_mem_q;


  /* trap_bus 寄存器 */
  wire [`ysyx_041514_TRAP_LEN-1:0] _trap_bus_ex_mem_d = trap_bus_ex_mem_i;
  wire [`ysyx_041514_TRAP_LEN-1:0] _trap_bus_ex_mem_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_TRAP_LEN),
      .RESET_VAL(`ysyx_041514_TRAP_LEN'b0)  //TODO:默认值未设置
  ) u_trap_bus_ex_mem_id (
      .clk (clk),
      .rst (reg_rst),
      .din (_trap_bus_ex_mem_d),
      .dout(_trap_bus_ex_mem_q),
      .wen (reg_wen)
  );
  assign trap_bus_ex_mem_o = _trap_bus_ex_mem_q;


endmodule
