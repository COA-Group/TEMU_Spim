#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__
#define EXPR_MAX_LEN 128
#include "../TEMU/temu/include/common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */
    //addadd
    char expr[EXPR_MAX_LEN];
    uint32_t value;

} WP;

#endif
