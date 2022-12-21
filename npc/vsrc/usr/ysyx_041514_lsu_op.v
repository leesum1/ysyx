`include "sysconfig.v"
module ysyx_041514_lsu_op (

    /* from ex/mem */
    input  [`ysyx_041514_MEMOP_LEN-1:0] mem_op_i,       // 访存操作码
    output                              ls_valid_o,
    output                              ls_type_o,      // load:0,store:1
    output                              ls_signed_o,    // signed:1,unsigned:0
    output [                       3:0] ls_size_o,      // [8,4,2,1]
    output                              fencei_valid_o
);


  wire memop_none = ~(|mem_op_i);
  wire memop_lb = mem_op_i[`ysyx_041514_MEMOP_LB];
  wire memop_lbu = mem_op_i[`ysyx_041514_MEMOP_LBU];
  wire memop_sb = mem_op_i[`ysyx_041514_MEMOP_SB];
  wire memop_lh = mem_op_i[`ysyx_041514_MEMOP_LH];
  wire memop_lhu = mem_op_i[`ysyx_041514_MEMOP_LHU];
  wire memop_sh = mem_op_i[`ysyx_041514_MEMOP_SH];
  wire memop_lw = mem_op_i[`ysyx_041514_MEMOP_LW];
  wire memop_lwu = mem_op_i[`ysyx_041514_MEMOP_LWU];
  wire memop_sw = mem_op_i[`ysyx_041514_MEMOP_SW];
  wire memop_ld = mem_op_i[`ysyx_041514_MEMOP_LD];
  wire memop_sd = mem_op_i[`ysyx_041514_MEMOP_SD];
  wire memop_fencei = mem_op_i[`ysyx_041514_MEMOP_FENCEI];


  /* 写入还是读取 */
  // wire isload = (memop_lb | memop_lbu | memop_ld | memop_lh | memop_lhu | memop_lw | memop_lwu);
  wire isstore = (memop_sb | memop_sd | memop_sh | memop_sw);

  /* 读取或写入的 byte */
  wire ls1byte = memop_lb | memop_lbu | memop_sb;
  wire ls2byte = memop_lh | memop_lhu | memop_sh;
  wire ls4byte = memop_lw | memop_sw | memop_lwu;
  wire ls8byte = memop_ld | memop_sd;

  /* 是否进行符号扩展 */
  // wire ls_unsigned = memop_lhu | memop_lbu | memop_lwu;
  wire ls_signed = memop_lh | memop_lb | memop_lw | memop_ld;





  assign ls_valid_o = (!memop_fencei) & (!memop_none);  // fencei 有效时，不使能
  assign ls_type_o = isstore;  // load:0,store:1
  assign ls_size_o = {ls8byte, ls4byte, ls2byte, ls1byte};
  assign ls_signed_o = ls_signed;  // signed:1,unsigned:0
  assign fencei_valid_o = memop_fencei;

endmodule
