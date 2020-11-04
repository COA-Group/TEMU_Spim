#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "ui_buffer.h"
extern char assembly[80];

/* stop temu */
decode_helper(d_temu_trap) {
    sprintf(assembly, "HIT GOOD TEMP");
    temu_state = END;
}

decode_helper(d_inv) {

    uint32_t temp;
    temp = instr_fetch(pc, 4);

    uint8_t *p = (void *)&temp;
    printf("invalid opcode(pc = 0x%08x): %02x %02x %02x %02x ...\n\n",
            pc, p[3], p[2], p[1], p[0]);

    printf("There are two cases which will trigger this unexpected exception:\n\
1. The instruction at pc = 0x%08x is not implemented.\n\
2. Something is implemented incorrectly.\n", pc);
    printf("Find this pc value(0x%08x) in the disassembling result to distinguish which case it is.\n\n", pc);

    assert(0);
}

