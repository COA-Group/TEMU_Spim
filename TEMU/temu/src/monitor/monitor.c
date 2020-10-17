#include "../TEMU/temu/include/temu.h"
#include "assembly.h"
#define ENTRY_START 0x00000000

char *exec_file;
uint8_t *hw_mem;
CPU_state cpu;

void init_regex();
void init_wp_pool();
void init_ddr3();

FILE *log_fp = NULL;

static void init_log() {
	log_fp = fopen("log.txt", "w");
	Assert(log_fp, "Can not open 'log.txt'");
}

static char* welcome() {
    char* str = "Welcome to TEMU!\nFor help, type \"help\"\n";
    return str;
}

char* init_monitor(int argc, char *argv[]) {
	/* Perform some global initialization */

	/* Open the log file. */
	exec_file = argv[1];
	init_log();

	/* Compile the regular expressions. */
	init_regex();

	/* Initialize the watchpoint pool. */
	init_wp_pool();

	/* Display welcome message. */
    return welcome();
}

static void load_entry() {
	int ret;
    FILE *fp = fopen("../TEMU/entry", "rb");
	Assert(fp, "Can not open 'entry'");
	if(fp == NULL)
		printf("Can not open 'entry'\n");

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	ret = fread((void *)(hw_mem), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}

void restart() {
	/* Perform some initialization to restart a program */

	/* Read the entry code into memory. */
	load_entry();

	/* Set the initial instruction pointer. */
	cpu.pc = ENTRY_START;

	/* Initialize DRAM. */
	init_ddr3();

    init_exec();
}

