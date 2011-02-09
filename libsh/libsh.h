#ifndef LIBSH_H
#define LIBSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

char** splitstr(const char* str, char delm);
int free2d(void ** src);
char* concat(const char* str1, const char* str2);
int array_length(void ** array);
const char* valid_path(char* command, char** subpaths);
void exec_commands(Command *cmd);
int validate(Pgm* pgm, char **subpaths);
void read_from_pipe (int file);
void write_to_pipe (int file, char *from_filename);
void run(Pgm* pgm, char **subpaths);

#endif
