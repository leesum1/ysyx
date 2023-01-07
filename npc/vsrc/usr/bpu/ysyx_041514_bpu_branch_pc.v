`include "sysconfig.v"

module ysyx_041514_bpu_branch_pc #(
    BHT_NUM = 1024
) (
    input clk,
    input rst,
    // from if
    input [31:0] bpu_pc_i,
    input bpu_branch_type_i,
    output bpu_branch_taken_o,
    output bpu_branch_hit_o,

    // from exe
    input [31:0] bpu_update_pc_i,
    input bpu_update_valid_i,
    input bpu_update_taken_i,
    input bpu_update_branch_type_i
);


  localparam BHT_ENTRIES_WIDTH = $clog2(BHT_NUM);

  wire [BHT_ENTRIES_WIDTH-1:0] _pc_idx_if = bpu_pc_i[BHT_ENTRIES_WIDTH-1+2:2];
  wire [BHT_ENTRIES_WIDTH-1:0] _pc_idx_exe = bpu_update_pc_i[BHT_ENTRIES_WIDTH-1+2:2];

  // branch history table

  //strongly taken (11), weakly taken(10), weakly not taken(01), strongly not taken(00)
  reg [1:0] bht_bi_reg[BHT_NUM-1:0];




  wire bht_update_valid = bpu_update_valid_i & bpu_update_branch_type_i;
  wire [1:0] bim_update_data_o;


  ysyx_041514_bim_update u_ysyx_041514_bim_update (
      .bim_update_req_i(bht_update_valid),
      .bim_update_type_i(bpu_update_taken_i),  // 1： 加 0: 减
      .bim_update_data_i(bht_bi_reg[_pc_idx_exe]),
      .bim_update_data_o(bim_update_data_o)
  );



  // write
  integer i0;
  always @(posedge clk) begin
    if (rst) begin
      for (i0 = 0; i0 < BHT_NUM; i0 = i0 + 1) begin
        bht_bi_reg[i0] = 'b0;
      end
    end else begin
      if (bht_update_valid) begin
        bht_bi_reg[_pc_idx_exe] <= bim_update_data_o;
      end
    end
  end

  // read
  assign bpu_branch_hit_o   = 1'b1 & bpu_branch_type_i;
  assign bpu_branch_taken_o = bht_bi_reg[_pc_idx_if] >= 2'b10;



endmodule

