#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/reg.h"
#include "inst_decode.h"
#include "ui_buffer.h"
extern uint32_t instr;
extern char assembly[80];

decode_helper(d_lui) {
    decode_imm_type(instr);
    sprintf(assembly, "lui   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

decode_helper(d_ori) {
    decode_imm_type(instr);
    sprintf(assembly, "ori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

decode_helper(d_andi) {

    decode_imm_type(instr);
    sprintf(assembly, "andi   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

decode_helper(d_xori) {

    decode_imm_type(instr);
    sprintf(assembly, "xori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

decode_helper(d_lb) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "lb   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
}

decode_helper(d_lbu) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "lbu   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->imm, REG_NAME(op_src1->reg));
}

decode_helper(d_lh) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "lh   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));

}

decode_helper(d_lhu) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "lhu   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
}

decode_helper(d_lw) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "lw   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
}

decode_helper(d_sb) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "sb   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
}

decode_helper(d_sh) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "sh   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
}

decode_helper(d_sw) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "sw   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));

}

decode_helper(d_addi) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "addi   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

decode_helper(d_addiu) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "addiu   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

decode_helper(d_slti) {

    decode_imm_type_memory(instr);
    sprintf(assembly, "slti   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), (int)op_src2->val);
}

decode_helper(d_sltiu) {
    decode_imm_type_memory(instr);
    sprintf(assembly, "sltiu   %s,   %s,   %u", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

decode_helper(d_beq){
    decode_imm_type_compare(instr);
    sprintf(assembly, "beq   %s,   %s,   %d", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val);
}

decode_helper(d_bgtz){
    decode_imm_type_compare(instr);
    sprintf(assembly, "bgtz   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
}

decode_helper(d_blez){
    decode_imm_type_compare(instr);
    sprintf(assembly, "blez   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
}

decode_helper(d_bne){
    decode_imm_type_compare(instr);
    sprintf(assembly, "bne   %s,   %s,   %d", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val);
}

decode_helper(d_g){
    decode_imm_type_compare(instr);
    if(op_dest->reg == 1){
        sprintf(assembly, "bgez   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    }
    else if(op_dest->reg == 0x11){
        sprintf(assembly, "bgezal   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    }
    else if(op_dest->reg == 0x10){
        sprintf(assembly, "bltzal   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    }
    else if(op_dest->reg == 0){
        sprintf(assembly, "bltz   %s,   %u", REG_NAME(op_src1->reg), op_src2->val);
    }
}
