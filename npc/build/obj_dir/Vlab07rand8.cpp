// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vlab07rand8.h"
#include "Vlab07rand8__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vlab07rand8::Vlab07rand8(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vlab07rand8__Syms(_vcontextp__, _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , out{vlSymsp->TOP.out}
    , seg1{vlSymsp->TOP.seg1}
    , seg2{vlSymsp->TOP.seg2}
    , rootp{&(vlSymsp->TOP)}
{
}

Vlab07rand8::Vlab07rand8(const char* _vcname__)
    : Vlab07rand8(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vlab07rand8::~Vlab07rand8() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vlab07rand8___024root___eval_initial(Vlab07rand8___024root* vlSelf);
void Vlab07rand8___024root___eval_settle(Vlab07rand8___024root* vlSelf);
void Vlab07rand8___024root___eval(Vlab07rand8___024root* vlSelf);
QData Vlab07rand8___024root___change_request(Vlab07rand8___024root* vlSelf);
#ifdef VL_DEBUG
void Vlab07rand8___024root___eval_debug_assertions(Vlab07rand8___024root* vlSelf);
#endif  // VL_DEBUG
void Vlab07rand8___024root___final(Vlab07rand8___024root* vlSelf);

static void _eval_initial_loop(Vlab07rand8__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vlab07rand8___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vlab07rand8___024root___eval_settle(&(vlSymsp->TOP));
        Vlab07rand8___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab07rand8___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab07rand8.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab07rand8___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vlab07rand8::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vlab07rand8::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vlab07rand8___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vlab07rand8___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab07rand8___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab07rand8.v", 1, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab07rand8___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vlab07rand8::final() {
    Vlab07rand8___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vlab07rand8::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vlab07rand8::name() const {
    return vlSymsp->name();
}

//============================================================
// Trace configuration

void Vlab07rand8___024root__traceInitTop(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep);

static void traceInit(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vlab07rand8___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vlab07rand8___024root*>(voidSelf);
    Vlab07rand8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vlab07rand8___024root__traceInitTop(vlSelf, tracep);
    tracep->scopeEscape('.');
}

void Vlab07rand8___024root__traceRegister(Vlab07rand8___024root* vlSelf, VerilatedVcd* tracep);

void Vlab07rand8::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, &(vlSymsp->TOP));
    Vlab07rand8___024root__traceRegister(&(vlSymsp->TOP), tfp->spTrace());
}
