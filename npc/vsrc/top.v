`include "sysconfig.v"


/* 需要设为为input熟悉才能才仿真中改变值 */
module top (
    input clk,
    input rst
);


  /* PC 模块 用于选择吓一跳指令地址*/
  reg [`XLEN-1:0] pc;
  pc u_pc (
      .clk             (clk),
      .rst             (rst),
      .pc_op_i         (pc_op),
      // pc 操作码
      .rs1_data_i      (rs1_data),
      .imm_data_i      (imm_data),
      .pc_out_o        (pc),             // to fetch
      .exc_data_i      (exc_alu_data),   // from exe
      .clint_pc_i      (clint_pc),       // from clint
      .clint_pc_valid_i(clint_pc_valid)  // from clint
  );
  /* 取指模块 */
  wire [`INST_LEN-1:0] inst_data;
  fetch u_fetch (
      .clk(clk),
      //指令地址
      .inst_addr_i(pc),
      //指令内容
      .inst_data_o(inst_data)
  );


  /***************译码模块*****************/
  /* 译码输出的指令操作数 */
  wire [    `REG_ADDRWIDTH-1:0 ] rs1_idx;
  wire [    `REG_ADDRWIDTH-1:0 ] rs2_idx;
  wire [    `REG_ADDRWIDTH-1:0 ] rd_idx;
  wire [`CSR_REG_ADDRWIDTH-1:0 ] csr_idx;
  wire [          `IMM_LEN-1:0 ] imm_data;
  wire [          `IMM_LEN-1:0 ] csr_imm;
  wire                           csr_imm_valid;

  /* 译码器输出的控制信号 */
  wire [        `ALUOP_LEN-1:0 ] alu_op;
  wire [        `MEMOP_LEN-1:0 ] mem_op;
  wire [        `EXCOP_LEN-1:0 ] exc_op;
  wire [         `PCOP_LEN-1:0 ] pc_op;
  wire [        `CSROP_LEN-1:0 ] csr_op;
  wire [             `TRAP_BUS]  trap_bus;
  dcode u_dcode (
      /* 输入信号 */
      .inst_data_i    (inst_data),
      /*输出信号： */
      .rs1_idx_o      (rs1_idx),
      .rs2_idx_o      (rs2_idx),
      .rd_idx_o       (rd_idx),
      .imm_data_o     (imm_data),
      /* CSR 译码结果 */
      .csr_imm_o      (csr_imm),
      .csr_imm_valid_o(csr_imm_valid),
      .csr_idx_o      (csr_idx),
      .alu_op_o       (alu_op),
      // alu 操作码
      .mem_op_o       (mem_op),
      // mem 操作码
      .exc_op_o       (exc_op),
      // exc 操作码
      .pc_op_o        (pc_op),
      // pc 操作码
      // csr 操作码
      .csr_op_o       (csr_op),
      .trap_bus_o     (trap_bus)        //to clint
  );


  /****************通用寄存器组***************/
  /* 寄存器组输入数据 */
  wire [         `XLEN-1:0]                       rs1_data;
  wire [         `XLEN-1:0]                       rs2_data;
  wire [         `XLEN-1:0] write_data = wb_data;
  wire [`REG_ADDRWIDTH-1:0] write_idx = rd_idx;

  rv64reg u_rv64reg (
      .clk(clk),
      /* 读取数据 */
      .rs1_idx_i(rs1_idx),
      .rs2_idx_i(rs2_idx),
      .rs1_data_o(rs1_data),
      .rs2_data_o(rs2_data),
      /* 写入数据 */
      .write_idx_i(write_idx),
      .write_data_i(write_data),
      .write_data_valid_i(1'b1)  // 写入一直使能,若该指令不需要写寄存器 w_idx = 0
  );

  /*****************CSR寄存器组*********************/
  /* 单独引出寄存器(写) */
  wire [`XLEN-1:0] csr_mepc_writedata;
  wire [`XLEN-1:0] csr_mcause_writedata;
  wire [`XLEN-1:0] csr_mtval_writedata;
  wire [`XLEN-1:0] csr_mtvec_writedata;
  wire [`XLEN-1:0] csr_mstatus_writedata;

  wire csr_mepc_write_valid;
  wire csr_mcause_write_valid;
  wire csr_mtval_write_valid;
  wire csr_mtvec_write_valid;
  wire csr_mstatus_write_valid;
  /* 单独引出寄存器(读) */
  wire [`XLEN-1:0] csr_mepc_readdata;
  wire [`XLEN-1:0] csr_mcause_readdata;
  wire [`XLEN-1:0] csr_mtval_readdata;
  wire [`XLEN-1:0] csr_mtvec_readdata;
  wire [`XLEN-1:0] csr_mstatus_readdata;

  /* 读取数据端口 */
  wire [`CSR_REG_ADDRWIDTH-1:0] csr_readaddr = csr_idx;
  wire [`XLEN-1:0] csr_readdata;
  /* 写入数据端口 */
  reg [`CSR_REG_ADDRWIDTH-1:0] csr_writeaddr = csr_idx;
  wire csr_write_valid = exc_csr_valid;
  wire [`XLEN-1:0] csr_writedata = exc_csr_data;

  rv64_csr_regfile u_rv64_csr_regfile (
      .clk                      (clk),
      .rst                      (rst),
      /* 单独引出寄存器(写) */
      .csr_mstatus_writedata_i  (csr_mstatus_writedata),
      .csr_mepc_writedata_i     (csr_mepc_writedata),
      .csr_mcause_writedata_i   (csr_mcause_writedata),
      .csr_mtval_writedata_i    (csr_mtval_writedata),
      .csr_mtvec_writedata_i    (csr_mtvec_writedata),
      .csr_mstatus_write_valid_i(csr_mstatus_write_valid),
      .csr_mepc_write_valid_i   (csr_mepc_write_valid),
      .csr_mcause_write_valid_i (csr_mcause_write_valid),
      .csr_mtval_write_valid_i  (csr_mtval_write_valid),
      .csr_mtvec_write_valid_i  (csr_mtvec_write_valid),
      /* 单独引出寄存器(读) */
      .csr_mstatus_readdata_o   (csr_mstatus_readdata),
      .csr_mepc_readdata_o      (csr_mepc_readdata),
      .csr_mcause_readdata_o    (csr_mcause_readdata),
      .csr_mtval_readdata_o     (csr_mtval_readdata),
      .csr_mtvec_readdata_o     (csr_mtvec_readdata),
      /* 读取数据端口 */
      .csr_readaddr_i           (csr_readaddr),
      .csr_readdata_o           (csr_readdata),
      /* 写入数据端口 */
      .csr_writeaddr_i          (csr_writeaddr),
      .csr_write_valid_i        (csr_write_valid),
      .csr_writedata_i          (csr_writedata)
  );

  /**********************执行模块**********************/

  wire [`XLEN-1:0] exc_alu_data;
  wire [`XLEN-1:0] exc_csr_data;
  wire [`XLEN-1:0] csr_data = csr_readdata;
  wire exc_csr_valid;
  execute_top u_execute (
      .pc             (pc),
      .rd_idx         (rd_idx),
      .rs1_data_i     (rs1_data),       // rs1 数据
      .rs2_data_i     (rs2_data),       // rs2 数据
      .imm_data_i     (imm_data),       // 立即数数据
      .csr_data_i     (csr_data),       // csr 数据
      .csr_imm_i      (csr_imm),        // csr 立即数
      .csr_imm_valid_i(csr_imm_valid),  // 是否需要 csr 立即数
      .alu_op_i       (alu_op),         // alu 操作码
      .mem_op_i       (mem_op),         // 访存操作码
      .exc_op_i       (exc_op),         // exc 操作码
      .csr_op_i       (csr_op),         // csr 操作码
      .exc_alu_data_o (exc_alu_data),   // 执行阶段 alu 输出
      .exc_csr_data_o (exc_csr_data),   // csr 写回数据
      .exc_csr_valid_o(exc_csr_valid)   // csr 写回使能
  );

  /*******************访存模块*************************/
  wire [`XLEN-1:0] mem_data;
  wire load_valid;
  memory u_memory (
      .clk           (clk),
      .rst           (rst),
      .pc_i          (pc),
      .rd_idx_i      (rd_idx),
      .rs1_data_i    (rs1_data),
      .rs2_data_i    (rs2_data),
      .imm_data_i    (imm_data),
      .mem_op_i      (mem_op),
      // 访存操作码
      .exc_alu_data_i(exc_alu_data),
      .mem_data_o    (mem_data),
      .load_valid_o  (load_valid)
  );

  /**************写回模块******************************/
  wire [`XLEN-1:0] wb_data;
  writeback u_writeback (
      .exc_alu_data_i  (exc_alu_data),
      .mem_data_i  (mem_data),
      .load_valid_i(load_valid),
      .wb_data_o   (wb_data)
  );

  /*******************中断异常控制模块*****************************/

  wire [`XLEN-1:0] clint_pc;
  wire clint_pc_valid;
  clint u_clint (
      // input wire clk,
      // input wire rst,
      .pc_i                     (pc),
      .inst_data_i              (inst_data),
      /* TARP 总线 */
      .trap_bus_i               (trap_bus),                 //from decode
      /* trap 所需寄存器，来自于 csr (读)*/
      .csr_mstatus_readdata_i   (csr_mstatus_readdata),
      .csr_mepc_readdata_i      (csr_mepc_readdata),
      .csr_mcause_readdata_i    (csr_mcause_readdata),
      .csr_mtval_readdata_i     (csr_mtval_readdata),
      .csr_mtvec_readdata_i     (csr_mtvec_readdata),
      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_o  (csr_mstatus_writedata),
      .csr_mepc_writedata_o     (csr_mepc_writedata),
      .csr_mcause_writedata_o   (csr_mcause_writedata),
      .csr_mtval_writedata_o    (csr_mtval_writedata),
      .csr_mtvec_writedata_o    (csr_mtvec_writedata),
      .csr_mstatus_write_valid_o(csr_mstatus_write_valid),
      .csr_mepc_write_valid_o   (csr_mepc_write_valid),
      .csr_mcause_write_valid_o (csr_mcause_write_valid),
      .csr_mtval_write_valid_o  (csr_mtval_write_valid),
      .csr_mtvec_write_valid_o  (csr_mtvec_write_valid),
      /* 输出至取指阶段 pc ,异常跳转 pc */
      .clint_pc_o               (clint_pc),
      .clint_pc_valid_o         (clint_pc_valid)
  );

endmodule

