// case class MyTopLevel() extends Component {
//   val bim_update = new Bundle {
//     val req_i = in Bool ()
//     val type_i = in Bool ()
//     val data_i = in UInt (2 bits)
//     val data_o = out UInt (2 bits)
//   }

//   
//   val data = UInt(2 bits)

//   when(bim_update.req_i && bim_update.type_i) {
//     data := bim_update.data_i +| 1;
//   }.elsewhen(bim_update.req_i && !bim_update.type_i) {

//     data := bim_update.data_i -| 1;
//   }.otherwise(
//     data := 0
//   )

//   bim_update.data_o := data

// }


module ysyx_041514_bim_update (
    input        bim_update_req_i,
    input        bim_update_type_i,  // 1： 加 0: 减
    input  [1:0] bim_update_data_i,
    output [1:0] bim_update_data_o
);

  localparam bim_update_inc = 1'b1;
  localparam bim_update_dec = 1'b0;


  wire bim_is_full = bim_update_data_i == 2'b11;
  wire bim_is_empty = bim_update_data_i == 2'b00;

  wire inc_valid = !bim_is_full && bim_update_req_i;
  wire dec_valid = !bim_is_empty && bim_update_req_i;
  reg [1:0] _temp_data;

  always @(*) begin

    if ((bim_update_type_i == bim_update_inc) && inc_valid) begin
      _temp_data = bim_update_data_i + 2'd1;
    end else if ((bim_update_type_i == bim_update_dec) && dec_valid) begin
      _temp_data = bim_update_data_i - 2'd1;
    end else begin
      _temp_data = bim_update_data_i;
    end
  end

  assign bim_update_data_o = _temp_data;


endmodule
