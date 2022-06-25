// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab05alu4.h for the primary calling header

#include "Vlab05alu4___024root.h"
#include "Vlab05alu4__Syms.h"

//==========


void Vlab05alu4___024root___ctor_var_reset(Vlab05alu4___024root* vlSelf);

Vlab05alu4___024root::Vlab05alu4___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vlab05alu4___024root___ctor_var_reset(this);
}

void Vlab05alu4___024root::__Vconfigure(Vlab05alu4__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vlab05alu4___024root::~Vlab05alu4___024root() {
}

void Vlab05alu4___024root___eval_initial(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___eval_initial\n"); );
}

void Vlab05alu4___024root___combo__TOP__1(Vlab05alu4___024root* vlSelf);

void Vlab05alu4___024root___eval_settle(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___eval_settle\n"); );
    // Body
    Vlab05alu4___024root___combo__TOP__1(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

void Vlab05alu4___024root___final(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___final\n"); );
}

void Vlab05alu4___024root___ctor_var_reset(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->a = 0;
    vlSelf->b = 0;
    vlSelf->out = 0;
    vlSelf->CF = 0;
    vlSelf->PF = 0;
    vlSelf->AF = 0;
    vlSelf->ZF = 0;
    vlSelf->SF = 0;
    vlSelf->OF = 0;
    vlSelf->sel = 0;
    vlSelf->segout = 0;
    vlSelf->lab05alu4__DOT__alu__DOT__d38out = 0;
    vlSelf->lab05alu4__DOT__alu__DOT__subb = 0;
    vlSelf->lab05alu4__DOT__alu__DOT__outps = 0;
    vlSelf->lab05alu4__DOT__alu__DOT__subflag = 0;
    vlSelf->lab05alu4__DOT__alu__DOT__psflag = 0;
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
