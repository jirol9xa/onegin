#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "title.h"
                                                            
static int swap(void* from, void* to);
static char* is_bad_symbol(char symbol);


const char* BAD_SYMBOLS = "0987654321 ,. ?! :;#@ \" \\ \' ";



/*!
    \brief   Функция ввода текста из файла
    \param   [FILE*] fp указатель на файл, из которого считывается текст
    \param   [int*] string_amount указатель на число строк в тексте
    \param   [char*] text_buffer Буфер. хранящий весь текст целиком
    \param   [long ing] file_length Общее количество символов в файле
    \return  0 если функция завершилась успешно,
             1 в случае ошибки
    \details Функция считывает текст из файла, записывая значения 
             числа строк и общего числа символов.
    \details Функция возвращает указатель на массив с текстом.
*/
int input(FILE* fp, int* string_amount, char* text_buffer, long file_length) {
    CHECK_PTR(fp)
    CHECK_PTR(string_amount)
    CHECK_PTR(text_buffer)

    fread(text_buffer, sizeof(char), file_length, fp);
    text_buffer[file_length] = '\0';

    for (int i = 0; i < file_length; i++) {
        if (text_buffer[i] == '\n') {
            (*string_amount)++;
        }
    }

    return 0;
}



/*!
    \brief   Функция вывода текста
    \param   [Text*] text Массив, хранящий отсортированный текст построчно
    \param   [int] string_amount Число строк в массиве
    \param   [FILE*] out Указатель на файл, куда будет
             происходить печать текста
    \return  0 если функция завершилась успешно,
             1 в случае ошибки
    \details Функция выыодит отсортированный текст построчно.
*/
int output(Line* text, int string_amount, FILE* out){
    CHECK_PTR(text)
    CHECK_PTR(out)

    for (int i = 0; i < string_amount; i++) {
        fprintf(out, "%s" "\n", text[i].string);
    }

    return 0;
}



/*!
    \brief   Функция преобразование массива текст в двумерный
    \param   [char*] text_buffer Массив всех символов текста
    \param   [Text*] text Двумерный массив, хранящий текст построчно
    \param   [int] string_amount Общее число строк в тексте
    \return  0 если функция завершилась успешно,
             1 в случае ошибки
    \details Данная функция разбивает массив с текстом на 
             строки для дальнейшей сортировки
*/
int to_strings(char* text_buffer, Line* text, int string_amount) {
    CHECK_PTR(text_buffer)
    CHECK_PTR(text)

    for (int i = 0; i < string_amount; i++) {

        text[i].string = text_buffer;  

        while (*text_buffer != '\n' && *text_buffer != '\0') {
            text_buffer++;
        }

        (*text_buffer) = '\0';
        text[i].length = strlen(text[i].string);
        text_buffer++;   
    }

    return 0;
}



/*!
    \brief  Функция сортировки
    \param  [Text*] text Массив, хранящий текст построчно
    \param  [int] string_amount Число строк в тексте
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/
int sorting(Line* text, int string_amount) {
    CHECK_PTR(text)

    qsorting(text, string_amount, sizeof(Line), strcmp_direct);

    return 0;
}



/*!
    \brief  Функция сортировки по последнему символу
    \param  [Text*] text Массив структур, хранящий текст построчно
    \param  [int] string_amount Число строк в тексте
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/
int create_new_poem(Line* text, int string_amount){
    CHECK_PTR(text)

    qsort(text, string_amount, sizeof(Line), strcmp_reverse);

    return 0;
}



/*!
    \brief  Функция сравнения строк
    \param  [const void*] str1 Первая строка
    \param  [const void*] str2 Вторая строка
    \return 1, если первая строка должна идти 
            после второй и -1, если первая строка 
            должна идти перед второй, 0 в случае
            ошибки
*/
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

        while (is_bad_symbol(string1.string[i1]) && i1 < string1.length){
            i1++;
        }

        symbol1 = toupper(string1.string[i1]);
        i1 += (i1 < string1.length);

        while (is_bad_symbol(string2.string[i2]) && i2 < string2.length){
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



/*!
    \brief  Сортирует строки по последнему символу
    \param  [const void*] str1 Первая строка
    \param  [const void*] str2 Вторая строка
    \return 1, если первая строка должна идти 
            после второй и -1, если первая строка 
            должна идти перед второй, 0 в случае
            ошибки

*/
int strcmp_reverse(const void* str1, const void* str2){
    CHECK_PTR(str1)
    CHECK_PTR(str2)

    const Line string1 = *(const Line*) str1;
    const Line string2 = *(const Line*) str2;

    int symbol1 = 0, symbol2 = 0;
    int i = string1.length - 1;
    int j = string2.length - 1;

    while (i >= 0 && j >= 0 && symbol1 == symbol2){
        symbol1 = 0;
        symbol2 = 0;

        while (is_bad_symbol(string1.string[i]) && i >= 0){
            i--;
        }

        symbol1 = toupper(string1.string[i]);
        i -= (i >= 0);

        while (is_bad_symbol(string2.string[j]) && j >= 0){
            j--;
        }

        symbol2 = toupper(string2.string[j]);
        j -= (j >= 0);
    }

    if (symbol1 == symbol2){
        return (string1.length > string2.length) ? 1 : -1;
    }

    return (symbol1 > symbol2) ? 1 : -1;
}



/*!
    \brief  Unitest
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/
int OneginTest(){
    int is_sort_ok = 0; 

    Poem Onegin = {};
    Poem Onegin_result = {};
    
    Onegin.input_file = fopen("TEST", "r");
    Onegin_result.input_file = fopen("TEST_RESULT", "r");

    CHECK_FUNC(fileLength(&Onegin.file_length, Onegin.input_file))

    Onegin.text_buffer = (char*) calloc(Onegin.file_length, sizeof(char));
    CHECK_PTR(Onegin.text_buffer)

    CHECK_FUNC(input(Onegin.input_file, &Onegin.string_amount, Onegin.text_buffer, Onegin.file_length))

    Onegin.text = (Line*) calloc(Onegin.string_amount, sizeof(Line));
    CHECK_PTR(Onegin.text)

    CHECK_FUNC(to_strings(Onegin.text_buffer, Onegin.text, Onegin.string_amount))

    CHECK_FUNC(sorting(Onegin.text, Onegin.string_amount))


    CHECK_FUNC(fileLength(&Onegin_result.file_length, Onegin_result.input_file))

    Onegin_result.text_buffer = (char*) calloc(Onegin_result.file_length, sizeof(char));
    CHECK_PTR(Onegin_result.text_buffer)

    CHECK_FUNC(input(Onegin_result.input_file, &Onegin_result.string_amount, Onegin_result.text_buffer, Onegin_result.file_length))


    Onegin_result.text = (Line*) calloc(Onegin_result.string_amount, sizeof(Line));
    CHECK_PTR(Onegin_result.text)

    CHECK_FUNC(to_strings(Onegin_result.text_buffer, Onegin_result.text, Onegin_result.string_amount))


    for (int i = 0; i < Onegin.string_amount; i++){
        if (strcmp(Onegin.text[i].string, Onegin_result.text[i].string)){
            is_sort_ok = 1;

            printf("Test failed on %d string \n", i);
            printf("Expected: %s \n", Onegin_result.text[i].string);
            printf("Received: %s \n", Onegin.text[i].string);

        }
    }


    fclose(Onegin.input_file);
    fclose(Onegin_result.input_file);
    finish_poem(&Onegin);
    finish_poem(&Onegin_result);
    return is_sort_ok;
}



/*!
    \brief  Выводит исходный текст
    \param  [char *] text_buffer Массив, хранящий 
            строки текста одну за одной
    \param  [int] string_amount Число строк в тексте
    \param  [FILE*] out Указатель на файл, куда
            будет происходить запись
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/
int output_original(char* text_buffer, int string_amount, FILE* out){
    CHECK_PTR(text_buffer)

    for (int i = 0; i < string_amount; i++){
        fprintf(out, "%s \n", text_buffer);
        text_buffer += strlen((const char*) text_buffer) + 1;
    }
    
    return 0;
}



/*!
    \brief  Функция измерения длины файла
    \param  [long int*] file_length Переменная, 
            куда будет записана длина файла
    \param  [FILE*] fp Указатель на файл, длину 
            которого надо узнать
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/
int fileLength(long * file_length, FILE* fp){
    CHECK_PTR(file_length)
    CHECK_PTR(fp)

    CHECK_FUNC(fseek(fp, 0L, SEEK_END))

    *file_length = ftell(fp);
    CHECK_PTR(*file_length)

    CHECK_FUNC(fseek(fp, 0L, SEEK_SET))

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



int qsorting(void* Array, int element_amount, size_t element_size, int (*comp)(void* elem1, void* elem2)) {
    CHECK_PTR(Array)


    char* buffer = (char*) calloc(1, element_size);
    Qsorting(Array, element_amount, element_size, comp, buffer);
    free(buffer);
    return 0;
}



int finish_poem(Poem* Onegin) {
    CHECK_PTR(Onegin)

    free(Onegin->text_buffer);
    free(Onegin->text);

    return 0;
}


static inline char* is_bad_symbol(char symbol){
    return ((char*) strchr(BAD_SYMBOLS, symbol));
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

        while (comp(Arr + left * element_size, buffer) < 0) {
            left++;
        }
        while (comp(buffer, Arr + right * element_size) < 0) {
            right--;
        }

        if (left < right) {
            swap(Arr + left * element_size, Arr + right * element_size, element_size);

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