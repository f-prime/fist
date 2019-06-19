#ifndef H_HASHMAP
#define H_HASHMAP

#define HMAP_SIZE 1000081

#include "dstring.h"

typedef struct keyval {
    dstring key;
    dstringa values;
} keyval;

typedef struct hashmap {
    int length;
    keyval *maps;
} hashmap;

hashmap *hcreate();
hashmap *hset(hashmap *hm, dstring key, dstring value);
dstringa hget(hashmap *hm, dstring key);

#endif
