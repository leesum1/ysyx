// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab01switch.h for the primary calling header

#include "Vlab01switch___024root.h"
#include "Vlab01switch__Syms.h"

//==========


void Vlab01switch___024root___ctor_var_reset(Vlab01switch___024root* vlSelf);

Vlab01switch___024root::Vlab01switch___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab01switch___024root___ctor_var_reset(this);
}

void Vlab01switch___024root::__Vconfigure(Vlab01switch__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab01switch___024root::~Vlab01switch___024root() {
}

void Vlab01switch___024root___eval_initial(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___eval_initial\n"); );
}

void Vlab01switch___024root___combo__TOP__1(Vlab01switch___024root* vlSelf);

void Vlab01switch___024root___eval_settle(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___eval_settle\n"); );
    // Body
    Vlab01switch___024root___combo__TOP__1(vlSelf);
}

void Vlab01switch___024root___final(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___final\n"); );
}

void Vlab01switch___024root___ctor_var_reset(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->a = 0;
    vlSelf->b = 0;
    vlSelf->f = 0;
}
