#ifndef BST_H
#define BST_H

#include "dstring.h"
#include "hashmap.h"

#define MAX_COMMAND_LENGTH 8

typedef int (*command_handler_t)(hashmap *hm, int fd, dstringa params);

struct bst_node {
    char key[MAX_COMMAND_LENGTH];
    command_handler_t value;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst_node *bst_create(const char *key, command_handler_t value);

void bst_free(struct bst_node *root);

void bst_insert(struct bst_node **root, const char *key, command_handler_t value);

command_handler_t bst_search(struct bst_node *root, const char *key);

#endif//BST_H
