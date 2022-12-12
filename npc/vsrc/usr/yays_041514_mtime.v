`include "sysconfig.v"
module yays_041514_mtime (
    input                              clk,
    input                              rst,
    input  [`ysyx_041514_NPC_ADDR_BUS] mtime_addr_i,
    input                              mtime_write_valid_i,
    input  [    `ysyx_041514_XLEN_BUS] mtime_wdata_i,
    output [    `ysyx_041514_XLEN_BUS] mtime_rdata_o,
    output                             mtime_ge_mtime_o
);

  wire mtime_en = mtime_addr_i == `ysyx_041514_MTIME_ADDR;
  wire mtimecmp_en = mtime_addr_i == `ysyx_041514_MTIMECMP_ADDR;
  wire mtime_write_en = mtime_write_valid_i & mtime_en;
  wire mtimecmp_write_en = mtime_write_valid_i & mtimecmp_en;


  /* mtime reg */
  wire [`ysyx_041514_XLEN-1:0] _mtime_d = mtime_write_en ? mtime_wdata_i : _mtime_q + 'd1;
  wire [`ysyx_041514_XLEN-1:0] _mtime_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_mtime (
      .clk (clk),
      .rst (rst),
      .din (_mtime_d),
      .dout(_mtime_q),
      .wen (1'b1)
  );

  /* mtimcmp reg */
  wire [`ysyx_041514_XLEN-1:0] _mtimecmp_d = mtime_wdata_i;
  wire [`ysyx_041514_XLEN-1:0] _mtimecmp_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_mtimecmp (
      .clk (clk),
      .rst (rst),
      .din (_mtimecmp_d),
      .dout(_mtimecmp_q),
      .wen (mtimecmp_write_en)
  );


  assign mtime_rdata_o = ({`ysyx_041514_XLEN{mtime_en}}&_mtime_q)
                       | ({`ysyx_041514_XLEN{mtimecmp_en}}&_mtimecmp_q);

  wire mtime_ge_mtime = (_mtime_q >= _mtimecmp_q);  // mtime >= mtimecmp
  assign mtime_ge_mtime_o = mtime_ge_mtime;

endmodule
