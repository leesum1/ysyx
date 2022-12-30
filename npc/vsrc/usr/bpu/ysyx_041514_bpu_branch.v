`include "sysconfig.v"

module ysyx_041514_bpu_branch #(
    BHT_NUM = 64
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

  wire    [31:0] _pc = bpu_pc_i[31:0];

  // branch history table
  // {bht_pc,bht_valid,bht_bi}
  //strongly taken (11), weakly taken(10), weakly not taken(01), strongly not taken(00)
  reg     [31:0]                       bht_pc_reg                      [BHT_NUM-1:0];
  reg                                  bht_valid_reg                   [BHT_NUM-1:0];
  reg     [ 1:0]                       bht_bi_reg                      [BHT_NUM-1:0];


  // read
  reg                                  bht_read_hit;
  reg                                  bht_jump_valid;  // 是否跳转
  integer                              i0;
  always @(*) begin
    bht_read_hit   = 1'b0;
    bht_jump_valid = 1'b0;
    for (i0 = 0; i0 < BHT_NUM; i0 = i0 + 1) begin
      if (bht_pc_reg[i0] == _pc && bht_valid_reg[i0]) begin  // bht hit
        bht_read_hit   = 1'b1;
        bht_jump_valid = bht_bi_reg[i0][1];
      end
    end
  end


  assign bpu_branch_hit_o   = bpu_branch_type_i & bht_read_hit;
  assign bpu_branch_taken_o = bpu_branch_hit_o & bht_jump_valid;




  // write
  reg                             bht_write_hit;
  reg     [BHT_ENTRIES_WIDTH-1:0] bht_write_hit_entry;

  integer                         i1;
  always @(*) begin
    bht_write_hit = 1'b0;
    bht_write_hit_entry = 'b0;
    for (i1 = 0; i1 < BHT_NUM; i1 = i1 + 1) begin
      if (bht_pc_reg[i1] == bpu_update_pc_i && bht_valid_reg[i1]) begin  // bht hit
        bht_write_hit = 1'b1;
        /* verilator lint_off WIDTH */
        bht_write_hit_entry = i1;
        /* verilator lint_off WIDTH */
      end
    end
  end


  reg [BHT_ENTRIES_WIDTH-1:0] bht_alloc_entry;
  wire alloc_i = bpu_update_valid_i && bpu_update_branch_type_i && (~bht_write_hit);
  ysyx_041514_lfsr_rand #(
      .DEPTH(BHT_NUM)
  ) u_ysyx_041514_lfsr_rand (
      .clk_i        (clk),
      .rst_i        (rst),
      .alloc_i      (alloc_i),
      .alloc_entry_o(bht_alloc_entry)
  );

  wire[BHT_ENTRIES_WIDTH-1:0] bht_write_entry = bht_write_hit?bht_write_hit_entry:bht_alloc_entry;



  integer i2;
  wire bht_update_valid = bpu_update_valid_i & bpu_update_branch_type_i;
  wire bht_bi_inc_valid = bpu_update_taken_i && (bht_bi_reg[bht_write_entry] < 2'b11);
  wire bht_bi_dec_valid = (~bpu_update_taken_i) && (bht_bi_reg[bht_write_entry] > 2'b00);

  always @(posedge clk) begin
    if (rst) begin
      for (i2 = 0; i2 < BHT_NUM; i2 = i2 + 1) begin
        bht_pc_reg[i2] <= 'b0;
        bht_valid_reg[i2] <= 'b0;
        bht_bi_reg[i2] <= 'b0;
      end
    end else if (bht_update_valid) begin
      bht_pc_reg[bht_write_entry] <= bpu_update_pc_i;
      bht_valid_reg[bht_write_entry] <= 1'b1;

      if (bht_bi_inc_valid) begin
        bht_bi_reg[bht_write_entry] <= bht_bi_reg[bht_write_entry] + 'd1;
      end else if (bht_bi_dec_valid) begin
        bht_bi_reg[bht_write_entry] <= bht_bi_reg[bht_write_entry] - 'd1;
      end

    end
  end


endmodule

