`include "sysconfig.v"
// 1. booth 华莱士乘法树，采用 全加器（csa）实现
module ysyx_041514_alu_mul_wallace_csa (
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
  // 寄存器已经复位
  localparam STATE_LEN = 3;
  localparam MUL_RST = 3'd0;
  localparam MUL_IDLE = 3'd1;
  localparam MUL_WAIT = 3'd3;



  wire _mul_valid = mul_valid_i;
  reg [STATE_LEN-1:0] mul_state;

  reg [3:0] mul_count;
  wire [3:0] mul_count_plus1 = mul_count + 'd1;

  reg mul_ready;
  reg [127:0] mul_data128;

  reg [`ysyx_041514_XLEN_BUS] booth_rs1;
  reg [`ysyx_041514_XLEN_BUS] booth_rs2;
  reg booth_rs1_signed_valid;
  reg booth_rs2_signed_valid;


  wire [127:0] mul_final128;
  assign mul_ready_o = mul_ready;

  assign mul_out_o   = mul_data128;


  /* 乘法状态机切换 */
  always @(posedge clk) begin
    if (rst) begin
      mul_state <= MUL_RST;
      mul_ready <= `ysyx_041514_FALSE;
      mul_data128 <= 'b0;
      mul_count <= 'b0;
      booth_rs1 <= 'b0;
      booth_rs2 <= 'b0;
      booth_rs1_signed_valid <= 'b0;
      booth_rs2_signed_valid <= 'b0;
    end else begin
      case (mul_state)
        MUL_RST: begin
          mul_state <= MUL_IDLE;
        end
        MUL_IDLE: begin
          mul_ready <= `ysyx_041514_FALSE;
          mul_count <= 'b0;
          if (_mul_valid) begin  // 乘法请求
            mul_state <= MUL_WAIT;
            booth_rs1 <= rs1_data_i;
            booth_rs2 <= rs2_data_i;
            booth_rs1_signed_valid <= rs1_signed_valid_i;
            booth_rs2_signed_valid <= rs2_signed_valid_i;
          end
        end
        MUL_WAIT: begin
          if (~_mul_valid) begin
            mul_state <= MUL_IDLE;
          end else begin
            mul_count <= mul_count_plus1;
            if (mul_count == 'd3) begin
              mul_data128 <= mul_final128;
              mul_state   <= MUL_IDLE;
              mul_ready   <= `ysyx_041514_TRUE;
            end
          end
        end
        default: begin
        end
      endcase
    end
  end







  wire [127:0] Partial_product[33-1:0];
  ysyx_041514_alu_mul_booth_r4 u_alu_mul_booth_r4 (
      .rs1_signed_valid_i(booth_rs1_signed_valid),
      .rs2_signed_valid_i(booth_rs2_signed_valid),
      .rs1_data_i        (booth_rs1),
      .rs2_data_i        (booth_rs2),
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

  //  部分积生成 ( 共33 个),缓存一个周期
  wire [127:0] step1_pp_q[33-1:0];

  genvar step1_Dflap;
  generate
    for (step1_Dflap = 0; step1_Dflap < 33; step1_Dflap = step1_Dflap + 1) begin
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL(0)
      ) u_ysyx_041514_regTemplate (
          .clk (clk),
          .rst (rst),
          .din (Partial_product[step1_Dflap]),
          .dout(step1_pp_q[step1_Dflap]),
          .wen (1'b1)
      );
    end
  endgenerate

  // wire [127:0] step1_pp[33-1:0];
  // assign step1_pp = step1_pp_q;

  /*******                    booth                ********/
  /* 流水线缓存1 */
  /*******                wallace tree            ********/
  /*******(33)             11*csa(3-2) --0        ********/
  /*******(22)             7*csa(3-2)  --1        ********/
  /*******(15)             5*csa(3-2)  --0        ********/
  /*******(10)             3*csa(3-2)  --1        ********/
  /* 流水线缓存2 */
  /*******(7)              2*csa(3-2)  --1        ********/
  /*******(5)              1*csa(3-2)  --2        ********/
  /*******(4)              1*csa(3-2)  --1        ********/
  /*******(3)              1*csa(3-2)  --0        ********/
  /* 流水线缓存3 */
  /*******(2)              add(2-1)               ********/
  /* 流水线缓存4 */
  /*******(1)              mul_final              ********/


  /* step1  */
  localparam STEP1_CSA_NUM = 11;
  genvar step1_num_count;
  genvar step1_bit_count;
  wire [128-1:0] step1_sum  [STEP1_CSA_NUM-1:0];
  wire [128-1:0] step1_carry[STEP1_CSA_NUM-1:0];

  generate
    for (
        step1_num_count = 0; step1_num_count < STEP1_CSA_NUM; step1_num_count = step1_num_count + 1
    ) begin
      for (step1_bit_count = 0; step1_bit_count < 128; step1_bit_count = step1_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step1 (
            .a (step1_pp_q[step1_num_count*3+0][step1_bit_count]),
            .b (step1_pp_q[step1_num_count*3+1][step1_bit_count]),
            .ci(step1_pp_q[step1_num_count*3+2][step1_bit_count]),
            .s (step1_sum[step1_num_count][step1_bit_count]),
            .co(step1_carry[step1_num_count][step1_bit_count])
        );
      end
    end
  endgenerate


  /* step2  */
  wire [128-1:0] step2_pp_q[22-1:0];
  genvar step2_pp_q_count;
  generate
    for (
        step2_pp_q_count = 0;
        step2_pp_q_count < STEP1_CSA_NUM;
        step2_pp_q_count = step2_pp_q_count + 1
    ) begin
      assign step2_pp_q[step2_pp_q_count*2+0] = step1_sum[step2_pp_q_count];
      assign step2_pp_q[step2_pp_q_count*2+1] = {step1_carry[step2_pp_q_count][126:0], 1'b0};
    end
  endgenerate



  localparam STEP2_CSA_NUM = 7;
  genvar step2_num_count;
  genvar step2_bit_count;
  wire [128-1:0] step2_sum  [STEP2_CSA_NUM-1:0];
  wire [128-1:0] step2_carry[STEP2_CSA_NUM-1:0];
  generate
    for (
        step2_num_count = 0; step2_num_count < STEP2_CSA_NUM; step2_num_count = step2_num_count + 1
    ) begin
      for (step2_bit_count = 0; step2_bit_count < 128; step2_bit_count = step2_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step2 (
            .a (step2_pp_q[step2_num_count*3+0][step2_bit_count]),
            .b (step2_pp_q[step2_num_count*3+1][step2_bit_count]),
            .ci(step2_pp_q[step2_num_count*3+2][step2_bit_count]),
            .s (step2_sum[step2_num_count][step2_bit_count]),
            .co(step2_carry[step2_num_count][step2_bit_count])
        );
      end
    end
  endgenerate



  /* step3  */
  wire [128-1:0] step3_pp_q[15-1:0];
  assign step3_pp_q[14] = step2_pp_q[21];  // 单独处理
  genvar step3_pp_q_count;
  generate
    for (
        step3_pp_q_count = 0;
        step3_pp_q_count < STEP2_CSA_NUM;
        step3_pp_q_count = step3_pp_q_count + 1
    ) begin
      assign step3_pp_q[step3_pp_q_count*2+0] = step2_sum[step3_pp_q_count];
      assign step3_pp_q[step3_pp_q_count*2+1] = {step2_carry[step3_pp_q_count][126:0], 1'b0};
    end
  endgenerate



  localparam STEP3_CSA_NUM = 5;
  genvar step3_num_count;
  genvar step3_bit_count;
  wire [128-1:0] step3_sum  [STEP3_CSA_NUM-1:0];
  wire [128-1:0] step3_carry[STEP3_CSA_NUM-1:0];
  generate
    for (
        step3_num_count = 0; step3_num_count < STEP3_CSA_NUM; step3_num_count = step3_num_count + 1
    ) begin
      for (step3_bit_count = 0; step3_bit_count < 128; step3_bit_count = step3_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step3 (
            .a (step3_pp_q[step3_num_count*3+0][step3_bit_count]),
            .b (step3_pp_q[step3_num_count*3+1][step3_bit_count]),
            .ci(step3_pp_q[step3_num_count*3+2][step3_bit_count]),
            .s (step3_sum[step3_num_count][step3_bit_count]),
            .co(step3_carry[step3_num_count][step3_bit_count])
        );
      end
    end
  endgenerate


  /* step4  */
  wire [128-1:0] step4_pp_q[10-1:0];
  // assign step4_pp_q[14] = step2_pp_q[21];  // 单独处理
  genvar step4_pp_q_count;
  generate
    for (
        step4_pp_q_count = 0;
        step4_pp_q_count < STEP3_CSA_NUM;
        step4_pp_q_count = step4_pp_q_count + 1
    ) begin
      assign step4_pp_q[step4_pp_q_count*2+0] = step3_sum[step4_pp_q_count];
      assign step4_pp_q[step4_pp_q_count*2+1] = {step3_carry[step4_pp_q_count][126:0], 1'b0};
    end
  endgenerate



  localparam STEP4_CSA_NUM = 3;
  genvar step4_num_count;
  genvar step4_bit_count;
  wire [128-1:0] step4_sum  [STEP4_CSA_NUM-1:0];
  wire [128-1:0] step4_carry[STEP4_CSA_NUM-1:0];
  generate
    for (
        step4_num_count = 0; step4_num_count < STEP4_CSA_NUM; step4_num_count = step4_num_count + 1
    ) begin
      for (step4_bit_count = 0; step4_bit_count < 128; step4_bit_count = step4_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step4 (
            .a (step4_pp_q[step4_num_count*3+0][step4_bit_count]),
            .b (step4_pp_q[step4_num_count*3+1][step4_bit_count]),
            .ci(step4_pp_q[step4_num_count*3+2][step4_bit_count]),
            .s (step4_sum[step4_num_count][step4_bit_count]),
            .co(step4_carry[step4_num_count][step4_bit_count])
        );
      end
    end
  endgenerate


  /* step5  */
  wire [128-1:0] step5_pp_q[7-1:0];
  // 单独处理
  // assign step5_pp_q[6] = step4_pp_q[9];  
  ysyx_041514_regTemplate #(
      .WIDTH    (128),
      .RESET_VAL('b0)
  ) u_ysyx_041514_regTemplate_step4_sum_alone (
      .clk (clk),
      .rst (rst),
      .din (step4_pp_q[9]),
      .dout(step5_pp_q[6]),
      .wen (1'b1)
  );

  genvar step5_pp_q_count;
  generate
    for (
        step5_pp_q_count = 0;
        step5_pp_q_count < STEP4_CSA_NUM;
        step5_pp_q_count = step5_pp_q_count + 1
    ) begin
      // assign step5_pp_q[step5_pp_q_count*2+0] = step4_sum[step5_pp_q_count];
      // assign step5_pp_q[step5_pp_q_count*2+1] = {step4_carry[step5_pp_q_count][126:0], 1'b0};
      //插入流水线缓存，切断关键路径
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL('b0)
      ) u_ysyx_041514_regTemplate_step4_sum (
          .clk (clk),
          .rst (rst),
          .din (step4_sum[step5_pp_q_count]),
          .dout(step5_pp_q[step5_pp_q_count*2+0]),
          .wen (1'b1)
      );
      ysyx_041514_regTemplate #(
          .WIDTH    (128),
          .RESET_VAL('b0)
      ) u_ysyx_041514_regTemplate_step4_carry (
          .clk (clk),
          .rst (rst),
          .din ({step4_carry[step5_pp_q_count][126:0], 1'b0}),
          .dout(step5_pp_q[step5_pp_q_count*2+1]),
          .wen (1'b1)
      );
    end
  endgenerate


  localparam STEP5_CSA_NUM = 2;
  genvar step5_num_count;
  genvar step5_bit_count;
  wire [128-1:0] step5_sum  [STEP5_CSA_NUM-1:0];
  wire [128-1:0] step5_carry[STEP5_CSA_NUM-1:0];
  generate
    for (
        step5_num_count = 0; step5_num_count < STEP5_CSA_NUM; step5_num_count = step5_num_count + 1
    ) begin
      for (step5_bit_count = 0; step5_bit_count < 128; step5_bit_count = step5_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step5 (
            .a (step5_pp_q[step5_num_count*3+0][step5_bit_count]),
            .b (step5_pp_q[step5_num_count*3+1][step5_bit_count]),
            .ci(step5_pp_q[step5_num_count*3+2][step5_bit_count]),
            .s (step5_sum[step5_num_count][step5_bit_count]),
            .co(step5_carry[step5_num_count][step5_bit_count])
        );
      end
    end
  endgenerate



  /* step6  */
  wire [128-1:0] step6_pp_q[5-1:0];
  assign step6_pp_q[4] = step5_pp_q[6];  // 单独处理
  genvar step6_pp_q_count;
  generate
    for (
        step6_pp_q_count = 0;
        step6_pp_q_count < STEP5_CSA_NUM;
        step6_pp_q_count = step6_pp_q_count + 1
    ) begin
      assign step6_pp_q[step6_pp_q_count*2+0] = step5_sum[step6_pp_q_count];
      assign step6_pp_q[step6_pp_q_count*2+1] = {step5_carry[step6_pp_q_count][126:0], 1'b0};
    end
  endgenerate


  localparam STEP6_CSA_NUM = 1;
  genvar step6_num_count;
  genvar step6_bit_count;
  wire [128-1:0] step6_sum  [STEP6_CSA_NUM-1:0];
  wire [128-1:0] step6_carry[STEP6_CSA_NUM-1:0];
  generate
    for (
        step6_num_count = 0; step6_num_count < STEP6_CSA_NUM; step6_num_count = step6_num_count + 1
    ) begin
      for (step6_bit_count = 0; step6_bit_count < 128; step6_bit_count = step6_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step6 (
            .a (step6_pp_q[step6_num_count*3+0][step6_bit_count]),
            .b (step6_pp_q[step6_num_count*3+1][step6_bit_count]),
            .ci(step6_pp_q[step6_num_count*3+2][step6_bit_count]),
            .s (step6_sum[step6_num_count][step6_bit_count]),
            .co(step6_carry[step6_num_count][step6_bit_count])
        );
      end
    end
  endgenerate



  /* step7  */
  wire [128-1:0] step7_pp_q[4-1:0];
  assign step7_pp_q[2] = step6_pp_q[3];  // 单独处理
  assign step7_pp_q[3] = step6_pp_q[4];  // 单独处理
  genvar step7_pp_q_count;
  generate
    for (
        step7_pp_q_count = 0;
        step7_pp_q_count < STEP6_CSA_NUM;
        step7_pp_q_count = step7_pp_q_count + 1
    ) begin
      assign step7_pp_q[step7_pp_q_count*2+0] = step6_sum[step7_pp_q_count];
      assign step7_pp_q[step7_pp_q_count*2+1] = {step6_carry[step7_pp_q_count][126:0], 1'b0};
    end
  endgenerate


  localparam STEP7_CSA_NUM = 1;
  genvar step7_num_count;
  genvar step7_bit_count;
  wire [128-1:0] step7_sum  [STEP7_CSA_NUM-1:0];
  wire [128-1:0] step7_carry[STEP7_CSA_NUM-1:0];
  generate
    for (
        step7_num_count = 0; step7_num_count < STEP7_CSA_NUM; step7_num_count = step7_num_count + 1
    ) begin
      for (step7_bit_count = 0; step7_bit_count < 128; step7_bit_count = step7_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step7 (
            .a (step7_pp_q[step7_num_count*3+0][step7_bit_count]),
            .b (step7_pp_q[step7_num_count*3+1][step7_bit_count]),
            .ci(step7_pp_q[step7_num_count*3+2][step7_bit_count]),
            .s (step7_sum[step7_num_count][step7_bit_count]),
            .co(step7_carry[step7_num_count][step7_bit_count])
        );
      end
    end
  endgenerate



  /* step8  */
  wire [128-1:0] step8_pp_q[3-1:0];
  assign step8_pp_q[2] = step7_pp_q[3];  // 单独处理
  genvar step8_pp_q_count;
  generate
    for (
        step8_pp_q_count = 0;
        step8_pp_q_count < STEP7_CSA_NUM;
        step8_pp_q_count = step8_pp_q_count + 1
    ) begin
      assign step8_pp_q[step8_pp_q_count*2+0] = step7_sum[step8_pp_q_count];
      assign step8_pp_q[step8_pp_q_count*2+1] = {step7_carry[step8_pp_q_count][126:0], 1'b0};
    end
  endgenerate


  localparam STEP8_CSA_NUM = 1;
  genvar step8_num_count;
  genvar step8_bit_count;
  wire [128-1:0] step8_sum  [STEP8_CSA_NUM-1:0];
  wire [128-1:0] step8_carry[STEP8_CSA_NUM-1:0];
  generate
    for (
        step8_num_count = 0; step8_num_count < STEP8_CSA_NUM; step8_num_count = step8_num_count + 1
    ) begin
      for (step8_bit_count = 0; step8_bit_count < 128; step8_bit_count = step8_bit_count + 1) begin
        ysyx_041514_full_adder u_ysyx_041514_full_adder_step8 (
            .a (step8_pp_q[step8_num_count*3+0][step8_bit_count]),
            .b (step8_pp_q[step8_num_count*3+1][step8_bit_count]),
            .ci(step8_pp_q[step8_num_count*3+2][step8_bit_count]),
            .s (step8_sum[step8_num_count][step8_bit_count]),
            .co(step8_carry[step8_num_count][step8_bit_count])
        );
      end
    end
  endgenerate

  // // 插入流水线缓存
  wire [128-1:0] mul_final_a;
  wire [128-1:0] mul_final_b;
  ysyx_041514_regTemplate #(
      .WIDTH    (128),
      .RESET_VAL('b0)
  ) u_ysyx_041514_regTemplate_step8_sum (
      .clk (clk),
      .rst (rst),
      .din (step8_sum[0]),
      .dout(mul_final_a),
      .wen (1'b1)
  );
  ysyx_041514_regTemplate #(
      .WIDTH    (128),
      .RESET_VAL('b0)
  ) u_ysyx_041514_regTemplate_step8_carry (
      .clk (clk),
      .rst (rst),
      .din ({step8_carry[0][126:0], 1'b0}),
      .dout(mul_final_b),
      .wen (1'b1)
  );

  /* step9 */
  // assign mul_final128 = step8_sum[0] + {step8_carry[0][126:0], 1'b0};
  assign mul_final128 = mul_final_a + mul_final_b;


endmodule
