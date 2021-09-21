#include <stdio.h>
#include "title.h"


int main(void){
    
    FILE* fp = nullptr;
    FILE* sorted_alphabetically = nullptr;
    FILE* sorted_reverse = nullptr;
    FILE* original_text = nullptr;

    if (!(fp = fopen("FILE", "r"))){
        printf("Can't open input file \n");
        return 0;
    }
    if (!(sorted_alphabetically = fopen("Alphabetically sort", "w"))){
        printf("Can't open alphabetically sort output file \n");
        return 0;
    }
    if (!(sorted_reverse = fopen("Reverse sort", "w"))){
        printf("Can't open reverse sort output file \n");
        return 0;
    }
    if (!(original_text = fopen("Original text", "w"))){
        printf("Can't open original output file \n");
        return 0;
    }

    else {
        if(OneginTest()){
            PRINT_ERROR(OneginTest);
        }
        if (makeOneginGreatAgain(fp, sorted_alphabetically, sorted_reverse, original_text)){
            PRINT_ERROR(makeOneginGreatAgain);
        }
    }


    fclose(fp);
    fclose(sorted_alphabetically);
    fclose(sorted_reverse);
    fclose(original_text);
    
    return 0;
}


