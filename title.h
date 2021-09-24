#ifndef TITLE_H
   #define TITLE_H

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
   int makeOneginGreatAgain(FILE* fp, FILE* out);
   int OneginTest();


   #define CHECK_FUNC(arg){                                               \
      if (arg){                                                            \
      printf("[%s:%d] --- %s failed\n", __func__, __LINE__, #arg);          \
      return 1;                                                              \
      }                                                                       \
   }                                                                           

   #define CHECK_PTR(arg){                                                \
      if (!arg){                                                           \
      printf("[%s:%d] --- %s failed\n", __func__, __LINE__, #arg);          \
      return 1;                                                              \
      }                                                                       \
   }


   typedef struct {
      char* string;
      int length;
   } Line;

   typedef struct {
      FILE* input_file;
      FILE* output_file;
      long file_length;
      int string_amount;
      char* text_buffer;
      Line* text;
   } Poem;


   int input(FILE* fp,  int* string_amount, char* text_buffer, long file_length);
   int to_strings(char* text_buffer, Line* text, int string_amount);
   int fileLength(long * file_length, FILE* fp);

   int sorting(Line* text, int string_amount);
   int create_new_poem(Line* text, int string_amount);
   int strcmp_reverse(void* str1, void* str2);
   int strcmp_direct(void* string1, void* string2);
   int Qsorting(void* Array, int element_amount, size_t element_size, int (*comp)(void* elem1, void* elem2), char* buffer);
   int finish_poem(Poem* Onegin);

   int output_original(char* text_buffer, int string_amount, FILE* output);
   int output(Line* text, int string_amount, FILE* out);
                                                                           
#endif
