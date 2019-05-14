#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

unsigned long HMAP_SIZE = 1000081;

unsigned long hash(char *val) {
    int sum = 0;
    for(int x = 0; x < strlen(val); x++) {
        sum += (int) val[x];
    }
    return sum % HMAP_SIZE;
}

l_item * h_create() {
    l_item *hm = malloc(sizeof(l_item) * HMAP_SIZE);
    for(int i = 0; i < HMAP_SIZE; i++) {
        hm[i] = NULL;
    }
    return hm;
}


l_item *h_add(l_item *ll, char *key, char *value) {
    unsigned long hval = hash(key);
    l_item entry = ll[hval];
    if(entry == NULL) {
        ll[hval] = malloc(sizeof(l_item));
        l_item item = ll_create();
        item = ll_add(item, key, value);
        ll[hval] = item;
    } else {
        ll_add(entry, key, value);
    }
    return ll;
}

l_item h_get(l_item *ll, char *key) {
    unsigned long hval = hash(key);
    l_item entry = ll[hval];
    if(entry == NULL)
        return NULL;
    
    l_item real_entry = ll_key(entry, key);
    return real_entry;
}
