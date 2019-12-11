#include "handlers.h"


/**
 * Type `str` method implementations
 */
obj_t *type_str_init_handler(obj_t *self, ...)
{
    va_list ap;
    va_start(ap, self);

    char *str = va_arg(ap, char *);
    char *ret = malloc(self->size_);

    memcpy(ret, str, self->size_);
    self->ptr_ = ret;

    va_end(ap);

    return self;
}


void type_str_del_handler(obj_t *self)
{
    free(self->ptr_);
    self->ptr_ = NULL;
}


char *type_str_cstr_handler(obj_t *self)
{
    return strdup(self->ptr_);
}


/**
 * Type `int` method implementations
 */
obj_t *type_int_init_handler(obj_t *self, ...)
{
    va_list ap;
    va_start(ap, self);

    int data = va_arg(ap, int);
    int *ret = malloc(self->size_);

    memcpy(ret, &data, self->size_);
    self->ptr_ = ret;

    va_end(ap);

    return self;
}


void type_int_del_handler(obj_t *self)
{
    free(self->ptr_);
    self->ptr_ = NULL;
}


char *type_int_cstr_handler(obj_t *self)
{
    char *ret = NULL;
    int len = snprintf(NULL, 0, "%d", *(int *)self->ptr_);

    ret = malloc(len+1);
    snprintf(ret, len+1, "%d", *(int *)self->ptr_);

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
    int *ret = malloc(self->size_);

    memcpy(ret, ptr, self->size_);
    self->ptr_ = ret;

    va_end(ap);

    return self;
}


void type_int_ptr_del_handler(obj_t *self)
{
    free(self->ptr_);
    self->ptr_ = NULL;
}

char *type_int_ptr_cstr_handler(obj_t *self)
{
    char *ret = NULL;
    int len = snprintf(NULL, 0, "%d", *(int *)self->ptr_);

    ret = malloc(len+1);
    snprintf(ret, len+1, "%d", *(int *)self->ptr_);

    ret[len] = '\0';

    return ret;
}


/**
 * Type `double` method implementations
 */
obj_t *type_double_init_handler(obj_t *self, ...)
{
    va_list ap;
    va_start(ap, self);

    double data = va_arg(ap, double);
    double *ret = malloc(self->size_);

    memcpy(ret, &data, self->size_);
    self->ptr_ = ret;

    va_end(ap);

    return self;
}


void type_double_del_handler(obj_t *self)
{
    free(self->ptr_);
    self->ptr_ = NULL;
}


char *type_double_cstr_handler(obj_t *self)
{
    char *ret = NULL;

    int len = snprintf(NULL, 0, "%lf", *(double *)self->ptr_);
    ret = malloc(len+1);

    snprintf(ret, len+1, "%lf", *(double *)self->ptr_);

    ret[len] = '\0';

    return ret;
}


