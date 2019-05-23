#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dstring.h"
#include "indexer.h"
#include "utils.h"

dstringa indexer(dstring text, int max_phrase_length) {
    // Needs to be fixed. Only indexing the first 10 words
    dstringa words = dsplit(text, ' ');
    dstringa index = dcreatea();
    
    int max_length = min(max_phrase_length, words.length);
    
    for(int text_size = 0; text_size < words.length; text_size += max_phrase_length)  {
        for(int ahead = 0; ahead < max_length; ahead++) {
            for(int i = text_size; i < max_length + text_size; i++) {
                int check_len = max_length + text_size;
                if(check_len > words.length)
                    check_len = words.length;
                if(i + ahead < check_len) { 
                    dstringa range = drange(words, i, i + ahead);
                    dstring joined = djoin(range, ' ');
                    index = dpush(index, joined);
                }
            }
        }
    }

    return index;
}
