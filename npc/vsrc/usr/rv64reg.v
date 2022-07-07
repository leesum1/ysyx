`include "./../sysconfig.v"


module rv64reg (
    /* 读取数据 */
    input wire [`REG_ADDRWIDTH-1:0] rs1addr,
    input wire [`REG_ADDRWIDTH-1:0] rs2addr,
    output wire [`XLEN-1:0] rs1data,
    output wire [`XLEN-1:0] rs2data,
    /* 写入数据 */
    input wire [`REG_ADDRWIDTH-1:0] rdaddr,
    input wire [`XLEN-1:0] rddata
);
  reg [`XLEN-1:0] riscvreg[`REG_NUM-1:0];
  assign rs1data = riscvreg[rs1addr];
  assign rs2data = riscvreg[rs2addr];

  assign riscvreg[rdaddr] = rddata;
endmodule
