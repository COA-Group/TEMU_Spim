#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/cpu/all-instr.h"

typedef void (*op_fun)(uint32_t);
static decode_helper(d_2byte_esc);

Operands ops_decoded;
uint32_t instr;


/* TODO: Add more instructions!!! */

op_fun f_opcode_table [64] = {
/* 0x00 */	d_2byte_esc, d_inv, d_inv, d_inv,
/* 0x04 */	d_inv, d_inv, d_inv, d_inv,
/* 0x08 */	d_inv, d_inv, d_inv, d_inv,
/* 0x0c */	d_inv, d_ori, d_inv, d_lui,
/* 0x10 */	d_inv, d_inv, d_temu_trap, d_inv,
/* 0x14 */	d_inv, d_inv, d_inv, d_inv,
/* 0x18 */	d_inv, d_inv, d_inv, d_inv,
/* 0x1c */	d_inv, d_inv, d_inv, d_inv,
/* 0x20 */	d_inv, d_inv, d_inv, d_inv,
/* 0x24 */	d_inv, d_inv, d_inv, d_inv,
/* 0x28 */	d_inv, d_inv, d_inv, d_inv,
/* 0x2c */	d_inv, d_inv, d_inv, d_inv,
/* 0x30 */	d_inv, d_inv, d_inv, d_inv,
/* 0x34 */	d_inv, d_inv, d_inv, d_inv,
/* 0x38 */	d_inv, d_inv, d_inv, d_inv,
/* 0x3c */	d_inv, d_inv, d_inv, d_inv
};

op_fun f_2byte_opcode_table [64] = {
/* 0x00 */	d_inv, d_inv, d_inv, d_inv,
/* 0x04 */	d_inv, d_inv, d_inv, d_inv,
/* 0x08 */	d_inv, d_inv, d_inv, d_inv,
/* 0x0c */	d_inv, d_inv, d_inv, d_inv,
/* 0x10 */	d_inv, d_inv, d_inv, d_inv,
/* 0x14 */	d_inv, d_inv, d_inv, d_inv,
/* 0x18 */	d_inv, d_inv, d_inv, d_inv,
/* 0x1c */	d_inv, d_inv, d_inv, d_inv,
/* 0x20 */	d_inv, d_inv, d_inv, d_inv,
/* 0x24 */	d_and, d_inv, d_inv, d_inv,
/* 0x28 */	d_inv, d_inv, d_inv, d_inv,
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
