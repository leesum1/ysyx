`include "./../sysconfig.v"
/* 与 mem 位于同一阶段 */
module clint (
    // input wire clk,
    input wire rst,

    input [`XLEN-1:0] pc_i,
    input [`INST_LEN-1:0] inst_data_i,
    /* TARP 总线 */
    input wire [`TRAP_BUS] trap_bus_i,

    /* ----- stall request from other modules 各个阶段请求流水线暂停请求 --------*/
    input wire stallreq_from_if_i,
    input wire stallreq_from_id_i,
    input wire stallreq_from_ex_i,
    input wire stallreq_from_mem_i,


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
    output wire clint_pc_valid_o,

    /* ---signals to other stages of the pipeline  ----*/
    output reg[5:0]              stall_o,   // stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB， one bit for one stage respectively
    output wire flush_o  // flush the whole pipleline, exception or interrupt happens
);

  /* --------------------- handle the stall request -------------------*/
  assign flush_o = _trap_valid;


  always @(*) begin
    if (rst) begin
      stall_o = 6'b000000;
      // stall request from lsu: need to stop the ifu(0), IF_ID(1), ID_EXE(2), EXE_MEM(3), MEM_WB(4)
    end else if (stallreq_from_mem_i == `TRUE) begin
      stall_o = 6'b011111;
      // stall request from exu: stop the PC,IF_ID, ID_EXE, EXE_MEM
    end else if (stallreq_from_ex_i == `TRUE) begin
      stall_o = 6'b001111;
      // stall request from id: stop PC,IF_ID, ID_EXE
    end else if (stallreq_from_id_i == `TRUE) begin
      stall_o = 6'b000111;
      // stall request from if: stop the PC,IF_ID, ID_EXE
    end else if (stallreq_from_if_i == `TRUE) begin
      stall_o = 6'b000111;
    end else begin
      stall_o = 6'b000000;
    end  // if
  end  // always




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
