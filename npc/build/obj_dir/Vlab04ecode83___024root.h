// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vlab04ecode83.h for the primary calling header

#ifndef VERILATED_VLAB04ECODE83___024ROOT_H_
#define VERILATED_VLAB04ECODE83___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vlab04ecode83__Syms;
class Vlab04ecode83_VerilatedVcd;


//----------

VL_MODULE(Vlab04ecode83___024root) {
  public:

    // PORTS
    VL_IN8(in,7,0);
    VL_OUT8(inflag,0,0);
    VL_OUT8(out,2,0);
    VL_OUT8(seg,7,0);

    // INTERNAL VARIABLES
    Vlab04ecode83__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vlab04ecode83___024root);  ///< Copying not allowed
  public:
    Vlab04ecode83___024root(const char* name);
    ~Vlab04ecode83___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vlab04ecode83__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
