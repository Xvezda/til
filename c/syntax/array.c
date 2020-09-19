#include <stdio.h>


int main(void) {
    printf("%c\n", *(1 + "asdf"));
    // is same as
    printf("%c\n", *("asdf" + 1));
    // is same as
    printf("%c\n", "asdf"[1]);
    // is same as
    printf("%c\n", 1["asdf"]);

    return 0;
}
