#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#ifndef TITLE_H
    #define TITLE_H
    #include "title.h"
#endif


const char BAD_SYMBOLS[] = ".,!?-:;  \" \\ \' «» () {} []";


static char * input(FILE * fp,  int * string_amount);
static void to_strings(char * text_temp, char ** text, int string_amount);

static void sorting(char ** text, int string_amount);
static inline int is_bad_symbol(char c);
static int comp(const void * str1, const void * str2);
static int strcmp1(const char * string1, const char * string2);

static void output_original(char * text_temp, int string_amount);
static void output(char ** text, int string_amount);



/*!
    \brief Главная функция, вызывающая сортировку
    \param [FILE *] fp Указатель на файл с исходным текстом
*/ 
void makeOneginGreatAgain(FILE * fp){
    assert(fp); 

    char ** text = NULL; // null to nullptr
    int string_amount = 0;
    char * text_temp = NULL; // gandon // rename

    text_temp = input(fp, &string_amount);
        
    text = (char **) calloc(string_amount, sizeof(char *)); 
    assert(text); // gandon


    to_strings(text_temp, text, string_amount);
    sorting(text, string_amount);

    output(text, string_amount);
    puts("\n \n \n Now original text: \n \n \n");
    output_original(text_temp, string_amount);

    
    free(text);
    free(text_temp);
}


/*!
    \brief Функция ввода текста из файла
    \param[FILE*] fp указатель на файл, из которого считывается текст
    \param[int*] string_amount указатель на число строк в тексте
    \details Функция считывает текст из файла, записывая значения 
            числа строк и общего числа символов.
    \details Функция возвращает указатель на массив с текстом.
*/
static char * input(FILE * fp, int * string_amount){
    assert(fp); 
    assert(string_amount); 

    char * text_temp = nullptr; 
    long int last = 0;

    int assertion = fseek(fp, 0L, SEEK_END);
    assert(assertion == 0);

    last = ftell(fp);

    assertion = fseek(fp, 0L, SEEK_SET);
    assert(assertion == 0);
    
    text_temp = (char *) calloc(last + 1, sizeof(char));
    assert(text_temp);

    fread(text_temp, sizeof(char), last, fp);
    text_temp[last] = '\0';

    for (int i = 0; i < last; i++){
        if (text_temp[i] == '\n'){
            (*string_amount)++;
        }
    }


    return text_temp;
}



/*!
    \brief Функция вывода текста
    \param[char**] text Массив, хранящий отсортированный текст построчно
    \param[int] string_amount Число строк в массиве
    \details Функция выыодит отсортированный текст построчно.
*/
static void output(char ** text, int string_amount){
    assert(text); 

    for (int i = 0; i < string_amount; i++){
        printf("%s \n", text[i]);
    }
}



/*!
    \brief Функция преобразование массива текст в двумерный
    \param[char*] text_temp УМассив всех символов текста
    \param[char**] text Двумерный массив, хранящий текст построчно
    \param[int] string_amount Общее число строк в тексте
    \details Данная функция разбивает массив с текстом на 
            строки для дальнейшей сортировки
*/
static void to_strings(char * text_temp, char ** text, int string_amount){
    assert(text_temp); 
    assert(text); 

    int in_string = 0;

    for (int i = 0; i < string_amount; i++){

        text[i] = text_temp;    

        while (*text_temp != '\n' && *text_temp != '\0'){
            text_temp++;
        }

        in_string = 0;
        (*text_temp) = '\0';
        text_temp++; 
    }
}



/*!
    \brief Функция сортировки
    \param[char**] text Массив, хранящий текст построчно
    \param[int] string_amount Число строк в тексте
*/
static void sorting(char ** text, int string_amount){
    assert(text); 

    qsort(text, string_amount, sizeof(char *), comp);
}




/*!
    \brief Аналогична функции strcmp1
    \details Работает со строками исходного 
            текста, определяя их очередность 
            по алфавиту.
*/
static int comp(const void * str1, const void * str2){
    const char * string1 = *(const char **) str1;
    const char * string2 = *(const char **) str2;


    return strcmp1(string1, string2);
}



/*!
    \brief Функция сравнения строк
    \param [const char *] string1 Первая строка
    \param [const char *] string2 Вторая строка
    \return 1, если первая строка должна идти 
            после второй и -1, если первая строка 
            должна идти перед второй.
*/
static int strcmp1(const char * string1, const char * string2){
    assert(string1); 
    assert(string2); 

    char simbol1 = 0, simbol2 = 0; // rename to symbol
    int i = 0, j = 0;

    while(simbol1 == simbol2 && (string1[i] != '\0' || string2[j] != '\0')){
        simbol1 = 0;
        simbol2 = 0;

        while(is_bad_symbol(string1[i])){
            i++;
        }

        simbol1 += toupper(string1[i]);
        i += (string1[i] != '\0');

        while(is_bad_symbol(string2[j])){
            j++;
        }

        simbol2 += toupper(string2[j]);
        j += (string2[j] != '\0');
        
    }

    if (simbol1 == simbol2){
        return (i > j) ? 1 : -1;
    }


    return (simbol1 > simbol2) ? 1 : -1;
}



/*!
    \brief Unitest
*/
int OneginTest(){
    int flag = 0;

    FILE * fp = NULL;
    FILE * fp_result = NULL;
    fp = fopen("TEST", "r");
    fp_result = fopen("TEST_RESULT", "r");

    char ** text = NULL;
    int string_amount = 0;
    char * text_temp = NULL;

    text_temp = input(fp, &string_amount);
    assert(text_temp);

    text = (char **) calloc(string_amount, sizeof(char *));
    assert(text);

    to_strings(text_temp, text, string_amount);
    sorting(text, string_amount);



    char * text_temp_res = NULL;
    char ** text_res = NULL;
    int string_amount1 = 0;

    text_temp_res = input(fp_result, &string_amount1);

    text_res = (char **) calloc(string_amount1, sizeof(char *));
    assert(text_res);

    to_strings(text_temp_res, text_res, string_amount1);



    for (int i = 0; i < string_amount; i++){
        if (strcmp(text[i], text_res[i])){
            flag = 1;

            printf("Test failed on %d string \n", i);
            printf("Expected: %s \n", text_res[i]);
            printf("Received: %s \n", text[i]);

        }
    }


    fclose(fp);
    fclose(fp_result);
    free(text);
    free(text_temp);
    free(text_res);
    free(text_temp_res);


    return flag;
}



/*!
    \brief Выводит обратную сортировку
    \param [char **] text Массив строк текста
    \param [int] string_amount Число строк в тексте
*/
static void output_reverse(char ** text, int string_amount){
    assert(text);

    for (int i = string_amount - 1; i >= 0; i--){
        printf("%s \n", text[i]);
    }
}



/*!
    \brief Выводит исходный текст
    \param [char *] text_temp Массив, хранящий 
            строки текста одну за одной
    \param [int] string_amount Число строк в тексте
*/
static void output_original(char * text_temp, int string_amount){
    assert(text_temp); 

    for (int i = 0; i < string_amount; i++){
        printf("%s \n", text_temp);
        text_temp += strlen((const char *) text_temp) + 1;
    }
    
}



/*!
    \brief Находит среди символов знаки препинания
    \param [char] c Символ
    \return [int] 1, если сивол явлеятся знаком 
            препинания и 0 в противном случае
*/
static inline int is_bad_symbol(char c){
    return (strchr(BAD_SYMBOLS, (int) c) != nullptr && c != '\0');
}