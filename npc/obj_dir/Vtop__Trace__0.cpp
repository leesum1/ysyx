// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgQData(oldp+0,(vlSelf->top__DOT__u_pc__DOT___pc_current),64);
        bufp->chgIData(oldp+2,((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data)),32);
        bufp->chgCData(oldp+3,(((((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                    | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
                                   | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                  | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch)) 
                                 & (~ (IData)(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR)))
                                 ? (0x1fU & (IData)(
                                                    (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                     >> 0xfU)))
                                 : 0U)),5);
        bufp->chgCData(oldp+4,(((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                  | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                 | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))
                                 ? (0x1fU & (IData)(
                                                    (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                     >> 0x14U)))
                                 : 0U)),5);
        bufp->chgCData(oldp+5,(vlSelf->top__DOT__u_dcode__DOT___rd_idx),5);
        bufp->chgSData(oldp+6,(vlSelf->top__DOT__u_dcode__DOT___csr_idx),12);
        bufp->chgQData(oldp+7,(vlSelf->top__DOT__u_dcode__DOT___imm_data),64);
        bufp->chgQData(oldp+9,((QData)((IData)((0x1fU 
                                                & (IData)(
                                                          (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                           >> 0xfU)))))),64);
        bufp->chgBit(oldp+11,(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR));
        bufp->chgCData(oldp+12,(vlSelf->top__DOT__u_dcode__DOT___alu_op),6);
        bufp->chgCData(oldp+13,(vlSelf->top__DOT__u_dcode__DOT___mem_op),4);
        bufp->chgCData(oldp+14,(vlSelf->top__DOT__u_dcode__DOT___exc_op),5);
        bufp->chgCData(oldp+15,(vlSelf->top__DOT__u_dcode__DOT___pc_op),4);
        bufp->chgCData(oldp+16,(vlSelf->top__DOT__u_dcode__DOT___csr_op),3);
        bufp->chgCData(oldp+17,(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus),3);
        bufp->chgQData(oldp+18,(vlSelf->top__DOT__rs1_data),64);
        bufp->chgQData(oldp+20,(vlSelf->top__DOT__rs2_data),64);
        bufp->chgQData(oldp+22,((((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                                  | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))
                                  ? ((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
                                      ? ((IData)(vlSelf->top__DOT__u_memory__DOT___ls8byte)
                                          ? (((- (QData)((IData)(
                                                                 (1U 
                                                                  & (IData)(
                                                                            (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                             >> 7U)))))) 
                                              << 8U) 
                                             | (QData)((IData)(
                                                               (0xffU 
                                                                & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))))
                                          : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls16byte)
                                              ? (((- (QData)((IData)(
                                                                     (1U 
                                                                      & (IData)(
                                                                                (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                                >> 0xfU)))))) 
                                                  << 0x10U) 
                                                 | (QData)((IData)(
                                                                   (0xffffU 
                                                                    & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))))
                                              : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls32byte)
                                                  ? 
                                                 (((QData)((IData)(
                                                                   (- (IData)(
                                                                              (1U 
                                                                               & (IData)(
                                                                                (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                                >> 0x1fU))))))) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                                  : vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                      : ((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned)
                                          ? ((IData)(vlSelf->top__DOT__u_memory__DOT___ls8byte)
                                              ? (QData)((IData)(
                                                                (0xffU 
                                                                 & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))))
                                              : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls16byte)
                                                  ? (QData)((IData)(
                                                                    (0xffffU 
                                                                     & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))))
                                                  : 
                                                 ((IData)(vlSelf->top__DOT__u_memory__DOT___ls32byte)
                                                   ? (QData)((IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))
                                                   : vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                          : 0ULL)) : vlSelf->top__DOT__exc_out)),64);
        bufp->chgQData(oldp+24,((QData)((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data))),64);
        bufp->chgBit(oldp+26,((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))));
        bufp->chgQData(oldp+27,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q),64);
        bufp->chgQData(oldp+29,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_q),64);
        bufp->chgQData(oldp+31,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_q),64);
        bufp->chgQData(oldp+33,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q),64);
        bufp->chgQData(oldp+35,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_q),64);
        bufp->chgQData(oldp+37,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata),64);
        bufp->chgBit(oldp+39,(vlSelf->top__DOT__u_execute__DOT___csr_exe_valid));
        bufp->chgQData(oldp+40,(vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result),64);
        bufp->chgQData(oldp+42,(vlSelf->top__DOT__exc_out),64);
        bufp->chgQData(oldp+44,(((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
                                  ? ((IData)(vlSelf->top__DOT__u_memory__DOT___ls8byte)
                                      ? (((- (QData)((IData)(
                                                             (1U 
                                                              & (IData)(
                                                                        (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                         >> 7U)))))) 
                                          << 8U) | (QData)((IData)(
                                                                   (0xffU 
                                                                    & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))))
                                      : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls16byte)
                                          ? (((- (QData)((IData)(
                                                                 (1U 
                                                                  & (IData)(
                                                                            (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                             >> 0xfU)))))) 
                                              << 0x10U) 
                                             | (QData)((IData)(
                                                               (0xffffU 
                                                                & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))))
                                          : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls32byte)
                                              ? (((QData)((IData)(
                                                                  (- (IData)(
                                                                             (1U 
                                                                              & (IData)(
                                                                                (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                                >> 0x1fU))))))) 
                                                  << 0x20U) 
                                                 | (QData)((IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                              : vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                  : ((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned)
                                      ? ((IData)(vlSelf->top__DOT__u_memory__DOT___ls8byte)
                                          ? (QData)((IData)(
                                                            (0xffU 
                                                             & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))))
                                          : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls16byte)
                                              ? (QData)((IData)(
                                                                (0xffffU 
                                                                 & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))))
                                              : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls32byte)
                                                  ? (QData)((IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))
                                                  : vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                      : 0ULL))),64);
        bufp->chgBit(oldp+46,(((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                               | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))));
        bufp->chgQData(oldp+47,((((- (QData)((IData)(
                                                     (1U 
                                                      & ((IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus) 
                                                         >> 2U))))) 
                                  & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q) 
                                 | ((- (QData)((IData)(
                                                       (1U 
                                                        & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))))) 
                                    & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q))),64);
        bufp->chgBit(oldp+49,((IData)((0U != (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus)))));
        bufp->chgQData(oldp+50,(vlSelf->top__DOT__u_execute__DOT___alu_in1),64);
        bufp->chgQData(oldp+52,(vlSelf->top__DOT__u_execute__DOT___alu_in2),64);
        bufp->chgQData(oldp+54,(vlSelf->top__DOT__u_execute__DOT___alu_out),64);
        bufp->chgBit(oldp+56,(((((((((0xcU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                     | (0x10U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                    & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)) 
                                   | (((0xdU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                       | (0x12U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                      & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))) 
                                  | ((0xeU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                     & (0U == ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                               | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                 | ((0xfU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                    & (0U != ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                               | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                              | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                | ((0x11U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                   & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)))) 
                               | ((0x13U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                  & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))))));
        bufp->chgBit(oldp+57,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed));
        bufp->chgBit(oldp+58,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32));
        bufp->chgQData(oldp+59,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                                  ? (QData)((IData)(
                                                    ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                      ? 
                                                     VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                      : 
                                                     VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                                  : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                      : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
        bufp->chgQData(oldp+61,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                                  ? (QData)((IData)(
                                                    ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                      ? 
                                                     VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                      : 
                                                     VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                                  : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                      : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
        bufp->chgQData(oldp+63,(VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        bufp->chgQData(oldp+65,(VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        bufp->chgQData(oldp+67,(VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        bufp->chgQData(oldp+69,(VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        bufp->chgQData(oldp+71,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                  ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                  : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
        bufp->chgQData(oldp+73,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                  ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                  : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
        bufp->chgIData(oldp+75,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1)),32);
        bufp->chgIData(oldp+76,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)),32);
        bufp->chgIData(oldp+77,(VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        bufp->chgIData(oldp+78,(VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        bufp->chgIData(oldp+79,(VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        bufp->chgIData(oldp+80,(VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        bufp->chgIData(oldp+81,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                  ? VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                  : VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
        bufp->chgIData(oldp+82,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                  ? VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                  : VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
        bufp->chgBit(oldp+83,(((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                 | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                | (0x16U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                               | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
        bufp->chgBit(oldp+84,((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                               | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
        bufp->chgWData(oldp+85,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result),128);
        bufp->chgBit(oldp+89,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra));
        bufp->chgBit(oldp+90,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl));
        bufp->chgBit(oldp+91,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll));
        bufp->chgBit(oldp+92,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32));
        bufp->chgCData(oldp+93,((0x3fU & (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),6);
        bufp->chgQData(oldp+94,(((((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))) 
                                   & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
                                  | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra))) 
                                     & ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
                                         & (0xffffffffffffffffULL 
                                            >> (0x3fU 
                                                & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                    ? 
                                                   ((IData)(0x20U) 
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
                                                 >> 
                                                 (0x3fU 
                                                  & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                      ? 
                                                     ((IData)(0x20U) 
                                                      + (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))
                                                      : (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))))))))) 
                                 | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))) 
                                    & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res))),64);
        bufp->chgQData(oldp+96,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num),64);
        bufp->chgQData(oldp+98,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv),64);
        bufp->chgQData(oldp+100,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res),64);
        bufp->chgQData(oldp+102,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res),64);
        bufp->chgQData(oldp+104,((((((- (QData)((IData)(
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
                                     | (4ULL & (- (QData)((IData)(vlSelf->top__DOT__u_pc__DOT___isready_inc4))))))),64);
        bufp->chgQData(oldp+106,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                   ? 0xbULL : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        bufp->chgBit(oldp+108,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en));
        bufp->chgQData(oldp+109,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                   ? vlSelf->top__DOT__u_pc__DOT___pc_current
                                   : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        bufp->chgBit(oldp+111,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en));
        bufp->chgQData(oldp+112,(((IData)(vlSelf->top__DOT__csr_mstatus_i_en)
                                   ? vlSelf->top__DOT__csr_mstatus_i
                                   : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        bufp->chgBit(oldp+114,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_en));
        bufp->chgQData(oldp+115,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                   ? (QData)((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data))
                                   : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        bufp->chgBit(oldp+117,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en));
        bufp->chgQData(oldp+118,(((IData)(vlSelf->top__DOT__csr_mtvec_i_en)
                                   ? vlSelf->top__DOT__csr_mtvec_i
                                   : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        bufp->chgBit(oldp+120,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en));
        bufp->chgQData(oldp+121,(vlSelf->top__DOT__u_rv64reg__DOT__rf[0]),64);
        bufp->chgQData(oldp+123,(vlSelf->top__DOT__u_rv64reg__DOT__rf[1]),64);
        bufp->chgQData(oldp+125,(vlSelf->top__DOT__u_rv64reg__DOT__rf[2]),64);
        bufp->chgQData(oldp+127,(vlSelf->top__DOT__u_rv64reg__DOT__rf[3]),64);
        bufp->chgQData(oldp+129,(vlSelf->top__DOT__u_rv64reg__DOT__rf[4]),64);
        bufp->chgQData(oldp+131,(vlSelf->top__DOT__u_rv64reg__DOT__rf[5]),64);
        bufp->chgQData(oldp+133,(vlSelf->top__DOT__u_rv64reg__DOT__rf[6]),64);
        bufp->chgQData(oldp+135,(vlSelf->top__DOT__u_rv64reg__DOT__rf[7]),64);
        bufp->chgQData(oldp+137,(vlSelf->top__DOT__u_rv64reg__DOT__rf[8]),64);
        bufp->chgQData(oldp+139,(vlSelf->top__DOT__u_rv64reg__DOT__rf[9]),64);
        bufp->chgQData(oldp+141,(vlSelf->top__DOT__u_rv64reg__DOT__rf[10]),64);
        bufp->chgQData(oldp+143,(vlSelf->top__DOT__u_rv64reg__DOT__rf[11]),64);
        bufp->chgQData(oldp+145,(vlSelf->top__DOT__u_rv64reg__DOT__rf[12]),64);
        bufp->chgQData(oldp+147,(vlSelf->top__DOT__u_rv64reg__DOT__rf[13]),64);
        bufp->chgQData(oldp+149,(vlSelf->top__DOT__u_rv64reg__DOT__rf[14]),64);
        bufp->chgQData(oldp+151,(vlSelf->top__DOT__u_rv64reg__DOT__rf[15]),64);
        bufp->chgQData(oldp+153,(vlSelf->top__DOT__u_rv64reg__DOT__rf[16]),64);
        bufp->chgQData(oldp+155,(vlSelf->top__DOT__u_rv64reg__DOT__rf[17]),64);
        bufp->chgQData(oldp+157,(vlSelf->top__DOT__u_rv64reg__DOT__rf[18]),64);
        bufp->chgQData(oldp+159,(vlSelf->top__DOT__u_rv64reg__DOT__rf[19]),64);
        bufp->chgQData(oldp+161,(vlSelf->top__DOT__u_rv64reg__DOT__rf[20]),64);
        bufp->chgQData(oldp+163,(vlSelf->top__DOT__u_rv64reg__DOT__rf[21]),64);
        bufp->chgQData(oldp+165,(vlSelf->top__DOT__u_rv64reg__DOT__rf[22]),64);
        bufp->chgQData(oldp+167,(vlSelf->top__DOT__u_rv64reg__DOT__rf[23]),64);
        bufp->chgQData(oldp+169,(vlSelf->top__DOT__u_rv64reg__DOT__rf[24]),64);
        bufp->chgQData(oldp+171,(vlSelf->top__DOT__u_rv64reg__DOT__rf[25]),64);
        bufp->chgQData(oldp+173,(vlSelf->top__DOT__u_rv64reg__DOT__rf[26]),64);
        bufp->chgQData(oldp+175,(vlSelf->top__DOT__u_rv64reg__DOT__rf[27]),64);
        bufp->chgQData(oldp+177,(vlSelf->top__DOT__u_rv64reg__DOT__rf[28]),64);
        bufp->chgQData(oldp+179,(vlSelf->top__DOT__u_rv64reg__DOT__rf[29]),64);
        bufp->chgQData(oldp+181,(vlSelf->top__DOT__u_rv64reg__DOT__rf[30]),64);
        bufp->chgQData(oldp+183,(vlSelf->top__DOT__u_rv64reg__DOT__rf[31]),64);
    }
    bufp->chgBit(oldp+185,(vlSelf->clk));
    bufp->chgBit(oldp+186,(vlSelf->rst));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
