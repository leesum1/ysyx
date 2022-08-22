`include "sysconfig.v"

module rv64_gpr_regfile (
    input clk,
    input rst,
    /* 读取数据 */
    input wire [`REG_ADDRWIDTH-1:0] rs1_idx_i,
    input wire [`REG_ADDRWIDTH-1:0] rs2_idx_i,
    output wire [`XLEN-1:0] rs1_data_o,
    output wire [`XLEN-1:0] rs2_data_o,
    /* 写入数据 */
    input wire [`REG_ADDRWIDTH-1:0] write_idx_i,
    input wire [`XLEN-1:0] write_data_i,
    input wire write_data_valid_i
);

  /* 寄存器组 */
  reg [`XLEN-1:0] rf[`REG_NUM-1:0];

  /* 写入数据,若目的寄存器为 x0,写入数据永远为0 */
  wire _isX0 = (write_idx_i == `REG_ADDRWIDTH'b0);
  wire [`XLEN-1:0] _write_data = (_isX0) ? `XLEN'b0 : write_data_i;  // x0 恒为0
  /* 写入使能 */
  wire _wen = write_data_valid_i;
  always @(posedge clk) begin
    if (_wen) rf[write_idx_i] <= _write_data;
  end

  /* 读取数据 */
  wire _rs1_bypass_valid = rs1_idx_i == write_idx_i;
  wire _rs2_bypass_valid = rs2_idx_i == write_idx_i;

  assign rs1_data_o = _rs1_bypass_valid ? _write_data : rf[rs1_idx_i];
  assign rs2_data_o = _rs2_bypass_valid ? _write_data : rf[rs2_idx_i];


  /************仿真使用：传递二维数组指针************/
  import "DPI-C" function void set_gpr_ptr(input logic [63:0] a[]);
  initial set_gpr_ptr(rf);  // rf为通用寄存器的二维数组变量
endmodule


