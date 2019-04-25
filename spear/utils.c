#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

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
            memcpy(word_array[word_on], tmp_word, strlen(tmp_word) + 1);
            word_on++;
            memset(tmp_word, '\0', strlen(tmp_word));
            tmp_char_on = 0;
        } else {
            tmp_word[tmp_char_on] = on;
            tmp_char_on++;
        }
    }    
    
    word_array[word_on] = malloc(strlen(tmp_word) * sizeof(char));
    memcpy(word_array[word_on], tmp_word, strlen(tmp_word) + 1);
    t_split out = {word_array, words};

    return out;
}

int max(int i1, int i2) {
    return i1 > i2 ? i1 : i2;
}

int min(int i1, int i2) {
    return i1 > i2 ? i2 : i1;
}
