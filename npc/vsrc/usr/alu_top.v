`include "./../sysconfig.v"
module alu_top (
    /* ALU 端口 */
    input [`XLEN-1:0] alu_a_i,
    input [`XLEN-1:0] alu_b_i,
    input [`ALUOP_LEN-1:0] alu_op_i,
    output [`XLEN-1:0] alu_out_o,
    //比较指令输出
    output compare_out_o

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

  wire _aluop_beq = (alu_op_i == `ALUOP_BEQ);
  wire _aluop_bne = (alu_op_i == `ALUOP_BNE);
  wire _aluop_blt = (alu_op_i == `ALUOP_BLT);
  wire _aluop_bge = (alu_op_i == `ALUOP_BGE);
  wire _aluop_bltu = (alu_op_i == `ALUOP_BLTU);
  wire _aluop_bgeu = (alu_op_i == `ALUOP_BGEU);

  //乘法
  wire _aluop_mul = (alu_op_i == `ALUOP_MUL);
  wire _aluop_mulh = (alu_op_i == `ALUOP_MULH);
  wire _aluop_mulhsu = (alu_op_i == `ALUOP_MULHSU);
  wire _aluop_mulhu = (alu_op_i == `ALUOP_MULHU);
  wire _aluop_mulw = (alu_op_i == `ALUOP_MULW);

  //除法
  wire _aluop_div = (alu_op_i == `ALUOP_DIV);
  wire _aluop_divu = (alu_op_i == `ALUOP_DIVU);
  wire _aluop_rem = (alu_op_i == `ALUOP_REM);
  wire _aluop_remu = (alu_op_i == `ALUOP_REMU);
  wire _aluop_divw = (alu_op_i == `ALUOP_DIVW);
  wire _aluop_divuw = (alu_op_i == `ALUOP_DIVUW);
  wire _aluop_remw = (alu_op_i == `ALUOP_REMW);
  wire _aluop_remuw = (alu_op_i == `ALUOP_REMUW);


  /*********************************加法-减法-比较器实现*************************************/

  wire _isCMP =   _aluop_slt | _aluop_bgeu |
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
  wire _isSF = _add_out[`XLEN-1];  //leesum(bug),最高位为扩展符号位,次高位为原始符号位
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

  /* 并行多路选择器,选择比较输出 */
  wire _compare_out = ((_aluop_slt|_aluop_blt)&_isSLT)|
                      ((_aluop_sltu|_aluop_bltu)&_isSLTU)|
                      ((_aluop_beq)&_isBEQ)|
                      ((_aluop_bne)&_isBNE)|
                      ((_aluop_bge)&_isBGE)|
                      ((_aluop_bgeu)&_isBGEU);

  /************************************* 移位器实现 *********************************************/

  wire _shift_sra = _aluop_sra | _aluop_sraw;  //算数右移
  wire _shift_srl = _aluop_srl | _aluop_srlw;  //逻辑右移
  wire _shift_sll = _aluop_sll | _aluop_sllw;  //逻辑左移

  //Shifts the lower 32 bits of x[rs1] left by x[rs2] bit positions. The vacated bits are filled withzeros, and the sign-extended 32-bit result is written to x[rd]. 
  wire _isshift32 = _aluop_sllw | _aluop_sraw | _aluop_srlw;  //是否忽略高32位
  wire [`XLEN-1:0] _shift_num = alu_a_i;  //进行移位的操作数
  wire [5:0] _shift_count = alu_b_i[5:0];  //移位次数
  wire [`XLEN-1:0] _shift_out;  //移位结果

  alu_shift u_alu_shift (
      .shift_sra_i(_shift_sra),
      .shift_srl_i(_shift_srl),
      .shift_sll_i(_shift_sll),
      .shift32_valid_i(_isshift32),
      .shift_num_i(_shift_num),
      .shift_count_i(_shift_count),
      .shift_out_o(_shift_out)
  );

  /***************************************逻辑运算*******************************************/
  wire [`XLEN-1:0] _and_res = alu_a_i & alu_b_i;
  wire [`XLEN-1:0] _or_res = alu_a_i | alu_b_i;
  wire [`XLEN-1:0] _xor_res = alu_a_i ^ alu_b_i;

  /***************************************乘法运算*******************************************/

  wire _is_mul_sr1_signed = _aluop_mul | _aluop_mulh | _aluop_mulhsu | _aluop_mulw;
  wire _is_mul_sr2_signed = _aluop_mul | _aluop_mulh | _aluop_mulw;
  wire [`XLEN*2-1:0] _mul_result;

  alu_mul_top u_alu_mul_top (
      .rs1_signed_valid_i(_is_mul_sr1_signed),
      .rs2_signed_valid_i(_is_mul_sr2_signed),
      .rs1_data_i        (alu_a_i),
      .rs2_data_i        (alu_b_i),
      .mul_out_o         (_mul_result)
  );



  /* 不同乘法指令的结果 */
  wire [`XLEN-1:0] _inst_mul_result = _mul_result[`XLEN-1:0];
  wire [`XLEN-1:0] _inst_mulh_mulhsu_mulhu_result = _mul_result[`XLEN*2-1:`XLEN];
  // w 指令的符号扩展统一在 execute 中执行.
  wire [`XLEN-1:0] _inst_mulw_result = {32'b0, _mul_result[31:0]};

  /***************************************除法运算*******************************************/
  // 是否是有符号除法
  wire _is_div_signed = _aluop_div | _aluop_divw | _aluop_rem | _aluop_remw;

  // 是否是 32 位除法
  wire _is_div32 = _aluop_divw | _aluop_divuw | _aluop_remw | _aluop_remuw;

  /* 暂存结果 */
  wire [`XLEN-1:0] _div_result, _rem_result;

  alu_div_top u_alu_div_top (
      // input clk,  //为流水线准备
      // input rst,
      .signed_valid_i(_is_div_signed),
      .div32_valid_i (_is_div32),
      .sr1_data_i    (alu_a_i),
      .sr2_data_i    (alu_b_i),
      .div_out_o     (_div_result),
      .rem_out_o     (_rem_result)
  );

  /* 不同除法指令的结果 */
  wire [`XLEN-1:0] _inst_div_divu_divw_divuw_ret = _div_result;
  wire [`XLEN-1:0] _inst_rem_remu_remw_remuw_ret = _rem_result;

  /****************************选择最终ALU结果***********************************************/

  wire [`XLEN-1:0] _alu_out = ({`XLEN{_aluop_add|_aluop_sub}}&_add_out[`XLEN-1:0])|
                                ({`XLEN{_aluop_and}}&_and_res)|
                                ({`XLEN{_aluop_or}}&_or_res)|
                                ({`XLEN{_aluop_xor}}&_xor_res)|
                                ({`XLEN{_shift_sra|_shift_srl|_shift_sll}}&_shift_out)|
                                ({`XLEN{_aluop_mul}}&_inst_mul_result) |
                                ({`XLEN{_aluop_mulh|_aluop_mulhsu|_aluop_mulhu}}&_inst_mulh_mulhsu_mulhu_result) |
                                ({`XLEN{_aluop_mulw}}&_inst_mulw_result)|
                                ({`XLEN{_aluop_div|_aluop_divu|_aluop_divw|_aluop_divuw}}&_inst_div_divu_divw_divuw_ret)|
                                ({`XLEN{_aluop_rem|_aluop_remu|_aluop_remw|_aluop_remuw}}&_inst_rem_remu_remw_remuw_ret);

  /* 选择最后输出 */
  assign alu_out_o = (_isCMP) ? {63'b0, _compare_out} : _alu_out;
  assign compare_out_o = _compare_out;

endmodule

