`include "sysconfig.v"

/* 需要设为为input熟悉才能才仿真中改变值 */
module top (
    input clk,
    input rst
);

  /*×××××××××××××××××××××××××× PC 模块 用于选择吓一跳指令地址 ×××××××××××××××××××××××*/
  wire [`XLEN_BUS] inst_addr;
  wire [`XLEN_BUS] pc_next;
  wire read_req;
  pc_reg u_pc_reg (
      .clk              (clk),
      .rst              (rst),
      .stall_valid_i    (stall_clint),
      .flush_valid_i    (flush_clint),
      .branch_pc_i      (branch_pc),
      .branch_pc_valid_i(branch_pc_valid),
      .clint_pc_i       (clint_pc),
      //trap pc,来自mem
      .clint_pc_valid_i (clint_pc_valid),
      //trap pc valide,来自mem
      //输出pc
      .read_req_o       (read_req),
      .if_rdata_valid_i (if_rdata_valid),
      .pc_next_o        (pc_next),          //输出 next_pc
      .pc_o             (inst_addr)
  );
  /*************************** 取指阶段 *************************************/
  wire [`XLEN_BUS] inst_addr_if;
  wire [`INST_LEN-1:0] inst_data_if;
  wire [`TRAP_BUS] trap_bus_if;

  //   // if ram 接口
  //   wire [`NPC_ADDR_BUS] if_read_addr;  // 地址
  //   wire if_raddr_valid;  // 地址是否准备好
  //   wire if_raddr_ready;
  //   wire [7:0] if_rmask;  // 数据掩码,读取多少位

  wire if_rdata_valid;  // 读数据是否准备好
  wire [`XLEN_BUS] if_rdata;  // 返回到读取的数据

  wire ram_stall_valid_if;


  fetch u_fetch (
      //指令地址
      .rst        (rst),
      .inst_addr_i(inst_addr),
      // from pc_reg

      .if_rdata_valid_i(if_rdata_valid),  // 读数据是否准备好
      .if_rdata_i      (if_rdata),        // 返回到读取的数据

      /* stall req */
      .ram_stall_valid_if_o(ram_stall_valid_if),
      // if 阶段访存暂停
      /* to if/id */
      .inst_addr_o         (inst_addr_if),
      .inst_data_o         (inst_data_if),
      .trap_bus_o          (trap_bus_if)
  );

  /*************************** if/id 流水线缓存 *************************************/
  wire [`XLEN_BUS] inst_addr_if_id;
  wire [`INST_LEN-1:0] inst_data_if_id;
  wire [`TRAP_BUS] trap_bus_if_id;

  if_id u_if_id (
      .clk              (clk),
      .rst              (rst),
      .flush_valid_i    (flush_clint),
      .stall_valid_i    (stall_clint),
      //指令地址
      .inst_addr_if_i   (inst_addr_if),
      //指令内容
      .inst_data_if_i   (inst_data_if),
      .trap_bus_if_i    (trap_bus_if),
      //指令地址
      .inst_addr_if_id_o(inst_addr_if_id),
      //指令内容
      .inst_data_if_id_o(inst_data_if_id),
      .trap_bus_if_id_o (trap_bus_if_id)
  );

  /*************************** decode 阶段 *************************************/

  /*通用寄存器译码结果：to id/ex */
  wire [    `REG_ADDRWIDTH-1:0 ] rs1_idx_id;
  wire [    `REG_ADDRWIDTH-1:0 ] rs2_idx_id;
  wire [    `REG_ADDRWIDTH-1:0 ] rd_idx_id;
  wire [             `XLEN_BUS]  rs1_data_id;
  wire [             `XLEN_BUS]  rs2_data_id;
  wire [          `IMM_LEN-1:0 ] imm_data_id;
  /* CSR 译码结果：to id/ex*/
  wire [          `IMM_LEN-1:0 ] csr_imm_id;
  wire                           csr_imm_valid_id;
  wire [`CSR_REG_ADDRWIDTH-1:0 ] csr_idx_id;
  wire [             `XLEN_BUS]  csr_readdata_id;

  wire [        `ALUOP_LEN-1:0 ] alu_op_id;  // alu 操作码
  wire [        `MEMOP_LEN-1:0 ] mem_op_id;  // mem 操作码
  wire [        `EXCOP_LEN-1:0 ] exc_op_id;  // exc 操作码
  wire [         `PCOP_LEN-1:0 ] pc_op_id;  // pc 操作码
  wire [        `CSROP_LEN-1:0 ] csr_op_id;  // csr 操作码

  wire [             `XLEN_BUS]  inst_addr_id;
  wire [         `INST_LEN-1:0 ] inst_data_id;
  // 请求暂停流水线
  wire                           load_use_valid;
  /* TARP 总线 */
  wire [             `TRAP_BUS]  trap_bus_id;

  dcode u_dcode (
      /* from if/id */
      .inst_addr_i(inst_addr_if_id),
      .inst_data_i(inst_data_if_id),
      .trap_bus_i(trap_bus_if_id),
      /* from gpr regs */
      .rs1_data_i(rs1_data_gpr),
      .rs2_data_i(rs2_data_gpr),
      /* from csr regs */
      .csr_data_i(csr_data_csr),
      /* from id/ex stage */
      .id_ex_exc_op_i (exc_op_id_ex), // 上一条指令的类型，用于判断上一条指令是否是访存指令
      /* from exc bypass */
      .ex_rd_data_i(exc_alu_data_ex),
      .ex_rd_addr_i(rd_idx_ex),
      .ex_csr_writeaddr_i(exc_csr_addr_ex),
      .ex_csr_writedata_i(exc_csr_data_ex),
      /* from mem bypass */
      .mem_rd_data_i(mem_data_mem),
      .mem_rd_addr_i(rd_idx_mem),
      /*通用寄存器译码结果：to id/ex */
      .rs1_idx_o(rs1_idx_id),
      .rs2_idx_o(rs2_idx_id),
      .rd_idx_o(rd_idx_id),
      .rs1_data_o(rs1_data_id),
      .rs2_data_o(rs2_data_id),
      .imm_data_o(imm_data_id),
      /* CSR 译码结果：to id/ex*/
      .csr_imm_o(csr_imm_id),
      .csr_imm_valid_o(csr_imm_valid_id),
      .csr_idx_o(csr_idx_id),
      .csr_readdata_o(csr_readdata_id),
      .alu_op_o(alu_op_id),
      // alu 操作码
      .mem_op_o(mem_op_id),
      // mem 操作码
      .exc_op_o(exc_op_id),
      // exc 操作码
      .pc_op_o(pc_op_id),
      // pc 操作码
      .csr_op_o(csr_op_id),
      // csr 操作码
      .inst_addr_o(inst_addr_id),
      .inst_data_o(inst_data_id),
      // 请求暂停流水线 to ctrl
      ._load_use_valid_o(load_use_valid),
      /* TARP 总线 */
      .trap_bus_o(trap_bus_id)
  );
  /*************************** id/ex 流水线缓存 *************************************/
  wire [    `REG_ADDRWIDTH-1:0 ] rs1_idx_id_ex;
  wire [    `REG_ADDRWIDTH-1:0 ] rs2_idx_id_ex;
  wire [    `REG_ADDRWIDTH-1:0 ] rd_idx_id_ex;
  wire [             `XLEN_BUS]  rs1_data_id_ex;
  wire [             `XLEN_BUS]  rs2_data_id_ex;
  wire [          `IMM_LEN-1:0 ] imm_data_id_ex;
  wire [          `IMM_LEN-1:0 ] csr_imm_id_ex;
  wire                           csr_imm_valid_id_ex;
  wire [`CSR_REG_ADDRWIDTH-1:0 ] csr_idx_id_ex;
  wire [             `XLEN_BUS]  csr_readdata_id_ex;
  wire [        `ALUOP_LEN-1:0 ] alu_op_id_ex;  // alu 操作码
  wire [        `MEMOP_LEN-1:0 ] mem_op_id_ex;  // mem 操作码
  wire [        `EXCOP_LEN-1:0 ] exc_op_id_ex;  // exc 操作码
  wire [         `PCOP_LEN-1:0 ] pc_op_id_ex;  // pc 操作码
  wire [        `CSROP_LEN-1:0 ] csr_op_id_ex;  // csr 操作码
  wire [             `XLEN_BUS]  inst_addr_id_ex;
  wire [         `INST_LEN-1:0 ] inst_data_id_ex;
  // wire                           id_stall_req_valid_id_ex;
  wire [             `TRAP_BUS]  trap_bus_id_ex;

  id_ex u_id_ex (
      .clk                  (clk),
      .rst                  (rst),
      .flush_valid_i        (flush_clint),
      .stall_valid_i        (stall_clint),
      /* 输入 */
      .pc_id_ex_i           (inst_addr_id),
      .inst_data_id_ex_i    (inst_data_id),
      .rs1_idx_id_ex_i      (rs1_idx_id),
      .rs2_idx_id_ex_i      (rs2_idx_id),
      .rd_idx_id_ex_i       (rd_idx_id),
      .imm_data_id_ex_i     (imm_data_id),
      .csr_imm_id_ex_i      (csr_imm_id),
      .csr_imm_valid_id_ex_i(csr_imm_valid_id),
      .csr_idx_id_ex_i      (csr_idx_id),
      .rs1_data_id_ex_i     (rs1_data_id),
      .rs2_data_id_ex_i     (rs2_data_id),
      .csr_data_id_ex_i     (csr_readdata_id),
      .alu_op_id_ex_i       (alu_op_id),
      // alu 操作码
      .mem_op_id_ex_i       (mem_op_id),
      // mem 操作码
      .exc_op_id_ex_i       (exc_op_id),
      // exc 操作码
      .pc_op_id_ex_i        (pc_op_id),
      // pc 操作码
      .csr_op_id_ex_i       (csr_op_id),
      // csr 操作码
      /* TARP 总线 */
      .trap_bus_id_ex_i     (trap_bus_id),
      /* 输出 */
      .pc_id_ex_o           (inst_addr_id_ex),
      .inst_data_id_ex_o    (inst_data_id_ex),
      .rs1_idx_id_ex_o      (rs1_idx_id_ex),
      .rs2_idx_id_ex_o      (rs2_idx_id_ex),
      .rd_idx_id_ex_o       (rd_idx_id_ex),
      .imm_data_id_ex_o     (imm_data_id_ex),
      .csr_imm_id_ex_o      (csr_imm_id_ex),
      .csr_imm_valid_id_ex_o(csr_imm_valid_id_ex),
      .csr_idx_id_ex_o      (csr_idx_id_ex),
      .rs1_data_id_ex_o     (rs1_data_id_ex),
      .rs2_data_id_ex_o     (rs2_data_id_ex),
      .csr_data_id_ex_o     (csr_readdata_id_ex),
      .alu_op_id_ex_o       (alu_op_id_ex),
      // alu 操作码
      .mem_op_id_ex_o       (mem_op_id_ex),
      // mem 操作码
      .exc_op_id_ex_o       (exc_op_id_ex),
      // exc 操作码
      .pc_op_id_ex_o        (pc_op_id_ex),
      // pc 操作码
      .csr_op_id_ex_o       (csr_op_id_ex),
      // csr 操作码
      /* TARP 总线 */
      .trap_bus_id_ex_o     (trap_bus_id_ex)
  );

  /*************************** ex 阶段 *************************************/

  wire [             `XLEN_BUS]  pc_ex;
  wire [         `INST_LEN-1:0 ] inst_data_ex;
  wire [    `REG_ADDRWIDTH-1:0 ] rd_idx_ex;
  wire [             `XLEN_BUS]  rs1_data_ex;
  wire [             `XLEN_BUS]  rs2_data_ex;
  wire [          `IMM_LEN-1:0 ] imm_data_ex;
  wire [             `XLEN_BUS]  csr_data_ex;
  wire [          `IMM_LEN-1:0 ] csr_imm_ex;
  wire                           csr_imm_valid_ex;
  wire [        `MEMOP_LEN-1:0 ] mem_op_ex;  // 访存操作码
  wire [         `PCOP_LEN-1:0 ] pc_op_ex;
  wire [             `XLEN_BUS]  exc_alu_data_ex;  // 同时送给 ID 和 EX/MEM
  wire [             `XLEN_BUS]  exc_csr_data_ex;
  wire                           exc_csr_valid_ex;
  wire [`CSR_REG_ADDRWIDTH-1:0 ] exc_csr_addr_ex;
  wire [        `EXCOP_LEN-1:0 ] exc_op_ex;  // exc 操作码
  // 请求暂停流水线
  wire                           jump_hazard_valid;
  /* TARP 总线 */
  wire [             `TRAP_BUS]  trap_bus_ex;


  wire [             `XLEN_BUS]  branch_pc;
  wire                           branch_pc_valid;

  execute_top u_execute_top (
      /******************************* from id/ex *************************/
      // pc
      .pc_i           (inst_addr_id_ex),
      .inst_data_i    (inst_data_id_ex),
      // gpr 译码结果
      .rd_idx_i       (rd_idx_id_ex),
      .rs1_data_i     (rs1_data_id_ex),
      .rs2_data_i     (rs2_data_id_ex),
      .imm_data_i     (imm_data_id_ex),
      // CSR 译码结果 
      .csr_readaddr_i (csr_idx_id_ex),
      .csr_data_i     (csr_readdata_id_ex),
      .csr_imm_i      (csr_imm_id_ex),
      .csr_imm_valid_i(csr_imm_valid_id_ex),
      // 指令微码
      .alu_op_i       (alu_op_id_ex),
      // alu 操作码
      .mem_op_i       (mem_op_id_ex),
      // 访存操作码
      .exc_op_i       (exc_op_id_ex),
      // exc 操作码
      .csr_op_i       (csr_op_id_ex),
      // exc_csr 操作码
      .pc_op_i        (pc_op_id_ex),
      /* TARP 总线 */
      .trap_bus_i     (trap_bus_id_ex),
      /********************** to ex/mem **************************/
      // pc
      .pc_o           (pc_ex),
      .inst_data_o    (inst_data_ex),
      // gpr 译码结果
      .rd_idx_o       (rd_idx_ex),
      .rs1_data_o     (rs1_data_ex),
      .rs2_data_o     (rs2_data_ex),
      .imm_data_o     (imm_data_ex),
      // CSR 译码结果 
      .csr_data_o     (csr_data_ex),
      .csr_imm_o      (csr_imm_ex),
      .csr_imm_valid_o(csr_imm_valid_ex),
      .mem_op_o       (mem_op_ex),
      // 访存操作码
      .pc_op_o        (pc_op_ex),
      .exc_alu_data_o (exc_alu_data_ex),
      // 同时送给 ID 和 EX/MEM
      .exc_csr_data_o (exc_csr_data_ex),
      .exc_csr_valid_o(exc_csr_valid_ex),
      .exc_csr_addr_o (exc_csr_addr_ex),
      /************************to id *************************************/
      .exc_op_o       (exc_op_ex),
      // exc 操作码

      // 请求暂停流水线
      .jump_hazard_valid_o(jump_hazard_valid),
      .branch_pc_o        (branch_pc),
      .branch_pc_valid_o  (branch_pc_valid),
      /* TARP 总线 */
      .trap_bus_o         (trap_bus_ex)
  );
  /**********************  ex/mem 流水线间缓存 **************************/


  wire [             `XLEN_BUS]  pc_ex_mem;
  wire [         `INST_LEN-1:0 ] inst_data_ex_mem;
  wire [             `XLEN_BUS]  imm_data_ex_mem;
  wire [    `REG_ADDRWIDTH-1:0 ] rd_idx_ex_mem;
  wire [             `XLEN_BUS]  rs1_data_ex_mem;
  wire [             `XLEN_BUS]  rs2_data_ex_mem;
  wire [             `XLEN_BUS]  alu_data_ex_mem;
  wire [             `XLEN_BUS]  csr_writedata_ex_mem;
  wire                           csr_writevalid_ex_mem;
  wire [`CSR_REG_ADDRWIDTH-1:0 ] csr_addr_ex_mem;
  wire [         `PCOP_LEN-1:0 ] pc_op_ex_mem;
  wire [        `MEMOP_LEN-1:0 ] mem_op_ex_mem;
  /* TARP 总线 */
  wire [             `TRAP_BUS]  trap_bus_ex_mem;

  ex_mem u_ex_mem (
      .clk                    (clk),
      .rst                    (rst),
      .flush_valid_i          (flush_clint),
      .stall_valid_i          (stall_clint),
      .pc_ex_mem_i            (pc_ex),
      .inst_data_ex_mem_i     (inst_data_ex),
      .imm_data_ex_mem_i      (imm_data_ex),
      .rd_idx_ex_mem_i        (rd_idx_ex),
      .rs1_data_ex_mem_i      (rs1_data_ex),
      .rs2_data_ex_mem_i      (rs2_data_ex),
      .alu_data_ex_mem_i      (exc_alu_data_ex),
      .csr_writedata_ex_mem_i (exc_csr_data_ex),
      .csr_writevalid_ex_mem_i(exc_csr_valid_ex),
      .csr_addr_ex_mem_i      (exc_csr_addr_ex),
      .pc_op_ex_mem_i         (pc_op_ex),
      .mem_op_ex_mem_i        (mem_op_ex),
      /* TARP 总线 */
      .trap_bus_ex_mem_i      (trap_bus_ex),
      .pc_ex_mem_o            (pc_ex_mem),
      .inst_data_ex_mem_o     (inst_data_ex_mem),
      .imm_data_ex_mem_o      (imm_data_ex_mem),
      .rd_idx_ex_mem_o        (rd_idx_ex_mem),
      .rs1_data_ex_mem_o      (rs1_data_ex_mem),
      .rs2_data_ex_mem_o      (rs2_data_ex_mem),
      .alu_data_ex_mem_o      (alu_data_ex_mem),
      .csr_writedata_ex_mem_o (csr_writedata_ex_mem),
      .csr_writevalid_ex_mem_o(csr_writevalid_ex_mem),
      .csr_addr_ex_mem_o      (csr_addr_ex_mem),
      .pc_op_ex_mem_o         (pc_op_ex_mem),
      .mem_op_ex_mem_o        (mem_op_ex_mem),
      /* TARP 总线 */
      .trap_bus_ex_mem_o      (trap_bus_ex_mem)
  );

  /**********************  访存阶段 **************************/


  /* to mem/wb */
  wire [             `XLEN_BUS]  pc_mem;
  wire [         `INST_LEN-1:0 ] inst_data_mem;
  wire [             `XLEN_BUS]  mem_data_mem;  //同时送回 id 阶段（bypass）
  wire [    `REG_ADDRWIDTH-1:0 ] rd_idx_mem;
  wire [`CSR_REG_ADDRWIDTH-1:0 ] csr_addr_mem;
  wire [             `XLEN_BUS]  exc_csr_data_mem;
  wire                           exc_csr_valid_mem;

  /* dcache 接口 */
  wire [         `NPC_ADDR_BUS]  mem_addr;  // 地址
  wire                           mem_addr_valid;  // 地址是否有效
  wire [                   7:0 ] mem_mask;  // 数据掩码,读取多少位
  wire                           mem_write_valid;  // 1'b1,表示写;1'b0 表示读 
  wire                           mem_data_ready;  // 读/写 数据是否准备好
  wire [             `XLEN_BUS]  mem_rdata;  // 返回到读取的数据
  wire [             `XLEN_BUS]  mem_wdata;  // 写入的数据


  /* TARP 总线 */
  wire [             `TRAP_BUS]  trap_bus_mem;

  wire                           ram_stall_valid_mem;

  memory u_memory (
      .clk(clk),
      .rst(rst),
      /* from ex/mem */
      .pc_i(pc_ex_mem),
      .inst_data_i(inst_data_ex_mem),
      .rd_idx_i(rd_idx_ex_mem),
      // input  [         `XLEN_BUS] rs1_data_i,
      .rs2_data_i(rs2_data_ex_mem),
      // input  [      `IMM_LEN-1:0] imm_data_i,
      .mem_op_i(mem_op_ex_mem),  // 访存操作码
      .exc_alu_data_i(alu_data_ex_mem),
      .csr_addr_i(csr_addr_ex_mem),
      .exc_csr_data_i(csr_writedata_ex_mem),
      .exc_csr_valid_i(csr_writevalid_ex_mem),
      /* dcache 接口 */
      .mem_addr_o(mem_addr),
      .mem_addr_valid_o(mem_addr_valid),
      .mem_mask_o(mem_mask),
      .mem_write_valid_o(mem_write_valid),
      .mem_data_ready_i(mem_data_ready),
      .mem_rdata_i(mem_rdata),
      .mem_wdata_o(mem_wdata),

      // TARP 总线
      .trap_bus_i(trap_bus_ex_mem),
      .ram_stall_valid_mem_o(ram_stall_valid_mem),
      /* to mem/wb */
      .pc_o(pc_mem),
      .inst_data_o(inst_data_mem),
      .mem_data_o(mem_data_mem),  // gpr写回数据，同时送回 id 阶段（bypass）
      .rd_idx_o(rd_idx_mem),  // gpr 写回地址
      .csr_addr_o(csr_addr_mem),  // csr 写回地址
      .exc_csr_data_o(exc_csr_data_mem),  // csr 写回数据
      .exc_csr_valid_o(exc_csr_valid_mem),  // 写回数据有效位
      .trap_bus_o(trap_bus_mem)  /* TARP 总线 */
  );

  // （组合逻辑电路）在访存阶段执行
  wire [`XLEN-1:0] csr_mstatus_writedata;
  wire [`XLEN-1:0] csr_mepc_writedata;
  wire [`XLEN-1:0] csr_mcause_writedata;
  wire [`XLEN-1:0] csr_mtval_writedata;
  wire [`XLEN-1:0] csr_mtvec_writedata;
  wire csr_mstatus_write_valid;
  wire csr_mepc_write_valid;
  wire csr_mcause_write_valid;
  wire csr_mtval_write_valid;
  wire csr_mtvec_write_valid;
  /* 输出至取指阶段 */
  wire [`XLEN-1:0] clint_pc;
  wire clint_pc_valid;

  reg[5:0]stall_clint;  // stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB， one bit for one stage respectively
  wire [5:0] flush_clint;

  clint u_clint (
      // input wire clk,
      .rst(rst),
      .pc_i(pc_ex_mem),
      .inst_data_i(inst_data_ex_mem),
      .load_use_valid_id_i(load_use_valid),  //load-use data hazard from id
      .jump_valid_ex_i(jump_hazard_valid),  // branch hazard from ex
      .ram_stall_valid_if_i(ram_stall_valid_if),
      .ram_stall_valid_mem_i(ram_stall_valid_mem),
      /* TARP 总线 */
      .trap_bus_i(trap_bus_mem),  // 包括 取指，译码，执行，访存 阶段的 trap 请求
      /* trap 所需寄存器，来自于 csr (读)*/
      .csr_mstatus_readdata_i(csr_mstatus_readdata_csr),
      .csr_mepc_readdata_i(csr_mepc_readdata_csr),
      .csr_mcause_readdata_i(csr_mcause_readdata_csr),
      .csr_mtval_readdata_i(csr_mtval_readdata_csr),
      .csr_mtvec_readdata_i(csr_mtvec_readdata_csr),
      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_o(csr_mstatus_writedata),
      .csr_mepc_writedata_o(csr_mepc_writedata),
      .csr_mcause_writedata_o(csr_mcause_writedata),
      .csr_mtval_writedata_o(csr_mtval_writedata),
      .csr_mtvec_writedata_o(csr_mtvec_writedata),
      .csr_mstatus_write_valid_o(csr_mstatus_write_valid),
      .csr_mepc_write_valid_o(csr_mepc_write_valid),
      .csr_mcause_write_valid_o(csr_mcause_write_valid),
      .csr_mtval_write_valid_o(csr_mtval_write_valid),
      .csr_mtvec_write_valid_o(csr_mtvec_write_valid),
      /* 输出至取指阶段 */
      .clint_pc_o(clint_pc),  // trap pc
      .clint_pc_valid_o(clint_pc_valid),  // trap pc valid
      .stall_o(stall_clint),
      .flush_o(flush_clint)
  );


  /**********************  mem/wb 阶段 **************************/

  wire [             `XLEN-1:0 ] csr_mstatus_writedata_mem_wb;
  wire [             `XLEN-1:0 ] csr_mepc_writedata_mem_wb;
  wire [             `XLEN-1:0 ] csr_mcause_writedata_mem_wb;
  wire [             `XLEN-1:0 ] csr_mtval_writedata_mem_wb;
  wire [             `XLEN-1:0 ] csr_mtvec_writedata_mem_wb;
  wire                           csr_mstatus_write_valid_mem_wb;
  wire                           csr_mepc_write_valid_mem_wb;
  wire                           csr_mcause_write_valid_mem_wb;
  wire                           csr_mtval_write_valid_mem_wb;
  wire                           csr_mtvec_write_valid_mem_wb;
  wire [             `XLEN-1:0 ] pc_mem_wb;  //指令地址
  wire [         `INST_LEN-1:0 ] inst_data_mem_wb;  //指令内容


  wire [`CSR_REG_ADDRWIDTH-1:0 ] csr_addr_mem_wb;  //csr 写回地址
  wire [             `XLEN_BUS]  exc_csr_data_mem_wb;  //csr 写回数据
  wire                           exc_csr_valid_mem_wb;  // csr 写回使能
  wire [    `REG_ADDRWIDTH-1:0 ] rd_addr_mem_wb;  // gpr 写回使能
  wire [             `XLEN-1:0 ] mem_data_mem_wb;  //访存阶段的数据



  //     input [`CSR_REG_ADDRWIDTH-1:0] csr_addr_mem_wb_i,       //csr 写回地址
  // input [             `XLEN_BUS] exc_csr_data_mem_wb_i,   //csr 写回数据
  // input                          exc_csr_valid_mem_wb_i,  // csr 写回使能
  // input [    `REG_ADDRWIDTH-1:0] rd_addr_mem_wb_i,        // gpr 写回使能
  // input [             `XLEN-1:0] mem_data_mem_wb_i,       //访存阶段的数据

  mem_wb u_mem_wb (
      .clk                             (clk),
      .rst                             (rst),
      .flush_valid_i                   (flush_clint),
      .stall_valid_i                   (stall_clint),
      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_mem_wb_i  (csr_mstatus_writedata),
      .csr_mepc_writedata_mem_wb_i     (csr_mepc_writedata),
      .csr_mcause_writedata_mem_wb_i   (csr_mcause_writedata),
      .csr_mtval_writedata_mem_wb_i    (csr_mtval_writedata),
      .csr_mtvec_writedata_mem_wb_i    (csr_mtvec_writedata),
      .csr_mstatus_write_valid_mem_wb_i(csr_mstatus_write_valid),
      .csr_mepc_write_valid_mem_wb_i   (csr_mepc_write_valid),
      .csr_mcause_write_valid_mem_wb_i (csr_mcause_write_valid),
      .csr_mtval_write_valid_mem_wb_i  (csr_mtval_write_valid),
      .csr_mtvec_write_valid_mem_wb_i  (csr_mtvec_write_valid),
      .pc_mem_wb_i                     (pc_mem),
      .inst_data_mem_wb_i              (inst_data_mem),
      .csr_addr_mem_wb_i               (csr_addr_mem),
      .exc_csr_data_mem_wb_i           (exc_csr_data_mem),
      .exc_csr_valid_mem_wb_i          (exc_csr_valid_mem),
      .rd_addr_mem_wb_i                (rd_idx_mem),
      .mem_data_mem_wb_i               (mem_data_mem),

      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_mem_wb_o(csr_mstatus_writedata_mem_wb),
      .csr_mepc_writedata_mem_wb_o(csr_mepc_writedata_mem_wb),
      .csr_mcause_writedata_mem_wb_o(csr_mcause_writedata_mem_wb),
      .csr_mtval_writedata_mem_wb_o(csr_mtval_writedata_mem_wb),
      .csr_mtvec_writedata_mem_wb_o(csr_mtvec_writedata_mem_wb),
      .csr_mstatus_write_valid_mem_wb_o(csr_mstatus_write_valid_mem_wb),
      .csr_mepc_write_valid_mem_wb_o(csr_mepc_write_valid_mem_wb),
      .csr_mcause_write_valid_mem_wb_o(csr_mcause_write_valid_mem_wb),
      .csr_mtval_write_valid_mem_wb_o(csr_mtval_write_valid_mem_wb),
      .csr_mtvec_write_valid_mem_wb_o(csr_mtvec_write_valid_mem_wb),
      .pc_mem_wb_o(pc_mem_wb),
      .inst_data_mem_wb_o(inst_data_mem_wb),
      .csr_addr_mem_wb_o(csr_addr_mem_wb),
      .exc_csr_data_mem_wb_o(exc_csr_data_mem_wb),
      .exc_csr_valid_mem_wb_o(exc_csr_valid_mem_wb),
      .rd_addr_mem_wb_o(rd_addr_mem_wb),
      .mem_data_mem_wb_o(mem_data_mem_wb)

  );



  /***************************写回阶段***********************************/
  writeback u_writeback (
      .clk           (clk),
      .rst           (rst),
      .pc_wb_i       (pc_mem_wb),
      .inst_data_wb_i(inst_data_mem_wb)
      //   .mem_data_i     (mem_data_mem_wb),
      //   .rd_idx_i       (rd_addr_mem_wb),
      //   .csr_addr_i     (csr_addr_mem_wb),
      //   .exc_csr_data_i (exc_csr_data_mem_wb),
      //   .exc_csr_valid_i(exc_csr_valid_mem_wb),
      //   /* TO GPR,CSR REGFILE */
      //   .mem_data_o     (mem_data_o),
      //   .rd_idx_o       (rd_idx_o),
      //   .csr_addr_o     (csr_addr_o),
      //   .exc_csr_data_o (exc_csr_data_o),
      //   .exc_csr_valid_o(exc_csr_valid_o)
  );
  /******************** gpr 寄存器组、csr 寄存器组 ************************/

  wire [`XLEN_BUS] rs1_data_gpr;
  wire [`XLEN_BUS] rs2_data_gpr;

  rv64_gpr_regfile u_rv64_gpr_regfile (
      .clk               (clk),
      .rst               (rst),
      /* 读取数据 */
      .rs1_idx_i         (rs1_idx_id),
      .rs2_idx_i         (rs2_idx_id),
      .rs1_data_o        (rs1_data_gpr),
      .rs2_data_o        (rs2_data_gpr),     //TODO 添加 valid 信号
      /* 写��数据 */
      .write_idx_i       (rd_addr_mem_wb),
      .write_data_i      (mem_data_mem_wb),
      .write_data_valid_i(1'b1)
  );



  /* 单独引出寄存器(读) */
  wire [`XLEN-1:0] csr_mstatus_readdata_csr;
  wire [`XLEN-1:0] csr_mepc_readdata_csr;
  wire [`XLEN-1:0] csr_mcause_readdata_csr;
  wire [`XLEN-1:0] csr_mtval_readdata_csr;
  wire [`XLEN-1:0] csr_mtvec_readdata_csr;

  wire [`XLEN-1:0] csr_data_csr;
  rv64_csr_regfile u_rv64_csr_regfile (
      .clk                      (clk),
      .rst                      (rst),
      /* 单独引出寄存器(写) */
      .csr_mstatus_writedata_i  (csr_mstatus_writedata_mem_wb),
      .csr_mepc_writedata_i     (csr_mepc_writedata_mem_wb),
      .csr_mcause_writedata_i   (csr_mcause_writedata_mem_wb),
      .csr_mtval_writedata_i    (csr_mtval_writedata_mem_wb),
      .csr_mtvec_writedata_i    (csr_mtvec_writedata_mem_wb),
      .csr_mstatus_write_valid_i(csr_mstatus_write_valid_mem_wb),
      .csr_mepc_write_valid_i   (csr_mepc_write_valid_mem_wb),
      .csr_mcause_write_valid_i (csr_mcause_write_valid_mem_wb),
      .csr_mtval_write_valid_i  (csr_mtval_write_valid_mem_wb),
      .csr_mtvec_write_valid_i  (csr_mtvec_write_valid_mem_wb),
      /* 单独引出寄存器(读) */
      .csr_mstatus_readdata_o   (csr_mstatus_readdata_csr),
      .csr_mepc_readdata_o      (csr_mepc_readdata_csr),
      .csr_mcause_readdata_o    (csr_mcause_readdata_csr),
      .csr_mtval_readdata_o     (csr_mtval_readdata_csr),
      .csr_mtvec_readdata_o     (csr_mtvec_readdata_csr),
      /* 读取数据端口 */
      .csr_readaddr_i           (csr_idx_id),
      .csr_readdata_o           (csr_data_csr),                    //TODO 添加 valid
      /* 写入数据端口 */
      .csr_writeaddr_i          (csr_addr_mem_wb),
      .csr_write_valid_i        (exc_csr_valid_mem_wb),
      .csr_writedata_i          (exc_csr_data_mem_wb)
  );

  /*****************************测试中的 cache 模块******************************/



  wire [`NPC_ADDR_BUS] ram_raddr_icache;
  wire ram_raddr_valid_icache;
  wire [7:0] ram_rmask_icache;
  wire ram_rdata_ready_icache;
  wire [`XLEN_BUS] ram_rdata_icache;
  icache_top u_icache_top (
      .clk(clk),
      .rst(rst),
      /* cpu<-->cache 端口 */
      .preif_raddr_i(pc_next[31:0]),  // CPU 的访存信息 
      .preif_rmask_i(8'b0000_1111),  // 访存掩码
      .preif_raddr_valid_i(read_req),  // 地址是否有效，无效时，停止访问 cache
      .if_rdata_o(if_rdata),  // icache 返回读数据
      .if_rdata_valid_o          (if_rdata_valid),// icache 读数据是否准备好(未准备好需要暂停流水线)
      /* cache<-->mem 端口 */
      .ram_raddr_icache_o(ram_raddr_icache),
      .ram_raddr_valid_icache_o(ram_raddr_valid_icache),
      .ram_rmask_icache_o(ram_rmask_icache),
      .ram_rdata_ready_icache_i(ram_rdata_ready_icache),
      .ram_rdata_icache_i(ram_rdata_icache)
  );


  /* dcache<-->mem 端口 */
  // 读端口
  wire [`NPC_ADDR_BUS]  ram_raddr_dcache;
  wire                  ram_raddr_valid_dcache;
  wire [          7:0 ] ram_rmask_dcache;
  wire                  ram_rdata_ready_dcache;
  wire [    `XLEN_BUS]  ram_rdata_dcache;
  // 写端口
  wire [`NPC_ADDR_BUS]  ram_waddr_dcache;  // 地址
  wire                  ram_waddr_valid_dcache;  // 地址是否准备好
  wire [          7:0 ] ram_wmask_dcache;  // 数据掩码,写入多少位
  wire                  ram_wdata_ready_dcache;  // 数据是否已经写入
  wire [    `XLEN_BUS]  ram_wdata_dcache;  // 写入的数据

  dcache_top u_dcache_top (
      .clk              (clk),
      .rst              (rst),
      /* cpu<-->cache 端口 */
      .mem_addr_i       (mem_addr),         // CPU 的访存信息 
      .mem_mask_i       (mem_mask),         // 访存掩码
      .mem_addr_valid_i (mem_addr_valid),   // 地址是否有效，无效时，停止访问 cache
      .mem_write_valid_i(mem_write_valid),  // 1'b1,表示写;1'b0 表示读 
      .mem_wdata_i      (mem_wdata),        // 写数据
      .mem_rdata_o      (mem_rdata),        // dcache 返回读数据
      .mem_data_ready_o (mem_data_ready),
      // dcache 读数据是否准备好(未准备好需要暂停流水线)

      /* cache<-->mem 端口 */
      // 读端口
      .ram_raddr_dcache_o(ram_raddr_dcache),
      .ram_raddr_valid_dcache_o(ram_raddr_valid_dcache),
      .ram_rmask_dcache_o(ram_rmask_dcache),
      .ram_rdata_ready_dcache_i(ram_rdata_ready_dcache),
      .ram_rdata_dcache_i(ram_rdata_dcache),
      // 写端口
      .ram_waddr_dcache_o(ram_waddr_dcache),  // 地址
      .ram_waddr_valid_dcache_o(ram_waddr_valid_dcache),  // 地址是否准备好
      .ram_wmask_dcache_o(ram_wmask_dcache),  // 数据掩码,写入多少位
      .ram_wdata_ready_dcache_i(ram_wdata_ready_dcache),// 数据是否已经写入// 写入的数据
      .ram_wdata_dcache_o(ram_wdata_dcache)
  );

  /****************************测试中的访存模块***********************************/
  ram_arb u_ram_arb (
      .clk              (clk),
      .rst              (rst),
      /* icache 读接口 */
      .if_read_addr_i   (ram_raddr_icache),        // if 阶段的 read
      .if_rmask_i       (ram_rmask_icache),        // 数据掩码
      .if_valid_i       (ram_raddr_valid_icache),  // 是否发起读请求
      .if_rdata_o       (ram_rdata_icache),        // 读数据返回mem
      .if_rdata_valid_o (ram_rdata_ready_icache),  // 读数据是否有效
      /* mem 读接口 */
      .mem_read_addr_i  (ram_raddr_dcache),        // mem 阶段的 read
      .mem_rmask_i      (ram_rmask_dcache),
      .mem_valid_i      (ram_raddr_valid_dcache),
      .mem_rdata_o      (ram_rdata_dcache),
      .mem_rdata_valid_o(ram_rdata_ready_dcache),

      // mem 访存请求端口（写）,独占
      .mem_write_addr_i(ram_waddr_dcache),  // mem 阶段的 write
      .mem_write_valid_i(ram_waddr_valid_dcache),
      .mem_wmask_i(ram_wmask_dcache),
      .mem_wdata_i(ram_wdata_dcache),
      .mem_wdata_ready_o(ram_wdata_ready_dcache)  // 数据是否已经写入
  );

endmodule

