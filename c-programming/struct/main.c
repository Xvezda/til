#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xobject.h"
#include "handlers.h"


#define type_str     1
#define type_int     2
#define type_int_ptr 3
#define type_double  4


int main(void)
{
    // It works... now thats interesting 🤔
    print_obj(OBJECT(type_str, "foobar"));
    char foobar[] = "hello world";
    print_obj(OBJECT(type_str, foobar));

    print_obj(OBJECT(type_int, 1234));
    int test = 31337;
    print_obj(OBJECT(type_int_ptr, &test));

    print_obj(OBJECT(type_double, 987.654));

    return 0;
}

