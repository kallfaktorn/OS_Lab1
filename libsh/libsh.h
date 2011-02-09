#ifndef LIBSH_H
#define LIBSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

int count(const char* str, char delm);
char** splitstr(const char* str, char delm);
int free2d(void ** src);
char* concat(const char* str1, const char* str2);
int ex_path(char** argv, char* path);
int execute(char** argv, char** paths);
int array_length(void ** array);
void debug_array(char ** arr);
const char* valid_path(char* command, char** subpaths);
void exec_commands(Pgm* pgm);
char*** tail(char*** array);
int array_length3(void *** array);
int count_pgm(Pgm* pgm);

#endif
