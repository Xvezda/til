#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *left;
    int value;
    struct node *right;
};


struct node *new_node(int value)
{
    struct node *root = malloc(sizeof(*root));
    if (!root) return NULL;

    root->left = NULL;
    root->value = value;
    root->right = NULL;

    return root;
}

void del_node(struct node *root)
{
    if (!root)
        return;

    fprintf(stderr, "del: %d\n", root->value);

    if (root->left)
        del_node(root->left);

    if (root->right)
        del_node(root->right);

    free(root);
}

void add_node(struct node *root, int value)
{
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

static inline void replace_child(struct node *parent,
                                 struct node *new_child,
                                 struct node *old_child)
{
    if (old_child->value < parent->value)
        parent->left = new_child;
    else
        parent->right = new_child;
}

struct node *find_min(struct node *node, struct node **parent)
{
    while (node && node->left) {
        if (parent) {
            *parent = node;
        }
        node = node->left;
    }
    return node;
}

void remove_child(struct node *parent, struct node *child)
{
#define aorb(a, b) ((a) ? (a) : (b))

    if (!child->left && !child->right) {  // Leaf node
        replace_child(parent, NULL, child);
    } else if (child->left && child->right) {
        struct node *repl = child->right,
                    *repl_parent = child;

        repl = find_min(child->right, &repl_parent);
        replace_child(parent, repl, child);

        repl->left = child->left;
        replace_child(repl_parent, aorb(repl->right, NULL), repl);
        if (repl != child->right)
            repl->right = child->right;

    } else if (child->left || child->right) {
        replace_child(parent, aorb(child->left, child->right), child);
    }
    free(child);
#undef aorb
}

void remove_value(struct node *root, int value)
{
    struct node *cursor = root,
                *parent = NULL;

    while (cursor) {
        if (value == cursor->value) {  // Found
            if (cursor == root) {
                assert(parent == NULL);
                break;
            }
            remove_child(parent, cursor);
            break;
        } else if (value < cursor->value) {
            parent = cursor;
            cursor = cursor->left;
        } else {
            parent = cursor;
            cursor = cursor->right;
        }
    }
}

struct node *find_node(struct node *root, int value)
{
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

void show_nodes(struct node *root)
{
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


int main()
{
#define UNSAFE_ACCESS
    struct node *root = new_node(5);

    add_node(root, 3);
    add_node(root, 7);

#if defined(UNSAFE_ACCESS)
    printf("left: %d\n", root->left->value);
    printf("right: %d\n", root->right->value);
#endif  // defined(UNSAFE_ACCESS)

    puts("=");

    add_node(root, 4);
    add_node(root, 1);

    show_nodes(root);

    puts("=");

    remove_value(root, 4);
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

#if defined(UNSAFE_ACCESS)
    struct node *ptr = find_node(root, 10);
    printf("find 10: %p -> %d\n", ptr, ptr->value);
    printf("10->left: %d\n", ptr->left->value);
    printf("10->right: %d\n", ptr->right->value);

    ptr = find_node(root, 12);
    printf("find 12: %p -> %d\n", ptr, ptr->value);
    printf("12->right: %p -> %d\n", ptr->right, ptr->right->value);
#endif  // defined(UNSAFE_ACCESS)

    remove_value(root, 10);
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
    remove_value(root, 6);
    show_nodes(root);


    puts("=");
    remove_value(root, 5);
    show_nodes(root);

    puts("=");
    remove_value(root, 14);
    show_nodes(root);

    puts("=");

#if defined(UNSAFE_ACCESS)
    ptr = find_node(root, 12);
    printf("find 12: %p -> %d\n", ptr, ptr->value);
#endif  // defined(UNSAFE_ACCESS)

    remove_value(root, 12);
    show_nodes(root);

    puts("=");
    remove_value(root, 10);
    show_nodes(root);

    puts("=");
    remove_value(root, 7);
    show_nodes(root);

    puts("=");
    remove_value(root, 13);
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
    remove_value(root, 2);
    show_nodes(root);

    puts("=");
    remove_value(root, 6);
    show_nodes(root);

    puts("=");
    remove_value(root, 7);
    show_nodes(root);

    puts("=");
    remove_value(root, 3);
    show_nodes(root);

    puts("=");
    remove_value(root, 5);
    show_nodes(root);

    puts("=");
    remove_value(root, 4);
    show_nodes(root);

    del_node(root);

    puts("=");
    root = new_node(10);
    add_node(root, 15);
    add_node(root, 13);
    add_node(root, 18);
    add_node(root, 19);

    show_nodes(root);

    puts("=");
    remove_value(root, 15);

    show_nodes(root);
#if defined(UNSAFE_ACCESS)
    ptr = find_node(root, 19);
    printf("find 19: %p -> %d\n", ptr, ptr->value);

    ptr = find_node(root, 13);
    printf("find 13: %p -> %d\n", ptr, ptr->value);

    ptr = find_node(root, 18);
    printf("find 18: %p -> %d\n", ptr, ptr->value);
#endif  // defined(UNSAFE_ACCESS)

    return 0;
}


