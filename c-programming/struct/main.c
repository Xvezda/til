#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Below is called ``compound literal''
 * Reference: https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html
 */
#define TEST_OBJ(msg_) &(test_t) { .size = sizeof(msg_), .msg = (char *)msg_ }


typedef struct test_s {
    size_t size;
    union {
        int dummy;
        char *msg;
    };
} test_t;


static void print_test(test_t *test)
{
    printf("%s\n", test->msg);
}


int main(void)
{
    // It works... now thats interesting 🤔
    print_test(TEST_OBJ("foobar"));

    return 0;
}

