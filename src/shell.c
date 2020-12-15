#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void parse(char *line, char **argv)
{
  int in = 0;      /* simple in-word flag 0-false/1-true */
  size_t n = 0;    /* counter to protect splitInput bounds */
  char *sp = line; /* start-pointer initialized to userInput */

  while (n < 64 - 1)
  { /* loop while pointers remain unfilled */
    /* if at end, is whitespace or a delimiter */
    if (!*line || isspace(*line) || *line == ';')
    {
      if (in)
      {                 /* if in word */
        argv[n++] = sp; /* set pointer to start-pointer */
        argv[n] = NULL; /* set next pointer NULL */
      }
      in = 0;    /* reset in flag zero */
      if (*line) /* if space or delim, nul-terminate */
        *line = 0;
      else      /* otherwise */
        return; /* at end-of-string */
    }
    else
    { /* normal char */
      if (!in)
      {            /* if not in-word */
        sp = line; /* set start-pointer to 1st good char */
        in = 1;    /* set in-word flag true */
      }
    }
    line++; /* advance to next char */
  }
}

  void execute(char **argv)
  {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    { /* fork a child process           */
      printf("*** ERROR: forking child process failed\n");
      exit(1);
    }
    else if (pid == 0)
    { /* for the child process:         */
      if (execvp(*argv, argv) < 0)
      { /* execute the command  */
        printf("*** ERROR: exec failed\n");
        exit(1);
      }
    }
    else
    {                              /* for the parent:      */
      while (wait(&status) != pid) /* wait for completion  */
        ;
    }
  }

  void main(void)
  {
    char line[512]; /* the input line                 */
    char *argv[64]; /* the command line argument      */

    while (1)
    {                          /* repeat until done ....         */
      printf("prompt> ");      /*   display a prompt             */
      fgets(line, 512, stdin); /*   read in the command line     */
      printf("\n");
      parse(line, argv);                /*   parse the line               */
      if (strcmp(argv[0], "quit") == 0) /* is it an "exit"?     */
        exit(0);                        /*   exit if it is                */
      execute(argv);                    /* otherwise, execute the command */
    }
  }
