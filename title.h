#ifndef TITLE_H

#define TITLE_H

#include <locale.h>

int makeOneginGreatAgain(FILE* fp, FILE* sorted_alphabetically, FILE* sorted_reverse, FILE* original_text);
int OneginTest();

#define PRINT_ERROR(arg)                                                  \
   printf("[%s:%d] --- %s failed\n", __func__, __LINE__, #arg);          \
   return 0    

#endif
