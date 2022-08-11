// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+1,"pc", false,-1, 63,0);
    tracep->declBus(c+3,"inst_data", false,-1, 31,0);
    tracep->declBus(c+4,"rs1_idx", false,-1, 4,0);
    tracep->declBus(c+5,"rs2_idx", false,-1, 4,0);
    tracep->declBus(c+6,"rd_idx", false,-1, 4,0);
    tracep->declBus(c+7,"csr_idx", false,-1, 11,0);
    tracep->declQuad(c+8,"imm_data", false,-1, 63,0);
    tracep->declQuad(c+10,"imm_csr", false,-1, 63,0);
    tracep->declBit(c+12,"isNeedimmCSR", false,-1);
    tracep->declBus(c+13,"alu_op", false,-1, 5,0);
    tracep->declBus(c+14,"mem_op", false,-1, 3,0);
    tracep->declBus(c+15,"exc_op", false,-1, 4,0);
    tracep->declBus(c+16,"pc_op", false,-1, 3,0);
    tracep->declBus(c+17,"csr_op", false,-1, 2,0);
    tracep->declBus(c+18,"trap_bus", false,-1, 2,0);
    tracep->declQuad(c+19,"rs1_data", false,-1, 63,0);
    tracep->declQuad(c+21,"rs2_data", false,-1, 63,0);
    tracep->declQuad(c+23,"w_data", false,-1, 63,0);
    tracep->declBus(c+6,"w_idx", false,-1, 4,0);
    tracep->declQuad(c+1,"csr_mepc_i", false,-1, 63,0);
    tracep->declQuad(c+188,"csr_mcause_i", false,-1, 63,0);
    tracep->declQuad(c+25,"csr_mtval_i", false,-1, 63,0);
    tracep->declQuad(c+190,"csr_mtvec_i", false,-1, 63,0);
    tracep->declQuad(c+192,"csr_mstatus_i", false,-1, 63,0);
    tracep->declBit(c+27,"csr_mepc_i_en", false,-1);
    tracep->declBit(c+27,"csr_mcause_i_en", false,-1);
    tracep->declBit(c+27,"csr_mtval_i_en", false,-1);
    tracep->declBit(c+194,"csr_mtvec_i_en", false,-1);
    tracep->declBit(c+195,"csr_mstatus_i_en", false,-1);
    tracep->declQuad(c+28,"csr_mepc_o", false,-1, 63,0);
    tracep->declQuad(c+30,"csr_mcause_o", false,-1, 63,0);
    tracep->declQuad(c+32,"csr_mtval_o", false,-1, 63,0);
    tracep->declQuad(c+34,"csr_mtvec_o", false,-1, 63,0);
    tracep->declQuad(c+36,"csr_mstatus_o", false,-1, 63,0);
    tracep->declBus(c+7,"csr_readaddr", false,-1, 11,0);
    tracep->declQuad(c+38,"csr_readdata", false,-1, 63,0);
    tracep->declBus(c+7,"csr_writeaddr", false,-1, 11,0);
    tracep->declBit(c+40,"write_enable", false,-1);
    tracep->declQuad(c+41,"csr_writedata", false,-1, 63,0);
    tracep->declQuad(c+43,"exc_out", false,-1, 63,0);
    tracep->declQuad(c+41,"exc_csr_out", false,-1, 63,0);
    tracep->declBit(c+40,"exc_csr_valid", false,-1);
    tracep->declQuad(c+45,"mem_out", false,-1, 63,0);
    tracep->declBit(c+47,"isloadEnable", false,-1);
    tracep->declQuad(c+23,"wb_data", false,-1, 63,0);
    tracep->declQuad(c+48,"clint_pc", false,-1, 63,0);
    tracep->declBit(c+50,"clint_pc_valid", false,-1);
    tracep->pushNamePrefix("u_clint ");
    tracep->declQuad(c+1,"pc_i", false,-1, 63,0);
    tracep->declBus(c+3,"inst_data_i", false,-1, 31,0);
    tracep->declBus(c+18,"trap_bus_i", false,-1, 2,0);
    tracep->declQuad(c+36,"csr_mstatus_clint_i", false,-1, 63,0);
    tracep->declQuad(c+28,"csr_mepc_clint_i", false,-1, 63,0);
    tracep->declQuad(c+30,"csr_mcause_clint_i", false,-1, 63,0);
    tracep->declQuad(c+32,"csr_mtval_clint_i", false,-1, 63,0);
    tracep->declQuad(c+34,"csr_mtvec_clint_i", false,-1, 63,0);
    tracep->declQuad(c+192,"csr_mstatus_clint_o", false,-1, 63,0);
    tracep->declQuad(c+1,"csr_mepc_clint_o", false,-1, 63,0);
    tracep->declQuad(c+188,"csr_mcause_clint_o", false,-1, 63,0);
    tracep->declQuad(c+25,"csr_mtval_clint_o", false,-1, 63,0);
    tracep->declQuad(c+190,"csr_mtvec_clint_o", false,-1, 63,0);
    tracep->declBit(c+195,"csr_mstatus_clint_o_valid", false,-1);
    tracep->declBit(c+27,"csr_mepc_clint_o_valid", false,-1);
    tracep->declBit(c+27,"csr_mcause_clint_o_valid", false,-1);
    tracep->declBit(c+27,"csr_mtval_clint_o_valid", false,-1);
    tracep->declBit(c+194,"csr_mtvec_clint_o_valid", false,-1);
    tracep->declQuad(c+48,"clint_pc_o", false,-1, 63,0);
    tracep->declBit(c+50,"clint_pc_valid_o", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_dcode ");
    tracep->declBus(c+3,"inst_data", false,-1, 31,0);
    tracep->declBus(c+4,"rs1_idx", false,-1, 4,0);
    tracep->declBus(c+5,"rs2_idx", false,-1, 4,0);
    tracep->declBus(c+6,"rd_idx", false,-1, 4,0);
    tracep->declQuad(c+8,"imm_data", false,-1, 63,0);
    tracep->declQuad(c+10,"immCSR", false,-1, 63,0);
    tracep->declBit(c+12,"isNeedimmCSR", false,-1);
    tracep->declBus(c+7,"csr_idx", false,-1, 11,0);
    tracep->declBus(c+13,"alu_op", false,-1, 5,0);
    tracep->declBus(c+14,"mem_op", false,-1, 3,0);
    tracep->declBus(c+15,"exc_op", false,-1, 4,0);
    tracep->declBus(c+16,"pc_op", false,-1, 3,0);
    tracep->declBus(c+17,"csr_op", false,-1, 2,0);
    tracep->declBus(c+18,"trap_bus_o", false,-1, 2,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_execute ");
    tracep->declQuad(c+1,"pc", false,-1, 63,0);
    tracep->declBus(c+6,"rd_idx", false,-1, 4,0);
    tracep->declQuad(c+19,"rs1_data", false,-1, 63,0);
    tracep->declQuad(c+21,"rs2_data", false,-1, 63,0);
    tracep->declQuad(c+8,"imm_data", false,-1, 63,0);
    tracep->declQuad(c+38,"csr_data", false,-1, 63,0);
    tracep->declQuad(c+10,"imm_CSR", false,-1, 63,0);
    tracep->declBit(c+12,"isNeedimmCSR", false,-1);
    tracep->declBus(c+13,"alu_op", false,-1, 5,0);
    tracep->declBus(c+14,"mem_op", false,-1, 3,0);
    tracep->declBus(c+15,"exc_op", false,-1, 4,0);
    tracep->declBus(c+17,"csr_op", false,-1, 2,0);
    tracep->declQuad(c+43,"exc_alu_out", false,-1, 63,0);
    tracep->declQuad(c+41,"exc_csr_out", false,-1, 63,0);
    tracep->declBit(c+40,"exc_csr_valid", false,-1);
    tracep->pushNamePrefix("u_alu ");
    tracep->declQuad(c+51,"alu_a_i", false,-1, 63,0);
    tracep->declQuad(c+53,"alu_b_i", false,-1, 63,0);
    tracep->declBus(c+13,"alu_op_i", false,-1, 5,0);
    tracep->declQuad(c+55,"alu_out", false,-1, 63,0);
    tracep->declBit(c+57,"compare_out", false,-1);
    tracep->pushNamePrefix("u_alu_div_top ");
    tracep->declBit(c+58,"issigned", false,-1);
    tracep->declBit(c+59,"isdivw", false,-1);
    tracep->declQuad(c+51,"sr1_data", false,-1, 63,0);
    tracep->declQuad(c+53,"sr2_data", false,-1, 63,0);
    tracep->declQuad(c+60,"div_result", false,-1, 63,0);
    tracep->declQuad(c+62,"rem_result", false,-1, 63,0);
    tracep->declQuad(c+51,"sr1_64_signed", false,-1, 63,0);
    tracep->declQuad(c+53,"sr2_64_signed", false,-1, 63,0);
    tracep->declQuad(c+64,"div64_signed", false,-1, 63,0);
    tracep->declQuad(c+66,"rem64_signed", false,-1, 63,0);
    tracep->declQuad(c+68,"div64_unsigned", false,-1, 63,0);
    tracep->declQuad(c+70,"rem64_unsigned", false,-1, 63,0);
    tracep->declQuad(c+72,"div64_result", false,-1, 63,0);
    tracep->declQuad(c+74,"rem64_result", false,-1, 63,0);
    tracep->declBus(c+76,"sr1_32_signed", false,-1, 31,0);
    tracep->declBus(c+77,"sr2_32_signed", false,-1, 31,0);
    tracep->declBus(c+78,"div32_signed", false,-1, 31,0);
    tracep->declBus(c+79,"rem32_signed", false,-1, 31,0);
    tracep->declBus(c+80,"div32_unsigned", false,-1, 31,0);
    tracep->declBus(c+81,"rem32_unsigned", false,-1, 31,0);
    tracep->declBus(c+82,"div32_result", false,-1, 31,0);
    tracep->declBus(c+83,"rem32_result", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_alu_mul_top ");
    tracep->declBit(c+84,"is_sr1_signed", false,-1);
    tracep->declBit(c+85,"is_sr2_signed", false,-1);
    tracep->declQuad(c+51,"sr1_data", false,-1, 63,0);
    tracep->declQuad(c+53,"sr2_data", false,-1, 63,0);
    tracep->declArray(c+86,"mul_result", false,-1, 127,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_alu_shift ");
    tracep->declBit(c+90,"shift_sra", false,-1);
    tracep->declBit(c+91,"shift_srl", false,-1);
    tracep->declBit(c+92,"shift_sll", false,-1);
    tracep->declBit(c+93,"isshift32", false,-1);
    tracep->declQuad(c+51,"shift_num", false,-1, 63,0);
    tracep->declBus(c+94,"shift_count", false,-1, 5,0);
    tracep->declQuad(c+95,"shift_out", false,-1, 63,0);
    tracep->pushNamePrefix("u_Vectorinvert1 ");
    tracep->declBus(c+196,"DATA_LEN", false,-1, 31,0);
    tracep->declQuad(c+97,"in", false,-1, 63,0);
    tracep->declQuad(c+99,"out", false,-1, 63,0);
    tracep->declBus(c+197,"i", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_Vectorinvert2 ");
    tracep->declBus(c+196,"DATA_LEN", false,-1, 31,0);
    tracep->declQuad(c+101,"in", false,-1, 63,0);
    tracep->declQuad(c+103,"out", false,-1, 63,0);
    tracep->declBus(c+197,"i", false,-1, 31,0);
    tracep->popNamePrefix(3);
    tracep->pushNamePrefix("u_execute_csr ");
    tracep->declQuad(c+10,"imm_CSR_i", false,-1, 63,0);
    tracep->declBit(c+12,"isNeedimmCSR_i", false,-1);
    tracep->declQuad(c+19,"rs1_data_i", false,-1, 63,0);
    tracep->declQuad(c+38,"csr_data_i", false,-1, 63,0);
    tracep->declBus(c+17,"csr_op_i", false,-1, 2,0);
    tracep->declQuad(c+41,"csr_exe_result", false,-1, 63,0);
    tracep->declBit(c+40,"csr_exe_valid", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("u_fetch ");
    tracep->declQuad(c+1,"inst_addr", false,-1, 63,0);
    tracep->declBus(c+3,"inst_data", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_memory ");
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+1,"pc", false,-1, 63,0);
    tracep->declBus(c+6,"rd_idx", false,-1, 4,0);
    tracep->declQuad(c+19,"rs1_data", false,-1, 63,0);
    tracep->declQuad(c+21,"rs2_data", false,-1, 63,0);
    tracep->declQuad(c+8,"imm_data", false,-1, 63,0);
    tracep->declBus(c+14,"mem_op", false,-1, 3,0);
    tracep->declQuad(c+43,"exc_in", false,-1, 63,0);
    tracep->declQuad(c+45,"mem_out", false,-1, 63,0);
    tracep->declBit(c+47,"isloadEnable", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_pc ");
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declBus(c+16,"pc_op", false,-1, 3,0);
    tracep->declQuad(c+19,"rs1_data", false,-1, 63,0);
    tracep->declQuad(c+8,"imm_data", false,-1, 63,0);
    tracep->declQuad(c+43,"execute_data", false,-1, 63,0);
    tracep->declQuad(c+48,"clint_pc_i", false,-1, 63,0);
    tracep->declBit(c+50,"clint_pc_valid_i", false,-1);
    tracep->declQuad(c+1,"pc_out", false,-1, 63,0);
    tracep->pushNamePrefix("u_regpc ");
    tracep->declBus(c+196,"WIDTH", false,-1, 31,0);
    tracep->declQuad(c+198,"RESET_VAL", false,-1, 63,0);
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+105,"din", false,-1, 63,0);
    tracep->declQuad(c+1,"dout", false,-1, 63,0);
    tracep->declBit(c+200,"wen", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("u_rv64_csr_regfile ");
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+192,"csr_mstatus_i", false,-1, 63,0);
    tracep->declQuad(c+1,"csr_mepc_i", false,-1, 63,0);
    tracep->declQuad(c+188,"csr_mcause_i", false,-1, 63,0);
    tracep->declQuad(c+25,"csr_mtval_i", false,-1, 63,0);
    tracep->declQuad(c+190,"csr_mtvec_i", false,-1, 63,0);
    tracep->declBit(c+195,"csr_mstatus_i_en", false,-1);
    tracep->declBit(c+27,"csr_mepc_i_en", false,-1);
    tracep->declBit(c+27,"csr_mcause_i_en", false,-1);
    tracep->declBit(c+27,"csr_mtval_i_en", false,-1);
    tracep->declBit(c+194,"csr_mtvec_i_en", false,-1);
    tracep->declQuad(c+36,"csr_mstatus_o", false,-1, 63,0);
    tracep->declQuad(c+28,"csr_mepc_o", false,-1, 63,0);
    tracep->declQuad(c+30,"csr_mcause_o", false,-1, 63,0);
    tracep->declQuad(c+32,"csr_mtval_o", false,-1, 63,0);
    tracep->declQuad(c+34,"csr_mtvec_o", false,-1, 63,0);
    tracep->declBus(c+7,"csr_readaddr", false,-1, 11,0);
    tracep->declQuad(c+38,"csr_readdata", false,-1, 63,0);
    tracep->declBus(c+7,"csr_writeaddr", false,-1, 11,0);
    tracep->declBit(c+40,"write_enable", false,-1);
    tracep->declQuad(c+41,"csr_writedata", false,-1, 63,0);
    tracep->pushNamePrefix("u_csr_mcause ");
    tracep->declBus(c+196,"WIDTH", false,-1, 31,0);
    tracep->declQuad(c+201,"RESET_VAL", false,-1, 63,0);
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+107,"din", false,-1, 63,0);
    tracep->declQuad(c+30,"dout", false,-1, 63,0);
    tracep->declBit(c+109,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_csr_mepc ");
    tracep->declBus(c+196,"WIDTH", false,-1, 31,0);
    tracep->declQuad(c+201,"RESET_VAL", false,-1, 63,0);
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+110,"din", false,-1, 63,0);
    tracep->declQuad(c+28,"dout", false,-1, 63,0);
    tracep->declBit(c+112,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_csr_mstatus ");
    tracep->declBus(c+196,"WIDTH", false,-1, 31,0);
    tracep->declQuad(c+203,"RESET_VAL", false,-1, 63,0);
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+113,"din", false,-1, 63,0);
    tracep->declQuad(c+36,"dout", false,-1, 63,0);
    tracep->declBit(c+115,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_csr_mtval ");
    tracep->declBus(c+196,"WIDTH", false,-1, 31,0);
    tracep->declQuad(c+201,"RESET_VAL", false,-1, 63,0);
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+116,"din", false,-1, 63,0);
    tracep->declQuad(c+32,"dout", false,-1, 63,0);
    tracep->declBit(c+118,"wen", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_csr_mtvec ");
    tracep->declBus(c+196,"WIDTH", false,-1, 31,0);
    tracep->declQuad(c+201,"RESET_VAL", false,-1, 63,0);
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBit(c+187,"rst", false,-1);
    tracep->declQuad(c+119,"din", false,-1, 63,0);
    tracep->declQuad(c+34,"dout", false,-1, 63,0);
    tracep->declBit(c+121,"wen", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("u_rv64reg ");
    tracep->declBit(c+186,"clk", false,-1);
    tracep->declBus(c+4,"rs1_idx", false,-1, 4,0);
    tracep->declBus(c+5,"rs2_idx", false,-1, 4,0);
    tracep->declQuad(c+19,"rs1_data", false,-1, 63,0);
    tracep->declQuad(c+21,"rs2_data", false,-1, 63,0);
    tracep->declBus(c+6,"write_idx", false,-1, 4,0);
    tracep->declQuad(c+23,"write_data", false,-1, 63,0);
    tracep->declBit(c+200,"wen", false,-1);
    for (int i = 0; i < 32; ++i) {
        tracep->declQuad(c+122+i*2,"rf", true,(i+0), 63,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_writeback ");
    tracep->declQuad(c+43,"exc_data_in", false,-1, 63,0);
    tracep->declQuad(c+45,"mem_data_in", false,-1, 63,0);
    tracep->declBit(c+47,"isloadEnable", false,-1);
    tracep->declQuad(c+23,"wb_data", false,-1, 63,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf, nullptr);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf, nullptr);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullQData(oldp+1,(vlSelf->top__DOT__u_pc__DOT___pc_current),64);
    bufp->fullIData(oldp+3,((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data)),32);
    bufp->fullCData(oldp+4,(((((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                 | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
                                | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                               | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch)) 
                              & (~ (IData)(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR)))
                              ? (0x1fU & (IData)((vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                  >> 0xfU)))
                              : 0U)),5);
    bufp->fullCData(oldp+5,(((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                               | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                              | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch))
                              ? (0x1fU & (IData)((vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                  >> 0x14U)))
                              : 0U)),5);
    bufp->fullCData(oldp+6,(vlSelf->top__DOT__u_dcode__DOT___rd_idx),5);
    bufp->fullSData(oldp+7,(vlSelf->top__DOT__u_dcode__DOT___csr_idx),12);
    bufp->fullQData(oldp+8,(vlSelf->top__DOT__u_dcode__DOT___imm_data),64);
    bufp->fullQData(oldp+10,((QData)((IData)((0x1fU 
                                              & (IData)(
                                                        (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                         >> 0xfU)))))),64);
    bufp->fullBit(oldp+12,(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR));
    bufp->fullCData(oldp+13,(vlSelf->top__DOT__u_dcode__DOT___alu_op),6);
    bufp->fullCData(oldp+14,(vlSelf->top__DOT__u_dcode__DOT___mem_op),4);
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__u_dcode__DOT___exc_op),5);
    bufp->fullCData(oldp+16,(vlSelf->top__DOT__u_dcode__DOT___pc_op),4);
    bufp->fullCData(oldp+17,(vlSelf->top__DOT__u_dcode__DOT___csr_op),3);
    bufp->fullCData(oldp+18,(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus),3);
    bufp->fullQData(oldp+19,(vlSelf->top__DOT__rs1_data),64);
    bufp->fullQData(oldp+21,(vlSelf->top__DOT__rs2_data),64);
    bufp->fullQData(oldp+23,((((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                               | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))
                               ? ((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
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
                                       : 0ULL)) : vlSelf->top__DOT__exc_out)),64);
    bufp->fullQData(oldp+25,((QData)((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data))),64);
    bufp->fullBit(oldp+27,((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))));
    bufp->fullQData(oldp+28,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q),64);
    bufp->fullQData(oldp+30,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_q),64);
    bufp->fullQData(oldp+32,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_q),64);
    bufp->fullQData(oldp+34,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q),64);
    bufp->fullQData(oldp+36,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_q),64);
    bufp->fullQData(oldp+38,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata),64);
    bufp->fullBit(oldp+40,(vlSelf->top__DOT__u_execute__DOT___csr_exe_valid));
    bufp->fullQData(oldp+41,(vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result),64);
    bufp->fullQData(oldp+43,(vlSelf->top__DOT__exc_out),64);
    bufp->fullQData(oldp+45,(((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
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
    bufp->fullBit(oldp+47,(((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                            | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))));
    bufp->fullQData(oldp+48,((((- (QData)((IData)((1U 
                                                   & ((IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus) 
                                                      >> 2U))))) 
                               & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q) 
                              | ((- (QData)((IData)(
                                                    (1U 
                                                     & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))))) 
                                 & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q))),64);
    bufp->fullBit(oldp+50,((IData)((0U != (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus)))));
    bufp->fullQData(oldp+51,(vlSelf->top__DOT__u_execute__DOT___alu_in1),64);
    bufp->fullQData(oldp+53,(vlSelf->top__DOT__u_execute__DOT___alu_in2),64);
    bufp->fullQData(oldp+55,(vlSelf->top__DOT__u_execute__DOT___alu_out),64);
    bufp->fullBit(oldp+57,(((((((((0xcU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
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
    bufp->fullBit(oldp+58,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed));
    bufp->fullBit(oldp+59,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32));
    bufp->fullQData(oldp+60,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                               ? (QData)((IData)(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                   ? 
                                                  VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                   : 
                                                  VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                               : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                   ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                   : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
    bufp->fullQData(oldp+62,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                               ? (QData)((IData)(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                   ? 
                                                  VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                   : 
                                                  VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                               : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                   ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                   : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
    bufp->fullQData(oldp+64,(VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
    bufp->fullQData(oldp+66,(VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
    bufp->fullQData(oldp+68,(VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
    bufp->fullQData(oldp+70,(VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
    bufp->fullQData(oldp+72,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                               ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                               : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
    bufp->fullQData(oldp+74,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                               ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                               : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
    bufp->fullIData(oldp+76,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1)),32);
    bufp->fullIData(oldp+77,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)),32);
    bufp->fullIData(oldp+78,(VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
    bufp->fullIData(oldp+79,(VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
    bufp->fullIData(oldp+80,(VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
    bufp->fullIData(oldp+81,(VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
    bufp->fullIData(oldp+82,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                               ? VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                               : VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
    bufp->fullIData(oldp+83,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                               ? VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                               : VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
    bufp->fullBit(oldp+84,(((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                              | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                             | (0x16U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                            | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
    bufp->fullBit(oldp+85,((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                             | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                            | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
    bufp->fullWData(oldp+86,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result),128);
    bufp->fullBit(oldp+90,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra));
    bufp->fullBit(oldp+91,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl));
    bufp->fullBit(oldp+92,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll));
    bufp->fullBit(oldp+93,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32));
    bufp->fullCData(oldp+94,((0x3fU & (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),6);
    bufp->fullQData(oldp+95,(((((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))) 
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
                                              >> (0x3fU 
                                                  & ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32)
                                                      ? 
                                                     ((IData)(0x20U) 
                                                      + (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))
                                                      : (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2))))))))) 
                              | ((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll))) 
                                 & vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res))),64);
    bufp->fullQData(oldp+97,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num),64);
    bufp->fullQData(oldp+99,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv),64);
    bufp->fullQData(oldp+101,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res),64);
    bufp->fullQData(oldp+103,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res),64);
    bufp->fullQData(oldp+105,((((((- (QData)((IData)(
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
    bufp->fullQData(oldp+107,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                ? 0xbULL : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
    bufp->fullBit(oldp+109,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en));
    bufp->fullQData(oldp+110,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                ? vlSelf->top__DOT__u_pc__DOT___pc_current
                                : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
    bufp->fullBit(oldp+112,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en));
    bufp->fullQData(oldp+113,(((IData)(vlSelf->top__DOT__csr_mstatus_i_en)
                                ? vlSelf->top__DOT__csr_mstatus_i
                                : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
    bufp->fullBit(oldp+115,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_en));
    bufp->fullQData(oldp+116,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                ? (QData)((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data))
                                : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
    bufp->fullBit(oldp+118,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en));
    bufp->fullQData(oldp+119,(((IData)(vlSelf->top__DOT__csr_mtvec_i_en)
                                ? vlSelf->top__DOT__csr_mtvec_i
                                : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
    bufp->fullBit(oldp+121,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en));
    bufp->fullQData(oldp+122,(vlSelf->top__DOT__u_rv64reg__DOT__rf[0]),64);
    bufp->fullQData(oldp+124,(vlSelf->top__DOT__u_rv64reg__DOT__rf[1]),64);
    bufp->fullQData(oldp+126,(vlSelf->top__DOT__u_rv64reg__DOT__rf[2]),64);
    bufp->fullQData(oldp+128,(vlSelf->top__DOT__u_rv64reg__DOT__rf[3]),64);
    bufp->fullQData(oldp+130,(vlSelf->top__DOT__u_rv64reg__DOT__rf[4]),64);
    bufp->fullQData(oldp+132,(vlSelf->top__DOT__u_rv64reg__DOT__rf[5]),64);
    bufp->fullQData(oldp+134,(vlSelf->top__DOT__u_rv64reg__DOT__rf[6]),64);
    bufp->fullQData(oldp+136,(vlSelf->top__DOT__u_rv64reg__DOT__rf[7]),64);
    bufp->fullQData(oldp+138,(vlSelf->top__DOT__u_rv64reg__DOT__rf[8]),64);
    bufp->fullQData(oldp+140,(vlSelf->top__DOT__u_rv64reg__DOT__rf[9]),64);
    bufp->fullQData(oldp+142,(vlSelf->top__DOT__u_rv64reg__DOT__rf[10]),64);
    bufp->fullQData(oldp+144,(vlSelf->top__DOT__u_rv64reg__DOT__rf[11]),64);
    bufp->fullQData(oldp+146,(vlSelf->top__DOT__u_rv64reg__DOT__rf[12]),64);
    bufp->fullQData(oldp+148,(vlSelf->top__DOT__u_rv64reg__DOT__rf[13]),64);
    bufp->fullQData(oldp+150,(vlSelf->top__DOT__u_rv64reg__DOT__rf[14]),64);
    bufp->fullQData(oldp+152,(vlSelf->top__DOT__u_rv64reg__DOT__rf[15]),64);
    bufp->fullQData(oldp+154,(vlSelf->top__DOT__u_rv64reg__DOT__rf[16]),64);
    bufp->fullQData(oldp+156,(vlSelf->top__DOT__u_rv64reg__DOT__rf[17]),64);
    bufp->fullQData(oldp+158,(vlSelf->top__DOT__u_rv64reg__DOT__rf[18]),64);
    bufp->fullQData(oldp+160,(vlSelf->top__DOT__u_rv64reg__DOT__rf[19]),64);
    bufp->fullQData(oldp+162,(vlSelf->top__DOT__u_rv64reg__DOT__rf[20]),64);
    bufp->fullQData(oldp+164,(vlSelf->top__DOT__u_rv64reg__DOT__rf[21]),64);
    bufp->fullQData(oldp+166,(vlSelf->top__DOT__u_rv64reg__DOT__rf[22]),64);
    bufp->fullQData(oldp+168,(vlSelf->top__DOT__u_rv64reg__DOT__rf[23]),64);
    bufp->fullQData(oldp+170,(vlSelf->top__DOT__u_rv64reg__DOT__rf[24]),64);
    bufp->fullQData(oldp+172,(vlSelf->top__DOT__u_rv64reg__DOT__rf[25]),64);
    bufp->fullQData(oldp+174,(vlSelf->top__DOT__u_rv64reg__DOT__rf[26]),64);
    bufp->fullQData(oldp+176,(vlSelf->top__DOT__u_rv64reg__DOT__rf[27]),64);
    bufp->fullQData(oldp+178,(vlSelf->top__DOT__u_rv64reg__DOT__rf[28]),64);
    bufp->fullQData(oldp+180,(vlSelf->top__DOT__u_rv64reg__DOT__rf[29]),64);
    bufp->fullQData(oldp+182,(vlSelf->top__DOT__u_rv64reg__DOT__rf[30]),64);
    bufp->fullQData(oldp+184,(vlSelf->top__DOT__u_rv64reg__DOT__rf[31]),64);
    bufp->fullBit(oldp+186,(vlSelf->clk));
    bufp->fullBit(oldp+187,(vlSelf->rst));
    bufp->fullQData(oldp+188,(0xbULL),64);
    bufp->fullQData(oldp+190,(vlSelf->top__DOT__csr_mtvec_i),64);
    bufp->fullQData(oldp+192,(vlSelf->top__DOT__csr_mstatus_i),64);
    bufp->fullBit(oldp+194,(vlSelf->top__DOT__csr_mtvec_i_en));
    bufp->fullBit(oldp+195,(vlSelf->top__DOT__csr_mstatus_i_en));
    bufp->fullIData(oldp+196,(0x40U),32);
    bufp->fullIData(oldp+197,(0x40U),32);
    bufp->fullQData(oldp+198,(0x80000000ULL),64);
    bufp->fullBit(oldp+200,(1U));
    bufp->fullQData(oldp+201,(0ULL),64);
    bufp->fullQData(oldp+203,(0xa00001800ULL),64);
}
