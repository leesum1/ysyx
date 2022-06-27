// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vlab08keyboard__Syms.h"


void Vlab08keyboard___024root__traceChgSub0(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep);

void Vlab08keyboard___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vlab08keyboard___024root* const __restrict vlSelf = static_cast<Vlab08keyboard___024root*>(voidSelf);
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vlab08keyboard___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vlab08keyboard___024root__traceChgSub0(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
            tracep->chgCData(oldp+0,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo
                                     [vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr]),8);
            tracep->chgIData(oldp+1,(vlSelf->lab08keyboard__DOT__ps2segin),24);
            tracep->chgBit(oldp+2,(vlSelf->lab08keyboard__DOT__ps2ready));
            tracep->chgBit(oldp+3,(vlSelf->lab08keyboard__DOT__ps2next));
            tracep->chgBit(oldp+4,(vlSelf->lab08keyboard__DOT__ps2over));
            tracep->chgBit(oldp+5,(vlSelf->lab08keyboard__DOT__segen));
            tracep->chgCData(oldp+6,(vlSelf->lab08keyboard__DOT__ascii),8);
            tracep->chgSData(oldp+7,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__buffer),10);
            tracep->chgCData(oldp+8,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[0]),8);
            tracep->chgCData(oldp+9,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[1]),8);
            tracep->chgCData(oldp+10,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[2]),8);
            tracep->chgCData(oldp+11,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[3]),8);
            tracep->chgCData(oldp+12,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[4]),8);
            tracep->chgCData(oldp+13,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[5]),8);
            tracep->chgCData(oldp+14,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[6]),8);
            tracep->chgCData(oldp+15,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__fifo[7]),8);
            tracep->chgCData(oldp+16,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__w_ptr),3);
            tracep->chgCData(oldp+17,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__r_ptr),3);
            tracep->chgCData(oldp+18,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__count),4);
            tracep->chgCData(oldp+19,(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync),3);
            tracep->chgBit(oldp+20,((IData)((4U == 
                                             (6U & (IData)(vlSelf->lab08keyboard__DOT__ps2keyboard__DOT__ps2_clk_sync))))));
            tracep->chgCData(oldp+21,((0xfU & vlSelf->lab08keyboard__DOT__ps2segin)),4);
            tracep->chgCData(oldp+22,((0xfU & (vlSelf->lab08keyboard__DOT__ps2segin 
                                               >> 4U))),4);
            tracep->chgCData(oldp+23,((0xffU & vlSelf->lab08keyboard__DOT__ps2segin)),8);
            tracep->chgCData(oldp+24,((0xfU & (IData)(vlSelf->lab08keyboard__DOT__ascii))),4);
            tracep->chgCData(oldp+25,((0xfU & ((IData)(vlSelf->lab08keyboard__DOT__ascii) 
                                               >> 4U))),4);
            tracep->chgCData(oldp+26,((0xfU & (vlSelf->lab08keyboard__DOT__ps2segin 
                                               >> 0x10U))),4);
            tracep->chgCData(oldp+27,((0xfU & (vlSelf->lab08keyboard__DOT__ps2segin 
                                               >> 0x14U))),4);
        }
        tracep->chgBit(oldp+28,(vlSelf->clk));
        tracep->chgBit(oldp+29,(vlSelf->rst));
        tracep->chgBit(oldp+30,(vlSelf->ps2_clk));
        tracep->chgBit(oldp+31,(vlSelf->ps2_data));
        tracep->chgCData(oldp+32,(vlSelf->seg1),8);
        tracep->chgCData(oldp+33,(vlSelf->seg2),8);
        tracep->chgCData(oldp+34,(vlSelf->seg3),8);
        tracep->chgCData(oldp+35,(vlSelf->seg4),8);
        tracep->chgCData(oldp+36,(vlSelf->seg5),8);
        tracep->chgCData(oldp+37,(vlSelf->seg6),8);
        tracep->chgCData(oldp+38,(vlSelf->seg7),8);
        tracep->chgCData(oldp+39,(vlSelf->seg8),8);
        tracep->chgCData(oldp+40,(vlSelf->lab08keyboard__DOT__state_current),4);
        tracep->chgCData(oldp+41,(vlSelf->lab08keyboard__DOT__state_next),4);
        tracep->chgCData(oldp+42,(vlSelf->lab08keyboard__DOT__segcountl),4);
        tracep->chgCData(oldp+43,(vlSelf->lab08keyboard__DOT__segcounth),4);
        tracep->chgBit(oldp+44,((1U & (~ (IData)(vlSelf->rst)))));
    }
}

void Vlab08keyboard___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    Vlab08keyboard___024root* const __restrict vlSelf = static_cast<Vlab08keyboard___024root*>(voidSelf);
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
        vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    }
}
