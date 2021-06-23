#include <stdio.h>

#define TABLE_SIZE 8
int table[TABLE_SIZE];

#define get_key(s) (*s)
#define hash_func(k) ((k) % TABLE_SIZE)

int main() {
    char *k1 = "Andy";
    table[hash_func(get_key(k1))] = 42;

    char *k2 = "Bob";
    table[hash_func(get_key(k2))] = 1337;

    printf("Andy: %d\n", table[hash_func(get_key(k1))]);
    printf("Bob: %d\n", table[hash_func(get_key(k2))]);

    return 0;
}
