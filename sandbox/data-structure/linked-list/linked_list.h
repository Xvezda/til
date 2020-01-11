/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#ifdef DEBUG
  #define DEBUG_PRINT(fmt, ...) \
    do { \
      fprintf(stderr, "%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__); \
    } while (0)
#else
  #define DEBUG_PRINT(...) \
    do { } while (0)
#endif


/**
 * First node of linked list is always ``entry''
 * which prevents list pointer return to null when unshifting.
 */
struct linked_list_s {
  /* Public attributes */
  void *data;
  /* Private attributes */
  size_t data_size_;
  struct linked_list_s *next_;
};
typedef struct linked_list_s linked_list_t;


linked_list_t *linked_list_new(void);
void linked_list_init(linked_list_t **ref);
void *linked_list_unshift(linked_list_t **ref);
void linked_list_append(linked_list_t **ref, const void *ptr, size_t size);
void linked_list_del(linked_list_t **ref);


#endif  // LINKED_LIST_H_

