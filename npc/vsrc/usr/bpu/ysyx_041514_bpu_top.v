`include "sysconfig.v"


module ysyx_041514_bpu_top (
    input [`ysyx_041514_XLEN_BUS] inst_data_i,
    input [`ysyx_041514_XLEN_BUS] pc_if_i,
    output [`ysyx_041514_XLEN_BUS] bpu_pc_o,
    output bpu_pc_valid_o
);


  wire [`ysyx_041514_XLEN_BUS] _inst = inst_data_i;
  wire [4:0] _rd = _inst[11:7];
  wire [2:0] _func3 = _inst[14:12];
  wire [4:0] _rs1 = _inst[19:15];
  wire [4:0] _rs2 = _inst[24:20];
  wire [6:0] _func7 = _inst[31:25];

  // 不同指令类型的立即数
  wire [`ysyx_041514_IMM_LEN-1:0] _immI = {{21 + 32{_inst[31]}}, _inst[30:20]};
  wire [`ysyx_041514_IMM_LEN-1:0] _immS = {
    {21 + 32{_inst[31]}}, _inst[30:25], _inst[11:8], _inst[7]
  };
  wire [`ysyx_041514_IMM_LEN-1:0] _immB = {
    {20 + 32{_inst[31]}}, _inst[7], _inst[30:25], _inst[11:8], 1'b0
  };
  wire [`ysyx_041514_IMM_LEN-1:0] _immU = {
    {1 + 32{_inst[31]}}, _inst[30:20], _inst[19:12], 12'b0
  };
  wire [`ysyx_041514_IMM_LEN-1:0] _immJ = {
    {12 + 32{_inst[31]}}, _inst[19:12], _inst[20], _inst[30:25], _inst[24:21], 1'b0
  };
  wire [`ysyx_041514_IMM_LEN-1:0] _immCSR = {59'b0, _inst[19:15]};

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

  wire [`ysyx_041514_XLEN_BUS] branch_pc_bru = pc_if_i + _immB;

  // 向后跳转跳转，向前跳转不跳转BTFN (Backward Taken，Forward Not-taken)
  wire branch_jump_valid = _immB[`ysyx_041514_XLEN-1] & _type_branch;

  wire [`ysyx_041514_XLEN_BUS] jal_pc_bru = pc_if_i + _immJ;
  wire jal_jump_valid = _type_jal;

  wire [`ysyx_041514_XLEN_BUS]bpu_pc = ({`ysyx_041514_XLEN{_type_branch}}&branch_pc_bru)
                                     | ({`ysyx_041514_XLEN{_type_jal}}&jal_pc_bru);

  wire bpu_pc_valid = branch_jump_valid & _type_branch | jal_jump_valid & _type_jal;


  assign bpu_pc_o = bpu_pc;
  assign bpu_pc_valid_o = bpu_pc_valid;


endmodule



