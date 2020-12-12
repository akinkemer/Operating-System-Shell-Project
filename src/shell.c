#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_input.h>

int main(int argc, char **argv)
{
  char input[512];
  while (strncmp(input, "quit", 4) != 0)
  {
    printf("prompt>");
  }


  return 0;
}
