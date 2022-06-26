// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab07rand8.h for the primary calling header

#include "Vlab07rand8___024root.h"
#include "Vlab07rand8__Syms.h"

//==========


void Vlab07rand8___024root___ctor_var_reset(Vlab07rand8___024root* vlSelf);

Vlab07rand8___024root::Vlab07rand8___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab07rand8___024root___ctor_var_reset(this);
}

void Vlab07rand8___024root::__Vconfigure(Vlab07rand8__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab07rand8___024root::~Vlab07rand8___024root() {
}

extern const VlUnpacked<CData/*7:0*/, 16> Vlab07rand8__ConstPool__TABLE_b791138e_0;

void Vlab07rand8___024root___settle__TOP__2(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___settle__TOP__2\n"); );
    // Variables
    CData/*3:0*/ __Vtableidx1;
    CData/*3:0*/ __Vtableidx2;
    // Body
    vlSelf->lab07rand8__DOT__newbit = (1U & VL_REDXOR_32(
                                                         (0x1dU 
                                                          & (IData)(vlSelf->out))));
    __Vtableidx1 = (0xfU & (IData)(vlSelf->out));
    vlSelf->seg1 = Vlab07rand8__ConstPool__TABLE_b791138e_0
        [__Vtableidx1];
    __Vtableidx2 = (0xfU & ((IData)(vlSelf->out) >> 4U));
    vlSelf->seg2 = Vlab07rand8__ConstPool__TABLE_b791138e_0
        [__Vtableidx2];
}

void Vlab07rand8___024root___eval_initial(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

void Vlab07rand8___024root___eval_settle(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___eval_settle\n"); );
    // Body
    Vlab07rand8___024root___settle__TOP__2(vlSelf);
}

void Vlab07rand8___024root___final(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___final\n"); );
}

void Vlab07rand8___024root___ctor_var_reset(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->out = 0;
    vlSelf->seg1 = 0;
    vlSelf->seg2 = 0;
    vlSelf->lab07rand8__DOT__newbit = 0;
}
