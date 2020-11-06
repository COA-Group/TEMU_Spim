#include "../TEMU/temu/include/temu.h"
#include "ui_buffer.h"
#include <stdlib.h>

CPU_state cpu;

const char *regfile[] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

void display_reg() {
        int i;
        int k = 0;
        int j = 0;

        for(i = 0; i < 32; i ++) {
            j += sprintf(reg_buf + j, "%s\t0x%08x\t%d\n", regfile[i], cpu.gpr[i]._32, cpu.gpr[i]._32);
        }
        j += sprintf(reg_buf + j ,"%s\t0x%08x\t%d\n", "$pc", cpu.pc, cpu.pc);
}

