#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const int SIZE = 100;

const char PUNKTUATION_MARK[] = ".,!?-:;  \" \\ \' «» () {} []";



void makeOneginGreatAgain(FILE * fp);

char * input(FILE * fp,  int * string_amount);

void to_strings(char * text_temp, char ** text, int string_amount);

void output(char ** text, int string_amount);

void sorting (char ** text, int string_amount);

size_t min(size_t a, size_t b);

int comp(const void * str1, const void * str2);

int strcmp1(const char * string1, const char * string2);

int OneginTest();

void output_reverse(char ** text, int string_amount);

void output_original(char * text_temp, int string_amount);