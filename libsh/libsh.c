#include "libsh.h"

int run(char ** argv) {
	
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
        execute(argv, subpaths);
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

	return 1;
}

int execute(const char** argv, char** paths)
{
	// try to execute the command
    i = 0;
    int ret = -1;
    while(paths[i])
    {
		
        ret = ex_path(argv, paths[i]); 
        if (ret == 0)
            break;
        i++;
    }

	free(argv);
    
    return ret;
}
    
int ex_path(char** argv, const char* path)
{
    const char* cmd;
    cmd = concat(path, "/");
    cmd = concat(cmd, argv[0]);
    return execvp(cmd, argv);
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

    while((c = *(str++)) != '\0')
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

int array_length(void ** array) {
	int i = 0;
	while(array[i])
		i++;
		
	return i;
}
                                         
void debug_array(char ** arr) {
	int i = 0;
	while(arr[i])
		fprintf(stderr, "debug: %s", arr[i++]);
}