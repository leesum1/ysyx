// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab08keyboard.h for the primary calling header

#include "Vlab08keyboard___024root.h"
#include "Vlab08keyboard__Syms.h"

//==========

extern const VlUnpacked<CData/*7:0*/, 256> Vlab08keyboard__ConstPool__TABLE_104519ac_0;
extern const VlUnpacked<CData/*7:0*/, 32> Vlab08keyboard__ConstPool__TABLE_88990450_0;

VL_INLINE_OPT void Vlab08keyboard___024root___sequent__TOP__2(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___sequent__TOP__2\n"); );
    // Variables
    CData/*4:0*/ __Vtableidx2;
    CData/*4:0*/ __Vtableidx3;
    CData/*7:0*/ __Vtableidx4;
    CData/*4:0*/ __Vtableidx5;
    CData/*4:0*/ __Vtableidx6;
    CData/*2:0*/ __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync;
    CData/*3:0*/ __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__count;
    CData/*2:0*/ __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__w_ptr;
    CData/*2:0*/ __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__r_ptr;
    CData/*0:0*/ __Vdly__lab08keyboard__DOT__ps2over;
    CData/*0:0*/ __Vdly__lab08keyboard__DOT__ps2ready;
    CData/*2:0*/ __Vdlyvdim0__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0;
    CData/*7:0*/ __Vdlyvval__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0;
    CData/*0:0*/ __Vdlyvset__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0;
    // Body
    __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync 
        = vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync;
    __Vdly__lab08keyboard__DOT__ps2over = vlSelf->lab08keyboard__DOT__ps2over;
    __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__r_ptr 
        = vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr;
    __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__w_ptr 
        = vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr;
    __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__count 
        = vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count;
    __Vdlyvset__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0 = 0U;
    __Vdly__lab08keyboard__DOT__ps2ready = vlSelf->lab08keyboard__DOT__ps2ready;
    __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync 
        = ((6U & ((IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync) 
                  << 1U)) | (IData)(vlSelf->ps2_clk));
    if (vlSelf->rst) {
        __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__count = 0U;
        __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__w_ptr = 0U;
        __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__r_ptr = 0U;
        __Vdly__lab08keyboard__DOT__ps2over = 0U;
        __Vdly__lab08keyboard__DOT__ps2ready = 0U;
    } else {
        if (vlSelf->lab08keyboard__DOT__ps2ready) {
            if ((1U & (~ (IData)(vlSelf->lab08keyboard__DOT__ps2next)))) {
                __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__r_ptr 
                    = (7U & ((IData)(1U) + (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr)));
                if (((IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr) 
                     == (7U & ((IData)(1U) + (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr))))) {
                    __Vdly__lab08keyboard__DOT__ps2ready = 0U;
                }
            }
        }
        if ((IData)((4U == (6U & (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync))))) {
            if ((0xaU == (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count))) {
                if ((((~ (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer)) 
                      & (IData)(vlSelf->ps2_data)) 
                     & VL_REDXOR_32((0x1ffU & ((IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer) 
                                               >> 1U))))) {
                    __Vdlyvval__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0 
                        = (0xffU & ((IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer) 
                                    >> 1U));
                    __Vdlyvset__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0 = 1U;
                    __Vdlyvdim0__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0 
                        = vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr;
                    __Vdly__lab08keyboard__DOT__ps2ready = 1U;
                    __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__w_ptr 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr)));
                    __Vdly__lab08keyboard__DOT__ps2over 
                        = ((IData)(vlSelf->lab08keyboard__DOT__ps2over) 
                           | ((IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr) 
                              == (7U & ((IData)(1U) 
                                        + (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr)))));
                }
                __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__count = 0U;
            } else {
                vlSelf->lab08keyboard__DOT__ps2keyboard__DOT____Vlvbound1 
                    = vlSelf->ps2_data;
                if ((9U >= (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count))) {
                    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer 
                        = (((~ ((IData)(1U) << (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count))) 
                            & (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer)) 
                           | (0x3ffU & ((IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT____Vlvbound1) 
                                        << (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count))));
                }
                __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__count 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count)));
            }
        }
    }
    if ((1U & (~ ((IData)(vlSelf->lab08keyboard__DOT__state_current) 
                  >> 3U)))) {
        if ((1U & (~ ((IData)(vlSelf->lab08keyboard__DOT__state_current) 
                      >> 2U)))) {
            if ((1U & (~ ((IData)(vlSelf->lab08keyboard__DOT__state_current) 
                          >> 1U)))) {
                if ((1U & (IData)(vlSelf->lab08keyboard__DOT__state_current))) {
                    vlSelf->lab08keyboard__DOT__ps2segin 
                        = ((0xffff00U & (vlSelf->lab08keyboard__DOT__ps2segin 
                                         << 8U)) | 
                           vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo
                           [vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr]);
                }
            }
        }
    }
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count 
        = __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__count;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr 
        = __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__w_ptr;
    vlSelf->lab08keyboard__DOT__ps2over = __Vdly__lab08keyboard__DOT__ps2over;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync 
        = __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync;
    vlSelf->lab08keyboard__DOT__ps2ready = __Vdly__lab08keyboard__DOT__ps2ready;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr 
        = __Vdly__lab08keyboard__DOT__ps2keyboard__DOT__r_ptr;
    if (__Vdlyvset__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0) {
        vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[__Vdlyvdim0__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0] 
            = __Vdlyvval__lab08keyboard__DOT__ps2keyboard__DOT__fifo__v0;
    }
    if ((8U & (IData)(vlSelf->lab08keyboard__DOT__state_current))) {
        vlSelf->lab08keyboard__DOT__ps2next = 1U;
    } else if ((4U & (IData)(vlSelf->lab08keyboard__DOT__state_current))) {
        vlSelf->lab08keyboard__DOT__ps2next = (IData)(
                                                      (0U 
                                                       != 
                                                       (3U 
                                                        & (IData)(vlSelf->lab08keyboard__DOT__state_current))));
    } else if ((2U & (IData)(vlSelf->lab08keyboard__DOT__state_current))) {
        vlSelf->lab08keyboard__DOT__ps2next = (1U & (IData)(vlSelf->lab08keyboard__DOT__state_current));
    } else if ((1U & (~ (IData)(vlSelf->lab08keyboard__DOT__state_current)))) {
        vlSelf->lab08keyboard__DOT__ps2next = 1U;
    }
    __Vtableidx4 = (0xffU & vlSelf->lab08keyboard__DOT__ps2segin);
    vlSelf->lab08keyboard__DOT__ascii = Vlab08keyboard__ConstPool__TABLE_104519ac_0
        [__Vtableidx4];
    vlSelf->lab08keyboard__DOT__segen = (1U & (~ ((0xf0U 
                                                   == 
                                                   (0xffU 
                                                    & (vlSelf->lab08keyboard__DOT__ps2segin 
                                                       >> 8U))) 
                                                  & ((0xffU 
                                                      & vlSelf->lab08keyboard__DOT__ps2segin) 
                                                     == 
                                                     (0xffU 
                                                      & (vlSelf->lab08keyboard__DOT__ps2segin 
                                                         >> 0x10U))))));
    __Vtableidx2 = ((0x1eU & (vlSelf->lab08keyboard__DOT__ps2segin 
                              << 1U)) | (IData)(vlSelf->lab08keyboard__DOT__segen));
    vlSelf->seg1 = Vlab08keyboard__ConstPool__TABLE_88990450_0
        [__Vtableidx2];
    __Vtableidx3 = ((0x1eU & (vlSelf->lab08keyboard__DOT__ps2segin 
                              >> 3U)) | (IData)(vlSelf->lab08keyboard__DOT__segen));
    vlSelf->seg2 = Vlab08keyboard__ConstPool__TABLE_88990450_0
        [__Vtableidx3];
    __Vtableidx5 = ((0x1eU & ((IData)(vlSelf->lab08keyboard__DOT__ascii) 
                              << 1U)) | (IData)(vlSelf->lab08keyboard__DOT__segen));
    vlSelf->seg3 = Vlab08keyboard__ConstPool__TABLE_88990450_0
        [__Vtableidx5];
    __Vtableidx6 = ((0x1eU & ((IData)(vlSelf->lab08keyboard__DOT__ascii) 
                              >> 3U)) | (IData)(vlSelf->lab08keyboard__DOT__segen));
    vlSelf->seg4 = Vlab08keyboard__ConstPool__TABLE_88990450_0
        [__Vtableidx6];
}

extern const VlUnpacked<CData/*3:0*/, 32> Vlab08keyboard__ConstPool__TABLE_884ab202_0;

VL_INLINE_OPT void Vlab08keyboard___024root___sequent__TOP__3(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___sequent__TOP__3\n"); );
    // Variables
    CData/*4:0*/ __Vtableidx1;
    // Body
    vlSelf->lab08keyboard__DOT__state_current = ((IData)(vlSelf->rst)
                                                  ? 8U
                                                  : (IData)(vlSelf->lab08keyboard__DOT__state_next));
    __Vtableidx1 = (((IData)(vlSelf->lab08keyboard__DOT__ps2ready) 
                     << 4U) | (IData)(vlSelf->lab08keyboard__DOT__state_current));
    vlSelf->lab08keyboard__DOT__state_next = Vlab08keyboard__ConstPool__TABLE_884ab202_0
        [__Vtableidx1];
}

extern const VlUnpacked<CData/*7:0*/, 16> Vlab08keyboard__ConstPool__TABLE_b791138e_0;

VL_INLINE_OPT void Vlab08keyboard___024root___sequent__TOP__4(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___sequent__TOP__4\n"); );
    // Variables
    CData/*3:0*/ __Vtableidx7;
    CData/*3:0*/ __Vtableidx8;
    CData/*3:0*/ __Vdly__lab08keyboard__DOT__segcountl;
    CData/*3:0*/ __Vdly__lab08keyboard__DOT__segcounth;
    // Body
    __Vdly__lab08keyboard__DOT__segcounth = vlSelf->lab08keyboard__DOT__segcounth;
    __Vdly__lab08keyboard__DOT__segcountl = vlSelf->lab08keyboard__DOT__segcountl;
    if (vlSelf->rst) {
        __Vdly__lab08keyboard__DOT__segcountl = 0U;
        __Vdly__lab08keyboard__DOT__segcounth = 0U;
    } else if ((9U == (IData)(vlSelf->lab08keyboard__DOT__segcountl))) {
        __Vdly__lab08keyboard__DOT__segcounth = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlSelf->lab08keyboard__DOT__segcounth)));
        __Vdly__lab08keyboard__DOT__segcountl = 0U;
    } else {
        __Vdly__lab08keyboard__DOT__segcountl = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlSelf->lab08keyboard__DOT__segcountl)));
    }
    vlSelf->lab08keyboard__DOT__segcountl = __Vdly__lab08keyboard__DOT__segcountl;
    vlSelf->lab08keyboard__DOT__segcounth = __Vdly__lab08keyboard__DOT__segcounth;
    __Vtableidx7 = vlSelf->lab08keyboard__DOT__segcountl;
    vlSelf->seg7 = Vlab08keyboard__ConstPool__TABLE_b791138e_0
        [__Vtableidx7];
    __Vtableidx8 = vlSelf->lab08keyboard__DOT__segcounth;
    vlSelf->seg8 = Vlab08keyboard__ConstPool__TABLE_b791138e_0
        [__Vtableidx8];
}

void Vlab08keyboard___024root___eval(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vlab08keyboard___024root___sequent__TOP__2(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    if ((((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk))) 
         | ((IData)(vlSelf->rst) & (~ (IData)(vlSelf->__Vclklast__TOP__rst))))) {
        Vlab08keyboard___024root___sequent__TOP__3(vlSelf);
    }
    if ((((~ (IData)(vlSelf->lab08keyboard__DOT__segen)) 
          & (IData)(vlSelf->__Vclklast__TOP__lab08keyboard__DOT__segen)) 
         | ((IData)(vlSelf->rst) & (~ (IData)(vlSelf->__Vclklast__TOP__rst))))) {
        Vlab08keyboard___024root___sequent__TOP__4(vlSelf);
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    vlSelf->__Vclklast__TOP__rst = vlSelf->rst;
    vlSelf->__Vclklast__TOP__lab08keyboard__DOT__segen 
        = vlSelf->lab08keyboard__DOT__segen;
}

QData Vlab08keyboard___024root___change_request_1(Vlab08keyboard___024root* vlSelf);

VL_INLINE_OPT QData Vlab08keyboard___024root___change_request(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___change_request\n"); );
    // Body
    return (Vlab08keyboard___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab08keyboard___024root___change_request_1(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab08keyboard___024root___eval_debug_assertions(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->ps2_clk & 0xfeU))) {
        Verilated::overWidthError("ps2_clk");}
    if (VL_UNLIKELY((vlSelf->ps2_data & 0xfeU))) {
        Verilated::overWidthError("ps2_data");}
}
#endif  // VL_DEBUG
