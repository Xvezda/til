#include <stdio.h>


void foo(void);
void bar(void);

int main(void) {
    bar();
#define EGG "ham"
    foo();
    bar();

    return 0;
}


void foo(void) {
#undef EGG
#define EGG "spam"
    printf("%s\n", EGG);
}


void bar(void) {
    printf("%s\n", EGG);
}
