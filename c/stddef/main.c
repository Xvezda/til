#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#define USE_CUSTOM_MACRO /* TOGGLE */
#if defined(USE_CUSTOM_MACRO)
# undef offsetof
# include <stdint.h>
# define offsetof(t, m) ((uintptr_t)&(((t *)NULL)->m))
#endif

#define SHOW_ADDR(v) printf(#v "\t: %p\n", &(v))
#define SHOW_OFFSET(p, m) \
    printf(#p " => " #m "\t: %zu\n", \
            offsetof(typeof(p), m))

#define container_of(p, t, m) \
    ((t *)((char *)(p) - offsetof(t, m)))
#define SHOW_PARENT(p, t, m) \
    printf("if " #p " is member of " #t "\t: %p\n", \
            container_of(p, t, m))
#define ___ puts("");


struct test {
    int a;
    int b;
    char c;
    short d;
};


int main(void)
{
    struct test t;

    SHOW_ADDR(t);
    SHOW_ADDR(t.a);
    SHOW_ADDR(t.b);
    SHOW_ADDR(t.c);
    SHOW_ADDR(t.d);

    SHOW_OFFSET(t, d);

    short *dp = &t.d;
    SHOW_PARENT(dp, struct test, d);

    ___

    struct test *tp = &t;
    SHOW_ADDR(tp);
    SHOW_ADDR(tp->a);
    SHOW_ADDR(tp->b);
    SHOW_ADDR(tp->c);
    SHOW_ADDR(tp->d);

    ___

    tp = (struct test *)0;
    SHOW_ADDR(tp->a);
    SHOW_ADDR(tp->b);
    SHOW_ADDR(tp->c);
    SHOW_ADDR(tp->d);

    return 0;
}

