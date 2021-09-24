#include <stdio.h>
#include <stdlib.h>
#include "title.h"


int main(void){

    FILE* fp = nullptr;
    FILE* out = nullptr;

    if (!(fp = fopen("onegintext", "r"))) {
        printf("Can't open input file \n");
        return 0;
    }
    if (!(out = fopen("Output", "w"))) {
        printf("Can't open alphabetically sort output file \n");
        return 0;
    }
    else {
        //CHECK_FUNC(OneginTest())
        CHECK_FUNC(makeOneginGreatAgain(fp, out))
    }

    fclose(fp);
    fclose(out);

    return 0;
}




int makeOneginGreatAgain(FILE* fp, FILE* out){
    CHECK_PTR(fp)

    Poem Onegin = {};
    Onegin.input_file = fp;
    Onegin.output_file = out;
  
    CHECK_FUNC(fileLength(&(Onegin.file_length), fp))
    
    Onegin.text_buffer = (char *) calloc(Onegin.file_length + 1, sizeof(char));
    CHECK_PTR(Onegin.text_buffer)

    input(fp, &(Onegin.string_amount), Onegin.text_buffer, Onegin.file_length);
        
    Onegin.text = (Line*) calloc(Onegin.string_amount, sizeof(Line)); 
    CHECK_PTR(Onegin.text)

    CHECK_FUNC(to_strings(Onegin.text_buffer, Onegin.text, Onegin.string_amount))

    CHECK_FUNC(sorting(Onegin.text, Onegin.string_amount))

    CHECK_FUNC(output(Onegin.text, Onegin.string_amount, Onegin.output_file))

    fputs("\n \n \n Now new poem: \n \n", Onegin.output_file);

    CHECK_FUNC(create_new_poem(Onegin.text, Onegin.string_amount))

    CHECK_FUNC(output(Onegin.text, Onegin.string_amount, Onegin.output_file))

    fputs("\n \n Now original text: \n \n", Onegin.output_file);

    CHECK_FUNC(output_original(Onegin.text_buffer, Onegin.string_amount, Onegin.output_file))

    finish_poem(&Onegin);
    return 0;
}
