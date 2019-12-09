/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


struct linked_list_s {
  void *data;
  size_t size;
  struct linked_list_s *next;
};
typedef struct linked_list_s linked_list_t;

linked_list_t* linked_list_new(void);
void linked_list_init(linked_list_t **ref);
void* linked_list_unshift(linked_list_t **ref);
void linked_list_append(linked_list_t **ref, void *ptr, size_t size);
void linked_list_del(linked_list_t **ref);

#endif  // _LINKED_LIST_H
