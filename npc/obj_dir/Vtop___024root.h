// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;
VL_MODULE(Vtop___024root) {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst,0,0);
        CData/*0:0*/ top__DOT__csr_mtvec_i_en;
        CData/*0:0*/ top__DOT__csr_mstatus_i_en;
        CData/*0:0*/ top__DOT__u_pc__DOT___isready_branch;
        CData/*0:0*/ top__DOT__u_pc__DOT___isready_inc4;
        CData/*0:0*/ top__DOT__u_dcode__DOT___type_load;
        CData/*0:0*/ top__DOT__u_dcode__DOT___type_store;
        CData/*0:0*/ top__DOT__u_dcode__DOT___type_branch;
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
        CData/*0:0*/ top__DOT__u_dcode__DOT___R_type;
        CData/*0:0*/ top__DOT__u_dcode__DOT___I_type;
        CData/*0:0*/ top__DOT__u_dcode__DOT___U_type;
        CData/*0:0*/ top__DOT__u_dcode__DOT___isNeed_immCSR;
        CData/*0:0*/ top__DOT__u_dcode__DOT___isNeed_csr;
        CData/*4:0*/ top__DOT__u_dcode__DOT___rd_idx;
        CData/*0:0*/ top__DOT__u_dcode__DOT___csr_set;
        CData/*0:0*/ top__DOT__u_dcode__DOT___csr_clear;
        CData/*2:0*/ top__DOT__u_dcode__DOT___csr_op;
        CData/*5:0*/ top__DOT__u_dcode__DOT___alu_op;
        CData/*4:0*/ top__DOT__u_dcode__DOT___exc_op;
        CData/*3:0*/ top__DOT__u_dcode__DOT___mem_op;
        CData/*3:0*/ top__DOT__u_dcode__DOT___pc_op;
        CData/*2:0*/ top__DOT__u_dcode__DOT___decode_trap_bus;
        CData/*0:0*/ top__DOT__u_rv64_csr_regfile__DOT___mstatus_en;
        CData/*0:0*/ top__DOT__u_rv64_csr_regfile__DOT___mepc_en;
        CData/*0:0*/ top__DOT__u_rv64_csr_regfile__DOT___mcause_en;
        CData/*0:0*/ top__DOT__u_rv64_csr_regfile__DOT___mtval_en;
        CData/*0:0*/ top__DOT__u_rv64_csr_regfile__DOT___mtvec_en;
        CData/*0:0*/ top__DOT__u_execute__DOT___rs1_rs2;
        CData/*0:0*/ top__DOT__u_execute__DOT___rs1_imm;
        CData/*0:0*/ top__DOT__u_execute__DOT___pc_4;
        CData/*0:0*/ top__DOT__u_execute__DOT___csr_exe_valid;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isCMP;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isSUBop;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isCF;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isSLT;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___shift_sra;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___shift_srl;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___shift_sll;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___isshift32;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___is_div_signed;
        CData/*0:0*/ top__DOT__u_execute__DOT__u_alu__DOT___is_div32;
        CData/*5:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_in2;
        CData/*0:0*/ top__DOT__u_memory__DOT___ls8byte;
        CData/*0:0*/ top__DOT__u_memory__DOT___ls16byte;
    };
    struct {
        CData/*0:0*/ top__DOT__u_memory__DOT___ls32byte;
        CData/*0:0*/ top__DOT__u_memory__DOT___unsigned;
        CData/*0:0*/ top__DOT__u_memory__DOT___signed;
        CData/*0:0*/ __Vclklast__TOP__clk;
        SData/*11:0*/ top__DOT__u_dcode__DOT___csr_idx;
        VlWide<3>/*64:0*/ top__DOT__u_execute__DOT__u_alu__DOT___alu_a;
        VlWide<3>/*64:0*/ top__DOT__u_execute__DOT__u_alu__DOT___alu_b;
        VlWide<3>/*64:0*/ top__DOT__u_execute__DOT__u_alu__DOT___add_out;
        VlWide<4>/*127:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_mul_top__DOT___mul_result;
        QData/*63:0*/ top__DOT__rs1_data;
        QData/*63:0*/ top__DOT__rs2_data;
        QData/*63:0*/ top__DOT__csr_mtvec_i;
        QData/*63:0*/ top__DOT__csr_mstatus_i;
        QData/*63:0*/ top__DOT__exc_out;
        QData/*63:0*/ top__DOT__u_pc__DOT___pc_next;
        QData/*63:0*/ top__DOT__u_pc__DOT___pc_current;
        QData/*63:0*/ top__DOT__u_fetch__DOT___mem_data;
        QData/*63:0*/ top__DOT__u_dcode__DOT___imm_data;
        QData/*63:0*/ top__DOT__u_rv64_csr_regfile__DOT___mstatus_q;
        QData/*63:0*/ top__DOT__u_rv64_csr_regfile__DOT___mepc_q;
        QData/*63:0*/ top__DOT__u_rv64_csr_regfile__DOT___mcause_q;
        QData/*63:0*/ top__DOT__u_rv64_csr_regfile__DOT___mtval_q;
        QData/*63:0*/ top__DOT__u_rv64_csr_regfile__DOT___mtvec_q;
        QData/*63:0*/ top__DOT__u_rv64_csr_regfile__DOT___csr_readdata;
        QData/*63:0*/ top__DOT__u_execute__DOT___alu_in1;
        QData/*63:0*/ top__DOT__u_execute__DOT___alu_in2;
        QData/*63:0*/ top__DOT__u_execute__DOT___alu_out;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT___alu_out;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shift_num_inv;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___shifter_res;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_alu__DOT__u_alu_shift__DOT___srl_res;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_op2;
        QData/*63:0*/ top__DOT__u_execute__DOT__u_execute_csr__DOT___csr_exe_result;
        QData/*63:0*/ top__DOT__u_memory__DOT___mem_read;
        QData/*63:0*/ top__DOT__u_memory__DOT___addr;
        QData/*63:0*/ __Vtask_top__DOT__u_fetch__DOT__pmem_read__0__rdata;
        VlUnpacked<QData/*63:0*/, 32> top__DOT__u_rv64reg__DOT__rf;
        VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    };

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
