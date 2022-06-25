// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab05alu4__Syms.h"


void Vlab05alu4___024root__traceChgSub0(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep);

void Vlab05alu4___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab05alu4___024root* const __restrict vlSelf = static_cast<Vlab05alu4___024root*>(voidSelf);
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vlab05alu4___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab05alu4___024root__traceChgSub0(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
            tracep->chgCData(oldp+0,(vlSelf->lab05alu4__DOT__alu__DOT__d38out),8);
            tracep->chgCData(oldp+1,(vlSelf->lab05alu4__DOT__alu__DOT__subb),5);
            tracep->chgCData(oldp+2,(vlSelf->lab05alu4__DOT__alu__DOT__outps),4);
            tracep->chgBit(oldp+3,(vlSelf->lab05alu4__DOT__alu__DOT__subflag));
            tracep->chgBit(oldp+4,(vlSelf->lab05alu4__DOT__alu__DOT__psflag));
        }
        tracep->chgCData(oldp+5,(vlSelf->a),4);
        tracep->chgCData(oldp+6,(vlSelf->b),4);
        tracep->chgCData(oldp+7,(vlSelf->out),4);
        tracep->chgBit(oldp+8,(vlSelf->CF));
        tracep->chgBit(oldp+9,(vlSelf->PF));
        tracep->chgBit(oldp+10,(vlSelf->AF));
        tracep->chgBit(oldp+11,(vlSelf->ZF));
        tracep->chgBit(oldp+12,(vlSelf->SF));
        tracep->chgBit(oldp+13,(vlSelf->OF));
        tracep->chgCData(oldp+14,(vlSelf->sel),3);
        tracep->chgCData(oldp+15,(vlSelf->segout),8);
        tracep->chgCData(oldp+16,((0xfU & (~ (IData)(vlSelf->a)))),4);
        tracep->chgCData(oldp+17,(((IData)(vlSelf->a) 
                                   & (IData)(vlSelf->b))),4);
        tracep->chgCData(oldp+18,(((IData)(vlSelf->a) 
                                   | (IData)(vlSelf->b))),4);
        tracep->chgCData(oldp+19,(((IData)(vlSelf->a) 
                                   ^ (IData)(vlSelf->b))),4);
        tracep->chgCData(oldp+20,((7U & (IData)(vlSelf->out))),3);
    }
}

void Vlab05alu4___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    Vlab05alu4___024root* const __restrict vlSelf = static_cast<Vlab05alu4___024root*>(voidSelf);
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
        vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    }
}
