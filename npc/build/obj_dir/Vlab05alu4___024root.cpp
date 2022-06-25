// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vlab05alu4.h for the primary calling header

#include "Vlab05alu4___024root.h"
#include "Vlab05alu4__Syms.h"

//==========

extern const VlUnpacked<CData/*7:0*/, 8> Vlab05alu4__ConstPool__TABLE_af10cd70_0;
extern const VlUnpacked<CData/*7:0*/, 8> Vlab05alu4__ConstPool__TABLE_c5bd01dd_0;

VL_INLINE_OPT void Vlab05alu4___024root___combo__TOP__1(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___combo__TOP__1\n"); );
    // Variables
    CData/*2:0*/ __Vtableidx1;
    CData/*2:0*/ __Vtableidx2;
    // Body
    __Vtableidx1 = vlSelf->sel;
    vlSelf->lab05alu4__DOT__alu__DOT__d38out = Vlab05alu4__ConstPool__TABLE_af10cd70_0
        [__Vtableidx1];
    vlSelf->lab05alu4__DOT__alu__DOT__subflag = 0U;
    if (((((((((1U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out)) 
               | (2U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
              | (4U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
             | (8U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
            | (0x10U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
           | (0x20U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
          | (0x40U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
         | (0x80U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out)))) {
        if ((1U != (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) {
            if ((2U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) {
                vlSelf->lab05alu4__DOT__alu__DOT__subflag = 1U;
            } else if ((4U != (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) {
                if ((8U != (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) {
                    if ((0x10U != (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) {
                        if ((0x20U != (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) {
                            vlSelf->lab05alu4__DOT__alu__DOT__subflag = 1U;
                        }
                    }
                }
            }
        }
    }
    vlSelf->lab05alu4__DOT__alu__DOT__subb = (0x1fU 
                                              & ((IData)(vlSelf->lab05alu4__DOT__alu__DOT__subflag)
                                                  ? 
                                                 ((IData)(1U) 
                                                  + 
                                                  ((0x10U 
                                                    & ((~ 
                                                        ((IData)(vlSelf->b) 
                                                         >> 3U)) 
                                                       << 4U)) 
                                                   | (0xfU 
                                                      & (~ (IData)(vlSelf->b)))))
                                                  : 
                                                 ((0x10U 
                                                   & ((IData)(vlSelf->b) 
                                                      << 1U)) 
                                                  | (IData)(vlSelf->b))));
    vlSelf->lab05alu4__DOT__alu__DOT__psflag = (1U 
                                                & ((((0x10U 
                                                      & ((IData)(vlSelf->a) 
                                                         << 1U)) 
                                                     | (IData)(vlSelf->a)) 
                                                    + (IData)(vlSelf->lab05alu4__DOT__alu__DOT__subb)) 
                                                   >> 4U));
    vlSelf->lab05alu4__DOT__alu__DOT__outps = (0xfU 
                                               & ((IData)(vlSelf->a) 
                                                  + (IData)(vlSelf->lab05alu4__DOT__alu__DOT__subb)));
    vlSelf->CF = vlSelf->lab05alu4__DOT__alu__DOT__psflag;
    vlSelf->ZF = (0U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__outps));
    vlSelf->SF = (1U & ((IData)(vlSelf->lab05alu4__DOT__alu__DOT__outps) 
                        >> 3U));
    vlSelf->OF = (1U & ((IData)(vlSelf->lab05alu4__DOT__alu__DOT__psflag) 
                        ^ ((IData)(vlSelf->lab05alu4__DOT__alu__DOT__outps) 
                           >> 3U)));
    vlSelf->out = (((((((((1U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out)) 
                          | (2U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
                         | (4U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
                        | (8U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
                       | (0x10U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
                      | (0x20U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
                     | (0x40U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))) 
                    | (0x80U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out)))
                    ? (0xfU & ((1U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))
                                ? (IData)(vlSelf->lab05alu4__DOT__alu__DOT__outps)
                                : ((2U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))
                                    ? (IData)(vlSelf->lab05alu4__DOT__alu__DOT__outps)
                                    : ((4U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))
                                        ? (~ (IData)(vlSelf->a))
                                        : ((8U == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))
                                            ? ((IData)(vlSelf->a) 
                                               & (IData)(vlSelf->b))
                                            : ((0x10U 
                                                == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))
                                                ? ((IData)(vlSelf->a) 
                                                   | (IData)(vlSelf->b))
                                                : (
                                                   (0x20U 
                                                    == (IData)(vlSelf->lab05alu4__DOT__alu__DOT__d38out))
                                                    ? 
                                                   ((IData)(vlSelf->a) 
                                                    ^ (IData)(vlSelf->b))
                                                    : (IData)(vlSelf->lab05alu4__DOT__alu__DOT__outps))))))))
                    : 0U);
    __Vtableidx2 = (7U & (IData)(vlSelf->out));
    vlSelf->segout = Vlab05alu4__ConstPool__TABLE_c5bd01dd_0
        [__Vtableidx2];
}

void Vlab05alu4___024root___eval(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___eval\n"); );
    // Body
    Vlab05alu4___024root___combo__TOP__1(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
}

QData Vlab05alu4___024root___change_request_1(Vlab05alu4___024root* vlSelf);

VL_INLINE_OPT QData Vlab05alu4___024root___change_request(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___change_request\n"); );
    // Body
    return (Vlab05alu4___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vlab05alu4___024root___change_request_1(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vlab05alu4___024root___eval_debug_assertions(Vlab05alu4___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vlab05alu4__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vlab05alu4___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xf0U))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xf0U))) {
        Verilated::overWidthError("b");}
    if (VL_UNLIKELY((vlSelf->sel & 0xf8U))) {
        Verilated::overWidthError("sel");}
}
#endif  // VL_DEBUG
