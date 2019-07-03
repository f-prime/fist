#ifndef BST_H
#define BST_H

#define MAX_COMMAND_LENGTH 8

struct bst_node
{
    char key[MAX_COMMAND_LENGTH];
    void *value;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst_node *bst_create(const char *key, void *value);

void bst_free(struct bst_node *root);

void bst_insert(struct bst_node **root, const char *key, void *value);

void *bst_search(struct bst_node *root, const char *key);

#endif // BST_H
