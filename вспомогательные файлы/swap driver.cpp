#include <stdio.h>


static int swap(void* element1, void* element2, int element_size){

    char* elem1 = (char*) element1;
    char* elem2 = (char*) element2;

    char buffer = 0;

    while (element_size >= 8){
        __int64_t buffer = *elem1;
        *elem1 = *elem2;
        *elem2 = buffer;

        elem1 += 8;
        elem2 += 8;
        element_size -= 8;
    }
    while (element_size >= 4){
        __int32_t buffer = *elem1;
        *elem1 = *elem2;
        *elem2 = buffer;

        elem1 += 4;
        elem2 += 4;
        element_size -= 4;
    }
    while (element_size >= 2){
        __int16_t buffer = *elem1;
        *elem1 = *elem2;
        *elem2 = buffer;

        elem1 += 2;
        elem2 += 2;
        element_size -=2;
    }
    if (element_size == 1){
        __int8_t buffer = *elem1;
        *elem1 = *elem2;
        *elem2 = buffer;
    }

    return 0;
}


int main(void){
    int A = 255, B = 2387;

    swap(&A, &B, sizeof(int));

    printf("A:%d\nB:%d", A, B);
    return 0;
}