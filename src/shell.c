#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_input.h>

int main(int argc, char **argv)
{
  char input[512];
  printf("prompt> ");
  while (strncmp(input, "quit", 4) != 0)
  {
    fgets(input,512,stdin);
    printf("prompt> ");
  }


  return 0;
}
