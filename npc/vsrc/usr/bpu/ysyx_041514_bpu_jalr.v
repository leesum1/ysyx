`include "sysconfig.v"

module ysyx_041514_bpu_jalr #(
    JALR_NUM = 64
) (
    input clk,
    input rst,
    input [31:0] bpu_ghr_data_i,
    // from if
    input [31:0] bpu_pc_i,
    input bpu_jalr_type_i,
    output bpu_jalr_taken_o,
    output bpu_jalr_hit_o,
    output [31:0] bpu_jalr_pc_o,

    // from exe
    input [31:0] bpu_update_pc_i,
    input bpu_update_valid_i,
    input bpu_update_taken_i,
    input bpu_update_jalr_type_i,
    input [31:0] bpu_update_jalr_redirect_pc
);

  localparam JALR_ENTRIES_WIDTH = $clog2(JALR_NUM);

  wire [JALR_ENTRIES_WIDTH-1:0] jalr_buff_idx_if = bpu_pc_i[JALR_ENTRIES_WIDTH-1+2:2]^bpu_pc_i[JALR_ENTRIES_WIDTH*2+1:JALR_ENTRIES_WIDTH+2];
  wire [JALR_ENTRIES_WIDTH-1:0] jalr_buff_idx_exe = bpu_update_pc_i[JALR_ENTRIES_WIDTH-1+2:2]^bpu_update_pc_i[JALR_ENTRIES_WIDTH*2+1:JALR_ENTRIES_WIDTH+2];

  // wire [JALR_ENTRIES_WIDTH-1:0] jalr_buff_idx_if = bpu_pc_i[JALR_ENTRIES_WIDTH-1+2:2]^bpu_ghr_data_i[JALR_ENTRIES_WIDTH-1:0];
  // wire [JALR_ENTRIES_WIDTH-1:0] jalr_buff_idx_exe = bpu_update_pc_i[JALR_ENTRIES_WIDTH-1+2:2]^bpu_ghr_data_i[JALR_ENTRIES_WIDTH-1:0];


  reg [31:0] jalr_buff[JALR_NUM-1:0];


  wire jalr_update_valid = bpu_update_jalr_type_i & bpu_update_valid_i;
  // write
  integer i0;
  always @(posedge clk) begin
    if (rst) begin
      for (i0 = 0; i0 < JALR_NUM; i0 = i0 + 1) begin
        jalr_buff[i0] = 'b0;
      end
    end else begin
      if (jalr_update_valid) begin
        jalr_buff[jalr_buff_idx_exe] <= bpu_update_jalr_redirect_pc;
      end
    end
  end



  // read 
  wire [31:0] jalr_read_data = jalr_buff[jalr_buff_idx_if];
  assign bpu_jalr_hit_o = jalr_read_data != 'd0 && bpu_jalr_type_i;
  assign bpu_jalr_taken_o = bpu_jalr_hit_o;
  assign bpu_jalr_pc_o = jalr_read_data;


endmodule
