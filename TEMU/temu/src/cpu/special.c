#include "../TEMU/temu/include/cpu/helper.h"
#include "../TEMU/temu/include/monitor/monitor.h"
#include "inst_decode.h"
#include "ui_buffer.h"
extern char assembly[80];
extern uint32_t instr;
/* invalid opcode */
make_helper(inv) {

	uint32_t temp;
	temp = instr_fetch(pc, 4);

	uint8_t *p = (void *)&temp;
	printf("invalid opcode(pc = 0x%08x): %02x %02x %02x %02x ...\n\n", 
			pc, p[3], p[2], p[1], p[0]);

	printf("There are two cases which will trigger this unexpected exception:\n\
1. The instruction at pc = 0x%08x is not implemented.\n\
2. Something is implemented incorrectly.\n", pc);
	printf("Find this pc value(0x%08x) in the disassembling result to distinguish which case it is.\n\n", pc);
    cp0_w(R_Cause) = (cp0_w(R_Cause) & 0xffffff03) | (0x0A << 2);
    cp0_w(R_EPC) = cpu.pc;
    cp0_w(R_Status) = (cp0_w(R_Status) & 0xfffffffd) | (0x1 << 1);
    if(temu_state == JUMP){//in the delay slot
        cp0_w(R_EPC) -= 4;
        cp0_w(R_Cause) = (cp0_w(R_Cause) & 0x7fffffff) | 0x80000000;
    }
    temu_state = STOP;
    return 0;
}

/* stop temu */
make_helper(temu_trap) {
    char res[128];
    sprintf(res , "temu: HIT GOOD TRAP at $pc = 0x%08x\n\n", cpu.pc);
    sprintf(assembly, "HIT GOOD TEMP");
    strcpy(result_buf , res);
	temu_state = END;

}


