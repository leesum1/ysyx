`include "sysconfig.v"
module execute_top (
    /******************************* from id/ex *************************/
    // pc
    input       [             `XLEN_BUS] pc_i,
    input       [         `INST_LEN-1:0] inst_data_i,
    // gpr 译码结果
    input       [    `REG_ADDRWIDTH-1:0] rd_idx_i,
    input       [             `XLEN_BUS] rs1_data_i,
    input       [             `XLEN_BUS] rs2_data_i,
    input       [          `IMM_LEN-1:0] imm_data_i,
    // CSR 译码结果 
    input       [`CSR_REG_ADDRWIDTH-1:0] csr_readaddr_i,
    input       [             `XLEN_BUS] csr_data_i,
    input       [          `IMM_LEN-1:0] csr_imm_i,
    input                                csr_imm_valid_i,
    // 指令微码
    input       [        `ALUOP_LEN-1:0] alu_op_i,         // alu 操作码
    input       [        `MEMOP_LEN-1:0] mem_op_i,         // 访存操作码
    input       [        `EXCOP_LEN-1:0] exc_op_i,         // exc 操作码
    input       [        `CSROP_LEN-1:0] csr_op_i,         // exc_csr 操作码
    input       [         `PCOP_LEN-1:0] pc_op_i,
    /* TARP 总线 */
    input  wire [             `TRAP_BUS] trap_bus_i,
    /********************** to ex/mem **************************/
    // pc
    output      [             `XLEN_BUS] pc_o,
    output      [         `INST_LEN-1:0] inst_data_o,
    // gpr 译码结果
    output      [    `REG_ADDRWIDTH-1:0] rd_idx_o,
    output      [             `XLEN_BUS] rs1_data_o,
    output      [             `XLEN_BUS] rs2_data_o,
    output      [          `IMM_LEN-1:0] imm_data_o,
    // CSR 译码结果 
    output      [             `XLEN_BUS] csr_data_o,
    output      [          `IMM_LEN-1:0] csr_imm_o,
    output                               csr_imm_valid_o,
    output      [`CSR_REG_ADDRWIDTH-1:0] exc_csr_addr_o,
    output      [        `MEMOP_LEN-1:0] mem_op_o,         // 访存操作码
    output      [         `PCOP_LEN-1:0] pc_op_o,

    output [     `XLEN_BUS] exc_alu_data_o,   // 同时送给 ID 和 EX/MEM
    output [     `XLEN_BUS] exc_csr_data_o,
    output                  exc_csr_valid_o,
    /************************to id *************************************/
    output [`EXCOP_LEN-1:0] exc_op_o,         // exc 操作码

    /************************to pc_reg ******************************************/
    output [`XLEN_BUS] branch_pc_o,
    output branch_pc_valid_o,

    // 请求暂停流水线
    output jump_hazard_valid_o,

    /* TARP 总线 */
    output wire [`TRAP_BUS] trap_bus_o
);
  assign pc_o = pc_i;
  assign inst_data_o = inst_data_i;
  assign exc_op_o = exc_op_i;
  assign mem_op_o = mem_op_i;
  assign pc_op_o = pc_op_i;
  assign rs1_data_o = rs1_data_i;
  assign rs2_data_o = rs2_data_i;
  assign rd_idx_o = rd_idx_i;
  assign imm_data_o = imm_data_i;
  assign csr_data_o = csr_data_i;
  assign csr_imm_o = csr_imm_i;
  assign csr_imm_valid_o = csr_imm_valid_i;
  assign exc_csr_addr_o = csr_readaddr_i;




  wire _excop_auipc = (exc_op_i == `EXCOP_AUIPC);
  wire _excop_lui = (exc_op_i == `EXCOP_LUI);
  wire _excop_jal = (exc_op_i == `EXCOP_JAL);
  wire _excop_jalr = (exc_op_i == `EXCOP_JALR);
  wire _excop_load = (exc_op_i == `EXCOP_LOAD);
  wire _excop_store = (exc_op_i == `EXCOP_STORE);
  wire _excop_branch = (exc_op_i == `EXCOP_BRANCH);
  wire _excop_opimm = (exc_op_i == `EXCOP_OPIMM);
  wire _excop_opimm32 = (exc_op_i == `EXCOP_OPIMM32);
  wire _excop_op = (exc_op_i == `EXCOP_OP);
  wire _excop_op32 = (exc_op_i == `EXCOP_OP32);
  wire _excop_csr = (exc_op_i == `EXCOP_CSR);
  wire _excop_ebreak = (exc_op_i == `EXCOP_EBREAK);
  wire _excop_none = (exc_op_i == `EXCOP_NONE);

  /*****************************branch 操作********************************/
  wire [`XLEN_BUS] _pc_add_imm;
  assign _pc_add_imm = pc_i + imm_data_i;

  wire [`XLEN_BUS] _rs1_add_imm;
  assign _rs1_add_imm = rs1_data_i + imm_data_i;

  wire [`XLEN_BUS] _branch_pc = ({`XLEN{_excop_jal|_excop_branch}}&_pc_add_imm)|
                                ({`XLEN{_excop_jalr}}&_rs1_add_imm);

  // TODO 还需要完善
  wire _branch_pc_valid = (_compare_out & _excop_branch) | _excop_jal | _excop_jalr;

  assign branch_pc_o = _branch_pc;
  assign branch_pc_valid_o = _branch_pc_valid;

  // 若跳转指令有效，通知控制模块，中断流水线
  assign jump_hazard_valid_o = _branch_pc_valid;

  /****************************** ALU 操作******************************************/

  /* ALU 两端操作数选择 */
  wire _rs1_rs2 = _excop_op32 | _excop_op | _excop_branch;
  wire _rs1_imm = _excop_opimm | _excop_opimm32 | _excop_load | _excop_store;
  wire _pc_4 = _excop_jal | _excop_jalr;
  wire _pc_imm12 = _excop_auipc;
  wire _none_imm12 = _excop_lui;
  wire _none_csr = _excop_csr;  //保存原来的 csr csr->rd

  /* jal jalr lui auipc ecall ebreak 需要单独处理 */
  /* 拼接代替左移 */
  // wire [`IMM_LEN-1:0] _imm_aui_auipc = imm_data << 12;
  wire [`IMM_LEN-1:0] _imm_aui_auipc = {imm_data_i[`IMM_LEN-1:12], 12'b0};
  // ALU 第一个操作数
  wire [         `XLEN_BUS] _alu_in1 = ({`XLEN{_rs1_rs2 | _rs1_imm}}&rs1_data_i) |
                                       ({`XLEN{_pc_4 | _pc_imm12}}&pc_i) |
                                       ({`XLEN{_none_imm12|_none_csr}}&`XLEN'b0);
  // ALU 第二个操作数
  wire [         `XLEN_BUS] _alu_in2 = ({`XLEN{_rs1_rs2}}&rs2_data_i) |
                                       ({`XLEN{_rs1_imm}}&imm_data_i) |
                                       ({`XLEN{_none_csr}}&csr_data_i) |
                                       ({`XLEN{_pc_4}}&`XLEN'd4)   |
                                       ({`XLEN{_pc_imm12|_none_imm12}}&_imm_aui_auipc);

  wire [`XLEN_BUS] _alu_out;
  wire _compare_out;
  alu_top u_alu (
      /* ALU 端口 */
      .alu_a_i(_alu_in1),
      .alu_b_i(_alu_in2),
      .alu_out_o(_alu_out),
      .alu_op_i(alu_op_i),
      .compare_out_o(_compare_out)
  );
  /* alu计算结果需要符号扩展 */
  wire _alu_sext = _excop_opimm32 | _excop_op32;
  wire [`XLEN_BUS] _alu_sext_out = {{32{_alu_out[31]}}, _alu_out[31:0]};
  assign exc_alu_data_o = (_alu_sext) ? _alu_sext_out : _alu_out;

  //assign exc_out = _alu_out;

  /***************************** CSR 执行操作 **************************/

  wire [`XLEN_BUS] _csr_exe_data;
  wire _csr_exe_data_valid;
  execute_csr u_execute_csr (
      .csr_imm_i           (csr_imm_i),
      .csr_imm_valid_i     (csr_imm_valid_i),     // 是否是立即数指令
      .rs1_data_i          (rs1_data_i),          // rs1 data
      .csr_data_i          (csr_data_i),          // 读取的 CSR 数据
      .csr_op_i            (csr_op_i),            // csr 操作码
      .csr_exe_data_o      (_csr_exe_data),
      .csr_exe_data_valid_o(_csr_exe_data_valid)
  );

  assign exc_csr_data_o  = _csr_exe_data;
  assign exc_csr_valid_o = _csr_exe_data_valid;


  /* trap_bus TODO:add more*/
  reg [`TRAP_BUS] _exc_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `TRAP_LEN; i = i + 1) begin
      _exc_trap_bus[i] = trap_bus_i[i];
    end
  end
  assign trap_bus_o = _exc_trap_bus;
endmodule
