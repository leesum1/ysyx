`include "./../sysconfig.v"
module execute (
    input [         `XLEN-1:0] pc,
    input [`REG_ADDRWIDTH-1:0] rd_idx,
    input [         `XLEN-1:0] rs1_data,
    input [         `XLEN-1:0] rs2_data,
    input [      `IMM_LEN-1:0] imm_data,
    /* CSR 译码结果 */
    input [         `XLEN-1:0] csr_data,
    input [          `IMM_LEN-1:0] imm_CSR,
    input  isNeedimmCSR,


    input  [`ALUOP_LEN-1:0] alu_op,  // alu 操作码
    input  [`MEMOP_LEN-1:0] mem_op,  // 访存操作码
    input  [`EXCOP_LEN-1:0] exc_op,  // exc 操作码
    input [`CSROP_LEN-1:0] csr_op,   // exc_csr 操作码

    output [     `XLEN-1:0] exc_alu_out,
    output [     `XLEN-1:0] exc_csr_out,
    output exc_csr_valid
);


  wire _excop_auipc = (exc_op == `EXCOP_AUIPC);
  wire _excop_lui = (exc_op == `EXCOP_LUI);
  wire _excop_jal = (exc_op == `EXCOP_JAL);
  wire _excop_jalr = (exc_op == `EXCOP_JALR);
  wire _excop_load = (exc_op == `EXCOP_LOAD);
  wire _excop_store = (exc_op == `EXCOP_STORE);
  wire _excop_branch = (exc_op == `EXCOP_BRANCH);
  wire _excop_opimm = (exc_op == `EXCOP_OPIMM);
  wire _excop_opimm32 = (exc_op == `EXCOP_OPIMM32);
  wire _excop_op = (exc_op == `EXCOP_OP);
  wire _excop_op32 = (exc_op == `EXCOP_OP32);
  wire _excop_csr = (exc_op == `EXCOP_CSR);
  wire _excop_ebreak = (exc_op == `EXCOP_EBREAK);
  wire _excop_none = (exc_op == `EXCOP_NONE);

  /* ALU 两端操作数选择 */
  wire _rs1_rs2 = _excop_op32 | _excop_op | _excop_branch;
  wire _rs1_imm = _excop_opimm | _excop_opimm32 | _excop_load | _excop_store;
  wire _pc_4 = _excop_jal | _excop_jalr;
  wire _pc_imm12 = _excop_auipc;
  wire _none_imm12 = _excop_lui;
  wire _none_csr = _excop_csr;  //保存原来的 csr

  /* jal jalr lui auipc ecall ebreak 需要单独处理 */
  /* 拼接代替左移 */
  // wire [`IMM_LEN-1:0] _imm_aui_auipc = imm_data << 12;
  wire [`IMM_LEN-1:0] _imm_aui_auipc = {imm_data[`IMM_LEN-1:12], 12'b0};
  // ALU 第一个操作数
  wire [         `XLEN-1:0] _alu_in1 = ({`XLEN{_rs1_rs2 | _rs1_imm}}&rs1_data) |
                                       ({`XLEN{_pc_4 | _pc_imm12}}&pc) |
                                       ({`XLEN{_none_imm12|_none_csr}}&`XLEN'b0);
  // ALU 第二个操作数
  wire [         `XLEN-1:0] _alu_in2 = ({`XLEN{_rs1_rs2}}&rs2_data) |
                                       ({`XLEN{_rs1_imm}}&imm_data) |
                                       ({`XLEN{_none_csr}}&csr_data) |
                                       ({`XLEN{_pc_4}}&`XLEN'd4)   |
                                       ({`XLEN{_pc_imm12|_none_imm12}}&_imm_aui_auipc);

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
  /* alu计算结果需要符号扩展 */
  wire _alu_sext = _excop_opimm32 | _excop_op32;
  wire [`XLEN-1:0] _alu_sext_out = {{32{_alu_out[31]}}, _alu_out[31:0]};
  assign exc_alu_out = (_alu_sext) ? _alu_sext_out : _alu_out;

  //assign exc_out = _alu_out;

/************* CSR 执行操作 **************************/

wire [`XLEN-1:0] _csr_exe_result;
wire _csr_exe_valid;
execute_csr u_execute_csr (
    .imm_CSR_i         (imm_CSR),
    .isNeedimmCSR_i    (isNeedimmCSR),  // 是否是立即数指令
    .rs1_data_i        (rs1_data),      // rs1 data
    .csr_data_i        (csr_data),      // 读取的 CSR 数据
    .csr_op_i          (csr_op),        // csr 操作码
    .csr_exe_result    (_csr_exe_result),
    .csr_exe_valid     (_csr_exe_valid)
);


assign exc_csr_out = _csr_exe_result;
assign exc_csr_valid = _csr_exe_valid;

  /*************ebreak仿真使用**************************/
  always @(*) begin
    if (_excop_ebreak) begin
      $finish;
    end
  end
endmodule
