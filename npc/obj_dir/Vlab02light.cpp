// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vlab02light.h"
#include "Vlab02light__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vlab02light::Vlab02light(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vlab02light__Syms(_vcontextp__, _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , led{vlSymsp->TOP.led}
    , rootp{&(vlSymsp->TOP)}
{
}

Vlab02light::Vlab02light(const char* _vcname__)
    : Vlab02light(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vlab02light::~Vlab02light() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vlab02light___024root___eval_initial(Vlab02light___024root* vlSelf);
void Vlab02light___024root___eval_settle(Vlab02light___024root* vlSelf);
void Vlab02light___024root___eval(Vlab02light___024root* vlSelf);
QData Vlab02light___024root___change_request(Vlab02light___024root* vlSelf);
#ifdef VL_DEBUG
void Vlab02light___024root___eval_debug_assertions(Vlab02light___024root* vlSelf);
#endif  // VL_DEBUG
void Vlab02light___024root___final(Vlab02light___024root* vlSelf);

static void _eval_initial_loop(Vlab02light__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vlab02light___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vlab02light___024root___eval_settle(&(vlSymsp->TOP));
        Vlab02light___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab02light___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("vsrc/lab02light.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab02light___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vlab02light::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vlab02light::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vlab02light___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vlab02light___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab02light___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("vsrc/lab02light.v", 1, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab02light___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vlab02light::final() {
    Vlab02light___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vlab02light::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vlab02light::name() const {
    return vlSymsp->name();
}

//============================================================
// Trace configuration

void Vlab02light___024root__traceInitTop(Vlab02light___024root* vlSelf, VerilatedVcd* tracep);

static void traceInit(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vlab02light___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vlab02light___024root*>(voidSelf);
    Vlab02light__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vlab02light___024root__traceInitTop(vlSelf, tracep);
    tracep->scopeEscape('.');
}

void Vlab02light___024root__traceRegister(Vlab02light___024root* vlSelf, VerilatedVcd* tracep);

void Vlab02light::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, &(vlSymsp->TOP));
    Vlab02light___024root__traceRegister(&(vlSymsp->TOP), tfp->spTrace());
}
