#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAXCOMMAND 64
#define MAXPARAMETERS 3

void parse(char *line, char **argv,const char* ch)
{
  int i = 0;
  char *token;
  char *rest = line;

  while ((token = strtok_r(rest, ch, &rest)))
  {
    strcpy(argv[i++], token);
  }
}
void execute(char **argv)
{
  pid_t pid;
  int status;

  if ((pid = fork()) < 0)
  {
    printf("ERROR: forking child process failed\n");
    exit(1);
  }
  else if (pid == 0)
  {
    if (execvp(*argv, argv) < 0)
    {
      printf("ERROR: exec failed\n");
      exit(1);
    }
  }
  else
  {
    while (wait(&status) != pid)
    {
    };
  }
}

int main(int argc, char **argv)
{
  char line[512];
  char *argvCommands[MAXCOMMAND+1];
  char *argvParameters[MAXPARAMETERS+1];

  while (1)
  {
    printf("prompt> ");
    fgets(line, 512, stdin);

    line[strlen(line) - 1] = '\0';

    printf("\n");

    parse(line, argvCommands,";");

    if (strcmp(argvCommands[0], "quit") == 0)
    {
      exit(0);
    }
  }
}