#ifndef LIBSH_H
#define LIBSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

typedef struct cmd {
    const char *fullpath;
    char **argv;
} Cmd;

char** splitstr(const char* str, char delm);
int free2d(void ** src);
char* concat(const char* str1, const char* str2);
int execute(char** argv, char** paths);
int array_length(void ** array);
const char* valid_path(char* command, char** subpaths);
void exec_commands(Pgm* pgm, int background);
int array_length3(void *** array);
int validate(Pgm* pgm, char **subpaths);

#endif
