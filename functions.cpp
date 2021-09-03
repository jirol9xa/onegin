#include "title.h"


/*!
    \brief Функция ввода текста из файла
    \param[FILE*] fp указатель на файл, из которого считывается текст
    \param[int*] string_amount указатель на число строк в тексте
    \param[long int *] last указатель на общее число символов в тексте

    Функция считывает текст из файла, записывая значения числа строк и общего числа символов.
    Функция возвращает указатель на массив с текстом.
*/
char * input(FILE * fp, int * string_amount, long int * last){
    assert(fp);

    char * text_temp = {};
    long int i = 0;

    fseek(fp, 0L, SEEK_END);
    *last = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
    text_temp = (char *) malloc(*last + 1);

    for (; i < *last; i++){
        text_temp[i] = getc(fp);

        if (text_temp[i] == '\n'){
            (*string_amount)++;
        }
    }
    text_temp[i] = '\0';


    return text_temp;
}


/*!
    \brief Функция вывода текста
    \param[char**] text Массив, хранящий отсортированный текст построчно
    \param[int] string_amount Число строк в массиве

    Функция выыодит отсортированный текст построчно.
*/
void output(char ** text, int string_amount){
    assert(text);


    for (int i = 0; i < string_amount; i++){
        printf("%s", text[i]);
    }
}


/*!
    \brief Функция преобразование массива текст в двумерный
    \param[char*] text_temp УМассив всех символов текста
    \param[char**] text Двумерный массив, хранящий текст построчно
    \param[long int] last Общее число символов в тексте

    Данная функция разбивает массив с текстом на строки для дальнейшей сортировки
*/
void to_strings(char * text_temp, char ** text, long int last){

    for (int i = 0, j = 0, g = 0; i < last; i++){

        char * string_temp = NULL;

        if (text_temp[i] == '\n'){
            string_temp = (char *) malloc(i - g + 2);


            for (int n = g; n <= i; n++){
                string_temp[n - g] = text_temp[n];
            }
            string_temp[i - g + 1] = '\0';


            text[j] = (char *) malloc (i - g + 2);


            strcpy(text[j], string_temp);

            g = i + 1;
            j++;
        }
    }


    free(text_temp);
}


/*!
    \brief Функция сортировки
    \param[char**] text Массив, хранящий текст построчно
    \param[int] string_amount Число строк в тексте
*/
void sorting(char ** text, int string_amount){

    for (int i = 0; i < string_amount; i++){

        for (int j = 0; j < string_amount; j++){

            char * string_temp1 = NULL;
            char * string_temp2 = NULL;


            string_temp1 = (char *) malloc(strlen(text[i]) + 1);
            strcpy(string_temp1, text[i]);
            string_temp2 = (char *) malloc(strlen(text[j]) + 1);
            strcpy(string_temp2, text[j]);


            ToUpper(string_temp1);
            ToUpper(string_temp2);


            if (strcmp(string_temp1, string_temp2) < 0){ //меняем строки местами
                free(string_temp2);
                free(string_temp1);


                char * string_temp3;
                string_temp3 = (char *) malloc(strlen(text[i]) + 1);


                strcpy(string_temp3, text[i]);
                strcpy(text[i], text[j]);
                strcpy(text[j], string_temp3);


                free(string_temp3);
            }
        }
    }
}


/*!
    \brief Перевод в капс
    \param[char*] string Строка, которую надо написать капсом

    Функция меняет все маленькие буквы в строке на буквы капсом
*/
void ToUpper(char * string){
    for (int i = 0; i < strlen(string); i++){
        string[i] = toupper(string[i]);
    }
}