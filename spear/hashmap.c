#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HMAP_SIZE 1000

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
    // Need to append to a 2D array of h_vals
    char **values = malloc(sizeof(char*));
    values[0] = malloc(strlen(val) * sizeof(char));
    values[0] = val;
    t_hval entry = {key, values, 1};
    map[hash(key)] = entry;
    return map;
}

t_hval *h_create() {
    // Need to create a 2D array of t_hvals
    t_hval *map = malloc(HMAP_SIZE * sizeof(t_hval));
    return map;
}

t_hval h_get(t_hval *map, char *key) {
    return map[hash(key)];
}
