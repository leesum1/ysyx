`include "sysconfig.v"


`ifdef ysyx_041514_YSYX_SOC

module ysyx_22041514 (
  input          clock,
  input          reset,
  input          io_master_arready,
  output         io_master_arvalid,
  output [31:0]  io_master_araddr,
  output [3:0]   io_master_arid,
  output [7:0]   io_master_arlen,
  output [2:0]   io_master_arsize,
  output [1:0]   io_master_arburst,
  output         io_master_rready,
  input          io_master_rvalid,
  input  [1:0]   io_master_rresp,
  input  [63:0]  io_master_rdata,
  input          io_master_rlast,
  input  [3:0]   io_master_rid,
  input          io_master_awready,
  output         io_master_awvalid,
  output [31:0]  io_master_awaddr,
  output [3:0]   io_master_awid,
  output [7:0]   io_master_awlen,
  output [2:0]   io_master_awsize,
  output [1:0]   io_master_awburst,
  input          io_master_wready,
  output         io_master_wvalid,
  output [63:0]  io_master_wdata,
  output [7:0]   io_master_wstrb,
  output         io_master_wlast,
  output         io_master_bready,
  input          io_master_bvalid,
  input  [1:0]   io_master_bresp,
  input  [3:0]   io_master_bid,
  output         io_slave_arready,
  input          io_slave_arvalid,
  input  [31:0]  io_slave_araddr,
  input  [3:0]   io_slave_arid,
  input  [7:0]   io_slave_arlen,
  input  [2:0]   io_slave_arsize,
  input  [1:0]   io_slave_arburst,
  input          io_slave_rready,
  output         io_slave_rvalid,
  output [1:0]   io_slave_rresp,
  output [63:0]  io_slave_rdata,
  output         io_slave_rlast,
  output [3:0]   io_slave_rid,
  output         io_slave_awready,
  input          io_slave_awvalid,
  input  [31:0]  io_slave_awaddr,
  input  [3:0]   io_slave_awid,
  input  [7:0]   io_slave_awlen,
  input  [2:0]   io_slave_awsize,
  input  [1:0]   io_slave_awburst,
  output         io_slave_wready,
  input          io_slave_wvalid,
  input  [63:0]  io_slave_wdata,
  input  [7:0]   io_slave_wstrb,
  input          io_slave_wlast,
  input          io_slave_bready,
  output         io_slave_bvalid,
  output [1:0]   io_slave_bresp,
  output [3:0]   io_slave_bid,
  input          io_interrupt,
  output [5:0]   io_sram0_addr,
  output         io_sram0_cen,
  output         io_sram0_wen,
  output [127:0] io_sram0_wmask,
  output [127:0] io_sram0_wdata,
  input  [127:0] io_sram0_rdata,
  output [5:0]   io_sram1_addr,
  output         io_sram1_cen,
  output         io_sram1_wen,
  output [127:0] io_sram1_wmask,
  output [127:0] io_sram1_wdata,
  input  [127:0] io_sram1_rdata,
  output [5:0]   io_sram2_addr,
  output         io_sram2_cen,
  output         io_sram2_wen,
  output [127:0] io_sram2_wmask,
  output [127:0] io_sram2_wdata,
  input  [127:0] io_sram2_rdata,
  output [5:0]   io_sram3_addr,
  output         io_sram3_cen,
  output         io_sram3_wen,
  output [127:0] io_sram3_wmask,
  output [127:0] io_sram3_wdata,
  input  [127:0] io_sram3_rdata,
  output [5:0]   io_sram4_addr,
  output         io_sram4_cen,
  output         io_sram4_wen,
  output [127:0] io_sram4_wmask,
  output [127:0] io_sram4_wdata,
  input  [127:0] io_sram4_rdata,
  output [5:0]   io_sram5_addr,
  output         io_sram5_cen,
  output         io_sram5_wen,
  output [127:0] io_sram5_wmask,
  output [127:0] io_sram5_wdata,
  input  [127:0] io_sram5_rdata,
  output [5:0]   io_sram6_addr,
  output         io_sram6_cen,
  output         io_sram6_wen,
  output [127:0] io_sram6_wmask,
  output [127:0] io_sram6_wdata,
  input  [127:0] io_sram6_rdata,
  output [5:0]   io_sram7_addr,
  output         io_sram7_cen,
  output         io_sram7_wen,
  output [127:0] io_sram7_wmask,
  output [127:0] io_sram7_wdata,
  input  [127:0] io_sram7_rdata
);

  assign io_slave_awready = 0;
  assign io_slave_wready = 0;
  assign io_slave_bvalid = 0;
  assign io_slave_bresp = 0;
  assign io_slave_bid = 0;
  assign io_slave_arready = 0;
  assign io_slave_rvalid = 0;
  assign io_slave_rresp = 0;
  assign io_slave_rdata = 0;
  assign io_slave_rlast = 0;
  assign io_slave_rid = 0;





  ysyx_041514_core u_ysyx_041514_core (
      .clk              (clock),              //todo clock reset
      .rst              (reset),
      /* AXI4 master */
      // 写地址通道
      .io_master_awready(io_master_awready),
      .io_master_awvalid(io_master_awvalid),
      .io_master_awaddr (io_master_awaddr),
      .io_master_awid   (io_master_awid),
      .io_master_awlen  (io_master_awlen),
      .io_master_awsize (io_master_awsize),
      .io_master_awburst(io_master_awburst),
      // 写数据通道
      .io_master_wready (io_master_wready),
      .io_master_wvalid (io_master_wvalid),
      .io_master_wdata  (io_master_wdata),
      .io_master_wstrb  (io_master_wstrb),
      .io_master_wlast  (io_master_wlast),
      // 写响应通道
      .io_master_bready (io_master_bready),
      .io_master_bvalid (io_master_bvalid),
      .io_master_bresp  (io_master_bresp),
      .io_master_bid    (io_master_bid),
      // 读地址通道
      .io_master_arready(io_master_arready),
      .io_master_arvalid(io_master_arvalid),
      .io_master_araddr (io_master_araddr),
      .io_master_arid   (io_master_arid),
      .io_master_arlen  (io_master_arlen),
      .io_master_arsize (io_master_arsize),
      .io_master_arburst(io_master_arburst),
      // 读数据通道
      .io_master_rready (io_master_rready),
      .io_master_rvalid (io_master_rvalid),
      .io_master_rresp  (io_master_rresp),
      .io_master_rdata  (io_master_rdata),
      .io_master_rlast  (io_master_rlast),
      .io_master_rid    (io_master_rid),
      .io_sram0_addr    (io_sram0_addr),
      .io_sram0_cen     (io_sram0_cen),
      .io_sram0_wen     (io_sram0_wen),
      .io_sram0_wmask   (io_sram0_wmask),
      .io_sram0_wdata   (io_sram0_wdata),
      .io_sram0_rdata   (io_sram0_rdata),
      .io_sram1_addr    (io_sram1_addr),
      .io_sram1_cen     (io_sram1_cen),
      .io_sram1_wen     (io_sram1_wen),
      .io_sram1_wmask   (io_sram1_wmask),
      .io_sram1_wdata   (io_sram1_wdata),
      .io_sram1_rdata   (io_sram1_rdata),
      .io_sram2_addr    (io_sram2_addr),
      .io_sram2_cen     (io_sram2_cen),
      .io_sram2_wen     (io_sram2_wen),
      .io_sram2_wmask   (io_sram2_wmask),
      .io_sram2_wdata   (io_sram2_wdata),
      .io_sram2_rdata   (io_sram2_rdata),
      .io_sram3_addr    (io_sram3_addr),
      .io_sram3_cen     (io_sram3_cen),
      .io_sram3_wen     (io_sram3_wen),
      .io_sram3_wmask   (io_sram3_wmask),
      .io_sram3_wdata   (io_sram3_wdata),
      .io_sram3_rdata   (io_sram3_rdata),
      .io_sram4_addr    (io_sram4_addr),
      .io_sram4_cen     (io_sram4_cen),
      .io_sram4_wen     (io_sram4_wen),
      .io_sram4_wmask   (io_sram4_wmask),
      .io_sram4_wdata   (io_sram4_wdata),
      .io_sram4_rdata   (io_sram4_rdata),
      .io_sram5_addr    (io_sram5_addr),
      .io_sram5_cen     (io_sram5_cen),
      .io_sram5_wen     (io_sram5_wen),
      .io_sram5_wmask   (io_sram5_wmask),
      .io_sram5_wdata   (io_sram5_wdata),
      .io_sram5_rdata   (io_sram5_rdata),
      .io_sram6_addr    (io_sram6_addr),
      .io_sram6_cen     (io_sram6_cen),
      .io_sram6_wen     (io_sram6_wen),
      .io_sram6_wmask   (io_sram6_wmask),
      .io_sram6_wdata   (io_sram6_wdata),
      .io_sram6_rdata   (io_sram6_rdata),
      .io_sram7_addr    (io_sram7_addr),
      .io_sram7_cen     (io_sram7_cen),
      .io_sram7_wen     (io_sram7_wen),
      .io_sram7_wmask   (io_sram7_wmask),
      .io_sram7_wdata   (io_sram7_wdata),
      .io_sram7_rdata   (io_sram7_rdata)
  );

endmodule
`else


module ysyx_22041514 (
  input          clock,
  input          reset,
  input          io_master_arready,
  output         io_master_arvalid,
  output [31:0]  io_master_araddr,
  output [3:0]   io_master_arid,
  output [7:0]   io_master_arlen,
  output [2:0]   io_master_arsize,
  output [1:0]   io_master_arburst,
  output         io_master_rready,
  input          io_master_rvalid,
  input  [1:0]   io_master_rresp,
  input  [63:0]  io_master_rdata,
  input          io_master_rlast,
  input  [3:0]   io_master_rid,
  input          io_master_awready,
  output         io_master_awvalid,
  output [31:0]  io_master_awaddr,
  output [3:0]   io_master_awid,
  output [7:0]   io_master_awlen,
  output [2:0]   io_master_awsize,
  output [1:0]   io_master_awburst,
  input          io_master_wready,
  output         io_master_wvalid,
  output [63:0]  io_master_wdata,
  output [7:0]   io_master_wstrb,
  output         io_master_wlast,
  output         io_master_bready,
  input          io_master_bvalid,
  input  [1:0]   io_master_bresp,
  input  [3:0]   io_master_bid
);


  ysyx_041514_core u_ysyx_041514_core (
      .clk              (clock),              //todo clock reset
      .rst              (reset),
      /* AXI4 master */
      // 写地址通道
      .io_master_awready(io_master_awready),
      .io_master_awvalid(io_master_awvalid),
      .io_master_awaddr (io_master_awaddr),
      .io_master_awid   (io_master_awid),
      .io_master_awlen  (io_master_awlen),
      .io_master_awsize (io_master_awsize),
      .io_master_awburst(io_master_awburst),
      // 写数据通道
      .io_master_wready (io_master_wready),
      .io_master_wvalid (io_master_wvalid),
      .io_master_wdata  (io_master_wdata),
      .io_master_wstrb  (io_master_wstrb),
      .io_master_wlast  (io_master_wlast),
      // 写响应通道
      .io_master_bready (io_master_bready),
      .io_master_bvalid (io_master_bvalid),
      .io_master_bresp  (io_master_bresp),
      .io_master_bid    (io_master_bid),
      // 读地址通道
      .io_master_arready(io_master_arready),
      .io_master_arvalid(io_master_arvalid),
      .io_master_araddr (io_master_araddr),
      .io_master_arid   (io_master_arid),
      .io_master_arlen  (io_master_arlen),
      .io_master_arsize (io_master_arsize),
      .io_master_arburst(io_master_arburst),
      // 读数据通道
      .io_master_rready (io_master_rready),
      .io_master_rvalid (io_master_rvalid),
      .io_master_rresp  (io_master_rresp),
      .io_master_rdata  (io_master_rdata),
      .io_master_rlast  (io_master_rlast),
      .io_master_rid    (io_master_rid),
      .io_sram0_addr    (io_sram0_addr),
      .io_sram0_cen     (io_sram0_cen),
      .io_sram0_wen     (io_sram0_wen),
      .io_sram0_wmask   (io_sram0_wmask),
      .io_sram0_wdata   (io_sram0_wdata),
      .io_sram0_rdata   (io_sram0_rdata),
      .io_sram1_addr    (io_sram1_addr),
      .io_sram1_cen     (io_sram1_cen),
      .io_sram1_wen     (io_sram1_wen),
      .io_sram1_wmask   (io_sram1_wmask),
      .io_sram1_wdata   (io_sram1_wdata),
      .io_sram1_rdata   (io_sram1_rdata),
      .io_sram2_addr    (io_sram2_addr),
      .io_sram2_cen     (io_sram2_cen),
      .io_sram2_wen     (io_sram2_wen),
      .io_sram2_wmask   (io_sram2_wmask),
      .io_sram2_wdata   (io_sram2_wdata),
      .io_sram2_rdata   (io_sram2_rdata),
      .io_sram3_addr    (io_sram3_addr),
      .io_sram3_cen     (io_sram3_cen),
      .io_sram3_wen     (io_sram3_wen),
      .io_sram3_wmask   (io_sram3_wmask),
      .io_sram3_wdata   (io_sram3_wdata),
      .io_sram3_rdata   (io_sram3_rdata),
      .io_sram4_addr    (io_sram4_addr),
      .io_sram4_cen     (io_sram4_cen),
      .io_sram4_wen     (io_sram4_wen),
      .io_sram4_wmask   (io_sram4_wmask),
      .io_sram4_wdata   (io_sram4_wdata),
      .io_sram4_rdata   (io_sram4_rdata),
      .io_sram5_addr    (io_sram5_addr),
      .io_sram5_cen     (io_sram5_cen),
      .io_sram5_wen     (io_sram5_wen),
      .io_sram5_wmask   (io_sram5_wmask),
      .io_sram5_wdata   (io_sram5_wdata),
      .io_sram5_rdata   (io_sram5_rdata),
      .io_sram6_addr    (io_sram6_addr),
      .io_sram6_cen     (io_sram6_cen),
      .io_sram6_wen     (io_sram6_wen),
      .io_sram6_wmask   (io_sram6_wmask),
      .io_sram6_wdata   (io_sram6_wdata),
      .io_sram6_rdata   (io_sram6_rdata),
      .io_sram7_addr    (io_sram7_addr),
      .io_sram7_cen     (io_sram7_cen),
      .io_sram7_wen     (io_sram7_wen),
      .io_sram7_wmask   (io_sram7_wmask),
      .io_sram7_wdata   (io_sram7_wdata),
      .io_sram7_rdata   (io_sram7_rdata)
  );


/* sram 接口 测试使用 */

  wire [  5:0] io_sram0_addr;
  wire         io_sram0_cen;
  wire         io_sram0_wen;
  wire [127:0] io_sram0_wmask;
  wire [127:0] io_sram0_wdata;
  wire [127:0] io_sram0_rdata;

  wire [  5:0] io_sram1_addr;
  wire         io_sram1_cen;
  wire         io_sram1_wen;
  wire [127:0] io_sram1_wmask;
  wire [127:0] io_sram1_wdata;
  wire [127:0] io_sram1_rdata;

  wire [  5:0] io_sram2_addr;
  wire         io_sram2_cen;
  wire         io_sram2_wen;
  wire [127:0] io_sram2_wmask;
  wire [127:0] io_sram2_wdata;
  wire [127:0] io_sram2_rdata;

  wire [  5:0] io_sram3_addr;
  wire         io_sram3_cen;
  wire         io_sram3_wen;
  wire [127:0] io_sram3_wmask;
  wire [127:0] io_sram3_wdata;
  wire [127:0] io_sram3_rdata;

  wire [  5:0] io_sram4_addr;
  wire         io_sram4_cen;
  wire         io_sram4_wen;
  wire [127:0] io_sram4_wmask;
  wire [127:0] io_sram4_wdata;
  wire [127:0] io_sram4_rdata;

  wire [  5:0] io_sram5_addr;
  wire         io_sram5_cen;
  wire         io_sram5_wen;
  wire [127:0] io_sram5_wmask;
  wire [127:0] io_sram5_wdata;
  wire [127:0] io_sram5_rdata;

  wire [  5:0] io_sram6_addr;
  wire         io_sram6_cen;
  wire         io_sram6_wen;
  wire [127:0] io_sram6_wmask;
  wire [127:0] io_sram6_wdata;
  wire [127:0] io_sram6_rdata;

  wire [  5:0] io_sram7_addr;
  wire         io_sram7_cen;
  wire         io_sram7_wen;
  wire [127:0] io_sram7_wmask;
  wire [127:0] io_sram7_wdata;
  wire [127:0] io_sram7_rdata;

  ysyx_041514_sram u_ysyx_041514_sram (
      .clk           (clock),
      .io_sram0_addr (io_sram0_addr),
      .io_sram0_cen  (io_sram0_cen),
      .io_sram0_wen  (io_sram0_wen),
      .io_sram0_wmask(io_sram0_wmask),
      .io_sram0_wdata(io_sram0_wdata),
      .io_sram0_rdata(io_sram0_rdata),
      .io_sram1_addr (io_sram1_addr),
      .io_sram1_cen  (io_sram1_cen),
      .io_sram1_wen  (io_sram1_wen),
      .io_sram1_wmask(io_sram1_wmask),
      .io_sram1_wdata(io_sram1_wdata),
      .io_sram1_rdata(io_sram1_rdata),
      .io_sram2_addr (io_sram2_addr),
      .io_sram2_cen  (io_sram2_cen),
      .io_sram2_wen  (io_sram2_wen),
      .io_sram2_wmask(io_sram2_wmask),
      .io_sram2_wdata(io_sram2_wdata),
      .io_sram2_rdata(io_sram2_rdata),
      .io_sram3_addr (io_sram3_addr),
      .io_sram3_cen  (io_sram3_cen),
      .io_sram3_wen  (io_sram3_wen),
      .io_sram3_wmask(io_sram3_wmask),
      .io_sram3_wdata(io_sram3_wdata),
      .io_sram3_rdata(io_sram3_rdata),
      .io_sram4_addr (io_sram4_addr),
      .io_sram4_cen  (io_sram4_cen),
      .io_sram4_wen  (io_sram4_wen),
      .io_sram4_wmask(io_sram4_wmask),
      .io_sram4_wdata(io_sram4_wdata),
      .io_sram4_rdata(io_sram4_rdata),
      .io_sram5_addr (io_sram5_addr),
      .io_sram5_cen  (io_sram5_cen),
      .io_sram5_wen  (io_sram5_wen),
      .io_sram5_wmask(io_sram5_wmask),
      .io_sram5_wdata(io_sram5_wdata),
      .io_sram5_rdata(io_sram5_rdata),
      .io_sram6_addr (io_sram6_addr),
      .io_sram6_cen  (io_sram6_cen),
      .io_sram6_wen  (io_sram6_wen),
      .io_sram6_wmask(io_sram6_wmask),
      .io_sram6_wdata(io_sram6_wdata),
      .io_sram6_rdata(io_sram6_rdata),
      .io_sram7_addr (io_sram7_addr),
      .io_sram7_cen  (io_sram7_cen),
      .io_sram7_wen  (io_sram7_wen),
      .io_sram7_wmask(io_sram7_wmask),
      .io_sram7_wdata(io_sram7_wdata),
      .io_sram7_rdata(io_sram7_rdata)
);
endmodule


`endif
