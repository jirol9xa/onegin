#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "title.h"
                                                            

typedef struct{
    char* string;
    int length;
} Line;


static int input(FILE* fp,  int* string_amount, char* text_buffer, long file_length);
static int to_strings(char* text_buffer, Line* text, int string_amount);
static int fileLength(long * file_length, FILE* fp);

static int sorting(Line* text, int string_amount);
static int create_new_poem(Line* text, int string_amount);
static inline int is_bad_symbol(char c);
static int strcmp_reverse(const void* str1, const void* str2);
static int strcmp1(const void* string1, const void* string2);

static int output_original(char* text_buffer, int string_amount, FILE* original_text);
static int output(Line* text, int string_amount, FILE* out);



/*!
    \brief  Главная функция, вызывающая сортировку
    \param  [FILE*] fp Указатель на файл с исходным текстом
    \param  [FILE*] sorted_alphabetically Указатель на файл,
            куда будет записана прямая сортировка
    \param  [FILE*] sorted_alphabetically Указатель на файл,
            куда будет записана обратная сортировка
    \param  [FILE*] sorted_alphabetically Указатель на файл,
            куда будет записан оригинальный текст
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/ 
int makeOneginGreatAgain(FILE* fp, FILE* sorted_alphabetically, FILE* sorted_reverse, FILE* original_text){
    if (!fp){
        PRINT_ERROR(fp)
    }

    Line* text = nullptr; 
    int string_amount = 0;
    char* text_buffer = nullptr; 

    long file_length = 0;
    if (fileLength(&file_length, fp)){
        PRINT_ERROR(fileLength);
    }
    
    if ((text_buffer = (char *) calloc(file_length + 1, sizeof(char))) == nullptr){
        PRINT_ERROR(text_buffer);
    }

    if (input(fp, &string_amount, text_buffer, file_length)){
        PRINT_ERROR(input)
    }
        
    text = (Line*) calloc(string_amount, sizeof(Line)); 
    if (text == nullptr){
        PRINT_ERROR(text)
    }

    if (to_strings(text_buffer, text, string_amount)){
        PRINT_ERROR(to_strings)
    }

    if (sorting(text, string_amount)){
        PRINT_ERROR(sorting)
    }
    if (output(text, string_amount, sorted_alphabetically)){
        PRINT_ERROR(output)
    }

    if (create_new_poem(text, string_amount)){
        PRINT_ERROR(create_new_poem)
    }
    if (output(text, string_amount, sorted_reverse)){
        PRINT_ERROR(output)
    }

    if (output_original(text_buffer, string_amount, original_text)){
        PRINT_ERROR(output_original)
    }

    
    free(text);
    free(text_buffer);
    return 0;
}



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
static int input(FILE* fp, int* string_amount, char* text_buffer, long file_length){
    if (!fp) {
        PRINT_ERROR(fp)
    }
    if (!string_amount){
        PRINT_ERROR(string_amount)
    }
    if (!text_buffer){
        PRINT_ERROR(text_buffer)
    }

    fread(text_buffer, sizeof(char), file_length, fp);
    text_buffer[file_length] = '\0';

    for (int i = 0; i < file_length; i++){
        if (text_buffer[i] == '\n'){
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
static int output(Line* text, int string_amount, FILE* out){
    if (!text){
        PRINT_ERROR(text)
    }
    if (!out){
        PRINT_ERROR(out)
    }

    for (int i = 0; i < string_amount; i++){
        fprintf(out, "%s \n", text[i].string);
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
static int to_strings(char* text_buffer, Line* text, int string_amount){
    if (!text_buffer){
        PRINT_ERROR(text_buffer)
    }
    if (!text){
        PRINT_ERROR(text)
    }

    for (int i = 0; i < string_amount; i++){

        text[i].string = text_buffer;  

        while (*text_buffer != '\n' && *text_buffer != '\0'){
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
static int sorting(Line* text, int string_amount){
    if (!text){
        PRINT_ERROR(text)
    }

    qsort(text, string_amount, sizeof(Line), strcmp1);

    return 0;
}



/*!
    \brief  Функция сортировки по последнему символу
    \param  [Text*] text Массив структур, хранящий текст построчно
    \param  [int] string_amount Число строк в тексте
    \return 0 если функция завершилась успешно,
            1 в случае ошибки
*/
static int create_new_poem(Line* text, int string_amount){
    if (!text){
        PRINT_ERROR(text)
    }

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
static int strcmp1(const void* str1, const void* str2){
    if (!str1){
        PRINT_ERROR(str1)
    }
    if (!str2){ 
        PRINT_ERROR(str2)
    }

    const Line string1 = *(const Line*) str1;
    const Line string2 = *(const Line*) str2;

    char symbol1 = 0, symbol2 = 0;
    int i = 0, j = 0;

    while (symbol1 == symbol2 && i < string1.length && j < string2.length){
        symbol1 = 0;
        symbol2 = 0;

        while (!isalpha(string1.string[i]) && i < string1.length){
            i++;
        }

        symbol1 = toupper(string1.string[i]);
        i += (i < string1.length);

        while (!isalpha(string2.string[j]) && j < string2.length){
            j++;
        }

        symbol2 = toupper(string2.string[j]);
        j += (j < string2.length);
        
    }

    if (symbol1 == symbol2){
        return (string1.length > string2.length) ? 1 : -1;
    }

    return (symbol1 > symbol2) ? 1 : -1;
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
static int strcmp_reverse(const void* str1, const void* str2){
    if (!str1){
        PRINT_ERROR(str1)
    }
    if (!str2){
        PRINT_ERROR(str2)
    }

    const Line string1 = *(const Line*) str1;
    const Line string2 = *(const Line*) str2;

    int symbol1 = 0, symbol2 = 0;
    int i = string1.length - 1;
    int j = string2.length - 1;

    while (i >= 0 && j >= 0 && symbol1 == symbol2){
        symbol1 = 0;
        symbol2 = 0;

        while (!isalpha(string1.string[i]) && i >= 0){
            i--;
        }

        symbol1 = toupper(string1.string[i]);
        i -= (i >= 0);

        while (!isalpha(string2.string[j]) && j >= 0){
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
    int flag = 0;

    FILE* fp = NULL;
    FILE* fp_result = NULL;
    fp = fopen("TEST", "r");
    fp_result = fopen("TEST_RESULT", "r");

    Line* text = nullptr;
    int string_amount = 0;
    char* text_buffer = nullptr;
    long file_length = 0;

    if (fileLength(&file_length, fp)){
        PRINT_ERROR(fileLength)
    }

    if (!(text_buffer = (char*) calloc(file_length, sizeof(char)))){
        PRINT_ERROR(text_buffer)
    }

    if (input(fp, &string_amount, text_buffer, file_length)){
        PRINT_ERROR(text_buffer)
    }

    if (!(text = (Line*) calloc(string_amount, sizeof(Line)))){
        PRINT_ERROR(text)
    }

    if (to_strings(text_buffer, text, string_amount)){
        PRINT_ERROR(to_strings)
    }
    if (sorting(text, string_amount)){
        PRINT_ERROR(sorting)
    }


    char* text_buffer_res = nullptr;
    Line* text_res = nullptr;
    int string_amount1 = 0;
    long file_length_res = 0;

    if (fileLength(&file_length_res, fp_result)){
        PRINT_ERROR(fileLength);
    }

    if (!(text_buffer_res = (char*) calloc(file_length_res, sizeof(char)))){
        PRINT_ERROR(text_buffer_res)
    }

    if (input(fp_result, &string_amount1, text_buffer_res, file_length_res)){
        PRINT_ERROR(input)
    }

    if (!(text_res = (Line*) calloc(string_amount1, sizeof(Line)))){
        PRINT_ERROR(text_res)
    }

    if (to_strings(text_buffer_res, text_res, string_amount1)){
       PRINT_ERROR(to_strings)
    }


    for (int i = 0; i < string_amount; i++){
        if (strcmp(text[i].string, text_res[i].string)){
            flag = 1;

            printf("Test failed on %d string \n", i);
            printf("Expected: %s \n", text_res[i].string);
            printf("Received: %s \n", text[i].string);

        }
    }


    fclose(fp);
    fclose(fp_result);
    free(text);
    free(text_buffer);
    free(text_res);
    free(text_buffer_res);

    return flag;
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
static int output_original(char* text_buffer, int string_amount, FILE* out){
    if (!text_buffer){
        PRINT_ERROR(text_buffer)
    }

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
static int fileLength(long * file_length, FILE* fp){
    if (!file_length){
        PRINT_ERROR(file_length)
    }
    if (!fp){
        PRINT_ERROR(fp)
    }

    if (fseek(fp, 0L, SEEK_END)){
        PRINT_ERROR(fseek)
    }

    *file_length = ftell(fp);
    if (!file_length){
        PRINT_ERROR(file_length)
    }

    if (fseek(fp, 0L, SEEK_SET)){
        PRINT_ERROR(fseek)
    }

    return 0;
}