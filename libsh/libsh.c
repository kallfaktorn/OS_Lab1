#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsh.h"

int execute(const char* command, const char* argv, char** paths)
{
    int i = 0;
    int ret = -1;
    while(paths[i])
    {
        ret = ex_path(command, argv, paths[i]); 
        if (ret == 0)
        {
            //printf("%i\n",ret);
            break;
        }
        i++;
    }
    
    return ret;
}
    
int ex_path(const char* command, const char* argv, const char* path)
{
    const char* cmd;
    cmd = concat(path, "/");
    cmd = concat(cmd, command);
    printf("%s\n", cmd);
    char * arg[] = { "ls" };
    return execvp(cmd, arg);
}
                                    
int count(const char* str, char delm)
{
    int i = 0;
    while(*(str++) != 0)
        if((*str) == delm)
            i++;
    return i;
}

char* concat(const char* str1, const char* str2)
{
    char* ret;
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    ret = calloc(len1+len2, sizeof(char));
    strcpy(ret,str1);
    strcat(ret,str2);

    return ret;
}

char** splitstr(const char* str, char delm)
{
    char c;
    size_t maxlen = strlen(str);
    char** retarr = calloc(count(str, ':')+1, sizeof(char) * maxlen);
    char* substr = calloc(maxlen, sizeof(char));
    int i = 0;
    int j = 0;

    while(c = *(str++))
    {
        if(c == delm)
        {
            retarr[i] = calloc(maxlen, sizeof(char));
            strcpy(retarr[i], substr);
            i++;
            free(substr);
            substr = calloc(maxlen, sizeof(char));
            j = 0;
        }
        else
        {
            substr[j] = c;
            j++;
        }
    }
    free(substr);
    
    return retarr;
}

int free2d(void ** src)
{
    int i = 0;
    while(src[i])
    {
        free(src[i]);
        i++;
    }

    free(src);

    return 0;
}
                                         
