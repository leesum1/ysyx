// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vlab01switch.h for the primary calling header

#ifndef VERILATED_VLAB01SWITCH___024ROOT_H_
#define VERILATED_VLAB01SWITCH___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vlab01switch__Syms;
class Vlab01switch_VerilatedVcd;


//----------

VL_MODULE(Vlab01switch___024root) {
  public:

    // PORTS
    VL_IN8(a,0,0);
    VL_IN8(b,0,0);
    VL_OUT8(f,0,0);

    // INTERNAL VARIABLES
    Vlab01switch__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vlab01switch___024root);  ///< Copying not allowed
  public:
    Vlab01switch___024root(const char* name);
    ~Vlab01switch___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vlab01switch__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
