`include "sysconfig.v"

// 用于进行 load data 的符号扩展
module ysyx_041514_lsu_ext (

    /* from ex/mem */
    input  [`ysyx_041514_XLEN_BUS] ext_data_i,
    input                          ls_signed_i,  // signed:1,unsigned:0
    input  [                  3:0] ls_size_i,    // [8,4,2,1]
    output [`ysyx_041514_XLEN_BUS] ext_data_o
);


  /* 符号扩展后的结果 */
  wire [`ysyx_041514_XLEN_BUS] _ext_data = ({64{ls_size_i[0]}}&{{`ysyx_041514_XLEN-8{ext_data_i[7]&ls_signed_i}},ext_data_i[7:0]})
                                               | ({64{ls_size_i[1]}}&{{`ysyx_041514_XLEN-16{ext_data_i[15]&ls_signed_i}},ext_data_i[15:0]})
                                               | ({64{ls_size_i[2]}}&{{`ysyx_041514_XLEN-32{ext_data_i[31]&ls_signed_i}},ext_data_i[31:0]})
                                               | ({64{ls_size_i[3]}}&ext_data_i);

  assign ext_data_o = _ext_data;

endmodule
