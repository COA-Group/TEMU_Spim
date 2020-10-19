#include "../TEMU/temu/include/monitor/monitor.h"
#include "../TEMU/temu/include/temu.h"
#include "outputfunc.h"
#include "ui_buffer.h"

#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

void display_reg();

/* We use the `readline' library to provide more flexibility to read from stdin. */

/*
 * char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(temu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}
*/

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
    // get number
	char *arg = strtok(NULL," ");
    if(arg == NULL){
        cpu_exec(1);
        return 0;
    }
	int num;
    // input arg into num
    sscanf(arg, "%d", &num);
    if(num < 1){
        printf("parameter cannot be less than 1(default is 1)\n");
        return 0;
    }
    for(int i = 0;i < num;i++){
        cpu_exec(1);
    }
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

	/* TODO: Add more commands */
	{ "si", "Single step execution of instruction", cmd_si }

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
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

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



