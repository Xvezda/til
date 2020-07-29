#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xobject.h"
#include "handlers.h"


int main(void)
{
    // It works... now thats interesting 🤔
    print_obj(OBJECT(str, "foobar"));
    char foobar[] = "hello world";
    print_obj(OBJECT(str, foobar));

    print_obj(OBJECT(int, 1234));
    int test = 31337;
    print_obj(OBJECT(int_ptr, &test));

    print_obj(OBJECT(double, 987.654));

    return 0;
}

