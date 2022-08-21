`include "sysconfig.v"

module ex_mem (
    input clk,
    input rst,

    input [             `XLEN_BUS] pc_ex_mem_i,
    input [         `INST_LEN-1:0] inst_data_ex_mem_i,
    input [             `XLEN_BUS] imm_data_ex_mem_i,
    input [    `REG_ADDRWIDTH-1:0] rd_idx_ex_mem_i,
    input [             `XLEN_BUS] rs1_data_ex_mem_i,
    input [             `XLEN_BUS] rs2_data_ex_mem_i,
    input [             `XLEN_BUS] alu_data_ex_mem_i,
    input [             `XLEN_BUS] csr_writedata_ex_mem_i,   // CSR 写回数据
    input                          csr_writevalid_ex_mem_i,  // CSR 写回使能
    input [`CSR_REG_ADDRWIDTH-1:0] csr_addr_ex_mem_i,        // CSR 写回地址
    input [         `PCOP_LEN-1:0] pc_op_ex_mem_i,
    input [        `MEMOP_LEN-1:0] mem_op_ex_mem_i,

    /* TARP 总线 */
    input [`TRAP_BUS] trap_bus_ex_mem_i,


    output [             `XLEN_BUS] pc_ex_mem_o,
    output [         `INST_LEN-1:0] inst_data_ex_mem_o,
    output [             `XLEN_BUS] imm_data_ex_mem_o,
    output [    `REG_ADDRWIDTH-1:0] rd_idx_ex_mem_o,
    output [             `XLEN_BUS] rs1_data_ex_mem_o,
    output [             `XLEN_BUS] rs2_data_ex_mem_o,
    output [             `XLEN_BUS] alu_data_ex_mem_o,
    output [             `XLEN_BUS] csr_writedata_ex_mem_o,
    output                          csr_writevalid_ex_mem_o,
    output [`CSR_REG_ADDRWIDTH-1:0] csr_addr_ex_mem_o,        // CSR 写回地址
    output [         `PCOP_LEN-1:0] pc_op_ex_mem_o,
    output [        `MEMOP_LEN-1:0] mem_op_ex_mem_o,

    /* TARP 总线 */
    output [`TRAP_BUS] trap_bus_ex_mem_o
);

  /* pc 寄存器 */
  wire [`XLEN_BUS] _pc_ex_mem_d = pc_ex_mem_i;
  reg [`XLEN_BUS] _pc_ex_mem_q;
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




  /* rd_idx 寄存器 */
  wire [`REG_ADDRWIDTH-1:0] _rd_idx_ex_mem_d = rd_idx_ex_mem_i;
  reg [`REG_ADDRWIDTH-1:0] _rd_idx_ex_mem_q;
  regTemplate #(
      .WIDTH    (`REG_ADDRWIDTH),
      .RESET_VAL(`REG_ADDRWIDTH'b0)  //TODO:默认值未设置
  ) u_rd_idx_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_rd_idx_ex_mem_d),
      .dout(_rd_idx_ex_mem_q),
      .wen (1'b1)
  );
  assign rd_idx_ex_mem_o = _rd_idx_ex_mem_q;


  /* rs1_data 寄存器 */
  wire [`XLEN_BUS] _rs1_data_ex_mem_d = rs1_data_ex_mem_i;
  reg [`XLEN_BUS] _rs1_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_rs1_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_rs1_data_ex_mem_d),
      .dout(_rs1_data_ex_mem_q),
      .wen (1'b1)
  );
  assign rs1_data_ex_mem_o = _rs1_data_ex_mem_q;


  /* rs2_data 寄存器 */
  wire [`XLEN_BUS] _rs2_data_ex_mem_d = rs2_data_ex_mem_i;
  reg [`XLEN_BUS] _rs2_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_rs2_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_rs2_data_ex_mem_d),
      .dout(_rs2_data_ex_mem_q),
      .wen (1'b1)
  );
  assign rs2_data_ex_mem_o = _rs2_data_ex_mem_q;


  /* imm_data 寄存器 */
  wire [`XLEN_BUS] _imm_data_ex_mem_d = imm_data_ex_mem_i;
  reg [`XLEN_BUS] _imm_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_imm_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_imm_data_ex_mem_d),
      .dout(_imm_data_ex_mem_q),
      .wen (1'b1)
  );
  assign imm_data_ex_mem_o = _imm_data_ex_mem_q;


  /* alu_data 寄存器 */
  wire [`XLEN_BUS] _alu_data_ex_mem_d = alu_data_ex_mem_i;
  reg [`XLEN_BUS] _alu_data_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值��设置
  ) u_alu_data_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_alu_data_ex_mem_d),
      .dout(_alu_data_ex_mem_q),
      .wen (1'b1)
  );
  assign alu_data_ex_mem_o = _alu_data_ex_mem_q;


  /* csr_writedata 寄存器 */
  wire [`XLEN_BUS] _csr_writedata_ex_mem_d = csr_writedata_ex_mem_i;
  reg [`XLEN_BUS] _csr_writedata_ex_mem_q;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)  //TODO:默认值未设置
  ) u_csr_writedata_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_csr_writedata_ex_mem_d),
      .dout(_csr_writedata_ex_mem_q),
      .wen (1'b1)
  );
  assign csr_writedata_ex_mem_o = _csr_writedata_ex_mem_q;

  /* csr_writevalid 寄存器 */
  wire _csr_writevalid_ex_mem_d = csr_writevalid_ex_mem_i;
  reg _csr_writevalid_ex_mem_q;
  regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(1'b0)  //TODO:默认值未设置
  ) u_csr_writevalid_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_csr_writevalid_ex_mem_d),
      .dout(_csr_writevalid_ex_mem_q),
      .wen (1'b1)
  );
  assign csr_writevalid_ex_mem_o = _csr_writevalid_ex_mem_q;


  /* csr_addr 寄存器 */
  wire [`CSR_REG_ADDRWIDTH-1:0] _csr_addr_ex_mem_d = csr_addr_ex_mem_i;
  reg [`CSR_REG_ADDRWIDTH-1:0] _csr_addr_ex_mem_q;
  regTemplate #(
      .WIDTH    (`CSR_REG_ADDRWIDTH),
      .RESET_VAL(`CSR_REG_ADDRWIDTH'b0)  //TODO:默认值未设置
  ) u_csr_addr_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_csr_addr_ex_mem_d),
      .dout(_csr_addr_ex_mem_q),
      .wen (1'b1)
  );
  assign csr_addr_ex_mem_o = _csr_addr_ex_mem_q;



  /* pc_op 寄存器 */
  wire [`PCOP_LEN-1:0] _pc_op_ex_mem_d = pc_op_ex_mem_i;
  reg [`PCOP_LEN-1:0] _pc_op_ex_mem_q;
  regTemplate #(
      .WIDTH    (`PCOP_LEN),
      .RESET_VAL(`PCOP_LEN'b0)  //TODO:默认值未设置
  ) u_pc_op_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_pc_op_ex_mem_d),
      .dout(_pc_op_ex_mem_q),
      .wen (1'b1)
  );
  assign pc_op_ex_mem_o = _pc_op_ex_mem_q;


  /* mem_op 寄存器 */
  wire [`MEMOP_LEN-1:0] _mem_op_ex_mem_d = mem_op_ex_mem_i;
  reg [`MEMOP_LEN-1:0] _mem_op_ex_mem_q;
  regTemplate #(
      .WIDTH    (`MEMOP_LEN),
      .RESET_VAL(`MEMOP_LEN'b0)  //TODO:默认值未设置
  ) u_mem_op_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_mem_op_ex_mem_d),
      .dout(_mem_op_ex_mem_q),
      .wen (1'b1)
  );
  assign mem_op_ex_mem_o = _mem_op_ex_mem_q;


  /* trap_bus 寄存器 */
  wire [`TRAP_LEN-1:0] _trap_bus_ex_mem_d = trap_bus_ex_mem_i;
  reg [`TRAP_LEN-1:0] _trap_bus_ex_mem_q;
  regTemplate #(
      .WIDTH    (`TRAP_LEN),
      .RESET_VAL(`TRAP_LEN'b0)  //TODO:默认值未设置
  ) u_trap_bus_ex_mem_id (
      .clk (clk),
      .rst (rst),
      .din (_trap_bus_ex_mem_d),
      .dout(_trap_bus_ex_mem_q),
      .wen (1'b1)
  );
  assign trap_bus_ex_mem_o = _trap_bus_ex_mem_q;


endmodule
