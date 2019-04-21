#ifndef H_HASHMAP
#define H_HASHMAP

typedef struct t_hval {
    char *key;
    char **values;
    int length;
} t_hval;

t_hval *h_create();
t_hval *h_add(t_hval *map, char *key, char *value);
t_hval h_get(t_hval *map, char *key);

#endif
