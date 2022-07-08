`include "./../sysconfig.v"


module dcode (
    input wire [`INST_LEN-1:0] inst_data
);

  wire [`INST_LEN-1:0] _inst = inst_data;
  // 指令分解
  wire [4:0] _rd = _inst[11:7];
  wire [2:0] _func3 = _inst[14:12];
  wire [4:0] _rs1 = _inst[19:15];
  wire [4:0] _rs2 = _inst[24:20];
  wire [6:0] _func7 = _inst[31:25];

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
  wire _func7_0000101 = (_func7 == 7'b0000101);
  wire _func7_0001001 = (_func7 == 7'b0001001);
  wire _func7_0001101 = (_func7 == 7'b0001101);
  wire _func7_0010101 = (_func7 == 7'b0010101);
  wire _func7_0100001 = (_func7 == 7'b0100001);
  wire _func7_0010001 = (_func7 == 7'b0010001);
  wire _func7_0101101 = (_func7 == 7'b0101101);
  wire _func7_1111111 = (_func7 == 7'b1111111);
  wire _func7_0000100 = (_func7 == 7'b0000100);
  wire _func7_0001000 = (_func7 == 7'b0001000);
  wire _func7_0001100 = (_func7 == 7'b0001100);
  wire _func7_0101100 = (_func7 == 7'b0101100);
  wire _func7_0010000 = (_func7 == 7'b0010000);
  wire _func7_0010100 = (_func7 == 7'b0010100);
  wire _func7_1100000 = (_func7 == 7'b1100000);
  wire _func7_1110000 = (_func7 == 7'b1110000);
  wire _func7_1010000 = (_func7 == 7'b1010000);
  wire _func7_1101000 = (_func7 == 7'b1101000);
  wire _func7_1111000 = (_func7 == 7'b1111000);
  wire _func7_1010001 = (_func7 == 7'b1010001);
  wire _func7_1110001 = (_func7 == 7'b1110001);
  wire _func7_1100001 = (_func7 == 7'b1100001);
  wire _func7_1101001 = (_func7 == 7'b1101001);

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

  /* _type_op_32 */
  wire _inst_add = _type_op_32 & _func3_000 & _func7_0000000;
  wire _inst_sub = _type_op_32 & _func3_000 & _func7_0100000;
  wire _inst_sll = _type_op_32 & _func3_001 & _func7_0000000;
  wire _inst_slt = _type_op_32 & _func3_010 & _func7_0000000;
  wire _inst_sltu = _type_op_32 & _func3_011 & _func7_0000000;
  wire _inst_xor = _type_op_32 & _func3_100 & _func7_0000000;
  wire _inst_srl = _type_op_32 & _func3_101 & _func7_0000000;
  wire _inst_sra = _type_op_32 & _func3_101 & _func7_0100000;
  wire _inst_or = _type_op_32 & _func3_110 & _func7_0000000;
  wire _inst_and = _type_op_32 & _func3_111 & _func7_0000000;
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
  // wire _inst_mret = _type_system & _func3_000 & (_inst[31:20] == 12'b0011_0000_0010);
  // wire _inst_dret = _type_system & _func3_000 & (_inst[31:20] == 12'b0111_1011_0010);
  // wire _inst_wfi = _type_system & _func3_000 & (_inst[31:20] == 12'b0001_0000_0101);

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






endmodule
