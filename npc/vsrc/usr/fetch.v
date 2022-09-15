
`include "sysconfig.v"
/**
* 取指模块
* 组合逻辑电路,仅仅起到传递作用,PC寄存器位于 IF/ID 
*/
module fetch (
    //指令地址
    input rst,
    input [`XLEN_BUS] inst_addr_i,  // from pc_reg
    /* ram 接口 */
    // output [`NPC_ADDR_BUS] if_read_addr_o,  // 地址
    // output if_raddr_valid_o,  // 地址是否准备好
    // output [7:0] if_rmask_o,  // 数据掩码,读取多少位
    input if_rdata_valid_i,  // 读数据是否准备好
    input [`XLEN_BUS] if_rdata_i,

    /* stall req */
    output wire ram_stall_valid_if_o,  // if 阶段访存暂停
    /* to if/id */
    output [`XLEN_BUS] inst_addr_o,
    output [`INST_LEN-1:0] inst_data_o,
    output [`TRAP_BUS] trap_bus_o
);


  assign inst_addr_o = inst_addr_i;


  // 选择读取数据
  wire [`NPC_ADDR_BUS] _inst_data = (if_rdata_valid_i) ? if_rdata_i[31:0] : `INST_NOP;


  // 若 icache 数据没有准备好,发出 stall 请求,暂停流水线
  wire _ram_stall = (!if_rdata_valid_i);

  assign ram_stall_valid_if_o = _ram_stall;
  assign inst_data_o = _inst_data;



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
