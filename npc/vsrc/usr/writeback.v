`include "./../sysconfig.v"
module writeback (
    input  [`XLEN-1:0] exc_data_in,
    input  [`XLEN-1:0] mem_data_in,
    input              isloadEnable,
    output [`XLEN-1:0] wb_data

);
  /* 写回有两个选择,
     1:普通指令,执行阶段得到结果
     2:访存执行,访存阶段得到结果
  */
  assign wb_data = (isloadEnable) ? mem_data_in : exc_data_in;
endmodule
