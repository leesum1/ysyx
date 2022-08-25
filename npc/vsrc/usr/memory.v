`include "sysconfig.v"
module memory (
    input clk,
    input rst,

    /* from ex/mem */
    input  [             `XLEN_BUS] pc_i,
    input  [         `INST_LEN-1:0] inst_data_i,
    input  [    `REG_ADDRWIDTH-1:0] rd_idx_i,
    // input  [         `XLEN_BUS] rs1_data_i,
    input  [             `XLEN_BUS] rs2_data_i,
    // input  [      `IMM_LEN-1:0] imm_data_i,
    input  [        `MEMOP_LEN-1:0] mem_op_i,         // 访存操作码
    input  [             `XLEN_BUS] exc_alu_data_i,
    input  [`CSR_REG_ADDRWIDTH-1:0] csr_addr_i,
    input  [             `XLEN_BUS] exc_csr_data_i,
    input                           exc_csr_valid_i,
    // TARP 总线
    input  [             `TRAP_BUS] trap_bus_i,
    /* to mem/wb */
    output [             `XLEN_BUS] pc_o,
    output [         `INST_LEN-1:0] inst_data_o,
    output [             `XLEN_BUS] mem_data_o,       //同时送回 id 阶段（bypass）
    //output                          load_valid_o,          
    output [    `REG_ADDRWIDTH-1:0] rd_idx_o,
    output [`CSR_REG_ADDRWIDTH-1:0] csr_addr_o,
    output [             `XLEN_BUS] exc_csr_data_o,
    output                          exc_csr_valid_o,

    /* TARP 总线 */
    output [`TRAP_BUS] trap_bus_o
);

  assign pc_o = pc_i;
  assign inst_data_o = inst_data_i;
  assign rd_idx_o = rd_idx_i;
  assign csr_addr_o = csr_addr_i;
  assign exc_csr_data_o = exc_csr_data_i;
  assign exc_csr_valid_o = exc_csr_valid_i;




  wire _memop_none = (mem_op_i == `MEMOP_NONE);
  wire _memop_lb = (mem_op_i == `MEMOP_LB);
  wire _memop_lbu = (mem_op_i == `MEMOP_LBU);
  wire _memop_sb = (mem_op_i == `MEMOP_SB);
  wire _memop_lh = (mem_op_i == `MEMOP_LH);
  wire _memop_lhu = (mem_op_i == `MEMOP_LHU);
  wire _memop_sh = (mem_op_i == `MEMOP_SH);
  wire _memop_lw = (mem_op_i == `MEMOP_LW);
  wire _memop_lwu = (mem_op_i == `MEMOP_LWU);
  wire _memop_sw = (mem_op_i == `MEMOP_SW);
  wire _memop_ld = (mem_op_i == `MEMOP_LD);
  wire _memop_sd = (mem_op_i == `MEMOP_SD);

  /* 写入还是读取 */
  wire _isload = (_memop_lb |_memop_lbu |_memop_ld|_memop_lh|_memop_lhu|_memop_lw|_memop_lwu);
  wire _isstore = (_memop_sb | _memop_sd | _memop_sh | _memop_sw);

  /* 读取或写入的 byte */
  wire _ls8byte = _memop_lb | _memop_lbu | _memop_sb;
  wire _ls16byte = _memop_lh | _memop_lhu | _memop_sh;
  wire _ls32byte = _memop_lw | _memop_sw | _memop_lwu;
  wire _ls64byte = _memop_ld | _memop_sd;

  /* 是否进行符号扩展 */
  wire _unsigned = _memop_lhu | _memop_lbu | _memop_lwu;
  wire _signed = _memop_lh | _memop_lb | _memop_lw | _memop_ld;


  /* 输出使能端口 */
  wire _load_valid = _unsigned | _signed;
  //assign load_valid_o = _load_valid;

  /* 从内存中读取的数据 */
  reg [`XLEN_BUS] _mem_read;

  /* 符号扩展后的结果 TODO:改成并行编码*/
  wire [     `XLEN_BUS] _mem__signed_out = (_ls8byte)?{{`XLEN-8{_mem_read[7]}},_mem_read[7:0]}:
                                   (_ls16byte)?{{`XLEN-16{_mem_read[15]}},_mem_read[15:0]}:
                                   (_ls32byte)?{{`XLEN-32{_mem_read[31]}},_mem_read[31:0]}:
                                   _mem_read;
  /* 不进行符号扩展的结果 TODO:改成并行编码 */
  wire [     `XLEN_BUS] _mem__unsigned_out = (_ls8byte)?{{`XLEN-8{1'b0}},_mem_read[7:0]}:
                                   (_ls16byte)?{{`XLEN-16{1'b0}},_mem_read[15:0]}:
                                   (_ls32byte)?{{`XLEN-32{1'b0}},_mem_read[31:0]}:
                                   _mem_read;
  /* 读取数据：选择最终结果 */
  wire [`XLEN_BUS] _mem_out = (_signed) ? _mem__signed_out: 
                               (_unsigned)? _mem__unsigned_out:
                               `XLEN'b0;

  // assign mem_data_o = _mem_out;
  // 选择最终写回的数据，算数运算指令或者 load 指令
  assign mem_data_o = (_load_valid) ? _mem_out : exc_alu_data_i;
  // assign wb_data_o = (load_valid_i) ? mem_data_i : exc_alu_data_i;


  /* 写入数据 */
  wire [`XLEN_BUS] _mem_write = (_ls8byte) ? {56'b0, rs2_data_i[7:0]} :
                                (_ls16byte) ? {48'b0, rs2_data_i[15:0]}:
                                (_ls32byte) ? {32'b0, rs2_data_i[31:0]}:
                                 rs2_data_i;

  /* 写数据 mask 选择,_mask:初步选择 _wmask:最终选择 */
  wire [7:0] _mask = ({8{_ls8byte}}&8'b0000_0001) |
                     ({8{_ls16byte}}&8'b0000_0011) |
                     ({8{_ls32byte}}&8'b0000_1111) |
                     ({8{_ls64byte}}&8'b1111_1111);

  wire [7:0] _wmask = (_isstore) ? _mask : 8'b0000_0000;
  wire [7:0] _rmask = (_isload) ? _mask : 8'b0000_0000;

  /* 地址 */
  wire [`XLEN_BUS] _addr = (_memop_none) ? `PC_RESET_ADDR : exc_alu_data_i;
  wire [`XLEN_BUS] _raddr = _addr;
  wire [`XLEN_BUS] _waddr = _addr;

  /***************************内存读写**************************/
  import "DPI-C" function void pmem_read(
    input longint pc,
    input longint raddr,
    output longint rdata,
    input byte rmask
  );
  import "DPI-C" function void pmem_write(
    input longint pc,
    input longint waddr,
    input longint wdata,
    input byte wmask
  );
  always @(*) begin
    _mem_read = `XLEN'b0;
    if (_isload) begin
      pmem_read(pc_i, _raddr, _mem_read, _rmask);
    end else if (_isstore) begin
      pmem_write(pc_i, _waddr, _mem_write, _wmask);
    end
  end


  /* trap_bus TODO:add more*/
  reg [`TRAP_BUS] _mem_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `TRAP_LEN; i = i + 1) begin
      _mem_trap_bus[i] = trap_bus_i[i];
    end
  end
  assign trap_bus_o = _mem_trap_bus;



  /************************××××××向仿真环境传递 PC *****************************/
  import "DPI-C" function void set_nextpc(input longint nextpc);

  always @(posedge clk) begin
    set_nextpc(pc_i);
  end

endmodule
