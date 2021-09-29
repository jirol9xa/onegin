#include <stdio.h>


static int swap(void* element1, void* element2, unsigned int element_size){

    char* elem1 = (char*) element1;
    char* elem2 = (char*) element2;

    while (element_size >= 16) {
        __int128_t buffer = *((__int128_t*) elem1);
        *((__int128_t*) elem1) = *((__int128_t*) elem2);
        *((__int128_t*) elem2) = buffer;

        elem1 += 16;
        elem2 += 16;
        element_size -= 16;
    }
    while (element_size >= 8) {
        __int64_t buffer = *((__int64_t*) elem1);
        *((__int64_t*) elem1) = *((__int64_t*) elem2);
        *((__int64_t*) elem2) = buffer;

        elem1 += 8;
        elem2 += 8;
        element_size -= 8;
    }
    while (element_size >= 4) {
        __int32_t buffer = *((__int32_t*) elem1);
        *((__int32_t*) elem1) = *((__int32_t*) elem2);
        *((__int32_t*) elem2) = buffer;

        elem1 += 4;
        elem2 += 4;
        element_size -= 4;
    }
    while (element_size >= 2) {
        __int16_t buffer = *((__int16_t*) elem1);
        *((__int16_t*) elem1) = *((__int16_t*) elem2);
        *((__int16_t*) elem2) = buffer;

        elem1 += 2;
        elem2 += 2;
        element_size -=2;
    }
    if (element_size == 1) {
        __int8_t buffer = *elem1;
        *elem1 = *elem2;
        *elem2 = buffer;
    }

    return 0;
}


int main(void) {
    long A = 15478546734563456, B = 43287462387642;

    swap(&A, &B, sizeof(long int));
    printf("A:%ld\nB:%ld", A, B);

    return 0;
}