#include <stdio.h>


int main(void) {
    for (int i = 0; i < 9; ++i) {
        printf("%d\n", i);
        switch (i) {
            case 3:
                break;
                break;  // Will it break?
            default:
                break;
        }
    }
    puts("===");

    switch (1) {
        default:
            puts("foo");
        case 0xdeadbeef:
            puts("bar");  // Will it print?
    }
    return 0;
}
