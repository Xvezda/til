#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *left;
    int value;
    struct node *right;
};

struct node *new_node(int value) {
    struct node *root = malloc(sizeof(*root));
    if (!root) return NULL;

    root->left = NULL;
    root->value = value;
    root->right = NULL;

    return root;
}

void del_node(struct node *root) {
    if (!root)
        return;

    fprintf(stderr, "del: %d\n", root->value);

    if (root->left) {
        del_node(root->left);
    }
    if (root->right) {
        del_node(root->right);
    }
    free(root);
}

void add_node(struct node *root, int value) {
    struct node *node = new_node(value);

    struct node *cursor = root;
    while (cursor) {
        if (value < cursor->value) {
            if (cursor->left) {
                cursor = cursor->left;
            } else {
                cursor->left = node;
                break;
            }
        } else {
            if (cursor->right) {
                cursor = cursor->right;
            } else {
                cursor->right = node;
                break;
            }
        }
    }
}

void rem_node(struct node *root, int value) {
    struct node *cursor = root,
                *parent = NULL;

#define replace_cursor(parent__, cursor__, value__)  \
    do {                                             \
        if ((cursor__)->value < (parent__)->value) { \
            (parent__)->left = (value__);            \
        } else {                                     \
            (parent__)->right = (value__);           \
        }                                            \
    } while (0)

    while (cursor) {
        if (value == cursor->value) {  // Found
            if (cursor == root) {
                assert(parent == NULL);
                break;
            }

            if (!cursor->left && !cursor->right) {  // Leaf node
                replace_cursor(parent, cursor, NULL);
            } else if (cursor->left && cursor->right) {
                struct node *tmp = cursor->right,
                            *tmp_parent = cursor;
                // Find smallest
                while (tmp && tmp->left) {
                    tmp_parent = tmp;
                    tmp = tmp->left;
                }
                replace_cursor(parent, cursor, tmp);
                tmp->left = cursor->left;
                replace_cursor(tmp_parent, tmp,
                        tmp->right ? tmp->right : NULL);

                if (tmp != cursor->right) {
                    tmp->right = cursor->right;
                }
            } else if (cursor->left || cursor->right) {
                replace_cursor(parent, cursor,
                        cursor->left ? cursor->left : cursor->right);
            }
            free(cursor);
            break;
        } else if (value < cursor->value) {
            parent = cursor;
            cursor = cursor->left;
        } else {
            parent = cursor;
            cursor = cursor->right;
        }
    }
    if (root && !parent) {
        del_node(root);
    }
#undef replace_cursor
}

struct node *find_node(struct node *root, int value) {
    struct node *cursor = root;
    while (cursor) {
        if (value == cursor->value) {
            return cursor;
        } else if (value < cursor->value) {
            cursor = cursor->left;
        } else {
            cursor = cursor->right;
        }
    }
    return cursor;
}

void show_nodes(struct node *root) {
    if (!root)
        return;

    if (root->left) {
        show_nodes(root->left);
    }
    printf("%p -> value: %d\n", root, root->value);
    if (root->right) {
        show_nodes(root->right);
    }
}


int main() {
    struct node *root = new_node(5);

    add_node(root, 3);
    add_node(root, 7);

    printf("left: %d\n", root->left->value);
    printf("right: %d\n", root->right->value);

    puts("=");

    add_node(root, 4);
    add_node(root, 1);

    show_nodes(root);

    puts("=");

    rem_node(root, 4);
    show_nodes(root);

    del_node(root);

    puts("=");

    // New tree
    root = new_node(15);
    add_node(root, 10);
    add_node(root, 5);
    add_node(root, 14);
    add_node(root, 12);
    add_node(root, 13);

    show_nodes(root);

    puts("=");

    struct node *ptr = find_node(root, 10);
    printf("find 10: %p -> %d\n", ptr, ptr->value);
    printf("10->left: %d\n", ptr->left->value);
    printf("10->right: %d\n", ptr->right->value);

    ptr = find_node(root, 12);
    printf("find 12: %p -> %d\n", ptr, ptr->value);
    printf("12->right: %p -> %d\n", ptr->right, ptr->right->value);

    rem_node(root, 10);
    show_nodes(root);

    del_node(root);

    puts("=");

    // Another tree
    root = new_node(20);
    add_node(root, 10);
    add_node(root, 5);
    add_node(root, 15);
    add_node(root, 14);
    add_node(root, 12);
    add_node(root, 13);
    add_node(root, 3);
    add_node(root, 6);
    add_node(root, 7);

    show_nodes(root);

    puts("=");
    // Remove right
    rem_node(root, 6);
    show_nodes(root);


    puts("=");
    rem_node(root, 5);
    show_nodes(root);

    puts("=");
    rem_node(root, 14);
    show_nodes(root);

    puts("=");
    ptr = find_node(root, 12);
    printf("find 12: %p -> %d\n", ptr, ptr->value);
    rem_node(root, 12);
    show_nodes(root);

    puts("=");
    rem_node(root, 10);
    show_nodes(root);

    puts("=");
    rem_node(root, 7);
    show_nodes(root);

    puts("=");
    rem_node(root, 13);
    show_nodes(root);

    del_node(root);
    puts("=");

    root = new_node(1);
    add_node(root, 2);
    add_node(root, 3);
    add_node(root, 6);
    add_node(root, 5);
    add_node(root, 4);
    add_node(root, 7);

    show_nodes(root);

    puts("=");
    rem_node(root, 2);
    show_nodes(root);

    puts("=");
    rem_node(root, 6);
    show_nodes(root);

    puts("=");
    rem_node(root, 7);
    show_nodes(root);

    puts("=");
    rem_node(root, 3);
    show_nodes(root);

    puts("=");
    rem_node(root, 5);
    show_nodes(root);

    puts("=");
    rem_node(root, 4);
    show_nodes(root);

    del_node(root);

    return 0;
}


