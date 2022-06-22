// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab01switch.h for the primary calling header

#include "Vlab01switch___024root.h"
#include "Vlab01switch__Syms.h"

//==========

VL_INLINE_OPT void Vlab01switch___024root___combo__TOP__1(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___combo__TOP__1\n"); );
    // Body
    vlSelf->f = ((IData)(vlSelf->a) ^ (IData)(vlSelf->b));
}

void Vlab01switch___024root___eval(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___eval\n"); );
    // Body
    Vlab01switch___024root___combo__TOP__1(vlSelf);
}

QData Vlab01switch___024root___change_request_1(Vlab01switch___024root* vlSelf);

VL_INLINE_OPT QData Vlab01switch___024root___change_request(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___change_request\n"); );
    // Body
    return (Vlab01switch___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab01switch___024root___change_request_1(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab01switch___024root___eval_debug_assertions(Vlab01switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab01switch___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xfeU))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xfeU))) {
        Verilated::overWidthError("b");}
}
#endif  // VL_DEBUG
