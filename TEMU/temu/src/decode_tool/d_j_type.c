#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/reg.h"
#include "inst_decode.h"
#include "ui_buffer.h"
extern uint32_t instr;
extern char assembly[80];

decode_helper(d_j){
    decode_j_type(instr);
    sprintf(assembly, "j   %u", op_dest->imm);
}

decode_helper(d_jal){
    decode_j_type(instr);
    sprintf(assembly, "jal   %u", op_dest->imm);
}
