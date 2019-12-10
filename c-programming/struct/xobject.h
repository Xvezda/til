#ifndef _XOBJECT_H
#define _XOBJECT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * Below is called ``compound literal''
 * Reference: https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html
 */
#define OBJECT(type, data) \
    type ## _init_handler(&(obj_t) { \
        ._type = type, \
        ._size = sizeof(data), \
        ._init_handler = type ## _init_handler, \
        ._del_handler = type ## _del_handler, \
        ._cstr_handler = type ## _cstr_handler, \
    }, data)

typedef int type_t;

#define type_etc 0

#define CALL_OBJECT_METHOD(obj, method, ...) \
    (obj)-> ## method((obj), __VA_ARGS__)
#define CALL_OBJECT_HANDLER(obj, name) \
    (obj)->_ ## name ## _handler(obj)


struct obj_s;
typedef struct obj_s *(*init_handler_t)(struct obj_s *self, ...);
typedef void (*del_handler_t)(struct obj_s *self);
typedef char *(*cstr_handler_t)(struct obj_s *self);
typedef struct obj_s {
    type_t _type;
    size_t _size;
    void *_ptr;
    init_handler_t _init_handler;
    del_handler_t _del_handler;
    cstr_handler_t _cstr_handler;
} obj_t;


void print_obj(obj_t *obj);


#endif  // _XOBJECT_H
