
`include "./../sysconfig.v"

/**
* 取指模块
*/
module fetch (
    //指令地址
    input wire [`XLEN-1:0] inst_addr,
    //指令内容
    output wire [`INST_LEN-1:0] inst_data
);

  wire [`XLEN-1:0] _mem_data;
  import "DPI-C" function void pmem_read(
    input  longint raddr,
    output longint rdata
  );

  import "DPI-C" function void get_pc(
    input  longint pc,
  );
/*  仿真使用,传递当前 pc 给仿真环境,根据pc 取指令 */
  always @(*) begin
    pmem_read(inst_addr, _mem_data);
    get_pc(inst_addr);
  end

  assign inst_data = _mem_data[31:0];

endmodule
