`include "sysconfig.v"

module id_ex (
    input                               clk,
    input                               rst,
    input      [                   5:0] flush_valid_i,
    input      [                   5:0] stall_valid_i,
    /* 输入 */
    input wire [             `XLEN-1:0] pc_id_ex_i,
    input wire [         `INST_LEN-1:0] inst_data_id_ex_i,
    input      [    `REG_ADDRWIDTH-1:0] rs1_idx_id_ex_i,
    input      [    `REG_ADDRWIDTH-1:0] rs2_idx_id_ex_i,
    input      [    `REG_ADDRWIDTH-1:0] rd_idx_id_ex_i,
    input      [          `IMM_LEN-1:0] imm_data_id_ex_i,
    input      [          `IMM_LEN-1:0] csr_imm_id_ex_i,
    input                               csr_imm_valid_id_ex_i,
    input      [             `XLEN_BUS] rs1_data_id_ex_i,
    input      [             `XLEN_BUS] rs2_data_id_ex_i,
    input      [             `XLEN_BUS] csr_data_id_ex_i,
    input      [`CSR_REG_ADDRWIDTH-1:0] csr_idx_id_ex_i,
    input      [        `ALUOP_LEN-1:0] alu_op_id_ex_i,         // alu 操作码
    input      [        `MEMOP_LEN-1:0] mem_op_id_ex_i,         // mem 操作码
    input      [        `EXCOP_LEN-1:0] exc_op_id_ex_i,         // exc 操作码
    input      [         `PCOP_LEN-1:0] pc_op_id_ex_i,          // pc 操作码
    input      [        `CSROP_LEN-1:0] csr_op_id_ex_i,         // csr 操作码
    /* TARP 总线 */
    input wire [             `TRAP_BUS] trap_bus_id_ex_i,

    /* 输出 */
    output wire [             `XLEN-1:0] pc_id_ex_o,
    output wire [         `INST_LEN-1:0] inst_data_id_ex_o,
    output      [    `REG_ADDRWIDTH-1:0] rs1_idx_id_ex_o,
    output      [    `REG_ADDRWIDTH-1:0] rs2_idx_id_ex_o,
    output      [    `REG_ADDRWIDTH-1:0] rd_idx_id_ex_o,
    output      [          `IMM_LEN-1:0] imm_data_id_ex_o,
    output      [          `IMM_LEN-1:0] csr_imm_id_ex_o,
    output                               csr_imm_valid_id_ex_o,
    output      [             `XLEN_BUS] rs1_data_id_ex_o,
    output      [             `XLEN_BUS] rs2_data_id_ex_o,
    output      [             `XLEN_BUS] csr_data_id_ex_o,
    output      [`CSR_REG_ADDRWIDTH-1:0] csr_idx_id_ex_o,
    output      [        `ALUOP_LEN-1:0] alu_op_id_ex_o,         // alu 操作码
    output      [        `MEMOP_LEN-1:0] mem_op_id_ex_o,         // mem 操作码
    output      [        `EXCOP_LEN-1:0] exc_op_id_ex_o,         // exc 操作码
    output      [         `PCOP_LEN-1:0] pc_op_id_ex_o,          // pc 操作码
    output      [        `CSROP_LEN-1:0] csr_op_id_ex_o,         // csr 操作码
    /* TARP 总线 */
    output wire [             `TRAP_BUS] trap_bus_id_ex_o

);
  //   wire reg_wen = (~stall_i[2]) | flush_valid_i;
  //   wire _flush_valid = flush_valid_i | branch_pc_valid_i;

  //   wire _load_hazed = (stall_i[2] == `TRUE && stall_i[3] == `FALSE);

  wire reg_wen = !stall_valid_i[`CTRLBUS_ID_EX];
  wire _flush_valid = flush_valid_i[`CTRLBUS_ID_EX];

  /* pc 寄存器 */
  wire [`XLEN-1:0] _pc_id_ex_d = (_flush_valid) ? `XLEN'b0 : pc_id_ex_i;
  reg [`XLEN-1:0] _pc_id_ex_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_pc_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_pc_id_ex_d),
      .dout(_pc_id_ex_q),
      .wen (reg_wen)
  );
  assign pc_id_ex_o = _pc_id_ex_q;

  /* inst_data 寄存器 */
  wire [`INST_LEN-1:0] _inst_data_id_ex_d = (_flush_valid) ? `INST_NOP : inst_data_id_ex_i;
  reg [`INST_LEN-1:0] _inst_data_id_ex_q;
  regTemplate #(
      .WIDTH    (`INST_LEN),
      .RESET_VAL(`INST_NOP)
  ) u_inst_data_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_inst_data_id_ex_d),
      .dout(_inst_data_id_ex_q),
      .wen (reg_wen)
  );
  assign inst_data_id_ex_o = _inst_data_id_ex_q;


  /* rs1_idx 寄存器 */
  wire [`REG_ADDRWIDTH-1:0] _rs1_idx_id_ex_d = (_flush_valid) ? `REG_ADDRWIDTH'b0 : rs1_idx_id_ex_i;
  reg [`REG_ADDRWIDTH-1:0] _rs1_idx_id_ex_q;
  regTemplate #(
      .WIDTH    (`REG_ADDRWIDTH),
      .RESET_VAL(`REG_ADDRWIDTH'b0)
  ) u_rs1_idx_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_rs1_idx_id_ex_d),
      .dout(_rs1_idx_id_ex_q),
      .wen (reg_wen)
  );
  assign rs1_idx_id_ex_o = _rs1_idx_id_ex_q;

  /* rs2_idx 寄存器 */
  wire [`REG_ADDRWIDTH-1:0] _rs2_idx_id_ex_d = (_flush_valid) ? `REG_ADDRWIDTH'b0 :rs2_idx_id_ex_i;
  reg [`REG_ADDRWIDTH-1:0] _rs2_idx_id_ex_q;
  regTemplate #(
      .WIDTH    (`REG_ADDRWIDTH),
      .RESET_VAL(`REG_ADDRWIDTH'b0)
  ) u_rs2_idx_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_rs2_idx_id_ex_d),
      .dout(_rs2_idx_id_ex_q),
      .wen (reg_wen)
  );
  assign rs2_idx_id_ex_o = _rs2_idx_id_ex_q;


  /* rd_idx 寄存器 */
  wire [`REG_ADDRWIDTH-1:0] _rd_idx_id_ex_d = (_flush_valid) ? `REG_ADDRWIDTH'b0 : rd_idx_id_ex_i;
  reg [`REG_ADDRWIDTH-1:0] _rd_idx_id_ex_q;
  regTemplate #(
      .WIDTH    (`REG_ADDRWIDTH),
      .RESET_VAL(`REG_ADDRWIDTH'b0)
  ) u_rd_idx_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_rd_idx_id_ex_d),
      .dout(_rd_idx_id_ex_q),
      .wen (reg_wen)
  );
  assign rd_idx_id_ex_o = _rd_idx_id_ex_q;


  /* imm_data 寄存器 */
  wire [`XLEN-1:0] _imm_data_id_ex_d = (_flush_valid) ? `XLEN'b0 : imm_data_id_ex_i;
  reg [`XLEN-1:0] _imm_data_id_ex_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_imm_data_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_imm_data_id_ex_d),
      .dout(_imm_data_id_ex_q),
      .wen (reg_wen)
  );
  assign imm_data_id_ex_o = _imm_data_id_ex_q;


  /* csr_imm 寄存器 */
  wire [`XLEN-1:0] _csr_imm_id_ex_d = (_flush_valid) ? `XLEN'b0 : csr_imm_id_ex_i;
  reg [`XLEN-1:0] _csr_imm_id_ex_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_csr_imm_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_csr_imm_id_ex_d),
      .dout(_csr_imm_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_imm_id_ex_o = _csr_imm_id_ex_q;


  /* csr_imm_valid 寄存器 */
  wire _csr_imm_valid_id_ex_d = (_flush_valid) ? `FALSE : csr_imm_valid_id_ex_i;
  reg _csr_imm_valid_id_ex_q;
  regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`FALSE)
  ) u_csr_imm_valid_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_csr_imm_valid_id_ex_d),
      .dout(_csr_imm_valid_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_imm_valid_id_ex_o = _csr_imm_valid_id_ex_q;


  /* csr_idx 寄存器 */
  wire [`CSR_REG_ADDRWIDTH-1:0] _csr_idx_id_ex_d = (_flush_valid) ? `CSR_REG_ADDRWIDTH'b0:csr_idx_id_ex_i;
  reg [`CSR_REG_ADDRWIDTH-1:0] _csr_idx_id_ex_q;
  regTemplate #(
      .WIDTH    (`CSR_REG_ADDRWIDTH),
      .RESET_VAL(`CSR_REG_ADDRWIDTH'b0)
  ) u_csr_idx_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_csr_idx_id_ex_d),
      .dout(_csr_idx_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_idx_id_ex_o = _csr_idx_id_ex_q;


  /* rs1_data 寄存器 */
  wire [`XLEN-1:0] _rs1_data_id_ex_d = (_flush_valid) ? `XLEN'b0 : rs1_data_id_ex_i;
  reg [`XLEN-1:0] _rs1_data_id_ex_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_rs1_data_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_rs1_data_id_ex_d),
      .dout(_rs1_data_id_ex_q),
      .wen (reg_wen)
  );
  assign rs1_data_id_ex_o = _rs1_data_id_ex_q;


  /* rs2_data 寄存器 */
  wire [`XLEN-1:0] _rs2_data_id_ex_d = (_flush_valid) ? `XLEN'b0 : rs2_data_id_ex_i;
  reg [`XLEN-1:0] _rs2_data_id_ex_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_rs2_data_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_rs2_data_id_ex_d),
      .dout(_rs2_data_id_ex_q),
      .wen (reg_wen)
  );
  assign rs2_data_id_ex_o = _rs2_data_id_ex_q;



  /* csr_data 寄存器 */
  wire [`XLEN-1:0] _csr_data_id_ex_d = (_flush_valid) ? `XLEN'b0 : csr_data_id_ex_i;
  reg [`XLEN-1:0] _csr_data_id_ex_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_csr_data_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_csr_data_id_ex_d),
      .dout(_csr_data_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_data_id_ex_o = _csr_data_id_ex_q;


  /* alu_op 寄存器 */
  wire [`ALUOP_LEN-1:0] _alu_op_id_ex_d = (_flush_valid) ? `ALUOP_NONE : alu_op_id_ex_i;
  reg [`ALUOP_LEN-1:0] _alu_op_id_ex_q;
  regTemplate #(
      .WIDTH    (`ALUOP_LEN),
      .RESET_VAL(`ALUOP_NONE)
  ) u_alu_op_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_alu_op_id_ex_d),
      .dout(_alu_op_id_ex_q),
      .wen (reg_wen)
  );
  assign alu_op_id_ex_o = _alu_op_id_ex_q;


  /* mem_op 寄存器 */
  wire [`MEMOP_LEN-1:0] _mem_op_id_ex_d = (_flush_valid) ? `MEMOP_NONE : mem_op_id_ex_i;
  reg [`MEMOP_LEN-1:0] _mem_op_id_ex_q;
  regTemplate #(
      .WIDTH    (`MEMOP_LEN),
      .RESET_VAL(`MEMOP_NONE)
  ) u_mem_op_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_mem_op_id_ex_d),
      .dout(_mem_op_id_ex_q),
      .wen (reg_wen)
  );
  assign mem_op_id_ex_o = _mem_op_id_ex_q;


  /* exc_op 寄存器 */
  wire [`EXCOP_LEN-1:0] _exc_op_id_ex_d = (_flush_valid) ? `EXCOP_NONE : exc_op_id_ex_i;
  reg [`EXCOP_LEN-1:0] _exc_op_id_ex_q;
  regTemplate #(
      .WIDTH    (`EXCOP_LEN),
      .RESET_VAL(`EXCOP_NONE)
  ) u_exc_op_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_exc_op_id_ex_d),
      .dout(_exc_op_id_ex_q),
      .wen (reg_wen)
  );
  assign exc_op_id_ex_o = _exc_op_id_ex_q;


  /* pc_op 寄存器 */
  wire [`PCOP_LEN-1:0] _pc_op_id_ex_d = (_flush_valid) ? `PCOP_NONE : pc_op_id_ex_i;
  reg [`PCOP_LEN-1:0] _pc_op_id_ex_q;
  regTemplate #(
      .WIDTH    (`PCOP_LEN),
      .RESET_VAL(`PCOP_NONE)
  ) u_pc_op_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_pc_op_id_ex_d),
      .dout(_pc_op_id_ex_q),
      .wen (reg_wen)
  );
  assign pc_op_id_ex_o = _pc_op_id_ex_q;


  /* csr_op 寄存器 */
  wire [`CSROP_LEN-1:0] _csr_op_id_ex_d = (_flush_valid) ? `CSROP_NONE : csr_op_id_ex_i;
  reg [`CSROP_LEN-1:0] _csr_op_id_ex_q;
  regTemplate #(
      .WIDTH    (`CSROP_LEN),
      .RESET_VAL(`CSROP_NONE)
  ) u_csr_op_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_csr_op_id_ex_d),
      .dout(_csr_op_id_ex_q),
      .wen (reg_wen)
  );
  assign csr_op_id_ex_o = _csr_op_id_ex_q;


  /* trap_bus 寄存器 */
  wire [`TRAP_LEN-1:0] _trap_bus_id_ex_d = (_flush_valid) ? `TRAP_LEN'b0 : trap_bus_id_ex_i;
  reg [`TRAP_LEN-1:0] _trap_bus_id_ex_q;
  regTemplate #(
      .WIDTH    (`TRAP_LEN),
      .RESET_VAL(`TRAP_LEN'b0)
  ) u_trap_bus_id_ex (
      .clk (clk),
      .rst (rst),
      .din (_trap_bus_id_ex_d),
      .dout(_trap_bus_id_ex_q),
      .wen (reg_wen)
  );
  assign trap_bus_id_ex_o = _trap_bus_id_ex_q;






endmodule
