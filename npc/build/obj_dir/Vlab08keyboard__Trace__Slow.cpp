// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab08keyboard__Syms.h"


void Vlab08keyboard___024root__traceInitSub0(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab08keyboard___024root__traceInitTop(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab08keyboard___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vlab08keyboard___024root__traceInitSub0(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+29,"clk", false,-1);
        tracep->declBit(c+30,"rst", false,-1);
        tracep->declBit(c+31,"ps2_clk", false,-1);
        tracep->declBit(c+32,"ps2_data", false,-1);
        tracep->declBus(c+33,"seg1", false,-1, 7,0);
        tracep->declBus(c+34,"seg2", false,-1, 7,0);
        tracep->declBus(c+35,"seg3", false,-1, 7,0);
        tracep->declBus(c+36,"seg4", false,-1, 7,0);
        tracep->declBus(c+37,"seg5", false,-1, 7,0);
        tracep->declBus(c+38,"seg6", false,-1, 7,0);
        tracep->declBus(c+39,"seg7", false,-1, 7,0);
        tracep->declBus(c+40,"seg8", false,-1, 7,0);
        tracep->declBit(c+29,"lab08keyboard clk", false,-1);
        tracep->declBit(c+30,"lab08keyboard rst", false,-1);
        tracep->declBit(c+31,"lab08keyboard ps2_clk", false,-1);
        tracep->declBit(c+32,"lab08keyboard ps2_data", false,-1);
        tracep->declBus(c+33,"lab08keyboard seg1", false,-1, 7,0);
        tracep->declBus(c+34,"lab08keyboard seg2", false,-1, 7,0);
        tracep->declBus(c+35,"lab08keyboard seg3", false,-1, 7,0);
        tracep->declBus(c+36,"lab08keyboard seg4", false,-1, 7,0);
        tracep->declBus(c+37,"lab08keyboard seg5", false,-1, 7,0);
        tracep->declBus(c+38,"lab08keyboard seg6", false,-1, 7,0);
        tracep->declBus(c+39,"lab08keyboard seg7", false,-1, 7,0);
        tracep->declBus(c+40,"lab08keyboard seg8", false,-1, 7,0);
        tracep->declBus(c+1,"lab08keyboard ps2out", false,-1, 7,0);
        tracep->declBus(c+2,"lab08keyboard ps2segin", false,-1, 23,0);
        tracep->declBit(c+3,"lab08keyboard ps2ready", false,-1);
        tracep->declBit(c+4,"lab08keyboard ps2next", false,-1);
        tracep->declBit(c+5,"lab08keyboard ps2over", false,-1);
        tracep->declBus(c+46,"lab08keyboard stateRead", false,-1, 3,0);
        tracep->declBus(c+47,"lab08keyboard stateNotify", false,-1, 3,0);
        tracep->declBus(c+48,"lab08keyboard stateNotify2", false,-1, 3,0);
        tracep->declBus(c+49,"lab08keyboard stateIdle", false,-1, 3,0);
        tracep->declBus(c+41,"lab08keyboard state_current", false,-1, 3,0);
        tracep->declBus(c+42,"lab08keyboard state_next", false,-1, 3,0);
        tracep->declBit(c+6,"lab08keyboard segen", false,-1);
        tracep->declBus(c+43,"lab08keyboard segcountl", false,-1, 3,0);
        tracep->declBus(c+44,"lab08keyboard segcounth", false,-1, 3,0);
        tracep->declBus(c+7,"lab08keyboard ascii", false,-1, 7,0);
        tracep->declBit(c+29,"lab08keyboard ps2keyboard clk", false,-1);
        tracep->declBit(c+45,"lab08keyboard ps2keyboard clrn", false,-1);
        tracep->declBit(c+31,"lab08keyboard ps2keyboard ps2_clk", false,-1);
        tracep->declBit(c+32,"lab08keyboard ps2keyboard ps2_data", false,-1);
        tracep->declBit(c+4,"lab08keyboard ps2keyboard nextdata_n", false,-1);
        tracep->declBus(c+1,"lab08keyboard ps2keyboard data", false,-1, 7,0);
        tracep->declBit(c+3,"lab08keyboard ps2keyboard ready", false,-1);
        tracep->declBit(c+5,"lab08keyboard ps2keyboard overflow", false,-1);
        tracep->declBus(c+8,"lab08keyboard ps2keyboard buffer", false,-1, 9,0);
        {int i; for (i=0; i<8; i++) {
                tracep->declBus(c+9+i*1,"lab08keyboard ps2keyboard fifo", true,(i+0), 7,0);}}
        tracep->declBus(c+17,"lab08keyboard ps2keyboard w_ptr", false,-1, 2,0);
        tracep->declBus(c+18,"lab08keyboard ps2keyboard r_ptr", false,-1, 2,0);
        tracep->declBus(c+19,"lab08keyboard ps2keyboard count", false,-1, 3,0);
        tracep->declBus(c+20,"lab08keyboard ps2keyboard ps2_clk_sync", false,-1, 2,0);
        tracep->declBit(c+21,"lab08keyboard ps2keyboard sampling", false,-1);
        tracep->declBus(c+22,"lab08keyboard seglow1 in", false,-1, 3,0);
        tracep->declBus(c+33,"lab08keyboard seglow1 out", false,-1, 7,0);
        tracep->declBit(c+6,"lab08keyboard seglow1 en", false,-1);
        tracep->declBus(c+23,"lab08keyboard seghigh1 in", false,-1, 3,0);
        tracep->declBus(c+34,"lab08keyboard seghigh1 out", false,-1, 7,0);
        tracep->declBit(c+6,"lab08keyboard seghigh1 en", false,-1);
        tracep->declBus(c+24,"lab08keyboard ps2ascii addr", false,-1, 7,0);
        tracep->declBus(c+7,"lab08keyboard ps2ascii val", false,-1, 7,0);
        tracep->declBus(c+25,"lab08keyboard seglow2 in", false,-1, 3,0);
        tracep->declBus(c+35,"lab08keyboard seglow2 out", false,-1, 7,0);
        tracep->declBit(c+6,"lab08keyboard seglow2 en", false,-1);
        tracep->declBus(c+26,"lab08keyboard seghigh2 in", false,-1, 3,0);
        tracep->declBus(c+36,"lab08keyboard seghigh2 out", false,-1, 7,0);
        tracep->declBit(c+6,"lab08keyboard seghigh2 en", false,-1);
        tracep->declBus(c+27,"lab08keyboard seglow3 in", false,-1, 3,0);
        tracep->declBus(c+37,"lab08keyboard seglow3 out", false,-1, 7,0);
        tracep->declBit(c+50,"lab08keyboard seglow3 en", false,-1);
        tracep->declBus(c+28,"lab08keyboard seghigh3 in", false,-1, 3,0);
        tracep->declBus(c+38,"lab08keyboard seghigh3 out", false,-1, 7,0);
        tracep->declBit(c+50,"lab08keyboard seghigh3 en", false,-1);
        tracep->declBus(c+43,"lab08keyboard segnuml in", false,-1, 3,0);
        tracep->declBus(c+39,"lab08keyboard segnuml out", false,-1, 7,0);
        tracep->declBit(c+51,"lab08keyboard segnuml en", false,-1);
        tracep->declBus(c+44,"lab08keyboard seghnumh in", false,-1, 3,0);
        tracep->declBus(c+40,"lab08keyboard seghnumh out", false,-1, 7,0);
        tracep->declBit(c+51,"lab08keyboard seghnumh en", false,-1);
    }
}

void Vlab08keyboard___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vlab08keyboard___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vlab08keyboard___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vlab08keyboard___024root__traceRegister(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vlab08keyboard___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vlab08keyboard___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vlab08keyboard___024root__traceCleanup, vlSelf);
    }
}

void Vlab08keyboard___024root__traceFullSub0(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vlab08keyboard___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab08keyboard___024root* const __restrict vlSelf = static_cast<Vlab08keyboard___024root*>(voidSelf);
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vlab08keyboard___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab08keyboard___024root__traceFullSub0(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo
                                  [vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr]),8);
        tracep->fullIData(oldp+2,(vlSelf->lab08keyboard__DOT__ps2segin),24);
        tracep->fullBit(oldp+3,(vlSelf->lab08keyboard__DOT__ps2ready));
        tracep->fullBit(oldp+4,(vlSelf->lab08keyboard__DOT__ps2next));
        tracep->fullBit(oldp+5,(vlSelf->lab08keyboard__DOT__ps2over));
        tracep->fullBit(oldp+6,(vlSelf->lab08keyboard__DOT__segen));
        tracep->fullCData(oldp+7,(vlSelf->lab08keyboard__DOT__ascii),8);
        tracep->fullSData(oldp+8,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer),10);
        tracep->fullCData(oldp+9,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[0]),8);
        tracep->fullCData(oldp+10,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[1]),8);
        tracep->fullCData(oldp+11,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[2]),8);
        tracep->fullCData(oldp+12,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[3]),8);
        tracep->fullCData(oldp+13,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[4]),8);
        tracep->fullCData(oldp+14,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[5]),8);
        tracep->fullCData(oldp+15,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[6]),8);
        tracep->fullCData(oldp+16,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[7]),8);
        tracep->fullCData(oldp+17,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr),3);
        tracep->fullCData(oldp+18,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr),3);
        tracep->fullCData(oldp+19,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count),4);
        tracep->fullCData(oldp+20,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync),3);
        tracep->fullBit(oldp+21,((IData)((4U == (6U 
                                                 & (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync))))));
        tracep->fullCData(oldp+22,((0xfU & vlSelf->lab08keyboard__DOT__ps2segin)),4);
        tracep->fullCData(oldp+23,((0xfU & (vlSelf->lab08keyboard__DOT__ps2segin 
                                            >> 4U))),4);
        tracep->fullCData(oldp+24,((0xffU & vlSelf->lab08keyboard__DOT__ps2segin)),8);
        tracep->fullCData(oldp+25,((0xfU & (IData)(vlSelf->lab08keyboard__DOT__ascii))),4);
        tracep->fullCData(oldp+26,((0xfU & ((IData)(vlSelf->lab08keyboard__DOT__ascii) 
                                            >> 4U))),4);
        tracep->fullCData(oldp+27,((0xfU & (vlSelf->lab08keyboard__DOT__ps2segin 
                                            >> 0x10U))),4);
        tracep->fullCData(oldp+28,((0xfU & (vlSelf->lab08keyboard__DOT__ps2segin 
                                            >> 0x14U))),4);
        tracep->fullBit(oldp+29,(vlSelf->clk));
        tracep->fullBit(oldp+30,(vlSelf->rst));
        tracep->fullBit(oldp+31,(vlSelf->ps2_clk));
        tracep->fullBit(oldp+32,(vlSelf->ps2_data));
        tracep->fullCData(oldp+33,(vlSelf->seg1),8);
        tracep->fullCData(oldp+34,(vlSelf->seg2),8);
        tracep->fullCData(oldp+35,(vlSelf->seg3),8);
        tracep->fullCData(oldp+36,(vlSelf->seg4),8);
        tracep->fullCData(oldp+37,(vlSelf->seg5),8);
        tracep->fullCData(oldp+38,(vlSelf->seg6),8);
        tracep->fullCData(oldp+39,(vlSelf->seg7),8);
        tracep->fullCData(oldp+40,(vlSelf->seg8),8);
        tracep->fullCData(oldp+41,(vlSelf->lab08keyboard__DOT__state_current),4);
        tracep->fullCData(oldp+42,(vlSelf->lab08keyboard__DOT__state_next),4);
        tracep->fullCData(oldp+43,(vlSelf->lab08keyboard__DOT__segcountl),4);
        tracep->fullCData(oldp+44,(vlSelf->lab08keyboard__DOT__segcounth),4);
        tracep->fullBit(oldp+45,((1U & (~ (IData)(vlSelf->rst)))));
        tracep->fullCData(oldp+46,(1U),4);
        tracep->fullCData(oldp+47,(2U),4);
        tracep->fullCData(oldp+48,(4U),4);
        tracep->fullCData(oldp+49,(8U),4);
        tracep->fullBit(oldp+50,(0U));
        tracep->fullBit(oldp+51,(1U));
    }
}
