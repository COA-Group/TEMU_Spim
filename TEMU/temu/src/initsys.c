#include "outputfunc.h"

char* init_monitor(int, char *[]);
void restart();

char* initSys(int argc, char *argv[]) {

    char* ret = init_monitor(argc, argv);

	restart();

    return ret;
}
