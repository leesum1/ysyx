module ysyx_041514_sram (

    input clk,
    
    input  [  5:0] io_sram0_addr,
    input          io_sram0_cen,
    input          io_sram0_wen,
    input  [127:0] io_sram0_wmask,
    input  [127:0] io_sram0_wdata,
    output [127:0] io_sram0_rdata,

    input  [  5:0] io_sram1_addr,
    input          io_sram1_cen,
    input          io_sram1_wen,
    input  [127:0] io_sram1_wmask,
    input  [127:0] io_sram1_wdata,
    output [127:0] io_sram1_rdata,

    input  [  5:0] io_sram2_addr,
    input          io_sram2_cen,
    input          io_sram2_wen,
    input  [127:0] io_sram2_wmask,
    input  [127:0] io_sram2_wdata,
    output [127:0] io_sram2_rdata,

    input  [  5:0] io_sram3_addr,
    input          io_sram3_cen,
    input          io_sram3_wen,
    input  [127:0] io_sram3_wmask,
    input  [127:0] io_sram3_wdata,
    output [127:0] io_sram3_rdata,

    input  [  5:0] io_sram4_addr,
    input          io_sram4_cen,
    input          io_sram4_wen,
    input  [127:0] io_sram4_wmask,
    input  [127:0] io_sram4_wdata,
    output [127:0] io_sram4_rdata,

    input  [  5:0] io_sram5_addr,
    input          io_sram5_cen,
    input          io_sram5_wen,
    input  [127:0] io_sram5_wmask,
    input  [127:0] io_sram5_wdata,
    output [127:0] io_sram5_rdata,

    input  [  5:0] io_sram6_addr,
    input          io_sram6_cen,
    input          io_sram6_wen,
    input  [127:0] io_sram6_wmask,
    input  [127:0] io_sram6_wdata,
    output [127:0] io_sram6_rdata,

    input  [  5:0] io_sram7_addr,
    input          io_sram7_cen,
    input          io_sram7_wen,
    input  [127:0] io_sram7_wmask,
    input  [127:0] io_sram7_wdata,
    output [127:0] io_sram7_rdata
);

ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram0 (
    .Q       (io_sram0_rdata),
    .CLK     (clk),
    .CEN     (io_sram0_cen),
    .WEN     (io_sram0_wen),
    .BWEN    (io_sram0_wmask),
    .A       (io_sram0_addr),
    .D       (io_sram0_wdata)
);

ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram1 (
    .Q       (io_sram1_rdata),
    .CLK     (clk),
    .CEN     (io_sram1_cen),
    .WEN     (io_sram1_wen),
    .BWEN    (io_sram1_wmask),
    .A       (io_sram1_addr),
    .D       (io_sram1_wdata)
);


ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram2 (
    .Q       (io_sram2_rdata),
    .CLK     (clk),
    .CEN     (io_sram2_cen),
    .WEN     (io_sram2_wen),
    .BWEN    (io_sram2_wmask),
    .A       (io_sram2_addr),
    .D       (io_sram2_wdata)
);


ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram3 (
    .Q       (io_sram3_rdata),
    .CLK     (clk),
    .CEN     (io_sram3_cen),
    .WEN     (io_sram3_wen),
    .BWEN    (io_sram3_wmask),
    .A       (io_sram3_addr),
    .D       (io_sram3_wdata)
);


ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram4 (
    .Q       (io_sram4_rdata),
    .CLK     (clk),
    .CEN     (io_sram4_cen),
    .WEN     (io_sram4_wen),
    .BWEN    (io_sram4_wmask),
    .A       (io_sram4_addr),
    .D       (io_sram4_wdata)
);


ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram5 (
    .Q       (io_sram5_rdata),
    .CLK     (clk),
    .CEN     (io_sram5_cen),
    .WEN     (io_sram5_wen),
    .BWEN    (io_sram5_wmask),
    .A       (io_sram5_addr),
    .D       (io_sram5_wdata)
);


ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram6 (
    .Q       (io_sram6_rdata),
    .CLK     (clk),
    .CEN     (io_sram6_cen),
    .WEN     (io_sram6_wen),
    .BWEN    (io_sram6_wmask),
    .A       (io_sram6_addr),
    .D       (io_sram6_wdata)
);


ysyx_041514_S011HD1P_X32Y2D128_BW u_S011HD1P_X32Y2D128_BW_sram7 (
    .Q       (io_sram7_rdata),
    .CLK     (clk),
    .CEN     (io_sram7_cen),
    .WEN     (io_sram7_wen),
    .BWEN    (io_sram7_wmask),
    .A       (io_sram7_addr),
    .D       (io_sram7_wdata)
);

endmodule
