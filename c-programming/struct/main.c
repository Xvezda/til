#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST_OBJ(msg_) &(test_t) { .msg = (char *)msg_ }


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
    print_test(TEST_OBJ("foobar"));

    return 0;
}

