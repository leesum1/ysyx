`include "sysconfig.v"

// 仲裁模块,if mem 同时读时,if 优先
module ram_arb (
    input clk,
    input rst,
    // if 访存请求端口（读）
    input [`NPC_ADDR_BUS] if_read_addr_i,  // if 阶段的 read
    input if_valid_i,  // 是否发起读请求
    input [7:0] if_rmask_i,  // 数据掩码
    output [`XLEN_BUS] if_rdata_o,  // 读数据返回mem
    output if_rdata_valid_o,  // 读数据是否有效
    // mem 访存请求端口（读）
    input [`NPC_ADDR_BUS] mem_read_addr_i,  // mem 阶段的 read
    input mem_valid_i,
    input [7:0] mem_rmask_i,
    output [`XLEN_BUS] mem_rdata_o,
    output mem_rdata_valid_o,
    // mem 访存请求端口（写）,独占
    input [`NPC_ADDR_BUS] mem_write_addr_i,  // mem 阶段的 write
    input mem_write_valid_i,
    input [7:0] mem_wmask_i,
    input [`XLEN_BUS] mem_wdata_i,
    output mem_wdata_ready_o  // 数据是否已经写入
);

  //machine state decode
  localparam STATE_LEN = 3;
  localparam IDLE = 3'd0;
  localparam MEM1 = 3'd1;
  localparam MEM2 = 3'd2;
  localparam MEM3 = 3'd3;
  localparam PREIDLE = 3'd4;

  import "DPI-C" function void pmem_read(
    input int raddr,
    output longint rdata,
    input byte rmask
  );

  import "DPI-C" function void pmem_write(
    input int waddr,
    input longint wdata,
    input byte wmask
  );


  /* mem 写 状态机(mem 独占一个写端口) */
  // 设置为 3 时钟周期写一次
  reg [`XLEN_BUS] _ram_wdata;
  reg [`NPC_ADDR_BUS] _ram_waddr;
  reg [7:0] _ram_wmask;
  reg _ram_write_ready;
  reg [STATE_LEN-1:0] _ram_write_state;

  always @(posedge clk) begin
    if (rst) begin
      _ram_wdata <= `XLEN'b0;
      _ram_waddr <= 32'b0;
      _ram_wmask <= 8'b0;
      _ram_write_ready <= `FALSE;
      _ram_write_state <= PREIDLE;
    end else begin
      case (_ram_write_state)
        PREIDLE: begin
          _ram_write_state <= IDLE;
        end
        IDLE: begin
          _ram_write_ready <= `FALSE;
          if (mem_write_valid_i) begin
            _ram_waddr <= mem_write_addr_i;
            _ram_wmask <= mem_wmask_i;
            _ram_wdata <= mem_wdata_i;
            _ram_write_state <= MEM1;
          end else begin
            _ram_write_state <= IDLE;
            _ram_waddr <= 32'b0;
            _ram_wmask <= 8'b0;
            _ram_wdata <= `XLEN'b0;
          end
        end
        MEM1: begin
          // 延时一个周期（可设置延时多个周期）
          _ram_write_ready <= `FALSE;
          if (mem_write_valid_i) begin
            _ram_waddr <= mem_write_addr_i;
            _ram_wmask <= mem_wmask_i;
            _ram_wdata <= mem_wdata_i;
            _ram_write_state <= MEM2;
          end else begin
            _ram_write_state <= IDLE;
            _ram_waddr <= 32'b0;
            _ram_wmask <= 8'b0;
            _ram_wdata <= `XLEN'b0;
          end
        end
        MEM2: begin
          // 发出写信号
          _ram_write_state <= IDLE;
          if (mem_write_valid_i) begin
            _ram_write_ready <= `TRUE;
          end else begin
            _ram_write_ready <= `FALSE;
          end
        end
        default: begin
        end
      endcase
    end
  end

  always @(*) begin
    if (_ram_write_ready) begin
      pmem_write(_ram_waddr, _ram_wdata, _ram_wmask);
    end
  end

  assign mem_wdata_ready_o = _ram_write_ready;





  /* mem 读 状态机（if 和 mem 共用一个读端口，mem 优先级高） */
  reg [`XLEN_BUS] _ram_rdata;
  reg [`NPC_ADDR_BUS] _ram_raddr;
  reg [7:0] _ram_rmask;
  reg _ram_read_valid;

  reg [STATE_LEN-1:0] _ram_read_state;
  // 用于记录当前访存部件
  reg _ram_if;
  reg _ram_mem;
  always @(posedge clk) begin
    if (rst) begin
      _ram_raddr <= 32'b0;
      _ram_rmask <= 8'b0;
      _ram_read_valid <= `FALSE;
      _ram_if <= `FALSE;
      _ram_mem <= `FALSE;
      _ram_read_state <= PREIDLE;
    end else begin
      case (_ram_read_state)
        // 接收 if 和 mem 的访存,并进行优先级判断
        PREIDLE: begin
          _ram_read_state <= IDLE;
        end
        IDLE: begin
          _ram_read_valid <= `FALSE;
          if (if_valid_i) begin
            _ram_raddr <= if_read_addr_i;
            _ram_rmask <= if_rmask_i;
            _ram_if <= `TRUE;
            _ram_mem <= `FALSE;
            _ram_read_state <= MEM2;
          end else if (mem_valid_i) begin
            _ram_raddr <= mem_read_addr_i;
            _ram_rmask <= mem_rmask_i;
            _ram_if <= `FALSE;
            _ram_mem <= `TRUE;
            _ram_read_state <= MEM2;
          end else begin
            _ram_raddr <= 32'b0;
            _ram_rmask <= 8'b0;
            _ram_if <= `FALSE;
            _ram_mem <= `FALSE;
            _ram_read_state <= IDLE;
          end
        end
        // MEM1: begin
        //   // 延时一个周期（可设置延时多个周期）
        //   if (mem_valid_i & _ram_mem) begin
        //     _ram_read_state <= MEM2;
        //   end else if (if_valid_i & _ram_if) begin
        //     _ram_read_state <= MEM2;
        //   end else begin
        //     _ram_read_state <= IDLE;
        //   end
        // end
        MEM2: begin
          if (if_valid_i & _ram_if) begin
            _ram_raddr <= if_read_addr_i;
            _ram_rmask <= if_rmask_i;
            _ram_read_state <= IDLE;
            _ram_read_valid <= `TRUE;
          end else if (mem_valid_i & _ram_mem) begin
            _ram_raddr <= mem_read_addr_i;
            _ram_rmask <= mem_rmask_i;
            _ram_read_state <= IDLE;
            _ram_read_valid <= `TRUE;
          end else begin
            _ram_read_valid <= `FALSE;
            _ram_read_state <= IDLE;
          end
        end
        MEM3: begin
        end
        default: begin
        end
      endcase
    end
  end


  always @(*) begin
    _ram_rdata = `XLEN'b0;
    if (_ram_read_valid) begin
      pmem_read(_ram_raddr, _ram_rdata, _ram_rmask);
    end
  end


  /* 根据优先级选择最后数据 */
  reg [`XLEN_BUS] _if_rdata_o;  // 读数据返回mem
  reg [`XLEN_BUS] _mem_rdata_o;
  reg _if_rdata_valid_o;  // 读数据是否有效
  reg _mem_rdata_valid_o;
  always @(*) begin
    // 默认值
    _mem_rdata_o = `XLEN'b0;
    _if_rdata_o = `XLEN'b0;
    _mem_rdata_valid_o = `FALSE;
    _if_rdata_valid_o = `FALSE;
    // if 读优先
    if (if_valid_i & _ram_if) begin
      _if_rdata_o = _ram_rdata;
      _if_rdata_valid_o = _ram_read_valid;
    end else if (mem_valid_i & _ram_mem) begin
      _mem_rdata_o = _ram_rdata;
      _mem_rdata_valid_o = _ram_read_valid;
    end  // if 读 

  end

  /* 输出指定 */
  assign mem_rdata_o = _mem_rdata_o;
  assign if_rdata_o = _if_rdata_o;
  assign mem_rdata_valid_o = _mem_rdata_valid_o;
  assign if_rdata_valid_o = _if_rdata_valid_o;


endmodule
