#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dstring.h"
#include "indexer.h"
#include "utils.h"

dstringa indexer(dstring text, int max_phrase_length) {
    dstringa words = dsplit(text, ' ');
    dstringa index = dcreatea();
    
    int max_length = min(max_phrase_length, words.length);
    
    for(int ahead = 0; ahead < max_length; ahead++) {
        for(int i = 0; i < max_length; i++) {
            if(i + ahead < max_length) { 
                dstringa range = drange(words, i, i + ahead);
                dstring joined = djoin(range, ' ');
                index = dpush(index, joined);
            }
        }
    }

    return index;
}
