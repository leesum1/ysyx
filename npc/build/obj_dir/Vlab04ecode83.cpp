// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vlab04ecode83.h"
#include "Vlab04ecode83__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vlab04ecode83::Vlab04ecode83(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vlab04ecode83__Syms(_vcontextp__, _vcname__, this)}
    , in{vlSymsp->TOP.in}
    , inflag{vlSymsp->TOP.inflag}
    , out{vlSymsp->TOP.out}
    , seg{vlSymsp->TOP.seg}
    , rootp{&(vlSymsp->TOP)}
{
}

Vlab04ecode83::Vlab04ecode83(const char* _vcname__)
    : Vlab04ecode83(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vlab04ecode83::~Vlab04ecode83() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vlab04ecode83___024root___eval_initial(Vlab04ecode83___024root* vlSelf);
void Vlab04ecode83___024root___eval_settle(Vlab04ecode83___024root* vlSelf);
void Vlab04ecode83___024root___eval(Vlab04ecode83___024root* vlSelf);
QData Vlab04ecode83___024root___change_request(Vlab04ecode83___024root* vlSelf);
#ifdef VL_DEBUG
void Vlab04ecode83___024root___eval_debug_assertions(Vlab04ecode83___024root* vlSelf);
#endif  // VL_DEBUG
void Vlab04ecode83___024root___final(Vlab04ecode83___024root* vlSelf);

static void _eval_initial_loop(Vlab04ecode83__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vlab04ecode83___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vlab04ecode83___024root___eval_settle(&(vlSymsp->TOP));
        Vlab04ecode83___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab04ecode83___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab04ecode83.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab04ecode83___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vlab04ecode83::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vlab04ecode83::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vlab04ecode83___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vlab04ecode83___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab04ecode83___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab04ecode83.v", 1, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab04ecode83___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vlab04ecode83::final() {
    Vlab04ecode83___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vlab04ecode83::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vlab04ecode83::name() const {
    return vlSymsp->name();
}

//============================================================
// Trace configuration

void Vlab04ecode83___024root__traceInitTop(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep);

static void traceInit(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vlab04ecode83___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vlab04ecode83___024root*>(voidSelf);
    Vlab04ecode83__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vlab04ecode83___024root__traceInitTop(vlSelf, tracep);
    tracep->scopeEscape('.');
}

void Vlab04ecode83___024root__traceRegister(Vlab04ecode83___024root* vlSelf, VerilatedVcd* tracep);

void Vlab04ecode83::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, &(vlSymsp->TOP));
    Vlab04ecode83___024root__traceRegister(&(vlSymsp->TOP), tfp->spTrace());
}
