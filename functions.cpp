#include "title.h"


/*!
    \brief Главная функция, вызывающая сортировку
    \param [FILE *] fp Указатель на файл с исходным текстом
*/ 
void makeOneginGreatAgain(FILE * fp){
    assert(fp);

    char ** text = NULL;
    int string_amount = 0;
    char * text_temp = NULL;

    text_temp = input(fp, &string_amount);
        
    text = (char **) calloc(string_amount, sizeof(char *));
    assert(text);


    to_strings(text_temp, text, string_amount);
    sorting(text, string_amount);

    output(text, string_amount);
    printf("\n \n Now reverse: \n \n \n");
    output_reverse(text, string_amount);
    printf("\n \n Now original text: \n \n \n");
    output_original(text_temp, string_amount);


    free(text);
    free(text_temp);
}


/*!
    \brief Функция ввода текста из файла
    \param[FILE*] fp указатель на файл, из которого считывается текст
    \param[int*] string_amount указатель на число строк в тексте


    Функция считывает текст из файла, записывая значения числа строк и общего числа символов.
    Функция возвращает указатель на массив с текстом.
*/
char * input(FILE * fp, int * string_amount){
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

    long int i = 0;
    for (; i < last; i++){
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
        printf("%s \n", text[i]);
    }
}



/*!
    \brief Функция преобразование массива текст в двумерный
    \param[char*] text_temp УМассив всех символов текста
    \param[char**] text Двумерный массив, хранящий текст построчно
    \param[int] string_amount Общее число строк в тексте

    Данная функция разбивает массив с текстом на строки для дальнейшей сортировки
*/
void to_strings(char * text_temp, char ** text, int string_amount){
    assert(text_temp);
    assert(text);

    int in_string = 0;

    for (int i = 0; i < string_amount; i++){

        text[i] = text_temp;    

        while (*text_temp != '\n' && *text_temp != '\0'){

            if (in_string == 0){
                text[i] = text_temp;
                in_string = 1;
            }

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
void sorting(char ** text, int string_amount){
    assert(text);

    qsort(text, string_amount, sizeof(char *), comp);
}

/*!
    \brief Находит минимум из двух чисел
*/
size_t min(size_t a, size_t b){
    return (a < b) ? a : b;
}




/*!
    \brief Аналогична функции strcmp1

    Работает со строками исходного текста, определяя их очередность по алфавиту.
*/
int comp(const void * str1, const void * str2){
    const char * string1 = *(const char **) str1;
    const char * string2 = *(const char **) str2;

    return strcmp1(string1, string2);
}



/*!
    \brief Функция сравнения строк
    \param [const char *] string1 Первая строка
    \param [const char *] string2 Вторая строка

    Возвращает 1, если первая строка должна идти после второй.
    Возвращает -1, если первая строка должна идти перед второй.
*/
int strcmp1(const char * string1, const char * string2){
    assert(string1);
    assert(string2);

    int sum1 = 0, sum2 = 0;
    int i = 0, j = 0;

    while(sum1 == sum2 && (string1[i] != '\0' || string2[j] != '\0')){

        while(strchr(PUNKTUATION_MARK, (int) string1[i]) != nullptr && string1[i] != '\0'){
            i++;
        }

        if (string1[i] != '\0'){
            if (isalpha(string1[i])){
                char c = toupper(string1[i]);
                sum1 += c;
            }
            else{
                sum1 += string1[i];
            }

            i++;
        }



        while(strchr(PUNKTUATION_MARK, (int) string2[j]) != nullptr && string2[j] != '\0'){
            j++;
        }

        if (string2[j] != '\0'){
            if (isalpha(string2[j])){
                char c = toupper(string2[j]);
                sum2 += c;
            }
            else{
                sum2 += string2[j];
            }

            j++;
        }
        
    }

    if (sum1 == sum2){
        return (strlen(string1) > strlen(string2)) ? 1 : -1;
    }


    return (sum1 > sum2) ? 1 : -1;
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
        
    text = (char **) calloc(string_amount, sizeof(char *));

    to_strings(text_temp, text, string_amount);
    sorting(text, string_amount);



    char * text_temp_res = NULL;
    char ** text_res = NULL;
    int string_amount1 = 0;

    text_temp_res = input(fp_result, &string_amount1);

    text_res = (char **) calloc(string_amount1, sizeof(char *));

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
void output_reverse(char ** text, int string_amount){
    assert(text);

    for (int i = string_amount - 1; i >= 0; i--){
        printf("%s \n", text[i]);
    }
}



/*!
    \brief Выводит исходный текст
    \param [char *] text_temp Массив, хранящий строки текста одну за одной
    \param [int] string_amount Число строк в тексте
*/
void output_original(char * text_temp, int string_amount){
    assert(text_temp);

    for (int i = 0; i < string_amount; i++){
        printf("%s \n", text_temp);
        text_temp += strlen((const char *) text_temp) + 1;
    }
    
}