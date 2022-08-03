`include "./../sysconfig.v"
module pc (
    input                      clk,
    input                      rst,
    input      [`PCOP_LEN-1:0] pc_op,             // pc 操作码
    input      [    `XLEN-1:0] rs1_data,
    input      [    `XLEN-1:0] imm_data,
    input      [    `XLEN-1:0] execute_data,
    input      [    `XLEN-1:0] clint_pc_i,
    input                      clint_pc_valid_i,
    output reg [    `XLEN-1:0] pc_out
);
  /* pc 操作码 */
  wire _pcop_branch = (pc_op == `PCOP_BRANCH);  // 分支指令: pc = pc + imm
  wire _pcop_jal = (pc_op == `PCOP_JAL);  // jal 指令: pc = pc + imm
  wire _pcop_jalr = (pc_op == `PCOP_JALR);  // jalr 指令: pc = rs1 + imm
  wire _pcop_inc4 = (pc_op == `PCOP_INC4);  // pc 自增: pc = pc +4
  wire _pcop_trap = (pc_op == `PCOP_TRAP);  // trap 指令: pc = clint_pc_i
  wire _pcop_none = (pc_op == `PCOP_NONE);  // 暂停: pc = pc

  wire _isready_branch = (execute_data == `XLEN'b1) & _pcop_branch;  //条件跳转指令
  wire _isready_inc4 = (_pcop_inc4) | ((~_isready_branch) & _pcop_branch);// 跳转指令退化成 +4

  /* 并行选择器:根据操作码选择跳转位置 */
  wire [`XLEN-1:0] _pc_a_in = ({`XLEN{_isready_branch | _pcop_jal | _isready_inc4|_pcop_none}} &  _pc_current) |
                              ({`XLEN{_pcop_jalr}} & rs1_data)|
                              ({`XLEN{_pcop_trap}} & clint_pc_i);

  wire [`XLEN-1:0] _pc_b_in = ({`XLEN{_isready_branch|_pcop_jal|_pcop_jalr}}&imm_data) |
                              ({`XLEN{_isready_inc4}} & `XLEN'd4)|
                              ({`XLEN{_pcop_none|_pcop_trap}} & `XLEN'd0);


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
