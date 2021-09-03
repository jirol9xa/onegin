#include "title.h"


int main(void){
    
    char file[SIZE] = {};
    FILE * fp = NULL;
    char ** text = NULL;
    int string_amount = 0;
    long int last = 0;

    printf("Enter the name of the file \n");
    scanf("%s", file);

    if(!(fp = fopen(file, "r"))) {
        printf("Can't open file \n");
    }
    else {
        char * text_temp = NULL;
        text_temp = input(fp, &string_amount, &last);
        text = (char **) malloc(string_amount * sizeof(char *));
        to_strings(text_temp, text, last);
        sorting(text, string_amount);
        output(text, &string_amount);
        free(text);
    }


    fclose(fp);
    
    return 0;
}


