#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include "../TEMU/temu/include/cpu/helper.h"
// run the prog first to get its assembly code
char assembly[80];
char asm_buf[128];
char inst[1024*128];

void print_bin_instr(uint32_t pc);
void init_exec();

//void decode_imm_type(uint32_t instr);
//void decode_r_type(uint32_t instr);

void init_decode();

#endif // ASSEMBLY_H
