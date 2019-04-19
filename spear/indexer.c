#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void indexer(char *text, int max_phrase_length) {
    t_split words = split(text);
    for(int i = 0; i < words.length; i++) {
        printf("%s ", words.word_array[i]);
    }
}
