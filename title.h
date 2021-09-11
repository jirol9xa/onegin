#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const int SIZE = 100;

void makeOneginGreatAgain(FILE * fp);

char * input(FILE * fp,  int * string_amount);

void to_strings(char * text_temp, char ** text, int string_amount);

void output(char ** text, int string_amount);

void sorting (char ** text, int string_amount);

void ToUpper(char * string);

size_t min(size_t a, size_t b);

int comp(const void * str1, const void * str2);

int strcmp1(const char * string1, const char * string2);

int OneginTest();