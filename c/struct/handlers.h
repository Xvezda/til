#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xobject.h"


obj_t *str_init_handler(obj_t *self, ...);
void str_del_handler(obj_t *self);
char *str_cstr_handler(obj_t *self);

obj_t *int_init_handler(obj_t *self, ...);
void int_del_handler(obj_t *self);
char *int_cstr_handler(obj_t *self);

obj_t *int_ptr_init_handler(obj_t *self, ...);
void int_ptr_del_handler(obj_t *self);
char *int_ptr_cstr_handler(obj_t *self);

obj_t *double_init_handler(obj_t *self, ...);
void double_del_handler(obj_t *self);
char *double_cstr_handler(obj_t *self);


#endif  // HANDLERS_H_
