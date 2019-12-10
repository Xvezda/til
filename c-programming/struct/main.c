#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct test_s {
    int dummy;
    char *msg;
} test_t;


static void print_test(test_t *test)
{
    printf("%s\n", test->msg);
}


int main(void)
{
    // It works... now thats interesting 🤔
    print_test(&(test_t) { .msg = (char *)"foobar" });

    return 0;
}

