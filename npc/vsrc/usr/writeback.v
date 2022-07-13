`include "./../sysconfig.v"
module writeback (
    input  [`XLEN-1:0] exc_data_in,
    input  [`XLEN-1:0] mem_data_in,
    input              isloadEnable,
    output [`XLEN-1:0] wb_data

);

  assign wb_data = (isloadEnable) ? mem_data_in : exc_data_in;
endmodule
