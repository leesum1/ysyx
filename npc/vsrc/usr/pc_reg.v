`include "sysconfig.v"
// /** 纯组合逻辑电路
//  * 1.branch_pc：来自exc阶段
//  * 2.csr_pc：来自mem阶段
//  * 3.pc_next：输出给if阶段
// ×/

module pc_reg (
    input                 clk,
    input                 rst,
    input                 stall_valid_i,
    input [`PCOP_LEN-1:0] pc_op_i,        // pc 操作码,在docode阶段生成,来自ex/mem
    input [    `XLEN_BUS] rs1_data_i,     //用于branch计算,来自ex/mem
    input [    `XLEN_BUS] imm_data_i,     //用于branch计算,来自ex/mem
    input [    `XLEN_BUS] exc_alu_data_i, //branch 跳转是否成立,ex/mem

    input  [`XLEN_BUS] clint_pc_i,        //trap pc,来自mem
    input              clint_pc_valid_i,  //trap pc valide,来自mem
    output [`XLEN_BUS] pc_o               //输出pc
);

  /* pc 操作码 */
  wire _pcop_branch = (pc_op_i == `PCOP_BRANCH);  // 分支指令: pc = pc + imm
  wire _pcop_jal = (pc_op_i == `PCOP_JAL);  // jal 指令: pc = pc + imm
  wire _pcop_jalr = (pc_op_i == `PCOP_JALR);  // jalr 指令: pc = rs1 + imm
  wire _pcop_inc4 = (pc_op_i == `PCOP_INC4);  // pc 自增: pc = pc +4
  //TODO:trap
  wire _pcop_trap = (pc_op_i == `PCOP_TRAP) | clint_pc_valid_i;  // trap 指令: pc = clint_pc_i
  wire _pcop_none = (pc_op_i == `PCOP_NONE);  // 暂停: pc = pc

  wire _isready_branch = (exc_alu_data_i == `XLEN'b1) & _pcop_branch;  //条件跳转指令
  wire _isready_inc4 = (_pcop_inc4) | ((~_isready_branch) & _pcop_branch);// 跳转指令退化成 +4

  /* 并行选择器:根据操作码选择跳转位置 */
  wire [`XLEN_BUS] _pc_a_in = ({`XLEN{_isready_branch | _pcop_jal | _isready_inc4|_pcop_none}} &  _pc_current) |
                                ({`XLEN{_pcop_jalr}} & rs1_data_i);

  wire [`XLEN_BUS] _pc_b_in = ({`XLEN{_isready_branch|_pcop_jal|_pcop_jalr}}&imm_data_i) |
                                ({`XLEN{_isready_inc4}} & `XLEN'd4)|
                                ({`XLEN{_pcop_none}} & `XLEN'd0);


  wire [`XLEN_BUS] _pc_next, _pc_current;
  wire [`XLEN_BUS] _pc_normal = _pc_a_in + _pc_b_in;
  // trap 优先级高
  assign _pc_next = clint_pc_valid_i ? clint_pc_i : _pc_normal;
  assign pc_o = _pc_current;


  wire _pc_reg_wen = ~stall_valid_i;
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`PC_RESET_ADDR)
  ) u_pc_dreg (
      .clk (clk),
      .rst (rst),
      .din (_pc_next),
      .dout(_pc_current),
      .wen (_pc_reg_wen)
  );
endmodule


// module pc (
//     input                 clk,
//     input                 rst,
//     input [`PCOP_LEN-1:0] pc_op_i,          // pc 操作码
//     input [    `XLEN_BUS] rs1_data_i,
//     input [    `XLEN_BUS] imm_data_i,
//     input [    `XLEN_BUS] exc_data_i,
//     input [    `XLEN_BUS] clint_pc_i,
//     input                 clint_pc_valid_i,

//     output reg [`XLEN_BUS] pc_out_o
// );
//   /* pc 操作码 */
//   wire _pcop_branch = (pc_op_i == `PCOP_BRANCH);  // 分支指令: pc = pc + imm
//   wire _pcop_jal = (pc_op_i == `PCOP_JAL);  // jal 指令: pc = pc + imm
//   wire _pcop_jalr = (pc_op_i == `PCOP_JALR);  // jalr 指令: pc = rs1 + imm
//   wire _pcop_inc4 = (pc_op_i == `PCOP_INC4);  // pc 自增: pc = pc +4
//   wire _pcop_trap = (pc_op_i == `PCOP_TRAP);  // trap 指令: pc = clint_pc_i
//   wire _pcop_none = (pc_op_i == `PCOP_NONE);  // 暂停: pc = pc

//   wire _isready_branch = (exc_data_i == `XLEN'b1) & _pcop_branch;  //条件跳转指令
//   wire _isready_inc4 = (_pcop_inc4) | ((~_isready_branch) & _pcop_branch);// 跳转指令退化成 +4

//   /* 并行选择器:根据操作码选择跳转位置 */
//   wire [`XLEN_BUS] _pc_a_in = ({`XLEN{_isready_branch | _pcop_jal | _isready_inc4|_pcop_none}} &  _pc_current) |
//                               ({`XLEN{_pcop_jalr}} & rs1_data_i)|
//                               ({`XLEN{_pcop_trap}} & clint_pc_i);

//   wire [`XLEN_BUS] _pc_b_in = ({`XLEN{_isready_branch|_pcop_jal|_pcop_jalr}}&imm_data_i) |
//                               ({`XLEN{_isready_inc4}} & `XLEN'd4)|
//                               ({`XLEN{_pcop_none|_pcop_trap}} & `XLEN'd0);


//   wire [`XLEN_BUS] _pc_next;
//   reg [`XLEN_BUS] _pc_current;
//   assign _pc_next = _pc_a_in + _pc_b_in;

//   regTemplate #(
//       .WIDTH    (`XLEN),
//       .RESET_VAL(`PC_RESET_ADDR)
//   ) u_regpc (
//       .clk (clk),
//       .rst (rst),
//       .din (_pc_next),
//       .dout(_pc_current),
//       .wen (1)
//   );
//   assign pc_out_o = _pc_current;
// endmodule
