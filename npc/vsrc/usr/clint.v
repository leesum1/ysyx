`include "./../sysconfig.v"
/* 与 mem 位于同一阶段 */
module clint (
    // input wire clk,
    // input wire rst,

    input [`XLEN-1:0] pc_i,
    input [`INST_LEN-1:0] inst_data_i,
    /* TARP 总线 */
    input wire [`TRAP_BUS] trap_bus_i,

    /* trap 所需寄存器，来自于 csr (读)*/
    input wire [`XLEN-1:0] csr_mstatus_readdata_i,
    input wire [`XLEN-1:0] csr_mepc_readdata_i,
    input wire [`XLEN-1:0] csr_mcause_readdata_i,
    input wire [`XLEN-1:0] csr_mtval_readdata_i,
    input wire [`XLEN-1:0] csr_mtvec_readdata_i,
    /* trap 所需寄存器，来自于 csr (写)*/
    output wire [`XLEN-1:0] csr_mstatus_writedata_o,
    output wire [`XLEN-1:0] csr_mepc_writedata_o,
    output wire [`XLEN-1:0] csr_mcause_writedata_o,
    output wire [`XLEN-1:0] csr_mtval_writedata_o,
    output wire [`XLEN-1:0] csr_mtvec_writedata_o,
    output wire csr_mstatus_write_valid_o,
    output wire csr_mepc_write_valid_o,
    output wire csr_mcause_write_valid_o,
    output wire csr_mtval_write_valid_o,
    output wire csr_mtvec_write_valid_o,

    /* 输出至取指阶段 */
    output wire [`XLEN-1:0] clint_pc_o,
    output wire clint_pc_valid_o
);
  /* type of trap */
  wire _trap_ecall = trap_bus_i[`TRAP_ECALL];
  wire _trap_ebreak = trap_bus_i[`TRAP_EBREAK];
  wire _trap_mret = trap_bus_i[`TRAP_MRET];
  wire _trap_valid = (_trap_ecall | _trap_ebreak | _trap_mret);

  /* set the csr register and new pc if traps happened */

  // step 1: save current pc 
  assign csr_mepc_writedata_o   = pc_i;
  assign csr_mepc_write_valid_o = _trap_ecall;
  // step 2: set the trap pc
  wire [`XLEN-1:0]_trap_pc_o = csr_mtvec_readdata_i;  // TODO:now only suppot direct mode,need to add vector mode
  wire _trap_pc_valid_o = _trap_ecall;
  // step 3: save trap cuase to mcause
  assign csr_mcause_writedata_o = 11; //TODO:now,only support ecall from mathine mode(11),need to add more
  assign csr_mcause_write_valid_o = _trap_ecall;
  // step 4: save inst_data to mtval
  assign csr_mtval_writedata_o = {32'b0, inst_data_i};
  assign csr_mtval_write_valid_o = _trap_ecall;

  /* restore pc and csr register if mret happened*/
  wire [`XLEN-1:0] _mret_pc_o = csr_mepc_readdata_i;
  wire _mret_pc_valid_o = _trap_mret;



  /* pc mux */
  assign clint_pc_o = ({`XLEN{_mret_pc_valid_o}}&_mret_pc_o)|
                        ({`XLEN{_trap_pc_valid_o}}&_trap_pc_o);
  assign clint_pc_valid_o = _trap_valid;

endmodule
