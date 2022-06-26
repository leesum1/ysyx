// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VLAB07RAND8__SYMS_H_
#define VERILATED_VLAB07RAND8__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODEL CLASS

#include "Vlab07rand8.h"

// INCLUDE MODULE CLASSES
#include "Vlab07rand8___024root.h"

// SYMS CLASS (contains all model state)
class Vlab07rand8__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vlab07rand8* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vlab07rand8___024root          TOP;

    // CONSTRUCTORS
    Vlab07rand8__Syms(VerilatedContext* contextp, const char* namep, Vlab07rand8* modelp);
    ~Vlab07rand8__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
