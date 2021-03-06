#ifndef __REG_H__
#define __REG_H__

#include "../TEMU/temu/include/common.h"

enum { R_ZERO, R_AT, R_V0, R_V1, R_A0, R_A1, R_A2, R_A3, R_T0, R_T1, R_T2, R_T3, R_T4, R_T5, R_T6, R_T7, R_S0, R_S1, R_S2, R_S3, R_S4, R_S5, R_S6, R_S7, R_T8, R_T9, R_K0, R_K1, R_GP, R_SP, R_FP, R_RA };

typedef struct {
     union {
        union {
            uint32_t _32;
            uint16_t _16;
            uint8_t _8;
        } gpr[32];

        /* Do NOT change the order of the GPRs' definitions. */

        uint32_t zero, at, v0, v1, a0, a1, a2, a3;
        uint32_t t0, t1, t2, t3, t4, t5, t6, t7;
        uint32_t s0, s1, s2, s3, s4, s5, s6, s7;
        uint32_t t8, t9, k0, k1, gp, sp, fp, ra;
     };
	uint32_t pc;
	uint32_t hi, lo;
    uint32_t next_PC;
} CPU_state;

enum { R_Index, R_Random, R_EntryLo0, R_EntryLo1, R_Context, R_PageMask, R_Wired, R_Reserved0,
       R_BadVAddr, R_Count, R_EntryHi, R_Compare, R_Status, R_Cause, R_EPC, R_PRId};

typedef struct {
    union{
        uint32_t cp0_gpr[16];
        uint32_t index,    random, entrylo0, entrylo1, context, pagemask, wired, reserved0;
        uint32_t badvaddr, count,  entryhi,  compare,  status,  cause,    epc,   prid;
    };
} CP0_regs;

extern CPU_state cpu;
extern CP0_regs cp0;

static inline int check_reg_index(int index) {
    assert(index >= 0 && index <= 31);
	return index;
}

static inline int check_cp0_index(int index) {
    assert(index >= 0 && index <= 15);
    return index;
}
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_h(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index)]._8)
#define cp0_w(index) (cp0.cp0_gpr[check_cp0_index(index)])

extern const char* regfile[];
extern const char* cp0file[];

#endif
