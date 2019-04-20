#ifndef H_UTILS
#define H_UTILS

typedef struct t_split {
   char **word_array;
   int length;
} t_split;

t_split split(char *text);

int max(int i1, int i2);
int min(int i1, int i2);

#endif
