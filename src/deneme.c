#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAXCMD 64

void parseToParameters(char *line, char **argv)
{
  const char s[2] = " ";
  int i = 0;
  *argv = NULL;
  char *token;

  token = strtok(line, s);

  while (token != NULL)
  {
    argv[i] = token;
    printf("par:%s\n",argv[i]);
    token = strtok(NULL, s);
    i++;
  }
  for (i; i < 3; i++)
  {
    argv[i] = NULL;
  }
}
void parseToCommands(char *line, char **argv)
{
  const char s[2] = ";";
  int i = 0;
  *argv = NULL;
  char *token;

  token = strtok(line, s);

  while (token != NULL)
  {
    argv[i] = token;
    printf("cmd:%s\n",argv[i]);
    token = strtok(NULL, s);
    i++;
  }
  for (i; i < MAXCMD; i++)
  {
    argv[i] = NULL;
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
  char line[512];
  char *argvCommands[MAXCMD];
  char *argvParameters[3];

  while (1)
  {
    printf("prompt> ");
    fgets(line, 512, stdin);
    printf("\n");
    parseToCommands(line, argvCommands);
    if (strcmp(argvCommands[0], "quit") == 0)
    {
      exit(0);
    }

    int i;
    for (i = 0; i < MAXCMD; i++)
    {
      if (argvCommands[i] != NULL)
      {
        parseToParameters(argvCommands[i], argvParameters);
        execute(argvParameters);
      }
    }
  }
}
