#include "libsh.h"

/*void run(Pgm *pgm, int background, int input) {
	
	char * path = getenv("PATH");

    char** subpaths = splitstr(path, ':');

	pid_t pid;
	int status;
	
	if ((pid = fork()) == -1) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}

    const char* fullpath = valid_path(pgm->pgmlist[0], subpaths);

    execvp(fullpath, pgm->pgmlist);

    if(fullpath != NULL)
    {
    }
    
    if(pid == 0) // child
    {    

		if(pgm->next != NULL) {
            int fd[2];
            pipe(fd);
            dup2(fd[0], input);
            //dup2(fd[1], Ifd[1]);

			run(pgm->next, 0, fd[1]);			
		}

		if(execute(pgm->pgmlist, subpaths) == -1) {
			fprintf(stderr, "Command not found.\n");
		}
    } else {
		
		if(background != 1)
			wait(&status);
		
		free2d((void**)subpaths);
    }
}
*/

void run(char **commands[], int* fd)
{
    char** command = commands[0];
    char*** rest = tail(commands);
    
    if(array_length3((void ***)rest) == 0)
    {
        execvp(command[0], command);
    }
    else if(array_length3((void ***)rest) > 0)
    {
        int new_fd[2];
        int pid;
        
        pipe(new_fd);
        pid = fork();
        if(pid == 0)
        {
            
            dup2(new_fd[1], STDOUT_FILENO);
            close(new_fd[0]);
            run(rest, new_fd);
        }
        else if(pid > 0)
        {
            dup2(new_fd[0], STDIN_FILENO);
            close(new_fd[1]);
            execvp(command[0], command);
        }
    }
    
    return;
}


const char*** exec_commands(Pgm* pgm)
{
    char* path = getenv("PATH");
    char** subpaths = splitstr(path, ':');

    int size = count_pgm(pgm);
    int cmdelements = 3;
    int stringlength = 100;
    
    char *** commands = calloc(size, sizeof(char) * cmdelements * stringlength);
    Pgm* p = pgm;

    int i;
    for(i=0; i < size; i++)
    {
        char** args = p->pgmlist;
        const char* fullpath = valid_path(p->pgmlist[0], subpaths);
        if(fullpath == NULL) return NULL;
        commands[i][0] = fullpath;
        commands[i][1] = p->pgmlist;
        p = p->next;
    }

    run(commands, NULL);
}
    
int count_pgm(Pgm* pgm)
{       
    if(pgm == NULL) return 0;
    else return 1 + count_pgm(pgm->next);
}

const char* valid_path(char* command, char** subpaths)
{
    FILE* fp = NULL;
    ret = NULL;
    int i = 0;
    while(subpaths[i])
    {
        fullpath = concat(subpaths[i], "/");
        fullpath = concat(fullpath, command);
        fp = fopen(fullpath);
        if(fp != NULL) fclose(fp), return fullpath;
        fclose(fp);
    }
    return NULL;
}
        

int execute(char** argv, char** paths)
{
	// try to execute the command
    int i = 0;
    int ret = -1;
    while(paths[i])
    {
        ret = ex_path(argv, paths[i]); 
        if (ret == 0)
            break;
        i++;
    }

    return ret;
}
    
int ex_path(char** argv, char* path)
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

char*** tail(char*** array)
{
    int new_length = array_length((void ***)array)-1;
    int cmdelements = 3;
    int stringlength = 100;
    char *** ret = calloc(new_length, sizeof(char) * cmdelements * stringlength);
    int i = 0;
    for(i; i < new_length; i++)
    {
        ret[i] = array[i+1];
    }
    return ret;
}

int array_length3(void *** array) {
	int i = 0;
	while(array[i])
		i++;
		
	return i;
}

