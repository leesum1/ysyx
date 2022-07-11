`include "sysconfig.v"


/* 需要设为为input熟悉才能才仿真中改变值 */
module top (
    input                  clk,
    input                  rst,
    output reg [`XLEN-1:0] pc,


    /****************decode******************/
    // 手动指定指令
    input [`INST_LEN-1:0] inst_data,


    /* 测试信号 */
    output inst_out
);


  /* PC 模块 */
  pc u_pc (
      .clk   (clk),
      .rst   (rst),
      .pc_out(pc)
  );
  //   // 根据pc取指令
  //   fetch u_fetch (
  //       //指令地址
  //       .inst_addr(pc),
  //       //指令内容
  //       .inst_data(inst_data)
  //   );


  /***************译码模块*****************/
  /* 译码输出的指令操作数 */
  wire [`REG_ADDRWIDTH-1:0] rs1_idx;
  wire [`REG_ADDRWIDTH-1:0] rs2_idx;
  wire [`REG_ADDRWIDTH-1:0] rd_idx;
  wire [      `IMM_LEN-1:0] imm_data;

  wire                      isNeed_rs1;
  wire                      isNeed_rs2;
  wire                      isNeed_rd;
  wire                      isNeed_imm;
  /* 译码器输出的控制信号 */
  wire [    `ALUOP_LEN-1:0] alu_op;
  wire [    `MEMOP_LEN-1:0] mem_op;
  wire [    `EXCOP_LEN-1:0] exc_op;

  dcode u_dcode (
      /* 输入信号 */
      .inst_data (inst_data),
      /*输出信号： */
      .rs1_idx   (rs1_idx),
      .rs2_idx   (rs2_idx),
      .rd_idx    (rd_idx),
      .imm_data  (imm_data),
      .isNeed_rs1(isNeed_rs1),
      .isNeed_rs2(isNeed_rs2),
      .isNeed_rd (isNeed_rd),
      .isNeed_imm(isNeed_imm),
      .alu_op    (alu_op),
      // alu 操作码
      .mem_op    (mem_op),
      // 访存操作码
      .exc_op    (exc_op),
      // exc 操作码
      /* 测试信号 */
      .inst_out  (inst_out)
  );


  /****************寄存器组***************/
  /* 寄存器组输入数据 */
  wire [`XLEN-1:0] rs1_data;
  wire [`XLEN-1:0] rs2_data;
  wire [`XLEN-1:0] w_data = wb_data;
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
      .wen       (1'b1)
  );

  /**********************执行模块**********************/
  wire [`XLEN-1:0] exc_out;
  execute u_execute (
      .pc        (pc),
      .rd_idx    (rd_idx),
      .rs1_data  (rs1_data),
      .rs2_data  (rs2_data),
      .imm_data  (imm_data),
      .isNeed_rs1(isNeed_rs1),
      .isNeed_rs2(isNeed_rs2),
      .isNeed_rd (isNeed_rd),
      .isNeed_imm(isNeed_imm),
      .alu_op    (alu_op),
      // alu 操作码
      .mem_op    (mem_op),
      // 访存操作码
      .exc_op    (exc_op),
      // exc 操作码
      .exc_out   (exc_out)
  );

  /*******************访存模块*************************/
  wire [`XLEN-1:0] mem_out;
  wire isloadEnable;
  memory u_memory (
      .pc          (pc),
      .rd_idx      (rd_idx),
      .rs1_data    (rs1_data),
      .rs2_data    (rs2_data),
      .imm_data    (imm_data),
      .isNeed_rs1  (isNeed_rs1),
      .isNeed_rs2  (isNeed_rs2),
      .isNeed_rd   (isNeed_rd),
      .isNeed_imm  (isNeed_imm),
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

