// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab04ecode83.h for the primary calling header

#include "Vlab04ecode83___024root.h"
#include "Vlab04ecode83__Syms.h"

//==========

extern const VlUnpacked<CData/*0:0*/, 256> Vlab04ecode83__ConstPool__TABLE_362cb652_0;
extern const VlUnpacked<CData/*2:0*/, 256> Vlab04ecode83__ConstPool__TABLE_026fb9a4_0;
extern const VlUnpacked<CData/*7:0*/, 8> Vlab04ecode83__ConstPool__TABLE_c5bd01dd_0;

VL_INLINE_OPT void Vlab04ecode83___024root___combo__TOP__1(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___combo__TOP__1\n"); );
    // Variables
    CData/*7:0*/ __Vtableidx1;
    CData/*2:0*/ __Vtableidx2;
    // Body
    __Vtableidx1 = vlSelf->in;
    vlSelf->inflag = Vlab04ecode83__ConstPool__TABLE_362cb652_0
        [__Vtableidx1];
    vlSelf->out = Vlab04ecode83__ConstPool__TABLE_026fb9a4_0
        [__Vtableidx1];
    __Vtableidx2 = vlSelf->out;
    vlSelf->seg = Vlab04ecode83__ConstPool__TABLE_c5bd01dd_0
        [__Vtableidx2];
}

void Vlab04ecode83___024root___eval(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___eval\n"); );
    // Body
    Vlab04ecode83___024root___combo__TOP__1(vlSelf);
}

QData Vlab04ecode83___024root___change_request_1(Vlab04ecode83___024root* vlSelf);

VL_INLINE_OPT QData Vlab04ecode83___024root___change_request(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___change_request\n"); );
    // Body
    return (Vlab04ecode83___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab04ecode83___024root___change_request_1(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab04ecode83___024root___eval_debug_assertions(Vlab04ecode83___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab04ecode83___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
