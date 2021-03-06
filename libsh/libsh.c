#include "libsh.h"


pid_t pid = -1;
int background = -1;

void run(Pgm* pgm, char **subpaths)
{
    if(pgm->next == NULL)
    {
		const char * fullpath = valid_path(pgm->pgmlist[0], subpaths);
		free2d((void**)subpaths);
		
        if (execvp(fullpath, pgm->pgmlist) < 0) {     /* execute the command  */
             printf("*** ERROR: exec failed1 %s\n", pgm->pgmlist[0]);
             exit(1);
        }
    }
    else
    {
        int fd[2];
        pid_t pid2;
        
        pipe(fd);
        pid2 = fork();
        if(pid2 == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            run(pgm->next, subpaths);
        }
        else if(pid2 > 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
						const char * fullpath = valid_path(pgm->pgmlist[0], subpaths);
						free2d((void**)subpaths);
			
	        if (execvp(fullpath, pgm->pgmlist) < 0) {     /* execute the command  */
	             printf("*** ERROR: exec failed: %s\n", pgm->pgmlist[0]);
	             exit(1);
	        }
        }
    }
    
    return;
}


void exec_commands(Command *cmd)
{

    char* path = getenv("PATH");
    char** subpaths = splitstr(path, ':');

	if(validate(cmd->pgm, subpaths) == 1) {
		
		if ((pid = fork()) == -1) {
			perror("fork error");
			exit(EXIT_FAILURE);
		}

		if(pid == 0) // child
    {
			if(cmd->rstdin != NULL) {
				freopen(cmd->rstdin, "r", stdin);
			}
			if(cmd->rstdout != NULL) {
				freopen(cmd->rstdout, "w", stdout);
			}
			run(cmd->pgm, subpaths);
    }
    else 
    {	
			background = cmd->bakground;
			if(cmd->bakground != 1) {
				int status;
				waitpid(pid, &status, 0);
			} else {
				printf("[%i]\n", pid);
			}

			pid = -1;
			free2d((void**)subpaths);
    }
		
	} else {
		printf("Command not found\n");
		free2d((void**)subpaths);		
	}
}

int validate(Pgm* pgm, char **subpaths) {
	Pgm *p = pgm;
	do {
		if(valid_path(p->pgmlist[0], subpaths) == NULL) {
			return 0;
		}
	} while((p = p->next) != NULL);
	
	return 1;
}

const char* valid_path(char* command, char** subpaths)
{
    int i = 0;
    char* fullpath = NULL;
    
    while(subpaths[i])
    {
        fullpath = concat(subpaths[i], "/");
        fullpath = concat(fullpath, command);
		
		struct stat buf;
		int ret = stat (fullpath, &buf);
		
		if (ret != -1 && buf.st_mode & S_IXUSR) {
			return fullpath;
		}
		i++;
    }
    return NULL;
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
    char** retarr = calloc(count(str, ':')+2, sizeof(char) * maxlen);
    char* substr = calloc(maxlen, sizeof(char));
    int i = 0;
    int j = 0;
    int k = 0;
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
        k++;
    }
    
    retarr[k-1] = NULL;
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

void leave(int sig) {
	if(sig != SIGCHLD && background == 0 && pid > 0) {
		kill(pid, sig);
		pid = -1;
	}
}

void childHandler(int sig) {
	int status;
	wait(&status);
}