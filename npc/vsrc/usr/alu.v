`include "./../sysconfig.v"
module alu (
    /* ALU 端口 */
    input [`XLEN-1:0] alu_a_i,
    input [`XLEN-1:0] alu_b_i,
    input [`ALUOP_LEN-1:0] alu_op_i,
    output [`XLEN-1:0] alu_out,
    //比较指令输出
    output compare_out

    /* 测试用 */
    // output [`XLEN-1:0] sra_out,
    // output [`XLEN-1:0] srl_out,
    // output [`XLEN-1:0] sll_out
    // /* 标志位 */
    // output OF,
    // output ZF,
    // output SLT,
    // output CF,
    // output SF,

);

  //加减和逻辑
  wire _aluop_add = (alu_op_i == `ALUOP_ADD);
  wire _aluop_sub = (alu_op_i == `ALUOP_SUB);
  wire _aluop_xor = (alu_op_i == `ALUOP_XOR);
  wire _aluop_or = (alu_op_i == `ALUOP_OR);
  wire _aluop_and = (alu_op_i == `ALUOP_AND);
  //移位
  wire _aluop_sll = (alu_op_i == `ALUOP_SLL);
  wire _aluop_srl = (alu_op_i == `ALUOP_SRL);
  wire _aluop_sra = (alu_op_i == `ALUOP_SRA);
  wire _aluop_sllw = (alu_op_i == `ALUOP_SLLW);
  wire _aluop_srlw = (alu_op_i == `ALUOP_SRLW);
  wire _aluop_sraw = (alu_op_i == `ALUOP_SRAW);
  //比较
  wire _aluop_slt = (alu_op_i == `ALUOP_SLT);
  wire _aluop_sltu = (alu_op_i == `ALUOP_SLTU);
  wire _aluop_slti = (alu_op_i == `ALUOP_SLTI);
  wire _aluop_sltiu = (alu_op_i == `ALUOP_SLTIU);
  wire _aluop_beq = (alu_op_i == `ALUOP_BEQ);
  wire _aluop_bne = (alu_op_i == `ALUOP_BNE);
  wire _aluop_blt = (alu_op_i == `ALUOP_BLT);
  wire _aluop_bge = (alu_op_i == `ALUOP_BGE);
  wire _aluop_bltu = (alu_op_i == `ALUOP_BLTU);
  wire _aluop_bgeu = (alu_op_i == `ALUOP_BGEU);

  /*********************************加法-减法-比较器实现*************************************/

  wire _isCMP =   _aluop_slt | _aluop_bgeu |
                  _aluop_slti | _aluop_sltiu|
                  _aluop_sltu |_aluop_beq |
                  _aluop_bne |_aluop_blt  |
                  _aluop_bge|_aluop_bltu  ;
  /* 如果是减法、比较操作则进行减法 */
  wire _isSUBop = _aluop_sub | _isCMP;
  /* 进位 */
  wire [`XLEN:0] _cin = {{64{1'b0}}, _isSUBop};  //减法的加1
  /* 扩展为双符号位 */
  wire [`XLEN:0] _alu_a = {{1{alu_a_i[`XLEN-1]}}, alu_a_i};
  wire [`XLEN:0] _alu_b = {{1{alu_b_i[`XLEN-1]}}, alu_b_i} ^ {65{_isSUBop}};  //异或实现取反
  wire [`XLEN:0] _add_out;
  /* 加法器 */
  assign _add_out = _alu_a + _alu_b + _cin;

  /* 标志位生成  具体看https://blog.csdn.net/mariodf/article/details/125334271*/
  //通过真值表得到,最高位进位,用于计算 CF 标志位
  wire _tb_A = _alu_a[`XLEN];
  wire _tb_B = _alu_b[`XLEN];
  wire _tb_C = _add_out[`XLEN];
  wire _tb_NOTA = ~_tb_A;
  wire _tb_NOTB = ~_tb_B;
  wire _tb_NOTC = ~_tb_C;
  // 最高位进位,(测试)
  wire _isC64in = (_tb_A|_tb_B|_tb_C) &
                  (_tb_A|_tb_NOTB|_tb_NOTC)&
                  (_tb_NOTA|_tb_B|_tb_NOTC)&
                  (_tb_NOTA|_tb_NOTB|_tb_C);

  wire _isZero = (_add_out == 65'd0);
  wire _isOF = _add_out[`XLEN] ^ _add_out[`XLEN-1];
  wire _isSF = _add_out[`XLEN-2];
  wire _isCF = _isSUBop ^ _isC64in;

  /* 比较信息 具体看 obsidian 笔记 */
  //   wire _isSLT = _isOF ^ _add_out[`XLEN-1];
  wire _isSLT = _isSF ^ _isOF;  // a<b (signed)
  wire _isSLTU = _isCF;  //a<b (unsigned)

  wire _isBLT = _isSLT;  // a<b(signed)
  wire _isBLTU = _isSLTU;  // a<b(unsigned)
  wire _isBGE = ~_isSLT;  // a>=b(signed)
  wire _isBGEU = ~_isSLTU;  //a>=b(unsigned)

  wire _isBEQ = _isZero;  //a==b
  wire _isBNE = ~_isZero;  //a!=b

  /* 并行多路选择器 */
  wire _compare_out = ((_aluop_slt|_aluop_blt)&_isSLT)|
                      ((_aluop_sltu|_aluop_bltu)&_isSLTU)|
                      ((_aluop_beq)&_isBEQ)|
                      ((_aluop_bne)&_isBNE)|
                      ((_aluop_bge)&_isBGE)|
                      ((_aluop_bgeu)&_isBGEU);

  /************************************* 移位器实现 *********************************************/
  //   wire [`XLEN-1:0] _shifter_in1;  //要移位的数
  //   wire [`XLEN-1:0] _shifter_in1_inv;  //要移位的数
  //   wire [6-1:0] _shifter_in2;  //移动次数
  //   wire [`XLEN-1:0] _shifter_res;  //最终结果

  //   wire _op_shift = _aluop_sra | _aluop_sll | _aluop_srl;

  wire _shift_sra = _aluop_sra | _aluop_sraw;
  wire _shift_srl = _aluop_srl | _aluop_srlw;
  wire _shift_sll = _aluop_sll | _aluop_sllw;
  wire _isshift32 = _aluop_sllw | _aluop_sraw | _aluop_srlw;
  wire [`XLEN-1:0] _shift_num = alu_a_i;
  wire [5:0] _shift_count = alu_b_i[5:0];
  wire [`XLEN-1:0] _shift_out;
  alu_shift u_alu_shift (
      .shift_sra  (_shift_sra),
      .shift_srl  (_shift_srl),
      .shift_sll  (_shift_sll),
      .isshift32  (_isshift32),
      .shift_num  (_shift_num),
      .shift_count(_shift_count),
      .shift_out  (_shift_out)
  );
  //   /* 位颠倒 */
  //   Vectorinvert #(
  //       .DATA_LEN(`XLEN)
  //   ) u_Vectorinvert1 (
  //       .in (alu_a_i),
  //       .out(_shifter_in1_inv)
  //   );
  //   /* 如果是右移则颠倒，转换为左移 */
  //   assign _shifter_in1 = {`XLEN{_op_shift}} & ((_aluop_sra | _aluop_srl) ? _shifter_in1_inv : alu_a_i);//操作数
  //   assign _shifter_in2 = {6{_op_shift}} & alu_b_i[5:0];  //移位次数

  //   /* 实际移位操作 */
  //   assign _shifter_res = (_shifter_in1 << _shifter_in2);
  //   wire [`XLEN-1:0] _sll_res = _shifter_res;  //逻辑左移结果
  //   wire [`XLEN-1:0] _srl_res;  //逻辑右移结果
  //   /* 位颠倒 */
  //   Vectorinvert #(
  //       .DATA_LEN(`XLEN)
  //   ) u_Vectorinvert2 (
  //       .in (_shifter_res),
  //       .out(_srl_res)
  //   );
  //   /* 算数右移结果，采用掩码算法实现算数右移 */
  //   wire [`XLEN-1:0] _eff_mask = (~(`XLEN'b0)) >> _shifter_in2;
  //   wire [`XLEN-1:0] _sra_res = (_srl_res & _eff_mask) | ({`XLEN{alu_a_i[`XLEN-1]}} & (~_eff_mask));

  /***************************************逻辑运算*******************************************/
  wire [`XLEN-1:0] _and_res = alu_a_i & alu_b_i;
  wire [`XLEN-1:0] _or_res = alu_a_i | alu_b_i;
  wire [`XLEN-1:0] _xor_res = alu_a_i ^ alu_b_i;

  /****************************选择最终ALU结果***********************************************/

  wire [`XLEN-1:0]_alu_out = (_aluop_add|_aluop_sub)?_add_out[`XLEN-1:0]:
                    (_aluop_and)?_and_res:
                    (_aluop_or)?_or_res:
                    (_aluop_xor)?_xor_res:
                    (_shift_sra|_shift_srl|_shift_sll)?_shift_out:
                    `XLEN'b0;

  /* 选择最后输出 */
  assign alu_out = (_isCMP) ? {63'b0, _compare_out} : _alu_out;
  assign compare_out = _compare_out;

endmodule

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
  wire [`XLEN-1:0] _shift_num32 = {32'b0, shift_num[31:0]};
  wire [`XLEN-1:0] _shift_num = (isshift32) ? _shift_num32 : shift_num;
  wire [`XLEN-1:0] _shift_num_inv;
  /* 位颠倒 */
  Vectorinvert #(
      .DATA_LEN(`XLEN)
  ) u_Vectorinvert1 (
      .in (_shift_num),
      .out(_shift_num_inv)
  );
  wire [`XLEN-1:0] _shifter_in1 = {`XLEN{_op_shift}} & ((shift_sra | shift_srl) ? _shift_num_inv : _shift_num);//操作数
  wire [5:0] _shifter_in2 = shift_count;
  wire [`XLEN-1:0] _shifter_res = _shifter_in1 << _shifter_in2;

  wire [`XLEN-1:0] _sll_res = _shifter_res;  //逻辑左移结果
  wire [`XLEN-1:0] _srl_res;  //逻辑右移结果
  Vectorinvert #(
      .DATA_LEN(`XLEN)
  ) u_Vectorinvert2 (
      .in (_sll_res),
      .out(_srl_res)
  );

  wire [5:0] _eff_mask_shift_count = (isshift32) ? (_shifter_in2 + 6'd32) : _shifter_in2;
  wire _lastbit = (isshift32) ? _shift_num[31] : _shift_num[`XLEN-1];
  /* 算数右移结果，采用掩码算法实现算数右移 */
  wire [`XLEN-1:0] _eff_mask = (~(`XLEN'b0)) >> _eff_mask_shift_count;
  wire [`XLEN-1:0] _sra_res = (_srl_res & _eff_mask) | ({`XLEN{_lastbit}} & (~_eff_mask));

  wire [`XLEN-1:0] _shift_out = ({`XLEN{shift_srl}}&_srl_res) |
                                ({`XLEN{shift_sra}}&_sra_res) |
                                ({`XLEN{shift_sll}}&_sll_res);
endmodule
