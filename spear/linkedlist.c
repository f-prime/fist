#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    char *key;
    char **values;
    int num_vals;
    struct LinkedList *next;
};

typedef struct LinkedList *l_item;

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
    strcpy(new->key, key);
    new->values = malloc(sizeof(char*));
    new->values[0] = malloc(sizeof(char) * strlen(value));
    strcpy(new->values[0], value);
    new->num_vals = 1;

    if(list->key == NULL) {
        list = new;
    } else {
        l_item on = list;
        while(on->next != NULL && strcmp(on->key, key)) {
            on = on->next; 
        }
        if(!strcmp(on->key, key)) { 
            free(new->key);
            free(new->values);
            free(new->values[0]);
            free(new);
            
            char **new_vals = realloc(on->values, sizeof(char*) * (on->num_vals + 1));
            new_vals[on->num_vals] = malloc(sizeof(char) * sizeof(value));
            strcpy(new_vals[on->num_vals], value);
            on->values = new_vals;
            on->num_vals++;     
        
        } else {
            on->next = new;
        }
    }
    return list;
}

unsigned int ll_length(l_item list) {
    unsigned int length = 0;
    while(list != NULL) {
        length++;
        list = list->next;
    }

    return length;
}

l_item ll_get(l_item list, unsigned int index) {
    for(int i = 1; i <= index; i++)
        list = list->next;
        if(list == NULL)
            return NULL;
    return list;
}

l_item ll_key(l_item list, char *key) {
    while(list->next != NULL) {
        if(!strcmp(list->key, key)) {
            return list;
        } else {
            list = list->next;
        }
    }
    return NULL;
}
