`include "sysconfig.v"

// 同步 ram
module ram_top (
    input clk,
    input rst,
    input [`NPC_ADDR_BUS] raddr_i,
    input [7:0] rmask_i,
    input read_valid_i,
    output [`XLEN_BUS] ram_read_data_o,
    output ram_read_valid_o,

    input [`NPC_ADDR_BUS] waddr_i,
    input [7:0] wmask_i,
    input [`XLEN_BUS] wdata_i,
    input write_valid_i,
    output ram_write_valid_o
);


  // /*  mem_arb<--->mem  */
  // output [`NPC_ADDR_BUS] arb_read_addr_o,
  // output [7:0] arb_rmask_o,
  // output arb_valid_o,
  // input [`XLEN_BUS] arb_rdata_i,
  // input arb_rdata_valid_i


  // /***************************内存读写**************************/
  // import "DPI-C" function void pmem_read(
  //   input int raddr,
  //   output longint rdata,
  //   input byte rmask
  // );
  // import "DPI-C" function void pmem_write(
  //   input int waddr,
  //   input longint wdata,
  //   input byte wmask
  // );


  // reg _ram_read_valid;
  // reg [`XLEN_BUS] _ram_read_data;

  // assign ram_read_valid_o = _ram_read_valid;
  // assign ram_read_data_o  = _ram_read_data;

  // always @(posedge clk) begin
  //   if (read_valid_i) begin
  //     pmem_read(raddr_i, _ram_read_data, rmask_i);
  //     _ram_read_valid <= `TRUE;
  //   end else begin
  //     _ram_read_valid <= `FALSE;
  //     //_ram_read_data <= `XLEN'b0;
  //   end
  // end

  // reg _ram_write_valid;
  // reg [`XLEN_BUS] _ram_write_data = wdata_i;

  // assign ram_write_valid_o = _ram_write_valid;

  // always @(posedge clk) begin
  //   if (write_valid_i) begin
  //     pmem_write(waddr_i, _ram_write_data, wmask_i);
  //     _ram_write_valid <= `TRUE;
  //   end else begin
  //     _ram_write_valid <= `FALSE;
  //     //_ram_read_data <= `XLEN'b0;
  //   end
  // end


endmodule
