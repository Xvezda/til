#include <stdio.h>
#include <stdlib.h>

/**
 * Recursion -> (Top => Down)
 */
int sum(int n)
{
    if (n <= 1) return 1;
    return sum(n - 1) + n;
}

/**
 * Do not calculate inside a parameter
 * pass parameter "as is"
 */
/*
int sum(int n, int prev)
{
    int next;
    if (n == 0) return prev + n;

    prev = prev + n;
    next = n - 1;

    return sum(next, prev);
}
*/


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s [NUMBER]\n", argv[0]);
        return 1;
    }
    // sum(10) -> 55
    // sum(1) -> 1
    // sum(2) -> 3
    // sum(3) -> 6
    // 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10
    int n = atoi(argv[1]);
    printf("%d\n", sum(n));
    /* printf("%d\n", sum(n, 0)); */

    return 0;
}
