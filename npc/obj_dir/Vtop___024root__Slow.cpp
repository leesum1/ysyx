// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop___024root.h"
#include "Vtop__Syms.h"

#include "verilated_dpi.h"

//==========


void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf);

Vtop___024root::Vtop___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vtop___024root___ctor_var_reset(this);
}

void Vtop___024root::__Vconfigure(Vtop__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vtop___024root::~Vtop___024root() {
}

void Vtop___024root____Vdpiimwrap_top__DOT__u_rv64reg__DOT__set_gpr_ptr__Vdpioc2_TOP(const VlUnpacked<QData/*63:0*/, 32> &a);

void Vtop___024root___initial__TOP__2(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___initial__TOP__2\n"); );
    // Body
    Vtop___024root____Vdpiimwrap_top__DOT__u_rv64reg__DOT__set_gpr_ptr__Vdpioc2_TOP(vlSelf->top__DOT__u_rv64reg__DOT__rf);
}

void Vtop___024root____Vdpiimwrap_top__DOT__u_fetch__DOT__pmem_read_TOP(QData/*63:0*/ raddr, QData/*63:0*/ &rdata);
void Vtop___024root____Vdpiimwrap_top__DOT__u_fetch__DOT__get_pc_TOP(QData/*63:0*/ pc);

void Vtop___024root___settle__TOP__3(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___settle__TOP__3\n"); );
    // Variables
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_load;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_jalr;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_jal;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_op_imm;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_op;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_system;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_auipc;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_lui;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_op_imm_32;
    CData/*0:0*/ top__DOT__u_dcode__DOT___type_op_32;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_jalr;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_ecall;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_ebreak;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_csrrw;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_csrrs;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_csrrc;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_csrrwi;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_csrrsi;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_csrrci;
    CData/*0:0*/ top__DOT__u_dcode__DOT___inst_mret;
    CData/*0:0*/ top__DOT__u_dcode__DOT___U_type;
    CData/*0:0*/ top__DOT__u_dcode__DOT___isNeed_csr;
    CData/*0:0*/ top__DOT__u_dcode__DOT___csr_set;
    CData/*0:0*/ top__DOT__u_dcode__DOT___csr_clear;
    CData/*0:0*/ top__DOT__u_execute__DOT___rs1_rs2;
    CData/*0:0*/ top__DOT__u_execute__DOT___rs1_imm;
    CData/*0:0*/ top__DOT__u_execute__DOT___pc_4;
    CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isCMP;
    CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isSUBop;
    VlWide<3>/*64:0*/ top__DOT__u_execute__DOT__u_alu__DOT___alu_a;
    VlWide<3>/*64:0*/ top__DOT__u_execute__DOT__u_alu__DOT___alu_b;
    VlWide<3>/*95:0*/ __Vtemp24;
    VlWide<4>/*127:0*/ __Vtemp25;
    VlWide<3>/*95:0*/ __Vtemp26;
    VlWide<4>/*127:0*/ __Vtemp27;
    VlWide<4>/*127:0*/ __Vtemp28;
    VlWide<3>/*95:0*/ __Vtemp31;
    VlWide<3>/*95:0*/ __Vtemp32;
    VlWide<3>/*95:0*/ __Vtemp33;
    QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT___alu_out;
    QData/*63:0*/ top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_op2;
    // Body
    Vtop___024root____Vdpiimwrap_top__DOT__u_fetch__DOT__pmem_read_TOP(vlSelf->top__DOT__u_pc__DOT___pc_current, vlSelf->__Vtask_top__DOT__u_fetch__DOT__pmem_read__0__rdata);
    vlSelf->top__DOT__u_fetch__DOT___mem_data = vlSelf->__Vtask_top__DOT__u_fetch__DOT__pmem_read__0__rdata;
    Vtop___024root____Vdpiimwrap_top__DOT__u_fetch__DOT__get_pc_TOP(vlSelf->top__DOT__u_pc__DOT___pc_current);
    top__DOT__u_dcode__DOT___type_jal = (IData)((0x6fULL 
                                                 == 
                                                 (0x7fULL 
                                                  & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_auipc = (IData)((0x17ULL 
                                                   == 
                                                   (0x7fULL 
                                                    & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_lui = (IData)((0x37ULL 
                                                 == 
                                                 (0x7fULL 
                                                  & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    vlSelf->top__DOT__u_dcode__DOT___type_store = (IData)(
                                                          (0x23ULL 
                                                           == 
                                                           (0x7fULL 
                                                            & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    vlSelf->top__DOT__u_dcode__DOT___type_branch = (IData)(
                                                           (0x63ULL 
                                                            == 
                                                            (0x7fULL 
                                                             & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_op = (IData)((0x33ULL 
                                                == 
                                                (0x7fULL 
                                                 & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_op_32 = (IData)((0x3bULL 
                                                   == 
                                                   (0x7fULL 
                                                    & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_op_imm = (IData)(
                                                   (0x13ULL 
                                                    == 
                                                    (0x7fULL 
                                                     & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_op_imm_32 = (IData)(
                                                      (0x1bULL 
                                                       == 
                                                       (0x7fULL 
                                                        & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_load = (IData)((3ULL 
                                                  == 
                                                  (0x7fULL 
                                                   & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_jalr = (IData)((0x67ULL 
                                                  == 
                                                  (0x7fULL 
                                                   & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___type_system = (IData)(
                                                   (0x73ULL 
                                                    == 
                                                    (0x7fULL 
                                                     & vlSelf->top__DOT__u_fetch__DOT___mem_data)));
    top__DOT__u_dcode__DOT___U_type = ((IData)(top__DOT__u_dcode__DOT___type_auipc) 
                                       | (IData)(top__DOT__u_dcode__DOT___type_lui));
    vlSelf->top__DOT__u_dcode__DOT___R_type = ((IData)(top__DOT__u_dcode__DOT___type_op) 
                                               | (IData)(top__DOT__u_dcode__DOT___type_op_32));
    vlSelf->top__DOT__u_dcode__DOT___mem_op = (((((
                                                   ((((((1U 
                                                         & (- (IData)(
                                                                      ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                       & (0U 
                                                                          == 
                                                                          (7U 
                                                                           & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))))) 
                                                        | (4U 
                                                           & (- (IData)(
                                                                        ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                         & (4U 
                                                                            == 
                                                                            (7U 
                                                                             & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                       | (2U 
                                                          & (- (IData)(
                                                                       ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                        & (1U 
                                                                           == 
                                                                           (7U 
                                                                            & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                      | (3U 
                                                         & (- (IData)(
                                                                      ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                       & (2U 
                                                                          == 
                                                                          (7U 
                                                                           & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                     | (5U 
                                                        & (- (IData)(
                                                                     ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                      & (5U 
                                                                         == 
                                                                         (7U 
                                                                          & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                    | (8U 
                                                       & (- (IData)(
                                                                    ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_store) 
                                                                     & (0U 
                                                                        == 
                                                                        (7U 
                                                                         & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                   | (9U 
                                                      & (- (IData)(
                                                                   ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_store) 
                                                                    & (1U 
                                                                       == 
                                                                       (7U 
                                                                        & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                  | (0xaU 
                                                     & (- (IData)(
                                                                  ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_store) 
                                                                   & (2U 
                                                                      == 
                                                                      (7U 
                                                                       & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                 | (7U 
                                                    & (- (IData)(
                                                                 ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                  & (6U 
                                                                     == 
                                                                     (7U 
                                                                      & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                | (6U 
                                                   & (- (IData)(
                                                                ((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                                 & (3U 
                                                                    == 
                                                                    (7U 
                                                                     & (IData)(
                                                                               (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                               | (0xbU 
                                                  & (- (IData)(
                                                               ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_store) 
                                                                & (3U 
                                                                   == 
                                                                   (7U 
                                                                    & (IData)(
                                                                              (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                               >> 0xcU)))))))));
    top__DOT__u_dcode__DOT___inst_jalr = ((IData)(top__DOT__u_dcode__DOT___type_jalr) 
                                          & (0U == 
                                             (7U & (IData)(
                                                           (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                            >> 0xcU)))));
    top__DOT__u_dcode__DOT___inst_ecall = (IData)((
                                                   (1U 
                                                    == 
                                                    (1U 
                                                     & (IData)(top__DOT__u_dcode__DOT___type_system))) 
                                                   & (0ULL 
                                                      == 
                                                      (0xfff07000ULL 
                                                       & vlSelf->top__DOT__u_fetch__DOT___mem_data))));
    top__DOT__u_dcode__DOT___inst_mret = (IData)(((1U 
                                                   == 
                                                   (1U 
                                                    & (IData)(top__DOT__u_dcode__DOT___type_system))) 
                                                  & (0x30200000ULL 
                                                     == 
                                                     (0xfff07000ULL 
                                                      & vlSelf->top__DOT__u_fetch__DOT___mem_data))));
    vlSelf->top__DOT__u_dcode__DOT___I_type = (((((IData)(top__DOT__u_dcode__DOT___type_load) 
                                                  | (IData)(top__DOT__u_dcode__DOT___type_op_imm)) 
                                                 | (IData)(top__DOT__u_dcode__DOT___type_op_imm_32)) 
                                                | (IData)(top__DOT__u_dcode__DOT___type_jalr)) 
                                               | (IData)(top__DOT__u_dcode__DOT___type_system));
    top__DOT__u_dcode__DOT___inst_ebreak = (IData)(
                                                   ((1U 
                                                     == 
                                                     (1U 
                                                      & (IData)(top__DOT__u_dcode__DOT___type_system))) 
                                                    & (0x100000ULL 
                                                       == 
                                                       (0xfff07000ULL 
                                                        & vlSelf->top__DOT__u_fetch__DOT___mem_data))));
    top__DOT__u_dcode__DOT___inst_csrrw = ((IData)(top__DOT__u_dcode__DOT___type_system) 
                                           & (1U == 
                                              (7U & (IData)(
                                                            (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                             >> 0xcU)))));
    top__DOT__u_dcode__DOT___inst_csrrs = ((IData)(top__DOT__u_dcode__DOT___type_system) 
                                           & (2U == 
                                              (7U & (IData)(
                                                            (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                             >> 0xcU)))));
    top__DOT__u_dcode__DOT___inst_csrrc = ((IData)(top__DOT__u_dcode__DOT___type_system) 
                                           & (3U == 
                                              (7U & (IData)(
                                                            (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                             >> 0xcU)))));
    top__DOT__u_dcode__DOT___inst_csrrwi = ((IData)(top__DOT__u_dcode__DOT___type_system) 
                                            & (5U == 
                                               (7U 
                                                & (IData)(
                                                          (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                           >> 0xcU)))));
    top__DOT__u_dcode__DOT___inst_csrrsi = ((IData)(top__DOT__u_dcode__DOT___type_system) 
                                            & (6U == 
                                               (7U 
                                                & (IData)(
                                                          (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                           >> 0xcU)))));
    top__DOT__u_dcode__DOT___inst_csrrci = ((IData)(top__DOT__u_dcode__DOT___type_system) 
                                            & (7U == 
                                               (7U 
                                                & (IData)(
                                                          (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                           >> 0xcU)))));
    vlSelf->top__DOT__rs2_data = vlSelf->top__DOT__u_rv64reg__DOT__rf
        [((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
            | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
           | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))
           ? (0x1fU & (IData)((vlSelf->top__DOT__u_fetch__DOT___mem_data 
                               >> 0x14U))) : 0U)];
    vlSelf->top__DOT__u_memory__DOT___ls8byte = (((1U 
                                                   == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)) 
                                                  | (4U 
                                                     == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))) 
                                                 | (8U 
                                                    == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)));
    vlSelf->top__DOT__u_memory__DOT___ls16byte = ((
                                                   (2U 
                                                    == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)) 
                                                   | (5U 
                                                      == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))) 
                                                  | (9U 
                                                     == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)));
    vlSelf->top__DOT__u_memory__DOT___ls32byte = ((
                                                   (3U 
                                                    == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)) 
                                                   | (0xaU 
                                                      == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))) 
                                                  | (7U 
                                                     == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)));
    vlSelf->top__DOT__u_memory__DOT___unsigned = ((
                                                   (5U 
                                                    == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)) 
                                                   | (4U 
                                                      == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))) 
                                                  | (7U 
                                                     == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)));
    vlSelf->top__DOT__u_memory__DOT___signed = ((((2U 
                                                   == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)) 
                                                  | (1U 
                                                     == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))) 
                                                 | (3U 
                                                    == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))) 
                                                | (6U 
                                                   == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op)));
    vlSelf->top__DOT__u_dcode__DOT___pc_op = ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch)
                                               ? 1U
                                               : ((IData)(top__DOT__u_dcode__DOT___type_jal)
                                                   ? 2U
                                                   : 
                                                  ((IData)(top__DOT__u_dcode__DOT___inst_jalr)
                                                    ? 3U
                                                    : 
                                                   (((IData)(top__DOT__u_dcode__DOT___inst_mret) 
                                                     | (IData)(top__DOT__u_dcode__DOT___inst_ecall))
                                                     ? 5U
                                                     : 4U))));
    vlSelf->top__DOT__u_dcode__DOT___rd_idx = (((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                                  | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
                                                 | (IData)(top__DOT__u_dcode__DOT___U_type)) 
                                                | (IData)(top__DOT__u_dcode__DOT___type_jal))
                                                ? (0x1fU 
                                                   & (IData)(
                                                             (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                              >> 7U)))
                                                : 0U);
    vlSelf->top__DOT__u_dcode__DOT___imm_data = (((
                                                   (((- (QData)((IData)(vlSelf->top__DOT__u_dcode__DOT___I_type))) 
                                                     & (((- (QData)((IData)(
                                                                            (1U 
                                                                             & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x1fU)))))) 
                                                         << 0xbU) 
                                                        | (QData)((IData)(
                                                                          (0x7ffU 
                                                                           & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x14U))))))) 
                                                    | ((- (QData)((IData)(vlSelf->top__DOT__u_dcode__DOT___type_store))) 
                                                       & (((- (QData)((IData)(
                                                                              (1U 
                                                                               & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x1fU)))))) 
                                                           << 0xbU) 
                                                          | (QData)((IData)(
                                                                            ((0x7e0U 
                                                                              & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x19U)) 
                                                                                << 5U)) 
                                                                             | (0x1fU 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 7U))))))))) 
                                                   | ((- (QData)((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))) 
                                                      & (((- (QData)((IData)(
                                                                             (1U 
                                                                              & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x1fU)))))) 
                                                          << 0xcU) 
                                                         | (QData)((IData)(
                                                                           ((0x800U 
                                                                             & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 7U)) 
                                                                                << 0xbU)) 
                                                                            | ((0x7e0U 
                                                                                & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x19U)) 
                                                                                << 5U)) 
                                                                               | (0x1eU 
                                                                                & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 8U)) 
                                                                                << 1U))))))))) 
                                                  | ((- (QData)((IData)(top__DOT__u_dcode__DOT___U_type))) 
                                                     & (((- (QData)((IData)(
                                                                            (1U 
                                                                             & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x1fU)))))) 
                                                         << 0x1fU) 
                                                        | (QData)((IData)(
                                                                          ((0x7ff00000U 
                                                                            & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x14U)) 
                                                                               << 0x14U)) 
                                                                           | (0xff000U 
                                                                              & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)) 
                                                                                << 0xcU)))))))) 
                                                 | ((- (QData)((IData)(top__DOT__u_dcode__DOT___type_jal))) 
                                                    & (((- (QData)((IData)(
                                                                           (1U 
                                                                            & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x1fU)))))) 
                                                        << 0x14U) 
                                                       | (QData)((IData)(
                                                                         ((0xff000U 
                                                                           & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)) 
                                                                              << 0xcU)) 
                                                                          | ((0x800U 
                                                                              & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x14U)) 
                                                                                << 0xbU)) 
                                                                             | ((0x7e0U 
                                                                                & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x19U)) 
                                                                                << 5U)) 
                                                                                | (0x1eU 
                                                                                & ((IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0x15U)) 
                                                                                << 1U))))))))));
    vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus 
        = (((IData)(top__DOT__u_dcode__DOT___inst_mret) 
            << 2U) | (((IData)(top__DOT__u_dcode__DOT___inst_ebreak) 
                       << 1U) | (IData)(top__DOT__u_dcode__DOT___inst_ecall)));
    top__DOT__u_dcode__DOT___csr_set = ((IData)(top__DOT__u_dcode__DOT___inst_csrrs) 
                                        | (IData)(top__DOT__u_dcode__DOT___inst_csrrsi));
    top__DOT__u_dcode__DOT___csr_clear = ((IData)(top__DOT__u_dcode__DOT___inst_csrrc) 
                                          | (IData)(top__DOT__u_dcode__DOT___inst_csrrci));
    vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR 
        = (((IData)(top__DOT__u_dcode__DOT___inst_csrrci) 
            | (IData)(top__DOT__u_dcode__DOT___inst_csrrsi)) 
           | (IData)(top__DOT__u_dcode__DOT___inst_csrrwi));
    top__DOT__u_dcode__DOT___isNeed_csr = ((((((IData)(top__DOT__u_dcode__DOT___inst_csrrc) 
                                               | (IData)(top__DOT__u_dcode__DOT___inst_csrrci)) 
                                              | (IData)(top__DOT__u_dcode__DOT___inst_csrrs)) 
                                             | (IData)(top__DOT__u_dcode__DOT___inst_csrrsi)) 
                                            | (IData)(top__DOT__u_dcode__DOT___inst_csrrw)) 
                                           | (IData)(top__DOT__u_dcode__DOT___inst_csrrwi));
    vlSelf->top__DOT__u_dcode__DOT___csr_op = ((((IData)(top__DOT__u_dcode__DOT___csr_set) 
                                                 | (IData)(top__DOT__u_dcode__DOT___csr_clear)) 
                                                & (0U 
                                                   == 
                                                   (0x1fU 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                               >> 0xfU)))))
                                                ? 1U
                                                : (
                                                   ((2U 
                                                     & (- (IData)(
                                                                  ((IData)(top__DOT__u_dcode__DOT___inst_csrrw) 
                                                                   | (IData)(top__DOT__u_dcode__DOT___inst_csrrwi))))) 
                                                    | (3U 
                                                       & (- (IData)((IData)(top__DOT__u_dcode__DOT___csr_set))))) 
                                                   | (4U 
                                                      & (- (IData)((IData)(top__DOT__u_dcode__DOT___csr_clear))))));
    vlSelf->top__DOT__rs1_data = vlSelf->top__DOT__u_rv64reg__DOT__rf
        [((((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
              | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
             | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
            | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch)) 
           & (~ (IData)(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR)))
           ? (0x1fU & (IData)((vlSelf->top__DOT__u_fetch__DOT___mem_data 
                               >> 0xfU))) : 0U)];
    vlSelf->top__DOT__u_dcode__DOT___csr_idx = ((IData)(top__DOT__u_dcode__DOT___isNeed_csr)
                                                 ? 
                                                (0xfffU 
                                                 & (IData)(
                                                           (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                            >> 0x14U)))
                                                 : 0U);
    vlSelf->top__DOT__u_dcode__DOT___alu_op = (((((
                                                   (((((((((((((((((((((((((((1U 
                                                                              & (- (IData)(
                                                                                (((((((((((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                                & (0ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm) 
                                                                                & (0U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm_32) 
                                                                                & (0U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))) 
                                                                                | (IData)(top__DOT__u_dcode__DOT___type_load)) 
                                                                                | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                                                                | (IData)(top__DOT__u_dcode__DOT___type_jal)) 
                                                                                | (IData)(top__DOT__u_dcode__DOT___inst_jalr)) 
                                                                                | (IData)(top__DOT__u_dcode__DOT___type_auipc)) 
                                                                                | (IData)(top__DOT__u_dcode__DOT___type_lui)) 
                                                                                | (IData)(top__DOT__u_dcode__DOT___isNeed_csr))))) 
                                                                             | (2U 
                                                                                & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x40000000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                                & (0x40000000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                            | (3U 
                                                                               & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x4000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm) 
                                                                                & (4U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))))))) 
                                                                           | (4U 
                                                                              & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x6000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm) 
                                                                                & (6U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))))))) 
                                                                          | (5U 
                                                                             & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x7000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm) 
                                                                                & (7U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))))))) 
                                                                         | (6U 
                                                                            & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x1000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_imm))) 
                                                                                & (0x1000ULL 
                                                                                == 
                                                                                (0xfc007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                        | (7U 
                                                                           & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x5000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_imm))) 
                                                                                & (0x5000ULL 
                                                                                == 
                                                                                (0xfc007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                       | (8U 
                                                                          & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x40005000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_imm))) 
                                                                                & (0x40005000ULL 
                                                                                == 
                                                                                (0xfc007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                      | (9U 
                                                                         & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_imm_32))) 
                                                                                & (0x1000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                                & (0x1000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                     | (0xaU 
                                                                        & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_imm_32))) 
                                                                                & (0x5000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                                & (0x5000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                    | (0xbU 
                                                                       & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_imm_32))) 
                                                                                & (0x40005000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | (IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                                & (0x40005000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))))) 
                                                                   | (0xcU 
                                                                      & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x2000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm) 
                                                                                & (2U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))))))) 
                                                                  | (0xdU 
                                                                     & (- (IData)(
                                                                                ((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x3000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))) 
                                                                                | ((IData)(top__DOT__u_dcode__DOT___type_op_imm) 
                                                                                & (3U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU)))))))))) 
                                                                 | (0xeU 
                                                                    & (- (IData)(
                                                                                ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch) 
                                                                                & (0U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                                | (0xfU 
                                                                   & (- (IData)(
                                                                                ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch) 
                                                                                & (1U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                               | (0x10U 
                                                                  & (- (IData)(
                                                                               ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch) 
                                                                                & (4U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                              | (0x11U 
                                                                 & (- (IData)(
                                                                              ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch) 
                                                                               & (5U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                             | (0x12U 
                                                                & (- (IData)(
                                                                             ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch) 
                                                                              & (6U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                            | (0x13U 
                                                               & (- (IData)(
                                                                            ((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch) 
                                                                             & (7U 
                                                                                == 
                                                                                (7U 
                                                                                & (IData)(
                                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                                >> 0xcU))))))))) 
                                                           | (0x14U 
                                                              & (- (IData)((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x2000000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                          | (0x15U 
                                                             & (- (IData)((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x2001000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                         | (0x16U 
                                                            & (- (IData)((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x2002000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                        | (0x17U 
                                                           & (- (IData)((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                                & (0x2003000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                       | (0x18U 
                                                          & (- (IData)((IData)(
                                                                               ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                                & (0x2000000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                      | (0x19U 
                                                         & (- (IData)((IData)(
                                                                              ((1U 
                                                                                == 
                                                                                (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                               & (0x2004000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                     | (0x1aU 
                                                        & (- (IData)((IData)(
                                                                             ((1U 
                                                                               == 
                                                                               (1U 
                                                                                & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                              & (0x2005000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                    | (0x1bU 
                                                       & (- (IData)((IData)(
                                                                            ((1U 
                                                                              == 
                                                                              (1U 
                                                                               & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                             & (0x2006000ULL 
                                                                                == 
                                                                                (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                   | (0x1cU 
                                                      & (- (IData)((IData)(
                                                                           ((1U 
                                                                             == 
                                                                             (1U 
                                                                              & (IData)(top__DOT__u_dcode__DOT___type_op))) 
                                                                            & (0x2007000ULL 
                                                                               == 
                                                                               (0xfe007000ULL 
                                                                                & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                  | (0x1dU 
                                                     & (- (IData)((IData)(
                                                                          ((1U 
                                                                            == 
                                                                            (1U 
                                                                             & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                           & (0x2004000ULL 
                                                                              == 
                                                                              (0xfe007000ULL 
                                                                               & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                 | (0x1eU 
                                                    & (- (IData)((IData)(
                                                                         ((1U 
                                                                           == 
                                                                           (1U 
                                                                            & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                          & (0x2005000ULL 
                                                                             == 
                                                                             (0xfe007000ULL 
                                                                              & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                                | (0x1fU 
                                                   & (- (IData)((IData)(
                                                                        ((1U 
                                                                          == 
                                                                          (1U 
                                                                           & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                         & (0x2006000ULL 
                                                                            == 
                                                                            (0xfe007000ULL 
                                                                             & vlSelf->top__DOT__u_fetch__DOT___mem_data)))))))) 
                                               | (0x20U 
                                                  & (- (IData)((IData)(
                                                                       ((1U 
                                                                         == 
                                                                         (1U 
                                                                          & (IData)(top__DOT__u_dcode__DOT___type_op_32))) 
                                                                        & (0x2007000ULL 
                                                                           == 
                                                                           (0xfe007000ULL 
                                                                            & vlSelf->top__DOT__u_fetch__DOT___mem_data))))))));
    vlSelf->top__DOT__u_dcode__DOT___exc_op = (((((
                                                   ((((((((1U 
                                                           & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_auipc)))) 
                                                          | (2U 
                                                             & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_lui))))) 
                                                         | (3U 
                                                            & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_jal))))) 
                                                        | (4U 
                                                           & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_jalr))))) 
                                                       | (5U 
                                                          & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_load))))) 
                                                      | (6U 
                                                         & (- (IData)((IData)(vlSelf->top__DOT__u_dcode__DOT___type_store))))) 
                                                     | (7U 
                                                        & (- (IData)((IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))))) 
                                                    | (8U 
                                                       & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_op_imm))))) 
                                                   | (9U 
                                                      & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_op_imm_32))))) 
                                                  | (0xaU 
                                                     & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_op))))) 
                                                 | (0xbU 
                                                    & (- (IData)((IData)(top__DOT__u_dcode__DOT___type_op_32))))) 
                                                | (0xcU 
                                                   & (- (IData)((IData)(top__DOT__u_dcode__DOT___isNeed_csr))))) 
                                               | (0xdU 
                                                  & (- (IData)((IData)(top__DOT__u_dcode__DOT___inst_ebreak)))));
    vlSelf->top__DOT__u_execute__DOT___csr_exe_valid 
        = (1U & (~ ((0U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_op)) 
                    | (1U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_op)))));
    top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_op2 
        = ((IData)(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR)
            ? (QData)((IData)((0x1fU & (IData)((vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                >> 0xfU)))))
            : vlSelf->top__DOT__rs1_data);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata 
        = ((0x300U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))
            ? vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_q
            : ((0x341U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))
                ? vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q
                : ((0x342U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))
                    ? vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_q
                    : ((0x343U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))
                        ? vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_q
                        : ((0x305U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))
                            ? vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q
                            : 0ULL)))));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed 
        = ((((0x19U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
             | (0x1dU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
            | (0x1bU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
           | (0x1fU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32 
        = ((((0x1dU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
             | (0x1eU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
            | (0x1fU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
           | (0x20U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra 
        = ((8U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
           | (0xbU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl 
        = ((7U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
           | (0xaU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll 
        = ((6U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
           | (9U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    top__DOT__u_execute__DOT__u_alu__DOT___isCMP = 
        ((((((((0xcU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
               | (0x13U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
              | (0xdU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
             | (0xeU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
            | (0xfU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
           | (0x10U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
          | (0x11U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
         | (0x12U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32 
        = (((9U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
            | (0xbU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
           | (0xaU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)));
    if (VL_UNLIKELY((0xdU == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)))) {
        VL_FINISH_MT("/home/leesum/ysyx-workbench/npc/vsrc/usr/execute.v", 101, "");
    }
    top__DOT__u_execute__DOT___rs1_rs2 = (((0xbU == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)) 
                                           | (0xaU 
                                              == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op))) 
                                          | (7U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)));
    top__DOT__u_execute__DOT___rs1_imm = ((((8U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)) 
                                            | (9U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op))) 
                                           | (5U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op))) 
                                          | (6U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)));
    top__DOT__u_execute__DOT___pc_4 = ((3U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)) 
                                       | (4U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)));
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en 
        = vlSelf->top__DOT__csr_mtvec_i_en;
    if ((0x300U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
        if ((0x341U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
            if ((0x342U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
                if ((0x343U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
                    if ((0x305U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
                        vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en 
                            = vlSelf->top__DOT__u_execute__DOT___csr_exe_valid;
                    }
                }
            }
        }
    }
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en 
        = (1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus));
    if ((0x300U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
        if ((0x341U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
            if ((0x342U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
                if ((0x343U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
                    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en 
                        = vlSelf->top__DOT__u_execute__DOT___csr_exe_valid;
                }
            }
        }
    }
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en 
        = (1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus));
    if ((0x300U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
        if ((0x341U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
            if ((0x342U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
                vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en 
                    = vlSelf->top__DOT__u_execute__DOT___csr_exe_valid;
            }
        }
    }
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_en 
        = vlSelf->top__DOT__csr_mstatus_i_en;
    if ((0x300U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
        vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_en 
            = vlSelf->top__DOT__u_execute__DOT___csr_exe_valid;
    }
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en 
        = (1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus));
    if ((0x300U != (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
        if ((0x341U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_idx))) {
            vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en 
                = vlSelf->top__DOT__u_execute__DOT___csr_exe_valid;
        }
    }
    vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result 
        = (((((- (QData)((IData)((2U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_op))))) 
              & top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_op2) 
             | ((- (QData)((IData)((3U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_op))))) 
                & (vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata 
                   | top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_op2))) 
            | ((- (QData)((IData)((4U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_op))))) 
               & (vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata 
                  & (~ top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_op2)))) 
           | ((- (QData)((IData)((1U == (IData)(vlSelf->top__DOT__u_dcode__DOT___csr_op))))) 
              & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata));
    top__DOT__u_execute__DOT__u_alu__DOT___isSUBop 
        = ((2U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
           | (IData)(top__DOT__u_execute__DOT__u_alu__DOT___isCMP));
    vlSelf->top__DOT__u_execute__DOT___alu_in2 = ((
                                                   ((((- (QData)((IData)(top__DOT__u_execute__DOT___rs1_rs2))) 
                                                      & vlSelf->top__DOT__rs2_data) 
                                                     | ((- (QData)((IData)(top__DOT__u_execute__DOT___rs1_imm))) 
                                                        & vlSelf->top__DOT__u_dcode__DOT___imm_data)) 
                                                    | ((- (QData)((IData)(
                                                                          (0xcU 
                                                                           == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op))))) 
                                                       & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata)) 
                                                   | (4ULL 
                                                      & (- (QData)((IData)(top__DOT__u_execute__DOT___pc_4))))) 
                                                  | (0xfffffffffffff000ULL 
                                                     & ((- (QData)((IData)(
                                                                           ((1U 
                                                                             == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)) 
                                                                            | (2U 
                                                                               == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)))))) 
                                                        & vlSelf->top__DOT__u_dcode__DOT___imm_data)));
    vlSelf->top__DOT__u_execute__DOT___alu_in1 = ((
                                                   (- (QData)((IData)(
                                                                      ((IData)(top__DOT__u_execute__DOT___rs1_rs2) 
                                                                       | (IData)(top__DOT__u_execute__DOT___rs1_imm))))) 
                                                   & vlSelf->top__DOT__rs1_data) 
                                                  | ((- (QData)((IData)(
                                                                        ((IData)(top__DOT__u_execute__DOT___pc_4) 
                                                                         | (1U 
                                                                            == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)))))) 
                                                     & vlSelf->top__DOT__u_pc__DOT___pc_current));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2 
        = (0x3fU & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                     ? (0x1fU & (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                     : (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)));
    top__DOT__u_execute__DOT__u_alu__DOT___alu_b[0U] 
        = ((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2) 
           ^ (- (IData)((IData)(top__DOT__u_execute__DOT__u_alu__DOT___isSUBop))));
    top__DOT__u_execute__DOT__u_alu__DOT___alu_b[1U] 
        = ((IData)((vlSelf->top__DOT__u_execute__DOT___alu_in2 
                    >> 0x20U)) ^ (- (IData)((IData)(top__DOT__u_execute__DOT__u_alu__DOT___isSUBop))));
    top__DOT__u_execute__DOT__u_alu__DOT___alu_b[2U] 
        = (1U & ((1U & (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in2 
                                >> 0x3fU))) ^ (- (IData)((IData)(top__DOT__u_execute__DOT__u_alu__DOT___isSUBop)))));
    __Vtemp24[0U] = (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1);
    __Vtemp24[1U] = (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in1 
                             >> 0x20U));
    __Vtemp24[2U] = (((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                        | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                       | (0x16U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                      | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                     & (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in1 
                                >> 0x3fU)));
    VL_EXTEND_WW(128,65, __Vtemp25, __Vtemp24);
    __Vtemp26[0U] = (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2);
    __Vtemp26[1U] = (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in2 
                             >> 0x20U));
    __Vtemp26[2U] = ((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                       | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                      | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                     & (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in2 
                                >> 0x3fU)));
    VL_EXTEND_WW(128,65, __Vtemp27, __Vtemp26);
    VL_MUL_W(4, __Vtemp28, __Vtemp25, __Vtemp27);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[0U] 
        = __Vtemp28[0U];
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[1U] 
        = __Vtemp28[1U];
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[2U] 
        = __Vtemp28[2U];
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[3U] 
        = __Vtemp28[3U];
    top__DOT__u_execute__DOT__u_alu__DOT___alu_a[0U] 
        = (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1);
    top__DOT__u_execute__DOT__u_alu__DOT___alu_a[1U] 
        = (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in1 
                   >> 0x20U));
    top__DOT__u_execute__DOT__u_alu__DOT___alu_a[2U] 
        = (1U & (IData)((vlSelf->top__DOT__u_execute__DOT___alu_in1 
                         >> 0x3fU)));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
        = ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
            ? (QData)((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1))
            : vlSelf->top__DOT__u_execute__DOT___alu_in1);
    VL_ADD_W(3, __Vtemp31, top__DOT__u_execute__DOT__u_alu__DOT___alu_a, top__DOT__u_execute__DOT__u_alu__DOT___alu_b);
    VL_EXTEND_WI(65,1, __Vtemp32, (IData)(top__DOT__u_execute__DOT__u_alu__DOT___isSUBop));
    VL_ADD_W(3, __Vtemp33, __Vtemp31, __Vtemp32);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
        = __Vtemp33[0U];
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U] 
        = __Vtemp33[1U];
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U] 
        = (1U & __Vtemp33[2U]);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffffffffffff8ULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | (IData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                              >> 0x3dU)) 
                                     << 2U)) | ((2U 
                                                 & ((IData)(
                                                            (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                             >> 0x3eU)) 
                                                    << 1U)) 
                                                | (1U 
                                                   & (IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x3fU))))))));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffffffffffffc7ULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x3aU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x3bU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x3cU))))))) 
              << 3U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffffffffffe3fULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x37U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x38U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x39U))))))) 
              << 6U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffffffffff1ffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x34U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x35U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x36U))))))) 
              << 9U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffffffffff8fffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x31U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x32U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x33U))))))) 
              << 0xcU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffffffffc7fffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x2eU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x2fU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x30U))))))) 
              << 0xfU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffffffffe3ffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x2bU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x2cU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x2dU))))))) 
              << 0x12U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffffffff1fffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x28U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x29U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x2aU))))))) 
              << 0x15U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffffff8ffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x25U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x26U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x27U))))))) 
              << 0x18U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffffffc7ffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x22U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x23U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x24U))))))) 
              << 0x1bU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffffe3fffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x1fU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x20U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x21U))))))) 
              << 0x1eU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffff1ffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x1cU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x1dU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x1eU))))))) 
              << 0x21U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffff8fffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x19U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x1aU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x1bU))))))) 
              << 0x24U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfffffc7fffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x16U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x17U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x18U))))))) 
              << 0x27U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffffe3ffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x13U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x14U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x15U))))))) 
              << 0x2aU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffff1fffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0x10U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0x11U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0x12U))))))) 
              << 0x2dU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfff8ffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0xdU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0xeU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0xfU))))))) 
              << 0x30U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xffc7ffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 0xaU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 0xbU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 0xcU))))))) 
              << 0x33U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xfe3fffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 7U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 8U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 9U))))))) 
              << 0x36U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0xf1ffffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 4U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 5U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 6U))))))) 
              << 0x39U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0x8fffffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                               >> 1U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                              >> 2U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                               >> 3U))))))) 
              << 0x3cU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv 
        = ((0x7fffffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv) 
           | ((QData)((IData)((1U & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num)))) 
              << 0x3fU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT 
        = (1U & ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U] 
                  >> 0x1fU) ^ (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U] 
                               ^ (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U] 
                                  >> 0x1fU))));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF 
        = (1U & ((IData)(top__DOT__u_execute__DOT__u_alu__DOT___isSUBop) 
                 ^ (((((top__DOT__u_execute__DOT__u_alu__DOT___alu_a[2U] 
                        | top__DOT__u_execute__DOT__u_alu__DOT___alu_b[2U]) 
                       | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U]) 
                      & ((top__DOT__u_execute__DOT__u_alu__DOT___alu_a[2U] 
                          | (~ top__DOT__u_execute__DOT__u_alu__DOT___alu_b[2U])) 
                         | (~ vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U]))) 
                     & (((~ top__DOT__u_execute__DOT__u_alu__DOT___alu_a[2U]) 
                         | top__DOT__u_execute__DOT__u_alu__DOT___alu_b[2U]) 
                        | (~ vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U]))) 
                    & (((~ top__DOT__u_execute__DOT__u_alu__DOT___alu_a[2U]) 
                        | (~ top__DOT__u_execute__DOT__u_alu__DOT___alu_b[2U])) 
                       | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U]))));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
        = (((- (QData)((IData)((((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra) 
                                 | (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl)) 
                                | (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))))) 
            & (((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra) 
                | (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))
                ? vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv
                : vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num)) 
           << (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffffffffffff8ULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | (IData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                              >> 0x3dU)) 
                                     << 2U)) | ((2U 
                                                 & ((IData)(
                                                            (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                             >> 0x3eU)) 
                                                    << 1U)) 
                                                | (1U 
                                                   & (IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x3fU))))))));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffffffffffffc7ULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x3aU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x3bU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x3cU))))))) 
              << 3U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffffffffffe3fULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x37U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x38U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x39U))))))) 
              << 6U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffffffffff1ffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x34U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x35U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x36U))))))) 
              << 9U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffffffffff8fffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x31U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x32U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x33U))))))) 
              << 0xcU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffffffffc7fffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x2eU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x2fU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x30U))))))) 
              << 0xfU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffffffffe3ffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x2bU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x2cU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x2dU))))))) 
              << 0x12U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffffffff1fffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x28U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x29U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x2aU))))))) 
              << 0x15U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffffff8ffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x25U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x26U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x27U))))))) 
              << 0x18U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffffffc7ffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x22U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x23U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x24U))))))) 
              << 0x1bU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffffe3fffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x1fU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x20U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x21U))))))) 
              << 0x1eU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffff1ffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x1cU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x1dU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x1eU))))))) 
              << 0x21U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffff8fffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x19U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x1aU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x1bU))))))) 
              << 0x24U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfffffc7fffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x16U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x17U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x18U))))))) 
              << 0x27U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffffe3ffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x13U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x14U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x15U))))))) 
              << 0x2aU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffff1fffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0x10U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0x11U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0x12U))))))) 
              << 0x2dU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfff8ffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0xdU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0xeU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0xfU))))))) 
              << 0x30U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xffc7ffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 0xaU)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 0xbU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 0xcU))))))) 
              << 0x33U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xfe3fffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 7U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 8U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 9U))))))) 
              << 0x36U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0xf1ffffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 4U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 5U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 6U))))))) 
              << 0x39U));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0x8fffffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)(((4U & ((IData)((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                               >> 1U)) 
                                      << 2U)) | ((2U 
                                                  & ((IData)(
                                                             (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                              >> 2U)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res 
                                                               >> 3U))))))) 
              << 0x3cU));
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
        = ((0x7fffffffffffffffULL & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
           | ((QData)((IData)((1U & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res)))) 
              << 0x3fU));
    top__DOT__u_execute__DOT__u_alu__DOT___alu_out 
        = (((((((((((- (QData)((IData)(((1U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                        | (2U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))))) 
                    & (((QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U])) 
                        << 0x20U) | (QData)((IData)(
                                                    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U])))) 
                   | ((- (QData)((IData)((5U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))))) 
                      & (vlSelf->top__DOT__u_execute__DOT___alu_in1 
                         & vlSelf->top__DOT__u_execute__DOT___alu_in2))) 
                  | ((- (QData)((IData)((4U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))))) 
                     & (vlSelf->top__DOT__u_execute__DOT___alu_in1 
                        | vlSelf->top__DOT__u_execute__DOT___alu_in2))) 
                 | ((- (QData)((IData)((3U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))))) 
                    & (vlSelf->top__DOT__u_execute__DOT___alu_in1 
                       ^ vlSelf->top__DOT__u_execute__DOT___alu_in2))) 
                | ((- (QData)((IData)((((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra) 
                                        | (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl)) 
                                       | (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))))) 
                   & ((((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))) 
                        & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
                       | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra))) 
                          & ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
                              & (0xffffffffffffffffULL 
                                 >> (0x3fU & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                               ? ((IData)(0x20U) 
                                                  + (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))
                                               : (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))))) 
                             | ((- (QData)((IData)(
                                                   (1U 
                                                    & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                        ? (IData)(
                                                                  (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                                   >> 0x1fU))
                                                        : (IData)(
                                                                  (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num 
                                                                   >> 0x3fU))))))) 
                                & (~ (0xffffffffffffffffULL 
                                      >> (0x3fU & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                    ? 
                                                   ((IData)(0x20U) 
                                                    + (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))
                                                    : (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))))))))) 
                      | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))) 
                         & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res)))) 
               | ((- (QData)((IData)((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))))) 
                  & (((QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[1U])) 
                      << 0x20U) | (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[0U]))))) 
              | ((- (QData)((IData)((((0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                      | (0x16U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                     | (0x17U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))))) 
                 & (((QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[3U])) 
                     << 0x20U) | (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[2U]))))) 
             | ((- (QData)((IData)((0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))))) 
                & (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result[0U])))) 
            | ((- (QData)((IData)(((((0x19U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                     | (0x1aU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                    | (0x1dU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                   | (0x1eU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))))) 
               & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                   ? (QData)((IData)(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                       ? VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                       : VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                   : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                       ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                       : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))))) 
           | ((- (QData)((IData)(((((0x1bU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                    | (0x1cU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                   | (0x1fU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                  | (0x20U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))))) 
              & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                  ? (QData)((IData)(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                      : VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                  : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                      ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                      : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))));
    vlSelf->top__DOT__u_execute__DOT___alu_out = ((IData)(top__DOT__u_execute__DOT__u_alu__DOT___isCMP)
                                                   ? (QData)((IData)(
                                                                     ((((((((0xcU 
                                                                             == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                                                            | (0x10U 
                                                                               == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                                                           & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)) 
                                                                          | (((0xdU 
                                                                               == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                                                              | (0x12U 
                                                                                == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                                                             & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))) 
                                                                         | ((0xeU 
                                                                             == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                                                            & (0U 
                                                                               == 
                                                                               ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                                                | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                                                                | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                                                        | ((0xfU 
                                                                            == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                                                           & (0U 
                                                                              != 
                                                                              ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                                                | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                                                               | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                                                       | ((0x11U 
                                                                           == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                                                          & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)))) 
                                                                      | ((0x13U 
                                                                          == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                                                         & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))))))
                                                   : top__DOT__u_execute__DOT__u_alu__DOT___alu_out);
    vlSelf->top__DOT__exc_out = (((9U == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)) 
                                  | (0xbU == (IData)(vlSelf->top__DOT__u_dcode__DOT___exc_op)))
                                  ? (((QData)((IData)(
                                                      (- (IData)(
                                                                 (1U 
                                                                  & (IData)(
                                                                            (vlSelf->top__DOT__u_execute__DOT___alu_out 
                                                                             >> 0x1fU))))))) 
                                      << 0x20U) | (QData)((IData)(vlSelf->top__DOT__u_execute__DOT___alu_out)))
                                  : vlSelf->top__DOT__u_execute__DOT___alu_out);
    vlSelf->top__DOT__u_memory__DOT___addr = ((0U == (IData)(vlSelf->top__DOT__u_dcode__DOT___mem_op))
                                               ? 0x80000000ULL
                                               : vlSelf->top__DOT__exc_out);
    vlSelf->top__DOT__u_pc__DOT___isready_branch = 
        ((1ULL == vlSelf->top__DOT__exc_out) & (1U 
                                                == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op)));
    vlSelf->top__DOT__u_pc__DOT___isready_inc4 = ((4U 
                                                   == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op)) 
                                                  | ((~ (IData)(vlSelf->top__DOT__u_pc__DOT___isready_branch)) 
                                                     & (1U 
                                                        == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op))));
    vlSelf->top__DOT__u_pc__DOT___pc_next = (((((- (QData)((IData)(
                                                                   ((((IData)(vlSelf->top__DOT__u_pc__DOT___isready_branch) 
                                                                      | (2U 
                                                                         == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op))) 
                                                                     | (IData)(vlSelf->top__DOT__u_pc__DOT___isready_inc4)) 
                                                                    | (0U 
                                                                       == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op)))))) 
                                                & vlSelf->top__DOT__u_pc__DOT___pc_current) 
                                               | ((- (QData)((IData)(
                                                                     (3U 
                                                                      == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op))))) 
                                                  & vlSelf->top__DOT__rs1_data)) 
                                              | ((- (QData)((IData)(
                                                                    (5U 
                                                                     == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op))))) 
                                                 & (((- (QData)((IData)(
                                                                        (1U 
                                                                         & ((IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus) 
                                                                            >> 2U))))) 
                                                     & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q) 
                                                    | ((- (QData)((IData)(
                                                                          (1U 
                                                                           & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))))) 
                                                       & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q)))) 
                                             + (((- (QData)((IData)(
                                                                    (((IData)(vlSelf->top__DOT__u_pc__DOT___isready_branch) 
                                                                      | (2U 
                                                                         == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op))) 
                                                                     | (3U 
                                                                        == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op)))))) 
                                                 & vlSelf->top__DOT__u_dcode__DOT___imm_data) 
                                                | (4ULL 
                                                   & (- (QData)((IData)(vlSelf->top__DOT__u_pc__DOT___isready_inc4))))));
}

void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    Vtop___024root___initial__TOP__2(vlSelf);
}

void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Body
    Vtop___024root___settle__TOP__3(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

void Vtop___024root___final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___final\n"); );
}

void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__rs1_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__rs2_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__csr_mtvec_i = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__csr_mstatus_i = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__csr_mtvec_i_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__csr_mstatus_i_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__exc_out = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_pc__DOT___isready_branch = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_pc__DOT___isready_inc4 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_pc__DOT___pc_next = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_pc__DOT___pc_current = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_fetch__DOT___mem_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dcode__DOT___type_store = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dcode__DOT___type_branch = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dcode__DOT___R_type = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dcode__DOT___I_type = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dcode__DOT___rd_idx = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__u_dcode__DOT___csr_idx = VL_RAND_RESET_I(12);
    vlSelf->top__DOT__u_dcode__DOT___imm_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dcode__DOT___csr_op = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_dcode__DOT___alu_op = VL_RAND_RESET_I(6);
    vlSelf->top__DOT__u_dcode__DOT___exc_op = VL_RAND_RESET_I(5);
    vlSelf->top__DOT__u_dcode__DOT___mem_op = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_dcode__DOT___pc_op = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus = VL_RAND_RESET_I(3);
    for (int __Vi0=0; __Vi0<32; ++__Vi0) {
        vlSelf->top__DOT__u_rv64reg__DOT__rf[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_q = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_q = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_q = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT___alu_in1 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT___alu_in2 = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT___alu_out = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT___csr_exe_valid = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(65, vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2 = VL_RAND_RESET_I(6);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result);
    vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_memory__DOT___ls8byte = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_memory__DOT___ls16byte = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_memory__DOT___ls32byte = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_memory__DOT___unsigned = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_memory__DOT___signed = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_memory__DOT___mem_read = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_memory__DOT___addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vtask_top__DOT__u_fetch__DOT__pmem_read__0__rdata = 0;
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}
