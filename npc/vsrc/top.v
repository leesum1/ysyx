`include "sysconfig.v"


/* 需要设为为input熟悉才能才仿真中改变值 */
module top (
    input                  clk,
    input                  rst,
    output reg [`XLEN-1:0] pc,


    /****************decode******************/
    // 手动指定指令
    input [`INST_LEN-1:0] inst_data,
    // 改变寄存器组值
    input wire [`REG_ADDRWIDTH-1:0] w_idx,
    input wire [`XLEN-1:0] w_data,
    /* 测试信号 */
    output inst_out
);


  //pc
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


  wire [`REG_ADDRWIDTH-1:0] rs1_idx;
  wire [`REG_ADDRWIDTH-1:0] rs2_idx;
  wire [`REG_ADDRWIDTH-1:0] rd_idx;
  wire [      `IMM_LEN-1:0] imm_data;
  wire [    `ALUOP_LEN-1:0] alu_op;
  dcode u_dcode (
      /* 输入信号 */
      .inst_data(inst_data),
      /*输出信号： */
      .rs1_idx  (rs1_idx),
      .rs2_idx  (rs2_idx),
      .rd_idx   (rd_idx),
      .imm_data (imm_data),
      .alu_op   (alu_op),
      /* 测试信号 */
      .inst_out (inst_out)
  );

  wire [`XLEN-1:0] rs1_data;
  wire [`XLEN-1:0] rs2_data;

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


  //   alu u_alu (
  //       /* ALU 端口 */
  //       .alu_a_i (rs1_data),
  //       .alu_b_i (rs2_data),
  //       .alu_out (alu_out),
  //       .alu_op_i(alu_op),
  //       /* 标志位 */
  //       .OF      (OF),
  //       .ZF      (ZF),
  //       .SLT     (SLT),
  //       .CF      (CF),
  //       .SF      (SF),
  //       /* 测试用 */
  //       .sra_out (sra_out),
  //       .srl_out (srl_out),
  //       .sll_out (sll_out)
  //   );




endmodule

