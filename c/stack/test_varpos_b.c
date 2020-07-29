#include <stdio.h>


int main(int argc, char **argv)
{
    /* $ diff a b
     *
     * <       movl    $1, -20(%rbp)
     * <       movb    $2, -21(%rbp)
     * ---
     * >       movb    $2, -17(%rbp)
     * >       movl    $1, -24(%rbp)
     *
     * # So, position does matter
     */
    char b = 2;
    int a = 1;

    return 0;
}
