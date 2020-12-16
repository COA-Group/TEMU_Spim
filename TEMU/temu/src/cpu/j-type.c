#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/reg.h"
#include "inst_decode.h"
#include "ui_buffer.h"
extern uint32_t instr;
extern char assembly[80];

make_helper(j){
    decode_j_type(instr);
    sprintf(result_buf, "%x : current position: j   %u", cpu.pc , op_dest->imm);
    cpu.next_PC = ((op_dest->imm << 2) | (cpu.pc >> 28) << 28) - 4;
    sprintf(assembly, "j   %u", op_dest->imm);
    temu_state = JUMP;
}

make_helper(jal){
    decode_j_type(instr);
    printf("%u , %u\n" , cpu.ra , cpu.pc);
    reg_w(31) = cpu.pc + 8;
    printf("%u\n" , cpu.ra);
    cpu.next_PC = ((op_dest->imm << 2) | (cpu.pc >> 28) << 28) - 4;
    sprintf(assembly, "jal   %u", op_dest->imm);
    sprintf(result_buf, "current position: jal   %u", op_dest->imm);
    temu_state = JUMP;
}
