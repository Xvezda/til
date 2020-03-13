#include <stdio.h>
#include <stdlib.h>

/**
 * Recursion -> (Top => Down)
 */
/*
int fibo(int n)
{
    if (n == 1 || n == 0) return 1;
    return fibo(n-2) + fibo(n-1);
}
*/

/**
 * Do not calculate inside a parameter
 * pass parameter "as is"
 */
int fibo(int n, int prev, int prevprev)
{
    if (n == 0) return prevprev;

    prev = n + prev;
    prevprev = prev;

    return fibo(n-1, prev, prevprev);
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s [NUMBER]\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    /* printf("%d\n", fibo(n)); */
    printf("%d\n", fibo(n, 0, 0));

    return 0;
}
