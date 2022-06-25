// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab05alu4__Syms.h"


void Vlab05alu4___024root__traceInitSub0(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab05alu4___024root__traceInitTop(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab05alu4___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vlab05alu4___024root__traceInitSub0(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+6,"a", false,-1, 3,0);
        tracep->declBus(c+7,"b", false,-1, 3,0);
        tracep->declBus(c+8,"out", false,-1, 3,0);
        tracep->declBus(c+9,"CF", false,-1, 0,0);
        tracep->declBus(c+10,"PF", false,-1, 0,0);
        tracep->declBus(c+11,"AF", false,-1, 0,0);
        tracep->declBus(c+12,"ZF", false,-1, 0,0);
        tracep->declBus(c+13,"SF", false,-1, 0,0);
        tracep->declBus(c+14,"OF", false,-1, 0,0);
        tracep->declBus(c+15,"sel", false,-1, 2,0);
        tracep->declBus(c+16,"segout", false,-1, 7,0);
        tracep->declBus(c+6,"lab05alu4 a", false,-1, 3,0);
        tracep->declBus(c+7,"lab05alu4 b", false,-1, 3,0);
        tracep->declBus(c+8,"lab05alu4 out", false,-1, 3,0);
        tracep->declBus(c+9,"lab05alu4 CF", false,-1, 0,0);
        tracep->declBus(c+10,"lab05alu4 PF", false,-1, 0,0);
        tracep->declBus(c+11,"lab05alu4 AF", false,-1, 0,0);
        tracep->declBus(c+12,"lab05alu4 ZF", false,-1, 0,0);
        tracep->declBus(c+13,"lab05alu4 SF", false,-1, 0,0);
        tracep->declBus(c+14,"lab05alu4 OF", false,-1, 0,0);
        tracep->declBus(c+15,"lab05alu4 sel", false,-1, 2,0);
        tracep->declBus(c+16,"lab05alu4 segout", false,-1, 7,0);
        tracep->declBus(c+6,"lab05alu4 alu a", false,-1, 3,0);
        tracep->declBus(c+7,"lab05alu4 alu b", false,-1, 3,0);
        tracep->declBus(c+8,"lab05alu4 alu out", false,-1, 3,0);
        tracep->declBus(c+9,"lab05alu4 alu CF", false,-1, 0,0);
        tracep->declBus(c+10,"lab05alu4 alu PF", false,-1, 0,0);
        tracep->declBus(c+11,"lab05alu4 alu AF", false,-1, 0,0);
        tracep->declBus(c+12,"lab05alu4 alu ZF", false,-1, 0,0);
        tracep->declBus(c+13,"lab05alu4 alu SF", false,-1, 0,0);
        tracep->declBus(c+14,"lab05alu4 alu OF", false,-1, 0,0);
        tracep->declBus(c+15,"lab05alu4 alu sel", false,-1, 2,0);
        tracep->declBus(c+1,"lab05alu4 alu d38out", false,-1, 7,0);
        tracep->declBus(c+2,"lab05alu4 alu subb", false,-1, 4,0);
        tracep->declBus(c+3,"lab05alu4 alu outps", false,-1, 3,0);
        tracep->declBus(c+17,"lab05alu4 alu outn", false,-1, 3,0);
        tracep->declBus(c+18,"lab05alu4 alu outand", false,-1, 3,0);
        tracep->declBus(c+19,"lab05alu4 alu outor", false,-1, 3,0);
        tracep->declBus(c+20,"lab05alu4 alu outxor", false,-1, 3,0);
        tracep->declBit(c+4,"lab05alu4 alu subflag", false,-1);
        tracep->declBit(c+5,"lab05alu4 alu psflag", false,-1);
        tracep->declBus(c+15,"lab05alu4 alu d38 in", false,-1, 2,0);
        tracep->declBus(c+1,"lab05alu4 alu d38 out", false,-1, 7,0);
        tracep->declBus(c+21,"lab05alu4 seg38a in", false,-1, 2,0);
        tracep->declBus(c+16,"lab05alu4 seg38a out", false,-1, 7,0);
    }
}

void Vlab05alu4___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vlab05alu4___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vlab05alu4___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vlab05alu4___024root__traceRegister(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vlab05alu4___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vlab05alu4___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vlab05alu4___024root__traceCleanup, vlSelf);
    }
}

void Vlab05alu4___024root__traceFullSub0(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab05alu4___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab05alu4___024root* const __restrict vlSelf = static_cast<Vlab05alu4___024root*>(voidSelf);
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab05alu4___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab05alu4___024root__traceFullSub0(Vlab05alu4___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlSelf->lab05alu4__DOT__alu__DOT__d38out),8);
        tracep->fullCData(oldp+2,(vlSelf->lab05alu4__DOT__alu__DOT__subb),5);
        tracep->fullCData(oldp+3,(vlSelf->lab05alu4__DOT__alu__DOT__outps),4);
        tracep->fullBit(oldp+4,(vlSelf->lab05alu4__DOT__alu__DOT__subflag));
        tracep->fullBit(oldp+5,(vlSelf->lab05alu4__DOT__alu__DOT__psflag));
        tracep->fullCData(oldp+6,(vlSelf->a),4);
        tracep->fullCData(oldp+7,(vlSelf->b),4);
        tracep->fullCData(oldp+8,(vlSelf->out),4);
        tracep->fullBit(oldp+9,(vlSelf->CF));
        tracep->fullBit(oldp+10,(vlSelf->PF));
        tracep->fullBit(oldp+11,(vlSelf->AF));
        tracep->fullBit(oldp+12,(vlSelf->ZF));
        tracep->fullBit(oldp+13,(vlSelf->SF));
        tracep->fullBit(oldp+14,(vlSelf->OF));
        tracep->fullCData(oldp+15,(vlSelf->sel),3);
        tracep->fullCData(oldp+16,(vlSelf->segout),8);
        tracep->fullCData(oldp+17,((0xfU & (~ (IData)(vlSelf->a)))),4);
        tracep->fullCData(oldp+18,(((IData)(vlSelf->a) 
                                    & (IData)(vlSelf->b))),4);
        tracep->fullCData(oldp+19,(((IData)(vlSelf->a) 
                                    | (IData)(vlSelf->b))),4);
        tracep->fullCData(oldp+20,(((IData)(vlSelf->a) 
                                    ^ (IData)(vlSelf->b))),4);
        tracep->fullCData(oldp+21,((7U & (IData)(vlSelf->out))),3);
    }
}
