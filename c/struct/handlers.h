#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xobject.h"


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


#endif  // HANDLERS_H_
