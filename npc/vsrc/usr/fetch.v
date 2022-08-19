
`include "./../sysconfig.v"

/**
* 取指模块
* 组合逻辑电路,仅仅起到传递作用,PC寄存器位于 IF/ID 
*/
module fetch (
    //指令地址
    input [`XLEN_BUS] inst_addr_i,
    //指令内容
    input [`XLEN_BUS] inst_data_i,

    output [`XLEN_BUS] inst_addr_o,
    output [`XLEN_BUS] inst_data_o,
    output [`TRAP_BUS] trap_bus_o
);


  assign inst_addr_o = inst_addr_i;
  assign inst_data_o = inst_data_i;

  //TODO:add more exceptons
  assign trap_bus_o  = 0;
  // wire [`XLEN-1:0] _mem_data;
  // import "DPI-C" function void pmem_read(
  //   input longint raddr,
  //   output longint rdata,
  //   input byte rmask
  // );

  // import "DPI-C" function void get_pc(input longint pc);
  // /*  仿真使用,传递当前 pc 给仿真环境,根据pc 取指令 */
  // wire [7:0] _rmask = 8'b1111_1111;
  // always @(*) begin
  //   pmem_read(inst_addr_i, _mem_data, _rmask);
  //   get_pc(inst_addr_i);
  // end

  // assign inst_data_o = _mem_data[31:0];

endmodule
