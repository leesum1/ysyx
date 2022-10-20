`include "sysconfig.v"


module ysyx_041514_uncache_check (
    input [`ysyx_041514_NPC_ADDR_BUS] addr_check_i,
    output uncache_valid_o
);

`ifndef ysyx_041514_YSYX_SOC
  assign uncache_valid_o = addr_check_i >= `ysyx_041514_MMIO_BASE;
`else
  assign uncache_valid_o = addr_check_i < 32'h80000000;
`endif

  //   assign uncache_valid_o = 1'b1;
endmodule
