#include <stdio.h>

int main(void){
    int A[2] = {1234, 2345};

    char* a = (char*) &A;

    for (int i = 0; i < 2; i++){
        printf("%d\n", *((int*)(a + i * 4)));
    }
    return 0;
}