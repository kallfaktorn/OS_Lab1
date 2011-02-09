#ifndef SIG_H
#define SIG_H
#include<signal.h>
#include<unistd.h>

static int CHILDPID = -1;

void sig_init();
void ctrl_c();

#endif
