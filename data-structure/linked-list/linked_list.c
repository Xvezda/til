/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#include "linked_list.h"


static linked_list_t* linked_list_wind(linked_list_t **ref);
/* Getter, Setter */
static inline size_t linked_list_get_size(linked_list_t *ptr);
static inline void linked_list_set_size(linked_list_t *ptr, size_t size);


linked_list_t* linked_list_new(void) {
    linked_list_t *ret = malloc(sizeof(linked_list_t));
    linked_list_init(&ret);

    return ret;
}


void linked_list_init(linked_list_t **ref) {
    if (!ref || !*ref) return;

    (*ref)->data = NULL;
    (*ref)->_next = NULL;
    (*ref)->_data_size = 0;
}


void* linked_list_unshift(linked_list_t **ref) {
    if (!ref || !*ref) return NULL;

    void *ret = NULL;
    void *data = (*ref)->data;
    size_t size = linked_list_get_size(*ref);

    if (data) {
        ret = malloc(size);
        memcpy(ret, data, size);
    }
    free((*ref)->data);
    (*ref)->data = NULL;

    *ref = (*ref)->_next;

    return ret;
}


void linked_list_append(linked_list_t **ref, void *ptr, size_t size) {
    if (!ref || !*ref) return;
    if (!ptr || !size) return;

    void *new_item = malloc(size);
    memcpy(new_item, ptr, size);

    linked_list_t *new_node = malloc(sizeof(linked_list_t));
    if (!new_node) return;

    new_node->data = new_item;
    linked_list_set_size(new_node, size);
    new_node->_next = NULL;

    linked_list_t *last_node = linked_list_wind(ref);
    if (!last_node) return;

    if (last_node == *ref) {
        *ref = new_node;
    }
    last_node->_next = new_node;
}


void linked_list_del(linked_list_t **ref) {
    if (!ref || !*ref) return;

    linked_list_t *curitem = *ref;
    do {
        free(curitem->data);
        curitem->data = NULL;
#ifdef DEBUG
        printf("free item size: %zu\n", linked_list_get_size(curitem));
#endif
        linked_list_set_size(curitem, 0);

        linked_list_t *next = curitem->_next;
        free(curitem);
        curitem = next;
    } while(curitem);

    free(*ref);
    *ref = NULL;
}


linked_list_t* linked_list_wind(linked_list_t **ref) {
    if (!ref || !*ref) return NULL;

    linked_list_t *curitem = *ref;
    while (curitem->_next) {
        curitem = curitem->_next;
    }
    return curitem;
}


static inline size_t linked_list_get_size(linked_list_t *ptr) {
    if (!ptr) return 0;
    return ptr->_data_size;
}


static inline void linked_list_set_size(linked_list_t *ptr, size_t size) {
    if (!ptr) return;
    ptr->_data_size = size;
}

