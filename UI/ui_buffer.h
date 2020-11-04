#ifndef UI_BUFFER_H
#define UI_BUFFER_H
#define MAX_LEN 128
#define MAX_HELP 16
#define MAX_INST 1024
#define REG 32
#define REG_INFO_LEN 64
//all strings used in ui is here

char result_buf[MAX_HELP * MAX_LEN];
char cmd_inst[MAX_INST * MAX_LEN];
char ui_inst[MAX_INST * MAX_LEN];
char reg_buf[REG * REG_INFO_LEN];

#endif // UI_BUFFER_H
