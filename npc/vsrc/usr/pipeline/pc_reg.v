`include "sysconfig.v"
// /** 纯组合逻辑电路
//  * 1.branch_pc：来自exc阶段
//  * 2.csr_pc：来自mem阶段
//  * 3.pc_next：输出给if阶段
// ×/

module pc_reg (
    input clk,
    input rst,
    input [5:0] stall_valid_i,
    input [5:0] flush_valid_i,

    input [`XLEN_BUS] branch_pc_i,        // branch pc,来自 exc
    input             branch_pc_valid_i,
    input [`XLEN_BUS] clint_pc_i,         //trap pc,来自mem
    input             clint_pc_valid_i,   //trap pc valide,来自mem

    input              if_rdata_valid_i,
    output             read_req_o,
    output [`XLEN_BUS] pc_next_o,         //输出 next_pc
    output [`XLEN_BUS] pc_o               //输出pc
);

  // trap 优先级高
  wire [`XLEN_BUS] _pc_next =  clint_pc_valid_i ? clint_pc_i : 
                            branch_pc_valid_i?branch_pc_i:_pc_current+4;

  reg [`XLEN_BUS] _pc_current;

  assign pc_o = _pc_current;
  assign pc_next_o = stall_valid_i[`CTRLBUS_PC] ? _pc_current : _pc_next_d;
  //assign pc_next_o = _pc_next_d;




  //   wire _read_req_stall = ((addr_ok_i) ? `FALSE : `TRUE);
  reg _read_req = (~rst);  //& (~if_rdata_valid_i);



  wire _pc_reg_wen = (~stall_valid_i[`CTRLBUS_PC]) & (~rst);

  wire _flush_valid = flush_valid_i[`CTRLBUS_PC];
  wire [`XLEN_BUS] _pc_next_d = (_flush_valid) ? `PC_RESET_ADDR : _pc_next;

  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`PC_RESET_ADDR)
  ) u_pc_dreg (
      .clk (clk),
      .rst (rst),
      .din (_pc_next_d),
      .dout(_pc_current),
      .wen (_pc_reg_wen)
  );



  assign read_req_o = _read_req;
endmodule
