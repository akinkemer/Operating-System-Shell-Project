#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CHARACTER 512 /* Bir satirdaki max karakter sayisi*/
#define MAX_COMMANDS 64   /* Bir satirdan okunacak max komut sayisi*/
#define MAX_PARAMETERS 3  /* Bir komutun max parametre sayisi*/

char line[MAX_CHARACTER];
char *argvCommands[MAX_COMMANDS + 1];
char *argvParameters[MAX_PARAMETERS];
int numberOfArgs;

/*
Komut satirindan alinan parametreler ';' ile ayriliyor.
*/
void parseToCommands(char *line, char **parsedCommands)
{
  int i = 0;
  const char *token;
  char *toBeParsedLine = strdup(line);
  while ((token = strtok_r(toBeParsedLine, ";", &toBeParsedLine)))
  {
    parsedCommands[i] = strdup(token);
    i++;
  }
  parsedCommands[i] = "eof"; /* Daha sonra dolu indeks sayisini hesaplamak icin
   dolu indekslerden sonraki indekse eof degeri ataniyor */
}

/* Ayristirilan komutlar ' ' karakteri ile parametrelerine ayriliyor.*/
void parseToParameters(char *line, char **parsedCommands)
{
  int i = 0;
  const char *token;
  char *toBeParsedCommands = strdup(line);
  while ((token = strtok_r(toBeParsedCommands, " ", &toBeParsedCommands)))
  {
    parsedCommands[i] = strdup(token);
    i++;
  }
  /* execvp() NULL olmayan ve bos olan parametre gecildiginde hata veriyor.
  Bu hatayi onlemek icin bos indekslere NULL degeri ataniyor*/
  for (i; i < MAX_PARAMETERS; i++)
  {
    parsedCommands[i] = NULL;
  }
}
void executeCommands(char **commands)
{
  pid_t process_id;
  int status;

  if ((process_id = fork()) < 0)
  {
    perror("ERROR:");
    exit(1);
  }
  else if (process_id == 0)
  {
    if (execvp(*commands, commands) < 0)
    {
      perror("ERROR:");
      exit(1);
    }
  }
  else
  {
    while (wait(&status) != process_id)
    {
    };
  }
}
void runBatchMode(FILE *file)
{
  while (fgets(line, MAX_CHARACTER, stdin))
  {
    line[strlen(line) - 1] = '\0';
    parseToCommands(line, argvCommands);

    while (strcmp(argvCommands[numberOfArgs], "eof") != 0)
    {
      numberOfArgs++;
    }
    int i;
    for (i = 0; i < numberOfArgs; i++)
    {
      if (strcmp(argvCommands[0], "quit") == 0)
      {
        exit(0);
      }
      parseToParameters(argvCommands[i], argvParameters);
      executeCommands(argvParameters);
    }
    numberOfArgs = 0;
  }
  fclose(file);
}
void runShellMode()
{
  while (1)
  {
    printf("prompt> ");
    fgets(line, MAX_CHARACTER, stdin);

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
    for (i = 0; i < numberOfArgs; i++)
    {
      parseToParameters(argvCommands[i], argvParameters);
      executeCommands(argvParameters);
    }
    numberOfArgs = 0;
  }
}

int main(int argc, char **argv)
{
  FILE *file;
  if (argc == 2)
  {
    if ((file = fopen(argv[1], "r")) == NULL)
    {
      perror("FILE ERROR:");
      exit(1);
    }
    else
    {
      runBatchMode(file);
      exit(0);
    }
  }
  else if (argc == 1)
  {
    runShellMode();
  }
  else
  {
    puts("ERROR: for using batch mode [$shell fileName.txt]");
    puts("for using batch mode [$shell fileName.txt]");
  }
}