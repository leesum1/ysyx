// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vlab08keyboard.h"
#include "Vlab08keyboard__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vlab08keyboard::Vlab08keyboard(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vlab08keyboard__Syms(_vcontextp__, _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , ps2_clk{vlSymsp->TOP.ps2_clk}
    , ps2_data{vlSymsp->TOP.ps2_data}
    , seg1{vlSymsp->TOP.seg1}
    , seg2{vlSymsp->TOP.seg2}
    , seg3{vlSymsp->TOP.seg3}
    , seg4{vlSymsp->TOP.seg4}
    , seg5{vlSymsp->TOP.seg5}
    , seg6{vlSymsp->TOP.seg6}
    , seg7{vlSymsp->TOP.seg7}
    , seg8{vlSymsp->TOP.seg8}
    , rootp{&(vlSymsp->TOP)}
{
}

Vlab08keyboard::Vlab08keyboard(const char* _vcname__)
    : Vlab08keyboard(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vlab08keyboard::~Vlab08keyboard() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vlab08keyboard___024root___eval_initial(Vlab08keyboard___024root* vlSelf);
void Vlab08keyboard___024root___eval_settle(Vlab08keyboard___024root* vlSelf);
void Vlab08keyboard___024root___eval(Vlab08keyboard___024root* vlSelf);
QData Vlab08keyboard___024root___change_request(Vlab08keyboard___024root* vlSelf);
#ifdef VL_DEBUG
void Vlab08keyboard___024root___eval_debug_assertions(Vlab08keyboard___024root* vlSelf);
#endif  // VL_DEBUG
void Vlab08keyboard___024root___final(Vlab08keyboard___024root* vlSelf);

static void _eval_initial_loop(Vlab08keyboard__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vlab08keyboard___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vlab08keyboard___024root___eval_settle(&(vlSymsp->TOP));
        Vlab08keyboard___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab08keyboard___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab08keyboard.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab08keyboard___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vlab08keyboard::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vlab08keyboard::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vlab08keyboard___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vlab08keyboard___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vlab08keyboard___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/leesum/ysyx-workbench/npc/vsrc/lab08keyboard.v", 1, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vlab08keyboard___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vlab08keyboard::final() {
    Vlab08keyboard___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vlab08keyboard::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vlab08keyboard::name() const {
    return vlSymsp->name();
}

//============================================================
// Trace configuration

void Vlab08keyboard___024root__traceInitTop(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep);

static void traceInit(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vlab08keyboard___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vlab08keyboard___024root*>(voidSelf);
    Vlab08keyboard__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vlab08keyboard___024root__traceInitTop(vlSelf, tracep);
    tracep->scopeEscape('.');
}

void Vlab08keyboard___024root__traceRegister(Vlab08keyboard___024root* vlSelf, VerilatedVcd* tracep);

void Vlab08keyboard::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, &(vlSymsp->TOP));
    Vlab08keyboard___024root__traceRegister(&(vlSymsp->TOP), tfp->spTrace());
}
