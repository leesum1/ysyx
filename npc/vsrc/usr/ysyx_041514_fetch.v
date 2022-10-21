
`include "sysconfig.v"
/**
* 取指模块
* 组合逻辑电路,仅仅起到传递作用,PC寄存器位于 IF/ID 
*/
module ysyx_041514_fetch (
    //指令地址
    // input rst,
    input [`ysyx_041514_XLEN_BUS] inst_addr_i,  // from pc_reg
    input if_rdata_valid_i,  // 读数据是否准备好
    input [`ysyx_041514_XLEN_BUS] if_rdata_i,

    output [`ysyx_041514_XLEN_BUS] jal_pc_o,
    output jal_pc_valid_o,

    /* stall req */
    output ram_stall_valid_if_o,  // if 阶段访存暂停
    /* to if/id */
    output [`ysyx_041514_XLEN_BUS] inst_addr_o,
    output [`ysyx_041514_INST_LEN-1:0] inst_data_o,
    output [`ysyx_041514_TRAP_BUS] trap_bus_o
);


  assign inst_addr_o = inst_addr_i;

  // 判断是否是 fencei 指令
  // wire inst_fencei = (if_rdata_i[6:0] == 7'b0001111) & (if_rdata_i[14:12] == 3'b001);
  // assign fencei_valid_o = inst_fencei & (~fencei_ready_i);

  // 选择读取数据
  wire [`ysyx_041514_NPC_ADDR_BUS] _inst_data = (if_rdata_valid_i) ? if_rdata_i[31:0] : `ysyx_041514_INST_NOP;


  // 若 icache 数据没有准备好,发出 stall 请求,暂停流水线
  wire _ram_stall = (!if_rdata_valid_i);

  assign ram_stall_valid_if_o = _ram_stall;
  assign inst_data_o = _inst_data;

  /* jal 指令，可以直接在 if 阶段得到跳转地址 */
  wire [6:0] _opcode = _inst_data[6:0];
  wire _opcode_6_5_11 = (_opcode[6:5] == 2'b11);
  wire _opcode_4_2_011 = (_opcode[4:2] == 3'b011);
  wire _opcode_1_0_11 = (_opcode[1:0] == 2'b11);
  wire [`ysyx_041514_IMM_LEN-1:0] _immJ = {
    {12 + 32{_inst_data[31]}},
    _inst_data[19:12],
    _inst_data[20],
    _inst_data[30:25],
    _inst_data[24:21],
    1'b0
  };
  wire _inst_jal = _opcode_6_5_11 & _opcode_4_2_011 & _opcode_1_0_11;
  wire [`ysyx_041514_XLEN_BUS] jal_pc = inst_addr_i + _immJ;  // pc+imm
  wire jal_pc_valid = _inst_jal;
  assign jal_pc_o = jal_pc;
  assign jal_pc_valid_o = jal_pc_valid;


  /***********************TRAP**********************/
  wire _Instruction_address_misaligned = `ysyx_041514_FALSE;
  wire _Instruction_access_fault = `ysyx_041514_FALSE;
  wire _Instruction_page_fault = `ysyx_041514_FALSE;

  reg [`ysyx_041514_TRAP_BUS] _if_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `ysyx_041514_TRAP_LEN; i = i + 1) begin
      if (i == `ysyx_041514_TRAP_INST_ADDR_MISALIGNED) begin
        _if_trap_bus[i] = _Instruction_address_misaligned;
      end else if (i == `ysyx_041514_TRAP_INST_ACCESS_FAULT) begin
        _if_trap_bus[i] = _Instruction_access_fault;
      end else if (i == `ysyx_041514_TRAP_INST_PAGE_FAULT) begin
        _if_trap_bus[i] = _Instruction_page_fault;
      end else begin
        _if_trap_bus[i] = `ysyx_041514_FALSE;
      end
    end
  end
  assign trap_bus_o = _if_trap_bus;


endmodule
