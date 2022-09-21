`include "sysconfig.v"
module memory (

    /* from mem/wb */
    input                           rdata_buff_valid_i,     // 读缓存有效
    input  [             `XLEN_BUS] rdata_buff_i,           // 读缓存
    /* from ex/mem */
    input  [             `XLEN_BUS] pc_i,
    input  [         `INST_LEN-1:0] inst_data_i,
    input  [    `REG_ADDRWIDTH-1:0] rd_idx_i,
    input  [             `XLEN_BUS] rs2_data_i,
    input  [        `MEMOP_LEN-1:0] mem_op_i,               // 访存操作码
    input  [             `XLEN_BUS] exc_alu_data_i,
    input  [`CSR_REG_ADDRWIDTH-1:0] csr_addr_i,
    input  [             `XLEN_BUS] exc_csr_data_i,
    input                           exc_csr_valid_i,
    /* dcache 接口 */
    output [         `NPC_ADDR_BUS] mem_addr_o,             // 地址
    output                          mem_addr_valid_o,       // 地址是否有效
    output [                   7:0] mem_mask_o,             // 数据掩码,读取多少位
    output                          mem_write_valid_o,      // 1'b1,表示写;1'b0 表示读 
    output [                   3:0] mem_size_o,             // 数据宽度 8、4、2、1 byte
    input                           mem_data_ready_i,       // 读/写 数据是否准备好
    input  [             `XLEN_BUS] mem_rdata_i,            // 返回到读取的数据
    output [             `XLEN_BUS] mem_wdata_o,            // 写入的数据
    /* to mem/wb */
    output [             `XLEN_BUS] pc_o,
    output [         `INST_LEN-1:0] inst_data_o,
    output [             `XLEN_BUS] mem_data_o,             //同时送回 id 阶段（bypass）
    output [    `REG_ADDRWIDTH-1:0] rd_idx_o,
    output [`CSR_REG_ADDRWIDTH-1:0] csr_addr_o,
    output [             `XLEN_BUS] exc_csr_data_o,
    output                          exc_csr_valid_o,
    /* stall req */
    output                          ram_stall_valid_mem_o,  // mem 阶段访存暂停
    /* TARP 总线 */
    input  [             `TRAP_BUS] trap_bus_i,
    output [             `TRAP_BUS] trap_bus_o
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


  /* 为 load 指令 */
  wire _load_valid = _unsigned | _signed;

  /* 从内存中读取的数据 */
  wire [`XLEN_BUS] _mem_read;

  /* 符号扩展后的结果 TODO:改成并行编码*/
  // wire [     `XLEN_BUS] _mem_signed_out = (_ls8byte)?{{`XLEN-8{_mem_read[7]}},_mem_read[7:0]}:
  //                                  (_ls16byte)?{{`XLEN-16{_mem_read[15]}},_mem_read[15:0]}:
  //                                  (_ls32byte)?{{`XLEN-32{_mem_read[31]}},_mem_read[31:0]}:
  //                                  _mem_read;
  wire [     `XLEN_BUS] _mem_signed_out = ({64{_ls8byte}}&{{`XLEN-8{_mem_read[7]}},_mem_read[7:0]})
                                        | ({64{_ls16byte}}&{{`XLEN-16{_mem_read[15]}},_mem_read[15:0]})
                                        | ({64{_ls32byte}}&{{`XLEN-32{_mem_read[31]}},_mem_read[31:0]})
                                        | ({64{_ls64byte}}&_mem_read);

  /* 不进行符号扩展的结果 TODO:改成并行编码 */
  // wire [     `XLEN_BUS] _mem_unsigned_out = (_ls8byte)?{{`XLEN-8{1'b0}},_mem_read[7:0]}:
  //                                  (_ls16byte)?{{`XLEN-16{1'b0}},_mem_read[15:0]}:
  //                                  (_ls32byte)?{{`XLEN-32{1'b0}},_mem_read[31:0]}:
  //                                  _mem_read;
  wire [     `XLEN_BUS] _mem_unsigned_out = ({64{_ls8byte}}&{{`XLEN-8{1'b0}},_mem_read[7:0]})
                                          | ({64{_ls16byte}}&{{`XLEN-16{1'b0}},_mem_read[15:0]})
                                          | ({64{_ls32byte}}&{{`XLEN-32{1'b0}},_mem_read[31:0]})
                                          | ({64{_ls64byte}}&_mem_read);

  /* 选择最终读取的数据 */
  wire [`XLEN_BUS] _mem_final_out = ({64{_signed}}&_mem_signed_out)
                                  | ({64{_unsigned}}&_mem_unsigned_out);

  /* 写入数据选择 */
  wire [`XLEN_BUS] _mem_write = ({64{_ls8byte}}&{56'b0, rs2_data_i[7:0]})  
                              | ({64{_ls16byte}}&{48'b0, rs2_data_i[15:0]}) 
                              | ({64{_ls32byte}}&{32'b0, rs2_data_i[31:0]}) 
                              | ({64{_ls64byte}}&rs2_data_i);

  /*  mask 选择, byte 选通 */
  wire [7:0] _mask = ({8{_ls8byte}}&8'b0000_0001)  
                   | ({8{_ls16byte}}&8'b0000_0011) 
                   | ({8{_ls32byte}}&8'b0000_1111) 
                   | ({8{_ls64byte}}&8'b1111_1111);

  wire [7:0] rmask = _mask;
  wire [7:0] wmask = (_mask << addr_last3);

  wire [3:0] _mem_size = {
    _ls64byte, _ls32byte, _ls16byte, _ls8byte
  };  // 全为 0 时，表示没有数据写入或读取

  // wire [7:0] _wmask = (_isstore) ? _mask : 8'b0000_0000;
  // wire [7:0] _rmask = (_isload) ? _mask : 8'b0000_0000;

  /* 地址 */
  wire [`XLEN_BUS] _addr = (_memop_none) ? `PC_RESET_ADDR : exc_alu_data_i;
  // wire [`XLEN_BUS] _raddr = _addr;
  // wire [`XLEN_BUS] _waddr = _addr;

  /** dcache  接口 **/
  // cache_line_temp <= (mem_addr_i[3]) ? {{mem_wdata_i<<{addr_last3,3'b0}}, 64'b0} : {64'b0, {mem_wdata_i<<{addr_last3,3'b0}}};
  // 1. mem store 指令,需要将 waddr,wdata,wmask 对齐
  // 2. mem load 指令,需要调整 rmask,不能与 wmask 相同
  // 3. dcache 的 mask 和 data 需要调整
  // 4. axi write strobes 和 wdata 需要调整
  wire [2:0] addr_last3 = _addr[2:0];

  assign mem_addr_o = _addr[31:0];
  assign mem_mask_o = mem_write_valid_o ? wmask : rmask;
  //assign mem_mask_o = (_mask << addr_last3);
  assign _mem_read = (mem_data_ready_i) ? (mem_rdata_i) : `XLEN'b0;
  // 访存有效条件
  // 1. 为访存指令
  // 2. 当前周期不是读数据返回周期、写数据成功周期(避免多次访存)
  // 3. 读数据缓存无效(避免多次访存，读数据缓存有效时，直接使用读数据缓存)
  assign mem_addr_valid_o = (_isload | _isstore) & (~mem_data_ready_i) & (~rdata_buff_valid_i);
  assign mem_write_valid_o = _isstore & (~mem_data_ready_i) & mem_addr_valid_o;
  assign mem_wdata_o = _mem_write << {addr_last3, 3'b0};  // 对齐位置调整
  assign mem_size_o = _mem_size;
  assign mem_data_o = ({64{~rdata_buff_valid_i & _load_valid}}&_mem_final_out) |  // 使用直接返回的读数据
      ({64{rdata_buff_valid_i & _load_valid}} & rdata_buff_i) |  // 使用读数据缓存
      ({64{_memop_none}} & exc_alu_data_i);  // 不是访存指令，直接传递 alu 结果



  /* stall_req */
  assign ram_stall_valid_mem_o = mem_addr_valid_o;





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

  // 用于 difftest，获��访��指令的 pc
  import "DPI-C" function void set_mem_pc(input longint mem_pc);
  always @(*) begin
    if (_isstore | _isload) begin
      set_mem_pc(pc_i);
    end
  end

endmodule
