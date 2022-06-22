// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vlab01switch.h"
#include "Vlab01switch__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vlab01switch::Vlab01switch(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vlab01switch__Syms(_vcontextp__, _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , f{vlSymsp->TOP.f}
    , rootp{&(vlSymsp->TOP)}
{
}

Vlab01switch::Vlab01switch(const char* _vcname__)
    : Vlab01switch(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vlab01switch::~Vlab01switch() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vlab01switch___024root___eval_initial(Vlab01switch___024root* vlSelf);
void Vlab01switch___024root___eval_settle(Vlab01switch___024root* vlSelf);
void Vlab01switch___024root___eval(Vlab01switch___024root* vlSelf);
QData Vlab01switch___024root___change_request(Vlab01switch___024root* vlSelf);
#ifdef VL_DEBUG
void Vlab01switch___024root___eval_debug_assertions(Vlab01switch___024root* vlSelf);
#endif  // VL_DEBUG
void Vlab01switch___024root___final(Vlab01switch___024root* vlSelf);

static void _eval_initial_loop(Vlab01switch__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vlab01switch___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vlab01switch___024root___eval_settle(&(vlSymsp->TOP));
        Vlab01switch___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab01switch___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab01switch.v", 2, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab01switch___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vlab01switch::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vlab01switch::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vlab01switch___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vlab01switch___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab01switch___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab01switch.v", 2, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab01switch___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vlab01switch::final() {
    Vlab01switch___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vlab01switch::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vlab01switch::name() const {
    return vlSymsp->name();
}

//============================================================
// Trace configuration

void Vlab01switch___024root__traceInitTop(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep);

static void traceInit(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vlab01switch___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vlab01switch___024root*>(voidSelf);
    Vlab01switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vlab01switch___024root__traceInitTop(vlSelf, tracep);
    tracep->scopeEscape('.');
}

void Vlab01switch___024root__traceRegister(Vlab01switch___024root* vlSelf, VerilatedVcd* tracep);

void Vlab01switch::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, &(vlSymsp->TOP));
    Vlab01switch___024root__traceRegister(&(vlSymsp->TOP), tfp->spTrace());
}
