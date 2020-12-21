#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/cpu/all-instr.h"

typedef void (*op_fun)(uint32_t);
static decode_helper(d_2byte_esc);
static make_helper(d_No1_esc);
Operands ops_decoded;
uint32_t instr;


/* TODO: Add more instructions!!! */

op_fun f_opcode_table [64] = {
    /* 0x00 */	d_2byte_esc, d_g, d_j, d_jal,
    /* 0x04 */	d_beq, d_bne, d_blez, d_bgtz,
    /* 0x08 */	d_addi, d_addiu, d_slti, d_sltiu,
    /* 0x0c */	d_andi, d_ori, d_xori, d_lui,
    /* 0x10 */	d_M_C0, d_inv, d_temu_trap, d_decode_trap,
    /* 0x14 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x18 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x1c */	d_inv, d_inv, d_inv, d_inv,
    /* 0x20 */	d_lb, d_lh, d_inv, d_lw,
    /* 0x24 */	d_lbu, d_lhu, d_inv, d_inv,
    /* 0x28 */	d_sb, d_sh, d_inv, d_sw,
    /* 0x2c */	d_inv, d_inv, d_inv, d_inv,
    /* 0x30 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x34 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x38 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x3c */	d_inv, d_inv, d_inv, d_inv
};

op_fun f_2byte_opcode_table [64] = {
    /* 0x00 */	d_sll, d_inv, d_srl, d_sra,
    /* 0x04 */	d_sllv, d_inv, d_srlv, d_srav,
    /* 0x08 */	d_jr, d_jalr, d_inv, d_inv,
    /* 0x0c */	d_sys_call, d_break, d_inv, d_inv,
    /* 0x10 */	d_mfhi, d_mthi, d_mflo, d_mtlo,
    /* 0x14 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x18 */	d_mult, d_multu, d_div, d_divu,
    /* 0x1c */	d_inv, d_inv, d_inv, d_inv,
    /* 0x20 */	d_add, d_addu, d_sub, d_subu,
    /* 0x24 */	d_and, d_or, d_xor, d_nor,
    /* 0x28 */	d_inv, d_inv, d_slt, d_sltu,
    /* 0x2c */	d_inv, d_inv, d_inv, d_inv,
    /* 0x30 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x34 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x38 */	d_inv, d_inv, d_inv, d_inv,
    /* 0x3c */	d_inv, d_inv, d_inv, d_inv
};

decode_helper(f_exec) {
    instr = instr_fetch(pc, 4);
    ops_decoded.opcode = instr >> 26;
    f_opcode_table[ ops_decoded.opcode ](pc);
}

static decode_helper(d_2byte_esc) {
    ops_decoded.func = instr & FUNC_MASK;
    f_2byte_opcode_table[ops_decoded.func](pc);
}
