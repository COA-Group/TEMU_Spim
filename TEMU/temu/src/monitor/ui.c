#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/temu.h"
#include "../TEMU/temu/include/monitor/watchpoint.h"
#include "outputfunc.h"
#include "ui_buffer.h"

#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
//addadd
WP *new_wp();
void free_wp(WP *wp);
uint32_t expr(char *e, bool *success);
extern WP *head;
//addadd
void cpu_exec(uint32_t);

void display_reg();

static int cmd_c(char *args) {
	cpu_exec(-1);
    display_reg();
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);
//addadd
static int cmd_info(char *args);
static int cmd_w(char *args);
static int cmd_d(char *args);
static int cmd_p(char *args);
static int cmd_x(char *args);
//addadd
static int cmd_si(char *args) {
    // get number
	char *arg = strtok(NULL," ");
    if(arg == NULL){
        cpu_exec(1);
        display_reg();
        return 0;
    }
	int num;
    // input arg into num
    sscanf(arg, "%d", &num);
    if(num < 1){
        strcpy(result_buf , "parameter cannot be less than 1(default is 1)\n");
        //printf("parameter cannot be less than 1(default is 1)\n");
        return 0;
    }
    for(int i = 0;i < num;i++){
        cpu_exec(1);
    }
    display_reg();
    return 0;
}

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
    { "q", "Exit TEMU", cmd_q },
//addadd
	/* TODO: Add more commands */
    { "si", "Single step execution of instruction", cmd_si },
    { "info", "Print Register/WatchPoint", cmd_info },
    { "w", "Set watchpoint", cmd_w},
    { "d", "Delete watchpoint", cmd_d},
    { "x", "Scan buffer", cmd_x},
    { "p", "Expression evaluation", cmd_p}
//addadd
};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;


	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
            if(i == 0)
                strcpy(result_buf , cmd_table[i].name);
            else
                strcat(result_buf , cmd_table[i].name);
            strcat(result_buf , " - ");
            strcat(result_buf , cmd_table[i].description);
            strcat(result_buf , "\n");
        }
        printf("%s ", result_buf);
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
                //printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
                strcpy(result_buf , cmd_table[i].name);
                strcat(result_buf , " - ");
                strcat(result_buf , cmd_table[i].description);
                strcat(result_buf , "\n");
				return 0;
			}
		}
        strcpy(result_buf , "Unknown command '");
        strcat(result_buf , args);
        strcat(result_buf , "'\n");
        //printf("Unknown command '%s'\n", arg);
	}
	return 0;
}
//addadd
//print reg/watchpoint
static int cmd_info(char *args) {
    /* extract the first argument */
  if(args){
    char *arg = strtok(NULL, " ");
    int j = 0;
    //r
    if(strcmp(arg, "r") == 0)
    {
        j += sprintf(result_buf + j , "Register Info:\n");
        display_reg();
    }
    //w
    else if (strcmp(arg, "w") == 0){
        WP *wp = head;
        if(wp == NULL){
            j += sprintf(result_buf + j , "No Watchpoint existed.\n");
        }
        else{
            j += sprintf(result_buf + j , "Watchpoint Info:\n");
            while(wp != NULL){
                j += sprintf(result_buf + j , "WatchPoint:\t%d\t%s\t%u\n", wp->NO, wp->expr, wp->value);
                wp = wp->next;
            }
        }
    }
    else if (strcmp(arg, "help") == 0)
    {
        j += sprintf(result_buf + j , "r -- Print Register Info\n");
        j += sprintf(result_buf + j , "w -- Print Watchpoint Info\n");
        j += sprintf(result_buf + j , "help -- Get Help\n");
    }
    else
    {
        j += sprintf(result_buf + j , "Unknown parameter '%s'\n", arg);
    }
  }
    return 0;
}
//addadd
//Set watchpoint
static int cmd_w(char *args){
    bool success;
    int j = 0;
    uint32_t num;
    if(args){
        num = expr(args, &success);
        if(!success){
            j += sprintf(result_buf + j,"fail to parse expression: %s\n", args);
            return 0;
        }
        WP *wp = new_wp();
        j = sprintf(result_buf + j,"try %s\n", args);
        strcpy(wp->expr , args);
        wp->value = num;
        j += sprintf(result_buf + j ,"set watchpoint successfully!\nwatchpoint no: %d\n", wp->NO);
    }
    return 0;
}

//Delete watchpoint
static int cmd_d(char *args){
    WP *wp = head;
    int j = 0;
    if(args)
    {
        while(wp != NULL){
            if(wp->NO == *args - '0'){
                free_wp(wp);
                j += sprintf(result_buf + j , "Delete watchpoint successfully\n");
                return 0;
            }
        }
        j += sprintf(result_buf + j , "This watchpoint has not been used\n");
    }
    return 0;
}

static int cmd_p(char *args){
    bool success=true;
    uint32_t ret;
    int j = 0;
    if(args)
    {
      ret= expr(args,&success);
      if(success)
      { j += sprintf(result_buf + j , "0x%08x\t%d\n",ret,ret); }
      else
      { j += sprintf(result_buf + j , "Bad expression\n"); }
    }
    return 0;
}


static int cmd_x(char *args){
    int i,k;
    int j = 0;
    int range;
    char *num = strtok(NULL, " ");
    char *exprl;
    if(num != NULL){
          exprl = strtok(NULL, " ");/*start address*/
    }
    bool success;
    success = true;
    range = atoi(num);/*char change to int*/
    //int addr = 0x00000000;
    int addr = expr(exprl, &success);
    if(success == false){
       j += sprintf(result_buf + j , "error expression!\n");
       return 0;
    }
    for(i = 0; i < range; i++){
        if(i%4 == 0)
            j += sprintf(result_buf + j , "addr:%d\t",addr);
        k = mem_read(addr + i * 4, 4);

        j += sprintf(result_buf + j , "0x%08x ", k);
        if(i%4 == 3)
           j += sprintf(result_buf + j , "\n");
        }
        return 0;
}//scan

int ui_solvecmd(char *str) {
    char *str_end = str + strlen(str);

    char *cmd = strtok(str, " ");
    if(cmd == NULL) { return -1; }

    char *args = cmd + strlen(cmd) + 1;
    if(args >= str_end) {
        args = NULL;
    }
    int i;
    for(i = 0; i < NR_CMD; i ++) {
        if(strcmp(cmd, cmd_table[i].name) == 0) {
            if(cmd_table[i].handler(args) < 0) { return -2; }
            break;
        }
    }

    if(i == NR_CMD) {
        strcpy(result_buf , "Unknown command '");
        strcat(result_buf , cmd);
        strcat(result_buf , "'\n");
        return -3;
    }
    return i;
}



