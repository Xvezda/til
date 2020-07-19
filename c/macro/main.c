#include <stdio.h>

#define ARGS(...) { __VA_ARGS__ }
#define LEN(iter) ((int)(sizeof(iter) / sizeof(iter[0])))
#define FOREACH(idx, iter) for (int (idx) = 0; (idx) < LEN(iter); ++(idx))


int foo(void);

int main(void) {
    // Interesting...
    int arr[] = ARGS(1, 2, 3, 4, foo());
    FOREACH(i, arr) {
        printf("%d\n", arr[i]);
    }
    return 0;
}


int foo(void) {
    return 5;
}


