#include "hashmap.h"
#include "dstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HMAP_SIZE 1000081

unsigned int hash(char *val) {
    unsigned long sum = 0;
    for(int x = 0; x < strlen(val); x++) {
        sum += (unsigned long)val[x];
    }

    return (unsigned int)(sum % HMAP_SIZE);
}

hashmap *hcreate() {
    hashmap *hm = calloc(HMAP_SIZE, sizeof(hashmap));
    return hm;
}

void hfree(hashmap *hm) {
    // TODO: Free every key
    for(int i = 0; i < HMAP_SIZE; i++) {
        hashmap *map_array = &hm[i];
        for(int j = 0; j < map_array->length; j++) {
            dfree(map_array->maps[j].key);
            dfreea(map_array->maps[j].values);
        }
        free(map_array->maps);
    }

    free(hm);
}

hashmap *hset(hashmap *hm, dstring key, dstring value) {
    unsigned int hash_val = hash(dtext(key));
    hashmap *map_array = &hm[hash_val];
    int length = map_array->length;
    if(length == 0) {
        map_array->maps = malloc(sizeof(keyval));
        map_array->maps[0].key = key;
        map_array->maps[0].values = dpush(dcreatea(), value);
        map_array->length++;
        // hm[hash_val] = map_array;
    } else {
        int index = -1;
        for(int i = 0; i < length; i++) {
            keyval on = map_array->maps[i];
            if(dequals(on.key, key)) {
                index = i;
                break;
            }
        }
        int new_length = length + 1;
        if(index == -1) { // Element not in array
            map_array->maps = realloc(map_array->maps, sizeof(keyval) * new_length);
            dstringa values = dcreatea();
            values = dpush(values, value);
            keyval new_keyval = {key, values};
            map_array->maps[length] = new_keyval;
            map_array->length++;
            // hm[hash_val] = map_array;
        } else { // Element in array
            dstringa values = map_array->maps[index].values;
            if(dindexofa(values, value) == -1) {
                map_array->maps[index].values = dpush(values, value);
            }
        }
    }

    return hm;
}

dstringa hget(hashmap *hm, dstring key) {
    unsigned int hash_val = hash(dtext(key));
    hashmap map_array = hm[hash_val];
    int length = map_array.length;
    if(length == 0) {
        dstringa empty = dcreatea();
        return empty;
    }

    dstringa values = dcreatea();
    for(int i = 0; i < length; i++) {
        keyval on = map_array.maps[i];
        if(dequals(on.key, key)) {
            values = on.values;
            break;
        }
    }

    return values;
}
