#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/cpu/helper.h"
#include "ui_buffer.h"
#include "assembly.h"
/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 10

int temu_state = STOP;

void exec(uint32_t);

char assembly[80];
char asm_buf[128];
char inst[1024*128];

void print_bin_instr(uint32_t pc) {
	int i;
	int l = sprintf(asm_buf, "%8x:   ", pc);
	for(i = 3; i >= 0; i --) {
		l += sprintf(asm_buf + l, "%02x ", instr_fetch(pc + i, 1));
	}
	sprintf(asm_buf + l, "%*.s", 8, "");
}

/* Simulate how the MiniMIPS32 CPU works. */
void cpu_exec(volatile uint32_t n) {
    strcpy(result_buf , "");
	if(temu_state == END) {
        strcpy(result_buf , "Program execution has ended. To restart the program, exit TEMU and run again.\n");
		return;
	}
	temu_state = RUNNING;

#ifdef DEBUG
	volatile uint32_t n_temp = n;
#endif

    strcpy(inst , "");
	for(; n > 0; n --) {
#ifdef DEBUG
        uint32_t pc_temp = cpu.pc;
        if((n & 0xffff) == 0) {

            fputc('.', stderr);
        }
#endif

		/* Execute one instruction, including instruction fetch,
		 * instruction decode, and the actual execution. */
		exec(cpu.pc);

		cpu.pc += 4;

        print_bin_instr(pc_temp);
        strcat(asm_buf, assembly);
        strcat(inst , asm_buf);
        strcat(inst , "\n");

		/* TODO: check watchpoints here. */

        if(temu_state != RUNNING) {
            return;
        }
	}

    if(temu_state == RUNNING) {
        temu_state = STOP;
    }
}

void init_exec(){
    temu_state = RUNNING;
    volatile uint32_t n = -1;

    for(; n > 0; n --) {
        uint32_t pc_temp = cpu.pc;
        /* Execute one instruction, including instruction fetch,
         * instruction decode, and the actual execution. */
        exec(cpu.pc);

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
