`include "sysconfig.v"


module ysyx_041514_genimm (
    input [`ysyx_041514_INST_LEN-1:0] inst_data_i,
    input [4:0] imm_type_i,  // [i,s,b,u,j]
    output [`ysyx_041514_XLEN_BUS] imm_data_o
);


  wire i_type, s_type, b_type, u_type, j_type;
  assign {i_type, s_type, b_type, u_type, j_type} = imm_type_i;


  wire [`ysyx_041514_INST_LEN-1:0] _inst = inst_data_i;

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
  wire [`ysyx_041514_IMM_LEN-1:0] _immZ = {59'b0, _inst[19:15]};


  /* assign 实现多路选择器：根据指令类型选立即数 */
  wire [`ysyx_041514_IMM_LEN-1:0] _imm_data = ({`ysyx_041514_IMM_LEN{i_type}}&_immI) |
                                  ({`ysyx_041514_IMM_LEN{s_type}}&_immS) |
                                  ({`ysyx_041514_IMM_LEN{b_type}}&_immB) |
                                  ({`ysyx_041514_IMM_LEN{u_type}}&_immU) |
                                  ({`ysyx_041514_IMM_LEN{j_type}}&_immJ);


  assign imm_data_o = _imm_data;

endmodule
