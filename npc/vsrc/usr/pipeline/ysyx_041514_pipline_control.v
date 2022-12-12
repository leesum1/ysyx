`include "sysconfig.v"

// 组合逻辑
module ysyx_041514_pipline_control (
    input rst,
    /* ----- stall request from other modules  --------*/
    input ram_stall_valid_if_i,  // if ram
    input ram_stall_valid_mem_i,  // mem ram
    input load_use_valid_id_i,  //load-use data hazard from id
    input jump_valid_ex_i,  // branch hazard from ex
    input alu_mul_div_valid_ex_i,  // mul div stall from ex
    input trap_stall_valid_wb_i,

    /* ---signals to other stages of the pipeline  ----*/
    output [5:0] stall_o,   // stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB， one bit for one stage respectively
    output [5:0] flush_o  // flush the whole pipleline if exception or interrupt happened
);

  //stall request to PC,IF_ID, ID_EX, EX_MEM, MEM_WB
  localparam load_use_flush = 6'b000100;
  localparam load_use_stall = 6'b000011;
  localparam jump_flush = 6'b000110;
  localparam jump_stall = 6'b000000;
  localparam mul_div_flush = 6'b001000;
  localparam mul_div_stall = 6'b000111;
  localparam trap_flush = 6'b001110;
  localparam trap_stall = 6'b000000;
  localparam ram_mem_flush = 6'b010000;
  localparam ram_mem_stall = 6'b001111;

  wire ram_stall_req = ram_stall_valid_mem_i | ram_stall_valid_if_i;
  wire trap_stall_req = trap_stall_valid_wb_i;

  reg [5:0] _flush;
  reg [5:0] _stall;
  /* 流水线越往后,优先级越高 */
  always @(*) begin
    if (rst) begin
      _stall = 6'b000000;
      _flush = 6'b011111;
      // 访存时阻塞所有流水线
    end else if (ram_stall_req) begin  // TODO ,if mem 访存合并
      _stall = ram_mem_stall;
      _flush = ram_mem_flush;

      // 中断|异常,(发生在 mem 阶段)
    end else if (trap_stall_req) begin
      _stall = trap_stall;
      _flush = trap_flush;
      // 跳转指令,(发生在 ex 阶段)
    end else if (jump_valid_ex_i) begin
      _stall = jump_stall;
      _flush = jump_flush;
      // 乘法和除法
    end else if (alu_mul_div_valid_ex_i) begin
      _stall = mul_div_stall;
      _flush = mul_div_flush;
      // load use data 冲突,(发生在 id 阶段)
    end else if (load_use_valid_id_i) begin
      _stall = load_use_stall;
      _flush = load_use_flush;
      // 没有异常情况,正常执行
    end else begin
      _stall = 6'b000000;
      _flush = 6'b000000;
    end
  end

  assign stall_o = _stall;
  assign flush_o = _flush;


endmodule
