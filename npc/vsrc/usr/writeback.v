`include "sysconfig.v"
module writeback (

    input                 clk,
    input                 rst,
    /* from MEM/WB */
    input [    `XLEN_BUS] pc_wb_i,
    input [`INST_LEN-1:0] inst_data_wb_i
    // input  [             `XLEN_BUS] mem_data_i,
    // input  [    `REG_ADDRWIDTH-1:0] rd_idx_i,
    // input  [`CSR_REG_ADDRWIDTH-1:0] csr_addr_i,
    // input  [             `XLEN_BUS] exc_csr_data_i,
    // input                           exc_csr_valid_i,
    // /* TO GPR,CSR REGFILE */
    // output [             `XLEN_BUS] mem_data_o,
    // output [    `REG_ADDRWIDTH-1:0] rd_idx_o,
    // output [`CSR_REG_ADDRWIDTH-1:0] csr_addr_o,
    // output [             `XLEN_BUS] exc_csr_data_o,
    // output                          exc_csr_valid_o

);
  // assign mem_data_o = mem_data_i;
  // assign rd_idx_o = rd_idx_i;
  // assign csr_addr_o = csr_addr_i;
  // assign exc_csr_data_o = exc_csr_data_i;
  // assign exc_csr_valid_o = exc_csr_valid_i;

  wire _commit_valid = (pc_wb_i != `XLEN'b0) && (inst_data_wb_i != `INST_NOP);

  import "DPI-C" function void inst_commit(
    input longint pc,
    input bit commit_valid
  );

  /***************difftest 使用****************/
  always @(posedge clk) begin
    inst_commit(pc_wb_i, _commit_valid);
  end
endmodule
