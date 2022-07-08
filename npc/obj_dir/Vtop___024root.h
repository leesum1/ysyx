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
    VL_OUT8(inst_en,0,0);
    VL_IN8(alu_op_i,3,0);
    VL_OUT8(OF,0,0);
    VL_OUT8(ZF,0,0);
    VL_OUT8(SLT,0,0);
    VL_OUT8(CF,0,0);
    VL_OUT8(SF,0,0);
    VL_IN(inst_data,31,0);
    VL_OUT64(pc,63,0);
    VL_IN64(alu_a_i,63,0);
    VL_IN64(alu_b_i,63,0);
    VL_OUT64(alu_out,63,0);
    VL_OUT64(sra_out,63,0);
    VL_OUT64(srl_out,63,0);
    VL_OUT64(sll_out,63,0);

    // LOCAL SIGNALS
    CData/*5:0*/ top__DOT__u_alu__DOT__shifter_in2;
    CData/*0:0*/ top__DOT__u_alu__DOT___op_shift;
    QData/*63:0*/ top__DOT__u_pc__DOT___pc_in;
    QData/*63:0*/ top__DOT__u_pc__DOT___pc_out;
    QData/*63:0*/ top__DOT__u_alu__DOT__shifter_in1_inv;
    QData/*63:0*/ top__DOT__u_alu__DOT__shifter_res;
    QData/*63:0*/ top__DOT__u_alu__DOT__srl_res;

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
