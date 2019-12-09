#include <stdio.h>

#define STRINGIFY(str) #str

#if 0
intentionally trying to occurring syntax error
...
OK, so it's fine to do this
#endif

#if 0
#error does it work?
#endif

int main(int argc, char **argv) {
    // Do nothing
    asm("nop");

    // It works :/
    #include "hello.txt"

    return 0;
}
