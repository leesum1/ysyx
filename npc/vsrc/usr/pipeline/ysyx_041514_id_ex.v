`include "sysconfig.v"

module ysyx_041514_id_ex (
    input                                      clk,
    input                                      rst,
    input [                               5:0] flush_valid_i,
    input [                               5:0] stall_valid_i,
    /* 输入 */
    input [             `ysyx_041514_XLEN-1:0] pc_id_ex_i,
    input [         `ysyx_041514_INST_LEN-1:0] inst_data_id_ex_i,
    input                                      bru_taken_id_ex_i,
    // input      [    `ysyx_041514_REG_ADDRWIDTH-1:0] rs1_idx_id_ex_i,
    // input      [    `ysyx_041514_REG_ADDRWIDTH-1:0] rs2_idx_id_ex_i,
    input [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_id_ex_i,
    input [          `ysyx_041514_IMM_LEN-1:0] imm_data_id_ex_i,
    input [          `ysyx_041514_IMM_LEN-1:0] csr_imm_id_ex_i,
    input                                      csr_imm_valid_id_ex_i,
    input [             `ysyx_041514_XLEN_BUS] rs1_data_id_ex_i,
    input [             `ysyx_041514_XLEN_BUS] rs2_data_id_ex_i,
    input [             `ysyx_041514_XLEN_BUS] csr_data_id_ex_i,
    input [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_idx_id_ex_i,
    input [        `ysyx_041514_ALUOP_LEN-1:0] alu_op_id_ex_i,         // alu 操作码
    input [        `ysyx_041514_MEMOP_LEN-1:0] mem_op_id_ex_i,         // mem 操作码
    input [        `ysyx_041514_EXCOP_LEN-1:0] exc_op_id_ex_i,         // exc 操作码
    // input      [         `ysyx_041514_PCOP_LEN-1:0] pc_op_id_ex_i,          // pc 操作码
    input [        `ysyx_041514_CSROP_LEN-1:0] csr_op_id_ex_i,         // csr 操作码
    /* TARP 总线 */
    input [             `ysyx_041514_TRAP_BUS] trap_bus_id_ex_i,

    /* 输出 */
    output [             `ysyx_041514_XLEN-1:0] pc_id_ex_o,
    output [         `ysyx_041514_INST_LEN-1:0] inst_data_id_ex_o,
    output                                      bru_taken_id_ex_o,
    // output      [    `ysyx_041514_REG_ADDRWIDTH-1:0] rs1_idx_id_ex_o,
    // output      [    `ysyx_041514_REG_ADDRWIDTH-1:0] rs2_idx_id_ex_o,
    output [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_id_ex_o,
    output [          `ysyx_041514_IMM_LEN-1:0] imm_data_id_ex_o,
    output [          `ysyx_041514_IMM_LEN-1:0] csr_imm_id_ex_o,
    output                                      csr_imm_valid_id_ex_o,
    output [             `ysyx_041514_XLEN_BUS] rs1_data_id_ex_o,
    output [             `ysyx_041514_XLEN_BUS] rs2_data_id_ex_o,
    output [             `ysyx_041514_XLEN_BUS] csr_data_id_ex_o,
    output [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_idx_id_ex_o,
    output [        `ysyx_041514_ALUOP_LEN-1:0] alu_op_id_ex_o,         // alu 操作码
    output [        `ysyx_041514_MEMOP_LEN-1:0] mem_op_id_ex_o,         // mem 操作码
    output [        `ysyx_041514_EXCOP_LEN-1:0] exc_op_id_ex_o,         // exc 操作码
    // output      [         `ysyx_041514_PCOP_LEN-1:0] pc_op_id_ex_o,          // pc 操作码
    output [        `ysyx_041514_CSROP_LEN-1:0] csr_op_id_ex_o,         // csr 操作码
    /* TARP 总线 */
    output [             `ysyx_041514_TRAP_BUS] trap_bus_id_ex_o

);

  wire reg_wen = !stall_valid_i[`ysyx_041514_CTRLBUS_ID_EX];
  wire _flush_valid = flush_valid_i[`ysyx_041514_CTRLBUS_ID_EX];
  wire reg_rst = rst | _flush_valid;

  /* pc 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _pc_id_ex_d = pc_id_ex_i;
  wire [`ysyx_041514_XLEN-1:0] _pc_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_pc_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_pc_id_ex_d),
      .dout(_pc_id_ex_q),
      .wen (reg_wen)
  );
  assign pc_id_ex_o = _pc_id_ex_q;

  /* inst_data 寄存器 */
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_id_ex_d = inst_data_id_ex_i;
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_INST_LEN),
      .RESET_VAL(`ysyx_041514_INST_NOP)
  ) u_inst_data_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_inst_data_id_ex_d),
      .dout(_inst_data_id_ex_q),
      .wen (reg_wen)
  );
  assign inst_data_id_ex_o = _inst_data_id_ex_q;


  /* bru_taken_if_i 寄存器 */
  wire _bru_taken_id_ex_d = bru_taken_id_ex_i;
  wire _bru_taken_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(0)
  ) u_bru_taken_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_bru_taken_id_ex_d),
      .dout(_bru_taken_id_ex_q),
      .wen (reg_wen)
  );
  assign bru_taken_id_ex_o = _bru_taken_id_ex_q;


  //   /* rs1_idx 寄存器 */
  //   wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rs1_idx_id_ex_d = (_flush_valid) ? `ysyx_041514_REG_ADDRWIDTH'b0 : rs1_idx_id_ex_i;
  //   wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rs1_idx_id_ex_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_REG_ADDRWIDTH),
  //       .RESET_VAL(`ysyx_041514_REG_ADDRWIDTH'b0)
  //   ) u_rs1_idx_id_ex (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_rs1_idx_id_ex_d),
  //       .dout(_rs1_idx_id_ex_q),
  //       .wen (reg_wen)
  //   );
  //   assign rs1_idx_id_ex_o = _rs1_idx_id_ex_q;

  //   /* rs2_idx 寄存器 */
  //   wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rs2_idx_id_ex_d = (_flush_valid) ? `ysyx_041514_REG_ADDRWIDTH'b0 :rs2_idx_id_ex_i;
  //   wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rs2_idx_id_ex_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_REG_ADDRWIDTH),
  //       .RESET_VAL(`ysyx_041514_REG_ADDRWIDTH'b0)
  //   ) u_rs2_idx_id_ex (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_rs2_idx_id_ex_d),
  //       .dout(_rs2_idx_id_ex_q),
  //       .wen (reg_wen)
  //   );
  //   assign rs2_idx_id_ex_o = _rs2_idx_id_ex_q;


  /* rd_idx 寄存器 */
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rd_idx_id_ex_d = rd_idx_id_ex_i;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rd_idx_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_REG_ADDRWIDTH),
      .RESET_VAL(`ysyx_041514_REG_ADDRWIDTH'b0)
  ) u_rd_idx_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_rd_idx_id_ex_d),
      .dout(_rd_idx_id_ex_q),
      .wen (reg_wen)
  );
  assign rd_idx_id_ex_o = _rd_idx_id_ex_q;


  /* imm_data 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _imm_data_id_ex_d = imm_data_id_ex_i;
  wire [`ysyx_041514_XLEN-1:0] _imm_data_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_imm_data_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_imm_data_id_ex_d),
      .dout(_imm_data_id_ex_q),
      .wen (reg_wen)
  );
  assign imm_data_id_ex_o = _imm_data_id_ex_q;


  /* csr_imm 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_imm_id_ex_d = csr_imm_id_ex_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_imm_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_imm_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_imm_id_ex_d),
      .dout(_csr_imm_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_imm_id_ex_o = _csr_imm_id_ex_q;


  /* csr_imm_valid 寄存器 */
  wire _csr_imm_valid_id_ex_d = csr_imm_valid_id_ex_i;
  wire _csr_imm_valid_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)
  ) u_csr_imm_valid_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_imm_valid_id_ex_d),
      .dout(_csr_imm_valid_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_imm_valid_id_ex_o = _csr_imm_valid_id_ex_q;


  /* csr_idx 寄存器 */
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_idx_id_ex_d = csr_idx_id_ex_i;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_idx_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_CSR_REG_ADDRWIDTH),
      .RESET_VAL(`ysyx_041514_CSR_REG_ADDRWIDTH'b0)
  ) u_csr_idx_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_idx_id_ex_d),
      .dout(_csr_idx_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_idx_id_ex_o = _csr_idx_id_ex_q;


  /* rs1_data 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _rs1_data_id_ex_d = rs1_data_id_ex_i;
  wire [`ysyx_041514_XLEN-1:0] _rs1_data_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_rs1_data_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_rs1_data_id_ex_d),
      .dout(_rs1_data_id_ex_q),
      .wen (reg_wen)
  );
  assign rs1_data_id_ex_o = _rs1_data_id_ex_q;


  /* rs2_data 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _rs2_data_id_ex_d = rs2_data_id_ex_i;
  wire [`ysyx_041514_XLEN-1:0] _rs2_data_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_rs2_data_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_rs2_data_id_ex_d),
      .dout(_rs2_data_id_ex_q),
      .wen (reg_wen)
  );
  assign rs2_data_id_ex_o = _rs2_data_id_ex_q;



  /* csr_data 寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_data_id_ex_d = csr_data_id_ex_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_data_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_data_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_data_id_ex_d),
      .dout(_csr_data_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_data_id_ex_o = _csr_data_id_ex_q;


  /* alu_op 寄存器 */
  wire [`ysyx_041514_ALUOP_LEN-1:0] _alu_op_id_ex_d = alu_op_id_ex_i;
  wire [`ysyx_041514_ALUOP_LEN-1:0] _alu_op_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_ALUOP_LEN),
      .RESET_VAL(`ysyx_041514_ALUOP_NONE)
  ) u_alu_op_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_alu_op_id_ex_d),
      .dout(_alu_op_id_ex_q),
      .wen (reg_wen)
  );
  assign alu_op_id_ex_o = _alu_op_id_ex_q;


  /* mem_op 寄存器 */
  wire [`ysyx_041514_MEMOP_LEN-1:0] _mem_op_id_ex_d = mem_op_id_ex_i;
  wire [`ysyx_041514_MEMOP_LEN-1:0] _mem_op_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_MEMOP_LEN),
      .RESET_VAL(`ysyx_041514_MEMOP_NONE)
  ) u_mem_op_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_mem_op_id_ex_d),
      .dout(_mem_op_id_ex_q),
      .wen (reg_wen)
  );
  assign mem_op_id_ex_o = _mem_op_id_ex_q;


  /* exc_op 寄存器 */

  wire [`ysyx_041514_EXCOP_LEN-1:0] _exc_op_id_ex_d = exc_op_id_ex_i;
  wire [`ysyx_041514_EXCOP_LEN-1:0] _exc_op_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_EXCOP_LEN),
      .RESET_VAL(`ysyx_041514_EXCOP_NONE)
  ) u_exc_op_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_exc_op_id_ex_d),
      .dout(_exc_op_id_ex_q),
      .wen (reg_wen)
  );
  assign exc_op_id_ex_o = _exc_op_id_ex_q;


  /* csr_op 寄存器 */
  wire [`ysyx_041514_CSROP_LEN-1:0] _csr_op_id_ex_d = csr_op_id_ex_i;
  wire [`ysyx_041514_CSROP_LEN-1:0] _csr_op_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_CSROP_LEN),
      .RESET_VAL(`ysyx_041514_CSROP_NONE)
  ) u_csr_op_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_op_id_ex_d),
      .dout(_csr_op_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_op_id_ex_o = _csr_op_id_ex_q;


  /* trap_bus 寄存器 */
  wire [`ysyx_041514_TRAP_LEN-1:0] _trap_bus_id_ex_d = trap_bus_id_ex_i;
  wire [`ysyx_041514_TRAP_LEN-1:0] _trap_bus_id_ex_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_TRAP_LEN),
      .RESET_VAL(`ysyx_041514_TRAP_LEN'b0)
  ) u_trap_bus_id_ex (
      .clk (clk),
      .rst (reg_rst),
      .din (_trap_bus_id_ex_d),
      .dout(_trap_bus_id_ex_q),
      .wen (reg_wen)
  );
  assign trap_bus_id_ex_o = _trap_bus_id_ex_q;






endmodule
