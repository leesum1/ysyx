`include "sysconfig.v"
module ysyx_041514_alu_mul_wallace (
    input                            clk,
    input                            rst,
    input                            rs1_signed_valid_i,
    input                            rs2_signed_valid_i,
    input  [  `ysyx_041514_XLEN_BUS] rs1_data_i,
    input  [  `ysyx_041514_XLEN_BUS] rs2_data_i,
    input                            mul_valid_i,
    output                           mul_ready_o,
    output [`ysyx_041514_XLEN*2-1:0] mul_out_o
);
  localparam STATE_LEN = 3;
  localparam MUL_RST = 3'd0;
  localparam MUL_IDLE = 3'd1;
  localparam MUL_BOOTH = 3'd2;
  localparam MUL_STEP1 = 3'd3;
  localparam MUL_STEP2 = 3'd4;
  localparam MUL_STEP3 = 3'd5;
  localparam MUL_STEP4 = 3'd6;
  localparam MUL_STEP5 = 3'd7;


  wire _mul_valid = mul_valid_i;
  reg [STATE_LEN-1:0] mul_state;
  reg mul_ready;
  reg [127:0] mul_data128;


  wire [127:0] mul_final128;
  assign mul_ready_o = mul_ready;

  assign mul_out_o   = mul_data128;


  /* 乘法状态机切换 */
  always @(posedge clk) begin
    if (rst) begin
      mul_state   <= MUL_RST;
      mul_ready   <= `ysyx_041514_FALSE;
      mul_data128 <= 'b0;
    end else begin
      case (mul_state)
        MUL_RST: begin
          mul_state <= MUL_IDLE;
        end
        // MUL_IDLE: begin
        //   if (_mul_valid) begin  // booth 结果有效
        //     mul_state <= MUL_BOOTH;
        //     mul_busy  <= `ysyx_041514_TRUE;
        //   end
        // end
        MUL_IDLE, MUL_BOOTH: begin
          mul_ready <= `ysyx_041514_FALSE;
          if (_mul_valid) begin
            mul_state <= MUL_STEP1;  // booth 结果有效，进入 step 1
          end else begin
            mul_state   <= MUL_IDLE;
            mul_data128 <= 'b0;
          end
        end
        MUL_STEP1: begin
          if (_mul_valid) begin
            mul_state <= MUL_STEP2;  // step1 33->16，进入 step2
          end else begin
            mul_state   <= MUL_IDLE;
            mul_data128 <= 'b0;
          end
        end
        MUL_STEP2: begin
          if (_mul_valid) begin
            mul_state <= MUL_STEP3;  // step2 16->8 ，进入step3
          end else begin
            mul_state   <= MUL_IDLE;
            mul_data128 <= 'b0;
          end
        end
        MUL_STEP3: begin
          if (_mul_valid) begin
            mul_state <= MUL_STEP4;  // step3 8->2，进入 step4
          end else begin
            mul_state   <= MUL_IDLE;
            mul_data128 <= 'b0;
          end
        end
        MUL_STEP4: begin
          if (_mul_valid) begin
            mul_state   <= MUL_IDLE;  // step4 2->1, 进入 idle
            mul_data128 <= mul_final128;  // 结果有效
            mul_ready   <= `ysyx_041514_TRUE;
          end else begin
            mul_state   <= MUL_IDLE;
            mul_data128 <= 'b0;
          end
        end
        MUL_STEP5: begin
          mul_state <= MUL_IDLE;
        end
      endcase
    end
  end







  wire [127:0] Partial_product[33-1:0];
  ysyx_041514_alu_mul_booth_r4 u_alu_mul_booth_r4 (
      .rs1_signed_valid_i(rs1_signed_valid_i),
      .rs2_signed_valid_i(rs2_signed_valid_i),
      .rs1_data_i        (rs1_data_i),
      .rs2_data_i        (rs2_data_i),
      .pp0_o             (Partial_product[0]),
      .pp1_o             (Partial_product[1]),
      .pp2_o             (Partial_product[2]),
      .pp3_o             (Partial_product[3]),
      .pp4_o             (Partial_product[4]),
      .pp5_o             (Partial_product[5]),
      .pp6_o             (Partial_product[6]),
      .pp7_o             (Partial_product[7]),
      .pp8_o             (Partial_product[8]),
      .pp9_o             (Partial_product[9]),
      .pp10_o            (Partial_product[10]),
      .pp11_o            (Partial_product[11]),
      .pp12_o            (Partial_product[12]),
      .pp13_o            (Partial_product[13]),
      .pp14_o            (Partial_product[14]),
      .pp15_o            (Partial_product[15]),
      .pp16_o            (Partial_product[16]),
      .pp17_o            (Partial_product[17]),
      .pp18_o            (Partial_product[18]),
      .pp19_o            (Partial_product[19]),
      .pp20_o            (Partial_product[20]),
      .pp21_o            (Partial_product[21]),
      .pp22_o            (Partial_product[22]),
      .pp23_o            (Partial_product[23]),
      .pp24_o            (Partial_product[24]),
      .pp25_o            (Partial_product[25]),
      .pp26_o            (Partial_product[26]),
      .pp27_o            (Partial_product[27]),
      .pp28_o            (Partial_product[28]),
      .pp29_o            (Partial_product[29]),
      .pp30_o            (Partial_product[30]),
      .pp31_o            (Partial_product[31]),
      .pp32_o            (Partial_product[32])
  );

  // 部分积生成 ( 共33 个)
  wire [127:0] step1_pp_d[33-1:0];
  assign step1_pp_d = Partial_product;
  reg [127:0] step1_pp_q[33-1:0];


  genvar step1_Dflap;
  generate
    for (step1_Dflap = 0; step1_Dflap < 33; step1_Dflap = step1_Dflap + 1) begin
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL(0)
      ) u_ysyx_041514_regTemplate (
          .clk (clk),
          .rst (rst),
          .din (step1_pp_d[step1_Dflap]),
          .dout(step1_pp_q[step1_Dflap]),
          .wen (1'b1)
      );
    end
  endgenerate

  wire [127:0] step1_pp[33-1:0];
  assign step1_pp = step1_pp_q;


  /*******             wallace tree            ********/
  /*******(33) 5-2 4-2 4-2 4-2 4-2 4-2 4-2 4-2 ********/
  /*******(16)        4-2 4-2 4-2 4-2          ********/
  /*******(8)            4-2 4-2               ********/
  /*******(4)              4-2                 ********/
  /*******(2)              2-1                 ********/



  /* step1 TODO:插入流水线 */
  wire [129-1:0] step1_A0_cout0  /* verilator split_var */;
  wire [129-1:0] step1_A0_cout1  /* verilator split_var */;
  assign step1_A0_cout0[0] = 1'b0;
  assign step1_A0_cout1[0] = 1'b0;
  wire [128-1:0] step1_A0_sum, step1_A0_carry;
  genvar step1_A0;
  generate
    for (step1_A0 = 0; step1_A0 < 128; step1_A0 = step1_A0 + 1) begin
      ysyx_041514_alu_mul_compressor52 u_alu_mul_compressor52 (
          .x0   (step1_pp[0][step1_A0]),
          .x1   (step1_pp[1][step1_A0]),
          .x2   (step1_pp[2][step1_A0]),
          .x3   (step1_pp[3][step1_A0]),
          .x4   (step1_pp[4][step1_A0]),
          .cin0 (step1_A0_cout0[step1_A0]),
          .cin1 (step1_A0_cout1[step1_A0]),
          .cout0(step1_A0_cout0[step1_A0+1]),
          .cout1(step1_A0_cout1[step1_A0+1]),
          .sum  (step1_A0_sum[step1_A0]),
          .carry(step1_A0_carry[step1_A0])
      );
    end
  endgenerate

  // wire [129-1:0] step1_A0_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  // assign step1_A0_cout[0] = 1'b0;
  // wire [128-1:0] step1_A0_sum, step1_A0_carry;
  // genvar step1_A0;
  // generate
  //   for (step1_A0 = 0; step1_A0 < 128; step1_A0 = step1_A0 + 1) begin
  //     alu_mul_compressor42 u_alu_mul_compressor42_step1_A0 (
  //         .x0   (step1_pp[1][step1_A0]),
  //         .x1   (step1_pp[2][step1_A0]),
  //         .x2   (step1_pp[3][step1_A0]),
  //         .x3   (step1_pp[4][step1_A0]),
  //         .ci   (step1_A0_cout[step1_A0]),
  //         .sum  (step1_A0_sum[step1_A0]),
  //         .co   (step1_A0_cout[step1_A0+1]),
  //         .carry(step1_A0_carry[step1_A0])
  //     );
  //   end
  // endgenerate


  wire [129-1:0] step1_A1_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step1_A1_cout[0] = 1'b0;
  wire [128-1:0] step1_A1_sum, step1_A1_carry;
  genvar step1_A1;
  generate
    for (step1_A1 = 0; step1_A1 < 128; step1_A1 = step1_A1 + 1) begin
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step1_A1 (
          .x0   (step1_pp[5][step1_A1]),
          .x1   (step1_pp[6][step1_A1]),
          .x2   (step1_pp[7][step1_A1]),
          .x3   (step1_pp[8][step1_A1]),
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step1_A2 (
          .x0   (step1_pp[9][step1_A2]),
          .x1   (step1_pp[10][step1_A2]),
          .x2   (step1_pp[11][step1_A2]),
          .x3   (step1_pp[12][step1_A2]),
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step1_A3 (
          .x0   (step1_pp[13][step1_A3]),
          .x1   (step1_pp[14][step1_A3]),
          .x2   (step1_pp[15][step1_A3]),
          .x3   (step1_pp[16][step1_A3]),
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step1_A4 (
          .x0   (step1_pp[17][step1_A4]),
          .x1   (step1_pp[18][step1_A4]),
          .x2   (step1_pp[19][step1_A4]),
          .x3   (step1_pp[20][step1_A4]),
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_tep1_A5 (
          .x0   (step1_pp[21][step1_A5]),
          .x1   (step1_pp[22][step1_A5]),
          .x2   (step1_pp[23][step1_A5]),
          .x3   (step1_pp[24][step1_A5]),
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step1_A6 (
          .x0   (step1_pp[25][step1_A6]),
          .x1   (step1_pp[26][step1_A6]),
          .x2   (step1_pp[27][step1_A6]),
          .x3   (step1_pp[28][step1_A6]),
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step1_A7 (
          .x0   (step1_pp[29][step1_A7]),
          .x1   (step1_pp[30][step1_A7]),
          .x2   (step1_pp[31][step1_A7]),
          .x3   (step1_pp[32][step1_A7]),
          .ci   (step1_A7_cout[step1_A7]),
          .sum  (step1_A7_sum[step1_A7]),
          .co   (step1_A7_cout[step1_A7+1]),
          .carry(step1_A7_carry[step1_A7])
      );
    end
  endgenerate



  /* step2 TODO:插入流水线 */
  wire [127:0] step2_pp_d[16-1:0];
  reg  [127:0] step2_pp_q[16-1:0];

  assign step2_pp_d[0]  = step1_A0_sum;
  assign step2_pp_d[1]  = step1_A1_sum;
  assign step2_pp_d[2]  = step1_A2_sum;
  assign step2_pp_d[3]  = step1_A3_sum;
  assign step2_pp_d[4]  = step1_A4_sum;
  assign step2_pp_d[5]  = step1_A5_sum;
  assign step2_pp_d[6]  = step1_A6_sum;
  assign step2_pp_d[7]  = step1_A7_sum;
  assign step2_pp_d[8]  = {step1_A0_carry[126:0], 1'b0};
  assign step2_pp_d[9]  = {step1_A1_carry[126:0], 1'b0};
  assign step2_pp_d[10] = {step1_A2_carry[126:0], 1'b0};
  assign step2_pp_d[11] = {step1_A3_carry[126:0], 1'b0};
  assign step2_pp_d[12] = {step1_A4_carry[126:0], 1'b0};
  assign step2_pp_d[13] = {step1_A5_carry[126:0], 1'b0};
  assign step2_pp_d[14] = {step1_A6_carry[126:0], 1'b0};
  assign step2_pp_d[15] = {step1_A7_carry[126:0], 1'b0};

  genvar step2_Dflap;
  generate
    for (step2_Dflap = 0; step2_Dflap < 16; step2_Dflap = step2_Dflap + 1) begin
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL(0)
      ) u_ysyx_041514_regTemplate_step2 (
          .clk (clk),
          .rst (rst),
          .din (step2_pp_d[step2_Dflap]),
          .dout(step2_pp_q[step2_Dflap]),
          .wen (1'b1)
      );
    end
  endgenerate

  wire [127:0] step2_pp[16-1:0];
  assign step2_pp = step2_pp_q;






  wire [129-1:0] step2_A0_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进位不使用
  assign step2_A0_cout[0] = 1'b0;
  wire [128-1:0] step2_A0_sum, step2_A0_carry;
  genvar step2_A0;
  generate
    for (step2_A0 = 0; step2_A0 < 128; step2_A0 = step2_A0 + 1) begin
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step2_A0 (
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step2_A1 (
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step2_A2 (
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step2_A3 (
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



  /* step3 TODO:插入流水线 */
  wire [127:0] step3_pp_d[8-1:0];
  reg  [127:0] step3_pp_q[8-1:0];
  assign step3_pp_d[0] = step2_A0_sum;
  assign step3_pp_d[1] = step2_A1_sum;
  assign step3_pp_d[2] = step2_A2_sum;
  assign step3_pp_d[3] = step2_A3_sum;
  assign step3_pp_d[4] = {step2_A0_carry[126:0], 1'b0};
  assign step3_pp_d[5] = {step2_A1_carry[126:0], 1'b0};
  assign step3_pp_d[6] = {step2_A2_carry[126:0], 1'b0};
  assign step3_pp_d[7] = {step2_A3_carry[126:0], 1'b0};

  genvar step3_Dflap;
  generate
    for (step3_Dflap = 0; step3_Dflap < 8; step3_Dflap = step3_Dflap + 1) begin
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL(0)
      ) u_ysyx_041514_regTemplate_step3 (
          .clk (clk),
          .rst (rst),
          .din (step3_pp_d[step3_Dflap]),
          .dout(step3_pp_q[step3_Dflap]),
          .wen (1'b1)
      );
    end
  endgenerate
  wire [127:0] step3_pp[8-1:0];
  assign step3_pp = step3_pp_q;






  wire [129-1:0] step3_A0_cout/* verilator split_var */;  // 最低位进位位 0 �����最高位进位不使用
  assign step3_A0_cout[0] = 1'b0;
  wire [128-1:0] step3_A0_sum, step3_A0_carry;
  genvar step3_A0;
  generate
    for (step3_A0 = 0; step3_A0 < 128; step3_A0 = step3_A0 + 1) begin
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step3_A0 (
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
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step3_A1 (
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


  /* step4 TODO:插入流水线 */
  wire [127:0] step4_pp_d[4-1:0];
  reg  [127:0] step4_pp_q[4-1:0];
  assign step4_pp_d[0] = step3_A0_sum;
  assign step4_pp_d[1] = step3_A1_sum;
  assign step4_pp_d[2] = {step3_A0_carry[126:0], 1'b0};
  assign step4_pp_d[3] = {step3_A1_carry[126:0], 1'b0};



  genvar step4_Dflap;
  generate
    for (step4_Dflap = 0; step4_Dflap < 4; step4_Dflap = step4_Dflap + 1) begin
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL(0)
      ) u_ysyx_041514_regTemplate_step4 (
          .clk (clk),
          .rst (rst),
          .din (step4_pp_d[step4_Dflap]),
          .dout(step4_pp_q[step4_Dflap]),
          .wen (1'b1)
      );
    end
  endgenerate
  wire [127:0] step4_pp[4-1:0];
  assign step4_pp = step4_pp_q;


  wire [129-1:0] step4_A0_cout/* verilator split_var */;  // 最低位进位位 0 ，最高位进����不���用
  assign step4_A0_cout[0] = 1'b0;
  wire [128-1:0] step4_A0_sum, step4_A0_carry;
  genvar step4_A0;
  generate
    for (step4_A0 = 0; step4_A0 < 128; step4_A0 = step4_A0 + 1) begin
      ysyx_041514_alu_mul_compressor42 u_alu_mul_compressor42_step4_A0 (
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




  assign mul_final128 = step4_A0_sum + {step4_A0_carry[126:0], 1'b0};

  // /* step5 TODO:插入流水线 */
  // assign mul_out_o = 
endmodule
