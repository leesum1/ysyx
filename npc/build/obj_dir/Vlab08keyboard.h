// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VLAB08KEYBOARD_H_
#define VERILATED_VLAB08KEYBOARD_H_  // guard

#include "verilated_heavy.h"

class Vlab08keyboard__Syms;
class Vlab08keyboard___024root;
class VerilatedVcdC;
class Vlab08keyboard_VerilatedVcd;


// This class is the main interface to the Verilated model
class Vlab08keyboard VL_NOT_FINAL {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vlab08keyboard__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clk,0,0);
    VL_IN8(&rst,0,0);
    VL_IN8(&ps2_clk,0,0);
    VL_IN8(&ps2_data,0,0);
    VL_OUT8(&seg1,7,0);
    VL_OUT8(&seg2,7,0);
    VL_OUT8(&seg3,7,0);
    VL_OUT8(&seg4,7,0);
    VL_OUT8(&seg5,7,0);
    VL_OUT8(&seg6,7,0);
    VL_OUT8(&seg7,7,0);
    VL_OUT8(&seg8,7,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vlab08keyboard___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vlab08keyboard(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vlab08keyboard(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vlab08keyboard();
  private:
    VL_UNCOPYABLE(Vlab08keyboard);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    /// Return current simulation context for this model.
    /// Used to get to e.g. simulation time via contextp()->time()
    VerilatedContext* contextp() const;
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
