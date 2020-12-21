#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/reg.h"
#include "ui_buffer.h"
#include "inst_decode.h"
extern uint32_t instr;
extern char assembly[80];

decode_helper(d_and) {
    decode_r_type(instr);
    sprintf(assembly, "and   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_or) {

    decode_r_type(instr);
    sprintf(assembly, "or   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_nor) {

    decode_r_type(instr);
    sprintf(assembly, "nor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_xor) {

    decode_r_type(instr);
    sprintf(assembly, "xor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_sllv) {

    decode_r_type(instr);
    sprintf(assembly, "sllv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

decode_helper(d_sll) {

    decode_r_type_shift(instr);
    sprintf(assembly, "sll   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
}


decode_helper(d_srav) {

    decode_r_type(instr);
    sprintf(assembly, "srav   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

decode_helper(d_sra) {

    decode_r_type_shift(instr);
    sprintf(assembly, "sra   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
}


decode_helper(d_srlv) {

    decode_r_type(instr);
    sprintf(assembly, "srlv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

decode_helper(d_srl) {

    decode_r_type_shift(instr);
    sprintf(assembly, "srl   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
}

decode_helper(d_mfhi) {

    decode_r_type(instr);
    sprintf(assembly, "mfhi   %s", REG_NAME(op_dest->reg));
}

decode_helper(d_mflo) {

    decode_r_type(instr);
    sprintf(assembly, "mflo   %s", REG_NAME(op_dest->reg));
}

decode_helper(d_mthi) {

    decode_r_type(instr);
    sprintf(assembly, "mthi   %s", REG_NAME(op_src1->reg));
}

decode_helper(d_mtlo) {

    decode_r_type(instr);
    sprintf(assembly, "mtlo   %s", REG_NAME(op_src1->reg));
}

decode_helper(d_add) {

    decode_r_type(instr);
    sprintf(assembly, "add   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_addu) {

    decode_r_type(instr);
    sprintf(assembly, "addu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_sub) {

    decode_r_type(instr);
    sprintf(assembly, "sub   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_subu) {

    decode_r_type(instr);
    sprintf(assembly, "subu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_slt) {

    decode_r_type(instr);
    sprintf(assembly, "slt   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_sltu) {

    decode_r_type(instr);
    sprintf(assembly, "sltu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_mult) {

    decode_r_type(instr);
    sprintf(assembly, "mult   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_multu) {

    decode_r_type(instr);
    sprintf(assembly, "multu   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_div){
    decode_r_type(instr);
    sprintf(assembly, "div   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_divu){
    decode_r_type(instr);
    sprintf(assembly, "divu   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

decode_helper(d_jalr){
    decode_r_type(instr);
    sprintf(assembly, "jalr   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg));
}

decode_helper(d_jr){
    decode_r_type(instr);
    sprintf(assembly, "jr   %s", REG_NAME(op_src1->reg));
}

decode_helper(d_break){
    decode_trap(instr);
    sprintf(assembly, "break   0x%x", op_src1->val);
}

decode_helper(d_M_C0){
    decode_M_C0(instr);
    if(op_src1->val == 0){
        sprintf(assembly, "mfc0   %s    %s", REG_NAME(op_src2->reg) , CP0_NAME(op_dest->reg));
    }
    else if(op_src1->val == 4){
        sprintf(assembly, "mft0   %s    %s", REG_NAME(op_src2->reg) , CP0_NAME(op_dest->reg));
    }
    else if(op_src1->val == 16 && (instr & FUNC_MASK) == 0x18){
        sprintf(assembly, "eret");
    }
}

decode_helper(d_sys_call){
    decode_trap(instr);
    sprintf(assembly, "syscall");
}
