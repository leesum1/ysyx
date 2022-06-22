// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab01switch__Syms.h"


void Vlab01switch___024root__traceInitSub0(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab01switch___024root__traceInitTop(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab01switch___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vlab01switch___024root__traceInitSub0(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"a", false,-1);
        tracep->declBit(c+2,"b", false,-1);
        tracep->declBit(c+3,"f", false,-1);
        tracep->declBit(c+1,"lab01switch a", false,-1);
        tracep->declBit(c+2,"lab01switch b", false,-1);
        tracep->declBit(c+3,"lab01switch f", false,-1);
    }
}

void Vlab01switch___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vlab01switch___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vlab01switch___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vlab01switch___024root__traceRegister(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vlab01switch___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vlab01switch___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vlab01switch___024root__traceCleanup, vlSelf);
    }
}

void Vlab01switch___024root__traceFullSub0(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab01switch___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab01switch___024root* const __restrict vlSelf = static_cast<Vlab01switch___024root*>(voidSelf);
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab01switch___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab01switch___024root__traceFullSub0(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlSelf->a));
        tracep->fullBit(oldp+2,(vlSelf->b));
        tracep->fullBit(oldp+3,(vlSelf->f));
    }
}
