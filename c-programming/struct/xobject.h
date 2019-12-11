#ifndef XOBJECT_H_
#define XOBJECT_H_

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
        .type_ = type, \
        .size_ = sizeof(data), \
        .init_handler_ = type ## _init_handler, \
        .del_handler_ = type ## _del_handler, \
        .cstr_handler_ = type ## _cstr_handler, \
    }, data)

typedef int type_t;

#define type_etc 0

#define CALL_OBJECT_METHOD(obj, method, ...) \
    (obj)-> ## method((obj), __VA_ARGS__)
#define CALL_OBJECT_HANDLER(obj, name) \
    (obj)->name ## _handler_(obj)


struct obj_s;
typedef struct obj_s *(*init_handler_t)(struct obj_s *self, ...);
typedef void (*del_handler_t)(struct obj_s *self);
typedef char *(*cstr_handler_t)(struct obj_s *self);
typedef struct obj_s {
    type_t type_;
    size_t size_;
    void *ptr_;
    init_handler_t init_handler_;
    del_handler_t del_handler_;
    cstr_handler_t cstr_handler_;
} obj_t;


void print_obj(obj_t *obj);


#endif  // XOBJECT_H_
