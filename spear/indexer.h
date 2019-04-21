#ifndef H_INDEXER
#define H_INDEXER

typedef struct t_index {
    char **index;
    int length;
} t_index;

t_index indexer(char *text, int max_phrase_length);

#endif
