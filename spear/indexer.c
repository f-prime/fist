#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void indexer(char *text, int max_phrase_length) {
    t_split words = split(text);
     
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
            
            printf("'%s'", index);
            free(index);

            printf("\n");
        }
    }
}
