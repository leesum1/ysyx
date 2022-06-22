// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab02light__Syms.h"


void Vlab02light___024root__traceInitSub0(Vlab02light___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab02light___024root__traceInitTop(Vlab02light___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab02light___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vlab02light___024root__traceInitSub0(Vlab02light___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"clk", false,-1);
        tracep->declBit(c+2,"rst", false,-1);
        tracep->declBus(c+3,"led", false,-1, 15,0);
        tracep->declBit(c+1,"lab02light clk", false,-1);
        tracep->declBit(c+2,"lab02light rst", false,-1);
        tracep->declBus(c+3,"lab02light led", false,-1, 15,0);
        tracep->declBus(c+4,"lab02light count", false,-1, 31,0);
    }
}

void Vlab02light___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vlab02light___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vlab02light___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vlab02light___024root__traceRegister(Vlab02light___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vlab02light___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vlab02light___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vlab02light___024root__traceCleanup, vlSelf);
    }
}

void Vlab02light___024root__traceFullSub0(Vlab02light___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab02light___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab02light___024root* const __restrict vlSelf = static_cast<Vlab02light___024root*>(voidSelf);
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab02light___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab02light___024root__traceFullSub0(Vlab02light___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlSelf->clk));
        tracep->fullBit(oldp+2,(vlSelf->rst));
        tracep->fullSData(oldp+3,(vlSelf->led),16);
        tracep->fullIData(oldp+4,(vlSelf->lab02light__DOT__count),32);
    }
}
