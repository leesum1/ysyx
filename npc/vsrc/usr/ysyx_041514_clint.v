`include "sysconfig.v"
/* 与 mem 位于同一阶段 */
module ysyx_041514_clint (
    input wire clk,
    input wire rst,

    input [    `ysyx_041514_XLEN-1:0] pc_from_mem_i,  // from mem
    input [    `ysyx_041514_XLEN-1:0] pc_from_exe_i,  // from exe
    input [`ysyx_041514_INST_LEN-1:0] inst_data_i,


    /* clint 接口 */
    input  [`ysyx_041514_NPC_ADDR_BUS] clint_addr_i,
    input                              clint_valid_i,
    input                              clint_write_valid_i,
    input  [    `ysyx_041514_XLEN_BUS] clint_wdata_i,
    output [    `ysyx_041514_XLEN_BUS] clint_rdata_o,

    /* TARP 总线 */
    input wire [`ysyx_041514_TRAP_BUS] trap_bus_i,
    /* ----- stall request from other modules 各个阶段请求流水线暂停请求 --------*/
    output trap_stall_valid_wb_o,
    // input wire ram_stall_valid_if_i,  // if 阶段访存暂停
    // input wire ram_stall_valid_mem_i,  // mem 访存暂停
    // input wire load_use_valid_id_i,  //load-use data hazard from id
    // input wire jump_valid_ex_i,  // branch hazard from ex
    // input wire alu_mul_div_valid_ex_i,  // mul div stall from ex

    /* trap 所需寄存器，来自于 csr (读)*/
    input  wire [`ysyx_041514_XLEN-1:0] csr_mstatus_readdata_i,
    input  wire [`ysyx_041514_XLEN-1:0] csr_mepc_readdata_i,
    //input wire [`ysyx_041514_XLEN-1:0] csr_mcause_readdata_i,
    //input wire [`ysyx_041514_XLEN-1:0] csr_mtval_readdata_i,
    input  wire [`ysyx_041514_XLEN-1:0] csr_mtvec_readdata_i,
    input  wire [`ysyx_041514_XLEN-1:0] csr_mip_readdata_i,
    input  wire [`ysyx_041514_XLEN-1:0] csr_mie_readdata_i,
    /* trap 所需寄存器，来自于 csr (写)*/
    output wire [`ysyx_041514_XLEN-1:0] csr_mstatus_writedata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mepc_writedata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mcause_writedata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mtval_writedata_o,
    //output wire [`ysyx_041514_XLEN-1:0] csr_mtvec_writedata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mip_writedata_o,
    //output wire [`ysyx_041514_XLEN-1:0] csr_mie_writedata_o,

    output wire csr_mstatus_write_valid_o,
    output wire csr_mepc_write_valid_o,
    output wire csr_mcause_write_valid_o,
    output wire csr_mtval_write_valid_o,
    //output wire csr_mtvec_write_valid_o,
    output wire csr_mip_write_valid_o,
    //output wire csr_mie_write_valid_o,

    /* 输出至取指阶段 */
    output [`ysyx_041514_XLEN-1:0] clint_pc_o,
    output clint_pc_valid_o,
    output clint_pc_plus4_valid_o

);

  /* --------------------- handle the stall request -------------------*/
  // assign flush_o = trap_valid;
  wire trap_valid;
  wire Machine_timer_interrupt;
  wire trap_mret;
  wire trap_fencei;




  wire trap_stall_valid_wb = (trap_valid | trap_mret | trap_fencei); // TODO 目前在 mem 阶段检测 tarp
  assign trap_stall_valid_wb_o = trap_stall_valid_wb;

  /******************************handle the trap request**************************************/
  /* type of trap */
  // wire _trap_ecall = trap_bus_i[`ysyx_041514_TRAP_ECALL]; // 11
  // wire _trap_ebreak = trap_bus_i[`ysyx_041514_TRAP_EBREAK];
  // wire trap_breakpoint = trap_bus_i[`ysyx_041514_TRAP_BREAKPOINT]; // 3
  // wire trap_inst_page_fault = trap_bus_i[`ysyx_041514_TRAP_INST_PAGE_FAULT]; // 12
  // wire trap_inst_access_fault = trap_bus_i[`ysyx_041514_TRAP_INST_ACCESS_FAULT]; // 1
  // wire trap_illegal_inst = trap_bus_i[`ysyx_041514_TRAP_INST_ACCESS_FAULT]; // 1

  assign trap_mret = trap_bus_i[`ysyx_041514_TRAP_MRET];
  assign trap_fencei = trap_bus_i[`ysyx_041514_TRAP_FENCEI];
  // wire [`ysyx_041514_XLEN_BUS]_fencei_pc = pc_from_mem_i+'d4; // TODO 加 4 操作，统一到 pc 自增上，节省一个加法器


  assign trap_valid = (|trap_bus_i[15:0]) | Machine_timer_interrupt;  // 0 - 15 表示 trap 发生

  reg [`ysyx_041514_XLEN_BUS] mcause_switch;
  always @(*) begin
    if (Machine_timer_interrupt) begin
      mcause_switch = {1'b1, 63'd7};
    end else if (trap_bus_i[`ysyx_041514_TRAP_BREAKPOINT]) begin
      mcause_switch = {1'b0, 63'd3};
    end else if (trap_bus_i[`ysyx_041514_TRAP_INST_PAGE_FAULT]) begin
      mcause_switch = {1'b0, 63'd12};
    end else if (trap_bus_i[`ysyx_041514_TRAP_INST_ACCESS_FAULT]) begin
      mcause_switch = {1'b0, 63'd1};
    end else if (trap_bus_i[`ysyx_041514_TRAP_ILLEGAL_INST]) begin
      mcause_switch = {1'b0, 63'd2};
    end else if (trap_bus_i[`ysyx_041514_TRAP_INST_ADDR_MISALIGNED]) begin
      mcause_switch = {1'b0, 63'd0};
    end else if (trap_bus_i[`ysyx_041514_TRAP_ECALL_M]) begin
      mcause_switch = {1'b0, 63'd11};
    end else if (trap_bus_i[`ysyx_041514_TRAP_ECALL_U]) begin
      mcause_switch = {1'b0, 63'd8};
    end else if (trap_bus_i[`ysyx_041514_TRAP_ECALL_S]) begin
      mcause_switch = {1'b0, 63'd9};
    end else if (trap_bus_i[`ysyx_041514_TRAP_EBREAK]) begin
      mcause_switch = {1'b0, 63'd3};
    end else if (trap_bus_i[`ysyx_041514_TRAP_LOAD_ADDR_MISALIGNED]) begin
      mcause_switch = {1'b0, 63'd4};
    end else if (trap_bus_i[`ysyx_041514_TRAP_STORE_ADDR_MISALIGNED]) begin
      mcause_switch = {1'b0, 63'd6};
    end else if (trap_bus_i[`ysyx_041514_TRAP_LOAD_PAGE_FAULT]) begin
      mcause_switch = {1'b0, 63'd13};
    end else if (trap_bus_i[`ysyx_041514_TRAP_STORE_PAGE_FAULT]) begin
      mcause_switch = {1'b0, 63'd15};
    end else if (trap_bus_i[`ysyx_041514_TRAP_LOAD_ACCESS_FAULT]) begin
      mcause_switch = {1'b0, 63'd5};
    end else if (trap_bus_i[`ysyx_041514_TRAP_STORE_ACCESS_FAULT]) begin
      mcause_switch = {1'b0, 63'd7};
    end else begin
      mcause_switch = 0;
    end
  end






  /* set the csr register and new pc if traps happened */
  // step 1: save current pc 
  assign csr_mepc_writedata_o   = Machine_timer_interrupt?pc_from_exe_i:pc_from_mem_i; // trap or int，int 保存前一条指令，trap 保存当前指令
  assign csr_mepc_write_valid_o = trap_valid;
  // step 2: set the trap pc
  wire [`ysyx_041514_XLEN-1:0]_trap_pc_o = csr_mtvec_readdata_i;  // TODO:now only suppot direct mode,need to add vector mode
  wire _trap_pc_valid_o = trap_valid;
  // step 3: save trap cuase to mcause
  assign csr_mcause_writedata_o = mcause_switch;
  assign csr_mcause_write_valid_o = trap_valid;
  // step 4: save inst_data to mtval
  assign csr_mtval_writedata_o = {32'b0, inst_data_i};
  assign csr_mtval_write_valid_o = trap_valid;
  // step 5 ： mstatus
  wire [`ysyx_041514_XLEN_BUS] trap_mstatus_wdata = {
    csr_mstatus_readdata_i[63:13],
    1'b0,
    1'b0,
    csr_mstatus_readdata_i[10:8],
    csr_mstatus_readdata_i[3],
    csr_mstatus_readdata_i[6:4],
    1'b0,
    csr_mstatus_readdata_i[2:0]
  };

  wire trap_mstatus_valid = trap_valid;


  /* restore pc and csr register if mret happened*/
  wire [`ysyx_041514_XLEN-1:0] _mret_pc_o = csr_mepc_readdata_i;  // TODO mstatus
  wire _mret_pc_valid_o = trap_mret;

  wire mret_mstatus_valid = trap_mret;
  wire [`ysyx_041514_XLEN_BUS] mret_mstatus_wdata = {
    csr_mstatus_readdata_i[63:13],
    1'b1,
    1'b1,
    csr_mstatus_readdata_i[10:8],
    1'b1,
    csr_mstatus_readdata_i[6:4],
    csr_mstatus_readdata_i[7],
    csr_mstatus_readdata_i[2:0]
  };



  /* mstatus mux */
  // `ifndef ysyx_041514_YSYX_SOC
  //   assign csr_mstatus_write_valid_o = `ysyx_041514_FALSE;
  // `else
  //   assign csr_mstatus_write_valid_o = mret_mstatus_valid|trap_mstatus_valid;
  // `endif 
  assign csr_mstatus_write_valid_o = mret_mstatus_valid | trap_mstatus_valid;
  assign csr_mstatus_writedata_o = ({`ysyx_041514_XLEN{mret_mstatus_valid}}&mret_mstatus_wdata)|
                                   ({`ysyx_041514_XLEN{trap_mstatus_valid}}&trap_mstatus_wdata);



  /* fencei pc */
  wire [`ysyx_041514_XLEN_BUS] _fencei_pc = pc_from_mem_i;  // +4 操作统一到 pc 阶段
  assign clint_pc_plus4_valid_o = trap_fencei;

  /* pc mux TODO 是否应该考虑优先级问题？同一时刻有多个跳转如何考虑？ */
  // 1. trap 发生，包括中断和异常
  // 2. mret 指令
  // 3. fencei 指令
  assign clint_pc_o = ({`ysyx_041514_XLEN{_mret_pc_valid_o}}&_mret_pc_o)|
                      ({`ysyx_041514_XLEN{_trap_pc_valid_o}}&_trap_pc_o)|
                      ({`ysyx_041514_XLEN{trap_fencei}}&_fencei_pc);

  assign clint_pc_valid_o = trap_valid | trap_mret | trap_fencei;



  /* mip TODO: 暂时只支持 mtime 中断 */
  assign csr_mip_write_valid_o = Machine_timer_interrupt;
  assign csr_mip_writedata_o = {csr_mip_readdata_i[63:8], 1'b1, csr_mip_readdata_i[6:0]};


  /*********************************clint******************************************/
  wire csr_mstatus_mie_valid = csr_mstatus_readdata_i[3];  // 全局中断
  wire csr_mie_mtie_valid = csr_mie_readdata_i[7];  // 定时器中断


  wire mtime_ge_mtime;


  wire pc_from_exe_valid = (|pc_from_exe_i[31:0]); // exe 阶段为有效指令时，才能进入中断，不然中断返回找不到返回地址
  wire pc_from_mem_valid = (|pc_from_mem_i[31:0]);
  assign Machine_timer_interrupt = mtime_ge_mtime&csr_mstatus_mie_valid&csr_mie_mtie_valid&pc_from_exe_valid&pc_from_mem_valid;



  wire [`ysyx_041514_NPC_ADDR_BUS] mtime_addr_i = clint_addr_i;
  wire mtime_write_valid_i = clint_write_valid_i;
  wire [`ysyx_041514_XLEN_BUS] mtime_wdata_i = clint_wdata_i;  // 写数据
  wire [`ysyx_041514_XLEN_BUS] mtime_rdata;
  yays_041514_mtime u_yays_041514_mtime (
      .clk                (clk),
      .rst                (rst),
      .mtime_addr_i       (mtime_addr_i),
      .mtime_write_valid_i(mtime_write_valid_i),
      .mtime_wdata_i      (mtime_wdata_i),
      .mtime_rdata_o      (mtime_rdata),
      .mtime_ge_mtime_o   (mtime_ge_mtime)
  );

  assign clint_rdata_o = mtime_rdata;


  /*************ebreak仿真使用**************************/

`ifndef ysyx_041514_YSYX_SOC
  wire _trap_ebreak = trap_bus_i[`ysyx_041514_TRAP_EBREAK];
  always @(*) begin
    if (_trap_ebreak) begin
      $finish;
    end
  end
`endif

endmodule
