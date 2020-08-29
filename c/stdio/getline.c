#include <stdio.h>
#include <stdlib.h>


int main(void) {
    /* `man getline` */
    size_t size = 0;
    char *str = NULL;

    ssize_t written;
    while ((written=getline(&str, &size, stdin)) > 0) {
        // Written characters include newline, So it's redundant.
        printf("%s" /* "\n" */, str);
    }
    free(str);

    return 0;
}

