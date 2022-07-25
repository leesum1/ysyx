`include "./../sysconfig.v"

module alu_shift (
    input shift_sra,
    input shift_srl,
    input shift_sll,
    input isshift32,
    input [`XLEN-1:0] shift_num,
    input [5:0] shift_count,
    output [`XLEN-1:0] shift_out
);
  wire _op_shift = shift_sra | shift_srl | shift_sll;
  /* 选择是否忽略高32位 */
  wire [`XLEN-1:0] _shift_num = (isshift32) ? {32'b0, shift_num[31:0]} : shift_num;
  wire [`XLEN-1:0] _shift_num_inv;
  /* 位颠倒 */
  Vectorinvert #(
      .DATA_LEN(`XLEN)
  ) u_Vectorinvert1 (
      .in (_shift_num),
      .out(_shift_num_inv)
  );
  //将右移转换为左移
  wire [`XLEN-1:0] _shifter_in1 = {`XLEN{_op_shift}} & ((shift_sra | shift_srl) ? _shift_num_inv : _shift_num);//操作数
  wire [5:0] _shifter_in2 = (isshift32) ? {1'b0, shift_count[4:0]} : shift_count;  //TODO:BUG(很坑)移位次数
  /* 实际移位操作,用一个移位器实现左移和右移 */
  wire [`XLEN-1:0] _shifter_res = _shifter_in1 << _shifter_in2;

  wire [`XLEN-1:0] _sll_res = _shifter_res;  //逻辑左移结果
  /*逻辑右移结果,srl_in->位颠倒->移位器(左移)->位颠倒->srl_out*/
  wire [`XLEN-1:0] _srl_res;
  Vectorinvert #(
      .DATA_LEN(`XLEN)
  ) u_Vectorinvert2 (
      .in (_sll_res),
      .out(_srl_res)
  );
  /* 选择掩码,64位移位和32位移位掩码不同 */
  wire [5:0] _eff_mask_shift_count = (isshift32) ? (_shifter_in2 + 6'd32) : _shifter_in2;
  /* 选择符号位,32位移位需要忽略输入num的高32位 */
  wire _lastbit = (isshift32) ? _shift_num[31] : _shift_num[`XLEN-1];

  /* 算数右移结果，采用掩码算法实现算数右移 */
  wire [`XLEN-1:0] _eff_mask = (~(`XLEN'b0)) >> _eff_mask_shift_count;
  wire [`XLEN-1:0] _sra_res = (_srl_res & _eff_mask) | ({`XLEN{_lastbit}} & (~_eff_mask));

  /* 多路选择器选择最终结果 */
  wire [`XLEN-1:0] _shift_out = ({`XLEN{shift_srl}}&_srl_res) |
                                ({`XLEN{shift_sra}}&_sra_res) |
                                ({`XLEN{shift_sll}}&_sll_res);
  assign shift_out = _shift_out;
endmodule
