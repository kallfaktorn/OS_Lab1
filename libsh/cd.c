#include "cd.h"

int execd(Command* cmd)
{
    if(strcmp(cmd->pgm->pgmlist[0], "cd") == 0)
    {
        //Command: cd
        if(cmd->pgm->pgmlist[1] == NULL)
            chdir(getenv("HOME"));
        
        //Command: cd arg1 arg2
        else if(cmd->pgm->pgmlist[2] != NULL)
            printf("Too many arguments.\n");
        
        //Command: cd arg1
        else
            chdir(cmd->pgm->pgmlist[1]);
            
        return 1;
    }
    
    return 0;
}
