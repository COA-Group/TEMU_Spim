#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/reg.h"
#include "ui_buffer.h"
#include "inst_decode.h"
extern uint32_t instr;
extern char assembly[80];

make_helper(and) {

	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val & op_src2->val);
	sprintf(assembly, "and   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: and   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(or) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (op_src1->val | op_src2->val);
    //printf("or: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "or   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: or   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(nor) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = ~ (op_src1->val | op_src2->val);
    //printf("nor: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "nor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: nor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(xor) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (op_src1->val ^ op_src2->val);
    //printf("xor: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "xor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: xor   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sllv) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (op_src2->val << ((op_src1->val << 27) >> 27));
    //printf("sllv: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "sllv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: sllv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper(sll) {

    decode_r_type_shift(instr);
    reg_w(op_dest->reg) = (op_src2->val << op_src1->val);
    //printf("sll: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "sll   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
    sprintf(result_buf, "current position: sll   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
}


make_helper(srav) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (((int)op_src2->val) >> ((op_src1->val << 27) >> 27));//检查是否进行了算数右移，查看符号位的情况
    //printf("srav: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "srav   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: srav   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper(sra) {

    decode_r_type_shift(instr);
    reg_w(op_dest->reg) = (((int)op_src2->val) >> op_src1->val);
    //printf("sra: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "sra   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
    sprintf(result_buf, "current position: sra   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
}


make_helper(srlv) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (op_src2->val >> ((op_src1->val << 27) >> 27));//检查是否进行了逻辑右移
    //printf("srlv: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "srlv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: srlv   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper(srl) {

    decode_r_type_shift(instr);
    reg_w(op_dest->reg) = (op_src2->val >> op_src1->val);
    //printf("srl: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "srl   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
    sprintf(result_buf, "current position: srl   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), op_src1->imm);
}

make_helper(mfhi) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = cpu.hi;
    //printf("mfhi: hi = %04x, dest = %04x\n", reg_hi(), reg_w(op_dest->reg));
    sprintf(assembly, "mfhi   %s", REG_NAME(op_dest->reg));
    sprintf(result_buf, "current position: mfhi   %s", REG_NAME(op_dest->reg));
}

make_helper(mflo) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = cpu.lo;
    //printf("mflo: lo = %04x, dest = %04x\n", reg_lo(), reg_w(op_dest->reg));
    sprintf(assembly, "mflo   %s", REG_NAME(op_dest->reg));
    sprintf(result_buf, "current position: mflo   %s", REG_NAME(op_dest->reg));
}

make_helper(mthi) {

    decode_r_type(instr);
    cpu.hi = op_src1->val;
    //printf("mthi: hi = %04x, src1 = %04x\n", reg_hi(), op_src1->val);
    sprintf(assembly, "mthi   %s", REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: mthi   %s", REG_NAME(op_src1->reg));
}

make_helper(mtlo) {

    decode_r_type(instr);
    cpu.lo = op_src1->val;
    //printf("mtlo: lo = %04x, src1 = %04x\n", reg_lo(), op_src1->val);
    sprintf(assembly, "mtlo   %s", REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: mtlo   %s", REG_NAME(op_src1->reg));
}

make_helper(add) {

    decode_r_type(instr);
    uint32_t temp = op_src1->val + op_src2->val;
    int j = 0;
    if((temp >> 31) != (op_src1->val >> 31) && (op_src1->val >> 31) == (op_src2->val >> 31)){
        j = sprintf(result_buf, "IntegerOverflow Exception Occured!\n");
    }
    reg_w(op_dest->reg) = (uint32_t)temp;
    //printf("add: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "add   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf+j, "current positon: add   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(addu) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (op_src1->val + op_src2->val);
    //printf("addu: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "addu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "curent position: addu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sub) {

    decode_r_type(instr);
    uint32_t temp = op_src1->val - op_src2->val;
    int j = 0;
    if((temp >> 31) != (op_src1->val >> 31) && (op_src1->val >> 31) != (op_src2->val >> 31)){
        j = sprintf(result_buf, "IntegerOverflow Exception Occured!\n");
    }
    reg_w(op_dest->reg) = (uint32_t)temp;
    //printf("sub: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "sub   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf + j, "current position: sub   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(subu) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (op_src1->val - op_src2->val);
    //printf("subu: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "subu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: subu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(slt) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = (int)op_src1->val < (int)op_src2->val ? 1 : 0;
    //printf("slt: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "slt   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: slt   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sltu) {

    decode_r_type(instr);
    reg_w(op_dest->reg) = op_src1->val < op_src2->val ? 1 : 0;
    //printf("sltu: src1 = %04x, src2 = %04x, dest = %04x\n", op_src1->val, op_src2->val, reg_w(op_dest->reg));
    sprintf(assembly, "sltu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: sltu   %s,   %s,   %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(mult) {

    decode_r_type(instr);
    uint64_t val1 = (int)op_src1->val, val2 = (int)op_src2->val;
    uint64_t tmp = (uint64_t)(val1 * val2);
    cpu.hi = tmp >> 32;
    cpu.lo = (tmp << 32) >> 32;
    sprintf(assembly, "mult   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: mult   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(multu) {

    decode_r_type(instr);
    uint64_t val1 = op_src1->val, val2 = op_src2->val;
    uint64_t tmp = (uint64_t)(val1 * val2);
    cpu.hi = tmp >> 32;
    cpu.lo = (tmp << 32) >> 32;
    sprintf(assembly, "multu   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: multu   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(div){
    decode_r_type(instr);
    uint32_t val1 = op_src1->val, val2 = op_src2->val;
    uint32_t res = (uint32_t)(val1 / val2);
    uint32_t mod = (uint32_t)(val1 % val2);
    cpu.hi = mod;
    cpu.lo = res;
    sprintf(assembly, "div   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: div   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(divu){
    decode_r_type(instr);
    uint32_t val1 = op_src1->val, val2 = op_src2->val;
    uint32_t res = (uint32_t)(val1 / val2);
    uint32_t mod = (uint32_t)(val1 % val2);
    cpu.hi = mod;
    cpu.lo = res;
    sprintf(assembly, "divu   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
    sprintf(result_buf, "current position: divu   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(jalr){
    decode_r_type(instr);
    reg_w(op_dest->reg) = cpu.pc + 8;
    cpu.next_PC = op_src1->val - 4;
    sprintf(assembly, "jalr   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg));
    sprintf(result_buf, "current position: jalr   %s,   %s", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg));
    temu_state = JUMP;
}

make_helper(jr){
    decode_r_type(instr);
    cpu.next_PC = op_src1->val - 4;
    sprintf(assembly, "jr   %s", REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: jr   %s", REG_NAME(op_src1->reg));
    temu_state = JUMP;
}

make_helper(c_break){
    decode_trap(instr);
    sprintf(assembly, "break   0x%x", op_src1->val);
    sprintf(result_buf, "trigger break, there're some error occered, the program has exited");
    temu_state = STOP;
}

make_helper(M_C0){
    decode_M_C0(instr);
    if(op_src1->val == 0){
        reg_w(op_src2->reg) = cp0_w(op_dest->reg);
        sprintf(assembly, "mfc0   %s    %s", REG_NAME(op_src2->reg) , CP0_NAME(op_dest->reg));
        sprintf(result_buf, "mfc0   %s    %s", REG_NAME(op_src2->reg) , CP0_NAME(op_dest->reg));
    }
    else if(op_src1->val == 4){
        cp0_w(op_dest->reg) = reg_w(op_src2->reg);
        sprintf(assembly, "mft0   %s    %s", REG_NAME(op_src2->reg) , CP0_NAME(op_dest->reg));
        sprintf(result_buf, "mft0   %s    %s", REG_NAME(op_src2->reg) , CP0_NAME(op_dest->reg));
    }
    else if(op_src1->val == 16 && (instr & FUNC_MASK) == 0x18){
        sprintf(assembly, "eret");
        sprintf(result_buf, "eret");
        cpu.pc = cp0_w(R_EPC) - 4;
    }
}

make_helper(syscall){
    decode_trap(instr);
    sprintf(assembly, "syscall");
    sprintf(result_buf, "syscall\ntrigger syscall, should generate ExeCode 0x08");
}
