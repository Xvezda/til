#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xobject.h"


#define type_str     1
#define type_int     2
#define type_int_ptr 3
#define type_double  4


obj_t *type_str_init_handler(obj_t *self, ...);
void type_str_del_handler(obj_t *self);
char *type_str_cstr_handler(obj_t *self);

obj_t *type_int_init_handler(obj_t *self, ...);
void type_int_del_handler(obj_t *self);
char *type_int_cstr_handler(obj_t *self);

obj_t *type_int_ptr_init_handler(obj_t *self, ...);
void type_int_ptr_del_handler(obj_t *self);
char *type_int_ptr_cstr_handler(obj_t *self);

obj_t *type_double_init_handler(obj_t *self, ...);
void type_double_del_handler(obj_t *self);
char *type_double_cstr_handler(obj_t *self);


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

