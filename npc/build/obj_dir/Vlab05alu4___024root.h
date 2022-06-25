// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vlab05alu4.h for the primary calling header

#ifndef VERILATED_VLAB05ALU4___024ROOT_H_
#define VERILATED_VLAB05ALU4___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vlab05alu4__Syms;
class Vlab05alu4_VerilatedVcd;


//----------

VL_MODULE(Vlab05alu4___024root) {
  public:

    // PORTS
    VL_IN8(a,3,0);
    VL_IN8(b,3,0);
    VL_OUT8(out,3,0);
    VL_OUT8(CF,0,0);
    VL_OUT8(PF,0,0);
    VL_OUT8(AF,0,0);
    VL_OUT8(ZF,0,0);
    VL_OUT8(SF,0,0);
    VL_OUT8(OF,0,0);
    VL_IN8(sel,2,0);
    VL_OUT8(segout,7,0);

    // LOCAL SIGNALS
    CData/*7:0*/ lab05alu4__DOT__alu__DOT__d38out;
    CData/*4:0*/ lab05alu4__DOT__alu__DOT__subb;
    CData/*3:0*/ lab05alu4__DOT__alu__DOT__outps;
    CData/*0:0*/ lab05alu4__DOT__alu__DOT__subflag;
    CData/*0:0*/ lab05alu4__DOT__alu__DOT__psflag;

    // LOCAL VARIABLES
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vlab05alu4__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vlab05alu4___024root);  ///< Copying not allowed
  public:
    Vlab05alu4___024root(const char* name);
    ~Vlab05alu4___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vlab05alu4__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
