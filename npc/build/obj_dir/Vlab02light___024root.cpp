// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab02light.h for the primary calling header

#include "Vlab02light___024root.h"
#include "Vlab02light__Syms.h"

//==========

VL_INLINE_OPT void Vlab02light___024root___sequent__TOP__1(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___sequent__TOP__1\n"); );
    // Variables
    SData/*15:0*/ __Vdly__led;
    IData/*31:0*/ __Vdly__lab02light__DOT__count;
    // Body
    __Vdly__lab02light__DOT__count = vlSelf->lab02light__DOT__count;
    __Vdly__led = vlSelf->led;
    if (vlSelf->rst) {
        __Vdly__led = 1U;
        __Vdly__lab02light__DOT__count = 0U;
    } else {
        if ((0U == vlSelf->lab02light__DOT__count)) {
            __Vdly__led = ((0xfffeU & ((IData)(vlSelf->led) 
                                       << 1U)) | (1U 
                                                  & ((IData)(vlSelf->led) 
                                                     >> 0xfU)));
        }
        __Vdly__lab02light__DOT__count = ((0x7a120U 
                                           <= vlSelf->lab02light__DOT__count)
                                           ? 0U : ((IData)(1U) 
                                                   + vlSelf->lab02light__DOT__count));
    }
    vlSelf->led = __Vdly__led;
    vlSelf->lab02light__DOT__count = __Vdly__lab02light__DOT__count;
}

void Vlab02light___024root___eval(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vlab02light___024root___sequent__TOP__1(vlSelf);
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

QData Vlab02light___024root___change_request_1(Vlab02light___024root* vlSelf);

VL_INLINE_OPT QData Vlab02light___024root___change_request(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___change_request\n"); );
    // Body
    return (Vlab02light___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab02light___024root___change_request_1(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab02light___024root___eval_debug_assertions(Vlab02light___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab02light___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
