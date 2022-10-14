`include "sysconfig.v"

module ysyx_041514_rv64_csr_regfile (
    input clk,
    input rst,
    /* 单独引出寄存器(写) */
    input wire [`ysyx_041514_XLEN-1:0] csr_mstatus_writedata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mepc_writedata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mcause_writedata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mtval_writedata_i,
    // input wire [`ysyx_041514_XLEN-1:0] csr_mtvec_writedata_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_mip_writedata_i,
    // input wire [`ysyx_041514_XLEN-1:0] csr_mie_writedata_i,
    input wire csr_mstatus_write_valid_i,
    input wire csr_mepc_write_valid_i,
    input wire csr_mcause_write_valid_i,
    input wire csr_mtval_write_valid_i,
    // input wire csr_mtvec_write_valid_i,
    input wire csr_mip_write_valid_i,
    // input wire csr_mie_write_valid_i,
    /* 单独引出寄存器(读) */
    output wire [`ysyx_041514_XLEN-1:0] csr_mstatus_readdata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mepc_readdata_o,
    // output wire [`ysyx_041514_XLEN-1:0] csr_mcause_readdata_o,
    // output wire [`ysyx_041514_XLEN-1:0] csr_mtval_readdata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mtvec_readdata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mip_readdata_o,
    output wire [`ysyx_041514_XLEN-1:0] csr_mie_readdata_o,
    /* 读取数据端口 */
    input wire [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_readaddr_i,
    output wire [`ysyx_041514_XLEN-1:0] csr_readdata_o,
    /* 写入数据端口 */
    input reg [`ysyx_041514_CSR_REG_ADDRWIDTH-1:0] csr_writeaddr_i,
    input csr_write_valid_i,
    input wire [`ysyx_041514_XLEN-1:0] csr_writedata_i
);


  // mstatus TODO 
  reg _mstatus_en;
  reg [`ysyx_041514_XLEN-1:0] _mstatus_q;
  wire [`ysyx_041514_XLEN-1:0] _mstatus_d = (csr_mstatus_write_valid_i) ? csr_mstatus_writedata_i : 
                                            (_mstatus_en)?csr_writedata_i:
                                            {_mstatus_q[63:13],1'b1,1'b1,_mstatus_q[10:0]};




  // mepc
  wire [`ysyx_041514_XLEN-1:0] _mepc_d = (csr_mepc_write_valid_i) ? csr_mepc_writedata_i : csr_writedata_i;
  reg [`ysyx_041514_XLEN-1:0] _mepc_q;
  reg _mepc_en;

  // mcause
  wire [`ysyx_041514_XLEN-1:0] _mcause_d = (csr_mcause_write_valid_i) ? csr_mcause_writedata_i : csr_writedata_i;
  reg [`ysyx_041514_XLEN-1:0] _mcause_q;
  reg _mcause_en;

  // mtval
  wire [`ysyx_041514_XLEN-1:0] _mtval_d = (csr_mtval_write_valid_i) ? csr_mtval_writedata_i : csr_writedata_i;
  reg [`ysyx_041514_XLEN-1:0] _mtval_q;
  reg _mtval_en;

  // mtvec
  wire [`ysyx_041514_XLEN-1:0] _mtvec_d = csr_writedata_i;
  reg [`ysyx_041514_XLEN-1:0] _mtvec_q;
  reg _mtvec_en;

  // mip TODO 设计不完善 目前只有 mtime 会使用
  reg _mip_en;
  reg [`ysyx_041514_XLEN-1:0] _mip_q;
  wire [`ysyx_041514_XLEN-1:0] _mip_d = (csr_mip_write_valid_i) ? csr_mip_writedata_i : 
                                        (_mip_en)?csr_writedata_i:
                                        {_mip_q[63:8],1'b0,_mip_q[6:0]}; // mtime 清 0



  // mie
  wire [`ysyx_041514_XLEN-1:0] _mie_d = csr_writedata_i;
  reg [`ysyx_041514_XLEN-1:0] _mie_q;
  reg _mie_en;


  /* 写使能 */
  always @(*) begin
    //需要赋初值防止生成 latch
    _mstatus_en = csr_mstatus_write_valid_i;
    _mepc_en = csr_mepc_write_valid_i;
    _mcause_en = csr_mcause_write_valid_i;
    _mtval_en = csr_mtval_write_valid_i;
    _mtvec_en = `ysyx_041514_FALSE;
    _mip_en = csr_mip_write_valid_i;
    _mie_en = `ysyx_041514_FALSE;
    case (csr_writeaddr_i)
      `ysyx_041514_CSR_MSTATUS: _mstatus_en = csr_write_valid_i;
      `ysyx_041514_CSR_MEPC: _mepc_en = csr_write_valid_i;
      `ysyx_041514_CSR_MCAUSE: _mcause_en = csr_write_valid_i;
      `ysyx_041514_CSR_MTVAL: _mtval_en = csr_write_valid_i;
      `ysyx_041514_CSR_MTVEC: _mtvec_en = csr_write_valid_i;
      `ysyx_041514_CSR_MIE: _mie_en = csr_write_valid_i;
      `ysyx_041514_CSR_MIP: _mip_en = csr_write_valid_i;
      default: ;
    endcase
  end

  /* 读取���据 */
  reg [`ysyx_041514_XLEN-1:0] _csr_readdata;
  always @(*) begin
    case (csr_readaddr_i)
      `ysyx_041514_CSR_MSTATUS: _csr_readdata = _mstatus_q;
      `ysyx_041514_CSR_MEPC: _csr_readdata = _mepc_q;
      `ysyx_041514_CSR_MCAUSE: _csr_readdata = _mcause_q;
      `ysyx_041514_CSR_MTVAL: _csr_readdata = _mtval_q;
      `ysyx_041514_CSR_MTVEC: _csr_readdata = _mtvec_q;
      `ysyx_041514_CSR_MIE: _csr_readdata = _mie_q;
      `ysyx_041514_CSR_MIP: _csr_readdata = _mip_q;
      default: _csr_readdata = `ysyx_041514_XLEN'b0;
    endcase
  end

  assign csr_readdata_o = _csr_readdata;

  assign csr_mepc_readdata_o = _mepc_q;
  //   assign csr_mcause_readdata_o = _mcause_q;
  //   assign csr_mtval_readdata_o = _mtval_q;
  assign csr_mtvec_readdata_o = _mtvec_q;
  assign csr_mstatus_readdata_o = _mstatus_q;
  assign csr_mie_readdata_o = _mie_q;
  assign csr_mip_readdata_o = _mip_q;


  /* CSR 寄存器组 */
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_CSR_MSTATUS_DEFAULT)  // TODO 为了 difftest
  ) u_csr_mstatus (
      .clk (clk),
      .rst (rst),
      .din (_mstatus_d),
      .dout(_mstatus_q),
      .wen (1'b1)
  );
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_mepc (
      .clk (clk),
      .rst (rst),
      .din (_mepc_d),
      .dout(_mepc_q),
      .wen (_mepc_en)
  );
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_mcause (
      .clk (clk),
      .rst (rst),
      .din (_mcause_d),
      .dout(_mcause_q),
      .wen (_mcause_en)
  );
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_mtval (
      .clk (clk),
      .rst (rst),
      .din (_mtval_d),
      .dout(_mtval_q),
      .wen (_mtval_en)
  );
  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_mtvec (
      .clk (clk),
      .rst (rst),
      .din (_mtvec_d),
      .dout(_mtvec_q),
      .wen (_mtvec_en)
  );

  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_mip (
      .clk (clk),
      .rst (rst),
      .din (_mip_d),
      .dout(_mip_q),
      .wen (1'b1)
  );

  ysyx_041514_regTemplate #(
      .WIDTH    (`ysyx_041514_XLEN),
      .RESET_VAL(`ysyx_041514_XLEN'b0)
  ) u_csr_mie (
      .clk (clk),
      .rst (rst),
      .din (_mie_d),
      .dout(_mie_q),
      .wen (_mie_en)
  );

endmodule
