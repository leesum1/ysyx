`include "./../sysconfig.v"
module pc (
    input                      clk,
    input                      rst,
    input      [`PCOP_LEN-1:0] pc_op,     // pc 操作码
    input      [    `XLEN-1:0] rs1_data,
    input      [    `XLEN-1:0] imm_data,
    output reg [    `XLEN-1:0] pc_out
);
  wire _pcop_branch = (pc_op == `PCOP_BRANCH);
  wire _pcop_jal = (pc_op == `PCOP_JAL);
  wire _pcop_jalr = (pc_op == `PCOP_JALR);
  wire _pcop_inc4 = (pc_op == `PCOP_INC4);
  wire _pcop_none = (pc_op == `PCOP_NONE);


  /* 选择跳转位置 */
  wire [`XLEN-1:0] _pc_a_in = (_pcop_jalr) ? rs1_data : _pc_current;
  wire [`XLEN-1:0] _pc_b_in = (_pcop_inc4)?`XLEN'd4:
                              (_pcop_branch | _pcop_jal | _pcop_jalr)?imm_data:
                              `XLEN'd0;
  wire [`XLEN-1:0] _pc_next;
  reg [`XLEN-1:0] _pc_current;
  assign _pc_next = _pc_a_in + _pc_b_in;

  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`PC_RESET_ADDR)
  ) u_regpc (
      .clk (clk),
      .rst (rst),
      .din (_pc_next),
      .dout(_pc_current),
      .wen (1)
  );

  assign pc_out = _pc_current;
endmodule
