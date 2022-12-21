// `include "sysconfig.v"

// `ifndef ysyx_041514_YSYX_SOC
// module ysyx_041514_writeback (
//     input                             clk,
//     /* from MEM/WB */
//     input [    `ysyx_041514_XLEN_BUS] pc_wb_i,
//     input [`ysyx_041514_INST_LEN-1:0] inst_data_wb_i
// );
//   /***************difftest 使用****************/
//   // 向仿真环境传递指令提交信息
//   // 当指令有效时：pc_wb_i = 当前指令 PC ，_commit_valid = 1
//   // 当指令无效时：pc_wb_i = 0 ，_commit_valid = 0；
//   wire _commit_valid = (pc_wb_i != `ysyx_041514_XLEN'b0);
//   import "DPI-C" function void inst_commit(
//     input longint pc,
//     input int inst,
//     input bit commit_valid
//   );
//   always @(posedge clk) begin
//     // 延时一个周期，让寄存器写入有效
//     inst_commit(pc_wb_i, inst_data_wb_i, _commit_valid);
//   end
// endmodule

// `endif 
