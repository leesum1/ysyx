// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop__Syms;
class Vtop_VerilatedVcd;


//----------

VL_MODULE(Vtop___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(w_idx,4,0);
    VL_OUT8(inst_out,0,0);
    VL_IN(inst_data,31,0);
    VL_OUT64(pc,63,0);
    VL_IN64(w_data,63,0);

    // LOCAL SIGNALS
    CData/*3:0*/ top__DOT__alu_op;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_store;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_branch;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_jal;
    CData/*0:0*/ top__DOT__u_dcode__DOT___R_type;
    CData/*0:0*/ top__DOT__u_dcode__DOT___I_type;
    CData/*0:0*/ top__DOT__u_dcode__DOT___U_type;
    QData/*63:0*/ top__DOT__u_pc__DOT___pc_in;
    QData/*63:0*/ top__DOT__u_pc__DOT___pc_out;
    VlUnpacked<QData/*63:0*/, 32> top__DOT__u_rv64reg__DOT__rf;

    // LOCAL VARIABLES
    CData/*0:0*/ __Vclklast__TOP__clk;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

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
