#include "sig.h"

void sig_init()
{
    signal(SIGINT, ctrl_c);
}

void ctrl_c()
{
    printf("Ctrl-C%i\n", CHILDPID);
    kill(CHILDPID, SIGABRT);
}
