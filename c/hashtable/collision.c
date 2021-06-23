#include <stdio.h>

#define TABLE_SIZE 4
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
    set_value("Ian", 777);

    printf("Andy: %d (hash: %d)\n",
            get_value("Andy"),
            hash_func(get_key("Andy")));  // Expect: 42

    printf("Bob: %d (hash: %d)\n",
            get_value("Bob"),
            hash_func(get_key("Bob")));

    printf("Ian: %d (hash: %d)\n",
            get_value("Ian"),
            hash_func(get_key("Ian")));

    return 0;
}
