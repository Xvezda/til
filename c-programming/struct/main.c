#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Below is called ``compound literal''
 * Reference: https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html
 */
#define OBJECT(type, data) \
    &(obj_t) { \
        ._type = type, \
        ._size = sizeof(data), \
        ._ptr = (void *)(data) \
    }


typedef enum type_e {
    TYPE_INT, TYPE_INT_PTR, TYPE_STR, TYPE_ETC
} type_t;

typedef struct obj_s {
    type_t _type;
    size_t _size;
    void *_ptr;
} obj_t;


static void print_obj(obj_t *obj)
{
    char *fmt;
    switch (obj->_type) {
    case TYPE_INT:
    case TYPE_INT_PTR:
        fmt = "%d\n";
        break;
    case TYPE_STR:
        fmt = "%s\n";
        break;
    case TYPE_ETC:
    default:
        fmt = "%p\n";
        break;
    }
    if (obj->_type == TYPE_INT_PTR) {
        printf(fmt, *(int *)obj->_ptr);
        return;
    }
    printf(fmt, obj->_ptr);
}


int main(void)
{
    // It works... now thats interesting 🤔
    print_obj(OBJECT(TYPE_STR, "foobar"));
    char foobar[] = "hello world";
    print_obj(OBJECT(TYPE_STR, foobar));

    print_obj(OBJECT(TYPE_INT, 1234));
    int test = 31337;
    print_obj(OBJECT(TYPE_INT_PTR, &test));

    return 0;
}

