#ifndef INPUT_
#define INPUT_

#include <stdio.h>
#define MAXLEN 513

 typedef struct input{
   FILE *file;
   int fields;
   char line[MAXLEN];
 } *INPUT;

 extern INPUT new_inputstruct();
 extern int get_line();
 extern void free_inputstruct();

#endif
