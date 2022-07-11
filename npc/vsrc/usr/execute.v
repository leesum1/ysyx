`include "./../sysconfig.v"
module execute (
    input  [         `XLEN-1:0] pc,
    input  [`REG_ADDRWIDTH-1:0] rd_idx,
    input  [         `XLEN-1:0] rs1_data,
    input  [         `XLEN-1:0] rs2_data,
    input  [      `IMM_LEN-1:0] imm_data,
    input                       isNeed_rs1,
    input                       isNeed_rs2,
    input                       isNeed_rd,
    input                       isNeed_imm,
    input  [    `ALUOP_LEN-1:0] alu_op,      // alu 操作码
    input  [    `MEMOP_LEN-1:0] mem_op,      // 访存操作码
    input  [    `EXCOP_LEN-1:0] exc_op,      // exc 操作码
    output [         `XLEN-1:0] exc_out
);


  /* 拼接代替左移 */
  // wire [`IMM_LEN-1:0] _imm_aui_auipc = imm_data << 12;
  wire [`IMM_LEN-1:0] _imm_aui_auipc = {imm_data[`IMM_LEN-1:12], 12'b0};

  wire [         `XLEN-1:0] _alu_in1 = (exc_op==`EXCOP_REG_REG)?rs1_data:
                                       (exc_op==`EXCOP_REG_IMM)?rs1_data:
                                       (exc_op==`EXCOP_AUIPC)?pc:
                                       (exc_op==`EXCOP_JAL)?pc:
                                       (exc_op==`EXCOP_JALR)?pc:
                                       (exc_op==`EXCOP_LUI)?`XLEN'b0:
                                        `XLEN'b0;

  wire [         `XLEN-1:0] _alu_in2 = (exc_op==`EXCOP_REG_REG)?rs2_data:
                                       (exc_op==`EXCOP_REG_IMM)?imm_data:
                                       (exc_op==`EXCOP_AUIPC)?_imm_aui_auipc:
                                       (exc_op==`EXCOP_JAL)?`XLEN'd4:
                                       (exc_op==`EXCOP_JALR)?`XLEN'd4:
                                       (exc_op==`EXCOP_LUI)?_imm_aui_auipc:
                                       `XLEN'b0;
  wire [`XLEN-1:0] _alu_out;
  wire _compare_out;
  alu u_alu (
      /* ALU 端口 */
      .alu_a_i(_alu_in1),
      .alu_b_i(_alu_in2),
      .alu_out(_alu_out),
      .alu_op_i(alu_op),
      .compare_out(_compare_out)
  );

  assign exc_out = _alu_out;



  /*************ebreak仿真使用**************************/
  wire _excop_ebreak = (exc_op == `EXCOP_EBREAK);
  always @(*) begin
    if (_excop_ebreak) begin
      $finish;
    end
  end
endmodule
