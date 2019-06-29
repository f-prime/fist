#include "indexer.h"
#include "dstring.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dstringa indexer(dstring text, int max_phrase_length) {
    dstringa words = dsplit(text, ' ');
    dstringa index = dcreatea();

    max_phrase_length = MIN(max_phrase_length, words.length);

    for (int i = 0; i < words.length; i += max_phrase_length) {
        for (int j = i; j < i + max_phrase_length; j++) {
            for (int k = 0; k < MIN(words.length - j, max_phrase_length); k++) {
                dstringa range = drange(words, j, j + k);
                dstring joined = djoin(range, ' ');
                index = dpush(index, joined);
                dfreea(range);
                dfree(joined);
            }
        }
    }

    dfreea(words);

    return index;
}
