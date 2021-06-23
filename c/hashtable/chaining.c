#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int value;
    struct node *next;
};

// Reduced table size to cause intended collisions
#define TABLE_SIZE 4
struct node *table[TABLE_SIZE];

int get_key(const char *data) {
    return *data;  // Use first character as key
}

int hash_func(int key) {
    return key % TABLE_SIZE;
}

void set_value(const char *data, int value) {
    const int key = get_key(data);
    const int hash = hash_func(key);

    struct node *slot = table[hash];
    while (slot && slot->next) {
        slot = slot->next;
    }

    struct node *new_node = malloc(sizeof(*new_node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    if (slot) {
        slot->next = new_node;
    } else {
        table[hash] = new_node;
    }
}

int get_value(const char *data) {
    const int key = get_key(data);
    const int hash = hash_func(key);

    struct node *slot = table[hash];
    while (slot && slot->next && slot->key != key) {
        slot = slot->next;
    }
    return slot->value;
}

void cleanup() {
    struct node *slot, *next;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        slot = table[i];
        while (slot) {
            printf("cleanup: %d\n", slot->value);
            next = slot->next;

            free(slot);
            slot = next;
        }
        table[i] = NULL;
    }
}


int main() {
    atexit(cleanup);

    set_value("Andy", 42);
    set_value("Bob", 1337);
    set_value("Ian", 777);
    set_value("John", 123);
    set_value("Mike", 456);

#define SHOW_VAL(data)                     \
    do {                                   \
        printf(data ": %d (hash: %d)\n",   \
                get_value(data),           \
                hash_func(get_key(data))); \
    } while (0)

    SHOW_VAL("Andy");
    SHOW_VAL("Bob");
    SHOW_VAL("Ian");
    SHOW_VAL("John");
    SHOW_VAL("Mike");

#undef SHOW_VAL
    return 0;
}
