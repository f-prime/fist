#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bst_node *bst_create(const char *key, void *value)
{
    struct bst_node *node;

    node = calloc(1, sizeof(struct bst_node));
    if(!node) {
        perror("calloc");
        return NULL;
    }

    strncpy(node->key, key, MAX_COMMAND_LENGTH - 1);
    node->value = value;

    return node;
}

void bst_free(struct bst_node *root) {
    if(!root)
        return;
    if(root->left)
        bst_free(root->left);
    if(root->right)
        bst_free(root->right);
    free(root);
}

void bst_insert(struct bst_node **root, const char *key, void *value) {
    int cmp;
    if(!*root) {
        *root = bst_create(key, value);
        return;
    }
    cmp = strncmp(key, (*root)->key, MAX_COMMAND_LENGTH);
    if(cmp == 0) {
        (*root)->value = value;
    } else if(cmp > 0) {
        return bst_insert(&(*root)->left, key, value);
    } else {
        return bst_insert(&(*root)->right, key, value);
    }
}

void *bst_search(struct bst_node *root, const char *key) {
    int cmp;
    if(!root)
        return NULL;
    cmp = strncmp(key, root->key, MAX_COMMAND_LENGTH);
    if(cmp == 0) {
        return root->value;
    } else if(cmp > 0) {
        return bst_search(root->left, key);
    } else {
        return bst_search(root->right, key);
    }
}
