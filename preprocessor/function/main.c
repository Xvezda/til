#include <stdio.h>


const char *s = __func__;

void foo(void);

int main(void) {
    foo();

    printf("what is s: %02x\n", *s);

    return 0;
}


void foo(void) {
    printf("this is %s\n", __func__);
}
