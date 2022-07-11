
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



  wire [`XLEN-1:0] mem_data;
  import "DPI-C" function void pmem_read(
    input  longint raddr,
    output longint rdata
  );

  import "DPI-C" function void get_pc(
    input  longint pc,
  );

  always @(*) begin
    pmem_read(inst_addr, mem_data);
    get_pc(inst_addr);
  end

  assign inst_data = mem_data[31:0];

endmodule
