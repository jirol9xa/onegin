#include "title.h"


void makeOneginGreatAgain(FILE * fp){
    char ** text = NULL;
    int string_amount = 0;
    char * text_temp = NULL;

    text_temp = input(fp, &string_amount);
        
    text = (char **) calloc(string_amount, sizeof(char *));

    to_strings(text_temp, text, string_amount);
    sorting(text, string_amount);
    output(text, string_amount);

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

    char * text_temp = {};
    long int i = 0;
    long int last = 0;

    fseek(fp, 0L, SEEK_END);
    last = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
    text_temp = (char *) calloc(last + 1, sizeof(char));

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
    qsort(text, string_amount, sizeof(char *), comp);
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
    int min_len = min(strlen(string1), strlen(string2));
    int sum1 = 0, sum2 = 0;

    for (int i = 0; i < min_len; i++){
        if (isalpha(string1[i])){
            char c = toupper(string1[i]);
            sum1 += c;
        }
        else{
            sum1 += string1[i];
        }

        

        if (isalpha(string2[i])){
            char c = toupper(string2[i]);
            sum2 += c;
        }
        else{
            sum2 += string2[i];
        }


        if (sum1 != sum2){
            break;
        }
    }


    if (sum1 == sum2){
        return (strlen(string1) > strlen(string2)) ? 1 : -1;
    }


    return (sum1 > sum2) ? 1 : -1;
}


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