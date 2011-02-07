#ifndef LIBSH_H
#define LIBSH_H

int count(const char* str, char delm);
char** splitstr(const char* str, char delm);
int free2d(void ** src);
char* concat(const char* str1, const char* str2);
int ex_path(const char * command, const char*  argv, const char* path);
int execute(const char* command, const char* argv, char** paths);

#endif
