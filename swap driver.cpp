#include <stdio.h>


static int swap(void* element1, void* element2, int element_size){

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


int main(void){
    int A = 255, B = 2387;

    swap(&A, &B, sizeof(int));

    printf("A:%d\nB:%d", A, B);
    return 0;
}