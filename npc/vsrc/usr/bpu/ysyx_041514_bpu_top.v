`include "sysconfig.v"


module ysyx_041514_bpu_top (
    input [`ysyx_041514_XLEN_BUS] inst_data_i,
    input [`ysyx_041514_XLEN_BUS] pc_if_i,
    // output [`ysyx_041514_XLEN_BUS] bpu_pc_o,
    output [`ysyx_041514_XLEN_BUS] bpu_pc_op1_o,
    output [`ysyx_041514_XLEN_BUS] bpu_pc_op2_o,
    output bpu_pc_valid_o
);


  wire [`ysyx_041514_XLEN_BUS] _inst = inst_data_i;
  // wire [4:0] _rd = _inst[11:7];
  // wire [2:0] _func3 = _inst[14:12];
  wire [4:0] _rs1 = _inst[19:15];
  // wire [4:0] _rs2 = _inst[24:20];
  // wire [6:0] _func7 = _inst[31:25];
  wire rs1_idx_zero = _rs1 == 'b0;

  // 不同指令类型的立即数
  wire [`ysyx_041514_IMM_LEN-1:0] _immI = {{21 + 32{_inst[31]}}, _inst[30:20]};
  wire [`ysyx_041514_IMM_LEN-1:0] _immB = {
    {20 + 32{_inst[31]}}, _inst[7], _inst[30:25], _inst[11:8], 1'b0
  };
  wire [`ysyx_041514_IMM_LEN-1:0] _immJ = {
    {12 + 32{_inst[31]}}, _inst[19:12], _inst[20], _inst[30:25], _inst[24:21], 1'b0
  };


  /* 分解_opcode */
  wire [6:0] _opcode = _inst[6:0];
  wire _opcode_1_0_11 = (_opcode[1:0] == 2'b11);
  wire _opcode_4_2_000 = (_opcode[4:2] == 3'b000);
  wire _opcode_4_2_001 = (_opcode[4:2] == 3'b001);
  wire _opcode_4_2_011 = (_opcode[4:2] == 3'b011);
  wire _opcode_6_5_11 = (_opcode[6:5] == 2'b11);

  wire _type_branch = _opcode_6_5_11 & _opcode_4_2_000 & _opcode_1_0_11;
  wire _type_jalr = _opcode_6_5_11 & _opcode_4_2_001 & _opcode_1_0_11;
  wire _type_jal = _opcode_6_5_11 & _opcode_4_2_011 & _opcode_1_0_11;


  // 向后跳转跳转，向前跳转不跳转BTFN (Backward Taken，Forward Not-taken) rs1+imm
  wire branch_jump_valid = ((_immB[`ysyx_041514_XLEN-1]) & _type_branch);
  // wire branch_jump_valid = 1'b1;

  // jal 指令，跳转地址在地址中得到 pc+imm
  wire jal_jump_valid = _type_jal;

  // jalr 指令，rs1 为 x0 时，可以直接得到跳转地址 rs1+imm
  wire jalr_pc_valid = _type_jalr & rs1_idx_zero;


  wire [`ysyx_041514_XLEN_BUS] bpu_pc_op1 = ({`ysyx_041514_XLEN{_type_branch|_type_jal}}&pc_if_i)
                                          | ({`ysyx_041514_XLEN{_type_jalr}}&64'b0);

  wire [`ysyx_041514_XLEN_BUS] bpu_pc_op2=({`ysyx_041514_XLEN{_type_branch}}&_immB)
                                          | ({`ysyx_041514_XLEN{_type_jalr}}&_immI)
                                          | ({`ysyx_041514_XLEN{_type_jal}}&_immJ);

  // wire [`ysyx_041514_XLEN_BUS] bpu_pc = bpu_pc_op1 + bpu_pc_op2;

  wire bpu_pc_valid = branch_jump_valid & _type_branch
                    | jal_jump_valid & _type_jal
                    | jalr_pc_valid&_type_jalr;


  // assign bpu_pc_o = bpu_pc;
  assign bpu_pc_op1_o   = bpu_pc_op1;
  assign bpu_pc_op2_o   = bpu_pc_op2;
  assign bpu_pc_valid_o = bpu_pc_valid;


endmodule



