`include "./../sysconfig.v"

module rv64reg (
    input clk,
    /* 读取数据 */
    input wire [`REG_ADDRWIDTH-1:0] rs1_idx,
    input wire [`REG_ADDRWIDTH-1:0] rs2_idx,
    output wire [`XLEN-1:0] rs1_data,
    output wire [`XLEN-1:0] rs2_data,
    /* 写入数据 */
    input wire [`REG_ADDRWIDTH-1:0] write_idx,
    input wire [`XLEN-1:0] write_data,
    input wire wen
);

  /* 寄存器组 */
  reg [`XLEN-1:0] rf[`REG_NUM-1:0];

  /* 写入数据,若目的寄存器为 x0,写入数据永远为0 */
  wire _isX0 = (write_idx == `REG_ADDRWIDTH'b0);
  wire [`XLEN-1:0] _write_data = (_isX0) ? `XLEN'b0 : write_data;  // x0 恒为0
  /* 写入使能 */
  wire _wen = wen;
  always @(posedge clk) begin
    if (_wen) rf[write_idx] <= _write_data;
  end

  /* 读取数据 */
  assign rs1_data = rf[rs1_idx];
  assign rs2_data = rf[rs2_idx];


  /************仿真使用：传递二维数组指针************/
  import "DPI-C" function void set_gpr_ptr(input logic [63:0] a[]);
  initial set_gpr_ptr(rf);  // rf为通用寄存器的二维数组变量
endmodule


