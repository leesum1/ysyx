
`include "sysconfig.v"
/**
* 取指模块
* 组合逻辑电路,仅仅起到传递作用,PC寄存器位于 IF/ID 
*/
module fetch (
    //指令地址
    input rst,
    input [`XLEN_BUS] inst_addr_i,  // from pc_reg
    // //指令内容
    // input [`INST_LEN-1:0] inst_data_i,
    /* to if/id */
    output [`XLEN_BUS] inst_addr_o,
    output [`INST_LEN-1:0] inst_data_o,
    output [`TRAP_BUS] trap_bus_o
);


  assign inst_addr_o = inst_addr_i;

  reg [`XLEN-1:0] _mem_data;
  import "DPI-C" function void pmem_inst_read(
    input longint raddr,
    output longint rdata,
    input byte rmask
  );
  /*  仿真使用,传递当前 pc 给仿真环境,根据pc 取指令 */
  wire [7:0] _rmask = 8'b1111_1111;
  always @(*) begin
    if (rst) begin
      pmem_inst_read(`PC_RESET_ADDR, _mem_data, _rmask);
    end else begin
      pmem_inst_read(inst_addr_i, _mem_data, _rmask);
    end
  end

  assign inst_data_o = _mem_data[31:0];

  /***********************TRAP**********************/
  wire _Instruction_address_misaligned = `FALSE;
  wire _Instruction_access_fault = `FALSE;
  wire _Instruction_page_fault = `FALSE;

  reg [`TRAP_BUS] _if_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `TRAP_LEN; i = i + 1) begin
      if (i == `TRAP_INST_ADDR_MISALIGNED) begin
        _if_trap_bus[i] = _Instruction_address_misaligned;
      end else if (i == `TRAP_INST_ACCESS_FAULT) begin
        _if_trap_bus[i] = _Instruction_access_fault;
      end else if (i == `TRAP_INST_PAGE_FAULT) begin
        _if_trap_bus[i] = _Instruction_page_fault;
      end else begin
        _if_trap_bus[i] = `FALSE;
      end
    end
  end
  assign trap_bus_o = _if_trap_bus;


endmodule
