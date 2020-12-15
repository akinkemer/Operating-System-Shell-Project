#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAXCOMMANDS 64
#define MAXPARAMETERS 3

void parseToCommands(char *line, char **argv)
{
  int i = 0;
  const char *token;
  char *rest = strdup(line);

  while ((token = strtok_r(rest, ";", &rest)))
  {
    argv[i] = strdup(token);
    i++;
  }
  argv[i] = "eof";
}
void parseToParameters(char *line, char **argv)
{
  int i = 0;
  const char *token;
  char *rest = strdup(line);
  while ((token = strtok_r(rest, " ", &rest)))
  {
    argv[i] = strdup(token);
    i++;
  }
  for(i;i<MAXPARAMETERS;i++){
    argv[i]=NULL;
  }
}
void execute(char **argv)
{
  pid_t pid;
  int status;

  if ((pid = fork()) < 0)
  {
    perror("ERROR:");
    exit(1);
  }
  else if (pid == 0)
  {
    if (execvp(*argv, argv) < 0)
    {
      perror("ERROR:");
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
  int i = 0;
  int numberOfArgs;
  char line[512];
  char *argvCommands[MAXCOMMANDS + 1];
  char *argvParameters[MAXPARAMETERS];
  char **executingCommands;

  while (1)
  {
    printf("prompt> ");
    fgets(line, 512, stdin);

    line[strlen(line) - 1] = '\0';

    printf("\n");

    parseToCommands(line, argvCommands);

    if (strcmp(argvCommands[0], "quit") == 0)
    {
      exit(0);
    }
    while (strcmp(argvCommands[numberOfArgs], "eof") != 0)
    {
      numberOfArgs++;
    }
    int i;
    int j;
    for (i = 0; i < numberOfArgs; i++)
    {
      parseToParameters(argvCommands[i], argvParameters);
      execute(argvParameters);
    }
    numberOfArgs = 0;
  }
}