#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/helper.h"
#include "ui_buffer.h"
#include "inst_decode.h"
#include "../TEMU/temu/include/cpu/reg.h"

extern int temu_state;

/* decode I-type instrucion with unsigned immediate */
void decode_imm_type(uint32_t instr) {

    op_src1->type = OP_TYPE_REG;
    op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
    op_src1->val = reg_w(op_src1->reg);

    op_src2->type = OP_TYPE_IMM;
    op_src2->imm = instr & IMM_MASK;
    op_src2->val = op_src2->imm;

    op_dest->type = OP_TYPE_REG;
    op_dest->reg = (instr & RT_MASK) >> (IMM_SIZE);
}

void decode_imm_type_memory(uint32_t instr) {

    op_src1->type = OP_TYPE_REG;
    op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
    op_src1->val = reg_w(op_src1->reg);

    op_src2->type = OP_TYPE_IMM;
    op_src2->imm = instr & IMM_MASK;
    op_src2->val = ((int)(op_src2->imm << 16)) >> 16;

    op_dest->type = OP_TYPE_REG;
    op_dest->reg = (instr & RT_MASK) >> (IMM_SIZE);
}

/* decode R-type instrucion */
void decode_r_type(uint32_t instr) {

    op_src1->type = OP_TYPE_REG;
    op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
    op_src1->val = reg_w(op_src1->reg);

    op_src2->type = OP_TYPE_REG;
    op_src2->imm = (instr & RT_MASK) >> (RD_SIZE + SHAMT_SIZE + FUNC_SIZE);
    op_src2->val = reg_w(op_src2->reg);

    op_dest->type = OP_TYPE_REG;
    op_dest->reg = (instr & RD_MASK) >> (SHAMT_SIZE + FUNC_SIZE);
}

void decode_r_type_shift(uint32_t instr) {

    op_src1->type = OP_TYPE_IMM;
    op_src1->imm = (instr & SHAMT_MASK) >> (FUNC_SIZE);
    op_src1->val = op_src1->imm;

    op_src2->type = OP_TYPE_REG;
    op_src2->imm = (instr & RT_MASK) >> (RD_SIZE + SHAMT_SIZE + FUNC_SIZE);
    op_src2->val = reg_w(op_src2->reg);

    op_dest->type = OP_TYPE_REG;
    op_dest->reg = (instr & RD_MASK) >> (SHAMT_SIZE + FUNC_SIZE);
}

void init_decode(){
    temu_state = RUNNING;
    volatile uint32_t n = -1;

    for(; n > 0; n --) {
        uint32_t pc_temp = cpu.pc;
        /* Execute one instruction, including instruction fetch,
         * instruction decode, and the actual execution. */
        f_exec(cpu.pc);

        cpu.pc += 4;
        print_bin_instr(pc_temp);
        strcat(asm_buf, assembly);
        strcat(inst , asm_buf);
        strcat(inst , "\n");
        if(temu_state != RUNNING) {
            strcpy(ui_inst , inst);
            cpu.pc = 0x00000000;
            temu_state = STOP;
            return;
        }
    }

    if(temu_state == RUNNING) {
        temu_state = STOP;
    }
}
