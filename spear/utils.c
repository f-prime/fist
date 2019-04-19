#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_split {
    char **word_array;
    int length;
} t_split;

t_split split(char *text) {
    int words = 0;

    for(int x = 0; x < strlen(text); x++) {
        if(text[x] == ' ') {
            words++;
        }
    }

    if(words) {
        words++;
    }
    
    char **word_array = malloc(words * sizeof(char*));
    
    char tmp_word[strlen(text)];
    int tmp_char_on = 0;
    int word_on = 0;

    for(int x = 0; x < strlen(text); x++) {
        char on = text[x];
        if(on == ' ') {
            word_array[word_on] = malloc(strlen(tmp_word) * sizeof(char));
            strcpy(word_array[word_on], tmp_word);
            word_on++;
            memset(tmp_word, '\0', strlen(tmp_word));
            tmp_char_on = 0;
        } else {
            tmp_word[tmp_char_on] = on;
            tmp_char_on++;
        }
    }    
    
    word_array[word_on] = malloc(strlen(tmp_word) * sizeof(char));
    strcpy(word_array[word_on], tmp_word);

    t_split out = {word_array, words};

    return out;
}


