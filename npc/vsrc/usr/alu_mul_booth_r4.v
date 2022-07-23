module alu_mul_booth_r4 (
    input  wire        i_multa_ns,  // 0-multa is unsigned, 1-multa is signed
    input  wire        i_multb_ns,  // 0-multb is unsigned, 1-multb is signed
    input  wire [63:0] i_multa,     // Multiplicand
    input  wire [63:0] i_multb,     // Multipler
    output wire [65:0] o_pp1,       // partial products
    output wire [65:0] o_pp2,
    output wire [65:0] o_pp3,
    output wire [65:0] o_pp4,
    output wire [65:0] o_pp5,
    output wire [65:0] o_pp6,
    output wire [65:0] o_pp7,
    output wire [65:0] o_pp8,
    output wire [65:0] o_pp9,
    output wire [65:0] o_pp10,
    output wire [65:0] o_pp11,
    output wire [65:0] o_pp12,
    output wire [65:0] o_pp13,
    output wire [65:0] o_pp14,
    output wire [65:0] o_pp15,
    output wire [65:0] o_pp16,
    output wire [65:0] o_pp17,
    output wire [65:0] o_pp18,
    output wire [65:0] o_pp19,
    output wire [65:0] o_pp20,
    output wire [65:0] o_pp21,
    output wire [65:0] o_pp22,
    output wire [65:0] o_pp23,
    output wire [65:0] o_pp24,
    output wire [65:0] o_pp25,
    output wire [65:0] o_pp26,
    output wire [65:0] o_pp27,
    output wire [65:0] o_pp28,
    output wire [65:0] o_pp29,
    output wire [65:0] o_pp30,
    output wire [65:0] o_pp31,
    output wire [65:0] o_pp32,
    output wire [65:0] o_pp33
);

  // sign bit extend, for unsigned operator extended by 0, for signed operator extended by orignal sign bit
  wire [ 1:0] sig_exta = ~i_multa_ns ? 2'b00 : {2{i_multa[63]}};
  wire [ 1:0] sig_extb = ~i_multb_ns ? 2'b00 : {2{i_multb[63]}};



  // generat -x, -2x, 2x for Booth encoding
  wire [65:0] x = {sig_exta, i_multa};
  wire [65:0] x_c = ~x + 1;  // -x, complement code of x
  wire [65:0] xm2 = x << 1;  // 2*x
  wire [65:0] x_cm2 = x_c << 1;  // -2*x

  //        18 17         [16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1]     0  
  //        |---|          |------------------------------------|      |
  // extended sign bits              orignal operator             appended bit for encoding
  wire [66:0] y = {sig_extb, i_multb, 1'b0};

  // calculating partial product based on Booth Radix-4 encoding
  wire [65:0]                                                    pp[32:0];
  generate
    genvar i;
    for (i = 0; i < 66; i = i + 2) begin : GEN_PP
      assign pp[i/2] = (y[i+2:i] == 3'b001 || y[i+2:i] == 3'b010) ? x     :
                       (y[i+2:i] == 3'b101 || y[i+2:i] == 3'b110) ? x_c   :
                   (y[i+2:i] == 3'b011                      ) ? xm2   :
                   (y[i+2:i] == 3'b100                      ) ? x_cm2 : 66'b0;
    end
  endgenerate
  assign o_pp1  = pp[0];
  assign o_pp2  = pp[1];
  assign o_pp3  = pp[2];
  assign o_pp4  = pp[3];
  assign o_pp5  = pp[4];
  assign o_pp6  = pp[5];
  assign o_pp7  = pp[6];
  assign o_pp8  = pp[7];
  assign o_pp9  = pp[8];
  assign o_pp10 = pp[9];
  assign o_pp11 = pp[10];
  assign o_pp12 = pp[11];
  assign o_pp13 = pp[12];
  assign o_pp14 = pp[13];
  assign o_pp15 = pp[14];
  assign o_pp16 = pp[15];
  assign o_pp17 = pp[16];
  assign o_pp18 = pp[17];
  assign o_pp19 = pp[18];
  assign o_pp20 = pp[19];
  assign o_pp21 = pp[20];
  assign o_pp22 = pp[21];
  assign o_pp23 = pp[22];
  assign o_pp24 = pp[23];
  assign o_pp25 = pp[24];
  assign o_pp26 = pp[25];
  assign o_pp27 = pp[26];
  assign o_pp28 = pp[27];
  assign o_pp29 = pp[28];
  assign o_pp30 = pp[29];
  assign o_pp31 = pp[30];
  assign o_pp32 = pp[31];
  assign o_pp33 = pp[32];

endmodule
