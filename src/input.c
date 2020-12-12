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
    input->NF=0;
    input->line[MAXLEN-1]='\0';
    return input;
    
}
int get_line(INPUT in)
{
    in->NF=0;

    if(fgets(in->line,MAXLEN-1,in->file)){
        in->NF=-1;
        return -1;
    }
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