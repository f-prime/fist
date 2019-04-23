#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct t_index {
    char **index;
    int length;
} t_index;

t_index create_indices(char *text, int max_phrase_length) {
    t_split words = split(text);
    char **index_list = malloc(words.length * words.length * sizeof(char*));
    int length = 0;

    for(int ahead = 1; ahead < min(words.length, max_phrase_length); ahead++) {
        for(int i = 0; i < words.length; i++) {
            if(i + ahead > words.length)
                break;
            
            char *index = malloc(strlen(text) * sizeof(char));
            memset(index, '\0', strlen(text)); 
            
            for(int j = i; j < i + ahead; j++) {
                char *word_on = words.word_array[j];
                if(j != i) {
                    strcat(index, " ");
                }

                strcat(index, word_on);
            }
            
            index_list[length] = malloc(strlen(index) * sizeof(char));
            memcpy(index_list[length], index, strlen(index) + 1);
            length++;
            free(index);
        }
    }
    t_index index_type = {index_list, length};
    return index_type;
}
