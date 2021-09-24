#include <stdio.h>
#include <stdlib.h>
#include "title.h"


int main(void){

    FILE* fp = fopen("FILE", "r");
    FILE* out = fopen("Output", "w");

    if (!fp) {
        printf("Can't open input file \n");
        return 0;
    }
    if (!out) {
        printf("Can't open alphabetically sort output file \n");
        return 0;
    }
    else {
        CHECK_FUNC(OneginTest())
        CHECK_FUNC(makeOneginGreatAgain(fp, out))
    }

    fclose(fp);
    fclose(out);

    return 0;
}
