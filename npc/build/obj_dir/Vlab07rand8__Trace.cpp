// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab07rand8__Syms.h"


void Vlab07rand8___024root__traceChgSub0(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep);

void Vlab07rand8___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab07rand8___024root* const __restrict vlSelf = static_cast<Vlab07rand8___024root*>(voidSelf);
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vlab07rand8___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab07rand8___024root__traceChgSub0(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlSelf->clk));
        tracep->chgCData(oldp+1,(vlSelf->out),8);
        tracep->chgCData(oldp+2,(vlSelf->seg1),8);
        tracep->chgCData(oldp+3,(vlSelf->seg2),8);
        tracep->chgBit(oldp+4,((1U & VL_REDXOR_32((0x1dU 
                                                   & (IData)(vlSelf->out))))));
        tracep->chgCData(oldp+5,((0xfU & (IData)(vlSelf->out))),4);
        tracep->chgCData(oldp+6,((0xfU & ((IData)(vlSelf->out) 
                                          >> 4U))),4);
    }
}

void Vlab07rand8___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VlUnpacked<CData/*31:0*/, 1> __Vm_traceActivity;
    Vlab07rand8___024root* const __restrict vlSelf = static_cast<Vlab07rand8___024root*>(voidSelf);
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        __Vm_traceActivity[0U] = 0U;
    }
}
