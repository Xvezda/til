#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define DEF_TREE(T, name) \
    typedef struct name##_node name##_t; \
    struct name##_node { \
        name##_t *left; \
        name##_t *right; \
        T value; \
    }; \
    typedef struct name##_list list_t; \
    struct name##_list { \
        name##_t *ptr; \
        struct name##_list *next; \
    }


DEF_TREE(int, tree);

tree_t *new_tree(int value);
void del_tree(tree_t **ref);
void dfs(tree_t *node, list_t **ref);

list_t *new_list(void);
void del_list(list_t **ref);
void print_list(const list_t *head);
void append(list_t **ref, tree_t *node);


int main(void) {
    tree_t *subtree = new_tree(2);

    tree_t *node = new_tree(1);
    subtree->left = node;

    node = new_tree(3);
    subtree->right = node;

    tree_t *tree = new_tree(4);
    tree->left = subtree;

    node = new_tree(5);
    tree->right = node;

    list_t *list = NULL;
    dfs(tree, &list);
    print_list(list);

    del_tree(&tree);
    assert(tree == NULL);

    del_list(&list);
    assert(list == NULL);

    return 0;
}


tree_t *new_tree(int value) {
    tree_t *ret = malloc(sizeof *ret);
    if (!ret) return NULL;

    memset(ret, 0, sizeof *ret);
    ret->value = value;

    return ret;
}


void del_tree(tree_t **ref) {
    if (!ref || !*ref) return;

    del_tree(&(*ref)->left);
    del_tree(&(*ref)->right);
    free(*ref);

    memset(ref, 0, sizeof *ref);
}


void dfs(tree_t *node, list_t **list) {
    if (!node) return;

    if (node->left) {
        dfs(node->left, list);
    }

    /* printf("%d\n", node->value); */
    append(list, node);

    if (node->right) {
        dfs(node->right, list);
    }
}


list_t *new_list(void) {
    list_t *ret = malloc(sizeof *ret);
    if (!ret) return NULL;

    memset(ret, 0, sizeof *ret);
    return ret;
}


void del_list(list_t **ref) {
    if (!ref || !*ref) return;
    *ref = NULL;
}


void append(list_t **ref, tree_t *node) {
    if (!ref) return;

    if (!*ref) {
        *ref = new_list();
        (*ref)->ptr = node;
        return;
    }
    list_t *item = new_list();
    item->ptr = node;

    list_t *cur = *ref;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = item;
}

void print_list(const list_t *head) {
    list_t *cur = (list_t*)head;
    if (!cur) return;
    do {
        if (cur->ptr) {
            printf("%d\n", cur->ptr->value);
        }
    } while ((cur=cur->next) != NULL);
}

