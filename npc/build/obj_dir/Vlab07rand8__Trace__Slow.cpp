// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab07rand8__Syms.h"


void Vlab07rand8___024root__traceInitSub0(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab07rand8___024root__traceInitTop(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab07rand8___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vlab07rand8___024root__traceInitSub0(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"clk", false,-1);
        tracep->declBus(c+2,"out", false,-1, 7,0);
        tracep->declBus(c+3,"seg1", false,-1, 7,0);
        tracep->declBus(c+4,"seg2", false,-1, 7,0);
        tracep->declBit(c+1,"lab07rand8 clk", false,-1);
        tracep->declBus(c+2,"lab07rand8 out", false,-1, 7,0);
        tracep->declBus(c+3,"lab07rand8 seg1", false,-1, 7,0);
        tracep->declBus(c+4,"lab07rand8 seg2", false,-1, 7,0);
        tracep->declBit(c+5,"lab07rand8 newbit", false,-1);
        tracep->declBus(c+6,"lab07rand8 seglow in", false,-1, 3,0);
        tracep->declBus(c+3,"lab07rand8 seglow out", false,-1, 7,0);
        tracep->declBus(c+7,"lab07rand8 seghigh in", false,-1, 3,0);
        tracep->declBus(c+4,"lab07rand8 seghigh out", false,-1, 7,0);
    }
}

void Vlab07rand8___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vlab07rand8___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vlab07rand8___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vlab07rand8___024root__traceRegister(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vlab07rand8___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vlab07rand8___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vlab07rand8___024root__traceCleanup, vlSelf);
    }
}

void Vlab07rand8___024root__traceFullSub0(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab07rand8___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab07rand8___024root* const __restrict vlSelf = static_cast<Vlab07rand8___024root*>(voidSelf);
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab07rand8___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab07rand8___024root__traceFullSub0(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlSelf->clk));
        tracep->fullCData(oldp+2,(vlSelf->out),8);
        tracep->fullCData(oldp+3,(vlSelf->seg1),8);
        tracep->fullCData(oldp+4,(vlSelf->seg2),8);
        tracep->fullBit(oldp+5,((1U & VL_REDXOR_32(
                                                   (0x1dU 
                                                    & (IData)(vlSelf->out))))));
        tracep->fullCData(oldp+6,((0xfU & (IData)(vlSelf->out))),4);
        tracep->fullCData(oldp+7,((0xfU & ((IData)(vlSelf->out) 
                                           >> 4U))),4);
    }
}
