// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab07rand8.h for the primary calling header

#include "Vlab07rand8___024root.h"
#include "Vlab07rand8__Syms.h"

//==========

extern const VlUnpacked<CData/*7:0*/, 16> Vlab07rand8__ConstPool__TABLE_b791138e_0;

VL_INLINE_OPT void Vlab07rand8___024root___sequent__TOP__1(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___sequent__TOP__1\n"); );
    // Variables
    CData/*3:0*/ __Vtableidx1;
    CData/*3:0*/ __Vtableidx2;
    // Body
    vlSelf->out = ((0U == (IData)(vlSelf->out)) ? 1U
                    : (((IData)(vlSelf->lab07rand8__DOT__newbit) 
                        << 7U) | (0x7fU & ((IData)(vlSelf->out) 
                                           >> 1U))));
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

void Vlab07rand8___024root___eval(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vlab07rand8___024root___sequent__TOP__1(vlSelf);
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

QData Vlab07rand8___024root___change_request_1(Vlab07rand8___024root* vlSelf);

VL_INLINE_OPT QData Vlab07rand8___024root___change_request(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___change_request\n"); );
    // Body
    return (Vlab07rand8___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab07rand8___024root___change_request_1(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab07rand8___024root___eval_debug_assertions(Vlab07rand8___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab07rand8___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
