#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "title.h"

static int swap(void* element1, void* element2, int element_size);
static inline int comp(void* A, void* B);

void PrintArr(void *Array, int n){

    char* Arr = (char*) Array;
    for (int i = 0; i < n; i++) {
        printf("%d ", *((int*)(Arr + i * 4)));
    }
    printf("\n");
}

int main(void){
    Line* text = (Line*) calloc(6, sizeof(Line));

    text[0].string = "AAA";
    text[0].length = 3;
    text[1].string = "BBB";
    text[1].length = 3;
    text[2].string = "CCC";
    text[2].length = 3;
    text[3].string = "WWW";
    text[3].length = 3;
    text[4].string = "ZZZ";
    text[4].length = 3;
    text[5].string = "DDD";
    text[5].length = 3;
    qsorting(text, 5, sizeof(Line), strcmp_direct);

    for (int i = 0; i < 3; i++){
        printf("%s\n", text[i].string);
    }
    return 0;
}



static int comp(void* A, void* B){

    int a = *(int*) A;
    int b = *(int*) B;

    if (a > b) return -1;
    else if (a < b) return 1;
    else return 0;
}


int strcmp_direct(void* str1, void* str2){
    CHECK_PTR(str1)
    CHECK_PTR(str2)

    const Line string1 = *(const Line*) str1;
    const Line string2 = *(const Line*) str2;

    char symbol1 = 0, symbol2 = 0;
    int i1 = 0, i2 = 0;

    while (symbol1 == symbol2 && i1 < string1.length && i2 < string2.length){
        symbol1 = 0;
        symbol2 = 0;

        while (!isalpha(string1.string[i1]) && i1 < string1.length){
            i1++;
        }

        symbol1 = toupper(string1.string[i1]);
        i1 += (i1 < string1.length);

        while (!isalpha(string2.string[i2]) && i2 < string2.length){
            i2++;
        }

        symbol2 = toupper(string2.string[i2]);
        i2 += (i2 < string2.length);
        
    }
    
    if (symbol1 > symbol2){
        return 1;
    }
    else if (symbol1 < symbol2){
        return -1;
    }
    else{
        return 0;
    }
}


int qsorting(void* Array, int element_amount, size_t element_size, int (*comp)(void* elem1, void* elem2)) {
    CHECK_PTR(Array)


    char* buffer = (char*) calloc(1, element_size);
    Qsorting(Array, element_amount, element_size, comp, buffer);
    free(buffer);
    return 0;
}


int Qsorting(void* Array, int element_amount, size_t element_size, int (*comp)(void* elem1, void* elem2), char* buffer){
    CHECK_PTR(Array)

    char* Arr = (char*) Array;

    int left = 0;
    int right = element_amount - 1;
    for (int i = 0; i < element_size; i++){
        buffer[i] = *(Arr + (right/2) * element_size + i);
    }

    do {

        while (comp(Arr + left * element_size, buffer) > 0) {
            left++;
        }
        while (comp(buffer, Arr + right * element_size) > 0) {
            right--;
        }

        if (left < right) {
            printf("right = %d, left = %d, mid = %d\n", right, left, *(int*)buffer);
            
            printf("i'm swaping\n");
            swap(Arr + left * element_size, Arr + right * element_size, element_size);
            printf("\n");

            printf("right = %d, left = %d, mid = %d\n", right, left, *(int*)buffer);
            left++;
            right--;
        }
        else if (left == right) {
            left++;
            right--;
        }
    } while (left <= right);
    if (right > 0) {
        qsorting(Arr, right + 1, element_size, comp);
    }
    if (left < element_amount) {
        qsorting(Arr + left * element_size, element_amount - left, element_size, comp);
    }

    return 0;
}

static int swap(void* element1, void* element2, int element_size){
    CHECK_PTR(element1)
    CHECK_PTR(element2)

    char* elem1 = (char*) element1;
    char* elem2 = (char*) element2;

    char buffer = 0;

    for (int i = 0; i < element_size; i++){
        buffer = elem1[i];
        elem1[i] = elem2[i];
        elem2[i] = buffer;
    }

    return 0;
}