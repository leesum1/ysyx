`include "sysconfig.v"
module ysyx_041514_memory (

    input clk,

    /* from databuff */
    input rdata_buff_valid_i,  // 读缓存有效
    input [`ysyx_041514_XLEN_BUS] rdata_buff_i,  // 读缓存


    input mem_fencei_ready_buff_i,
    input mem_fencei_buff_valid_i,
    /* from ex/mem */
    input [`ysyx_041514_XLEN_BUS] pc_i,
    input [`ysyx_041514_INST_LEN-1:0] inst_data_i,
    input [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_i,
    input [`ysyx_041514_XLEN_BUS] rs2_data_i,
    input [`ysyx_041514_MEMOP_LEN-1:0] mem_op_i,  // 访存操作码
    input [`ysyx_041514_XLEN_BUS] exc_alu_data_i,
    input [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_i,
    input [`ysyx_041514_XLEN_BUS] exc_csr_data_i,
    input exc_csr_valid_i,
    /* clint 接口 */
    output [`ysyx_041514_NPC_ADDR_BUS] clint_addr_o,
    output clint_valid_o,
    output clint_write_valid_o,
    output [`ysyx_041514_XLEN_BUS] clint_wdata_o,
    input [`ysyx_041514_XLEN_BUS] clint_rdata_i,
    /* dcache 接口 */
    output [`ysyx_041514_NPC_ADDR_BUS] mem_addr_o,  // 地址
    output mem_addr_valid_o,  // 地址是否有效
    output [7:0] mem_mask_o,  // 数据掩码,读取多少位
    output mem_write_valid_o,  // 1'b1,表示写;1'b0 表示读 
    output [3:0] mem_size_o,  // 数据宽度 8、4、2、1 byte
    input mem_data_ready_i,  // 读/写 数据是否准备好
    input [`ysyx_041514_XLEN_BUS] mem_rdata_i,  // 返回到读取的数据
    output [`ysyx_041514_XLEN_BUS] mem_wdata_o,  // 写入的数据
    output mem_fencei_valid_o,
    input mem_fencei_ready_i,
    /* to mem/wb */
    output [`ysyx_041514_XLEN_BUS] pc_o,
    output [`ysyx_041514_INST_LEN-1:0] inst_data_o,
    output [`ysyx_041514_XLEN_BUS] mem_data_o,  //同时送回 id 阶段（bypass）
    output [`ysyx_041514_REG_ADDRWIDTH-1:0] rd_idx_o,
    output [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_addr_o,
    output [`ysyx_041514_XLEN_BUS] exc_csr_data_o,
    output exc_csr_valid_o,
    /* stall req */
    output ram_stall_valid_mem_o,  // mem 阶段访存暂停
    /* TARP 总线 */
    input [`ysyx_041514_TRAP_BUS] trap_bus_i,
    output [`ysyx_041514_TRAP_BUS] trap_bus_o
);

  assign pc_o = pc_i;
  assign inst_data_o = inst_data_i;
  assign rd_idx_o = rd_idx_i;
  assign csr_addr_o = csr_addr_i;
  assign exc_csr_data_o = exc_csr_data_i;
  assign exc_csr_valid_o = exc_csr_valid_i;


  wire [`ysyx_041514_NPC_ADDR_BUS]  clint_addr;
  wire                              clint_valid;
  wire                              clint_write_valid;
  wire [    `ysyx_041514_XLEN_BUS]  clint_wdata;
  wire [    `ysyx_041514_XLEN_BUS]  clint_rdata;
  wire [    `ysyx_041514_XLEN_BUS]  mem_rdata;


  /* mem_op 译码 */
  wire                              ls_valid;
  wire                              ls_type;  // load:0,store:1
  wire                              ls_signed;  // signed:1,unsigned:0
  wire [                      3:0 ] ls_size;  // [8,4,2,1]
  wire                              fencei_valid;

  ysyx_041514_lsu_op u_ysyx_041514_lsu (
      .mem_op_i      (mem_op_i),
      .ls_valid_o    (ls_valid),
      .ls_type_o     (ls_type),
      .ls_signed_o   (ls_signed),
      .ls_size_o     (ls_size),
      .fencei_valid_o(fencei_valid)
  );

  wire _isload = (!ls_type) & ls_valid;
  wire _isstore = (ls_type) & ls_valid;
  wire _memop_none = !ls_valid;

  /* fencei 指令 */
  wire mem_fencei_ready_final = (mem_fencei_buff_valid_i)?mem_fencei_ready_buff_i:mem_fencei_ready_i;
  assign mem_fencei_valid_o = fencei_valid && (~mem_fencei_ready_final);


  /* 读取的数据 */
  wire [`ysyx_041514_XLEN_BUS] rdata_switch = (clint_valid) ? clint_rdata : mem_rdata;


  /* 读取数据符号扩展 */
  wire [`ysyx_041514_XLEN_BUS] mem_rdata_ext;
  ysyx_041514_lsu_ext u_ysyx_041514_lsu_ext_load (
      /* from ex/mem */
      .ext_data_i (rdata_switch),
      .ls_signed_i(ls_signed),
      // signed:1,unsigned:0
      .ls_size_i  (ls_size),
      // [8,4,2,1]
      .ext_data_o (mem_rdata_ext)
  );

  /* 写入数据处理 */
  wire [`ysyx_041514_XLEN_BUS] _mem_write;
  ysyx_041514_lsu_ext u_ysyx_041514_lsu_ext_store (
      /* from ex/mem */
      .ext_data_i (rs2_data_i),
      .ls_signed_i(`ysyx_041514_FALSE),
      // signed:1,unsigned:0
      .ls_size_i  (ls_size),
      // [8,4,2,1]
      .ext_data_o (_mem_write)
  );


  /*  mask 选择, byte 选通 */
  wire [7:0] _mask = ({8{ls_size[0]}}&8'b0000_0001)  
                   | ({8{ls_size[1]}}&8'b0000_0011) 
                   | ({8{ls_size[2]}}&8'b0000_1111) 
                   | ({8{ls_size[3]}}&8'b1111_1111);

  /* 地址 */
  wire [`ysyx_041514_XLEN_BUS] _addr = (ls_valid) ? exc_alu_data_i : `ysyx_041514_PC_RESET_ADDR;
  wire [2:0] addr_last3 = _addr[2:0];

  wire [7:0] rmask = _mask;
  wire [7:0] wmask = (_mask << addr_last3);


  /***************************** clint 接口 ************************************************/
  assign clint_addr = _addr[31:0];
  assign clint_valid = (_addr[31:0] == `ysyx_041514_MTIME_ADDR) | (_addr[31:0] == `ysyx_041514_MTIMECMP_ADDR);
  assign clint_write_valid = _isstore;
  assign clint_wdata = _mem_write;
  assign clint_rdata = clint_rdata_i;

  assign clint_addr_o = clint_addr;
  assign clint_valid_o = clint_valid;
  assign clint_write_valid_o = clint_write_valid;
  assign clint_wdata_o = clint_wdata;


  /***************************** dcache 接口 ************************************************/
  // cache_line_temp <= (mem_addr_i[3]) ? {{mem_wdata_i<<{addr_last3,3'b0}}, 64'b0} : {64'b0, {mem_wdata_i<<{addr_last3,3'b0}}};
  // 1. mem store 指令,需要将 waddr,wdata,wmask 对齐
  // 2. mem load 指令,需要调整 rmask,不能与 wmask 相同
  // 3. dcache 的 mask 和 data 需要调整
  // 4. axi write strobes 和 wdata 需要调整


  assign mem_addr_o = _addr[31:0];
  assign mem_mask_o = mem_write_valid_o ? wmask : rmask;
  assign mem_rdata = (mem_data_ready_i) ? (mem_rdata_i) : `ysyx_041514_XLEN'b0;


  // 访存有效条件
  // 1. 为访存指令
  // 2. 当前周期不是读数据返回周期、写数据成功周期(避免多次访存)
  // 3. 读数据缓存无效(避免多次访存，读数据缓存有效时，直接使用读数据缓存)
  // 4. 不是读写 clint mtime 指令
  assign mem_addr_valid_o = (ls_valid) & (~mem_data_ready_i) & (~rdata_buff_valid_i) & (~clint_valid);
  assign mem_write_valid_o = _isstore & mem_addr_valid_o;
  assign mem_wdata_o = _mem_write << {addr_last3, 3'b0};  // 对齐位置调整 TODO 移位器优化


  assign mem_size_o = ls_size;
  assign mem_data_o = 
      ({64{~rdata_buff_valid_i & _isload}}&mem_rdata_ext) |  // 使用直接返回的读数据
      ({64{rdata_buff_valid_i & _isload}} & rdata_buff_i) |  // 使用读数据缓存
      ({64{_memop_none}} & exc_alu_data_i);  // 不是访存指令，直接传递 alu 结果


  /* stall_req */
  assign ram_stall_valid_mem_o = mem_addr_valid_o | mem_fencei_valid_o;



  /* trap_bus TODO:add more*/
  wire _1byte_misaligned = `ysyx_041514_FALSE & ls_size[0];
  wire _2byte_misaligned = _addr[0] & ls_size[1];
  wire _4byte_misaligned = (|_addr[1:0]) & ls_size[2];
  wire _8byte_misaligned = (|_addr[2:0]) & ls_size[3];

  wire _addr_misaligned = _1byte_misaligned|_2byte_misaligned|_4byte_misaligned|_8byte_misaligned;
  wire _load_addr_misaligned = _isload & _addr_misaligned;
  wire _store_addr_misaligned = _isstore & _addr_misaligned;

  reg [`ysyx_041514_TRAP_BUS] _mem_trap_bus;
  integer i;
  always @(*) begin
    for (i = 0; i < `ysyx_041514_TRAP_LEN; i = i + 1) begin
      if (i == `ysyx_041514_TRAP_LOAD_ADDR_MISALIGNED) begin
        _mem_trap_bus[i] = _load_addr_misaligned;
      end else if (i == `ysyx_041514_TRAP_STORE_ADDR_MISALIGNED) begin
        _mem_trap_bus[i] = _store_addr_misaligned;
      end else if (i == `ysyx_041514_TRAP_FENCEI) begin  // fencei 复用 trap 线路，实现跳转
        _mem_trap_bus[i] = mem_fencei_valid_o;
      end else begin
        _mem_trap_bus[i] = trap_bus_i[i];
      end
    end
  end
  assign trap_bus_o = _mem_trap_bus;


  /************************××××××向仿真环境传递 PC *****************************/

`ifndef ysyx_041514_YSYX_SOC
  // 用于 difftest，获取 mem_pc
  import "DPI-C" function void set_mem_pc(input longint mem_pc);
  always @(*) begin
    if (ls_valid) begin
      set_mem_pc(pc_i);
    end
  end
`endif







endmodule
