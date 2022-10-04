`include "sysconfig.v"


module ysyx_041514_dcode (
    /* from if/id */
    input [`ysyx_041514_XLEN_BUS] inst_addr_i,
    input [`ysyx_041514_INST_LEN-1:0] inst_data_i,
    input [`ysyx_041514_TRAP_BUS] trap_bus_i,
    /* from gpr regs */
    input [`ysyx_041514_XLEN_BUS] rs1_data_i,
    input [`ysyx_041514_XLEN_BUS] rs2_data_i,
    /* from csr regs */
    input [`ysyx_041514_XLEN_BUS] csr_data_i,
    /* from id/ex stage */
    input [`ysyx_041514_EXCOP_LEN-1:0] id_ex_exc_op_i, // 上一条指令的类型，用于判断上一条指令是否是访存指令
    /* from exc bypass */
    input [`ysyx_041514_XLEN_BUS] ex_rd_data_i,
    input [`ysyx_041514_REG_ADDRWIDTH-1:0] ex_rd_addr_i,
    input [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] ex_csr_writeaddr_i,
    input [`ysyx_041514_XLEN_BUS] ex_csr_writedata_i,
    /* from mem bypass */
    input [`ysyx_041514_XLEN_BUS] mem_rd_data_i,
    input [`ysyx_041514_REG_ADDRWIDTH-1:0] mem_rd_addr_i,


    /*通用寄存器译码结果：to id/ex */
    output [    `ysyx_041514_REG_ADDRWIDTH-1:0] rs1_idx_o,
    output [    `ysyx_041514_REG_ADDRWIDTH-1:0] rs2_idx_o,
    output [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_o,
    output [             `ysyx_041514_XLEN_BUS] rs1_data_o,
    output [             `ysyx_041514_XLEN_BUS] rs2_data_o,
    output [          `ysyx_041514_IMM_LEN-1:0] imm_data_o,
    /* CSR 译码结果：to id/ex*/
    output [          `ysyx_041514_IMM_LEN-1:0] csr_imm_o,
    output                          csr_imm_valid_o,
    output [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_idx_o,
    output [             `ysyx_041514_XLEN_BUS] csr_readdata_o,

    output [`ysyx_041514_ALUOP_LEN-1:0] alu_op_o,  // alu 操作码
    output [`ysyx_041514_MEMOP_LEN-1:0] mem_op_o,  // mem 操作码
    output [`ysyx_041514_EXCOP_LEN-1:0] exc_op_o,  // exc 操作码
    output [ `ysyx_041514_PCOP_LEN-1:0] pc_op_o,   // pc 操作码
    output [`ysyx_041514_CSROP_LEN-1:0] csr_op_o,  // csr 操作码


    output [`ysyx_041514_XLEN_BUS] inst_addr_o,
    output [`ysyx_041514_INST_LEN-1:0] inst_data_o,
    // 请求暂停流水线
    output _load_use_valid_o,
    /* TARP 总线 */
    output wire [`ysyx_041514_TRAP_BUS] trap_bus_o

);
  assign inst_addr_o = inst_addr_i;
  assign inst_data_o = inst_data_i;





  wire [`ysyx_041514_INST_LEN-1:0] _inst = inst_data_i;
  /* 指令分解 */
  wire [4:0] _rd = _inst[11:7];
  wire [2:0] _func3 = _inst[14:12];
  wire [4:0] _rs1 = _inst[19:15];
  wire [4:0] _rs2 = _inst[24:20];
  wire [6:0] _func7 = _inst[31:25];
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr = _inst[31:20];  // CSR 地址

  // 不同指令类型的立即数
  wire [`ysyx_041514_IMM_LEN-1:0] _immI = {{21 + 32{_inst[31]}}, _inst[30:20]};
  wire [`ysyx_041514_IMM_LEN-1:0] _immS = {{21 + 32{_inst[31]}}, _inst[30:25], _inst[11:8], _inst[7]};
  wire [`ysyx_041514_IMM_LEN-1:0] _immB = {{20 + 32{_inst[31]}}, _inst[7], _inst[30:25], _inst[11:8], 1'b0};
  wire [`ysyx_041514_IMM_LEN-1:0] _immU = {{1 + 32{_inst[31]}}, _inst[30:20], _inst[19:12], 12'b0};
  wire [`ysyx_041514_IMM_LEN-1:0] _immJ = {
    {12 + 32{_inst[31]}}, _inst[19:12], _inst[20], _inst[30:25], _inst[24:21], 1'b0
  };
  wire [`ysyx_041514_IMM_LEN-1:0] _immCSR = {59'b0, _inst[19:15]};



  /* 分解_opcode */
  wire [6:0] _opcode = _inst[6:0];
  /* 1:0 */
  wire _opcode_1_0_00 = (_opcode[1:0] == 2'b00);
  wire _opcode_1_0_01 = (_opcode[1:0] == 2'b01);
  wire _opcode_1_0_10 = (_opcode[1:0] == 2'b10);
  wire _opcode_1_0_11 = (_opcode[1:0] == 2'b11);
  /* 4:2 */
  wire _opcode_4_2_000 = (_opcode[4:2] == 3'b000);
  wire _opcode_4_2_001 = (_opcode[4:2] == 3'b001);
  wire _opcode_4_2_010 = (_opcode[4:2] == 3'b010);
  wire _opcode_4_2_011 = (_opcode[4:2] == 3'b011);
  wire _opcode_4_2_100 = (_opcode[4:2] == 3'b100);
  wire _opcode_4_2_101 = (_opcode[4:2] == 3'b101);
  wire _opcode_4_2_110 = (_opcode[4:2] == 3'b110);
  wire _opcode_4_2_111 = (_opcode[4:2] == 3'b111);
  /* 6:5 */
  wire _opcode_6_5_00 = (_opcode[6:5] == 2'b00);
  wire _opcode_6_5_01 = (_opcode[6:5] == 2'b01);
  wire _opcode_6_5_10 = (_opcode[6:5] == 2'b10);
  wire _opcode_6_5_11 = (_opcode[6:5] == 2'b11);
  /* 分解 func3 */
  wire _func3_000 = (_func3 == 3'b000);
  wire _func3_001 = (_func3 == 3'b001);
  wire _func3_010 = (_func3 == 3'b010);
  wire _func3_011 = (_func3 == 3'b011);
  wire _func3_100 = (_func3 == 3'b100);
  wire _func3_101 = (_func3 == 3'b101);
  wire _func3_110 = (_func3 == 3'b110);
  wire _func3_111 = (_func3 == 3'b111);

  /* 分解func7 */
  wire _func7_0000000 = (_func7 == 7'b0000000);
  wire _func7_0100000 = (_func7 == 7'b0100000);
  wire _func7_0000001 = (_func7 == 7'b0000001);
  // wire _func7_0000101 = (_func7 == 7'b0000101);
  // wire _func7_0001001 = (_func7 == 7'b0001001);
  // wire _func7_0001101 = (_func7 == 7'b0001101);
  // wire _func7_0010101 = (_func7 == 7'b0010101);
  // wire _func7_0100001 = (_func7 == 7'b0100001);
  // wire _func7_0010001 = (_func7 == 7'b0010001);
  // wire _func7_0101101 = (_func7 == 7'b0101101);
  // wire _func7_1111111 = (_func7 == 7'b1111111);
  // wire _func7_0000100 = (_func7 == 7'b0000100);
  // wire _func7_0001000 = (_func7 == 7'b0001000);
  // wire _func7_0001100 = (_func7 == 7'b0001100);
  // wire _func7_0101100 = (_func7 == 7'b0101100);
  // wire _func7_0010000 = (_func7 == 7'b0010000);
  // wire _func7_0010100 = (_func7 == 7'b0010100);
  // wire _func7_1100000 = (_func7 == 7'b1100000);
  // wire _func7_1110000 = (_func7 == 7'b1110000);
  // wire _func7_1010000 = (_func7 == 7'b1010000);
  // wire _func7_1101000 = (_func7 == 7'b1101000);
  // wire _func7_1111000 = (_func7 == 7'b1111000);
  // wire _func7_1010001 = (_func7 == 7'b1010001);
  // wire _func7_1110001 = (_func7 == 7'b1110001);
  // wire _func7_1100001 = (_func7 == 7'b1100001);
  // wire _func7_1101001 = (_func7 == 7'b1101001);

  /* 指令类型,具体参考手册 */
  /* 000 */
  wire _type_load = _opcode_6_5_00 & _opcode_4_2_000 & _opcode_1_0_11;
  wire _type_store = _opcode_6_5_01 & _opcode_4_2_000 & _opcode_1_0_11;
  wire _type_madd = _opcode_6_5_10 & _opcode_4_2_000 & _opcode_1_0_11;
  wire _type_branch = _opcode_6_5_11 & _opcode_4_2_000 & _opcode_1_0_11;
  /* 001 */
  wire _type_load_fp = _opcode_6_5_00 & _opcode_4_2_001 & _opcode_1_0_11;
  wire _type_store_fp = _opcode_6_5_01 & _opcode_4_2_001 & _opcode_1_0_11;
  wire _type_msub = _opcode_6_5_10 & _opcode_4_2_001 & _opcode_1_0_11;
  wire _type_jalr = _opcode_6_5_11 & _opcode_4_2_001 & _opcode_1_0_11;
  /* 010 */
  wire _type_custom0 = _opcode_6_5_00 & _opcode_4_2_010 & _opcode_1_0_11;
  wire _type_custom1 = _opcode_6_5_01 & _opcode_4_2_010 & _opcode_1_0_11;
  wire _type_nmsub = _opcode_6_5_10 & _opcode_4_2_010 & _opcode_1_0_11;
  wire _type_resved0 = _opcode_6_5_11 & _opcode_4_2_010 & _opcode_1_0_11;
  /* 011 */
  wire _type_miscmem = _opcode_6_5_00 & _opcode_4_2_011 & _opcode_1_0_11;
  wire _type_amo = _opcode_6_5_01 & _opcode_4_2_011 & _opcode_1_0_11;
  wire _type_nmadd = _opcode_6_5_10 & _opcode_4_2_011 & _opcode_1_0_11;
  wire _type_jal = _opcode_6_5_11 & _opcode_4_2_011 & _opcode_1_0_11;
  /* 100 */
  wire _type_op_imm = _opcode_6_5_00 & _opcode_4_2_100 & _opcode_1_0_11;
  wire _type_op = _opcode_6_5_01 & _opcode_4_2_100 & _opcode_1_0_11;
  wire _type_op_fp = _opcode_6_5_10 & _opcode_4_2_100 & _opcode_1_0_11;
  wire _type_system = _opcode_6_5_11 & _opcode_4_2_100 & _opcode_1_0_11;
  /* 101 */
  wire _type_auipc = _opcode_6_5_00 & _opcode_4_2_101 & _opcode_1_0_11;
  wire _type_lui = _opcode_6_5_01 & _opcode_4_2_101 & _opcode_1_0_11;
  wire _type_resved1 = _opcode_6_5_10 & _opcode_4_2_101 & _opcode_1_0_11;
  wire _type_resved2 = _opcode_6_5_11 & _opcode_4_2_101 & _opcode_1_0_11;
  /* 110 */
  wire _type_op_imm_32 = _opcode_6_5_00 & _opcode_4_2_110 & _opcode_1_0_11;
  wire _type_op_32 = _opcode_6_5_01 & _opcode_4_2_110 & _opcode_1_0_11;
  wire _type_custom2 = _opcode_6_5_10 & _opcode_4_2_110 & _opcode_1_0_11;
  wire _type_custom3 = _opcode_6_5_11 & _opcode_4_2_110 & _opcode_1_0_11;

  /******************************RV64I Base Instruction************************************/
  /* _type_lui */
  wire _inst_lui = _type_lui;
  /* _type_auipc */
  wire _inst_auipc = _type_auipc;
  /* _type_jal */
  wire _inst_jal = _type_jal;
  /* _type_jalr */
  wire _inst_jalr = _type_jalr & _func3_000;
  /* _type_branch */
  wire _inst_beq = _type_branch & _func3_000;
  wire _inst_bne = _type_branch & _func3_001;
  wire _inst_blt = _type_branch & _func3_100;
  wire _inst_bge = _type_branch & _func3_101;
  wire _inst_bltu = _type_branch & _func3_110;
  wire _inst_bgeu = _type_branch & _func3_111;

  /* _type_load */
  wire _inst_lb = _type_load & _func3_000;
  wire _inst_lh = _type_load & _func3_001;
  wire _inst_lw = _type_load & _func3_010;
  wire _inst_lbu = _type_load & _func3_100;
  wire _inst_lhu = _type_load & _func3_101;

  // rv64 only
  wire _inst_lwu = _type_load & _func3_110;
  wire _inst_ld = _type_load & _func3_011;

  /* _type_store */
  wire _inst_sb = _type_store & _func3_000;
  wire _inst_sh = _type_store & _func3_001;
  wire _inst_sw = _type_store & _func3_010;

  // rv64 only
  wire _inst_sd = _type_store & _func3_011;


  /*_type_op_imm*/
  wire _inst_addi = _type_op_imm & _func3_000;
  wire _inst_slti = _type_op_imm & _func3_010;
  wire _inst_sltiu = _type_op_imm & _func3_011;
  wire _inst_xori = _type_op_imm & _func3_100;
  wire _inst_ori = _type_op_imm & _func3_110;
  wire _inst_andi = _type_op_imm & _func3_111;

  // rv64 only 
  wire _inst_slli = _type_op_imm & _func3_001 & (_func7[6:1] == 6'b000000);
  wire _inst_srli = _type_op_imm & _func3_101 & (_func7[6:1] == 6'b000000);
  wire _inst_srai = _type_op_imm & _func3_101 & (_func7[6:1] == 6'b010000);

  // // rv32 
  // wire _inst_slli = _type_op_imm & _func3_001 & _func7_0000000;
  // wire _inst_srli = _type_op_imm & _func3_101 & _func7_0000000;
  // wire _inst_srai = _type_op_imm & _func3_101 & _func7_0100000;

  /* _type_op */
  wire _inst_add = _type_op & _func3_000 & _func7_0000000;
  wire _inst_sub = _type_op & _func3_000 & _func7_0100000;
  wire _inst_sll = _type_op & _func3_001 & _func7_0000000;
  wire _inst_slt = _type_op & _func3_010 & _func7_0000000;
  wire _inst_sltu = _type_op & _func3_011 & _func7_0000000;
  wire _inst_xor = _type_op & _func3_100 & _func7_0000000;
  wire _inst_srl = _type_op & _func3_101 & _func7_0000000;
  wire _inst_sra = _type_op & _func3_101 & _func7_0100000;
  wire _inst_or = _type_op & _func3_110 & _func7_0000000;
  wire _inst_and = _type_op & _func3_111 & _func7_0000000;
  /* _type_op_32 */
  // rv64 only  
  wire _inst_addw = _type_op_32 & _func3_000 & _func7_0000000;
  wire _inst_subw = _type_op_32 & _func3_000 & _func7_0100000;
  wire _inst_sllw = _type_op_32 & _func3_001 & _func7_0000000;
  wire _inst_srlw = _type_op_32 & _func3_101 & _func7_0000000;
  wire _inst_sraw = _type_op_32 & _func3_101 & _func7_0100000;

  /* _type_op_imm_32 */
  // rv64 only
  wire _inst_addiw = _type_op_imm_32 & _func3_000;
  wire _inst_slliw = _type_op_imm_32 & _func3_001 & _func7_0000000;
  wire _inst_srliw = _type_op_imm_32 & _func3_101 & _func7_0000000;
  wire _inst_sraiw = _type_op_imm_32 & _func3_101 & _func7_0100000;


  /* _type_system */

  wire _inst_ecall = _type_system & _func3_000 & (_inst[31:20] == 12'b0000_0000_0000);
  wire _inst_ebreak = _type_system & _func3_000 & (_inst[31:20] == 12'b0000_0000_0001);


  // CSR
  wire _inst_csrrw = _type_system & _func3_001;
  wire _inst_csrrs = _type_system & _func3_010;
  wire _inst_csrrc = _type_system & _func3_011;
  wire _inst_csrrwi = _type_system & _func3_101;
  wire _inst_csrrsi = _type_system & _func3_110;
  wire _inst_csrrci = _type_system & _func3_111;

  wire _inst_mret = _type_system & _func3_000 & (_inst[31:20] == 12'b0011_0000_0010);
  wire _inst_dret = _type_system & _func3_000 & (_inst[31:20] == 12'b0111_1011_0010);
  wire _inst_wfi = _type_system & _func3_000 & (_inst[31:20] == 12'b0001_0000_0101);

  /*_type_miscmem*/
  wire _inst_fence = _type_miscmem & _func3_000;
  wire _inst_fence_i = _type_miscmem & _func3_001;


  /******************************RV64M Instruction************************************/
  /* _type_op */
  wire _inst_mul = _type_op & _func3_000 & _func7_0000001;
  wire _inst_mulh = _type_op & _func3_001 & _func7_0000001;
  wire _inst_mulhsu = _type_op & _func3_010 & _func7_0000001;
  wire _inst_mulhu = _type_op & _func3_011 & _func7_0000001;
  wire _inst_div = _type_op & _func3_100 & _func7_0000001;
  wire _inst_divu = _type_op & _func3_101 & _func7_0000001;
  wire _inst_rem = _type_op & _func3_110 & _func7_0000001;
  wire _inst_remu = _type_op & _func3_111 & _func7_0000001;

  /* _type_op_32 */
  // rv64 only
  wire _inst_mulw = _type_op_32 & _func3_000 & _func7_0000001;
  wire _inst_divw = _type_op_32 & _func3_100 & _func7_0000001;
  wire _inst_divuw = _type_op_32 & _func3_101 & _func7_0000001;
  wire _inst_remw = _type_op_32 & _func3_110 & _func7_0000001;
  wire _inst_remuw = _type_op_32 & _func3_111 & _func7_0000001;

  /* 将指令分为 R I S B U J 六类，便于获得操作数 TODO:还有一些没有添加*/
  wire _R_type = _type_op | _type_op_32;
  wire _I_type = _type_load | _type_op_imm | _type_op_imm_32 | _type_jalr | _type_system;
  wire _S_type = _type_store;
  wire _B_type = _type_branch;
  wire _U_type = _type_auipc | _type_lui;
  wire _J_type = _type_jal;
  // 无效指令_type_miscmem
  wire _NONE_type = ~(_R_type | _I_type | _S_type | _U_type | _J_type | _B_type|_type_miscmem);

  /*获取操作数  */  //TODO:一些特殊指令没有归类ecall,ebreak
  wire _isNeed_imm = (_I_type | _S_type | _B_type | _U_type | _J_type);
  wire _csr_imm_valid = (_inst_csrrci | _inst_csrrsi | _inst_csrrwi);

  // I 型指令中, CSR 立即数占了 rs1 的位置
  wire _isNeed_rs1 = (_R_type | _I_type | _S_type | _B_type) & (~_csr_imm_valid);
  wire _isNeed_rs2 = (_R_type | _S_type | _B_type);
  wire _isNeed_rd = (_R_type | _I_type | _U_type | _J_type);
  wire _isNeed_csr = (_inst_csrrc|_inst_csrrci|_inst_csrrs|_inst_csrrsi|_inst_csrrw|_inst_csrrwi);

  wire [4:0] _rs1_idx = (_isNeed_rs1) ? _rs1 : 5'b0;
  wire [4:0] _rs2_idx = (_isNeed_rs2) ? _rs2 : 5'b0;
  wire [4:0] _rd_idx = (_isNeed_rd) ? _rd : 5'b0;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_idx = (_isNeed_csr) ? _csr : `ysyx_041514_CSR_REG_ADDRWIDTH'b0;


  /* assign 实现多路选择器：根据指令类型选立即数 */
  wire [`ysyx_041514_IMM_LEN-1:0] _imm_data = ({`ysyx_041514_IMM_LEN{_I_type}}&_immI) |
                                  ({`ysyx_041514_IMM_LEN{_S_type}}&_immS) |
                                  ({`ysyx_041514_IMM_LEN{_B_type}}&_immB) |
                                  ({`ysyx_041514_IMM_LEN{_U_type}}&_immU) |
                                  ({`ysyx_041514_IMM_LEN{_J_type}}&_immJ);

  /* 输出指定 */
  assign rs1_idx_o = _rs1_idx;
  assign rs2_idx_o = _rs2_idx;
  assign rd_idx_o = _rd_idx;
  assign csr_idx_o = _csr_idx;
  assign imm_data_o = _imm_data;

  // CSR 中的立即数 特殊处理
  assign csr_imm_valid_o = _csr_imm_valid;
  assign csr_imm_o = _immCSR;

  /******************************************冲突处理***************************************************/
  wire _pre_inst_is_load = (id_ex_exc_op_i == `ysyx_041514_EXCOP_LOAD);

  // 0 号寄存器特殊处理，不然出错
  wire _rs1_idx_not_zero = (_rs1_idx != `ysyx_041514_REG_ADDRWIDTH'b0);
  wire _rs2_idx_not_zero = (_rs2_idx != `ysyx_041514_REG_ADDRWIDTH'b0);

  // exc stage bypass
  wire _rs1_exc_bypass_valid = (_rs1_idx == ex_rd_addr_i) && (_rs1_idx_not_zero);
  wire _rs2_exc_bypass_valid = (_rs2_idx == ex_rd_addr_i) && (_rs2_idx_not_zero);
  // mem stage bypass
  wire _rs1_mem_bypass_valid = (_rs1_idx == mem_rd_addr_i) && (_rs1_idx_not_zero);
  wire _rs2_mem_bypass_valid = (_rs2_idx == mem_rd_addr_i) && (_rs2_idx_not_zero);
  // wb stage bypass was enabled in gpr


  // 优先级选择权 ex > mem > wb > gpr (wb 和 gpr 的优先级在通用寄存器堆中实现)
  wire [`ysyx_041514_XLEN_BUS] _rs1_data = (_rs1_exc_bypass_valid)?ex_rd_data_i:
                                (_rs1_mem_bypass_valid)?mem_rd_data_i:
                                rs1_data_i;
  // 优先级选择权 ex > mem > wb > gpr
  wire [`ysyx_041514_XLEN_BUS] _rs2_data = (_rs2_exc_bypass_valid)?ex_rd_data_i:
                                (_rs2_mem_bypass_valid)?mem_rd_data_i:
                                rs2_data_i;
  // load-use hazard: 前一条指令为 load 类型，且下一条 rs1、rs2 为 load 指令的 rd，
  // https://courses.cs.vt.edu/cs2506/Spring2013/Notes/L12.PipelineStalls.pdf
  wire _load_use_data_hazard_valid = _pre_inst_is_load & (_rs1_exc_bypass_valid | _rs2_exc_bypass_valid);


  // 输出指定
  assign rs1_data_o = _rs1_data;
  assign rs2_data_o = _rs2_data;
  assign _load_use_valid_o = _load_use_data_hazard_valid;


  /***************CSR 寄存器冲突处理*****************/
  // TODO 添加 csr 数据旁路
  assign csr_readdata_o = csr_data_i;

  /******************************************×××××××***************************************************/

  /* CSR_OP */
  wire _csr_write = _inst_csrrw | _inst_csrrwi;
  wire _csr_set = _inst_csrrs | _inst_csrrsi;
  wire _csr_clear = _inst_csrrc | _inst_csrrci;
  // CSRRSI/CSRRCI must not write 0 to CSRs (uimm[4:0]=='0)
  // CSRRS/CSRRC must not write from x0 to CSRs (rs1=='0)
  wire _csr_read = (_csr_set | _csr_clear) & (_rs1 == '0);
  // read 优先级高
  wire [`ysyx_041514_CSROP_LEN-1:0]_csr_op = (_csr_read)?`ysyx_041514_CSROP_READ:(
                 ({`ysyx_041514_CSROP_LEN{_csr_write}}&`ysyx_041514_CSROP_WRITE)|
                 ({`ysyx_041514_CSROP_LEN{_csr_set}}&`ysyx_041514_CSROP_SET)|
                 ({`ysyx_041514_CSROP_LEN{_csr_clear}}&`ysyx_041514_CSROP_CLEAR));
  assign csr_op_o = _csr_op;

  /* ALU_OP */
  //加减和逻辑
  wire _alu_add = _inst_add |_inst_addw |_inst_addi |_inst_addiw| _type_load 
                  | _type_store | _inst_jal |_inst_jalr |_inst_auipc | _inst_lui|_isNeed_csr;
  wire _alu_sub = _inst_sub | _inst_subw;
  wire _alu_xor = _inst_xor | _inst_xori;
  wire _alu_and = _inst_and | _inst_andi;
  wire _alu_or = _inst_or | _inst_ori;
  //移位
  wire _alu_sll = _inst_sll | _inst_slli;
  wire _alu_srl = _inst_srl | _inst_srli;
  wire _alu_sra = _inst_sra | _inst_srai;
  wire _alu_sllw = _inst_slliw | _inst_sllw;
  wire _alu_srlw = _inst_srliw | _inst_srlw;
  wire _alu_sraw = _inst_sraiw | _inst_sraw;
  //比较
  wire _alu_slt = _inst_slt | _inst_slti;
  wire _alu_sltu = _inst_sltu | _inst_sltiu;
  wire _alu_beq = _inst_beq;
  wire _alu_bne = _inst_bne;
  wire _alu_blt = _inst_blt;
  wire _alu_bge = _inst_bge;
  wire _alu_bltu = _inst_bltu;
  wire _alu_bgeu = _inst_bgeu;
  //定点乘法
  wire _alu_mul = _inst_mul;
  wire _alu_mulh = _inst_mulh;
  wire _alu_mulhsu = _inst_mulhsu;
  wire _alu_mulhu = _inst_mulhu;
  wire _alu_mulw = _inst_mulw;
  //定点除法
  wire _alu_div = _inst_div;
  wire _alu_divu = _inst_divu;
  wire _alu_rem = _inst_rem;
  wire _alu_remu = _inst_remu;
  wire _alu_divw = _inst_divw;
  wire _alu_divuw = _inst_divuw;
  wire _alu_remw = _inst_remw;
  wire _alu_remuw = _inst_remuw;



  // // ALU 计算结果是否需要符号扩展,放在 execute 下实现
  // wire _alu_sext = _type_op_imm_32 | _type_op_32;
  //多路选择器
  wire [`ysyx_041514_ALUOP_LEN-1:0] _alu_op = ({`ysyx_041514_ALUOP_LEN{_alu_add}} & `ysyx_041514_ALUOP_ADD)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_sub}} & `ysyx_041514_ALUOP_SUB)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_xor}} & `ysyx_041514_ALUOP_XOR)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_or}} & `ysyx_041514_ALUOP_OR)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_and}} & `ysyx_041514_ALUOP_AND)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_sll}} & `ysyx_041514_ALUOP_SLL)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_srl}} & `ysyx_041514_ALUOP_SRL)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_sra}} & `ysyx_041514_ALUOP_SRA)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_sllw}} & `ysyx_041514_ALUOP_SLLW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_srlw}} & `ysyx_041514_ALUOP_SRLW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_sraw}} & `ysyx_041514_ALUOP_SRAW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_slt}} & `ysyx_041514_ALUOP_SLT)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_sltu}} & `ysyx_041514_ALUOP_SLTU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_beq}} & `ysyx_041514_ALUOP_BEQ)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_bne}} & `ysyx_041514_ALUOP_BNE)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_blt}} & `ysyx_041514_ALUOP_BLT)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_bge}} & `ysyx_041514_ALUOP_BGE)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_bltu}} & `ysyx_041514_ALUOP_BLTU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_bgeu}} & `ysyx_041514_ALUOP_BGEU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_mul}} & `ysyx_041514_ALUOP_MUL)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_mulh}} & `ysyx_041514_ALUOP_MULH)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_mulhsu}} & `ysyx_041514_ALUOP_MULHSU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_mulhu}} & `ysyx_041514_ALUOP_MULHU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_mulw}} & `ysyx_041514_ALUOP_MULW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_div}} & `ysyx_041514_ALUOP_DIV)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_divu}} & `ysyx_041514_ALUOP_DIVU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_rem}} & `ysyx_041514_ALUOP_REM)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_remu}} & `ysyx_041514_ALUOP_REMU)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_divw}} & `ysyx_041514_ALUOP_DIVW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_divuw}} & `ysyx_041514_ALUOP_DIVUW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_remw}} & `ysyx_041514_ALUOP_REMW)|
                                  ({`ysyx_041514_ALUOP_LEN{_alu_remuw}} & `ysyx_041514_ALUOP_REMUW);

  assign alu_op_o = _alu_op;

  /* EXC_OP */
  wire [`ysyx_041514_EXCOP_LEN-1:0] _exc_op = ({`ysyx_041514_EXCOP_LEN{_type_auipc}}&`ysyx_041514_EXCOP_AUIPC) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_lui}}&`ysyx_041514_EXCOP_LUI) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_jal}}&`ysyx_041514_EXCOP_JAL) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_jalr}}&`ysyx_041514_EXCOP_JALR) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_load}}&`ysyx_041514_EXCOP_LOAD) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_store}}&`ysyx_041514_EXCOP_STORE) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_branch}}&`ysyx_041514_EXCOP_BRANCH) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_op_imm}}&`ysyx_041514_EXCOP_OPIMM) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_op_imm_32}}&`ysyx_041514_EXCOP_OPIMM32) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_op}}&`ysyx_041514_EXCOP_OP) |
                                  ({`ysyx_041514_EXCOP_LEN{_type_op_32}}&`ysyx_041514_EXCOP_OP32) |
                                  ({`ysyx_041514_EXCOP_LEN{_isNeed_csr}}&`ysyx_041514_EXCOP_CSR) |
                                  ({`ysyx_041514_EXCOP_LEN{_inst_ebreak}}&`ysyx_041514_EXCOP_EBREAK) | //TODO:暂时对 ebreak 特殊处理

  ({`ysyx_041514_EXCOP_LEN{_NONE_type}} & `ysyx_041514_EXCOP_NONE);

  assign exc_op_o = _exc_op;


  /* MEM_OP */
  wire [`ysyx_041514_MEMOP_LEN-1:0] _mem_op =  ({`ysyx_041514_MEMOP_LEN{_inst_lb}}&`ysyx_041514_MEMOP_LB)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_lbu}}&`ysyx_041514_MEMOP_LBU)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_lh}}&`ysyx_041514_MEMOP_LH)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_lw}}&`ysyx_041514_MEMOP_LW)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_lhu}}&`ysyx_041514_MEMOP_LHU)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_sb}}&`ysyx_041514_MEMOP_SB)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_sh}}&`ysyx_041514_MEMOP_SH)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_sw}}&`ysyx_041514_MEMOP_SW)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_lwu}}&`ysyx_041514_MEMOP_LWU)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_ld}}&`ysyx_041514_MEMOP_LD)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_sd}}&`ysyx_041514_MEMOP_SD)|
                                   ({`ysyx_041514_MEMOP_LEN{_inst_fence_i}}&`ysyx_041514_MEMOP_FENCEI);
  assign mem_op_o = _mem_op;


  // 已废弃
  assign pc_op_o  = `ysyx_041514_PCOP_LEN'b0;




  /* trap_bus TODO:add more*/

  wire _Illegal_instruction = _NONE_type;


  reg [`ysyx_041514_TRAP_BUS] _decode_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `ysyx_041514_TRAP_LEN; i = i + 1) begin
      if (i == `ysyx_041514_TRAP_MRET) begin
        _decode_trap_bus[i] = _inst_mret;
      end else if (i == `ysyx_041514_TRAP_EBREAK) begin
        _decode_trap_bus[i] = _inst_ebreak;
      end else if (i == `ysyx_041514_TRAP_ECALL_M) begin // TODO 权限设置
        _decode_trap_bus[i] = _inst_ecall;
      end else if (i == `ysyx_041514_TRAP_ILLEGAL_INST) begin
        _decode_trap_bus[i] = _Illegal_instruction;
      end else begin
        _decode_trap_bus[i] = trap_bus_i[i];
      end
    end
  end
  assign trap_bus_o = _decode_trap_bus;

endmodule
