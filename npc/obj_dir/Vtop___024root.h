// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop__Syms;

//----------

VL_MODULE(Vtop___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);

    // LOCAL SIGNALS
    CData/*4:0*/ top__DOT__u_dcode__DOT___rd_idx;
    CData/*0:0*/ top__DOT__u_memory__DOT___ls8byte;
    CData/*0:0*/ top__DOT__u_memory__DOT___ls16byte;
    CData/*0:0*/ top__DOT__u_memory__DOT___ls32byte;
    CData/*0:0*/ top__DOT__u_memory__DOT___unsigned;
    CData/*0:0*/ top__DOT__u_memory__DOT___signed;
    QData/*63:0*/ top__DOT__exc_out;
    QData/*63:0*/ top__DOT__u_pc__DOT___pc_next;
    QData/*63:0*/ top__DOT__u_pc__DOT___pc_current;
    QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv;
    QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res;
    QData/*63:0*/ top__DOT__u_memory__DOT___mem_read;
    VlUnpacked<QData/*63:0*/, 32> top__DOT__u_rv64reg__DOT__rf;

    // LOCAL VARIABLES
    CData/*0:0*/ __Vclklast__TOP__clk;
    QData/*63:0*/ __Vtask_top__DOT__u_fetch__DOT__pmem_read__0__rdata;
    QData/*63:0*/ __Vtask_top__DOT__u_memory__DOT__pmem_read__3__rdata;

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop___024root);  ///< Copying not allowed
  public:
    Vtop___024root(const char* name);
    ~Vtop___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
