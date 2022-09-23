`include "sysconfig.v"
module alu_mul_wallace (
    // input                clk,
    // input                rst,
    input                rs1_signed_valid_i,
    input                rs2_signed_valid_i,
    input  [  `XLEN_BUS] rs1_data_i,
    input  [  `XLEN_BUS] rs2_data_i,
    output [`XLEN*2-1:0] mul_out_o
);


  // 部分积生成
  wire [127:0] p_product[33-1:0];
  alu_mul_booth_r4 u_alu_mul_booth_r4 (
      .rs1_signed_valid_i(rs1_signed_valid_i),
      .rs2_signed_valid_i(rs2_signed_valid_i),
      .rs1_data_i        (rs1_data_i),
      .rs2_data_i        (rs2_data_i),
      .pp0_o             (p_product[0]),
      .pp1_o             (p_product[1]),
      .pp2_o             (p_product[2]),
      .pp3_o             (p_product[3]),
      .pp4_o             (p_product[4]),
      .pp5_o             (p_product[5]),
      .pp6_o             (p_product[6]),
      .pp7_o             (p_product[7]),
      .pp8_o             (p_product[8]),
      .pp9_o             (p_product[9]),
      .pp10_o            (p_product[10]),
      .pp11_o            (p_product[11]),
      .pp12_o            (p_product[12]),
      .pp13_o            (p_product[13]),
      .pp14_o            (p_product[14]),
      .pp15_o            (p_product[15]),
      .pp16_o            (p_product[16]),
      .pp17_o            (p_product[17]),
      .pp18_o            (p_product[18]),
      .pp19_o            (p_product[19]),
      .pp20_o            (p_product[20]),
      .pp21_o            (p_product[21]),
      .pp22_o            (p_product[22]),
      .pp23_o            (p_product[23]),
      .pp24_o            (p_product[24]),
      .pp25_o            (p_product[25]),
      .pp26_o            (p_product[26]),
      .pp27_o            (p_product[27]),
      .pp28_o            (p_product[28]),
      .pp29_o            (p_product[29]),
      .pp30_o            (p_product[30]),
      .pp31_o            (p_product[31]),
      .pp32_o            (p_product[32])
  );





  wire [129-1:0] step1_A0_cout0  /* verilator split_var */;
  wire [129-1:0] step1_A0_cout1  /* verilator split_var */;
  assign step1_A0_cout0[0] = 1'b0;
  assign step1_A0_cout1[0] = 1'b0;
  wire [128-1:0] step1_A0_sum, step1_A0_carry;
  genvar step1_A0;
  generate
    for (step1_A0 = 0; step1_A0 < 128; step1_A0 = step1_A0 + 1) begin
      alu_mul_compressor52 u_alu_mul_compressor52 (
          .x0   (p_product[0][step1_A0]),
          .x1   (p_product[1][step1_A0]),
          .x2   (p_product[2][step1_A0]),
          .x3   (p_product[3][step1_A0]),
          .x4   (p_product[4][step1_A0]),
          .cin0 (step1_A0_cout0[step1_A0]),
          .cin1 (step1_A0_cout1[step1_A0]),
          .cout0(step1_A0_cout0[step1_A0+1]),
          .cout1(step1_A0_cout1[step1_A0+1]),
          .sum  (step1_A0_sum[step1_A0]),
          .carry(step1_A0_carry[step1_A0])
      );
    end
  endgenerate


  wire [129-1:0] step1_A1_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A1_cout[0] = 1'b0;
  wire [128-1:0] step1_A1_sum, step1_A1_carry;
  genvar step1_A1;
  generate
    for (step1_A1 = 0; step1_A1 < 128; step1_A1 = step1_A1 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step1_A1 (
          .x0   (p_product[5][step1_A1]),
          .x1   (p_product[6][step1_A1]),
          .x2   (p_product[7][step1_A1]),
          .x3   (p_product[8][step1_A1]),
          .ci   (step1_A1_cout[step1_A1]),
          .sum  (step1_A1_sum[step1_A1]),
          .co   (step1_A1_cout[step1_A1+1]),
          .carry(step1_A1_carry[step1_A1])
      );
    end
  endgenerate


  wire [129-1:0] step1_A2_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A2_cout[0] = 1'b0;
  wire [128-1:0] step1_A2_sum, step1_A2_carry;
  genvar step1_A2;
  generate
    for (step1_A2 = 0; step1_A2 < 128; step1_A2 = step1_A2 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step1_A2 (
          .x0   (p_product[9][step1_A2]),
          .x1   (p_product[10][step1_A2]),
          .x2   (p_product[11][step1_A2]),
          .x3   (p_product[12][step1_A2]),
          .ci   (step1_A2_cout[step1_A2]),
          .sum  (step1_A2_sum[step1_A2]),
          .co   (step1_A2_cout[step1_A2+1]),
          .carry(step1_A2_carry[step1_A2])
      );
    end
  endgenerate


  wire [129-1:0] step1_A3_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A3_cout[0] = 1'b0;
  wire [128-1:0] step1_A3_sum, step1_A3_carry;
  genvar step1_A3;
  generate
    for (step1_A3 = 0; step1_A3 < 128; step1_A3 = step1_A3 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step1_A3 (
          .x0   (p_product[13][step1_A3]),
          .x1   (p_product[14][step1_A3]),
          .x2   (p_product[15][step1_A3]),
          .x3   (p_product[16][step1_A3]),
          .ci   (step1_A3_cout[step1_A3]),
          .sum  (step1_A3_sum[step1_A3]),
          .co   (step1_A3_cout[step1_A3+1]),
          .carry(step1_A3_carry[step1_A3])
      );
    end
  endgenerate




  wire [129-1:0] step1_A4_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A4_cout[0] = 1'b0;
  wire [128-1:0] step1_A4_sum, step1_A4_carry;
  genvar step1_A4;
  generate
    for (step1_A4 = 0; step1_A4 < 128; step1_A4 = step1_A4 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step1_A4 (
          .x0   (p_product[17][step1_A4]),
          .x1   (p_product[18][step1_A4]),
          .x2   (p_product[19][step1_A4]),
          .x3   (p_product[20][step1_A4]),
          .ci   (step1_A4_cout[step1_A4]),
          .sum  (step1_A4_sum[step1_A4]),
          .co   (step1_A4_cout[step1_A4+1]),
          .carry(step1_A4_carry[step1_A4])
      );
    end
  endgenerate



  wire [129-1:0] step1_A5_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A5_cout[0] = 1'b0;
  wire [128-1:0] step1_A5_sum, step1_A5_carry;
  genvar step1_A5;
  generate
    for (step1_A5 = 0; step1_A5 < 128; step1_A5 = step1_A5 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_tep1_A5 (
          .x0   (p_product[21][step1_A5]),
          .x1   (p_product[22][step1_A5]),
          .x2   (p_product[23][step1_A5]),
          .x3   (p_product[24][step1_A5]),
          .ci   (step1_A5_cout[step1_A5]),
          .sum  (step1_A5_sum[step1_A5]),
          .co   (step1_A5_cout[step1_A5+1]),
          .carry(step1_A5_carry[step1_A5])
      );
    end
  endgenerate


  wire [129-1:0] step1_A6_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A6_cout[0] = 1'b0;
  wire [128-1:0] step1_A6_sum, step1_A6_carry;
  genvar step1_A6;
  generate
    for (step1_A6 = 0; step1_A6 < 128; step1_A6 = step1_A6 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step1_A6 (
          .x0   (p_product[25][step1_A6]),
          .x1   (p_product[26][step1_A6]),
          .x2   (p_product[27][step1_A6]),
          .x3   (p_product[28][step1_A6]),
          .ci   (step1_A6_cout[step1_A6]),
          .sum  (step1_A6_sum[step1_A6]),
          .co   (step1_A6_cout[step1_A6+1]),
          .carry(step1_A6_carry[step1_A6])
      );
    end
  endgenerate


  wire [129-1:0] step1_A7_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A7_cout[0] = 1'b0;
  wire [128-1:0] step1_A7_sum, step1_A7_carry;
  genvar step1_A7;
  generate
    for (step1_A7 = 0; step1_A7 < 128; step1_A7 = step1_A7 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step1_A7 (
          .x0   (p_product[29][step1_A7]),
          .x1   (p_product[30][step1_A7]),
          .x2   (p_product[31][step1_A7]),
          .x3   (p_product[32][step1_A7]),
          .ci   (step1_A7_cout[step1_A7]),
          .sum  (step1_A7_sum[step1_A7]),
          .co   (step1_A7_cout[step1_A7+1]),
          .carry(step1_A7_carry[step1_A7])
      );
    end
  endgenerate


  wire [127:0] step2_pp[16-1:0];
  assign step2_pp[0]  = step1_A0_sum;
  assign step2_pp[1]  = step1_A1_sum;
  assign step2_pp[2]  = step1_A2_sum;
  assign step2_pp[3]  = step1_A3_sum;
  assign step2_pp[4]  = step1_A4_sum;
  assign step2_pp[5]  = step1_A5_sum;
  assign step2_pp[6]  = step1_A6_sum;
  assign step2_pp[7]  = step1_A7_sum;
  assign step2_pp[8]  = {step1_A0_carry[126:0], 1'b0};
  assign step2_pp[9]  = {step1_A1_carry[126:0], 1'b0};
  assign step2_pp[10] = {step1_A2_carry[126:0], 1'b0};
  assign step2_pp[11] = {step1_A3_carry[126:0], 1'b0};
  assign step2_pp[12] = {step1_A4_carry[126:0], 1'b0};
  assign step2_pp[13] = {step1_A5_carry[126:0], 1'b0};
  assign step2_pp[14] = {step1_A6_carry[126:0], 1'b0};
  assign step2_pp[15] = {step1_A7_carry[126:0], 1'b0};



  wire [129-1:0] step2_A0_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step2_A0_cout[0] = 1'b0;
  wire [128-1:0] step2_A0_sum, step2_A0_carry;
  genvar step2_A0;
  generate
    for (step2_A0 = 0; step2_A0 < 128; step2_A0 = step2_A0 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step2_A0 (
          .x0   (step2_pp[0][step2_A0]),
          .x1   (step2_pp[1][step2_A0]),
          .x2   (step2_pp[2][step2_A0]),
          .x3   (step2_pp[3][step2_A0]),
          .ci   (step2_A0_cout[step2_A0]),
          .sum  (step2_A0_sum[step2_A0]),
          .co   (step2_A0_cout[step2_A0+1]),
          .carry(step2_A0_carry[step2_A0])
      );
    end
  endgenerate


  wire [129-1:0] step2_A1_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step2_A1_cout[0] = 1'b0;
  wire [128-1:0] step2_A1_sum, step2_A1_carry;
  genvar step2_A1;
  generate
    for (step2_A1 = 0; step2_A1 < 128; step2_A1 = step2_A1 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step2_A1 (
          .x0   (step2_pp[4][step2_A1]),
          .x1   (step2_pp[5][step2_A1]),
          .x2   (step2_pp[6][step2_A1]),
          .x3   (step2_pp[7][step2_A1]),
          .ci   (step2_A1_cout[step2_A1]),
          .sum  (step2_A1_sum[step2_A1]),
          .co   (step2_A1_cout[step2_A1+1]),
          .carry(step2_A1_carry[step2_A1])
      );
    end
  endgenerate


  wire [129-1:0] step2_A2_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step2_A2_cout[0] = 1'b0;
  wire [128-1:0] step2_A2_sum, step2_A2_carry;
  genvar step2_A2;
  generate
    for (step2_A2 = 0; step2_A2 < 128; step2_A2 = step2_A2 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step2_A2 (
          .x0   (step2_pp[8][step2_A2]),
          .x1   (step2_pp[9][step2_A2]),
          .x2   (step2_pp[10][step2_A2]),
          .x3   (step2_pp[11][step2_A2]),
          .ci   (step2_A2_cout[step2_A2]),
          .sum  (step2_A2_sum[step2_A2]),
          .co   (step2_A2_cout[step2_A2+1]),
          .carry(step2_A2_carry[step2_A2])
      );
    end
  endgenerate


  wire [129-1:0] step2_A3_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step2_A3_cout[0] = 1'b0;
  wire [128-1:0] step2_A3_sum, step2_A3_carry;
  genvar step2_A3;
  generate
    for (step2_A3 = 0; step2_A3 < 128; step2_A3 = step2_A3 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step2_A3 (
          .x0   (step2_pp[12][step2_A3]),
          .x1   (step2_pp[13][step2_A3]),
          .x2   (step2_pp[14][step2_A3]),
          .x3   (step2_pp[15][step2_A3]),
          .ci   (step2_A3_cout[step2_A3]),
          .sum  (step2_A3_sum[step2_A3]),
          .co   (step2_A3_cout[step2_A3+1]),
          .carry(step2_A3_carry[step2_A3])
      );
    end
  endgenerate


  wire [127:0] step3_pp[8-1:0];
  assign step3_pp[0] = step2_A0_sum;
  assign step3_pp[1] = step2_A1_sum;
  assign step3_pp[2] = step2_A2_sum;
  assign step3_pp[3] = step2_A3_sum;
  assign step3_pp[4] = {step2_A0_carry[126:0], 1'b0};
  assign step3_pp[5] = {step2_A1_carry[126:0], 1'b0};
  assign step3_pp[6] = {step2_A2_carry[126:0], 1'b0};
  assign step3_pp[7] = {step2_A3_carry[126:0], 1'b0};


  wire [129-1:0] step3_A0_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step3_A0_cout[0] = 1'b0;
  wire [128-1:0] step3_A0_sum, step3_A0_carry;
  genvar step3_A0;
  generate
    for (step3_A0 = 0; step3_A0 < 128; step3_A0 = step3_A0 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step3_A0 (
          .x0   (step3_pp[0][step3_A0]),
          .x1   (step3_pp[1][step3_A0]),
          .x2   (step3_pp[2][step3_A0]),
          .x3   (step3_pp[3][step3_A0]),
          .ci   (step3_A0_cout[step3_A0]),
          .sum  (step3_A0_sum[step3_A0]),
          .co   (step3_A0_cout[step3_A0+1]),
          .carry(step3_A0_carry[step3_A0])
      );
    end
  endgenerate


  wire [129-1:0] step3_A1_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step3_A1_cout[0] = 1'b0;
  wire [128-1:0] step3_A1_sum, step3_A1_carry;
  genvar step3_A1;
  generate
    for (step3_A1 = 0; step3_A1 < 128; step3_A1 = step3_A1 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step3_A1 (
          .x0   (step3_pp[4][step3_A1]),
          .x1   (step3_pp[5][step3_A1]),
          .x2   (step3_pp[6][step3_A1]),
          .x3   (step3_pp[7][step3_A1]),
          .ci   (step3_A1_cout[step3_A1]),
          .sum  (step3_A1_sum[step3_A1]),
          .co   (step3_A1_cout[step3_A1+1]),
          .carry(step3_A1_carry[step3_A1])
      );
    end
  endgenerate


  wire [127:0] step4_pp[4-1:0];
  assign step4_pp[0] = step3_A0_sum;
  assign step4_pp[1] = step3_A1_sum;
  assign step4_pp[2] = {step3_A0_carry[126:0], 1'b0};
  assign step4_pp[3] = {step3_A1_carry[126:0], 1'b0};


  wire [129-1:0] step4_A0_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step4_A0_cout[0] = 1'b0;
  wire [128-1:0] step4_A0_sum, step4_A0_carry;
  genvar step4_A0;
  generate
    for (step4_A0 = 0; step4_A0 < 128; step4_A0 = step4_A0 + 1) begin
      alu_mul_compressor42 u_alu_mul_compressor42_step4_A0 (
          .x0   (step4_pp[0][step4_A0]),
          .x1   (step4_pp[1][step4_A0]),
          .x2   (step4_pp[2][step4_A0]),
          .x3   (step4_pp[3][step4_A0]),
          .ci   (step4_A0_cout[step4_A0]),
          .sum  (step4_A0_sum[step4_A0]),
          .co   (step4_A0_cout[step4_A0+1]),
          .carry(step4_A0_carry[step4_A0])
      );
    end
  endgenerate

  assign mul_out_o = step4_A0_sum + {step4_A0_carry[126:0], 1'b0};

endmodule
