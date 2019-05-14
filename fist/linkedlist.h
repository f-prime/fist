#ifndef H_LINKEDLIST
#define H_LINKEDLIST

struct LinkedList {
    char *key;
    char **values;
    int num_vals;
    struct t_list *next;
};

typedef struct LinkedList *l_item;

l_item ll_create();
l_item ll_add(l_item list, char *key, char *value);
l_item ll_get(l_item list, unsigned int index);
l_item ll_key(l_item list, char *key);
unsigned int ll_length(l_item list);

#endif
