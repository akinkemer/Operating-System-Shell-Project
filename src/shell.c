#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CHARACTER 512                /* Bir satirdaki max karakter sayisi*/
#define MAX_COMMANDS (MAX_CHARACTER / 3) /* Bir satirdan okunacak max komut sayisi*/
#define MAX_PARAMETERS 3                 /* Bir komutun max parametre sayisi*/

char line[MAX_CHARACTER + 2];/*Fazla karakter girdisini kontrol etmek amacıyla fazladan okuma yapmak icin*/
char *argvCommands[MAX_COMMANDS + 1];/*Dizinin sonunu belirlemek amacıyla fazladan indeks eklemek icin*/
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

/* Ayristirilan komutlar bosluk karakteri ile parametrelerine ayriliyor.*/
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
  /* execvp() NULL olmayan ve bos olan parametre gecildiginde hata verir.
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
void freeAllocatedMemories(){
  int i;
  for(i=0;i<MAX_COMMANDS+1;i++){
    if(argvCommands[i]==NULL){
      free(argvCommands[i]);
    }
  }
  for(i=0;i<MAX_PARAMETERS;i++){
    if(argvParameters[i]==NULL){
      free(argvParameters[i]);
    }
  }


}
void runBatchMode(FILE *file)
{
  while (fgets(line, MAX_CHARACTER + 2, file) != NULL)
  {
    if (strlen(line) > MAX_CHARACTER)
    {
      fprintf(stderr,
              "\e[31m(Girilen karakter sayisi %d'yi asiyor. Fazla karakterler isleme alinmayacaktir)\e[0m\n",
              MAX_CHARACTER);
      line[MAX_CHARACTER - 1] = '\0';
    }
    else
    {
      line[strlen(line) - 1] = '\0';
    }

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
        freeAllocatedMemories();
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
  freeAllocatedMemories();
  fclose(file);
}
void runInteractiveMode()
{
  while (1)
  {
    printf("prompt>");
    if (fgets(line, MAX_CHARACTER + 2, stdin) == NULL)
    {
      printf("\e[32m(Ctrl-D ile cikis yaptiniz)\e[0m\n");
      freeAllocatedMemories();
      exit(EXIT_SUCCESS);
    }
    if (strlen(line) > MAX_CHARACTER)
    {
      fprintf(stderr,
              "\e[31m(Girilen karakter sayisi %d'yi asiyor. Fazla karakterler isleme alinmayacaktir)\e[0m",
              MAX_CHARACTER);
      line[MAX_CHARACTER - 1] = '\0';
    }
    else
    {
      line[strlen(line) - 1] = '\0';
    }

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
        freeAllocatedMemories();
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
      freeAllocatedMemories();
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
    fprintf(stderr, "\e[31mERROR: for using batch mode \e[33m[$./bin/shell fileName]\e[0m\n");
    fprintf(stderr, "\e[31mERROR: for using interactive mode \e[33m[$./bin/shell ] \e[0m \n");
  }
}
