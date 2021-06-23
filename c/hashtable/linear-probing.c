#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    int value;
};

#define TABLE_SIZE 8
struct node table[TABLE_SIZE];

int get_key(const char *data) {
    return *data;  // Use first character as key
}

int hash_func(int key) {
    return key % TABLE_SIZE;
}

void set_value(const char *data, int value) {
    const int key = get_key(data);
    const int hash = hash_func(key);

    for (int i = hash; i < TABLE_SIZE; ++i) {
        if (!table[i].key) {
            table[i].key = key;
            table[i].value = value;
            break;
        } else if (table[i].key == key) {
            table[i].value = value;
            break;
        }
    }
}

int get_value(const char *data) {
    const int key = get_key(data);
    const int hash = hash_func(key);

    for (int i = hash; i < TABLE_SIZE; ++i) {
        if (table[i].key == key) {
            return table[i].value;
        }
    }
    return 0;
}


int main() {
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
