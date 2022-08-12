
`include "./../sysconfig.v"

/**
* 取指模块
*/
module fetch (
    input clk,
    //指令地址
    input wire [`XLEN-1:0] inst_addr,
    //指令内容
    output wire [`INST_LEN-1:0] inst_data
);

  wire [`XLEN-1:0] _mem_data;
  import "DPI-C" function void pmem_read(
    input longint raddr,
    output longint rdata,
    input byte rmask
  );

  import "DPI-C" function void get_pc(input longint pc);
  /*  仿真使用,传递当前 pc 给仿真环境,根据pc 取指令 */
  wire [7:0] _rmask = 8'b1111_1111;
  always @(posedge clk) begin
    pmem_read(inst_addr, _mem_data, _rmask);
    get_pc(inst_addr);
  end

  assign inst_data = _mem_data[31:0];

endmodule
