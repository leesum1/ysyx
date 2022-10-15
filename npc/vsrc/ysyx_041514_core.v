`include "sysconfig.v"

/* 需要设为为input熟悉才能才仿真中改变值 */
module ysyx_041514_core (
    input clk,  //todo clock reset
    input rst,
    /* AXI4 master */
    // 写地址通道
    input io_master_awready,
    output io_master_awvalid,
    output [31:0] io_master_awaddr,
    output [3:0] io_master_awid,
    output [7:0] io_master_awlen,
    output [2:0] io_master_awsize,
    output [1:0] io_master_awburst,
    // 写数据通道
    input io_master_wready,
    output io_master_wvalid,
    output [63:0] io_master_wdata,
    output [7:0] io_master_wstrb,
    output io_master_wlast,
    // 写响应通道
    output io_master_bready,
    input io_master_bvalid,
    input [1:0] io_master_bresp,
    input [3:0] io_master_bid,
    // 读地址通道
    input io_master_arready,
    output io_master_arvalid,
    output [31:0] io_master_araddr,
    output [3:0] io_master_arid,
    output [7:0] io_master_arlen,
    output [2:0] io_master_arsize,
    output [1:0] io_master_arburst,
    // 读数据通道
    output io_master_rready,
    input io_master_rvalid,
    input [1:0] io_master_rresp,
    input [63:0] io_master_rdata,
    input io_master_rlast,
    input [3:0] io_master_rid,

    output [  5:0] io_sram0_addr,
    output         io_sram0_cen,
    output         io_sram0_wen,
    output [127:0] io_sram0_wmask,
    output [127:0] io_sram0_wdata,
    input  [127:0] io_sram0_rdata,
    output [  5:0] io_sram1_addr,
    output         io_sram1_cen,
    output         io_sram1_wen,
    output [127:0] io_sram1_wmask,
    output [127:0] io_sram1_wdata,
    input  [127:0] io_sram1_rdata,
    output [  5:0] io_sram2_addr,
    output         io_sram2_cen,
    output         io_sram2_wen,
    output [127:0] io_sram2_wmask,
    output [127:0] io_sram2_wdata,
    input  [127:0] io_sram2_rdata,
    output [  5:0] io_sram3_addr,
    output         io_sram3_cen,
    output         io_sram3_wen,
    output [127:0] io_sram3_wmask,
    output [127:0] io_sram3_wdata,
    input  [127:0] io_sram3_rdata,
    output [  5:0] io_sram4_addr,
    output         io_sram4_cen,
    output         io_sram4_wen,
    output [127:0] io_sram4_wmask,
    output [127:0] io_sram4_wdata,
    input  [127:0] io_sram4_rdata,
    output [  5:0] io_sram5_addr,
    output         io_sram5_cen,
    output         io_sram5_wen,
    output [127:0] io_sram5_wmask,
    output [127:0] io_sram5_wdata,
    input  [127:0] io_sram5_rdata,
    output [  5:0] io_sram6_addr,
    output         io_sram6_cen,
    output         io_sram6_wen,
    output [127:0] io_sram6_wmask,
    output [127:0] io_sram6_wdata,
    input  [127:0] io_sram6_rdata,
    output [  5:0] io_sram7_addr,
    output         io_sram7_cen,
    output         io_sram7_wen,
    output [127:0] io_sram7_wmask,
    output [127:0] io_sram7_wdata,
    input  [127:0] io_sram7_rdata
);
  /*×××××××××××××××××××××××××× PC 模块 用于选择吓一跳指令地址 ×××××××××××××××××××××××*/
  wire [`ysyx_041514_XLEN_BUS] inst_addr;
  wire [`ysyx_041514_NPC_ADDR_BUS] pc_next;  // 输出给 icache
  wire read_req;

  /*************************** 取指阶段 *************************************/
  wire [`ysyx_041514_XLEN_BUS] inst_addr_if;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_if;
  wire [`ysyx_041514_TRAP_BUS] trap_bus_if;

  //   // if ram 接口
  //   wire [`ysyx_041514_NPC_ADDR_BUS] if_read_addr;  // 地址
  //   wire if_raddr_valid;  // 地址是否准备好
  //   wire if_raddr_ready;
  //   wire [7:0] if_rmask;  // 数据掩码,读取多少位

  wire if_rdata_valid;  // 读数据是否准备好
  wire [`ysyx_041514_XLEN_BUS] if_rdata;  // 返回到读取的数据

  wire ram_stall_valid_if;
  /*************************** if/id 流水线缓存 *************************************/
  wire [`ysyx_041514_XLEN_BUS] inst_addr_if_id;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_if_id;
  wire [`ysyx_041514_TRAP_BUS] trap_bus_if_id;


  /*************************** decode 阶段 *************************************/

  /*通用寄存器译码结果：to id/ex */
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rs1_idx_id;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rs2_idx_id;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_id;
  wire [`ysyx_041514_XLEN_BUS] rs1_data_id;
  wire [`ysyx_041514_XLEN_BUS] rs2_data_id;
  wire [`ysyx_041514_IMM_LEN-1:0] imm_data_id;
  /* CSR 译码结果：to id/ex*/
  wire [`ysyx_041514_IMM_LEN-1:0] csr_imm_id;
  wire csr_imm_valid_id;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_idx_id;
  wire [`ysyx_041514_XLEN_BUS] csr_readdata_id;

  wire [`ysyx_041514_ALUOP_LEN-1:0] alu_op_id;  // alu 操作码
  wire [`ysyx_041514_MEMOP_LEN-1:0] mem_op_id;  // mem 操作码
  wire [`ysyx_041514_EXCOP_LEN-1:0] exc_op_id;  // exc 操作码
  // wire [         `ysyx_041514_PCOP_LEN-1:0 ] pc_op_id;  // pc 操作码
  wire [`ysyx_041514_CSROP_LEN-1:0] csr_op_id;  // csr 操作码

  wire [`ysyx_041514_XLEN_BUS] inst_addr_id;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_id;
  // 请求暂停流水线
  wire load_use_valid;
  /* TARP 总线 */
  wire [`ysyx_041514_TRAP_BUS] trap_bus_id;
  /*************************** id/ex 流水线缓存 *************************************/
  //   wire [    `ysyx_041514_REG_ADDRWIDTH-1:0 ] rs1_idx_id_ex;
  //   wire [    `ysyx_041514_REG_ADDRWIDTH-1:0 ] rs2_idx_id_ex;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_id_ex;
  wire [`ysyx_041514_XLEN_BUS] rs1_data_id_ex;
  wire [`ysyx_041514_XLEN_BUS] rs2_data_id_ex;
  wire [`ysyx_041514_IMM_LEN-1:0] imm_data_id_ex;
  wire [`ysyx_041514_IMM_LEN-1:0] csr_imm_id_ex;
  wire csr_imm_valid_id_ex;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_idx_id_ex;
  wire [`ysyx_041514_XLEN_BUS] csr_readdata_id_ex;
  wire [`ysyx_041514_ALUOP_LEN-1:0] alu_op_id_ex;  // alu 操作码
  wire [`ysyx_041514_MEMOP_LEN-1:0] mem_op_id_ex;  // mem 操作码
  wire [`ysyx_041514_EXCOP_LEN-1:0] exc_op_id_ex;  // exc 操作码
  // wire [         `ysyx_041514_PCOP_LEN-1:0 ] pc_op_id_ex;  // pc 操作码
  wire [`ysyx_041514_CSROP_LEN-1:0] csr_op_id_ex;  // csr 操作码
  wire [`ysyx_041514_XLEN_BUS] inst_addr_id_ex;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_id_ex;
  // wire                           id_stall_req_valid_id_ex;
  wire [`ysyx_041514_TRAP_BUS] trap_bus_id_ex;
  /*************************** ex 阶段 *************************************/

  wire [`ysyx_041514_XLEN_BUS] pc_ex;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_ex;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_ex;
  //   wire [             `ysyx_041514_XLEN_BUS]  rs1_data_ex;
  wire [`ysyx_041514_XLEN_BUS] rs2_data_ex;
  //   wire [          `ysyx_041514_IMM_LEN-1:0 ] imm_data_ex;
  //   wire [             `ysyx_041514_XLEN_BUS]  csr_data_ex;
  //   wire [          `ysyx_041514_IMM_LEN-1:0 ] csr_imm_ex;
  //   wire                                       csr_imm_valid_ex;
  wire [`ysyx_041514_MEMOP_LEN-1:0] mem_op_ex;  // 访存操作码
  //   wire [         `ysyx_041514_PCOP_LEN-1:0 ] pc_op_ex;
  wire [`ysyx_041514_XLEN_BUS] exc_alu_data_ex;  // 同时送给 ID 和 EX/MEM
  wire [`ysyx_041514_XLEN_BUS] exc_csr_data_ex;
  wire exc_csr_valid_ex;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] exc_csr_addr_ex;
  //   wire [        `ysyx_041514_EXCOP_LEN-1:0 ] exc_op_ex;  // exc 操作码
  // 请求暂停流水线
  wire jump_hazard_valid;
  wire alu_mul_div_valid;
  /* TARP 总线 */
  wire [`ysyx_041514_TRAP_BUS] trap_bus_ex;


  wire [`ysyx_041514_XLEN_BUS] branch_pc;
  wire branch_pc_valid;
  /**********************  ex/mem 流水线间缓存 **************************/


  wire [`ysyx_041514_XLEN_BUS] pc_ex_mem;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_ex_mem;
  //   wire [             `ysyx_041514_XLEN_BUS]  imm_data_ex_mem;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_ex_mem;
  //   wire [             `ysyx_041514_XLEN_BUS]  rs1_data_ex_mem;
  wire [`ysyx_041514_XLEN_BUS] rs2_data_ex_mem;
  wire [`ysyx_041514_XLEN_BUS] alu_data_ex_mem;
  wire [`ysyx_041514_XLEN_BUS] csr_writedata_ex_mem;
  wire csr_writevalid_ex_mem;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_ex_mem;
  //   wire [         `ysyx_041514_PCOP_LEN-1:0 ] pc_op_ex_mem;
  wire [`ysyx_041514_MEMOP_LEN-1:0] mem_op_ex_mem;
  /* TARP 总线 */
  wire [`ysyx_041514_TRAP_BUS] trap_bus_ex_mem;


  /**********************  访存阶段 **************************/


  /* to mem/wb */
  wire [`ysyx_041514_XLEN_BUS] pc_mem;
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_mem;
  wire [`ysyx_041514_XLEN_BUS] mem_data_mem;  //同时送回 id 阶段（bypass）
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_mem;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_mem;
  wire [`ysyx_041514_XLEN_BUS] exc_csr_data_mem;
  wire exc_csr_valid_mem;

  /* clint 接口 */
  wire [`ysyx_041514_NPC_ADDR_BUS] clint_addr;
  wire clint_valid;
  wire clint_write_valid;
  wire [`ysyx_041514_XLEN_BUS] clint_wdata;
  wire [`ysyx_041514_XLEN_BUS] clint_rdata;

  /* dcache 接口 */
  wire [`ysyx_041514_NPC_ADDR_BUS] mem_addr;  // 地址
  wire mem_addr_valid;  // 地址是否有效
  wire [7:0] mem_mask;  // 数据掩码,读取多少位
  wire [`ysyx_041514_XLEN_BUS] mem_rdata;  // 返回到读取的数据
  wire [`ysyx_041514_XLEN_BUS] mem_wdata;  // 写入的数据
  wire [3:0] mem_size;  // 数据大小
  wire mem_write_valid;  // 1'b1,表示写;1'b0 表示读 
  wire mem_data_ready;  // 读/写 数据是否准备好
  wire mem_fencei_valid;
  wire mem_fencei_ready;


  /* TARP 总线 */
  wire [`ysyx_041514_TRAP_BUS] trap_bus_mem;

  wire ram_stall_valid_mem;


  /**************** 控制模块 加 中断模块 ******************/
  wire [`ysyx_041514_XLEN-1:0] csr_mstatus_writedata;
  wire [`ysyx_041514_XLEN-1:0] csr_mepc_writedata;
  wire [`ysyx_041514_XLEN-1:0] csr_mcause_writedata;
  wire [`ysyx_041514_XLEN-1:0] csr_mtval_writedata;
  //wire [`ysyx_041514_XLEN-1:0] csr_mtvec_writedata;
  wire [`ysyx_041514_XLEN-1:0] csr_mip_writedata;
  //wire [`ysyx_041514_XLEN-1:0] csr_mie_writedata;
  wire csr_mstatus_write_valid;
  wire csr_mepc_write_valid;
  wire csr_mcause_write_valid;
  wire csr_mtval_write_valid;
  //wire csr_mtvec_write_valid;
  wire csr_mip_write_valid;
  //wire csr_mie_write_valid;
  /* 输出至取指阶段 */
  wire [`ysyx_041514_XLEN-1:0] clint_pc;
  wire clint_pc_valid;
  wire clint_pc_plus4_valid;
  reg[5:0]stall_clint;  // stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB， one bit for one stage respectively
  wire [5:0] flush_clint;


  /**********************  mem/wb 阶段 **************************/

  wire [`ysyx_041514_XLEN-1:0] csr_mstatus_writedata_mem_wb;
  wire [`ysyx_041514_XLEN-1:0] csr_mepc_writedata_mem_wb;
  wire [`ysyx_041514_XLEN-1:0] csr_mcause_writedata_mem_wb;
  wire [`ysyx_041514_XLEN-1:0] csr_mtval_writedata_mem_wb;
  //   wire [             `ysyx_041514_XLEN-1:0 ] csr_mtvec_writedata_mem_wb;
  //   wire [             `ysyx_041514_XLEN-1:0 ] csr_mie_writedata_mem_wb;
  wire [`ysyx_041514_XLEN-1:0] csr_mip_writedata_mem_wb;

  wire csr_mstatus_write_valid_mem_wb;
  wire csr_mepc_write_valid_mem_wb;
  wire csr_mcause_write_valid_mem_wb;
  wire csr_mtval_write_valid_mem_wb;
  //   wire                                       csr_mtvec_write_valid_mem_wb;
  //   wire                                       csr_mie_write_valid_mem_wb;
  wire csr_mip_write_valid_mem_wb;
  wire [`ysyx_041514_XLEN-1:0] pc_mem_wb;  //指令地址
  wire [`ysyx_041514_INST_LEN-1:0] inst_data_mem_wb;  //指令内容


  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_mem_wb;  //csr 写回地址
  wire [`ysyx_041514_XLEN_BUS] exc_csr_data_mem_wb;  //csr 写回数据
  wire exc_csr_valid_mem_wb;  // csr 写回使能
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_addr_mem_wb;  // gpr 写回使能
  wire [`ysyx_041514_XLEN-1:0] mem_data_mem_wb;  //访存阶段的数据



  //     input [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_mem_wb_i,       //csr 写回地址
  // input [             `ysyx_041514_XLEN_BUS] exc_csr_data_mem_wb_i,   //csr 写回数据
  // input                          exc_csr_valid_mem_wb_i,  // csr 写回使能
  // input [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_addr_mem_wb_i,        // gpr 写回使能
  // input [             `ysyx_041514_XLEN-1:0] mem_data_mem_wb_i,       //访存阶段的数据

  /******************** gpr 寄存器组、csr 寄存器组 ************************/

  wire [`ysyx_041514_XLEN_BUS] rs1_data_gpr;
  wire [`ysyx_041514_XLEN_BUS] rs2_data_gpr;


  /* CSR 单独引出寄存器(读) */
  wire [`ysyx_041514_XLEN-1:0] csr_mstatus_readdata_csr;
  wire [`ysyx_041514_XLEN-1:0] csr_mepc_readdata_csr;
  //   wire [`ysyx_041514_XLEN-1:0] csr_mcause_readdata_csr;
  //   wire [`ysyx_041514_XLEN-1:0] csr_mtval_readdata_csr;
  wire [`ysyx_041514_XLEN-1:0] csr_mtvec_readdata_csr;
  wire [`ysyx_041514_XLEN-1:0] csr_mie_readdata_csr;
  wire [`ysyx_041514_XLEN-1:0] csr_mip_readdata_csr;

  wire [`ysyx_041514_XLEN-1:0] csr_data_csr;



  /*****************************测试中的 cache 模块******************************/



  wire [`ysyx_041514_NPC_ADDR_BUS] ram_raddr_icache;
  wire ram_raddr_valid_icache;
  wire [7:0] ram_rmask_icache;
  wire [3:0] ram_rsize_icache;
  wire [7:0] ram_rlen_icache;
  wire ram_rdata_ready_icache;
  wire [`ysyx_041514_XLEN_BUS] ram_rdata_icache;



  /* dcache<-->mem 端口 */
  // 读端口
  wire [`ysyx_041514_NPC_ADDR_BUS] ram_raddr_dcache;
  wire ram_raddr_valid_dcache;
  wire [7:0] ram_rmask_dcache;
  wire [3:0] ram_rsize_dcache;
  wire [7:0] ram_rlen_dcache;
  wire ram_rdata_ready_dcache;
  wire [`ysyx_041514_XLEN_BUS] ram_rdata_dcache;
  // 写端口
  wire [`ysyx_041514_NPC_ADDR_BUS] ram_waddr_dcache;  // 地址
  wire ram_waddr_valid_dcache;  // 地址是否准备好
  wire [7:0] ram_wmask_dcache;  // 数据掩码,写入多少位
  wire ram_wdata_ready_dcache;  // 数据是否已经写入
  wire [`ysyx_041514_XLEN_BUS] ram_wdata_dcache;  // 写入的数据
  wire [3:0] ram_wsize_dcache;
  wire [7:0] ram_wlen_dcache;


  /***********************************测试中的 AXI4 总线接口***************************************/
  /* arb<-->axi */
  // 读通道
  wire [`ysyx_041514_NPC_ADDR_BUS] arb_read_addr;
  wire arb_raddr_valid;  // 是否发起读请求
  wire [7:0] arb_rmask;  // 数据掩码
  wire [3:0] arb_rsize;
  wire [7:0] arb_rlen;
  wire [`ysyx_041514_XLEN_BUS] arb_rdata;  // 读数据返回mem
  wire arb_rdata_ready;  // 读数据是否有效
  wire arb_rlast;
  //写通道
  wire [`ysyx_041514_NPC_ADDR_BUS] arb_write_addr;  // mem 阶段的 write
  wire arb_write_valid;
  wire [7:0] arb_wmask;
  wire [`ysyx_041514_XLEN_BUS] arb_wdata;
  wire [3:0] arb_wsize;
  wire [7:0] arb_wlen;
  wire arb_wdata_ready;  // 数据是否已经写入


  /********************** 各种数据缓存  ***********************/
  /* 乘法器数据缓存 */
  wire [`ysyx_041514_XLEN_BUS] alu_data = exc_alu_data_ex;
  wire alu_data_ready;
  wire alu_data_buff_valid;
  wire [`ysyx_041514_XLEN_BUS] alu_data_buff;


  wire rdata_buff_valid;
  wire [`ysyx_041514_XLEN_BUS] rdata_buff;

  /* fencei ready 缓存 */
  //wire  mem_fencei_ready_i,
  wire mem_fencei_ready_buff;
  wire mem_fencei_buff_valid;

  ysyx_041514_pc_reg u_pc_reg (
      .clk                   (clk),
      .rst                   (rst),
      .stall_valid_i         (stall_clint),
      .flush_valid_i         (flush_clint),
      .branch_pc_i           (branch_pc),
      .branch_pc_valid_i     (branch_pc_valid),
      .clint_pc_i            (clint_pc),              //trap pc,来自mem
      .clint_pc_valid_i      (clint_pc_valid),        //trap pc valide,来自mem
      .clint_pc_plus4_valid_o(clint_pc_plus4_valid),
      .read_req_o            (read_req),
      //.if_rdata_valid_i (if_rdata_valid),
      .pc_next_o             (pc_next),               //输出 next_pc
      .pc_o                  (inst_addr)
  );
  ysyx_041514_fetch u_fetch (
      //指令地址
      //   .rst        (rst),
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



  ysyx_041514_if_id u_if_id (
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


  ysyx_041514_dcode u_dcode (
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
      // .pc_op_o(pc_op_id),
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

  ysyx_041514_id_ex u_id_ex (
      .clk                  (clk),
      .rst                  (rst),
      .flush_valid_i        (flush_clint),
      .stall_valid_i        (stall_clint),
      /* 输入 */
      .pc_id_ex_i           (inst_addr_id),
      .inst_data_id_ex_i    (inst_data_id),
      //   .rs1_idx_id_ex_i      (rs1_idx_id),
      //   .rs2_idx_id_ex_i      (rs2_idx_id),
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
      // .pc_op_id_ex_i        (pc_op_id),
      // pc 操作码
      .csr_op_id_ex_i       (csr_op_id),
      // csr 操作码
      /* TARP 总线 */
      .trap_bus_id_ex_i     (trap_bus_id),
      /* 输出 */
      .pc_id_ex_o           (inst_addr_id_ex),
      .inst_data_id_ex_o    (inst_data_id_ex),
      //   .rs1_idx_id_ex_o      (rs1_idx_id_ex),
      //   .rs2_idx_id_ex_o      (rs2_idx_id_ex),
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
      // .pc_op_id_ex_o        (pc_op_id_ex),
      // pc 操作码
      .csr_op_id_ex_o       (csr_op_id_ex),
      // csr 操作码
      /* TARP 总线 */
      .trap_bus_id_ex_o     (trap_bus_id_ex)
  );


  ysyx_041514_execute_top u_execute_top (
      .clk            (clk),
      .rst            (rst),
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
      // .pc_op_i        (pc_op_id_ex),
      /* TARP 总线 */
      .trap_bus_i     (trap_bus_id_ex),
      /********************** to ex/mem **************************/
      // pc
      .pc_o           (pc_ex),
      .inst_data_o    (inst_data_ex),
      // gpr 译码结果
      .rd_idx_o       (rd_idx_ex),
      // .rs1_data_o     (rs1_data_ex),
      .rs2_data_o     (rs2_data_ex),
      // .imm_data_o     (imm_data_ex),
      // CSR 译码结果 
      // .csr_data_o     (csr_data_ex),
      // .csr_imm_o      (csr_imm_ex),
      // .csr_imm_valid_o(csr_imm_valid_ex),
      .mem_op_o       (mem_op_ex),
      // 访存操作码
      // .pc_op_o        (pc_op_ex),
      .exc_alu_data_o (exc_alu_data_ex),
      // 同时送给 ID 和 EX/MEM
      .exc_csr_data_o (exc_csr_data_ex),
      .exc_csr_valid_o(exc_csr_valid_ex),
      .exc_csr_addr_o (exc_csr_addr_ex),
      /************************to id *************************************/
      // .exc_op_o       (exc_op_ex),
      // exc 操作码

      /********************* from data_buff *******************/
      // ALU结果缓存
      .alu_data_buff_valid_i(alu_data_buff_valid),
      .alu_data_buff_i(alu_data_buff),
      .alu_data_ready_o(alu_data_ready),

      // 请求暂停流水线
      .jump_hazard_valid_o(jump_hazard_valid),
      .alu_mul_div_valid_o(alu_mul_div_valid),
      .branch_pc_o        (branch_pc),
      .branch_pc_valid_o  (branch_pc_valid),
      /* TARP 总线 */
      .trap_bus_o         (trap_bus_ex)
  );

  ysyx_041514_ex_mem u_ex_mem (
      .clk                    (clk),
      .rst                    (rst),
      .flush_valid_i          (flush_clint),
      .stall_valid_i          (stall_clint),
      .pc_ex_mem_i            (pc_ex),
      .inst_data_ex_mem_i     (inst_data_ex),
      //   .imm_data_ex_mem_i      (imm_data_ex),
      .rd_idx_ex_mem_i        (rd_idx_ex),
      //   .rs1_data_ex_mem_i      (rs1_data_ex),
      .rs2_data_ex_mem_i      (rs2_data_ex),
      .alu_data_ex_mem_i      (exc_alu_data_ex),
      .csr_writedata_ex_mem_i (exc_csr_data_ex),
      .csr_writevalid_ex_mem_i(exc_csr_valid_ex),
      .csr_addr_ex_mem_i      (exc_csr_addr_ex),
      //   .pc_op_ex_mem_i         (pc_op_ex),
      .mem_op_ex_mem_i        (mem_op_ex),
      /* TARP 总线 */
      .trap_bus_ex_mem_i      (trap_bus_ex),
      .pc_ex_mem_o            (pc_ex_mem),
      .inst_data_ex_mem_o     (inst_data_ex_mem),
      //   .imm_data_ex_mem_o      (imm_data_ex_mem),
      .rd_idx_ex_mem_o        (rd_idx_ex_mem),
      //   .rs1_data_ex_mem_o      (rs1_data_ex_mem),
      .rs2_data_ex_mem_o      (rs2_data_ex_mem),
      .alu_data_ex_mem_o      (alu_data_ex_mem),
      .csr_writedata_ex_mem_o (csr_writedata_ex_mem),
      .csr_writevalid_ex_mem_o(csr_writevalid_ex_mem),
      .csr_addr_ex_mem_o      (csr_addr_ex_mem),
      //   .pc_op_ex_mem_o         (pc_op_ex_mem),
      .mem_op_ex_mem_o        (mem_op_ex_mem),
      /* TARP 总线 */
      .trap_bus_ex_mem_o      (trap_bus_ex_mem)
  );


  ysyx_041514_memory u_memory (
      //TODO:TEST
      .rdata_buff_valid_i(rdata_buff_valid),
      .rdata_buff_i(rdata_buff),
      .mem_fencei_ready_buff_i(mem_fencei_ready_buff),
      .mem_fencei_buff_valid_i(mem_fencei_buff_valid),
      /* from ex/mem */
      .pc_i(pc_ex_mem),
      .inst_data_i(inst_data_ex_mem),
      .rd_idx_i(rd_idx_ex_mem),
      // input  [         `ysyx_041514_XLEN_BUS] rs1_data_i,
      .rs2_data_i(rs2_data_ex_mem),
      // input  [      `ysyx_041514_IMM_LEN-1:0] imm_data_i,
      .mem_op_i(mem_op_ex_mem),  // 访存操作码
      .exc_alu_data_i(alu_data_ex_mem),
      .csr_addr_i(csr_addr_ex_mem),
      .exc_csr_data_i(csr_writedata_ex_mem),
      .exc_csr_valid_i(csr_writevalid_ex_mem),
      /* clint 接口 */
      .clint_addr_o(clint_addr),
      .clint_valid_o(clint_valid),
      .clint_write_valid_o(clint_write_valid),
      .clint_wdata_o(clint_wdata),
      .clint_rdata_i(clint_rdata),
      /* dcache 接口 */
      .mem_addr_o(mem_addr),
      .mem_addr_valid_o(mem_addr_valid),
      .mem_mask_o(mem_mask),
      .mem_write_valid_o(mem_write_valid),
      .mem_data_ready_i(mem_data_ready),
      .mem_rdata_i(mem_rdata),
      .mem_wdata_o(mem_wdata),
      .mem_size_o(mem_size),  // 数据宽度 8、4、2、1 byte
      .mem_fencei_valid_o(mem_fencei_valid),
      .mem_fencei_ready_i(mem_fencei_ready),
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





  ysyx_041514_clint u_clint (
      .clk(clk),
      .rst(rst),
      .pc_from_mem_i(pc_ex_mem),
      .pc_from_exe_i(pc_ex),
      .inst_data_i(inst_data_ex_mem),
      /* 各级流水线的 stall 请求 */
      .load_use_valid_id_i(load_use_valid),  //load-use data hazard from id
      .jump_valid_ex_i(jump_hazard_valid),  // branch hazard from ex
      .alu_mul_div_valid_ex_i(alu_mul_div_valid),
      .ram_stall_valid_if_i(ram_stall_valid_if),
      .ram_stall_valid_mem_i(ram_stall_valid_mem),

      /* clint 接口 */
      .clint_addr_i       (clint_addr),
      .clint_valid_i      (clint_valid),
      .clint_write_valid_i(clint_write_valid),
      .clint_wdata_i      (clint_wdata),
      .clint_rdata_o      (clint_rdata),

      /* TARP 总线 */
      .trap_bus_i(trap_bus_mem),  // 包括 取指，译码，执行，访存 阶段的 trap 请求
      /* trap 所需寄存器，来自于 csr (读)*/
      .csr_mstatus_readdata_i(csr_mstatus_readdata_csr),
      .csr_mepc_readdata_i(csr_mepc_readdata_csr),
      //   .csr_mcause_readdata_i(csr_mcause_readdata_csr),
      //   .csr_mtval_readdata_i(csr_mtval_readdata_csr),
      .csr_mtvec_readdata_i(csr_mtvec_readdata_csr),
      .csr_mie_readdata_i(csr_mie_readdata_csr),
      .csr_mip_readdata_i(csr_mip_readdata_csr),
      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_o(csr_mstatus_writedata),
      .csr_mepc_writedata_o(csr_mepc_writedata),
      .csr_mcause_writedata_o(csr_mcause_writedata),
      .csr_mtval_writedata_o(csr_mtval_writedata),
      //   .csr_mtvec_writedata_o(csr_mtvec_writedata),
      //   .csr_mie_writedata_o(csr_mie_writedata),
      .csr_mip_writedata_o(csr_mip_writedata),

      .csr_mstatus_write_valid_o(csr_mstatus_write_valid),
      .csr_mepc_write_valid_o(csr_mepc_write_valid),
      .csr_mcause_write_valid_o(csr_mcause_write_valid),
      .csr_mtval_write_valid_o(csr_mtval_write_valid),
      //   .csr_mtvec_write_valid_o(csr_mtvec_write_valid),
      //   .csr_mie_write_valid_o(csr_mie_write_valid),
      .csr_mip_write_valid_o(csr_mip_write_valid),
      /* 输出至取指阶段 */
      .clint_pc_o(clint_pc),  // trap pc
      .clint_pc_valid_o(clint_pc_valid),  // trap pc valid
      .clint_pc_plus4_valid_o(clint_pc_plus4_valid),
      .stall_o(stall_clint),
      .flush_o(flush_clint)
  );




  ysyx_041514_mem_wb u_mem_wb (
      .clk                           (clk),
      .rst                           (rst),
      .flush_valid_i                 (flush_clint),
      .stall_valid_i                 (stall_clint),
      //   // TODO:TSET
      //   .mem_data_ready_i              (mem_data_ready),
      //   .rdata_buff_valid_o            (rdata_buff_valid),
      //   .rdata_buff_o                  (rdata_buff),
      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_mem_wb_i(csr_mstatus_writedata),
      .csr_mepc_writedata_mem_wb_i   (csr_mepc_writedata),
      .csr_mcause_writedata_mem_wb_i (csr_mcause_writedata),
      .csr_mtval_writedata_mem_wb_i  (csr_mtval_writedata),
      //.csr_mtvec_writedata_mem_wb_i  (csr_mtvec_writedata),
      //.csr_mie_writedata_mem_wb_i    (csr_mie_writedata),
      .csr_mip_writedata_mem_wb_i    (csr_mip_writedata),

      .csr_mstatus_write_valid_mem_wb_i(csr_mstatus_write_valid),
      .csr_mepc_write_valid_mem_wb_i   (csr_mepc_write_valid),
      .csr_mcause_write_valid_mem_wb_i (csr_mcause_write_valid),
      .csr_mtval_write_valid_mem_wb_i  (csr_mtval_write_valid),
      //.csr_mtvec_write_valid_mem_wb_i  (csr_mtvec_write_valid),
      //.csr_mie_write_valid_mem_wb_i  (csr_mie_write_valid),
      .csr_mip_write_valid_mem_wb_i  (csr_mip_write_valid),

      .pc_mem_wb_i           (pc_mem),
      .inst_data_mem_wb_i    (inst_data_mem),
      .csr_addr_mem_wb_i     (csr_addr_mem),
      .exc_csr_data_mem_wb_i (exc_csr_data_mem),
      .exc_csr_valid_mem_wb_i(exc_csr_valid_mem),
      .rd_addr_mem_wb_i      (rd_idx_mem),
      .mem_data_mem_wb_i     (mem_data_mem),

      /* trap 所需寄存器，来自于 csr (写)*/
      .csr_mstatus_writedata_mem_wb_o(csr_mstatus_writedata_mem_wb),
      .csr_mepc_writedata_mem_wb_o(csr_mepc_writedata_mem_wb),
      .csr_mcause_writedata_mem_wb_o(csr_mcause_writedata_mem_wb),
      .csr_mtval_writedata_mem_wb_o(csr_mtval_writedata_mem_wb),
      //   .csr_mtvec_writedata_mem_wb_o(csr_mtvec_writedata_mem_wb),
      //   .csr_mie_writedata_mem_wb_o(csr_mie_writedata_mem_wb),
      .csr_mip_writedata_mem_wb_o(csr_mip_writedata_mem_wb),

      .csr_mstatus_write_valid_mem_wb_o(csr_mstatus_write_valid_mem_wb),
      .csr_mepc_write_valid_mem_wb_o(csr_mepc_write_valid_mem_wb),
      .csr_mcause_write_valid_mem_wb_o(csr_mcause_write_valid_mem_wb),
      .csr_mtval_write_valid_mem_wb_o(csr_mtval_write_valid_mem_wb),
      //   .csr_mtvec_write_valid_mem_wb_o(csr_mtvec_write_valid_mem_wb),
      //   .csr_mie_write_valid_mem_wb_o(csr_mie_write_valid_mem_wb),
      .csr_mip_write_valid_mem_wb_o(csr_mip_write_valid_mem_wb),

      .pc_mem_wb_o(pc_mem_wb),
      .inst_data_mem_wb_o(inst_data_mem_wb),
      .csr_addr_mem_wb_o(csr_addr_mem_wb),
      .exc_csr_data_mem_wb_o(exc_csr_data_mem_wb),
      .exc_csr_valid_mem_wb_o(exc_csr_valid_mem_wb),
      .rd_addr_mem_wb_o(rd_addr_mem_wb),
      .mem_data_mem_wb_o(mem_data_mem_wb)

  );



  /***************************写回阶段***********************************/
`ifndef ysyx_041514_YSYX_SOC
  ysyx_041514_writeback u_writeback (
      .clk           (clk),
      //   .rst           (rst),
      .pc_wb_i       (pc_mem_wb),
      .inst_data_wb_i(inst_data_mem_wb)

  );
`endif



  ysyx_041514_rv64_gpr_regfile u_rv64_gpr_regfile (
      .clk               (clk),
      .rst               (rst),
      /* 读取数据 */
      .rs1_idx_i         (rs1_idx_id),
      .rs2_idx_i         (rs2_idx_id),
      .rs1_data_o        (rs1_data_gpr),
      .rs2_data_o        (rs2_data_gpr),     //TODO 添加 valid 信号
      /* 写数据 */
      .write_idx_i       (rd_addr_mem_wb),
      .write_data_i      (mem_data_mem_wb),
      .write_data_valid_i(1'b1)
  );




  ysyx_041514_rv64_csr_regfile u_rv64_csr_regfile (
      .clk                    (clk),
      .rst                    (rst),
      /* 单独引出寄存器(写) */
      .csr_mstatus_writedata_i(csr_mstatus_writedata_mem_wb),
      .csr_mepc_writedata_i   (csr_mepc_writedata_mem_wb),
      .csr_mcause_writedata_i (csr_mcause_writedata_mem_wb),
      .csr_mtval_writedata_i  (csr_mtval_writedata_mem_wb),
      //   .csr_mtvec_writedata_i  (csr_mtvec_writedata_mem_wb),
      //   .csr_mie_writedata_i    (csr_mie_writedata_mem_wb),
      .csr_mip_writedata_i    (csr_mip_writedata_mem_wb),

      .csr_mstatus_write_valid_i(csr_mstatus_write_valid_mem_wb),
      .csr_mepc_write_valid_i   (csr_mepc_write_valid_mem_wb),
      .csr_mcause_write_valid_i (csr_mcause_write_valid_mem_wb),
      .csr_mtval_write_valid_i  (csr_mtval_write_valid_mem_wb),
      //   .csr_mtvec_write_valid_i  (csr_mtvec_write_valid_mem_wb),
      //   .csr_mie_write_valid_i    (csr_mie_write_valid_mem_wb),
      .csr_mip_write_valid_i    (csr_mip_write_valid_mem_wb),
      /* 单独引出寄存器(读) */
      .csr_mstatus_readdata_o   (csr_mstatus_readdata_csr),
      .csr_mepc_readdata_o      (csr_mepc_readdata_csr),
      //   .csr_mcause_readdata_o    (csr_mcause_readdata_csr),
      //   .csr_mtval_readdata_o     (csr_mtval_readdata_csr),
      .csr_mtvec_readdata_o     (csr_mtvec_readdata_csr),
      .csr_mie_readdata_o       (csr_mie_readdata_csr),
      .csr_mip_readdata_o       (csr_mip_readdata_csr),
      /* 读取数据端口 */
      .csr_readaddr_i           (csr_idx_id),
      .csr_readdata_o           (csr_data_csr),                    //TODO 添加 valid
      /* 写入数据端口 */
      .csr_writeaddr_i          (csr_addr_mem_wb),
      .csr_write_valid_i        (exc_csr_valid_mem_wb),
      .csr_writedata_i          (exc_csr_data_mem_wb)
  );




  ysyx_041514_icache_top u_icache_top (
      .clk(clk),
      .rst(rst),
      /* cpu<-->cache 端口 */
      .preif_raddr_i(pc_next[31:0]),  // CPU 的访存信息 
      .preif_rmask_i(8'b0000_1111),  // 访存掩码
      .preif_raddr_valid_i(read_req),  // 地址是否有效，无效时，停止访问 cache
      .if_rdata_o(if_rdata),  // icache 返回读数据
      .if_rdata_valid_o          (if_rdata_valid),// icache 读数据是否准备好(未准备好需要暂停流水线)
      .mem_fencei_valid_i(mem_fencei_valid),
      /* cache<-->mem 端口 */
      .ram_raddr_icache_o(ram_raddr_icache),
      .ram_raddr_valid_icache_o(ram_raddr_valid_icache),
      .ram_rmask_icache_o(ram_rmask_icache),
      .ram_rsize_icache_o(ram_rsize_icache),
      .ram_rlen_icache_o(ram_rlen_icache),
      .ram_rdata_ready_icache_i(ram_rdata_ready_icache),
      .ram_rdata_icache_i(ram_rdata_icache),
      /* sram */
      .io_sram4_addr(io_sram4_addr),
      .io_sram4_cen(io_sram4_cen),
      .io_sram4_wen(io_sram4_wen),
      .io_sram4_wmask(io_sram4_wmask),
      .io_sram4_wdata(io_sram4_wdata),
      .io_sram4_rdata(io_sram4_rdata),
      .io_sram5_addr(io_sram5_addr),
      .io_sram5_cen(io_sram5_cen),
      .io_sram5_wen(io_sram5_wen),
      .io_sram5_wmask(io_sram5_wmask),
      .io_sram5_wdata(io_sram5_wdata),
      .io_sram5_rdata(io_sram5_rdata),
      .io_sram6_addr(io_sram6_addr),
      .io_sram6_cen(io_sram6_cen),
      .io_sram6_wen(io_sram6_wen),
      .io_sram6_wmask(io_sram6_wmask),
      .io_sram6_wdata(io_sram6_wdata),
      .io_sram6_rdata(io_sram6_rdata),
      .io_sram7_addr(io_sram7_addr),
      .io_sram7_cen(io_sram7_cen),
      .io_sram7_wen(io_sram7_wen),
      .io_sram7_wmask(io_sram7_wmask),
      .io_sram7_wdata(io_sram7_wdata),
      .io_sram7_rdata(io_sram7_rdata)
  );




  ysyx_041514_dcache_top u_dcache_top (
      .clk(clk),
      .rst(rst),
      .mem_fencei_valid_i(mem_fencei_valid),
      .mem_fencei_ready_o(mem_fencei_ready),
      /* cpu<-->cache 端口 */
      .mem_addr_i(mem_addr),  // CPU 的访存信息 
      .mem_mask_i(mem_mask),  // 访存掩码
      .mem_addr_valid_i  (mem_addr_valid),    // 地址是否有效，无效时，���止访问 cache
      .mem_write_valid_i(mem_write_valid),  // 1'b1,表示写;1'b0 表示读 
      .mem_wdata_i(mem_wdata),  // 写数据
      .mem_rdata_o(mem_rdata),  // dcache 返回读数据
      .mem_data_ready_o(mem_data_ready),
      .mem_size_i(mem_size),
      // dcache 读数据是否准备好(未准备好需要暂停流水线)

      /* cache<-->mem 端口 */
      // 读端口
      .ram_raddr_dcache_o(ram_raddr_dcache),
      .ram_raddr_valid_dcache_o(ram_raddr_valid_dcache),
      .ram_rmask_dcache_o(ram_rmask_dcache),
      .ram_rdata_ready_dcache_i(ram_rdata_ready_dcache),
      .ram_rdata_dcache_i(ram_rdata_dcache),
      .ram_rsize_dcache_o(ram_rsize_dcache),
      .ram_rlen_dcache_o(ram_rlen_dcache),
      // 写端口
      .ram_waddr_dcache_o(ram_waddr_dcache),  // 地址
      .ram_waddr_valid_dcache_o(ram_waddr_valid_dcache),  // 地址是否准备好
      .ram_wmask_dcache_o(ram_wmask_dcache),  // 数据掩码,写入多少位
      .ram_wsize_dcache_o(ram_wsize_dcache),
      .ram_wlen_dcache_o(ram_wlen_dcache),
      .ram_wdata_ready_dcache_i(ram_wdata_ready_dcache),// 数据是否已经写入// 写入的数据
      .ram_wdata_dcache_o(ram_wdata_dcache),

      /* sram */
      .io_sram0_addr (io_sram0_addr),
      .io_sram0_cen  (io_sram0_cen),
      .io_sram0_wen  (io_sram0_wen),
      .io_sram0_wmask(io_sram0_wmask),
      .io_sram0_wdata(io_sram0_wdata),
      .io_sram0_rdata(io_sram0_rdata),
      .io_sram1_addr (io_sram1_addr),
      .io_sram1_cen  (io_sram1_cen),
      .io_sram1_wen  (io_sram1_wen),
      .io_sram1_wmask(io_sram1_wmask),
      .io_sram1_wdata(io_sram1_wdata),
      .io_sram1_rdata(io_sram1_rdata),
      .io_sram2_addr (io_sram2_addr),
      .io_sram2_cen  (io_sram2_cen),
      .io_sram2_wen  (io_sram2_wen),
      .io_sram2_wmask(io_sram2_wmask),
      .io_sram2_wdata(io_sram2_wdata),
      .io_sram2_rdata(io_sram2_rdata),
      .io_sram3_addr (io_sram3_addr),
      .io_sram3_cen  (io_sram3_cen),
      .io_sram3_wen  (io_sram3_wen),
      .io_sram3_wmask(io_sram3_wmask),
      .io_sram3_wdata(io_sram3_wdata),
      .io_sram3_rdata(io_sram3_rdata)
  );



  ysyx_041514_axi_arb u_axi_arb (
      .clk(clk),
      .rst(rst),

      /* if 访存请求端口（读）*/
      .if_read_addr_i(ram_raddr_icache),  // if 阶段的 read
      .if_raddr_valid_i(ram_raddr_valid_icache),  // 是否发起读请求
      .if_rmask_i(ram_rmask_icache),  // 数据掩码
      .if_rsize_i(ram_rsize_icache),
      .if_rlen_i(ram_rlen_icache),
      .if_rdata_o(ram_rdata_icache),  // 读数据返回mem
      .if_rdata_ready_o (ram_rdata_ready_icache),// 读数据是否有效// mem 访存请求端口（读）
      /* mem 访存请求端口（读）*/
      .mem_read_addr_i(ram_raddr_dcache),
      .mem_raddr_valid_i(ram_raddr_valid_dcache),
      .mem_rmask_i(ram_rmask_dcache),
      .mem_rsize_i(ram_rsize_dcache),
      .mem_rlen_i(ram_rlen_dcache),
      .mem_rdata_o(ram_rdata_dcache),
      .mem_rdata_ready_o(ram_rdata_ready_dcache),
      /* mem 访存接口（写）*/
      .mem_write_addr_i(ram_waddr_dcache),  // mem 阶段的 write
      .mem_write_valid_i(ram_waddr_valid_dcache),
      .mem_wmask_i(ram_wmask_dcache),
      .mem_wdata_i(ram_wdata_dcache),
      .mem_wsize_i(ram_wsize_dcache),
      .mem_wlen_i(ram_wlen_dcache),
      .mem_wdata_ready_o(ram_wdata_ready_dcache),  // 数据是否已经写入

      /* arb<-->axi */
      // 读通道
      .arb_read_addr_o  (arb_read_addr),
      .arb_raddr_valid_o(arb_raddr_valid),  // 是否发起读请求
      .arb_rmask_o      (arb_rmask),        // 数据掩码
      .arb_rsize_o      (arb_rsize),
      .arb_rlen_o       (arb_rlen),
      .arb_rdata_i      (arb_rdata),        // 读数据返回mem
      .arb_rdata_ready_i(arb_rdata_ready),  // 读数据是否有效
      .arb_rlast_i      (arb_rlast),
      //写通道
      .arb_write_addr_o (arb_write_addr),   // mem 阶段的 write
      .arb_write_valid_o(arb_write_valid),
      .arb_wmask_o      (arb_wmask),
      .arb_wdata_o      (arb_wdata),        // 数据是否已经写入
      .arb_wsize_o      (arb_wsize),
      .arb_wlen_o       (arb_wlen),
      .arb_wdata_ready_i(arb_wdata_ready)
  );


  /* 未使用到的信号 */
  wire [2:0] io_master_awprot;
  wire io_master_awuser;
  wire io_master_awlock;
  wire [3:0] io_master_awcache;
  wire [3:0] io_master_awqos;
  wire [3:0] io_master_awregion;
  wire io_master_wuser;
  wire io_master_buser = 0;
  wire [2:0] io_master_arprot;
  wire io_master_aruser;
  wire io_master_arlock;
  wire [3:0] io_master_arcache;
  wire [3:0] io_master_arqos;
  wire [3:0] io_master_arregion;
  wire io_master_ruser = 0;

  ysyx_041514_axi_rw #(
      .RW_DATA_WIDTH (64),
      .RW_ADDR_WIDTH (32),
      .AXI_DATA_WIDTH(64),
      .AXI_ADDR_WIDTH(32),
      .AXI_ID_WIDTH  (4),
      .AXI_STRB_WIDTH(8),
      .AXI_USER_WIDTH(1)
  ) u_axi_rw (
      .clock            (clk),
      .reset            (rst),
      /* arb<-->axi */
      // 读通道
      .arb_read_addr_i  (arb_read_addr),
      .arb_raddr_valid_i(arb_raddr_valid),  // 是否发起读请求
      .arb_rmask_i      (arb_rmask),        // 数据掩码
      .arb_rsize_i      (arb_rsize),
      .arb_rlen_i       (arb_rlen),
      .arb_rdata_o      (arb_rdata),        // 读数据返回mem
      .arb_rdata_ready_o(arb_rdata_ready),  // 读数据是否有效//写通道
      .arb_rlast_o      (arb_rlast),
      // 写通道
      .arb_write_addr_i (arb_write_addr),   // mem 阶段的 write
      .arb_write_valid_i(arb_write_valid),
      .arb_wmask_i      (arb_wmask),
      .arb_wdata_i      (arb_wdata),
      .arb_wsize_i      (arb_wsize),
      .arb_wlen_i       (arb_wlen),
      .arb_wdata_ready_o(arb_wdata_ready),  // 数据是否已经写���

      /* axi master */
      // Advanced eXtensible Interface
      // 写地址
      .axi_aw_ready_i (io_master_awready),
      .axi_aw_valid_o (io_master_awvalid),
      .axi_aw_addr_o  (io_master_awaddr),
      .axi_aw_prot_o  (io_master_awprot),
      .axi_aw_id_o    (io_master_awid),
      .axi_aw_user_o  (io_master_awuser),
      .axi_aw_len_o   (io_master_awlen),
      .axi_aw_size_o  (io_master_awsize),
      .axi_aw_burst_o (io_master_awburst),
      .axi_aw_lock_o  (io_master_awlock),
      .axi_aw_cache_o (io_master_awcache),
      .axi_aw_qos_o   (io_master_awqos),
      .axi_aw_region_o(io_master_awregion),
      //写数据
      .axi_w_ready_i  (io_master_wready),
      .axi_w_valid_o  (io_master_wvalid),
      .axi_w_data_o   (io_master_wdata),
      .axi_w_strb_o   (io_master_wstrb),
      .axi_w_last_o   (io_master_wlast),
      .axi_w_user_o   (io_master_wuser),
      //写响应
      .axi_b_ready_o  (io_master_bready),
      .axi_b_valid_i  (io_master_bvalid),
      .axi_b_resp_i   (io_master_bresp),
      .axi_b_id_i     (io_master_bid),
      .axi_b_user_i   (io_master_buser),
      //读地址
      .axi_ar_ready_i (io_master_arready),
      .axi_ar_valid_o (io_master_arvalid),
      .axi_ar_addr_o  (io_master_araddr),
      .axi_ar_prot_o  (io_master_arprot),
      .axi_ar_id_o    (io_master_arid),
      .axi_ar_user_o  (io_master_aruser),
      .axi_ar_len_o   (io_master_arlen),
      .axi_ar_size_o  (io_master_arsize),
      .axi_ar_burst_o (io_master_arburst),
      .axi_ar_lock_o  (io_master_arlock),
      .axi_ar_cache_o (io_master_arcache),
      .axi_ar_qos_o   (io_master_arqos),
      .axi_ar_region_o(io_master_arregion),
      //读数据
      .axi_r_ready_o  (io_master_rready),
      .axi_r_valid_i  (io_master_rvalid),
      .axi_r_resp_i   (io_master_rresp),
      .axi_r_data_i   (io_master_rdata),
      .axi_r_last_i   (io_master_rlast),
      .axi_r_id_i     (io_master_rid),
      .axi_r_user_i   (io_master_ruser)
  );


  ysyx_041514_data_buff u_data_buff (
      .clk                    (clk),
      .rst                    (rst),
      .flush_i                (flush_clint),
      .stall_i                (stall_clint),
      /* 乘法器数据缓存 */
      .alu_data_i             (alu_data),
      .alu_data_ready_i       (alu_data_ready),
      .alu_data_buff_valid_o  (alu_data_buff_valid),
      .alu_data_buff_o        (alu_data_buff),
      /* fencei ready 缓存 */
      .mem_fencei_ready_i     (mem_fencei_ready),
      .mem_fencei_ready_buff_o(mem_fencei_ready_buff),
      .mem_fencei_buff_valid_o(mem_fencei_buff_valid),
      /* mem load 数据缓存 */
      .mem_data_mem_i         (mem_data_mem),
      .mem_data_ready_i       (mem_data_ready),
      .rdata_buff_valid_o     (rdata_buff_valid),
      .rdata_buff_o           (rdata_buff)
  );

endmodule

