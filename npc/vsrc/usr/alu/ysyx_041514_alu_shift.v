`include "sysconfig.v"
// 1. 移位器实现，能够实现 逻辑左移、逻辑右移、算数右移
// 2. 采用掩码算法，将右移转换为左移，节省资源
module ysyx_041514_alu_shift (
    input shift_sra_i,
    input shift_srl_i,
    input shift_sll_i,
    input shift32_valid_i,
    input [`ysyx_041514_XLEN-1:0] shift_num_i,
    input [5:0] shift_count_i,
    output [`ysyx_041514_XLEN-1:0] shift_out_o
);
  wire _op_shift = shift_sra_i | shift_srl_i | shift_sll_i;
  /* 选择是否忽略高32位 */
  wire [`ysyx_041514_XLEN-1:0] _shift_num = (shift32_valid_i) ? {32'b0, shift_num_i[31:0]} : shift_num_i;
  wire [`ysyx_041514_XLEN-1:0] _shift_num_inv;
  /* 位颠倒 */
  ysyx_041514_Vectorinvert #(
      .DATA_LEN(`ysyx_041514_XLEN)
  ) u_ysyx_041514_Vectorinvert1 (
      .in (_shift_num),
      .out(_shift_num_inv)
  );
  //将右移转换为左移
  wire [`ysyx_041514_XLEN-1:0] _shifter_in1 = {`ysyx_041514_XLEN{_op_shift}} & ((shift_sra_i | shift_srl_i) ? _shift_num_inv : _shift_num);//操作数
  wire [5:0] _shifter_in2 = (shift32_valid_i) ? {1'b0, shift_count_i[4:0]} : shift_count_i;  //TODO:BUG(很坑)移位次数
  /* 实际移位操作,用一个移位器实现左移和右移 */
  wire [`ysyx_041514_XLEN-1:0] _shifter_res = _shifter_in1 << _shifter_in2;

  wire [`ysyx_041514_XLEN-1:0] _sll_res = _shifter_res;  //逻辑左移结果
  /*逻辑右移结果,srl_in->位颠倒->移位器(左移)->位颠倒->srl_out*/
  wire [`ysyx_041514_XLEN-1:0] _srl_res;
  ysyx_041514_Vectorinvert #(
      .DATA_LEN(`ysyx_041514_XLEN)
  ) u_ysyx_041514_Vectorinvert2 (
      .in (_sll_res),
      .out(_srl_res)
  );
  /* 选择掩码,64位移位和32位移位掩码不同 */
  wire [5:0] _eff_mask_shift_count = (shift32_valid_i) ? (_shifter_in2 + 6'd32) : _shifter_in2;
  /* 选择符号位,32位移位需要忽略输入num的高32位 */
  wire _lastbit = (shift32_valid_i) ? _shift_num[31] : _shift_num[`ysyx_041514_XLEN-1];

  /* 算数右移结果，采用掩码算法实现算数右移 */
  wire [`ysyx_041514_XLEN-1:0] _eff_mask = (~(`ysyx_041514_XLEN'b0)) >> _eff_mask_shift_count;
  wire [`ysyx_041514_XLEN-1:0] _sra_res = (_srl_res & _eff_mask) | ({`ysyx_041514_XLEN{_lastbit}} & (~_eff_mask));

  /* 多路选择器选择最终结果 */
  wire [`ysyx_041514_XLEN-1:0] _shift_out = ({`ysyx_041514_XLEN{shift_srl_i}}&_srl_res) |
                                ({`ysyx_041514_XLEN{shift_sra_i}}&_sra_res) |
                                ({`ysyx_041514_XLEN{shift_sll_i}}&_sll_res);
  assign shift_out_o = _shift_out;
endmodule
