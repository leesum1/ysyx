// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab08keyboard.h for the primary calling header

#include "Vlab08keyboard___024root.h"
#include "Vlab08keyboard__Syms.h"

//==========


void Vlab08keyboard___024root___ctor_var_reset(Vlab08keyboard___024root* vlSelf);

Vlab08keyboard___024root::Vlab08keyboard___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab08keyboard___024root___ctor_var_reset(this);
}

void Vlab08keyboard___024root::__Vconfigure(Vlab08keyboard__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab08keyboard___024root::~Vlab08keyboard___024root() {
}

extern const VlUnpacked<CData/*7:0*/, 256> Vlab08keyboard__ConstPool__TABLE_104519ac_0;
extern const VlUnpacked<CData/*3:0*/, 32> Vlab08keyboard__ConstPool__TABLE_884ab202_0;
extern const VlUnpacked<CData/*7:0*/, 16> Vlab08keyboard__ConstPool__TABLE_b791138e_0;
extern const VlUnpacked<CData/*7:0*/, 32> Vlab08keyboard__ConstPool__TABLE_88990450_0;

void Vlab08keyboard___024root___settle__TOP__1(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___settle__TOP__1\n"); );
    // Variables
    CData/*4:0*/ __Vtableidx1;
    CData/*4:0*/ __Vtableidx2;
    CData/*4:0*/ __Vtableidx3;
    CData/*7:0*/ __Vtableidx4;
    CData/*4:0*/ __Vtableidx5;
    CData/*4:0*/ __Vtableidx6;
    CData/*3:0*/ __Vtableidx7;
    CData/*3:0*/ __Vtableidx8;
    // Body
    vlSelf->seg5 = 0xffU;
    vlSelf->seg6 = 0xffU;
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
    __Vtableidx1 = (((IData)(vlSelf->lab08keyboard__DOT__ps2ready) 
                     << 4U) | (IData)(vlSelf->lab08keyboard__DOT__state_current));
    vlSelf->lab08keyboard__DOT__state_next = Vlab08keyboard__ConstPool__TABLE_884ab202_0
        [__Vtableidx1];
    __Vtableidx7 = vlSelf->lab08keyboard__DOT__segcountl;
    vlSelf->seg7 = Vlab08keyboard__ConstPool__TABLE_b791138e_0
        [__Vtableidx7];
    __Vtableidx8 = vlSelf->lab08keyboard__DOT__segcounth;
    vlSelf->seg8 = Vlab08keyboard__ConstPool__TABLE_b791138e_0
        [__Vtableidx8];
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

void Vlab08keyboard___024root___eval_initial(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    vlSelf->__Vclklast__TOP__rst = vlSelf->rst;
    vlSelf->__Vclklast__TOP__lab08keyboard__DOT__segen 
        = vlSelf->lab08keyboard__DOT__segen;
}

void Vlab08keyboard___024root___eval_settle(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___eval_settle\n"); );
    // Body
    Vlab08keyboard___024root___settle__TOP__1(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

void Vlab08keyboard___024root___final(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___final\n"); );
}

void Vlab08keyboard___024root___ctor_var_reset(Vlab08keyboard___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab08keyboard___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst = 0;
    vlSelf->ps2_clk = 0;
    vlSelf->ps2_data = 0;
    vlSelf->seg1 = 0;
    vlSelf->seg2 = 0;
    vlSelf->seg3 = 0;
    vlSelf->seg4 = 0;
    vlSelf->seg5 = 0;
    vlSelf->seg6 = 0;
    vlSelf->seg7 = 0;
    vlSelf->seg8 = 0;
    vlSelf->lab08keyboard__DOT__ps2segin = 0;
    vlSelf->lab08keyboard__DOT__ps2ready = 0;
    vlSelf->lab08keyboard__DOT__ps2next = 0;
    vlSelf->lab08keyboard__DOT__ps2over = 0;
    vlSelf->lab08keyboard__DOT__state_current = 0;
    vlSelf->lab08keyboard__DOT__state_next = 0;
    vlSelf->lab08keyboard__DOT__segen = 0;
    vlSelf->lab08keyboard__DOT__segcountl = 0;
    vlSelf->lab08keyboard__DOT__segcounth = 0;
    vlSelf->lab08keyboard__DOT__ascii = 0;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer = 0;
    for (int __Vi0=0; __Vi0<8; ++__Vi0) {
        vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[__Vi0] = 0;
    }
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr = 0;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr = 0;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count = 0;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync = 0;
    vlSelf->lab08keyboard__DOT__ps2keyboard__DOT____Vlvbound1 = 0;
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
