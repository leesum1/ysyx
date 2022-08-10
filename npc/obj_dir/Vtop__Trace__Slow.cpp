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
        tracep->declBit(c+186,"clk", false,-1);
        tracep->declBit(c+187,"rst", false,-1);
        tracep->declBit(c+186,"top clk", false,-1);
        tracep->declBit(c+187,"top rst", false,-1);
        tracep->declQuad(c+1,"top pc", false,-1, 63,0);
        tracep->declBus(c+3,"top inst_data", false,-1, 31,0);
        tracep->declBus(c+4,"top rs1_idx", false,-1, 4,0);
        tracep->declBus(c+5,"top rs2_idx", false,-1, 4,0);
        tracep->declBus(c+6,"top rd_idx", false,-1, 4,0);
        tracep->declBus(c+7,"top csr_idx", false,-1, 11,0);
        tracep->declQuad(c+8,"top imm_data", false,-1, 63,0);
        tracep->declQuad(c+10,"top imm_csr", false,-1, 63,0);
        tracep->declBit(c+12,"top isNeedimmCSR", false,-1);
        tracep->declBus(c+13,"top alu_op", false,-1, 5,0);
        tracep->declBus(c+14,"top mem_op", false,-1, 3,0);
        tracep->declBus(c+15,"top exc_op", false,-1, 4,0);
        tracep->declBus(c+16,"top pc_op", false,-1, 3,0);
        tracep->declBus(c+17,"top csr_op", false,-1, 2,0);
        tracep->declBus(c+18,"top trap_bus", false,-1, 2,0);
        tracep->declQuad(c+19,"top rs1_data", false,-1, 63,0);
        tracep->declQuad(c+21,"top rs2_data", false,-1, 63,0);
        tracep->declQuad(c+23,"top w_data", false,-1, 63,0);
        tracep->declBus(c+6,"top w_idx", false,-1, 4,0);
        tracep->declQuad(c+1,"top csr_mepc_i", false,-1, 63,0);
        tracep->declQuad(c+188,"top csr_mcause_i", false,-1, 63,0);
        tracep->declQuad(c+25,"top csr_mtval_i", false,-1, 63,0);
        tracep->declQuad(c+190,"top csr_mtvec_i", false,-1, 63,0);
        tracep->declQuad(c+192,"top csr_mstatus_i", false,-1, 63,0);
        tracep->declBit(c+27,"top csr_mepc_i_en", false,-1);
        tracep->declBit(c+27,"top csr_mcause_i_en", false,-1);
        tracep->declBit(c+27,"top csr_mtval_i_en", false,-1);
        tracep->declBit(c+194,"top csr_mtvec_i_en", false,-1);
        tracep->declBit(c+195,"top csr_mstatus_i_en", false,-1);
        tracep->declQuad(c+28,"top csr_mepc_o", false,-1, 63,0);
        tracep->declQuad(c+30,"top csr_mcause_o", false,-1, 63,0);
        tracep->declQuad(c+32,"top csr_mtval_o", false,-1, 63,0);
        tracep->declQuad(c+34,"top csr_mtvec_o", false,-1, 63,0);
        tracep->declQuad(c+36,"top csr_mstatus_o", false,-1, 63,0);
        tracep->declBus(c+7,"top csr_readaddr", false,-1, 11,0);
        tracep->declQuad(c+38,"top csr_readdata", false,-1, 63,0);
        tracep->declBus(c+7,"top csr_writeaddr", false,-1, 11,0);
        tracep->declBit(c+40,"top write_enable", false,-1);
        tracep->declQuad(c+41,"top csr_writedata", false,-1, 63,0);
        tracep->declQuad(c+43,"top exc_out", false,-1, 63,0);
        tracep->declQuad(c+41,"top exc_csr_out", false,-1, 63,0);
        tracep->declBit(c+40,"top exc_csr_valid", false,-1);
        tracep->declQuad(c+45,"top mem_out", false,-1, 63,0);
        tracep->declBit(c+47,"top isloadEnable", false,-1);
        tracep->declQuad(c+23,"top wb_data", false,-1, 63,0);
        tracep->declQuad(c+48,"top clint_pc", false,-1, 63,0);
        tracep->declBit(c+50,"top clint_pc_valid", false,-1);
        tracep->declBit(c+186,"top u_pc clk", false,-1);
        tracep->declBit(c+187,"top u_pc rst", false,-1);
        tracep->declBus(c+16,"top u_pc pc_op", false,-1, 3,0);
        tracep->declQuad(c+19,"top u_pc rs1_data", false,-1, 63,0);
        tracep->declQuad(c+8,"top u_pc imm_data", false,-1, 63,0);
        tracep->declQuad(c+43,"top u_pc execute_data", false,-1, 63,0);
        tracep->declQuad(c+48,"top u_pc clint_pc_i", false,-1, 63,0);
        tracep->declBit(c+50,"top u_pc clint_pc_valid_i", false,-1);
        tracep->declQuad(c+1,"top u_pc pc_out", false,-1, 63,0);
        tracep->declBus(c+196,"top u_pc u_regpc WIDTH", false,-1, 31,0);
        tracep->declQuad(c+197,"top u_pc u_regpc RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+186,"top u_pc u_regpc clk", false,-1);
        tracep->declBit(c+187,"top u_pc u_regpc rst", false,-1);
        tracep->declQuad(c+51,"top u_pc u_regpc din", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_pc u_regpc dout", false,-1, 63,0);
        tracep->declBit(c+199,"top u_pc u_regpc wen", false,-1);
        tracep->declQuad(c+1,"top u_fetch inst_addr", false,-1, 63,0);
        tracep->declBus(c+3,"top u_fetch inst_data", false,-1, 31,0);
        tracep->declBus(c+3,"top u_dcode inst_data", false,-1, 31,0);
        tracep->declBus(c+4,"top u_dcode rs1_idx", false,-1, 4,0);
        tracep->declBus(c+5,"top u_dcode rs2_idx", false,-1, 4,0);
        tracep->declBus(c+6,"top u_dcode rd_idx", false,-1, 4,0);
        tracep->declQuad(c+8,"top u_dcode imm_data", false,-1, 63,0);
        tracep->declQuad(c+10,"top u_dcode immCSR", false,-1, 63,0);
        tracep->declBit(c+12,"top u_dcode isNeedimmCSR", false,-1);
        tracep->declBus(c+7,"top u_dcode csr_idx", false,-1, 11,0);
        tracep->declBus(c+13,"top u_dcode alu_op", false,-1, 5,0);
        tracep->declBus(c+14,"top u_dcode mem_op", false,-1, 3,0);
        tracep->declBus(c+15,"top u_dcode exc_op", false,-1, 4,0);
        tracep->declBus(c+16,"top u_dcode pc_op", false,-1, 3,0);
        tracep->declBus(c+17,"top u_dcode csr_op", false,-1, 2,0);
        tracep->declBus(c+18,"top u_dcode trap_bus_o", false,-1, 2,0);
        tracep->declBit(c+186,"top u_rv64reg clk", false,-1);
        tracep->declBus(c+4,"top u_rv64reg rs1_idx", false,-1, 4,0);
        tracep->declBus(c+5,"top u_rv64reg rs2_idx", false,-1, 4,0);
        tracep->declQuad(c+19,"top u_rv64reg rs1_data", false,-1, 63,0);
        tracep->declQuad(c+21,"top u_rv64reg rs2_data", false,-1, 63,0);
        tracep->declBus(c+6,"top u_rv64reg write_idx", false,-1, 4,0);
        tracep->declQuad(c+23,"top u_rv64reg write_data", false,-1, 63,0);
        tracep->declBit(c+199,"top u_rv64reg wen", false,-1);
        {int i; for (i=0; i<32; i++) {
                tracep->declQuad(c+53+i*2,"top u_rv64reg rf", true,(i+0), 63,0);}}
        tracep->declBit(c+186,"top u_rv64_csr_regfile clk", false,-1);
        tracep->declBit(c+187,"top u_rv64_csr_regfile rst", false,-1);
        tracep->declQuad(c+192,"top u_rv64_csr_regfile csr_mstatus_i", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_rv64_csr_regfile csr_mepc_i", false,-1, 63,0);
        tracep->declQuad(c+188,"top u_rv64_csr_regfile csr_mcause_i", false,-1, 63,0);
        tracep->declQuad(c+25,"top u_rv64_csr_regfile csr_mtval_i", false,-1, 63,0);
        tracep->declQuad(c+190,"top u_rv64_csr_regfile csr_mtvec_i", false,-1, 63,0);
        tracep->declBit(c+195,"top u_rv64_csr_regfile csr_mstatus_i_en", false,-1);
        tracep->declBit(c+27,"top u_rv64_csr_regfile csr_mepc_i_en", false,-1);
        tracep->declBit(c+27,"top u_rv64_csr_regfile csr_mcause_i_en", false,-1);
        tracep->declBit(c+27,"top u_rv64_csr_regfile csr_mtval_i_en", false,-1);
        tracep->declBit(c+194,"top u_rv64_csr_regfile csr_mtvec_i_en", false,-1);
        tracep->declQuad(c+36,"top u_rv64_csr_regfile csr_mstatus_o", false,-1, 63,0);
        tracep->declQuad(c+28,"top u_rv64_csr_regfile csr_mepc_o", false,-1, 63,0);
        tracep->declQuad(c+30,"top u_rv64_csr_regfile csr_mcause_o", false,-1, 63,0);
        tracep->declQuad(c+32,"top u_rv64_csr_regfile csr_mtval_o", false,-1, 63,0);
        tracep->declQuad(c+34,"top u_rv64_csr_regfile csr_mtvec_o", false,-1, 63,0);
        tracep->declBus(c+7,"top u_rv64_csr_regfile csr_readaddr", false,-1, 11,0);
        tracep->declQuad(c+38,"top u_rv64_csr_regfile csr_readdata", false,-1, 63,0);
        tracep->declBus(c+7,"top u_rv64_csr_regfile csr_writeaddr", false,-1, 11,0);
        tracep->declBit(c+40,"top u_rv64_csr_regfile write_enable", false,-1);
        tracep->declQuad(c+41,"top u_rv64_csr_regfile csr_writedata", false,-1, 63,0);
        tracep->declBus(c+196,"top u_rv64_csr_regfile u_csr_mstatus WIDTH", false,-1, 31,0);
        tracep->declQuad(c+200,"top u_rv64_csr_regfile u_csr_mstatus RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+186,"top u_rv64_csr_regfile u_csr_mstatus clk", false,-1);
        tracep->declBit(c+187,"top u_rv64_csr_regfile u_csr_mstatus rst", false,-1);
        tracep->declQuad(c+117,"top u_rv64_csr_regfile u_csr_mstatus din", false,-1, 63,0);
        tracep->declQuad(c+36,"top u_rv64_csr_regfile u_csr_mstatus dout", false,-1, 63,0);
        tracep->declBit(c+119,"top u_rv64_csr_regfile u_csr_mstatus wen", false,-1);
        tracep->declBus(c+196,"top u_rv64_csr_regfile u_csr_mepc WIDTH", false,-1, 31,0);
        tracep->declQuad(c+202,"top u_rv64_csr_regfile u_csr_mepc RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+186,"top u_rv64_csr_regfile u_csr_mepc clk", false,-1);
        tracep->declBit(c+187,"top u_rv64_csr_regfile u_csr_mepc rst", false,-1);
        tracep->declQuad(c+120,"top u_rv64_csr_regfile u_csr_mepc din", false,-1, 63,0);
        tracep->declQuad(c+28,"top u_rv64_csr_regfile u_csr_mepc dout", false,-1, 63,0);
        tracep->declBit(c+122,"top u_rv64_csr_regfile u_csr_mepc wen", false,-1);
        tracep->declBus(c+196,"top u_rv64_csr_regfile u_csr_mcause WIDTH", false,-1, 31,0);
        tracep->declQuad(c+202,"top u_rv64_csr_regfile u_csr_mcause RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+186,"top u_rv64_csr_regfile u_csr_mcause clk", false,-1);
        tracep->declBit(c+187,"top u_rv64_csr_regfile u_csr_mcause rst", false,-1);
        tracep->declQuad(c+123,"top u_rv64_csr_regfile u_csr_mcause din", false,-1, 63,0);
        tracep->declQuad(c+30,"top u_rv64_csr_regfile u_csr_mcause dout", false,-1, 63,0);
        tracep->declBit(c+125,"top u_rv64_csr_regfile u_csr_mcause wen", false,-1);
        tracep->declBus(c+196,"top u_rv64_csr_regfile u_csr_mtval WIDTH", false,-1, 31,0);
        tracep->declQuad(c+202,"top u_rv64_csr_regfile u_csr_mtval RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+186,"top u_rv64_csr_regfile u_csr_mtval clk", false,-1);
        tracep->declBit(c+187,"top u_rv64_csr_regfile u_csr_mtval rst", false,-1);
        tracep->declQuad(c+126,"top u_rv64_csr_regfile u_csr_mtval din", false,-1, 63,0);
        tracep->declQuad(c+32,"top u_rv64_csr_regfile u_csr_mtval dout", false,-1, 63,0);
        tracep->declBit(c+128,"top u_rv64_csr_regfile u_csr_mtval wen", false,-1);
        tracep->declBus(c+196,"top u_rv64_csr_regfile u_csr_mtvec WIDTH", false,-1, 31,0);
        tracep->declQuad(c+202,"top u_rv64_csr_regfile u_csr_mtvec RESET_VAL", false,-1, 63,0);
        tracep->declBit(c+186,"top u_rv64_csr_regfile u_csr_mtvec clk", false,-1);
        tracep->declBit(c+187,"top u_rv64_csr_regfile u_csr_mtvec rst", false,-1);
        tracep->declQuad(c+129,"top u_rv64_csr_regfile u_csr_mtvec din", false,-1, 63,0);
        tracep->declQuad(c+34,"top u_rv64_csr_regfile u_csr_mtvec dout", false,-1, 63,0);
        tracep->declBit(c+131,"top u_rv64_csr_regfile u_csr_mtvec wen", false,-1);
        tracep->declQuad(c+1,"top u_execute pc", false,-1, 63,0);
        tracep->declBus(c+6,"top u_execute rd_idx", false,-1, 4,0);
        tracep->declQuad(c+19,"top u_execute rs1_data", false,-1, 63,0);
        tracep->declQuad(c+21,"top u_execute rs2_data", false,-1, 63,0);
        tracep->declQuad(c+8,"top u_execute imm_data", false,-1, 63,0);
        tracep->declQuad(c+38,"top u_execute csr_data", false,-1, 63,0);
        tracep->declQuad(c+10,"top u_execute imm_CSR", false,-1, 63,0);
        tracep->declBit(c+12,"top u_execute isNeedimmCSR", false,-1);
        tracep->declBus(c+13,"top u_execute alu_op", false,-1, 5,0);
        tracep->declBus(c+14,"top u_execute mem_op", false,-1, 3,0);
        tracep->declBus(c+15,"top u_execute exc_op", false,-1, 4,0);
        tracep->declBus(c+17,"top u_execute csr_op", false,-1, 2,0);
        tracep->declQuad(c+43,"top u_execute exc_alu_out", false,-1, 63,0);
        tracep->declQuad(c+41,"top u_execute exc_csr_out", false,-1, 63,0);
        tracep->declBit(c+40,"top u_execute exc_csr_valid", false,-1);
        tracep->declQuad(c+132,"top u_execute u_alu alu_a_i", false,-1, 63,0);
        tracep->declQuad(c+134,"top u_execute u_alu alu_b_i", false,-1, 63,0);
        tracep->declBus(c+13,"top u_execute u_alu alu_op_i", false,-1, 5,0);
        tracep->declQuad(c+136,"top u_execute u_alu alu_out", false,-1, 63,0);
        tracep->declBit(c+138,"top u_execute u_alu compare_out", false,-1);
        tracep->declBit(c+139,"top u_execute u_alu u_alu_shift shift_sra", false,-1);
        tracep->declBit(c+140,"top u_execute u_alu u_alu_shift shift_srl", false,-1);
        tracep->declBit(c+141,"top u_execute u_alu u_alu_shift shift_sll", false,-1);
        tracep->declBit(c+142,"top u_execute u_alu u_alu_shift isshift32", false,-1);
        tracep->declQuad(c+132,"top u_execute u_alu u_alu_shift shift_num", false,-1, 63,0);
        tracep->declBus(c+143,"top u_execute u_alu u_alu_shift shift_count", false,-1, 5,0);
        tracep->declQuad(c+144,"top u_execute u_alu u_alu_shift shift_out", false,-1, 63,0);
        tracep->declBus(c+196,"top u_execute u_alu u_alu_shift u_Vectorinvert1 DATA_LEN", false,-1, 31,0);
        tracep->declQuad(c+146,"top u_execute u_alu u_alu_shift u_Vectorinvert1 in", false,-1, 63,0);
        tracep->declQuad(c+148,"top u_execute u_alu u_alu_shift u_Vectorinvert1 out", false,-1, 63,0);
        tracep->declBus(c+204,"top u_execute u_alu u_alu_shift u_Vectorinvert1 i", false,-1, 31,0);
        tracep->declBus(c+196,"top u_execute u_alu u_alu_shift u_Vectorinvert2 DATA_LEN", false,-1, 31,0);
        tracep->declQuad(c+150,"top u_execute u_alu u_alu_shift u_Vectorinvert2 in", false,-1, 63,0);
        tracep->declQuad(c+152,"top u_execute u_alu u_alu_shift u_Vectorinvert2 out", false,-1, 63,0);
        tracep->declBus(c+204,"top u_execute u_alu u_alu_shift u_Vectorinvert2 i", false,-1, 31,0);
        tracep->declBit(c+154,"top u_execute u_alu u_alu_mul_top is_sr1_signed", false,-1);
        tracep->declBit(c+155,"top u_execute u_alu u_alu_mul_top is_sr2_signed", false,-1);
        tracep->declQuad(c+132,"top u_execute u_alu u_alu_mul_top sr1_data", false,-1, 63,0);
        tracep->declQuad(c+134,"top u_execute u_alu u_alu_mul_top sr2_data", false,-1, 63,0);
        tracep->declArray(c+156,"top u_execute u_alu u_alu_mul_top mul_result", false,-1, 127,0);
        tracep->declBit(c+160,"top u_execute u_alu u_alu_div_top issigned", false,-1);
        tracep->declBit(c+161,"top u_execute u_alu u_alu_div_top isdivw", false,-1);
        tracep->declQuad(c+132,"top u_execute u_alu u_alu_div_top sr1_data", false,-1, 63,0);
        tracep->declQuad(c+134,"top u_execute u_alu u_alu_div_top sr2_data", false,-1, 63,0);
        tracep->declQuad(c+162,"top u_execute u_alu u_alu_div_top div_result", false,-1, 63,0);
        tracep->declQuad(c+164,"top u_execute u_alu u_alu_div_top rem_result", false,-1, 63,0);
        tracep->declQuad(c+132,"top u_execute u_alu u_alu_div_top sr1_64_signed", false,-1, 63,0);
        tracep->declQuad(c+134,"top u_execute u_alu u_alu_div_top sr2_64_signed", false,-1, 63,0);
        tracep->declQuad(c+166,"top u_execute u_alu u_alu_div_top div64_signed", false,-1, 63,0);
        tracep->declQuad(c+168,"top u_execute u_alu u_alu_div_top rem64_signed", false,-1, 63,0);
        tracep->declQuad(c+170,"top u_execute u_alu u_alu_div_top div64_unsigned", false,-1, 63,0);
        tracep->declQuad(c+172,"top u_execute u_alu u_alu_div_top rem64_unsigned", false,-1, 63,0);
        tracep->declQuad(c+174,"top u_execute u_alu u_alu_div_top div64_result", false,-1, 63,0);
        tracep->declQuad(c+176,"top u_execute u_alu u_alu_div_top rem64_result", false,-1, 63,0);
        tracep->declBus(c+178,"top u_execute u_alu u_alu_div_top sr1_32_signed", false,-1, 31,0);
        tracep->declBus(c+179,"top u_execute u_alu u_alu_div_top sr2_32_signed", false,-1, 31,0);
        tracep->declBus(c+180,"top u_execute u_alu u_alu_div_top div32_signed", false,-1, 31,0);
        tracep->declBus(c+181,"top u_execute u_alu u_alu_div_top rem32_signed", false,-1, 31,0);
        tracep->declBus(c+182,"top u_execute u_alu u_alu_div_top div32_unsigned", false,-1, 31,0);
        tracep->declBus(c+183,"top u_execute u_alu u_alu_div_top rem32_unsigned", false,-1, 31,0);
        tracep->declBus(c+184,"top u_execute u_alu u_alu_div_top div32_result", false,-1, 31,0);
        tracep->declBus(c+185,"top u_execute u_alu u_alu_div_top rem32_result", false,-1, 31,0);
        tracep->declQuad(c+10,"top u_execute u_execute_csr imm_CSR_i", false,-1, 63,0);
        tracep->declBit(c+12,"top u_execute u_execute_csr isNeedimmCSR_i", false,-1);
        tracep->declQuad(c+19,"top u_execute u_execute_csr rs1_data_i", false,-1, 63,0);
        tracep->declQuad(c+38,"top u_execute u_execute_csr csr_data_i", false,-1, 63,0);
        tracep->declBus(c+17,"top u_execute u_execute_csr csr_op_i", false,-1, 2,0);
        tracep->declQuad(c+41,"top u_execute u_execute_csr csr_exe_result", false,-1, 63,0);
        tracep->declBit(c+40,"top u_execute u_execute_csr csr_exe_valid", false,-1);
        tracep->declBit(c+186,"top u_memory clk", false,-1);
        tracep->declBit(c+187,"top u_memory rst", false,-1);
        tracep->declQuad(c+1,"top u_memory pc", false,-1, 63,0);
        tracep->declBus(c+6,"top u_memory rd_idx", false,-1, 4,0);
        tracep->declQuad(c+19,"top u_memory rs1_data", false,-1, 63,0);
        tracep->declQuad(c+21,"top u_memory rs2_data", false,-1, 63,0);
        tracep->declQuad(c+8,"top u_memory imm_data", false,-1, 63,0);
        tracep->declBus(c+14,"top u_memory mem_op", false,-1, 3,0);
        tracep->declQuad(c+43,"top u_memory exc_in", false,-1, 63,0);
        tracep->declQuad(c+45,"top u_memory mem_out", false,-1, 63,0);
        tracep->declBit(c+47,"top u_memory isloadEnable", false,-1);
        tracep->declQuad(c+43,"top u_writeback exc_data_in", false,-1, 63,0);
        tracep->declQuad(c+45,"top u_writeback mem_data_in", false,-1, 63,0);
        tracep->declBit(c+47,"top u_writeback isloadEnable", false,-1);
        tracep->declQuad(c+23,"top u_writeback wb_data", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_clint pc_i", false,-1, 63,0);
        tracep->declBus(c+3,"top u_clint inst_data_i", false,-1, 31,0);
        tracep->declBus(c+18,"top u_clint trap_bus_i", false,-1, 2,0);
        tracep->declQuad(c+36,"top u_clint csr_mstatus_clint_i", false,-1, 63,0);
        tracep->declQuad(c+28,"top u_clint csr_mepc_clint_i", false,-1, 63,0);
        tracep->declQuad(c+30,"top u_clint csr_mcause_clint_i", false,-1, 63,0);
        tracep->declQuad(c+32,"top u_clint csr_mtval_clint_i", false,-1, 63,0);
        tracep->declQuad(c+34,"top u_clint csr_mtvec_clint_i", false,-1, 63,0);
        tracep->declQuad(c+192,"top u_clint csr_mstatus_clint_o", false,-1, 63,0);
        tracep->declQuad(c+1,"top u_clint csr_mepc_clint_o", false,-1, 63,0);
        tracep->declQuad(c+188,"top u_clint csr_mcause_clint_o", false,-1, 63,0);
        tracep->declQuad(c+25,"top u_clint csr_mtval_clint_o", false,-1, 63,0);
        tracep->declQuad(c+190,"top u_clint csr_mtvec_clint_o", false,-1, 63,0);
        tracep->declBit(c+195,"top u_clint csr_mstatus_clint_o_valid", false,-1);
        tracep->declBit(c+27,"top u_clint csr_mepc_clint_o_valid", false,-1);
        tracep->declBit(c+27,"top u_clint csr_mcause_clint_o_valid", false,-1);
        tracep->declBit(c+27,"top u_clint csr_mtval_clint_o_valid", false,-1);
        tracep->declBit(c+194,"top u_clint csr_mtvec_clint_o_valid", false,-1);
        tracep->declQuad(c+48,"top u_clint clint_pc_o", false,-1, 63,0);
        tracep->declBit(c+50,"top u_clint clint_pc_valid_o", false,-1);
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
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullQData(oldp+1,(vlSelf->top__DOT__u_pc__DOT___pc_current),64);
        tracep->fullIData(oldp+3,((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data)),32);
        tracep->fullCData(oldp+4,(((((((IData)(vlSelf->top__DOT__u_dcode__DOT___R_type) 
                                       | (IData)(vlSelf->top__DOT__u_dcode__DOT___I_type)) 
                                      | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_store)) 
                                     | (IData)(vlSelf->top__DOT__u_dcode__DOT___type_branch)) 
                                    & (~ (IData)(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR)))
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
        tracep->fullSData(oldp+7,(vlSelf->top__DOT__u_dcode__DOT___csr_idx),12);
        tracep->fullQData(oldp+8,(vlSelf->top__DOT__u_dcode__DOT___imm_data),64);
        tracep->fullQData(oldp+10,((QData)((IData)(
                                                   (0x1fU 
                                                    & (IData)(
                                                              (vlSelf->top__DOT__u_fetch__DOT___mem_data 
                                                               >> 0xfU)))))),64);
        tracep->fullBit(oldp+12,(vlSelf->top__DOT__u_dcode__DOT___isNeed_immCSR));
        tracep->fullCData(oldp+13,(vlSelf->top__DOT__u_dcode__DOT___alu_op),6);
        tracep->fullCData(oldp+14,(vlSelf->top__DOT__u_dcode__DOT___mem_op),4);
        tracep->fullCData(oldp+15,(vlSelf->top__DOT__u_dcode__DOT___exc_op),5);
        tracep->fullCData(oldp+16,(vlSelf->top__DOT__u_dcode__DOT___pc_op),4);
        tracep->fullCData(oldp+17,(vlSelf->top__DOT__u_dcode__DOT___csr_op),3);
        tracep->fullCData(oldp+18,(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus),3);
        tracep->fullQData(oldp+19,(vlSelf->top__DOT__rs1_data),64);
        tracep->fullQData(oldp+21,(vlSelf->top__DOT__rs2_data),64);
        tracep->fullQData(oldp+23,((((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
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
        tracep->fullQData(oldp+25,((QData)((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data))),64);
        tracep->fullBit(oldp+27,((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))));
        tracep->fullQData(oldp+28,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q),64);
        tracep->fullQData(oldp+30,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_q),64);
        tracep->fullQData(oldp+32,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_q),64);
        tracep->fullQData(oldp+34,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q),64);
        tracep->fullQData(oldp+36,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_q),64);
        tracep->fullQData(oldp+38,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___csr_readdata),64);
        tracep->fullBit(oldp+40,(vlSelf->top__DOT__u_execute__DOT___csr_exe_valid));
        tracep->fullQData(oldp+41,(vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result),64);
        tracep->fullQData(oldp+43,(vlSelf->top__DOT__exc_out),64);
        tracep->fullQData(oldp+45,(((IData)(vlSelf->top__DOT__u_memory__DOT___signed)
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
        tracep->fullBit(oldp+47,(((IData)(vlSelf->top__DOT__u_memory__DOT___unsigned) 
                                  | (IData)(vlSelf->top__DOT__u_memory__DOT___signed))));
        tracep->fullQData(oldp+48,((((- (QData)((IData)(
                                                        (1U 
                                                         & ((IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus) 
                                                            >> 2U))))) 
                                     & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_q) 
                                    | ((- (QData)((IData)(
                                                          (1U 
                                                           & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))))) 
                                       & vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_q))),64);
        tracep->fullBit(oldp+50,((IData)((0U != (7U 
                                                 & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))))));
        tracep->fullQData(oldp+51,((((((- (QData)((IData)(
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
        tracep->fullQData(oldp+53,(vlSelf->top__DOT__u_rv64reg__DOT__rf[0]),64);
        tracep->fullQData(oldp+55,(vlSelf->top__DOT__u_rv64reg__DOT__rf[1]),64);
        tracep->fullQData(oldp+57,(vlSelf->top__DOT__u_rv64reg__DOT__rf[2]),64);
        tracep->fullQData(oldp+59,(vlSelf->top__DOT__u_rv64reg__DOT__rf[3]),64);
        tracep->fullQData(oldp+61,(vlSelf->top__DOT__u_rv64reg__DOT__rf[4]),64);
        tracep->fullQData(oldp+63,(vlSelf->top__DOT__u_rv64reg__DOT__rf[5]),64);
        tracep->fullQData(oldp+65,(vlSelf->top__DOT__u_rv64reg__DOT__rf[6]),64);
        tracep->fullQData(oldp+67,(vlSelf->top__DOT__u_rv64reg__DOT__rf[7]),64);
        tracep->fullQData(oldp+69,(vlSelf->top__DOT__u_rv64reg__DOT__rf[8]),64);
        tracep->fullQData(oldp+71,(vlSelf->top__DOT__u_rv64reg__DOT__rf[9]),64);
        tracep->fullQData(oldp+73,(vlSelf->top__DOT__u_rv64reg__DOT__rf[10]),64);
        tracep->fullQData(oldp+75,(vlSelf->top__DOT__u_rv64reg__DOT__rf[11]),64);
        tracep->fullQData(oldp+77,(vlSelf->top__DOT__u_rv64reg__DOT__rf[12]),64);
        tracep->fullQData(oldp+79,(vlSelf->top__DOT__u_rv64reg__DOT__rf[13]),64);
        tracep->fullQData(oldp+81,(vlSelf->top__DOT__u_rv64reg__DOT__rf[14]),64);
        tracep->fullQData(oldp+83,(vlSelf->top__DOT__u_rv64reg__DOT__rf[15]),64);
        tracep->fullQData(oldp+85,(vlSelf->top__DOT__u_rv64reg__DOT__rf[16]),64);
        tracep->fullQData(oldp+87,(vlSelf->top__DOT__u_rv64reg__DOT__rf[17]),64);
        tracep->fullQData(oldp+89,(vlSelf->top__DOT__u_rv64reg__DOT__rf[18]),64);
        tracep->fullQData(oldp+91,(vlSelf->top__DOT__u_rv64reg__DOT__rf[19]),64);
        tracep->fullQData(oldp+93,(vlSelf->top__DOT__u_rv64reg__DOT__rf[20]),64);
        tracep->fullQData(oldp+95,(vlSelf->top__DOT__u_rv64reg__DOT__rf[21]),64);
        tracep->fullQData(oldp+97,(vlSelf->top__DOT__u_rv64reg__DOT__rf[22]),64);
        tracep->fullQData(oldp+99,(vlSelf->top__DOT__u_rv64reg__DOT__rf[23]),64);
        tracep->fullQData(oldp+101,(vlSelf->top__DOT__u_rv64reg__DOT__rf[24]),64);
        tracep->fullQData(oldp+103,(vlSelf->top__DOT__u_rv64reg__DOT__rf[25]),64);
        tracep->fullQData(oldp+105,(vlSelf->top__DOT__u_rv64reg__DOT__rf[26]),64);
        tracep->fullQData(oldp+107,(vlSelf->top__DOT__u_rv64reg__DOT__rf[27]),64);
        tracep->fullQData(oldp+109,(vlSelf->top__DOT__u_rv64reg__DOT__rf[28]),64);
        tracep->fullQData(oldp+111,(vlSelf->top__DOT__u_rv64reg__DOT__rf[29]),64);
        tracep->fullQData(oldp+113,(vlSelf->top__DOT__u_rv64reg__DOT__rf[30]),64);
        tracep->fullQData(oldp+115,(vlSelf->top__DOT__u_rv64reg__DOT__rf[31]),64);
        tracep->fullQData(oldp+117,(((IData)(vlSelf->top__DOT__csr_mstatus_i_en)
                                      ? vlSelf->top__DOT__csr_mstatus_i
                                      : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        tracep->fullBit(oldp+119,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mstatus_en));
        tracep->fullQData(oldp+120,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                      ? vlSelf->top__DOT__u_pc__DOT___pc_current
                                      : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        tracep->fullBit(oldp+122,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mepc_en));
        tracep->fullQData(oldp+123,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                      ? 0xbULL : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        tracep->fullBit(oldp+125,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mcause_en));
        tracep->fullQData(oldp+126,(((1U & (IData)(vlSelf->top__DOT__u_dcode__DOT___decode_trap_bus))
                                      ? (QData)((IData)(vlSelf->top__DOT__u_fetch__DOT___mem_data))
                                      : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        tracep->fullBit(oldp+128,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtval_en));
        tracep->fullQData(oldp+129,(((IData)(vlSelf->top__DOT__csr_mtvec_i_en)
                                      ? vlSelf->top__DOT__csr_mtvec_i
                                      : vlSelf->top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result)),64);
        tracep->fullBit(oldp+131,(vlSelf->top__DOT__u_rv64_csr_regfile__DOT___mtvec_en));
        tracep->fullQData(oldp+132,(vlSelf->top__DOT__u_execute__DOT___alu_in1),64);
        tracep->fullQData(oldp+134,(vlSelf->top__DOT__u_execute__DOT___alu_in2),64);
        tracep->fullQData(oldp+136,(vlSelf->top__DOT__u_execute__DOT___alu_out),64);
        tracep->fullBit(oldp+138,(((((((((0xcU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                         | (0x10U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                        & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)) 
                                       | (((0xdU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                           | (0x12U 
                                              == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                          & (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))) 
                                      | ((0xeU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                         & (0U == (
                                                   (vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                    | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                                   | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                     | ((0xfU == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                        & (0U != ((
                                                   vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[0U] 
                                                   | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[1U]) 
                                                  | vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___add_out[2U])))) 
                                    | ((0x11U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                       & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isSLT)))) 
                                   | ((0x13U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                      & (~ (IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isCF))))));
        tracep->fullBit(oldp+139,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sra));
        tracep->fullBit(oldp+140,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl));
        tracep->fullBit(oldp+141,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_sll));
        tracep->fullBit(oldp+142,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___isshift32));
        tracep->fullCData(oldp+143,((0x3fU & (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),6);
        tracep->fullQData(oldp+144,(((((- (QData)((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___shift_srl))) 
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
        tracep->fullQData(oldp+146,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num),64);
        tracep->fullQData(oldp+148,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv),64);
        tracep->fullQData(oldp+150,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res),64);
        tracep->fullQData(oldp+152,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res),64);
        tracep->fullBit(oldp+154,(((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                     | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                    | (0x16U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                   | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
        tracep->fullBit(oldp+155,((((0x14U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)) 
                                    | (0x15U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op))) 
                                   | (0x18U == (IData)(vlSelf->top__DOT__u_dcode__DOT___alu_op)))));
        tracep->fullWData(oldp+156,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result),128);
        tracep->fullBit(oldp+160,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed));
        tracep->fullBit(oldp+161,(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32));
        tracep->fullQData(oldp+162,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                                      ? (QData)((IData)(
                                                        ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                          ? 
                                                         VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                          : 
                                                         VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                                      : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                          ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                          : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
        tracep->fullQData(oldp+164,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div32)
                                      ? (QData)((IData)(
                                                        ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                                          ? 
                                                         VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                                          : 
                                                         VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))))
                                      : ((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                          ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                          : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)))),64);
        tracep->fullQData(oldp+166,(VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        tracep->fullQData(oldp+168,(VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        tracep->fullQData(oldp+170,(VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        tracep->fullQData(oldp+172,(VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)),64);
        tracep->fullQData(oldp+174,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_DIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                      : VL_DIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
        tracep->fullQData(oldp+176,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_MODDIVS_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2)
                                      : VL_MODDIV_QQQ(64, vlSelf->top__DOT__u_execute__DOT___alu_in1, vlSelf->top__DOT__u_execute__DOT___alu_in2))),64);
        tracep->fullIData(oldp+178,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1)),32);
        tracep->fullIData(oldp+179,((IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)),32);
        tracep->fullIData(oldp+180,(VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        tracep->fullIData(oldp+181,(VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        tracep->fullIData(oldp+182,(VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        tracep->fullIData(oldp+183,(VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))),32);
        tracep->fullIData(oldp+184,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_DIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                      : VL_DIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
        tracep->fullIData(oldp+185,(((IData)(vlSelf->top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed)
                                      ? VL_MODDIVS_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2))
                                      : VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in1), (IData)(vlSelf->top__DOT__u_execute__DOT___alu_in2)))),32);
        tracep->fullBit(oldp+186,(vlSelf->clk));
        tracep->fullBit(oldp+187,(vlSelf->rst));
        tracep->fullQData(oldp+188,(0xbULL),64);
        tracep->fullQData(oldp+190,(vlSelf->top__DOT__csr_mtvec_i),64);
        tracep->fullQData(oldp+192,(vlSelf->top__DOT__csr_mstatus_i),64);
        tracep->fullBit(oldp+194,(vlSelf->top__DOT__csr_mtvec_i_en));
        tracep->fullBit(oldp+195,(vlSelf->top__DOT__csr_mstatus_i_en));
        tracep->fullIData(oldp+196,(0x40U),32);
        tracep->fullQData(oldp+197,(0x80000000ULL),64);
        tracep->fullBit(oldp+199,(1U));
        tracep->fullQData(oldp+200,(0xa00001800ULL),64);
        tracep->fullQData(oldp+202,(0ULL),64);
        tracep->fullIData(oldp+204,(0x40U),32);
    }
}
