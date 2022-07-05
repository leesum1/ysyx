// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vlab08keyboard.h for the primary calling header

#ifndef VERILATED_VLAB08KEYBOARD___024ROOT_H_
#define VERILATED_VLAB08KEYBOARD___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vlab08keyboard__Syms;
class Vlab08keyboard_VerilatedVcd;


//----------

VL_MODULE(Vlab08keyboard___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(ps2_clk,0,0);
    VL_IN8(ps2_data,0,0);
    VL_OUT8(seg1,7,0);
    VL_OUT8(seg2,7,0);
    VL_OUT8(seg3,7,0);
    VL_OUT8(seg4,7,0);
    VL_OUT8(seg5,7,0);
    VL_OUT8(seg6,7,0);
    VL_OUT8(seg7,7,0);
    VL_OUT8(seg8,7,0);

    // LOCAL SIGNALS
    CData/*0:0*/ lab08keyboard__DOT__segen;
    CData/*0:0*/ lab08keyboard__DOT__ps2ready;
    CData/*0:0*/ lab08keyboard__DOT__ps2next;
    CData/*0:0*/ lab08keyboard__DOT__ps2over;
    CData/*3:0*/ lab08keyboard__DOT__state_current;
    CData/*3:0*/ lab08keyboard__DOT__state_next;
    CData/*3:0*/ lab08keyboard__DOT__segcountl;
    CData/*3:0*/ lab08keyboard__DOT__segcounth;
    CData/*7:0*/ lab08keyboard__DOT__ascii;
    CData/*2:0*/ lab08keyboard__DOT__ps2keyboard__DOT__w_ptr;
    CData/*2:0*/ lab08keyboard__DOT__ps2keyboard__DOT__r_ptr;
    CData/*3:0*/ lab08keyboard__DOT__ps2keyboard__DOT__count;
    CData/*2:0*/ lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync;
    SData/*9:0*/ lab08keyboard__DOT__ps2keyboard__DOT__buffer;
    IData/*23:0*/ lab08keyboard__DOT__ps2segin;
    VlUnpacked<CData/*7:0*/, 8> lab08keyboard__DOT__ps2keyboard__DOT__fifo;

    // LOCAL VARIABLES
    CData/*0:0*/ lab08keyboard__DOT__ps2keyboard__DOT____Vlvbound1;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst;
    CData/*0:0*/ __Vclklast__TOP__lab08keyboard__DOT__segen;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vlab08keyboard__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vlab08keyboard___024root);  ///< Copying not allowed
  public:
    Vlab08keyboard___024root(const char* name);
    ~Vlab08keyboard___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vlab08keyboard__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
