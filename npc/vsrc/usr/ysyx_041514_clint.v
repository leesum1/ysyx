`include "sysconfig.v"
/* 与 mem 位于同一阶段 */
module ysyx_041514_clint (
    input wire clk,
    input wire rst,

    input [`ysyx_041514_XLEN-1:0] pc_i, // from mem
    input [`ysyx_041514_XLEN-1:0] pc_from_exe_i, // from exe
    input [`ysyx_041514_INST_LEN-1:0] inst_data_i,

    /* clint 接口 */
    input [         `ysyx_041514_NPC_ADDR_BUS] clint_addr_i,
    input                          clint_valid_i,
    input                          clint_write_valid_i,
    input [             `ysyx_041514_XLEN_BUS] clint_wdata_i,
    output  [             `ysyx_041514_XLEN_BUS] clint_rdata_o,

    /* TARP 总线 */
    input wire [`ysyx_041514_TRAP_BUS] trap_bus_i,
    /* ----- stall request from other modules 各个阶段请求流水线暂停请求 --------*/
    input wire ram_stall_valid_if_i, // if 阶段访存暂停
    input wire ram_stall_valid_mem_i,// mem 访存暂停
    input wire load_use_valid_id_i,  //load-use data hazard from id
    input wire jump_valid_ex_i,  // branch hazard from ex
    input wire alu_mul_div_valid_ex_i, // mul div stall from ex

    /* trap 所需寄存器，来自于 csr (读)*/
    input wire [`ysyx_041514_XLEN-1:0] csr_mstatus_readdata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mepc_readdata_i,
    //input wire [`ysyx_041514_XLEN-1:0] csr_mcause_readdata_i,
    //input wire [`ysyx_041514_XLEN-1:0] csr_mtval_readdata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mtvec_readdata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mip_readdata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mie_readdata_i,
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
    output wire [`ysyx_041514_XLEN-1:0] clint_pc_o,
    output wire clint_pc_valid_o,

    /* ---signals to other stages of the pipeline  ----*/
    output reg[5:0]              stall_o,   // stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB， one bit for one stage respectively
    output wire [5:0] flush_o  // flush the whole pipleline, exception or interrupt happens
);

  /* --------------------- handle the stall request -------------------*/
  // assign flush_o = trap_valid;

  //stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB
  localparam load_use_flush = 6'b000100;
  localparam load_use_stall = 6'b000011;
  localparam jump_flush = 6'b000110;
  localparam jump_stall = 6'b000000;
  localparam mul_div_flush = 6'b001000;
  localparam mul_div_stall = 6'b000111;
  localparam trap_flush = 6'b001110;
  localparam trap_stall = 6'b000000;
  localparam ram_if_flush = 6'b010000;
  localparam ram_if_stall = 6'b001111;
  localparam ram_mem_flush = 6'b010000;
  localparam ram_mem_stall = 6'b001111;
  // localparam mutiple_alu_inst_flush = 6'b000011;
  // localparam mutiple_alu_inst_stall = 6'b000000;


/* 流水线越往后,优先级越高 */
  always @(*) begin
    if (rst) begin
      stall_o = 6'b000000;
      flush_o = 6'b011111;
    // 访存时阻塞所有流水线
    end else if (ram_stall_valid_mem_i) begin
      stall_o = ram_mem_stall;
      flush_o = ram_mem_flush;
    // 访存时阻塞所有流水线
    end else if (ram_stall_valid_if_i) begin
      stall_o = ram_if_stall;
      flush_o = ram_if_flush;
    // 中断|异常,(发生在 mem 阶段)
    end else if (trap_valid | trap_mret) begin
      stall_o = trap_stall;
      flush_o = trap_flush;
    // 跳转指令,(发生在 ex 阶段)
    end else if (jump_valid_ex_i) begin
      stall_o = jump_stall;
      flush_o = jump_flush;
    // 乘法和除法
    end else if (alu_mul_div_valid_ex_i) begin
      stall_o = mul_div_stall;
      flush_o = mul_div_flush;
    // load use data 冲突,(发生在 id 阶段)
    end else if (load_use_valid_id_i) begin
      stall_o = load_use_stall;
      flush_o = load_use_flush;
    // 没有异常情况,正常执行
    end else begin
      stall_o = 6'b000000;
      flush_o = 6'b000000;
    end
  end



/******************************handle the trap request**************************************/
  /* type of trap */
  // wire _trap_ecall = trap_bus_i[`ysyx_041514_TRAP_ECALL]; // 11
  // wire _trap_ebreak = trap_bus_i[`ysyx_041514_TRAP_EBREAK];
  // wire trap_breakpoint = trap_bus_i[`ysyx_041514_TRAP_BREAKPOINT]; // 3
  // wire trap_inst_page_fault = trap_bus_i[`ysyx_041514_TRAP_INST_PAGE_FAULT]; // 12
  // wire trap_inst_access_fault = trap_bus_i[`ysyx_041514_TRAP_INST_ACCESS_FAULT]; // 1
  // wire trap_illegal_inst = trap_bus_i[`ysyx_041514_TRAP_INST_ACCESS_FAULT]; // 1

  wire trap_mret = trap_bus_i[`ysyx_041514_TRAP_MRET];


  wire trap_valid = (|trap_bus_i[15:0])| Machine_timer_interrupt; // 0 - 15 表示 trap 发生

  reg [`ysyx_041514_XLEN_BUS]mcause_switch;
  always @(*) begin
    if (Machine_timer_interrupt) begin
      mcause_switch={1'b1,63'd7};
      end
    else if (trap_bus_i[`ysyx_041514_TRAP_BREAKPOINT]) begin
      mcause_switch={1'b0,63'd3};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_INST_PAGE_FAULT]) begin
      mcause_switch={1'b0,63'd12};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_INST_ACCESS_FAULT]) begin
      mcause_switch={1'b0,63'd1};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_ILLEGAL_INST]) begin
      mcause_switch={1'b0,63'd2};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_INST_ADDR_MISALIGNED]) begin
      mcause_switch={1'b0,63'd0};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_ECALL_M]) begin
      mcause_switch={1'b0,63'd11};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_ECALL_U]) begin
      mcause_switch={1'b0,63'd8};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_ECALL_S]) begin
      mcause_switch={1'b0,63'd9};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_EBREAK]) begin
      mcause_switch={1'b0,63'd3};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_LOAD_ADDR_MISALIGNED]) begin
      mcause_switch={1'b0,63'd4};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_STORE_ADDR_MISALIGNED]) begin
      mcause_switch={1'b0,63'd6};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_LOAD_PAGE_FAULT]) begin
      mcause_switch={1'b0,63'd13};
    end
        else if (trap_bus_i[`ysyx_041514_TRAP_STORE_PAGE_FAULT]) begin
      mcause_switch={1'b0,63'd15};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_LOAD_ACCESS_FAULT]) begin
      mcause_switch={1'b0,63'd5};
    end
    else if (trap_bus_i[`ysyx_041514_TRAP_STORE_ACCESS_FAULT]) begin
      mcause_switch={1'b0,63'd7};
    end
    else begin
      mcause_switch=0;
    end
  end



  


  /* set the csr register and new pc if traps happened */
  // step 1: save current pc 
  assign csr_mepc_writedata_o   = Machine_timer_interrupt?pc_from_exe_i:pc_i; // trap or int
  assign csr_mepc_write_valid_o = trap_valid;
  // step 2: set the trap pc
  wire [`ysyx_041514_XLEN-1:0]_trap_pc_o = csr_mtvec_readdata_i;  // TODO:now only suppot direct mode,need to add vector mode
  wire _trap_pc_valid_o = trap_valid;
  // step 3: save trap cuase to mcause
  assign csr_mcause_writedata_o = mcause_switch; //TODO:now,only support ecall from mathine mode(11),need to add more
  assign csr_mcause_write_valid_o = trap_valid;
  // step 4: save inst_data to mtval
  assign csr_mtval_writedata_o = {32'b0, inst_data_i};
  assign csr_mtval_write_valid_o = trap_valid;
  // step 5 ： mstatus
  wire  [`ysyx_041514_XLEN_BUS] trap_mstatus_wdata = {csr_mstatus_readdata_i[63:13],
                                   1'b0,1'b0,csr_mstatus_readdata_i[10:8],
                                   csr_mstatus_readdata_i[3],csr_mstatus_readdata_i[6:4],
                                   1'b0,csr_mstatus_readdata_i[2:0]};

  wire trap_mstatus_valid = trap_valid;


  /* restore pc and csr register if mret happened*/
  wire [`ysyx_041514_XLEN-1:0] _mret_pc_o = csr_mepc_readdata_i; // TODO mstatus
  wire _mret_pc_valid_o = trap_mret;
  
  wire mret_mstatus_valid = trap_mret;
  wire  [`ysyx_041514_XLEN_BUS] mret_mstatus_wdata = {csr_mstatus_readdata_i[63:13],1'b1,1'b1,
                                          csr_mstatus_readdata_i[10:8],1'b1,
                                          csr_mstatus_readdata_i[6:4],
                                          csr_mstatus_readdata_i[7],
                                          csr_mstatus_readdata_i[2:0]};



  /* mstatus mux */
  // `ifndef ysyx_041514_YSYX_SOC
  //   assign csr_mstatus_write_valid_o = `ysyx_041514_FALSE;
  // `else
  //   assign csr_mstatus_write_valid_o = mret_mstatus_valid|trap_mstatus_valid;
  // `endif 
  assign csr_mstatus_write_valid_o = mret_mstatus_valid|trap_mstatus_valid;
  assign csr_mstatus_writedata_o = ({`ysyx_041514_XLEN{mret_mstatus_valid}}&mret_mstatus_wdata)|
                                   ({`ysyx_041514_XLEN{trap_mstatus_valid}}&trap_mstatus_wdata);

  /* pc mux */
  assign clint_pc_o = ({`ysyx_041514_XLEN{_mret_pc_valid_o}}&_mret_pc_o)|
                      ({`ysyx_041514_XLEN{_trap_pc_valid_o}}&_trap_pc_o);
  // mret 指令和 中断异常需要跳转 pc
  assign clint_pc_valid_o = trap_valid | trap_mret;


  /* mip TODO: 暂时只支持 mtime 中断 */
  assign csr_mip_write_valid_o = Machine_timer_interrupt;
  assign csr_mip_writedata_o = {csr_mip_readdata_i[63:8],1'b1,csr_mip_readdata_i[6:0]};


  /*********************************clint******************************************/
  wire csr_mstatus_mie_valid = csr_mstatus_readdata_i[3]; // 全局中断
  wire csr_mie_mtie_valid = csr_mie_readdata_i[7];        // 定时器中断

  reg [`ysyx_041514_XLEN_BUS] mtime,mtimecmp;
  wire mtime_ge_mtime = (mtime >= mtimecmp); // mtime >= mtimecmp


  wire pc_from_exe_valid = (|pc_from_exe_i[31:0]); // exe 阶段为有效指令
  wire Machine_timer_interrupt = mtime_ge_mtime&csr_mstatus_mie_valid&csr_mie_mtie_valid&pc_from_exe_valid;

  



  wire [`ysyx_041514_NPC_ADDR_BUS] clint_waddr = clint_addr_i;
  wire [`ysyx_041514_NPC_ADDR_BUS] clint_raddr = clint_addr_i;
  wire clint_waddr_valid = clint_write_valid_i & clint_valid_i; // 写有效
  wire [`ysyx_041514_XLEN_BUS]clint_wdata = clint_wdata_i;  // 写数据
  assign clint_rdata_o = clint_rdata; // 读数据
  reg [`ysyx_041514_XLEN_BUS]clint_rdata;

  wire [`ysyx_041514_XLEN_BUS] mtime_plus1 = mtime+64'b1;

   // 写 mtime
  always @(posedge clk) begin
    if (rst) begin
      mtime <=0;
    end
    else if (clint_waddr_valid & (clint_waddr==`ysyx_041514_MTIME_ADDR)) begin
      mtime <=clint_wdata;
    end
    else begin
      mtime<=mtime_plus1;
    end
  end
  // 写 mtimecmp
  always @(posedge clk) begin
    if (rst) begin
      mtimecmp <=0;
    end
    else if (clint_waddr_valid & (clint_waddr==`ysyx_041514_MTIMECMP_ADDR)) begin
      mtimecmp <=clint_wdata;
    end
    else begin :keep
      mtimecmp<=mtimecmp;
    end
  end
 // 读 mtime mtimecmp
  always @(*) begin
    case (clint_raddr)
      `ysyx_041514_MTIMECMP_ADDR: begin 
        clint_rdata=mtimecmp;
      end
      `ysyx_041514_MTIME_ADDR: begin 
        clint_rdata=mtime;
      end
      default: begin 
        clint_rdata=0;
      end
    endcase
  end 

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
