#include <stdio.h>

#ifndef TITLE_H
   #define TITLE_H
   #include "title.h"
#endif


const int SIZE = 100;


int main(void){
    
    char file[SIZE] = {};
    FILE * fp = nullptr;
    char ** text = nullptr;
    int string_amount = 0;
 
    // do argv & argc

    printf("Enter the name of the file \n");
    while (scanf("%s", file) != 1){
        printf("Wrong format!!! \nEnter the name of the file \n");
    }

    if(!(fp = fopen(file, "r"))) {
        printf("Can't open file \n");
    }
    else {
        if(OneginTest()) return 0;
        makeOneginGreatAgain(fp);
    }


    fclose(fp);
    
    return 0;
}


