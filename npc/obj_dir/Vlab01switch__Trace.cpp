// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab01switch__Syms.h"


void Vlab01switch___024root__traceChgSub0(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep);

void Vlab01switch___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab01switch___024root* const __restrict vlSelf = static_cast<Vlab01switch___024root*>(voidSelf);
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vlab01switch___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab01switch___024root__traceChgSub0(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlSelf->a));
        tracep->chgBit(oldp+1,(vlSelf->b));
        tracep->chgBit(oldp+2,(vlSelf->f));
    }
}

void Vlab01switch___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    Vlab01switch___024root* const __restrict vlSelf = static_cast<Vlab01switch___024root*>(voidSelf);
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        __Vm_traceActivity[0U] = 0U;
    }
}
