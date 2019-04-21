#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int HMAP_SIZE = 1000;

/*
    {
        "New York":["1", "2", "5"]
    }   

*/

typedef struct t_hval {
    char *key;
    char **values;
    int length;
} t_hval;

int hash(char *val) {
    int sum = 0;
    for(int i = 0; i < strlen(val); i++) {
        sum += (int) val[i];
    }

    return sum % HMAP_SIZE;
}

t_hval *h_add(t_hval *map, char *key, char *val) {
    /*
     * Need to expand array if hash all other indexes are taken.
     * Need to append to array if key already exists.
     */
    
    int h_val = hash(key);
    t_hval entry = map[h_val];
    while(entry.key != NULL && strcmp(entry.key, key) && h_val < HMAP_SIZE) {
        h_val++;
        entry = map[h_val];
    }

    // h_val is entry point
    
    if(h_val > HMAP_SIZE) { // If all other slots beyond h_val are taken we need to expand the array
        HMAP_SIZE *= 2;
        t_hval *new_map = malloc((HMAP_SIZE + h_val) * sizeof(t_hval));
        for(int i = 0; i < HMAP_SIZE; i++) {
            new_map[i] = map[i];
        }
        map = new_map;
    }

    if(entry.key != NULL && !strcmp(entry.key, key)) {
        int length = entry.length + 1;
        char **new_vals = malloc(length * sizeof(char*));
        int i;
        for(i = 0; i < entry.length; i++) {
            new_vals[i] = entry.values[i];
        }
        new_vals[i] = val;
        map[h_val].values = new_vals;
        map[h_val].length = length;
    } else {    
        char **values = malloc(sizeof(char*));
        values[0] = val;
        t_hval new_entry = {key, values, 1};
        map[h_val] = new_entry;    
    }

    return map;
}

t_hval *h_create() {
    // Need to create a 2D array of t_hvals
    t_hval *map = malloc(HMAP_SIZE * sizeof(t_hval));
    return map;
}

t_hval h_get(t_hval *map, char *key) {
    int on = hash(key);
    
    t_hval mval = map[on];
    
    if(mval.key == NULL || !strcmp(mval.key, key)) {
        return mval;
    } else {
        while(strcmp(mval.key, key) && on < HMAP_SIZE) {
            on++;
            mval = map[on];
        }
        return mval;
    }
}
