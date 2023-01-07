
module ysyx_041514_edge_detect (
    input  clk,
    input  io_data_in,
    output rise_o,
    output fall_o,
    output toggle_o

);

  wire data_edges_rise = ((!io_data_in_regNext) && io_data_in);
  wire data_edges_fall = (io_data_in_regNext && (!io_data_in));
  wire data_edges_toggle = (io_data_in_regNext != io_data_in);
  reg io_data_in_regNext;

  always @(posedge clk) begin
    io_data_in_regNext <= io_data_in;
  end

  assign rise_o   = data_edges_rise;
  assign fall_o   = data_edges_fall;
  assign toggle_o = data_edges_toggle;
  
endmodule


