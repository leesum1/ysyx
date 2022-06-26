// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vlab07rand8.h for the primary calling header

#ifndef VERILATED_VLAB07RAND8___024ROOT_H_
#define VERILATED_VLAB07RAND8___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vlab07rand8__Syms;
class Vlab07rand8_VerilatedVcd;


//----------

VL_MODULE(Vlab07rand8___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_OUT8(out,7,0);
    VL_OUT8(seg1,7,0);
    VL_OUT8(seg2,7,0);

    // LOCAL SIGNALS
    CData/*0:0*/ lab07rand8__DOT__newbit;

    // LOCAL VARIABLES
    CData/*0:0*/ __Vclklast__TOP__clk;

    // INTERNAL VARIABLES
    Vlab07rand8__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vlab07rand8___024root);  ///< Copying not allowed
  public:
    Vlab07rand8___024root(const char* name);
    ~Vlab07rand8___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vlab07rand8__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
