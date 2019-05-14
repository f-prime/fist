#ifndef H_HASHMAP
#define H_HASHMAP

#include "linkedlist.h"

l_item *h_create();
l_item *h_add(l_item *ll, char *key, char *value);
l_item h_get(l_item *ll, char *key);

#endif
