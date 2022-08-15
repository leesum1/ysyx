`include "./../sysconfig.v"

module rv64_csr_regfile (
    input clk,
    input rst,
    /* 单独引出寄存器(写) */
    input wire [`XLEN-1:0] csr_mstatus_writedata_i,
    input wire [`XLEN-1:0] csr_mepc_writedata_i,
    input wire [`XLEN-1:0] csr_mcause_writedata_i,
    input wire [`XLEN-1:0] csr_mtval_writedata_i,
    input wire [`XLEN-1:0] csr_mtvec_writedata_i,
    input wire csr_mstatus_write_valid_i,
    input wire csr_mepc_write_valid_i,
    input wire csr_mcause_write_valid_i,
    input wire csr_mtval_write_valid_i,
    input wire csr_mtvec_write_valid_i,
    /* 单独引出寄存器(读) */
    output wire [`XLEN-1:0] csr_mstatus_readdata_o,
    output wire [`XLEN-1:0] csr_mepc_readdata_o,
    output wire [`XLEN-1:0] csr_mcause_readdata_o,
    output wire [`XLEN-1:0] csr_mtval_readdata_o,
    output wire [`XLEN-1:0] csr_mtvec_readdata_o,

    /* 读取数据端口 */
    input wire [`CSR_REG_ADDRWIDTH-1:0] csr_readaddr_i,
    output wire [`XLEN-1:0] csr_readdata_o,
    /* 写入数据端口 */
    input reg [`CSR_REG_ADDRWIDTH-1:0] csr_writeaddr_i,
    input csr_write_valid_i,
    input wire [`XLEN-1:0] csr_writedata_i
);

  // mstatus
  wire [`XLEN-1:0] _mstatus_d = (csr_mstatus_write_valid_i) ? csr_mstatus_writedata_i : csr_writedata_i;
  reg [`XLEN-1:0] _mstatus_q;
  reg _mstatus_en;

  // mepc
  wire [`XLEN-1:0] _mepc_d = (csr_mepc_write_valid_i) ? csr_mepc_writedata_i : csr_writedata_i;
  reg [`XLEN-1:0] _mepc_q;
  reg _mepc_en;

  // mcause
  wire [`XLEN-1:0] _mcause_d = (csr_mcause_write_valid_i) ? csr_mcause_writedata_i : csr_writedata_i;
  reg [`XLEN-1:0] _mcause_q;
  reg _mcause_en;

  // mtval
  wire [`XLEN-1:0] _mtval_d = (csr_mtval_write_valid_i) ? csr_mtval_writedata_i : csr_writedata_i;
  reg [`XLEN-1:0] _mtval_q;
  reg _mtval_en;

  // mtvec
  wire [`XLEN-1:0] _mtvec_d = (csr_mtvec_write_valid_i) ? csr_mtvec_writedata_i : csr_writedata_i;
  reg [`XLEN-1:0] _mtvec_q;
  reg _mtvec_en;




  /* 写使能 */
  always @(*) begin
    //需要赋初值防止生成 latch
    _mstatus_en = csr_mstatus_write_valid_i;
    _mepc_en = csr_mepc_write_valid_i;
    _mcause_en = csr_mcause_write_valid_i;
    _mtval_en = csr_mtval_write_valid_i;
    _mtvec_en = csr_mtvec_write_valid_i;
    case (csr_writeaddr_i)
      `CSR_MSTATUS: _mstatus_en = csr_write_valid_i;
      `CSR_MEPC: _mepc_en = csr_write_valid_i;
      `CSR_MCAUSE: _mcause_en = csr_write_valid_i;
      `CSR_MTVAL: _mtval_en = csr_write_valid_i;
      `CSR_MTVEC: _mtvec_en = csr_write_valid_i;
      default: ;
    endcase
  end

  /* 读取数据 */
  reg [`XLEN-1:0] _csr_readdata;
  always @(*) begin
    case (csr_readaddr_i)
      `CSR_MSTATUS: _csr_readdata = _mstatus_q;
      `CSR_MEPC: _csr_readdata = _mepc_q;
      `CSR_MCAUSE: _csr_readdata = _mcause_q;
      `CSR_MTVAL: _csr_readdata = _mtval_q;
      `CSR_MTVEC: _csr_readdata = _mtvec_q;
      default: _csr_readdata = `XLEN'b0;
    endcase
  end

  assign csr_readdata_o = _csr_readdata;

  assign csr_mepc_readdata_o = _mepc_q;
  assign csr_mcause_readdata_o = _mcause_q;
  assign csr_mtval_readdata_o = _mtval_q;
  assign csr_mtvec_readdata_o = _mtvec_q;
  assign csr_mstatus_readdata_o = _mstatus_q;


  /* CSR 寄存器组 */
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`CSR_MSTATUS_DEFAULT)  // 为了 difftest
  ) u_csr_mstatus (
      .clk (clk),
      .rst (rst),
      .din (_mstatus_d),
      .dout(_mstatus_q),
      .wen (_mstatus_en)
  );
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_csr_mepc (
      .clk (clk),
      .rst (rst),
      .din (_mepc_d),
      .dout(_mepc_q),
      .wen (_mepc_en)
  );
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_csr_mcause (
      .clk (clk),
      .rst (rst),
      .din (_mcause_d),
      .dout(_mcause_q),
      .wen (_mcause_en)
  );
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_csr_mtval (
      .clk (clk),
      .rst (rst),
      .din (_mtval_d),
      .dout(_mtval_q),
      .wen (_mtval_en)
  );
  regTemplate #(
      .WIDTH    (`XLEN),
      .RESET_VAL(`XLEN'b0)
  ) u_csr_mtvec (
      .clk (clk),
      .rst (rst),
      .din (_mtvec_d),
      .dout(_mtvec_q),
      .wen (_mtvec_en)
  );

endmodule
