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

