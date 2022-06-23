// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab04ecode83.h for the primary calling header

#include "Vlab04ecode83___024root.h"
#include "Vlab04ecode83__Syms.h"

//==========


void Vlab04ecode83___024root___ctor_var_reset(Vlab04ecode83___024root* vlSelf);

Vlab04ecode83___024root::Vlab04ecode83___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab04ecode83___024root___ctor_var_reset(this);
}

void Vlab04ecode83___024root::__Vconfigure(Vlab04ecode83__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab04ecode83___024root::~Vlab04ecode83___024root() {
}

void Vlab04ecode83___024root___eval_initial(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___eval_initial\n"); );
}

void Vlab04ecode83___024root___combo__TOP__1(Vlab04ecode83___024root* vlSelf);

void Vlab04ecode83___024root___eval_settle(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___eval_settle\n"); );
    // Body
    Vlab04ecode83___024root___combo__TOP__1(vlSelf);
}

void Vlab04ecode83___024root___final(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___final\n"); );
}

void Vlab04ecode83___024root___ctor_var_reset(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->in = 0;
    vlSelf->inflag = 0;
    vlSelf->out = 0;
    vlSelf->seg = 0;
}
