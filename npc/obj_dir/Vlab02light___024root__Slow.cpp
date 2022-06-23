// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab02light.h for the primary calling header

#include "Vlab02light___024root.h"
#include "Vlab02light__Syms.h"

//==========


void Vlab02light___024root___ctor_var_reset(Vlab02light___024root* vlSelf);

Vlab02light___024root::Vlab02light___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab02light___024root___ctor_var_reset(this);
}

void Vlab02light___024root::__Vconfigure(Vlab02light__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab02light___024root::~Vlab02light___024root() {
}

void Vlab02light___024root___eval_initial(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

void Vlab02light___024root___eval_settle(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___eval_settle\n"); );
}

void Vlab02light___024root___final(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___final\n"); );
}

void Vlab02light___024root___ctor_var_reset(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->led = VL_RAND_RESET_I(16);
    vlSelf->lab02light__DOT__count = VL_RAND_RESET_I(32);
}
