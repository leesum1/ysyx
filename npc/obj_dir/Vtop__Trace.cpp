// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__traceChgSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep);

void Vtop___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vtop___024root* const __restrict vlSelf = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vtop___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vtop___024root__traceChgSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
            tracep->chgQData(oldp+0,(vlSelf->top__DOT__u_pc__DOT___pc_current),64);
            tracep->chgIData(oldp+2,((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data)),32);
            tracep->chgCData(oldp+3,(((((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                          | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
                                         | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                        | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch)) 
                                       & (IData)(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR))
                                       ? (0x1fU & (IData)(
                                                          (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                           >> 0xfU)))
                                       : 0U)),5);
            tracep->chgCData(oldp+4,(((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                        | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                       | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))
                                       ? (0x1fU & (IData)(
                                                          (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                           >> 0x14U)))
                                       : 0U)),5);
            tracep->chgCData(oldp+5,(vlSelf->top__DOT__u_dcode__DOT___rd_idx),5);
            tracep->chgSData(oldp+6,(vlSelf->top__DOT__u_dcode__DOT___csr_idx),12);
            tracep->chgQData(oldp+7,(vlSelf->top__DOT__u_dcode__DOT___imm_data),64);
            tracep->chgQData(oldp+9,((QData)((IData)(
                                                     (0x1fU 
                                                      & (IData)(
                                                                (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                                 >> 0xfU)))))),64);
            tracep->chgBit(oldp+11,(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR));
            tracep->chgCData(oldp+12,(vlSelf->top__DOT__u_dcode__DOT___alu_op),6);
            tracep->chgCData(oldp+13,(vlSelf->top__DOT__u_dcode__DOT___mem_op),4);
            tracep->chgCData(oldp+14,(vlSelf->top__DOT__u_dcode__DOT___exc_op),5);
            tracep->chgCData(oldp+15,(vlSelf->top__DOT__u_dcode__DOT___pc_op),4);
            tracep->chgCData(oldp+16,(vlSelf->top__DOT__u_dcode__DOT___csr_op),3);
            tracep->chgQData(oldp+17,(vlSelf->top__DOT__rs1_data),64);
            tracep->chgQData(oldp+19,(vlSelf->top__DOT__rs2_data),64);
            tracep->chgQData(oldp+21,((((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                                        | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))
                                        ? ((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
                                            ? ((IData)(vlSelf->top__DOT__u_memory__DOT___ls8byte)
                                                ? (
                                                   ((- (QData)((IData)(
                                                                       (1U 
                                                                        & (IData)(
                                                                                (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                                >> 7U)))))) 
                                                    << 8U) 
                                                   | (QData)((IData)(
                                                                     (0xffU 
                                                                      & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))))
                                                : ((IData)(vlSelf->top__DOT__u_memory__DOT___ls16byte)
                                                    ? 
                                                   (((- (QData)((IData)(
                                                                        (1U 
                                                                         & (IData)(
                                                                                (vlSelf->top__DOT__u_memory__DOT___mem_read 
                                                                                >> 0xfU)))))) 
                                                     << 0x10U) 
                                                    | (QData)((IData)(
                                                                      (0xffffU 
                                                                       & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read)))))
                                                    : 
                                                   ((IData)(vlSelf->top__DOT__u_memory__DOT___ls32byte)
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
                                                    : 
                                                   ((IData)(vlSelf->top__DOT__u_memory__DOT___ls16byte)
                                                     ? (QData)((IData)(
                                                                       (0xffffU 
                                                                        & (IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))))
                                                     : 
                                                    ((IData)(vlSelf->top__DOT__u_memory__DOT___ls32byte)
                                                      ? (QData)((IData)(vlSelf->top__DOT__u_memory__DOT___mem_read))
                                                      : vlSelf->top__DOT__u_memory__DOT___mem_read)))
                                                : 0ULL))
                                        : vlSelf->top__DOT__exc_out)),64);
            tracep->chgQData(oldp+23,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q),64);
            tracep->chgQData(oldp+25,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_q),64);
            tracep->chgQData(oldp+27,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_q),64);
            tracep->chgQData(oldp+29,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q),64);
            tracep->chgQData(oldp+31,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata),64);
            tracep->chgBit(oldp+33,(vlSelf->top__DOT__u_execute__DOT___csr_exe_valid));
            tracep->chgQData(oldp+34,(vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result),64);
            tracep->chgQData(oldp+36,(vlSelf->top__DOT__exc_out),64);
            tracep->chgQData(oldp+38,(((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
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
                                                ? (
                                                   ((- (QData)((IData)(
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
                                            : 0ULL))),64);
            tracep->chgBit(oldp+40,(((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                                     | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))));
            tracep->chgQData(oldp+41,(((((- (QData)((IData)(
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
                                       + (((- (QData)((IData)(
                                                              (((IData)(vlSelf->top__DOT__u_pc__DOT___isready_branch) 
                                                                | (2U 
                                                                   == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op))) 
                                                               | (3U 
                                                                  == (IData)(vlSelf->top__DOT__u_dcode__DOT___pc_op)))))) 
                                           & vlSelf->top__DOT__u_dcode__DOT___imm_data) 
                                          | (4ULL & 
                                             (- (QData)((IData)(vlSelf->top__DOT__u_pc__DOT___isready_inc4))))))),64);
            tracep->chgQData(oldp+43,(vlSelf->top__DOT__u_rv64reg__DOT__rf[0]),64);
            tracep->chgQData(oldp+45,(vlSelf->top__DOT__u_rv64reg__DOT__rf[1]),64);
            tracep->chgQData(oldp+47,(vlSelf->top__DOT__u_rv64reg__DOT__rf[2]),64);
            tracep->chgQData(oldp+49,(vlSelf->top__DOT__u_rv64reg__DOT__rf[3]),64);
            tracep->chgQData(oldp+51,(vlSelf->top__DOT__u_rv64reg__DOT__rf[4]),64);
            tracep->chgQData(oldp+53,(vlSelf->top__DOT__u_rv64reg__DOT__rf[5]),64);
            tracep->chgQData(oldp+55,(vlSelf->top__DOT__u_rv64reg__DOT__rf[6]),64);
            tracep->chgQData(oldp+57,(vlSelf->top__DOT__u_rv64reg__DOT__rf[7]),64);
            tracep->chgQData(oldp+59,(vlSelf->top__DOT__u_rv64reg__DOT__rf[8]),64);
            tracep->chgQData(oldp+61,(vlSelf->top__DOT__u_rv64reg__DOT__rf[9]),64);
            tracep->chgQData(oldp+63,(vlSelf->top__DOT__u_rv64reg__DOT__rf[10]),64);
            tracep->chgQData(oldp+65,(vlSelf->top__DOT__u_rv64reg__DOT__rf[11]),64);
            tracep->chgQData(oldp+67,(vlSelf->top__DOT__u_rv64reg__DOT__rf[12]),64);
            tracep->chgQData(oldp+69,(vlSelf->top__DOT__u_rv64reg__DOT__rf[13]),64);
            tracep->chgQData(oldp+71,(vlSelf->top__DOT__u_rv64reg__DOT__rf[14]),64);
            tracep->chgQData(oldp+73,(vlSelf->top__DOT__u_rv64reg__DOT__rf[15]),64);
            tracep->chgQData(oldp+75,(vlSelf->top__DOT__u_rv64reg__DOT__rf[16]),64);
            tracep->chgQData(oldp+77,(vlSelf->top__DOT__u_rv64reg__DOT__rf[17]),64);
            tracep->chgQData(oldp+79,(vlSelf->top__DOT__u_rv64reg__DOT__rf[18]),64);
            tracep->chgQData(oldp+81,(vlSelf->top__DOT__u_rv64reg__DOT__rf[19]),64);
            tracep->chgQData(oldp+83,(vlSelf->top__DOT__u_rv64reg__DOT__rf[20]),64);
            tracep->chgQData(oldp+85,(vlSelf->top__DOT__u_rv64reg__DOT__rf[21]),64);
            tracep->chgQData(oldp+87,(vlSelf->top__DOT__u_rv64reg__DOT__rf[22]),64);
            tracep->chgQData(oldp+89,(vlSelf->top__DOT__u_rv64reg__DOT__rf[23]),64);
            tracep->chgQData(oldp+91,(vlSelf->top__DOT__u_rv64reg__DOT__rf[24]),64);
            tracep->chgQData(oldp+93,(vlSelf->top__DOT__u_rv64reg__DOT__rf[25]),64);
            tracep->chgQData(oldp+95,(vlSelf->top__DOT__u_rv64reg__DOT__rf[26]),64);
            tracep->chgQData(oldp+97,(vlSelf->top__DOT__u_rv64reg__DOT__rf[27]),64);
            tracep->chgQData(oldp+99,(vlSelf->top__DOT__u_rv64reg__DOT__rf[28]),64);
            tracep->chgQData(oldp+101,(vlSelf->top__DOT__u_rv64reg__DOT__rf[29]),64);
            tracep->chgQData(oldp+103,(vlSelf->top__DOT__u_rv64reg__DOT__rf[30]),64);
            tracep->chgQData(oldp+105,(vlSelf->top__DOT__u_rv64reg__DOT__rf[31]),64);
            tracep->chgQData(oldp+107,(((IData)(vlSelf->top__DOT__csr_mepc_i_en)
                                         ? vlSelf->top__DOT__csr_mepc_i
                                         : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
            tracep->chgBit(oldp+109,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en));
            tracep->chgQData(oldp+110,(((IData)(vlSelf->top__DOT__csr_mcause_i_en)
                                         ? vlSelf->top__DOT__csr_mcause_i
                                         : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
            tracep->chgBit(oldp+112,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en));
            tracep->chgQData(oldp+113,(((IData)(vlSelf->top__DOT__csr_mtval_i_en)
                                         ? vlSelf->top__DOT__csr_mtval_i
                                         : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
            tracep->chgBit(oldp+115,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en));
            tracep->chgQData(oldp+116,(((IData)(vlSelf->top__DOT__csr_mtvec_i_en)
                                         ? vlSelf->top__DOT__csr_mtvec_i
                                         : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
            tracep->chgBit(oldp+118,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en));
            tracep->chgQData(oldp+119,(vlSelf->top__DOT__u_execute__DOT___alu_in1),64);
            tracep->chgQData(oldp+121,(vlSelf->top__DOT__u_execute__DOT___alu_in2),64);
            tracep->chgQData(oldp+123,(vlSelf->top__DOT__u_execute__DOT___alu_out),64);
            tracep->chgBit(oldp+125,(((((((((0xcU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                            | (0x10U 
                                               == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                           & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)) 
                                          | (((0xdU 
                                               == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                              | (0x12U 
                                                 == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                             & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))) 
                                         | ((0xeU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                            & (0U == 
                                               ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                 | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                                | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                        | ((0xfU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                           & (0U != 
                                              ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                               | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                       | ((0x11U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                          & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)))) 
                                      | ((0x13U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                         & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))))));
            tracep->chgBit(oldp+126,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra));
            tracep->chgBit(oldp+127,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl));
            tracep->chgBit(oldp+128,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll));
            tracep->chgBit(oldp+129,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32));
            tracep->chgCData(oldp+130,((0x3fU & (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),6);
            tracep->chgQData(oldp+131,(((((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))) 
                                          & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
                                         | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra))) 
                                            & ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
                                                & (0xffffffffffffffffULL 
                                                   >> 
                                                   (0x3fU 
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
                                                  & (~ 
                                                     (0xffffffffffffffffULL 
                                                      >> 
                                                      (0x3fU 
                                                       & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                           ? 
                                                          ((IData)(0x20U) 
                                                           + (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))
                                                           : (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))))))))) 
                                        | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))) 
                                           & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res))),64);
            tracep->chgQData(oldp+133,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num),64);
            tracep->chgQData(oldp+135,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv),64);
            tracep->chgQData(oldp+137,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res),64);
            tracep->chgQData(oldp+139,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res),64);
            tracep->chgBit(oldp+141,(((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                        | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                       | (0x16U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                      | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
            tracep->chgBit(oldp+142,((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                       | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                      | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
            tracep->chgWData(oldp+143,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result),128);
            tracep->chgBit(oldp+147,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed));
            tracep->chgBit(oldp+148,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32));
            tracep->chgQData(oldp+149,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                                         ? (QData)((IData)(
                                                           ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                             ? 
                                                            VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                             : 
                                                            VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                                         : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                             ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                             : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
            tracep->chgQData(oldp+151,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                                         ? (QData)((IData)(
                                                           ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                             ? 
                                                            VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                             : 
                                                            VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                                         : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                             ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                             : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
            tracep->chgQData(oldp+153,(VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
            tracep->chgQData(oldp+155,(VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
            tracep->chgQData(oldp+157,(VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
            tracep->chgQData(oldp+159,(VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
            tracep->chgQData(oldp+161,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                         ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                         : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
            tracep->chgQData(oldp+163,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                         ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                         : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
            tracep->chgIData(oldp+165,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1)),32);
            tracep->chgIData(oldp+166,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)),32);
            tracep->chgIData(oldp+167,(VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
            tracep->chgIData(oldp+168,(VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
            tracep->chgIData(oldp+169,(VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
            tracep->chgIData(oldp+170,(VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
            tracep->chgIData(oldp+171,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                         ? VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                         : VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
            tracep->chgIData(oldp+172,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                         ? VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                         : VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
        }
        tracep->chgBit(oldp+173,(vlSelf->clk));
        tracep->chgBit(oldp+174,(vlSelf->rst));
    }
}

void Vtop___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    Vtop___024root* const __restrict vlSelf = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
        vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    }
}
