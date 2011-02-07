#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsh/libsh.h"

int main(int argc, char* argv)
{
    char * path = getenv("PATH");
    printf("%s\n",path);

    char** subpaths;
    subpaths = splitstr(path, ':');

    execute("ls", "", subpaths);

    free2d((void**)subpaths);
    return 0; 
}
