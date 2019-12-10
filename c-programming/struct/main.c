#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct test_s {
    int dummy;
    char *msg;
} test_t;


test_t *test_new(void);
void test_init(test_t *ptr);
void test_del(test_t *ptr);
static void print_test(test_t *test);


int main(void)
{
    test_t *v = test_new();

    v = &(test_t) { .msg = strdup("foobar") };

    print_test(v);
    test_del(v);

    return 0;
}


test_t *test_new(void)
{
    test_t *ret = malloc(sizeof(*ret));
    test_init(ret);

    return ret;
}


void test_init(test_t *ptr)
{
    ptr->msg = NULL;
}


void test_del(test_t *ptr)
{
    free(ptr->msg);
    free(ptr);
}


static void print_test(test_t *test)
{
    printf("%s\n", test->msg);
}

