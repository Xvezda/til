#include <stdio.h>

#define TABLE_SIZE 8
int table[TABLE_SIZE];

#define get_key(s) (*s)
#define hash_func(k) ((k) % TABLE_SIZE)

#define set_value(d, v) \
    do { \
        table[hash_func(get_key(d))] = (v); \
    } while (0)

#define get_value(d) \
    ({ \
        table[hash_func(get_key(d))]; \
    })


int main() {
    set_value("Andy", 42);
    set_value("Bob", 1337);

    printf("Andy: %d\n", get_value("Andy"));
    printf("Bob: %d\n", get_value("Bob"));

    return 0;
}
