#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

const int SIZE = 100;

char * input(FILE * fp,  int * string_amount, long int * last);

void to_strings(char * text_temp, char ** text, long int last);

void output(char ** text, int string_amount);

void sorting (char ** text, int string_amount);

void ToUpper(char * string);
