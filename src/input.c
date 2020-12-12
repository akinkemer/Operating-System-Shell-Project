#include <input.h>

INPUT new_inputstruct(char *filename)
{
    FILE *f;
    if ((f= fopen(filename, "w")) == NULL)
    {
        printf("Dosya açma hatası!");
        return NULL;
    }
    INPUT input=(INPUT)malloc(sizeof(struct input));
    input->fields=0;
    input->line[MAXLEN-1]='\0';
    return input;
    
}
int get_line(INPUT input)
{
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