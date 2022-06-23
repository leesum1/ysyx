// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab04ecode83__Syms.h"


void Vlab04ecode83___024root__traceInitSub0(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab04ecode83___024root__traceInitTop(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab04ecode83___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vlab04ecode83___024root__traceInitSub0(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+1,"in", false,-1, 7,0);
        tracep->declBit(c+2,"inflag", false,-1);
        tracep->declBus(c+3,"out", false,-1, 2,0);
        tracep->declBus(c+4,"seg", false,-1, 7,0);
        tracep->declBus(c+1,"lab04ecode83 in", false,-1, 7,0);
        tracep->declBit(c+2,"lab04ecode83 inflag", false,-1);
        tracep->declBus(c+3,"lab04ecode83 out", false,-1, 2,0);
        tracep->declBus(c+4,"lab04ecode83 seg", false,-1, 7,0);
        tracep->declBus(c+3,"lab04ecode83 seg38 in", false,-1, 2,0);
        tracep->declBus(c+4,"lab04ecode83 seg38 out", false,-1, 7,0);
    }
}

void Vlab04ecode83___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vlab04ecode83___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vlab04ecode83___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vlab04ecode83___024root__traceRegister(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vlab04ecode83___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vlab04ecode83___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vlab04ecode83___024root__traceCleanup, vlSelf);
    }
}

void Vlab04ecode83___024root__traceFullSub0(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab04ecode83___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab04ecode83___024root* const __restrict vlSelf = static_cast<Vlab04ecode83___024root*>(voidSelf);
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab04ecode83___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab04ecode83___024root__traceFullSub0(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlSelf->in),8);
        tracep->fullBit(oldp+2,(vlSelf->inflag));
        tracep->fullCData(oldp+3,(vlSelf->out),3);
        tracep->fullCData(oldp+4,(vlSelf->seg),8);
    }
}
