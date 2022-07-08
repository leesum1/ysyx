`include "./../sysconfig.v"

module rv64reg (
    input clk,
    /* 读取数据 */
    input wire [`REG_ADDRWIDTH-1:0] rs1addr,
    input wire [`REG_ADDRWIDTH-1:0] rs2addr,
    output wire [`XLEN-1:0] rs1data,
    output wire [`XLEN-1:0] rs2data,
    /* 写入数据 */
    input wire [`REG_ADDRWIDTH-1:0] waddr,
    input wire [`XLEN-1:0] wdata,
    input wire wen
);

  reg [`XLEN-1:0] rf[`REG_NUM-1:0];

  /* 写入数据 */
  wire _isX0 = (waddr == `REG_ADDRWIDTH'b0);
  wire [`XLEN-1:0] _wdata = (_isX0) ? `XLEN'b0 : wdata;  // x0 恒为0
  wire _wen = wen;
  always @(posedge clk) begin
    if (_wen) rf[waddr] <= _wdata;
  end

  /* 读取数据 */
  assign rs1data = rf[rs1addr];
  assign rs2data = rf[rs2addr];
endmodule


