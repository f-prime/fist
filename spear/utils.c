#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

t_split split(char *text) {
    int words = 1;

    for(int x = 0; x < strlen(text); x++) {
        if(text[x] == ' ') {
            words++;
        }
    }

    if(words == 1) {
        char **word_array = malloc(sizeof(char*));
        word_array[0] = malloc(sizeof(char) * strlen(text));
        word_array[0] = text;
        t_split out = {word_array, 1};
        return out;
    }
    
    char **word_array = malloc(words * sizeof(char*));
    
    char *tmp_word = malloc(strlen(text) * sizeof(char));
    int tmp_char_on = 0;
    int word_on = 0;

    for(int x = 0; x < strlen(text); x++) {
        char on = text[x];
        if(on == ' ') {
            word_array[word_on] = malloc(tmp_char_on * sizeof(char));
            memset(word_array[word_on], 0, strlen(tmp_word));
            memcpy(word_array[word_on], tmp_word, strlen(tmp_word) + 1);
            word_on++;
            memset(tmp_word, 0, strlen(tmp_word));
            tmp_char_on = 0;
        } else {
            tmp_word[tmp_char_on] = on;
            tmp_char_on++;
        }
    }    
    
    word_array[word_on] = malloc(strlen(tmp_word) * sizeof(char));
    memcpy(word_array[word_on], tmp_word, strlen(tmp_word) + 1);
    t_split out = {word_array, words};
    free(tmp_word);

    return out;
}

char *stripend(char *buffer) {
    int length = strlen(buffer);
    if(buffer[length - 1] != '\n')
        return buffer;
    int size = length - 2;
    char *stripped = malloc(size);
    memset(stripped, 0, size);
    memcpy(stripped, buffer, size);
    return stripped;
}

int max(int i1, int i2) {
    return i1 > i2 ? i1 : i2;
}

int min(int i1, int i2) {
    return i1 > i2 ? i2 : i1;
}
