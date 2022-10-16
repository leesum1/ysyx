`include "sysconfig.v"

module ysyx_041514_mem_wb (
    input clk,
    input rst,
    input [5:0] flush_valid_i,
    input [5:0] stall_valid_i,


    // input [    `ysyx_041514_XLEN_BUS] pc_mem_wb_i,
    // input [`ysyx_041514_INST_LEN-1:0] inst_data_mem_wb_i,
    /* trap 所需寄存器，来自于 csr (写)*/
    input [`ysyx_041514_XLEN-1:0] csr_mstatus_writedata_mem_wb_i,
    input [`ysyx_041514_XLEN-1:0] csr_mepc_writedata_mem_wb_i,
    input [`ysyx_041514_XLEN-1:0] csr_mcause_writedata_mem_wb_i,
    input [`ysyx_041514_XLEN-1:0] csr_mtval_writedata_mem_wb_i,
    // input [`ysyx_041514_XLEN-1:0] csr_mtvec_writedata_mem_wb_i,
    // input [`ysyx_041514_XLEN-1:0] csr_mie_writedata_mem_wb_i,
    input [`ysyx_041514_XLEN-1:0] csr_mip_writedata_mem_wb_i,

    input                             csr_mstatus_write_valid_mem_wb_i,
    input                             csr_mepc_write_valid_mem_wb_i,
    input                             csr_mcause_write_valid_mem_wb_i,
    input                             csr_mtval_write_valid_mem_wb_i,
    // input                             csr_mtvec_write_valid_mem_wb_i,
    // input                             csr_mie_write_valid_mem_wb_i,
    input                             csr_mip_write_valid_mem_wb_i,
    input [    `ysyx_041514_XLEN-1:0] pc_mem_wb_i,                       //指令地址
    input [`ysyx_041514_INST_LEN-1:0] inst_data_mem_wb_i,                //指令内容


    input [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_mem_wb_i,       //csr 写回地址
    input [             `ysyx_041514_XLEN_BUS] exc_csr_data_mem_wb_i,   //csr 写回数据
    input                                      exc_csr_valid_mem_wb_i,  // csr 写回使能
    input [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_addr_mem_wb_i,        // gpr 写回使能
    input [             `ysyx_041514_XLEN-1:0] mem_data_mem_wb_i,       //访存阶段的数据

    /* trap 所需寄存器，来自于 csr (写)*/
    output [`ysyx_041514_XLEN-1:0] csr_mstatus_writedata_mem_wb_o,
    output [`ysyx_041514_XLEN-1:0] csr_mepc_writedata_mem_wb_o,
    output [`ysyx_041514_XLEN-1:0] csr_mcause_writedata_mem_wb_o,
    output [`ysyx_041514_XLEN-1:0] csr_mtval_writedata_mem_wb_o,
    // output [`ysyx_041514_XLEN-1:0] csr_mtvec_writedata_mem_wb_o,
    // output [`ysyx_041514_XLEN-1:0] csr_mie_writedata_mem_wb_o,
    output [`ysyx_041514_XLEN-1:0] csr_mip_writedata_mem_wb_o,

    output csr_mstatus_write_valid_mem_wb_o,
    output csr_mepc_write_valid_mem_wb_o,
    output csr_mcause_write_valid_mem_wb_o,
    output csr_mtval_write_valid_mem_wb_o,
    // output csr_mtvec_write_valid_mem_wb_o,
    // output csr_mie_write_valid_mem_wb_o,
    output csr_mip_write_valid_mem_wb_o,

    output [`ysyx_041514_XLEN-1:0] pc_mem_wb_o,  //指令地址
    output [`ysyx_041514_INST_LEN-1:0] inst_data_mem_wb_o,  //指令内容

    output [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_mem_wb_o,       //csr 写回地址
    output [             `ysyx_041514_XLEN_BUS] exc_csr_data_mem_wb_o,   //csr 写回数据
    output                                      exc_csr_valid_mem_wb_o,  // csr 写回使能
    output [    `ysyx_041514_REG_ADDRWIDTH-1:0] rd_addr_mem_wb_o,        // gpr 写回使能
    output [             `ysyx_041514_XLEN-1:0] mem_data_mem_wb_o        //访存阶段的数据
);

  wire reg_wen = !stall_valid_i[`ysyx_041514_CTRLBUS_MEM_WB];
  wire _flush_valid = flush_valid_i[`ysyx_041514_CTRLBUS_MEM_WB];
  wire reg_rst = rst | _flush_valid;

`ifndef ysyx_041514_YSYX_SOC
  // 用于 difftest，获取即将提交的下一条指令的 pc
  import "DPI-C" function void set_nextpc(input longint nextpc);
  always @(posedge clk) begin
    // 避免重复提交 pc
    if (reg_wen & (~_flush_valid)) begin
      set_nextpc(pc_mem_wb_i);
    end
  end
`endif

  //   /* pc 寄存器 */
  //   wire [`ysyx_041514_XLEN_BUS] _pc_mem_wb_d = (_flush_valid) ? `ysyx_041514_XLEN'b0 : pc_mem_wb_i;
  //   wire [`ysyx_041514_XLEN_BUS] _pc_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_XLEN),
  //       .RESET_VAL(`ysyx_041514_XLEN'b0)
  //   ) u_pc_mem_wb_id (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_pc_mem_wb_d),
  //       .dout(_pc_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign pc_mem_wb_o = _pc_mem_wb_q;


  //   /* inst_data 寄存器 */
  //   wire [`ysyx_041514_INST_LEN-1:0] _inst_data_mem_wb_d = (_flush_valid) ? `ysyx_041514_INST_NOP : inst_data_mem_wb_i;
  //   wire [`ysyx_041514_INST_LEN-1:0] _inst_data_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_INST_LEN),
  //       .RESET_VAL(`ysyx_041514_INST_NOP)
  //   ) u_inst_data_mem_wb_id (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_inst_data_mem_wb_d),
  //       .dout(_inst_data_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign inst_data_mem_wb_o = _inst_data_mem_wb_q;


  /* csr_mip_write_valid寄存器 */
  wire _csr_mip_write_valid_mem_wb_d = csr_mip_write_valid_mem_wb_i;
  wire _csr_mip_write_valid_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_csr_mip_write_valid_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mip_write_valid_mem_wb_d),
      .dout(_csr_mip_write_valid_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mip_write_valid_mem_wb_o = _csr_mip_write_valid_mem_wb_q;



  //   /* csr_mie_write_valid寄存器 */
  //   wire _csr_mie_write_valid_mem_wb_d = (_flush_valid) ? `ysyx_041514_FALSE : csr_mie_write_valid_mem_wb_i;
  //   wire _csr_mie_write_valid_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (1),
  //       .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  //   ) u_csr_mie_write_valid_mem_wb (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_csr_mie_write_valid_mem_wb_d),
  //       .dout(_csr_mie_write_valid_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign csr_mie_write_valid_mem_wb_o = _csr_mie_write_valid_mem_wb_q;



  //   /* csr_mtvec_write_valid寄存器 */
  //   wire _csr_mtvec_write_valid_mem_wb_d = (_flush_valid) ? `ysyx_041514_FALSE : csr_mtvec_write_valid_mem_wb_i;
  //   wire _csr_mtvec_write_valid_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (1),
  //       .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  //   ) u_csr_mtvec_write_valid_mem_wb (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_csr_mtvec_write_valid_mem_wb_d),
  //       .dout(_csr_mtvec_write_valid_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign csr_mtvec_write_valid_mem_wb_o = _csr_mtvec_write_valid_mem_wb_q;


  /* csr_mtval_write_valid寄存器 */
  wire _csr_mtval_write_valid_mem_wb_d = csr_mtval_write_valid_mem_wb_i;
  wire _csr_mtval_write_valid_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_csr_mtval_write_valid_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mtval_write_valid_mem_wb_d),
      .dout(_csr_mtval_write_valid_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mtval_write_valid_mem_wb_o = _csr_mtval_write_valid_mem_wb_q;


  /* csr_mcause_write_valid寄存器 */
  wire _csr_mcause_write_valid_mem_wb_d = csr_mcause_write_valid_mem_wb_i;
  wire _csr_mcause_write_valid_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_csr_mcause_write_valid_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mcause_write_valid_mem_wb_d),
      .dout(_csr_mcause_write_valid_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mcause_write_valid_mem_wb_o = _csr_mcause_write_valid_mem_wb_q;

  /* csr_mepc_write_valid寄存器 */
  wire _csr_mepc_write_valid_mem_wb_d = csr_mepc_write_valid_mem_wb_i;
  wire _csr_mepc_write_valid_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_csr_mepc_write_valid_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mepc_write_valid_mem_wb_d),
      .dout(_csr_mepc_write_valid_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mepc_write_valid_mem_wb_o = _csr_mepc_write_valid_mem_wb_q;


  /* csr_mstatus_write_valid寄存器 */
  wire _csr_mstatus_write_valid_mem_wb_d = csr_mstatus_write_valid_mem_wb_i;
  wire _csr_mstatus_write_valid_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_csr_mstatus_write_valid_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mstatus_write_valid_mem_wb_d),
      .dout(_csr_mstatus_write_valid_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mstatus_write_valid_mem_wb_o = _csr_mstatus_write_valid_mem_wb_q;




  /* csr_mip_writedata寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_mip_writedata_mem_wb_d = csr_mip_writedata_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_mip_writedata_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_csr_mip_writedata_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mip_writedata_mem_wb_d),
      .dout(_csr_mip_writedata_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mip_writedata_mem_wb_o = _csr_mip_writedata_mem_wb_q;


  //   /* csr_mie_writedata寄存器 */
  //   wire [`ysyx_041514_XLEN-1:0] _csr_mie_writedata_mem_wb_d = (_flush_valid) ? `ysyx_041514_XLEN'b0 : csr_mie_writedata_mem_wb_i;
  //   wire [`ysyx_041514_XLEN-1:0] _csr_mie_writedata_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_XLEN),
  //       .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  //   ) u_csr_mie_writedata_mem_wb (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_csr_mie_writedata_mem_wb_d),
  //       .dout(_csr_mie_writedata_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign csr_mie_writedata_mem_wb_o = _csr_mie_writedata_mem_wb_q;


  //   /* csr_mtvec_writedata寄存器 */
  //   wire [`ysyx_041514_XLEN-1:0] _csr_mtvec_writedata_mem_wb_d = (_flush_valid) ? `ysyx_041514_XLEN'b0 : csr_mtvec_writedata_mem_wb_i;
  //   wire [`ysyx_041514_XLEN-1:0] _csr_mtvec_writedata_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_XLEN),
  //       .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  //   ) u_csr_mtvec_writedata_mem_wb (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_csr_mtvec_writedata_mem_wb_d),
  //       .dout(_csr_mtvec_writedata_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign csr_mtvec_writedata_mem_wb_o = _csr_mtvec_writedata_mem_wb_q;

  /* csr_mtval_writedata寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_mtval_writedata_mem_wb_d = csr_mtval_writedata_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_mtval_writedata_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_csr_mtval_writedata_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mtval_writedata_mem_wb_d),
      .dout(_csr_mtval_writedata_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mtval_writedata_mem_wb_o = _csr_mtval_writedata_mem_wb_q;


  /* csr_mcause_writedata寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_mcause_writedata_mem_wb_d = csr_mcause_writedata_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_mcause_writedata_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_csr_mcause_writedata_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mcause_writedata_mem_wb_d),
      .dout(_csr_mcause_writedata_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mcause_writedata_mem_wb_o = _csr_mcause_writedata_mem_wb_q;

  /* csr_mepc_writedata寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_mepc_writedata_mem_wb_d = csr_mepc_writedata_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_mepc_writedata_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:��认值未设置
  ) u_csr_mepc_writedata_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mepc_writedata_mem_wb_d),
      .dout(_csr_mepc_writedata_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mepc_writedata_mem_wb_o = _csr_mepc_writedata_mem_wb_q;

  /* csr_mstatus_writedata寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _csr_mstatus_writedata_mem_wb_d = csr_mstatus_writedata_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _csr_mstatus_writedata_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默���值未设置
  ) u_csr_mstatus_writedata_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_mstatus_writedata_mem_wb_d),
      .dout(_csr_mstatus_writedata_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_mstatus_writedata_mem_wb_o = _csr_mstatus_writedata_mem_wb_q;


  /* pc寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _pc_mem_wb_d = pc_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _pc_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_pc_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_pc_mem_wb_d),
      .dout(_pc_mem_wb_q),
      .wen (reg_wen)
  );
  assign pc_mem_wb_o = _pc_mem_wb_q;

  /* inst_data寄存器 */
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_mem_wb_d = inst_data_mem_wb_i;
  wire [`ysyx_041514_INST_LEN-1:0] _inst_data_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_INST_LEN),
      .RESET_VAL(`ysyx_041514_INST_NOP)
  ) u_inst_data_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_inst_data_mem_wb_d),
      .dout(_inst_data_mem_wb_q),
      .wen (reg_wen)
  );
  assign inst_data_mem_wb_o = _inst_data_mem_wb_q;


  //   /* exc_alu_data寄存器 */
  //   wire [`ysyx_041514_XLEN-1:0] _exc_alu_data_mem_wb_d = exc_alu_data_mem_wb_i;
  //   wire [`ysyx_041514_XLEN-1:0] _exc_alu_data_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (`ysyx_041514_XLEN),
  //       .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  //   ) u_exc_alu_data_mem_wb (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_exc_alu_data_mem_wb_d),
  //       .dout(_exc_alu_data_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign exc_alu_data_mem_wb_o = _exc_alu_data_mem_wb_q;




  //   /* load_valid寄存器 */
  //   wire _load_valid_mem_wb_d = load_valid_mem_wb_i;
  //   wire _load_valid_mem_wb_q;
  //   ysyx_041514_regTemplate #(
  //       .WIDTH    (1),
  //       .RESET_VAL(1'b0)  //TODO:默认值未设置
  //   ) u_load_valid_mem_wb (
  //       .clk (clk),
  //       .rst (reg_rst),
  //       .din (_load_valid_mem_wb_d),
  //       .dout(_load_valid_mem_wb_q),
  //       .wen (reg_wen)
  //   );
  //   assign load_valid_mem_wb_o = _load_valid_mem_wb_q;

  /* csr_addr 寄存器 */
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_addr_mem_wb_d = csr_addr_mem_wb_i;
  wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] _csr_addr_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_CSR_REG_ADDRWIDTH),
      .RESET_VAL(`ysyx_041514_CSR_REG_ADDRWIDTH'b0)  //TODO:默认值未设置
  ) u_csr_addr_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_csr_addr_mem_wb_d),
      .dout(_csr_addr_mem_wb_q),
      .wen (reg_wen)
  );
  assign csr_addr_mem_wb_o = _csr_addr_mem_wb_q;


  /* exc_csr_data 寄存器 */
  wire [`ysyx_041514_XLEN_BUS] _exc_csr_data_mem_wb_d = exc_csr_data_mem_wb_i;
  wire [`ysyx_041514_XLEN_BUS] _exc_csr_data_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_exc_csr_data_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_exc_csr_data_mem_wb_d),
      .dout(_exc_csr_data_mem_wb_q),
      .wen (reg_wen)
  );
  assign exc_csr_data_mem_wb_o = _exc_csr_data_mem_wb_q;


  /* exc_csr_valid 寄存器 */
  wire _exc_csr_valid_mem_wb_d = exc_csr_valid_mem_wb_i;
  wire _exc_csr_valid_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (1),
      .RESET_VAL(`ysyx_041514_FALSE)  //TODO:默认值未设置
  ) u_exc_csr_valid_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_exc_csr_valid_mem_wb_d),
      .dout(_exc_csr_valid_mem_wb_q),
      .wen (reg_wen)
  );
  assign exc_csr_valid_mem_wb_o = _exc_csr_valid_mem_wb_q;


  /* rd_addr 寄存器 */
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rd_addr_mem_wb_d = rd_addr_mem_wb_i;
  wire [`ysyx_041514_REG_ADDRWIDTH-1:0] _rd_addr_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_REG_ADDRWIDTH),
      .RESET_VAL(`ysyx_041514_REG_ADDRWIDTH'b0)  //TODO:默认值未设置
  ) u_rd_addr_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_rd_addr_mem_wb_d),
      .dout(_rd_addr_mem_wb_q),
      .wen (reg_wen)
  );
  assign rd_addr_mem_wb_o = _rd_addr_mem_wb_q;


  /* mem_data寄存器 */
  wire [`ysyx_041514_XLEN-1:0] _mem_data_mem_wb_d = mem_data_mem_wb_i;
  wire [`ysyx_041514_XLEN-1:0] _mem_data_mem_wb_q;
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)  //TODO:默认值未设置
  ) u_mem_data_mem_wb (
      .clk (clk),
      .rst (reg_rst),
      .din (_mem_data_mem_wb_d),
      .dout(_mem_data_mem_wb_q),
      .wen (reg_wen)
  );

  assign mem_data_mem_wb_o = _mem_data_mem_wb_q;

endmodule


