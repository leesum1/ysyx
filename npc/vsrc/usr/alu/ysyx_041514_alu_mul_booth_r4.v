`include "sysconfig.v"
module ysyx_041514_alu_mul_booth_r4 (

    input             rs1_signed_valid_i,
    input             rs2_signed_valid_i,
    input [`ysyx_041514_XLEN_BUS] rs1_data_i,
    input [`ysyx_041514_XLEN_BUS] rs2_data_i,

    output [128-1:0] pp0_o,
    output [128-1:0] pp1_o,
    output [128-1:0] pp2_o,
    output [128-1:0] pp3_o,
    output [128-1:0] pp4_o,
    output [128-1:0] pp5_o,
    output [128-1:0] pp6_o,
    output [128-1:0] pp7_o,
    output [128-1:0] pp8_o,
    output [128-1:0] pp9_o,
    output [128-1:0] pp10_o,
    output [128-1:0] pp11_o,
    output [128-1:0] pp12_o,
    output [128-1:0] pp13_o,
    output [128-1:0] pp14_o,
    output [128-1:0] pp15_o,
    output [128-1:0] pp16_o,
    output [128-1:0] pp17_o,
    output [128-1:0] pp18_o,
    output [128-1:0] pp19_o,
    output [128-1:0] pp20_o,
    output [128-1:0] pp21_o,
    output [128-1:0] pp22_o,
    output [128-1:0] pp23_o,
    output [128-1:0] pp24_o,
    output [128-1:0] pp25_o,
    output [128-1:0] pp26_o,
    output [128-1:0] pp27_o,
    output [128-1:0] pp28_o,
    output [128-1:0] pp29_o,
    output [128-1:0] pp30_o,
    output [128-1:0] pp31_o,
    output [128-1:0] pp32_o
);

  // 两位符号扩展
  wire [66-1:0]rs1_66 = rs1_signed_valid_i?{{2{rs1_data_i[63]}},rs1_data_i}:{2'b00,rs1_data_i};
  wire [66-1:0]rs2_66 = rs2_signed_valid_i?{{2{rs2_data_i[63]}},rs2_data_i}:{2'b00,rs2_data_i};
  // booth 编码
  wire [66-1:0] x = rs1_66;
  wire [66-1:0] x_double = {x[66-2:0], 1'b0};
  wire [66-1:0] x_neg = ~x + 1;  // TODO 加法器可以省吗？，可以但要改结构
  wire [66-1:0] x_neg_double = {x_neg[66-2:0], 1'b0};
  // booth 编码 扫描数
  wire [67-1:0] scan_num = {rs2_66, 1'b0};

  wire [66-1:0] pp_o[33-1:0];  // 部分积
  genvar i;
  generate
    // i*2+1==j
    for (i = 0; i < 33; i = i + 1) begin : gen_pp
      wire x_valid = (scan_num[i*2+2:i*2] == 3'b001) | (scan_num[i*2+2:i*2] == 3'b010);
      wire x_neg_valid = (scan_num[i*2+2:i*2] == 3'b101) | (scan_num[i*2+2:i*2] == 3'b110);
      wire x_neg_double_valid = (scan_num[i*2+2:i*2] == 3'b100);
      wire x_double_valid = (scan_num[i*2+2:i*2] == 3'b011);
      wire x_zero_valid = (scan_num[i*2+2:i*2] == 3'b000) | (scan_num[i*2+2:i*2] == 3'b111);

      assign pp_o[i] = ({66{x_valid}}&x) 
                     | ({66{x_neg_valid}}&x_neg) 
                     | ({66{x_neg_double_valid}}&x_neg_double) 
                     | ({66{x_double_valid}}&x_double) 
                     | ({66{x_zero_valid}}&66'b0);
    end
  endgenerate


  // 手动移位器，将部分积移动到 128 bit 中对应的位置上
  assign pp0_o  = {{128 - 66 - 0{1'b0}}, pp_o[0]};
  assign pp1_o  = {{128 - 66 - 2{1'b0}}, pp_o[1], 2'b0};
  assign pp2_o  = {{128 - 66 - 4{1'b0}}, pp_o[2], 4'b0};
  assign pp3_o  = {{128 - 66 - 6{1'b0}}, pp_o[3], 6'b0};
  assign pp4_o  = {{128 - 66 - 8{1'b0}}, pp_o[4], 8'b0};
  assign pp5_o  = {{128 - 66 - 10{1'b0}}, pp_o[5], 10'b0};
  assign pp6_o  = {{128 - 66 - 12{1'b0}}, pp_o[6], 12'b0};
  assign pp7_o  = {{128 - 66 - 14{1'b0}}, pp_o[7], 14'b0};
  assign pp8_o  = {{128 - 66 - 16{1'b0}}, pp_o[8], 16'b0};
  assign pp9_o  = {{128 - 66 - 18{1'b0}}, pp_o[9], 18'b0};
  assign pp10_o = {{128 - 66 - 20{1'b0}}, pp_o[10], 20'b0};
  assign pp11_o = {{128 - 66 - 22{1'b0}}, pp_o[11], 22'b0};
  assign pp12_o = {{128 - 66 - 24{1'b0}}, pp_o[12], 24'b0};
  assign pp13_o = {{128 - 66 - 26{1'b0}}, pp_o[13], 26'b0};
  assign pp14_o = {{128 - 66 - 28{1'b0}}, pp_o[14], 28'b0};
  assign pp15_o = {{128 - 66 - 30{1'b0}}, pp_o[15], 30'b0};
  assign pp16_o = {{128 - 66 - 32{1'b0}}, pp_o[16], 32'b0};
  assign pp17_o = {{128 - 66 - 34{1'b0}}, pp_o[17], 34'b0};
  assign pp18_o = {{128 - 66 - 36{1'b0}}, pp_o[18], 36'b0};
  assign pp19_o = {{128 - 66 - 38{1'b0}}, pp_o[19], 38'b0};
  assign pp20_o = {{128 - 66 - 40{1'b0}}, pp_o[20], 40'b0};
  assign pp21_o = {{128 - 66 - 42{1'b0}}, pp_o[21], 42'b0};
  assign pp22_o = {{128 - 66 - 44{1'b0}}, pp_o[22], 44'b0};
  assign pp23_o = {{128 - 66 - 46{1'b0}}, pp_o[23], 46'b0};
  assign pp24_o = {{128 - 66 - 48{1'b0}}, pp_o[24], 48'b0};
  assign pp25_o = {{128 - 66 - 50{1'b0}}, pp_o[25], 50'b0};
  assign pp26_o = {{128 - 66 - 52{1'b0}}, pp_o[26], 52'b0};
  assign pp27_o = {{128 - 66 - 54{1'b0}}, pp_o[27], 54'b0};
  assign pp28_o = {{128 - 66 - 56{1'b0}}, pp_o[28], 56'b0};
  assign pp29_o = {{128 - 66 - 58{1'b0}}, pp_o[29], 58'b0};
  assign pp30_o = {{128 - 66 - 60{1'b0}}, pp_o[30], 60'b0};
  assign pp31_o = {{128 - 66 - 62{1'b0}}, pp_o[31], 62'b0};
  assign pp32_o = {pp_o[32][63:0], 64'b0};  // 最后一个部分积特殊处理，溢出两位


endmodule
