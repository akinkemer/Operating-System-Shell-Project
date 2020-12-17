#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/*512 karakterden fazla girisleri kontrol etme eksik*/
/* strdup ile alinan hafiza geri iade edilmiyor*/
/* fgets null ise ctr d ile cikilmistir onu kullaniciya bildirme eksik*/
#define MAX_CHARACTER 512 /* Bir satirdaki max karakter sayisi*/
#define MAX_COMMANDS (MAX_CHARACTER+1/3)   /* Bir satirdan okunacak max komut sayisi*/
#define MAX_PARAMETERS 3  /* Bir komutun max parametre sayisi*/

char line[MAX_CHARACTER];
char *argvCommands[MAX_COMMANDS + 1]; /* Dizinin sonu belli olsun diye fazladan end eklendigi icin +1*/
char *argvParameters[MAX_PARAMETERS];
int numberOfArgs;

/*
Komut satirindan alinan parametreler ';' ile ayriliyor.
*/
void parseToCommands(char *lineFromInput, char **parsedCommands)
{
  int i = 0;
  const char *token;
  char *toBeParsedLine = strdup(lineFromInput);

  while ((token = strtok_r(toBeParsedLine, ";", &toBeParsedLine)))
  {
    parsedCommands[i++] = strdup(token);
  }
  parsedCommands[i] = "end"; /* Daha sonra dolu indeks sayisini hesaplamak icin
   dolu indekslerden sonraki indekse end degeri ataniyor */
}

/* Ayristirilan komutlar ' ' karakteri ile parametrelerine ayriliyor.*/
void parseToParameters(char *lineFromInput, char **parsedCommands)
{
  int i = 0;
  int j;
  const char *token;
  char *toBeParsedCommands = strdup(lineFromInput);
  while ((token = strtok_r(toBeParsedCommands, " ", &toBeParsedCommands)))
  {
    parsedCommands[i++] = strdup(token);
  }
  /* execvp() NULL olmayan ve bos olan parametre gecildiginde hata veriyor.
  Bu hatayi onlemek icin bos indekslere NULL degeri ataniyor*/
  for (j = i; j < MAX_PARAMETERS; j++)
  {
    parsedCommands[j] = NULL;
  }
}
void executeCommands(char **commands)
{
  pid_t process_id;
  int status;

  if ((process_id = fork()) < 0)
  {
    perror("\e[31mERROR");
    printf("\e[0m");
    exit(1);
  }
  else if (process_id == 0)
  {
    if (execvp(*commands, commands) < 0)
    {
      perror("\e[31mERROR");
      printf("\e[0m");
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
  while (fgets(line, MAX_CHARACTER, file) != NULL)
  {
    line[strlen(line) - 1] = '\0';
    puts(line);
    parseToCommands(line, argvCommands);

    while (strcmp(argvCommands[numberOfArgs], "end") != 0)
    {
      numberOfArgs++;
    }
    int i;
    for (i = 0; i < numberOfArgs; i++)
    {
      if (strcmp(argvCommands[i], "quit") == 0)
      {
        printf("\e[32m(quit komutu ile cikis yaptiniz)\e[0m\n");
        fclose(file);
        exit(EXIT_SUCCESS);
      }
      if (strcmp(argvCommands[i], " ") == 0)
      {
        fprintf(stderr, "\e[31mUyari:bosluk karakteri gecersiz bir komuttur! \e[0m\n");
      }
      else
      {
        parseToParameters(argvCommands[i], argvParameters);
        executeCommands(argvParameters);
      }
    }
    numberOfArgs = 0;
  }
  fclose(file);
}
void runInteractiveMode()
{
  while (1)
  {
    printf("prompt>");
    if (fgets(line, MAX_CHARACTER, stdin) == NULL)
    {
      exit(EXIT_SUCCESS);
    }

    line[strlen(line) - 1] = '\0';

    parseToCommands(line, argvCommands);

    while (strcmp(argvCommands[numberOfArgs], "end") != 0)
    {
      numberOfArgs++;
    }
    int i;
    for (i = 0; i < numberOfArgs; i++)
    {
      if (strcmp(argvCommands[i], "quit") == 0)
      {
        printf("\e[32m(Basariyla cikis yaptiniz)\e[0m\n");
        exit(EXIT_SUCCESS);
      }
      if (strcmp(argvCommands[i], " ") == 0)
      {
        fprintf(stderr, "\e[31mUyari:bosluk karakteri gecersiz bir komuttur! \e[0m\n");
      }
      else
      {
        parseToParameters(argvCommands[i], argvParameters);
        executeCommands(argvParameters);
      }
    }

    printf("\n");
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
      perror("\e[31mFILE ERROR");
      printf("\e[0m");
      exit(EXIT_FAILURE);
    }
    else
    {
      runBatchMode(file);
    }
  }
  else if (argc == 1)
  {
    runInteractiveMode();
  }
  else
  {
    fprintf(stderr, "\e[31m ERROR: for using batch mode [$./bin/shell fileName.txt]\n");
    fprintf(stderr, "\e[31m ERROR: for using interactive mode [$./bin/shell ] \e[0m \n");
  }
}
