`include "sysconfig.v"
// 使用触发器模板的示例

module top (
    input                      clk,
    input                      rst,
    output reg [    `XLEN-1:0] pc,
    output     [`INST_LEN-1:0] inst_data,

    // ALU
    input [`XLEN-1:0] alu_a_i,
    input [`XLEN-1:0] alu_b_i,
    input [3:0] alu_op_i,
    output [`XLEN-1:0] alu_out,
    output OF,
    output ZF,
    output SLT,
    output CF,
    output SF
);


  //pc
  pc u_pc (
      .clk   (clk),
      .rst   (rst),
      .pc_out(pc)
  );
  // 根据pc取指令
  fetch u_fetch (
      //指令地址
      .inst_addr(pc),
      //指令内容
      .inst_data(inst_data)
  );

  alu u_alu (
      .alu_a_i (alu_a_i),
      .alu_b_i (alu_b_i),
      .alu_op_i(alu_op_i),
      .alu_out (alu_out),
      .OF      (OF),
      .ZF      (ZF),
      .SLT     (SLT),
      .CF      (CF),
      .SF      (SF)
  );

endmodule

