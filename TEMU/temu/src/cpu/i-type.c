#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/reg.h"
#include "inst_decode.h"
#include "ui_buffer.h"
extern uint32_t instr;
extern char assembly[80];
make_helper(lui) {

	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src2->val << 16);
	sprintf(assembly, "lui   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
    sprintf(result_buf, "current position: lui   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

make_helper(ori) {

	decode_imm_type(instr);
	reg_w(op_dest->reg) = op_src1->val | op_src2->val;
	sprintf(assembly, "ori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
    sprintf(result_buf, "current position: ori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(andi) {

    decode_imm_type(instr);
    reg_w(op_dest->reg) = op_src1->val & op_src2->val;
    sprintf(assembly, "andi   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
    sprintf(result_buf, "current position: andi   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(xori) {

    decode_imm_type(instr);
    reg_w(op_dest->reg) = op_src1->val ^ op_src2->val;
    sprintf(assembly, "xori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
    sprintf(result_buf, "current position: xori   %s,   %s,   0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->imm);
}

make_helper(lb) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    reg_w(op_dest->reg) = ((int)(mem_read(addr, 1) << 24)) >> 24;
    sprintf(assembly, "lb   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: lb   %s,   0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}

make_helper(lbu) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    reg_w(op_dest->reg) = mem_read(addr, 1);
    sprintf(assembly, "lbu   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->imm, REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: lbu   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->imm, REG_NAME(op_src1->reg));
}

make_helper(lh) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    uint32_t mask = 0x1;
    int check = addr & mask;
    if(check != 0){
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x04 << 2);
        cp0_w(R_BadVAddr) = addr;
        cp0_w(R_EPC) = cpu.pc;
        cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
        if(temu_state == JUMP){//in the delay slot
            cp0_w(R_EPC) -= 4;
            cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
        }

        sprintf(result_buf, "AddressError Exception Occured in MEM!\ncurrent position: lh   %s,   %d(%s)"
                , REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
    else{
        reg_w(op_dest->reg) = ((int)(mem_read(addr, 2) << 16)) >> 16;
        sprintf(assembly, "lh   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
        sprintf(result_buf, "current position: lh   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
}

make_helper(lhu) {
    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    uint32_t mask = 1;
    int check = addr & mask;
    if(check != 0){
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x04 << 2);
        cp0_w(R_BadVAddr) = addr;
        cp0_w(R_EPC) = cpu.pc;
        cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
        if(temu_state == JUMP){//in the delay slot
            cp0_w(R_EPC) -= 4;
            cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
        }
        sprintf(result_buf, "AddressError Exception Occured in MEM!\ncurrent position: lhu   %s,   %d(%s)"
                , REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
    else{
        reg_w(op_dest->reg) = mem_read(addr, 2);
        sprintf(assembly, "lhu   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
        sprintf(result_buf, "current position: lhu   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
}

make_helper(lw) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    uint32_t mask = 0x3;
    int check = addr & mask;
    if(check != 0){
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x04 << 2);
        cp0_w(R_BadVAddr) = addr;
        cp0_w(R_EPC) = cpu.pc;
        cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
        if(temu_state == JUMP){//in the delay slot
            cp0_w(R_EPC) -= 4;
            cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
        }
        sprintf(result_buf, "AddressError Exception Occured in MEM!\ncurrent position: lw   %s,   %d(%s)"
                , REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
    else{
        reg_w(op_dest->reg) = mem_read(addr, 4);
        sprintf(assembly, "lw   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
        sprintf(result_buf, "current position: lw   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
}

make_helper(sb) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    mem_write(addr, 1, reg_w(op_dest->reg));
    sprintf(assembly, "sb   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    sprintf(result_buf, "current position: sb   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(sh) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    uint32_t mask = 1;
    int check = addr & mask;
    if(check != 0){
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x05 << 2);
        cp0_w(R_BadVAddr) = addr;
        cp0_w(R_EPC) = cpu.pc;
        cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
        if(temu_state == JUMP){//in the delay slot
            cp0_w(R_EPC) -= 4;
            cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
        }
        sprintf(result_buf, "AddressError Exception Occured in MEM!\ncurrent position: sh   %s,   %d(%s)"
                , REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
    else{
        mem_write(addr, 2, reg_w(op_dest->reg));
        sprintf(assembly, "sh   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
        sprintf(result_buf, "current position: sh   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
}

make_helper(sw) {

    decode_imm_type_memory(instr);
    uint32_t addr = op_src1->val + op_src2->val;
    uint32_t mask = 3;
    int check = addr & mask;
    if(check != 0){
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x05 << 2);
        cp0_w(R_BadVAddr) = addr;
        cp0_w(R_EPC) = cpu.pc;
        cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
        if(temu_state == JUMP){//in the delay slot
            cp0_w(R_EPC) -= 4;
            cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
        }
        sprintf(result_buf, "AddressError Exception Occured in MEM!\ncurrent position: sw   %s,   %d(%s)"
                , REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
    else{
        mem_write(addr, 4, reg_w(op_dest->reg));
        sprintf(assembly, "sw   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
        sprintf(result_buf, "current position: sw   %s,   %d(%s)", REG_NAME(op_dest->reg), (int)op_src2->val, REG_NAME(op_src1->reg));
    }
}

make_helper(addi) {

    decode_imm_type_memory(instr);
    int temp = op_src1->val + op_src2->val;
    int j = 0;

    if(((temp & 0x80000000) != (op_src1->val & 0x80000000))
            && ((op_src1->val & 0x80000000) == (op_src2->val & 0x80000000))){
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x0C << 2);
        j = sprintf(result_buf, "IntegerOverflow Exception Occured!\n");
        cp0_w(R_EPC) = cpu.pc;
        cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
        if(temu_state == JUMP){//in the delay slot
            cp0_w(R_EPC) -= 4;
            cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
        }
    }
    reg_w(op_dest->reg) = (uint32_t)temp;
    sprintf(assembly, "addi   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
    sprintf(result_buf + j, "current position: addi   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(addiu) {

    decode_imm_type_memory(instr);
    reg_w(op_dest->reg) = op_src1->val + op_src2->val;
    sprintf(assembly, "addiu   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
    sprintf(result_buf, "current position: addiu   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(slti) {

    decode_imm_type_memory(instr);
    reg_w(op_dest->reg) = (int)op_src1->val < (int)op_src2->val ? 1 : 0;
    sprintf(assembly, "slti   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), (int)op_src2->val);
    sprintf(result_buf, "current position: slti   %s,   %s,   %d", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), (int)op_src2->val);
}

make_helper(sltiu) {

    decode_imm_type_memory(instr);
    reg_w(op_dest->reg) = op_src1->val < op_src2->val ? 1 : 0;
    sprintf(assembly, "sltiu   %s,   %s,   %u", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
    sprintf(result_buf, "current position: sltiu   %s,   %s,   %u", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(beq){
    decode_imm_type_compare(instr);
    int offset = (op_src1->val == op_dest->val)? (op_src2->val): 0;
    cpu.next_PC = cpu.pc + offset;//it's exception will be checked when next_PC is executed. the same in the following instructions.
    sprintf(assembly, "beq   %s,   %s,   %d", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val);
    sprintf(result_buf, "current position: beq   %s,   %s,   %d\n next pc: %x", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val
            ,cpu.pc);
    temu_state = JUMP;
}

make_helper(bgtz){
    decode_imm_type_compare(instr);
    int offset = (op_src1->val > 0 && op_src1->val < (1 << 16))? (op_src2->val): 0;
    cpu.next_PC = cpu.pc + offset;
    sprintf(assembly, "bgtz   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    sprintf(result_buf, "current position: bgtz   %s,   %u", REG_NAME(op_src1->reg), op_src2->val);
    temu_state = JUMP;
}

make_helper(blez){
    decode_imm_type_compare(instr);
    int offset = (op_src1->val >= (1 << 16) || op_src1->val == 0)? (op_src2->val): 0;
    cpu.next_PC = cpu.pc + offset;
    sprintf(assembly, "blez   %s,   %d", REG_NAME(op_src1->reg), op_src2->imm);
    sprintf(result_buf, "current position: blez   %s,   %d", REG_NAME(op_src1->reg), op_src2->imm);
    temu_state = JUMP;
}

make_helper(bne){
    decode_imm_type_compare(instr);
    int offset = (op_src1->val != op_dest->val)? (op_src2->val): 0;
    cpu.next_PC = cpu.pc + offset;
    sprintf(assembly, "bne   %s,   %s,   %d", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val);
    sprintf(result_buf, "current position: bne   %s,   %s,   %d", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val);
    temu_state = JUMP;
}

make_helper(g){
    decode_imm_type_compare(instr);
    int offset = 0;
    if(op_dest->reg == 1){
        offset = (op_src1->val < (1 << 16))? (op_src2->val): 0;
        sprintf(assembly, "bgez   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
        sprintf(result_buf, "current position: bgez   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    }
    else if(op_dest->reg == 0x11){
        if(op_src1->val < (1 << 16)){
            cpu.ra = cpu.pc + 8;
            offset = op_src2->val;
        }
        sprintf(assembly, "bgezal   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
        sprintf(result_buf, "current position: bgezal   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    }
    else if(op_dest->reg == 0x10){
        if(op_src1->val >= (1 << 16)){
            cpu.ra = cpu.pc + 8;
            offset = op_src2->val;
        }
        sprintf(assembly, "bltzal   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
        sprintf(result_buf, "current position: bltzal   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
    }
    else if(op_dest->reg == 0){

        offset = (op_src1->val >= (1 << 16))? (op_src2->val): 0;
        sprintf(assembly, "bltz   %s,   %d", REG_NAME(op_src1->reg), op_src2->val);
        sprintf(result_buf, "%x : current position: bltz   %s,   %d", cpu.pc,REG_NAME(op_src1->reg), op_src2->val);
    }
    cpu.next_PC = cpu.pc + offset;
    temu_state = JUMP;
}
