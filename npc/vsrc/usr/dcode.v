`include "./../sysconfig.v"


module dcode (
    input wire [`INST_LEN-1:0] inst_data
);

  /* 指令分解 */
  wire [`REG_ADDRWIDTH-1:0] rs1addr, rs2addr, rdaddr;
  wire [2:0] func3;
  wire [6:0] func7, opcode;
  assign opcode  = inst_data[6:0];
  assign rdaddr  = inst_data[11:7];
  assign func3   = inst_data[14:12];
  assign rs1addr = inst_data[19:15];
  assign rs2addr = inst_data[24:20];
  assign func7   = inst_data[31:25];


endmodule
