#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

l_item ll_create() {
    l_item item = malloc(sizeof(struct LinkedList));
    item->key = NULL;
    item->next = NULL;
    item->num_vals = 0;
    item->values = NULL;
    return item;
}

l_item ll_add(l_item list, char *key, char *value) {
    l_item new = ll_create();
    new->key = malloc(sizeof(char) * strlen(key));
    memcpy(new->key, key, strlen(key) + 1);
    new->values = malloc(sizeof(char*));
    new->values[0] = malloc(sizeof(char) * strlen(value));
    memcpy(new->values[0], value, strlen(value) + 1);
    new->num_vals = 1;

    if(list->key == NULL) {
        list = new;
    } else {
        l_item on = list;
        while((l_item) on->next != NULL && strcmp(on->key, key)) {
            on = (l_item) on->next; 
        }
        if(!strcmp(on->key, key)) {  
            for(int i = 0; i < on->num_vals; i++) {
                if(!strcmp(on->values[i], value)) {
                    return list;
                }
            }
            free(new->key);
            free(new->values);
            free(new->values[0]);
            free(new);
            
            char **new_vals = realloc(on->values, sizeof(char*) * (on->num_vals + 1));
            new_vals[on->num_vals] = malloc(sizeof(char) * sizeof(value));
            memcpy(new_vals[on->num_vals], value, strlen(value) + 1);
            on->values = new_vals;
            on->num_vals++;     
        
        } else {
            on->next = (l_item) new;
        }
    }
    return list;
}

unsigned int ll_length(l_item list) {
    unsigned int length = 0;
    while(list != NULL) {
        length++;
        list = (l_item) list->next;
    }

    return length;
}

l_item ll_get(l_item list, unsigned int index) {
    if(index == 0)
        return list;

    for(int i = 1; i <= index; i++)
        list = (l_item) list->next;
        if(list == NULL)
            return NULL;
    return list;
}

l_item ll_key(l_item list, char *key) {
    if (!strcmp(list->key, key)) {
        return list;
    }

    while(list != NULL) {
        if(!strcmp(list->key, key)) {
            return list;
        } else {
            list = (l_item) list->next;
        }
    }
    return NULL;
}
