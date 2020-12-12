#ifndef INPUT_
#define INPUT_

#include <stdio.h>
#define MAXLEN 513
#define MAXFIELDS 512

 typedef struct input{
   FILE *file;
   int NF; /* Number of fields*/
   char line[MAXLEN];
   char *fields[MAXFIELDS];
 } *INPUT;

 extern INPUT new_inputstruct();
 extern int get_line();
 extern void free_inputstruct();

#endif
