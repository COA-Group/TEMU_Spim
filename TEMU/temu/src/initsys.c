#include "outputfunc.h"
#include "ui_buffer.h"
char* init_monitor(int, char *[]);
void restart();

char result_buf[MAX_HELP * MAX_LEN];
char cmd_inst[MAX_INST * MAX_LEN];
char ui_inst[MAX_INST * MAX_LEN];
char reg_buf[REG * REG_INFO_LEN];
char cp0_buf[REG * REG_INFO_LEN / 2];

char* initSys(int argc, char *argv[]) {

    char* ret = init_monitor(argc, argv);

	restart();

    return ret;
}
