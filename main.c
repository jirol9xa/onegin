#include "title.h"

void input(char ** str, FILE * fp);

void output(char ** str);

int main(void){
    char * strings[10] = {};
    char file[SIZE] = {};
    FILE * fp = NULL;

    printf("Enter the name of the file \n");
    scanf("%s", file);

    if(!(fp = fopen(file, "r"))){
        printf("Can't open file \n");
    }
    else{
        input(strings, fp);
        output(strings);
    }


    return 0;
}


void input(char ** str, FILE * fp){
    assert(str);

    char temp[SIZE] = {};
    while(fgets(temp, SIZE - 1, fp)){
        strcpy(*str, temp);
    }

}


void output(char ** str){
    assert (str);

    while(*str != NULL){
        printf("%s \n", *str);
        *str++;
    }
}