`include "./../sysconfig.v"

module rv64_csr_regfile (
    input clk,
    /* 读取数据 */
    input wire [`CSR_REG_ADDRWIDTH-1:0] csr_read_idx,
    output wire [`XLEN-1:0] csr_read_data,
    /* 写入数据 */
    input wire [`CSR_REG_ADDRWIDTH-1:0] csr_write_idx,
    input wire [`XLEN-1:0] csr_write_data,
    input wire csr_write_wen

);
  /***** CSR - Machine *****/

  //Machine Information Registers
  reg  [`XLEN-1:0] mvendorid;
  reg  [`XLEN-1:0] marchid;
  reg  [`XLEN-1:0] mimpid;
  reg  [`XLEN-1:0] mhartid;
  reg  [`XLEN-1:0] mconfigptr;

  //Machine Trap Setup
  reg  [`XLEN-1:0] mstatus;
  reg  [`XLEN-1:0] misa;
  reg  [`XLEN-1:0] medeleg;
  reg  [`XLEN-1:0] mideleg;
  reg  [`XLEN-1:0] mie;
  reg  [`XLEN-1:0] mtvec;
  reg  [`XLEN-1:0] mcounteren;
  //   reg [`XLEN-1:0] mstatush; rv32 only

  //Machine Trap Handling
  reg  [`XLEN-1:0] mscratch;
  reg  [`XLEN-1:0] mepc;
  reg  [`XLEN-1:0] mcause;
  reg  [`XLEN-1:0] mtval;
  reg  [`XLEN-1:0] mip;
  reg  [`XLEN-1:0] mtinst;
  reg  [`XLEN-1:0] mtval2;
  //Machine Configuration
  reg  [`XLEN-1:0] menvcfg;
  reg  [`XLEN-1:0] mseccfg;
  //   reg [`XLEN-1:0] menvcfgh; rv32 only
  //   reg [`XLEN-1:0] mseccfgh; rv32 only

  /* 读 csr 寄存器 */
  wire [`XLEN-1:0] _read_data;
  always @(*) begin
    case (csr_read_idx)
      `CSR_MVENDORID:  _read_data = mvendorid;
      `CSR_MARCHID:    _read_data = marchid;
      `CSR_MIMPID:     _read_data = mimpid;
      `CSR_MHARTID:    _read_data = mhartid;
      `CSR_MCONFIGPTR: _read_data = mconfigptr;
      `CSR_MSTATUS:    _read_data = mstatus;
      `CSR_MISA:       _read_data = misa;
      `CSR_MEDELEG:    _read_data = medeleg;
      `CSR_MIDELEG:    _read_data = mideleg;
      `CSR_MIE:        _read_data = mie;
      `CSR_MTVEC:      _read_data = mtvec;
      `CSR_MCOUNTEREN: _read_data = mcounteren;
      `CSR_MSCRATCH:   _read_data = mscratch;
      `CSR_MEPC:       _read_data = mepc;
      `CSR_MCAUSE:     _read_data = mcause;
      `CSR_MTVAL:      _read_data = mtval;
      `CSR_MIP:        _read_data = mip;
      `CSR_MTINST:     _read_data = mtinst;
      `CSR_MTVAL2:     _read_data = mtval2;
      `CSR_MENVCFG:    _read_data = menvcfg;
      `CSR_MSECCFG:    _read_data = mseccfg;
      default:         _read_data = `XLEN'b0;
    endcase
  end

  /* 写 csr 寄存器 */
  wire [`XLEN-1:0] _write_data = csr_write_data;
  always @(posedge clk) begin
    if (csr_write_wen == 1'b1) begin
      case (csr_write_idx)
        `CSR_MVENDORID:  mvendorid <= csr_write_data;
        `CSR_MARCHID:    marchid <= csr_write_data;
        `CSR_MIMPID:     mimpid <= csr_write_data;
        `CSR_MHARTID:    mhartid <= csr_write_data;
        `CSR_MCONFIGPTR: mconfigptr <= csr_write_data;
        `CSR_MSTATUS:    mstatus <= csr_write_data;
        `CSR_MISA:       misa <= csr_write_data;
        `CSR_MEDELEG:    medeleg <= csr_write_data;
        `CSR_MIDELEG:    mideleg <= csr_write_data;
        `CSR_MIE:        mie <= csr_write_data;
        `CSR_MTVEC:      mtvec <= csr_write_data;
        `CSR_MCOUNTEREN: mcounteren <= csr_write_data;
        `CSR_MSCRATCH:   mscratch <= csr_write_data;
        `CSR_MEPC:       mepc <= csr_write_data;
        `CSR_MCAUSE:     mcause <= csr_write_data;
        `CSR_MTVAL:      mtval <= csr_write_data;
        `CSR_MIP:        mip <= csr_write_data;
        `CSR_MTINST:     mtinst <= csr_write_data;
        `CSR_MTVAL2:     mtval2 <= csr_write_data;
        `CSR_MENVCFG:    menvcfg <= csr_write_data;
        `CSR_MSECCFG:    mseccfg <= csr_write_data;
        default: begin
        end
      endcase
    end
  end



















  //   always @(posedge clk) begin
  //     if (_wen) rf[write_idx] <= _write_data;
  //   end





endmodule


