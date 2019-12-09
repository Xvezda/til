#ifndef _ABSTRACT_ITEM_H
#define _ABSTRACT_ITEM_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GET_ITEM_CSTR(item) ((item)->c_str_(item))


enum item_type_e {
  string_e, char_e, int_e, long_e, float_e,
  double_e, number_e, object_e, null_e
};


/*
 *  warning: declaration of 'struct abs_item_s' will not be visible
 *    outside of this function [-Wvisibility]
 */
struct abs_item_s;  // It will resolve error somehow ¯\_(ツ)_/¯ prototyping?

/* Function pointer typedef */
typedef char* (*cstr_handler_t)(struct abs_item_s* self);

struct abs_item_s {
  enum item_type_e type;
  void *data;
  size_t size;
  // Mimick of obj.c_str() in C++
  cstr_handler_t c_str_;
};
typedef struct abs_item_s abs_item_t;


abs_item_t* item_new(enum item_type_e type,
    void *ptr, size_t size, char* (*handler)(abs_item_t*));
void item_del(abs_item_t* item);


#endif  // _ABSTRACT_ITEM_H
