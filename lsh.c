#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parse.h"

/*
 * Prototypes
 */

void PrintCommand(int, Command *);
void PrintPgm(Pgm *);
void stripwhite(char *);

/* When non-zero, this global means the user is done using this program. */
int done = 0;

/*
 * Name: main
 *
 * Desc: Gets the ball rolling...
 *
 */
int main(void)
{
    Command cmd;
    int n;

    while (! done) {

	char *line;

	line = readline("@ ");

	if (!line)
	{
	    /* Encountered EOF at top level */
	    done = 1;
	}
	else
	{
	    /*
	     * Remove leading and trailing whitespace from the line
	     * Then, if there is anything left, add it to the history list
	     * and execute it.
	     */
	    stripwhite(line);

	    if(*line)
	    {
		add_history(line);
		/* execute it */
		n = parse(line, &cmd);
		PrintCommand(n, &cmd);
	    }
	}
	
	if(line)
	    free(line);
    }
    return 0;
}

/*
 * Name: PrintCommand
 *
 * Desc: Prints a Command structure as returned by parse on stdout.
 *
 */
void
PrintCommand (int n, Command *cmd)
{
    printf("Parse returned %d:\n", n);
    printf("   stdin : %s\n", cmd->rstdin  ? cmd->rstdin  : "<none>" );
    printf("   stdout: %s\n", cmd->rstdout ? cmd->rstdout : "<none>" );
    printf("   bg    : %s\n", cmd->bakground ? "yes" : "no");
    PrintPgm(cmd->pgm);
}

/*
 * Name: PrintPgm
 *
 * Desc: Prints a list of Pgm:s
 *
 */
void
PrintPgm (Pgm *p)
{
    if (p == NULL)
	return;
    else
    {
	char **pl = p->pgmlist;

	/* The list is in reversed order so print
         * it reversed so get right :-)
         */
	PrintPgm(p->next);
	printf("    [");
        while (*pl)
	    printf("%s ", *pl++);
	printf("]\n");
    }
}

/*
 * Name: stripwhite
 *
 * Desc: Strip whitespace from the start and end of STRING.
 */
void
stripwhite (char *string)
{
    register int i = 0;
    while (whitespace( string[i] ))
	i++;
    if (i)
	strcpy (string, string + i);

    i = strlen( string ) - 1;
    while (i> 0 && whitespace (string[i]))
	i--;
    string [++i] = '\0';
}
