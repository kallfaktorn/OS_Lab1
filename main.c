#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "libsh.h"

int main(int argc, char** argv)
{
    char * path = getenv("PATH");

    char** subpaths;
    subpaths = splitstr(path, ':');

    int fd[2];
    pipe(fd);
    
    char buf[256];
    
    if(fork() == 0) // child
    {    
        dup2(0, fd[1]);
		close(1);
        execute("echo", "test", subpaths);
    } 
    else 
    {
        dup2(1, fd[0]);
        close(0);
        
        while(read(fd[0], buf, 256) > 0 ) {
            printf("OUTPUT: %s", buf);
        }
    }

    free2d((void**)subpaths);
    return 0; 
}
