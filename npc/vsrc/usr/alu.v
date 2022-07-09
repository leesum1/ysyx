`include "./../sysconfig.v"
module alu (
    /* ALU 端口 */
    input [`XLEN-1:0] alu_a_i,
    input [`XLEN-1:0] alu_b_i,
    output [`XLEN-1:0] alu_out,
    input [3:0] alu_op_i,
    /* 标志位 */
    output OF,
    output ZF,
    output SLT,
    output CF,
    output SF,
    /* 测试用 */
    output [`XLEN-1:0] sra_out,
    output [`XLEN-1:0] srl_out,
    output [`XLEN-1:0] sll_out

);

  wire _isSUBop = (alu_op_i == `ALUOP_SUB);
  wire [`XLEN:0] _cin = {{64{1'b0}}, _isSUBop};
  //采用双符号位
  wire [`XLEN:0] _alu_a = {{1{alu_a_i[`XLEN-1]}}, alu_a_i};
  wire [`XLEN:0] _alu_b = {{1{alu_b_i[`XLEN-1]}}, alu_b_i} ^ {65{_isSUBop}};
  wire [`XLEN:0] _alu_out, _add_out;
  //加减法
  assign _add_out = _alu_a + _alu_b + _cin;

  /* 标志位生成  具体看https://blog.csdn.net/mariodf/article/details/125334271*/
  wire _isZero = (_add_out == 65'd0);
  wire _isOF = _alu_out[`XLEN] ^ _alu_out[`XLEN-1];
  wire _isSF = _alu_out[`XLEN-1];
  wire _isCF = _isSUBop ^ _alu_out[`XLEN];
  wire _isSLT = _isOF ^ _add_out[`XLEN-1];


  /* 输出指定 */
  assign _alu_out = _add_out;
  assign ZF = _isZero;
  assign OF = _isOF;
  assign SLT = _isSLT;
  assign CF = _isCF;
  assign SF = _isSF;
  assign alu_out = _alu_out[`XLEN-1:0];

  /************************************* 移位器实现 *********************************************/
  wire                                          [`XLEN-1:0] shifter_in1;  //要移位的数
  wire                                          [`XLEN-1:0] shifter_in1_inv;  //要移位的数
  wire                                          [    6-1:0] shifter_in2;  //移动次数
  wire                                          [`XLEN-1:0] shifter_res;  //最终结果

  wire _op_sra = (alu_op_i == `ALUOP_SRA);
  wire _op_sll = (alu_op_i == `ALUOP_SLL);
  wire _op_srl = (alu_op_i == `ALUOP_SRL);
  wire _op_shift = _op_sra | _op_sll | _op_srl;

  /* 位颠倒 */
  Vectorinvert #(
      .DATA_LEN(`XLEN)
  ) u_Vectorinvert1 (
      .in (alu_a_i),
      .out(shifter_in1_inv)
  );
  /* 如果是右移则颠倒，转换为左移 */
  assign shifter_in1 = {`XLEN{_op_shift}} & ((_op_sra | _op_srl) ? shifter_in1_inv : alu_a_i);//操作数
  assign shifter_in2 = {6{_op_shift}} & alu_b_i[5:0];  //移位次数

  /* 实际移位操作 */
  assign shifter_res = (shifter_in1 << shifter_in2);
  wire [`XLEN-1:0] sll_res = shifter_res;  //逻辑左移
  wire [`XLEN-1:0] srl_res;  //逻辑右移
  Vectorinvert #(
      .DATA_LEN(`XLEN)
  ) u_Vectorinvert2 (
      .in (shifter_res),
      .out(srl_res)
  );
  /* 算数右移结果，采用掩码算法实现算数右移 */
  wire [`XLEN-1:0] eff_mask = (~(`XLEN'b0)) >> shifter_in2;
  wire [`XLEN-1:0] sra_res = (srl_res & eff_mask) | ({`XLEN{alu_a_i[`XLEN-1]}} & (~eff_mask));

  assign sra_out = sra_res;
  assign srl_out = srl_res;
  assign sll_out = sll_res;


  /*****************************比较器实现************************************/


endmodule

