`include "sysconfig.v"
module writeback (
    /* from MEM/WB */
    input  [             `XLEN_BUS] mem_data_i,
    input  [    `REG_ADDRWIDTH-1:0] rd_idx_i,
    input  [`CSR_REG_ADDRWIDTH-1:0] csr_addr_i,
    input  [             `XLEN_BUS] exc_csr_data_i,
    input                           exc_csr_valid_i,
    /* TO GPR,CSR REGFILE */
    output [             `XLEN_BUS] mem_data_o,
    output [    `REG_ADDRWIDTH-1:0] rd_idx_o,
    output [`CSR_REG_ADDRWIDTH-1:0] csr_addr_o,
    output [             `XLEN_BUS] exc_csr_data_o,
    output                          exc_csr_valid_o

);
  assign mem_data_o = mem_data_i;
  assign rd_idx_o = rd_idx_i;
  assign csr_addr_o = csr_addr_i;
  assign exc_csr_data_o = exc_csr_data_i;
  assign exc_csr_valid_o = exc_csr_valid_i;

endmodule
