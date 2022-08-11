`include "./../sysconfig.v"
module memory (
    input                      clk,
    input                      rst,
    input [         `XLEN-1:0] pc,
    input [`REG_ADDRWIDTH-1:0] rd_idx,
    input [         `XLEN-1:0] rs1_data,
    input [         `XLEN-1:0] rs2_data,
    input [      `IMM_LEN-1:0] imm_data,
    input [    `MEMOP_LEN-1:0] mem_op,    // 访存操作码

    input [`XLEN-1:0] exc_in,

    output [`XLEN-1:0] mem_out,
    output             isloadEnable  //读数据使能
);
  wire _memop_none = (mem_op == `MEMOP_NONE);
  wire _memop_lb = (mem_op == `MEMOP_LB);
  wire _memop_lbu = (mem_op == `MEMOP_LBU);
  wire _memop_sb = (mem_op == `MEMOP_SB);
  wire _memop_lh = (mem_op == `MEMOP_LH);
  wire _memop_lhu = (mem_op == `MEMOP_LHU);
  wire _memop_sh = (mem_op == `MEMOP_SH);
  wire _memop_lw = (mem_op == `MEMOP_LW);
  wire _memop_lwu = (mem_op == `MEMOP_LWU);
  wire _memop_sw = (mem_op == `MEMOP_SW);
  wire _memop_ld = (mem_op == `MEMOP_LD);
  wire _memop_sd = (mem_op == `MEMOP_SD);

  /* 写入还是读取 */
  wire _isload = (_memop_lb |_memop_lbu |_memop_ld|_memop_lh|_memop_lhu|_memop_lw|_memop_lwu)&(~_memop_none);
  wire _isstore = (_memop_sb | _memop_sd | _memop_sh | _memop_sw) & (~_memop_none);

  /* 读取或写入的 byte */
  wire _ls8byte = _memop_lb | _memop_lbu | _memop_sb;
  wire _ls16byte = _memop_lh | _memop_lhu | _memop_sh;
  wire _ls32byte = _memop_lw | _memop_sw | _memop_lwu;
  wire _ls64byte = _memop_ld | _memop_sd;

  /* 是否进行符号扩展 */
  wire _unsigned = _memop_lhu | _memop_lbu | _memop_lwu;
  wire _signed = _memop_lh | _memop_lb | _memop_lw | _memop_ld;


  /* 输出使能端口 */
  wire _isloadEnable = _unsigned | _signed;
  assign isloadEnable = _isloadEnable;

  /* 从内存中读取的数据 */
  wire [`XLEN-1:0] _mem_read;

  /* 符号扩展后的结果 TODO:改成并行编码*/
  wire [     `XLEN-1:0] _mem__signed_out = (_ls8byte)?{{`XLEN-8{_mem_read[7]}},_mem_read[7:0]}:
                                   (_ls16byte)?{{`XLEN-16{_mem_read[15]}},_mem_read[15:0]}:
                                   (_ls32byte)?{{`XLEN-32{_mem_read[31]}},_mem_read[31:0]}:
                                   _mem_read;
  /* 不进行符号扩展的结果 TODO:改成并行编码 */
  wire [     `XLEN-1:0] _mem__unsigned_out = (_ls8byte)?{{`XLEN-8{1'b0}},_mem_read[7:0]}:
                                   (_ls16byte)?{{`XLEN-16{1'b0}},_mem_read[15:0]}:
                                   (_ls32byte)?{{`XLEN-32{1'b0}},_mem_read[31:0]}:
                                   _mem_read;
  /* 读取数据：选择最终结果 */
  wire [`XLEN-1:0] _mem_out = (_signed) ? _mem__signed_out: 
                               (_unsigned)? _mem__unsigned_out:
                               `XLEN'b0;

  assign mem_out = _mem_out;



  /* 写入数据 */
  wire [`XLEN-1:0] _mem_write = (_ls8byte) ? {56'b0, rs2_data[7:0]} :
                                (_ls16byte) ? {48'b0, rs2_data[15:0]}:
                                (_ls32byte) ? {32'b0, rs2_data[31:0]}:
                                 rs2_data;

  /* 写数据 mask 选择,_mask:初步选择 _wmask:最终选择 */
  wire [7:0] _mask = ({8{_ls8byte}}&8'b0000_0001) |
                     ({8{_ls16byte}}&8'b0000_0011) |
                     ({8{_ls32byte}}&8'b0000_1111) |
                     ({8{_ls64byte}}&8'b1111_1111);

  wire [7:0] _wmask = (_isstore) ? _mask : 8'b0000_0000;

  /* 地址 */
  wire [`XLEN-1:0] _addr = (_memop_none) ? `PC_RESET_ADDR : exc_in;
  wire [`XLEN-1:0] _raddr = _addr;
  wire [`XLEN-1:0] _waddr = _addr;

  /***************************内存读写**************************/
  import "DPI-C" function void pmem_read(
    input  longint raddr,
    output longint rdata
  );
  import "DPI-C" function void pmem_write(
    input longint waddr,
    input longint wdata,
    input byte wmask
  );

  // always @(*) begin
  //   pmem_read(_raddr, _mem_read);
  //   pmem_write(_waddr, _mem_write, _wmask);
  // end

  always @(posedge clk) begin
    pmem_read(_raddr, _mem_read);
    pmem_write(_waddr, _mem_write, _wmask);
  end

endmodule
