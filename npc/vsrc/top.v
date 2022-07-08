`include "sysconfig.v"


/* 需要设为为input熟悉才能才仿真中改变值 */
module top (
    input                      clk,
    input                      rst,
    output reg [    `XLEN-1:0] pc,
    input      [`INST_LEN-1:0] inst_data,
    output                     inst_en,
    // ALU
    input      [    `XLEN-1:0] alu_a_i,
    input      [    `XLEN-1:0] alu_b_i,
    input      [          3:0] alu_op_i,
    output     [    `XLEN-1:0] alu_out,
    output                     OF,
    output                     ZF,
    output                     SLT,
    output                     CF,
    output                     SF,

    /* 测试用 */
    output [`XLEN-1:0] sra_out,
    output [`XLEN-1:0] srl_out,
    output [`XLEN-1:0] sll_out
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

  alu u_alu (
      /* ALU 端口 */
      .alu_a_i (alu_a_i),
      .alu_b_i (alu_b_i),
      .alu_out (alu_out),
      .alu_op_i(alu_op_i),
      /* 标志位 */
      .OF      (OF),
      .ZF      (ZF),
      .SLT     (SLT),
      .CF      (CF),
      .SF      (SF),
      /* 测试用 */
      .sra_out (sra_out),
      .srl_out (srl_out),
      .sll_out (sll_out)
  );

  dcode u_dcode (
      .inst_data(inst_data),
      .inst_out (inst_en)
  );

endmodule

