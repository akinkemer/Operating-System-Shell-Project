#include <file_input.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

INPUT new_inputstruct(char *filename)
{
    FILE *f;
    if ((f = fopen(filename, "r")) == NULL)
    {
        puts("Hata:dosya bulunamadi!");
        return NULL;
    }
    INPUT input = malloc(sizeof(struct input));
    input->file=f;
    input->NF = 0;
    input->line[MAXLEN - 1] = '\0';
    return input;
}
int get_line(INPUT in)
{
    in->NF = 0;
    char *textline;
    if (fgets(in->line, MAXLEN - 1, in->file) == NULL)
    {
        in->NF = -1;
        return -1;
    }
    
    strcpy(textline,in->line); /* Dosyadan okunan satir kopyalaniyor */
    char lastchar=' ';
    int i;
    for (i = 0; textline[i] != '\0' && i < MAXLEN - 1; i++)
    {
        if (isspace(textline[i]))
        {
            lastchar = textline[i];
            textline[i] = '\0';
        }
        else
        {
            if (isspace(lastchar))
            {
                in->fields[in->NF] = textline + i;
                in->NF++;
            }
            lastchar = textline[i];
        }
    }
    
    return in->NF;
}
void free_inputstruct(INPUT input)
{
    if (input->file)
    {
        fclose(input->file);
    }
    free(input);
    return;
}