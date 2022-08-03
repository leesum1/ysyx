`include "sysconfig.v"


/* 需要设为为input熟悉才能才仿真中改变值 */
module top (
    input clk,
    input rst
);


  /* PC 模块 */
  reg [`XLEN-1:0] pc;
  pc u_pc (
      .clk         (clk),
      .rst         (rst),
      .pc_op       (pc_op),
      // pc 操作码
      .rs1_data    (rs1_data),
      .imm_data    (imm_data),
      .pc_out      (pc),
      .execute_data(exc_out)
  );
  /* 取指模块 */
  wire [`INST_LEN-1:0] inst_data;
  fetch u_fetch (
      //指令地址
      .inst_addr(pc),
      //指令内容
      .inst_data(inst_data)
  );


  /***************译码模块*****************/
  /* 译码输出的指令操作数 */
  wire [    `REG_ADDRWIDTH-1:0] rs1_idx;
  wire [    `REG_ADDRWIDTH-1:0] rs2_idx;
  wire [    `REG_ADDRWIDTH-1:0] rd_idx;
  wire [`CSR_REG_ADDRWIDTH-1:0] csr_idx;
  wire [          `IMM_LEN-1:0] imm_data;
  wire [          `IMM_LEN-1:0] imm_csr;
  wire                          isNeedimmCSR;

  /* 译码器输出的控制信号 */
  wire [        `ALUOP_LEN-1:0] alu_op;
  wire [        `MEMOP_LEN-1:0] mem_op;
  wire [        `EXCOP_LEN-1:0] exc_op;
  wire [         `PCOP_LEN-1:0] pc_op;
  wire [        `CSROP_LEN-1:0] csr_op;

  dcode u_dcode (
      /* 输入信号 */
      .inst_data   (inst_data),
      /*输出信号： */
      .rs1_idx     (rs1_idx),
      .rs2_idx     (rs2_idx),
      .rd_idx      (rd_idx),
      .imm_data    (imm_data),
      /* CSR 译码结果 */
      .immCSR      (imm_csr),
      .isNeedimmCSR(isNeedimmCSR),
      .csr_idx     (csr_idx),
      .alu_op      (alu_op),
      // alu 操作码
      .mem_op      (mem_op),
      // mem 操作码
      .exc_op      (exc_op),
      // exc 操作码
      .pc_op       (pc_op),
      // pc 操作码
      // csr 操作码
      .csr_op      (csr_op)
  );


  /****************通用寄存器组***************/
  /* 寄存器组输入数据 */
  wire [         `XLEN-1:0]                   rs1_data;
  wire [         `XLEN-1:0]                   rs2_data;
  wire [         `XLEN-1:0] w_data = wb_data;
  wire [`REG_ADDRWIDTH-1:0] w_idx = rd_idx;

  rv64reg u_rv64reg (
      .clk       (clk),
      /* 读取数据 */
      .rs1_idx   (rs1_idx),
      .rs2_idx   (rs2_idx),
      .rs1_data  (rs1_data),
      .rs2_data  (rs2_data),
      /* 写入数据 */
      .write_idx (w_idx),
      .write_data(w_data),
      .wen       (1'b1)       // 写入一直使能,若该指令不需要写寄存器 w_idx = 0
  );

  /*****************CSR寄存器组*********************/
  /* 单独引出寄存器(写) */
  wire [`XLEN-1:0] csr_mepc_i;
  wire [`XLEN-1:0] csr_mcause_i;
  wire [`XLEN-1:0] csr_mtval_i;
  wire [`XLEN-1:0] csr_mtvec_i;
  wire csr_mepc_i_en;
  wire csr_mcause_i_en;
  wire csr_mtval_i_en;
  wire csr_mtvec_i_en;
  /* 单独引出寄存器(读) */
  wire [`XLEN-1:0] csr_mepc_o;
  wire [`XLEN-1:0] csr_mcause_o;
  wire [`XLEN-1:0] csr_mtval_o;
  wire [`XLEN-1:0] csr_mtvec_o;

  /* 读取数据端口 */
  wire [`CSR_REG_ADDRWIDTH-1:0] csr_readaddr = csr_idx;
  wire [`XLEN-1:0] csr_readdata;
  /* 写入数据端口 */
  reg [`CSR_REG_ADDRWIDTH-1:0] csr_writeaddr = csr_idx;
  wire write_enable = exc_csr_valid;
  wire [`XLEN-1:0] csr_writedata = exc_csr_out;

  rv64_csr_regfile u_rv64_csr_regfile (
      .clk            (clk),
      .rst            (rst),
      /* 单独引出寄存器(写) */
      .csr_mepc_i     (csr_mepc_i),
      .csr_mcause_i   (csr_mcause_i),
      .csr_mtval_i    (csr_mtval_i),
      .csr_mtvec_i    (csr_mtvec_i),
      .csr_mepc_i_en  (csr_mepc_i_en),
      .csr_mcause_i_en(csr_mcause_i_en),
      .csr_mtval_i_en (csr_mtval_i_en),
      .csr_mtvec_i_en (csr_mtvec_i_en),
      /* 单独引出寄存器(读) */
      .csr_mepc_o     (csr_mepc_o),
      .csr_mcause_o   (csr_mcause_o),
      .csr_mtval_o    (csr_mtval_o),
      .csr_mtvec_o    (csr_mtvec_o),
      /* 读取数据端口 */
      .csr_readaddr   (csr_readaddr),
      .csr_readdata   (csr_readdata),
      /* 写入数据端口 */
      .csr_writeaddr  (csr_writeaddr),
      .write_enable   (write_enable),
      .csr_writedata  (csr_writedata)
  );

  /**********************执行模块**********************/

  wire [`XLEN-1:0] exc_out;
  wire [`XLEN-1:0] exc_csr_out;
  wire exc_csr_valid;
  execute u_execute (
      .pc           (pc),
      .rd_idx       (rd_idx),
      .rs1_data     (rs1_data),      // rs1 数据
      .rs2_data     (rs2_data),      // rs2 数据
      .imm_data     (imm_data),      // 立即数数据
      .csr_data     (csr_readdata),  // csr 数据
      .imm_CSR      (imm_csr),       // csr 立即数
      .isNeedimmCSR (isNeedimmCSR),  // 是否需要 csr 立即数
      .alu_op       (alu_op),        // alu 操作码
      .mem_op       (mem_op),        // 访存操作码
      .exc_op       (exc_op),        // exc 操作码
      .csr_op       (csr_op),        // csr 操作码
      .exc_alu_out  (exc_out),       // 执行阶段 alu 输出
      .exc_csr_out  (exc_csr_out),   // csr 写回数据
      .exc_csr_valid(exc_csr_valid)  // csr 写回使能
  );

  /*******************访存模块*************************/
  wire [`XLEN-1:0] mem_out;
  wire isloadEnable;
  memory u_memory (
      .clk         (clk),
      .rst         (rst),
      .pc          (pc),
      .rd_idx      (rd_idx),
      .rs1_data    (rs1_data),
      .rs2_data    (rs2_data),
      .imm_data    (imm_data),
      .mem_op      (mem_op),
      // 访存操作码
      .exc_in      (exc_out),
      .mem_out     (mem_out),
      .isloadEnable(isloadEnable)
  );

  /**************写回模块******************************/
  wire [`XLEN-1:0] wb_data;
  writeback u_writeback (
      .exc_data_in (exc_out),
      .mem_data_in (mem_out),
      .isloadEnable(isloadEnable),
      .wb_data     (wb_data)
  );

endmodule

