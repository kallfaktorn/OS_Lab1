#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsh.h"

//Max length of a path.
#define MAX 100
int main(int argc, char* argv)
{
    char * path = getenv("PATH");
    printf("%s\n",path);

    char** subpaths;
    subpaths = splitstr(path, ':');


    //int i = 0;
    /*while(subpaths[i])
    {
        printf("%s\n", subpaths[i]);
        i++;
    } */

    execute("ls", "", subpaths);

    free2d((void**)subpaths);
    return 0; 
}
