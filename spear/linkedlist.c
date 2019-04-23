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
    return item;
}

l_item ll_add(l_item list, char *key, char *value) {
    l_item new = ll_create();
    new->key = malloc(sizeof(char) * strlen(key));
    strcpy(new->key, key);
    new->values = malloc(sizeof(char*));
    new->values[0] = malloc(sizeof(char) * strlen(value));
    strcpy(new->values[0], value);
    if(list->key == NULL) {
        list = new;
    } else {
        l_item on = list;
        while(on->next != NULL) {
            on = on->next; 
        }

        on->next = new;
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
    unsigned int length = ll_length(list);
    if(length <= index)
        return NULL;
    for(int i = 1; i <= index; i++)
        list = list->next;
    return list;
}

l_item ll_key(l_item list, char *key) {
    unsigned int length = ll_length(list);
    for(int i = 1; i <= length; i++)
        if(!strcmp(key, list->key))
            break;
    return list;
}
