#ifndef __MONITOR_H__
#define __MONITOR_H__

enum { STOP, RUNNING, END, JUMP };
extern int temu_state;

void init_monitor(int, char *[]);
void restart();

#endif
