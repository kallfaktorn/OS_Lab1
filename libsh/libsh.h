#ifndef LIBSH_H
#define LIBSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int run(char ** argv, int background);
int count(const char* str, char delm);
char** splitstr(const char* str, char delm);
int free2d(void ** src);
char* concat(const char* str1, const char* str2);
int ex_path(char** argv, char* path);
int execute(char** argv, char** paths);
int array_length(void ** array);
void debug_array(char ** arr);

#endif
