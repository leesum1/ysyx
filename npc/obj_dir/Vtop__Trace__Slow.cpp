// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__traceInitSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vtop___024root__traceInitTop(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vtop___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vtop___024root__traceInitSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+123,"clk", false,-1);
        tracep->declBit(c+124,"rst", false,-1);
        tracep->declBit(c+123,"top clk", false,-1);
        tracep->declBit(c+124,"top rst", false,-1);
        tracep->declQuad(c+1,"top pc", false,-1, 63,0);
        tracep->declBus(c+3,"top inst_data", false,-1, 31,0);
        tracep->declBus(c+4,"top rs1_idx", false,-1, 4,0);
        tracep->declBus(c+5,"top rs2_idx", false,-1, 4,0);
        tracep->declBus(c+6,"top rd_idx", false,-1, 4,0);
        tracep->declQuad(c+7,"top imm_data", false,-1, 63,0);
        tracep->declBus(c+9,"top alu_op", false,-1, 5,0);
        tracep->declBus(c+10,"top mem_op", false,-1, 3,0);
        tracep->declBus(c+11,"top exc_op", false,-1, 4,0);
        tracep->declBus(c+12,"top pc_op", false,-1, 2,0);
        tracep->declQuad(c+13,"top rs1_data", false,-1, 63,0);
        tracep->declQuad(c+15,"top rs2_data", false,-1, 63,0);
        tracep->declQuad(c+17,"top w_data", false,-1, 63,0);
        tracep->declBus(c+6,"top w_idx", false,-1, 4,0);
        tracep->declQuad(c+19,"top exc_out", false,-1, 63,0);
        tracep->declQuad(c+21,"top mem_out", false,-1, 63,0);
        tracep->declBit(c+23,"top isloadEnable", false,-1);
        tracep->declQuad(c+17,"top wb_data", false,-1, 63,0);
        tracep->declBit(c+123,"top u_pc clk", false,-1);
        tracep->declBit(c+124,"top u_pc rst", false,-1);
        tracep->declBus(c+12,"top u_pc pc_op", false,-1, 2,0);
        tracep->declQuad(c+13,"top u_pc rs1_data", false,-1, 63,0);
        tracep->declQuad(c+7,"top u_pc imm_data", false,-1, 63,0);
        tracep->declQuad(c+19,"top u_pc execute_data", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_pc pc_out", false,-1, 63,0);
        tracep->declBus(c+125,"top u_pc u_regpc WIDTH", false,-1, 31,0);
        tracep->declQuad(c+126,"top u_pc u_regpc RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+123,"top u_pc u_regpc clk", false,-1);
        tracep->declBit(c+124,"top u_pc u_regpc rst", false,-1);
        tracep->declQuad(c+24,"top u_pc u_regpc din", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_pc u_regpc dout", false,-1, 63,0);
        tracep->declBit(c+128,"top u_pc u_regpc wen", false,-1);
        tracep->declQuad(c+1,"top u_fetch inst_addr", false,-1, 63,0);
        tracep->declBus(c+3,"top u_fetch inst_data", false,-1, 31,0);
        tracep->declBus(c+3,"top u_dcode inst_data", false,-1, 31,0);
        tracep->declBus(c+4,"top u_dcode rs1_idx", false,-1, 4,0);
        tracep->declBus(c+5,"top u_dcode rs2_idx", false,-1, 4,0);
        tracep->declBus(c+6,"top u_dcode rd_idx", false,-1, 4,0);
        tracep->declQuad(c+7,"top u_dcode imm_data", false,-1, 63,0);
        tracep->declBus(c+9,"top u_dcode alu_op", false,-1, 5,0);
        tracep->declBus(c+10,"top u_dcode mem_op", false,-1, 3,0);
        tracep->declBus(c+11,"top u_dcode exc_op", false,-1, 4,0);
        tracep->declBus(c+12,"top u_dcode pc_op", false,-1, 2,0);
        tracep->declBit(c+123,"top u_rv64reg clk", false,-1);
        tracep->declBus(c+4,"top u_rv64reg rs1_idx", false,-1, 4,0);
        tracep->declBus(c+5,"top u_rv64reg rs2_idx", false,-1, 4,0);
        tracep->declQuad(c+13,"top u_rv64reg rs1_data", false,-1, 63,0);
        tracep->declQuad(c+15,"top u_rv64reg rs2_data", false,-1, 63,0);
        tracep->declBus(c+6,"top u_rv64reg write_idx", false,-1, 4,0);
        tracep->declQuad(c+17,"top u_rv64reg write_data", false,-1, 63,0);
        tracep->declBit(c+128,"top u_rv64reg wen", false,-1);
        {int i; for (i=0; i<32; i++) {
                tracep->declQuad(c+26+i*2,"top u_rv64reg rf", true,(i+0), 63,0);}}
        tracep->declQuad(c+1,"top u_execute pc", false,-1, 63,0);
        tracep->declBus(c+6,"top u_execute rd_idx", false,-1, 4,0);
        tracep->declQuad(c+13,"top u_execute rs1_data", false,-1, 63,0);
        tracep->declQuad(c+15,"top u_execute rs2_data", false,-1, 63,0);
        tracep->declQuad(c+7,"top u_execute imm_data", false,-1, 63,0);
        tracep->declBus(c+9,"top u_execute alu_op", false,-1, 5,0);
        tracep->declBus(c+10,"top u_execute mem_op", false,-1, 3,0);
        tracep->declBus(c+11,"top u_execute exc_op", false,-1, 4,0);
        tracep->declQuad(c+19,"top u_execute exc_out", false,-1, 63,0);
        tracep->declQuad(c+90,"top u_execute u_alu alu_a_i", false,-1, 63,0);
        tracep->declQuad(c+92,"top u_execute u_alu alu_b_i", false,-1, 63,0);
        tracep->declBus(c+9,"top u_execute u_alu alu_op_i", false,-1, 5,0);
        tracep->declQuad(c+94,"top u_execute u_alu alu_out", false,-1, 63,0);
        tracep->declBit(c+96,"top u_execute u_alu compare_out", false,-1);
        tracep->declBit(c+97,"top u_execute u_alu u_alu_shift shift_sra", false,-1);
        tracep->declBit(c+98,"top u_execute u_alu u_alu_shift shift_srl", false,-1);
        tracep->declBit(c+99,"top u_execute u_alu u_alu_shift shift_sll", false,-1);
        tracep->declBit(c+100,"top u_execute u_alu u_alu_shift isshift32", false,-1);
        tracep->declQuad(c+90,"top u_execute u_alu u_alu_shift shift_num", false,-1, 63,0);
        tracep->declBus(c+101,"top u_execute u_alu u_alu_shift shift_count", false,-1, 5,0);
        tracep->declQuad(c+102,"top u_execute u_alu u_alu_shift shift_out", false,-1, 63,0);
        tracep->declBus(c+125,"top u_execute u_alu u_alu_shift u_Vectorinvert1 DATA_LEN", false,-1, 31,0);
        tracep->declQuad(c+104,"top u_execute u_alu u_alu_shift u_Vectorinvert1 in", false,-1, 63,0);
        tracep->declQuad(c+106,"top u_execute u_alu u_alu_shift u_Vectorinvert1 out", false,-1, 63,0);
        tracep->declBus(c+129,"top u_execute u_alu u_alu_shift u_Vectorinvert1 i", false,-1, 31,0);
        tracep->declBus(c+125,"top u_execute u_alu u_alu_shift u_Vectorinvert2 DATA_LEN", false,-1, 31,0);
        tracep->declQuad(c+108,"top u_execute u_alu u_alu_shift u_Vectorinvert2 in", false,-1, 63,0);
        tracep->declQuad(c+110,"top u_execute u_alu u_alu_shift u_Vectorinvert2 out", false,-1, 63,0);
        tracep->declBus(c+129,"top u_execute u_alu u_alu_shift u_Vectorinvert2 i", false,-1, 31,0);
        tracep->declBit(c+112,"top u_execute u_alu u_alu_mul_top is_sr1_signed", false,-1);
        tracep->declBit(c+113,"top u_execute u_alu u_alu_mul_top is_sr2_signed", false,-1);
        tracep->declQuad(c+90,"top u_execute u_alu u_alu_mul_top sr1_data", false,-1, 63,0);
        tracep->declQuad(c+92,"top u_execute u_alu u_alu_mul_top sr2_data", false,-1, 63,0);
        tracep->declArray(c+114,"top u_execute u_alu u_alu_mul_top mul_result", false,-1, 127,0);
        tracep->declBit(c+118,"top u_execute u_alu u_alu_div_top is_sr1_signed", false,-1);
        tracep->declBit(c+112,"top u_execute u_alu u_alu_div_top is_sr2_signed", false,-1);
        tracep->declQuad(c+90,"top u_execute u_alu u_alu_div_top sr1_data", false,-1, 63,0);
        tracep->declQuad(c+92,"top u_execute u_alu u_alu_div_top sr2_data", false,-1, 63,0);
        tracep->declQuad(c+119,"top u_execute u_alu u_alu_div_top div_result", false,-1, 63,0);
        tracep->declQuad(c+121,"top u_execute u_alu u_alu_div_top rem_result", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_memory pc", false,-1, 63,0);
        tracep->declBus(c+6,"top u_memory rd_idx", false,-1, 4,0);
        tracep->declQuad(c+13,"top u_memory rs1_data", false,-1, 63,0);
        tracep->declQuad(c+15,"top u_memory rs2_data", false,-1, 63,0);
        tracep->declQuad(c+7,"top u_memory imm_data", false,-1, 63,0);
        tracep->declBus(c+10,"top u_memory mem_op", false,-1, 3,0);
        tracep->declQuad(c+19,"top u_memory exc_in", false,-1, 63,0);
        tracep->declQuad(c+21,"top u_memory mem_out", false,-1, 63,0);
        tracep->declBit(c+23,"top u_memory isloadEnable", false,-1);
        tracep->declQuad(c+19,"top u_writeback exc_data_in", false,-1, 63,0);
        tracep->declQuad(c+21,"top u_writeback mem_data_in", false,-1, 63,0);
        tracep->declBit(c+23,"top u_writeback isloadEnable", false,-1);
        tracep->declQuad(c+17,"top u_writeback wb_data", false,-1, 63,0);
    }
}

void Vtop___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vtop___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vtop___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vtop___024root__traceRegister(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vtop___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vtop___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vtop___024root__traceCleanup, vlSelf);
    }
}

void Vtop___024root__traceFullSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vtop___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vtop___024root* const __restrict vlSelf = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vtop___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vtop___024root__traceFullSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlWide<3>/*95:0*/ __Vtemp56;
    VlWide<3>/*95:0*/ __Vtemp59;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullQData(oldp+1,(vlSelf->top__DOT__u_pc__DOT___pc_current),64);
        tracep->fullIData(oldp+3,((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data)),32);
        tracep->fullCData(oldp+4,((((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                      | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
                                     | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                    | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))
                                    ? (0x1fU & (IData)(
                                                       (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                        >> 0xfU)))
                                    : 0U)),5);
        tracep->fullCData(oldp+5,(((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                     | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                    | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))
                                    ? (0x1fU & (IData)(
                                                       (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                        >> 0x14U)))
                                    : 0U)),5);
        tracep->fullCData(oldp+6,(vlSelf->top__DOT__u_dcode__DOT___rd_idx),5);
        tracep->fullQData(oldp+7,(vlSelf->top__DOT__u_dcode__DOT___imm_data),64);
        tracep->fullCData(oldp+9,(vlSelf->top__DOT__u_dcode__DOT___alu_op),6);
        tracep->fullCData(oldp+10,(vlSelf->top__DOT__u_dcode__DOT___mem_op),4);
        tracep->fullCData(oldp+11,(vlSelf->top__DOT__u_dcode__DOT___exc_op),5);
        tracep->fullCData(oldp+12,(vlSelf->top__DOT__u_dcode__DOT___pc_op),3);
        tracep->fullQData(oldp+13,(vlSelf->top__DOT__rs1_data),64);
        tracep->fullQData(oldp+15,(vlSelf->top__DOT__rs2_data),64);
        tracep->fullQData(oldp+17,((((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
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
        tracep->fullQData(oldp+19,(vlSelf->top__DOT__exc_out),64);
        tracep->fullQData(oldp+21,(((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
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
                                         : 0ULL))),64);
        tracep->fullBit(oldp+23,(((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                                  | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))));
        tracep->fullQData(oldp+24,(((((- (QData)((IData)(
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
                                       | (4ULL & (- (QData)((IData)(vlSelf->top__DOT__u_pc__DOT___isready_inc4))))))),64);
        tracep->fullQData(oldp+26,(vlSelf->top__DOT__u_rv64reg__DOT__rf[0]),64);
        tracep->fullQData(oldp+28,(vlSelf->top__DOT__u_rv64reg__DOT__rf[1]),64);
        tracep->fullQData(oldp+30,(vlSelf->top__DOT__u_rv64reg__DOT__rf[2]),64);
        tracep->fullQData(oldp+32,(vlSelf->top__DOT__u_rv64reg__DOT__rf[3]),64);
        tracep->fullQData(oldp+34,(vlSelf->top__DOT__u_rv64reg__DOT__rf[4]),64);
        tracep->fullQData(oldp+36,(vlSelf->top__DOT__u_rv64reg__DOT__rf[5]),64);
        tracep->fullQData(oldp+38,(vlSelf->top__DOT__u_rv64reg__DOT__rf[6]),64);
        tracep->fullQData(oldp+40,(vlSelf->top__DOT__u_rv64reg__DOT__rf[7]),64);
        tracep->fullQData(oldp+42,(vlSelf->top__DOT__u_rv64reg__DOT__rf[8]),64);
        tracep->fullQData(oldp+44,(vlSelf->top__DOT__u_rv64reg__DOT__rf[9]),64);
        tracep->fullQData(oldp+46,(vlSelf->top__DOT__u_rv64reg__DOT__rf[10]),64);
        tracep->fullQData(oldp+48,(vlSelf->top__DOT__u_rv64reg__DOT__rf[11]),64);
        tracep->fullQData(oldp+50,(vlSelf->top__DOT__u_rv64reg__DOT__rf[12]),64);
        tracep->fullQData(oldp+52,(vlSelf->top__DOT__u_rv64reg__DOT__rf[13]),64);
        tracep->fullQData(oldp+54,(vlSelf->top__DOT__u_rv64reg__DOT__rf[14]),64);
        tracep->fullQData(oldp+56,(vlSelf->top__DOT__u_rv64reg__DOT__rf[15]),64);
        tracep->fullQData(oldp+58,(vlSelf->top__DOT__u_rv64reg__DOT__rf[16]),64);
        tracep->fullQData(oldp+60,(vlSelf->top__DOT__u_rv64reg__DOT__rf[17]),64);
        tracep->fullQData(oldp+62,(vlSelf->top__DOT__u_rv64reg__DOT__rf[18]),64);
        tracep->fullQData(oldp+64,(vlSelf->top__DOT__u_rv64reg__DOT__rf[19]),64);
        tracep->fullQData(oldp+66,(vlSelf->top__DOT__u_rv64reg__DOT__rf[20]),64);
        tracep->fullQData(oldp+68,(vlSelf->top__DOT__u_rv64reg__DOT__rf[21]),64);
        tracep->fullQData(oldp+70,(vlSelf->top__DOT__u_rv64reg__DOT__rf[22]),64);
        tracep->fullQData(oldp+72,(vlSelf->top__DOT__u_rv64reg__DOT__rf[23]),64);
        tracep->fullQData(oldp+74,(vlSelf->top__DOT__u_rv64reg__DOT__rf[24]),64);
        tracep->fullQData(oldp+76,(vlSelf->top__DOT__u_rv64reg__DOT__rf[25]),64);
        tracep->fullQData(oldp+78,(vlSelf->top__DOT__u_rv64reg__DOT__rf[26]),64);
        tracep->fullQData(oldp+80,(vlSelf->top__DOT__u_rv64reg__DOT__rf[27]),64);
        tracep->fullQData(oldp+82,(vlSelf->top__DOT__u_rv64reg__DOT__rf[28]),64);
        tracep->fullQData(oldp+84,(vlSelf->top__DOT__u_rv64reg__DOT__rf[29]),64);
        tracep->fullQData(oldp+86,(vlSelf->top__DOT__u_rv64reg__DOT__rf[30]),64);
        tracep->fullQData(oldp+88,(vlSelf->top__DOT__u_rv64reg__DOT__rf[31]),64);
        tracep->fullQData(oldp+90,(vlSelf->top__DOT__u_execute__DOT___alu_in1),64);
        tracep->fullQData(oldp+92,(vlSelf->top__DOT__u_execute__DOT___alu_in2),64);
        tracep->fullQData(oldp+94,(vlSelf->top__DOT__u_execute__DOT___alu_out),64);
        tracep->fullBit(oldp+96,(((((((((0xcU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                        | (0x10U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                       & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)) 
                                      | (((0xdU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                          | (0x12U 
                                             == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                         & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))) 
                                     | ((0xeU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                        & (0U == ((
                                                   vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
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
        tracep->fullBit(oldp+97,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra));
        tracep->fullBit(oldp+98,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl));
        tracep->fullBit(oldp+99,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll));
        tracep->fullBit(oldp+100,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32));
        tracep->fullCData(oldp+101,((0x3fU & (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),6);
        tracep->fullQData(oldp+102,(((((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))) 
                                       & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res) 
                                      | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra))) 
                                         & ((vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res 
                                             & (0xffffffffffffffffULL 
                                                >> 
                                                (0x3fU 
                                                 & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                     ? 
                                                    ((IData)(0x20U) 
                                                     + (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                     : (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))))) 
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
                                                        + (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                        : (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))))))))) 
                                     | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))) 
                                        & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res))),64);
        tracep->fullQData(oldp+104,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num),64);
        tracep->fullQData(oldp+106,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv),64);
        tracep->fullQData(oldp+108,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res),64);
        tracep->fullQData(oldp+110,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res),64);
        tracep->fullBit(oldp+112,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_mul_sr1_signed));
        tracep->fullBit(oldp+113,((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                    | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                   | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
        tracep->fullWData(oldp+114,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result),128);
        tracep->fullBit(oldp+118,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_sr1_signed));
        VL_DIV_WWW(65, __Vtemp56, vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_div_top__DOT___sr1_65, vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_div_top__DOT___sr2_65);
        tracep->fullQData(oldp+119,((((QData)((IData)(
                                                      __Vtemp56[1U])) 
                                      << 0x20U) | (QData)((IData)(
                                                                  __Vtemp56[0U])))),64);
        VL_MODDIV_WWW(65, __Vtemp59, vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_div_top__DOT___sr1_65, vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_div_top__DOT___sr2_65);
        tracep->fullQData(oldp+121,((((QData)((IData)(
                                                      __Vtemp59[1U])) 
                                      << 0x20U) | (QData)((IData)(
                                                                  __Vtemp59[0U])))),64);
        tracep->fullBit(oldp+123,(vlSelf->clk));
        tracep->fullBit(oldp+124,(vlSelf->rst));
        tracep->fullIData(oldp+125,(0x40U),32);
        tracep->fullQData(oldp+126,(0x80000000ULL),64);
        tracep->fullBit(oldp+128,(1U));
        tracep->fullIData(oldp+129,(0x40U),32);
    }
}
