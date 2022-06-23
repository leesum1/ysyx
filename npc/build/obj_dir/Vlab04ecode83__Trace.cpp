// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab04ecode83__Syms.h"


void Vlab04ecode83___024root__traceChgSub0(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep);

void Vlab04ecode83___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab04ecode83___024root* const __restrict vlSelf = static_cast<Vlab04ecode83___024root*>(voidSelf);
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vlab04ecode83___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab04ecode83___024root__traceChgSub0(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgCData(oldp+0,(vlSelf->in),8);
        tracep->chgBit(oldp+1,(vlSelf->inflag));
        tracep->chgCData(oldp+2,(vlSelf->out),3);
        tracep->chgCData(oldp+3,(vlSelf->seg),8);
    }
}

void Vlab04ecode83___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    Vlab04ecode83___024root* const __restrict vlSelf = static_cast<Vlab04ecode83___024root*>(voidSelf);
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        __Vm_traceActivity[0U] = 0U;
    }
}
