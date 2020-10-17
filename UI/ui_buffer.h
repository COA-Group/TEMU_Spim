#ifndef UI_BUFFER_H
#define UI_BUFFER_H
#define MAX_LEN 128
#define MAX_HELP 16
#define MAX_INST 1024

//all strings used in ui is here

char result_buf[MAX_HELP * MAX_LEN];
char cmd_inst[MAX_INST * MAX_LEN];
char ui_inst[MAX_INST * MAX_LEN];

#endif // UI_BUFFER_H
