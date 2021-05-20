#include <stdio.h>


int main(void) {
#if 0
    printf("\0");  // Not gonna work
#endif
    fwrite("\0", 1, 1, stdout);  // This works

    char hello[] = "Hello\0 World";
    printf("%s\n", hello);  // Hello
    fwrite(hello, 1, sizeof(hello) - 1, stdout);  // Hello\0 world

    putchar('\n');

    return 0;
}
