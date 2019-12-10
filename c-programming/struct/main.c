#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xobject.h"


#define type_str     1
#define type_int     2
#define type_int_ptr 3


obj_t *type_str_init_handler(obj_t *self, ...);
void type_str_del_handler(obj_t *self);
char *type_str_cstr_handler(obj_t *self);

obj_t *type_int_init_handler(obj_t *self, ...);
void type_int_del_handler(obj_t *self);
char *type_int_cstr_handler(obj_t *self);

obj_t *type_int_ptr_init_handler(obj_t *self, ...);
void type_int_ptr_del_handler(obj_t *self);
char *type_int_ptr_cstr_handler(obj_t *self);


int main(void)
{
    // It works... now thats interesting 🤔
    print_obj(OBJECT(type_str, "foobar"));
    char foobar[] = "hello world";
    print_obj(OBJECT(type_str, foobar));

    print_obj(OBJECT(type_int, 1234));
    int test = 31337;
    print_obj(OBJECT(type_int_ptr, &test));

    return 0;
}


/**
 * Type `str` method implementations
 */
obj_t *type_str_init_handler(obj_t *self, ...)
{
    va_list ap;
    va_start(ap, self);

    char *str = va_arg(ap, char *);
    char *ret = malloc(self->_size);

    memcpy(ret, str, self->_size);
    self->_ptr = ret;

    va_end(ap);

    return self;
}


void type_str_del_handler(obj_t *self)
{
    free(self->_ptr);
    self->_ptr = NULL;
}


char *type_str_cstr_handler(obj_t *self)
{
    return strdup(self->_ptr);
}


/**
 * Type `int` method implementations
 */
obj_t *type_int_init_handler(obj_t *self, ...)
{
    va_list ap;
    va_start(ap, self);

    int data = va_arg(ap, int);
    int *ret = malloc(self->_size);

    memcpy(ret, &data, self->_size);
    self->_ptr = ret;

    va_end(ap);

    return self;
}


void type_int_del_handler(obj_t *self)
{
    free(self->_ptr);
    self->_ptr = NULL;
}


char *type_int_cstr_handler(obj_t *self)
{
    char *ret = NULL;
    int len = snprintf(NULL, 0, "%d", *(int *)self->_ptr);

    ret = malloc(len+1);
    snprintf(ret, len+1, "%d", *(int *)self->_ptr);

    ret[len] = '\0';

    return ret;
}


/**
 * Type `intptr` method implementations
 */
obj_t *type_int_ptr_init_handler(obj_t *self, ...)
{
    va_list ap;
    va_start(ap, self);

    int *ptr = va_arg(ap, int *);
    int *ret = malloc(self->_size);

    memcpy(ret, ptr, self->_size);
    self->_ptr = ret;

    va_end(ap);

    return self;
}


void type_int_ptr_del_handler(obj_t *self)
{
    free(self->_ptr);
    self->_ptr = NULL;
}


char *type_int_ptr_cstr_handler(obj_t *self)
{
    char *ret = NULL;
    int len = snprintf(NULL, 0, "%d", *(int *)self->_ptr);

    ret = malloc(len+1);
    snprintf(ret, len+1, "%d", *(int *)self->_ptr);

    ret[len] = '\0';

    return ret;
}


