/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#include "linked_list.h"


static linked_list_t* linked_list_wind(linked_list_t **ref);
/* Getter, Setter */
static inline size_t linked_list_get_size(const linked_list_t *ptr);
static inline void linked_list_set_size(linked_list_t *ptr, size_t size);


linked_list_t* linked_list_new(void) {
    linked_list_t *ret = malloc(sizeof(linked_list_t));
    linked_list_init(&ret);

    return ret;
}


void linked_list_init(linked_list_t **ref) {
    if (!ref || !*ref) return;

    (*ref)->data = NULL;
    linked_list_set_size(*ref, 0);

    // Create entry
    linked_list_t *entry = malloc(sizeof(linked_list_t));
    entry->data = NULL;
    // Entry must has size 0 \w not null data
    linked_list_set_size(entry, 0);
    entry->_next = NULL;

    (*ref)->_next = entry;
}


void* linked_list_unshift(linked_list_t **ref) {
    if (!ref || !*ref) return NULL;

    if (!(*ref)->_next->_next) {
        fprintf(stderr, "EmptyError: unshift operation failed."
                        " (linked list is empty)\n");
        return NULL;
    }

    void *ret = NULL;
    void *data = (*ref)->_next->_next->data;
    size_t size = linked_list_get_size((*ref)->_next->_next);

    DEBUG_PRINT("%s:%d: ref: %p, size: %zu\n",
            __FILE__, __LINE__, (void*) (*ref)->_next->_next, size);

    if (data) {
        ret = malloc(size);
        memcpy(ret, data, size);
    }
    free((*ref)->_next->_next->data);
    (*ref)->_next->_next->data = NULL;

    (*ref)->_next->_next = (*ref)->_next->_next->_next;

    return ret;
}


void linked_list_append(linked_list_t **ref, const void *ptr, size_t size) {
    if (!ref || !*ref) return;
    if (!ptr || !size) return;

    void *new_item = malloc(size);
    memcpy(new_item, ptr, size);

    linked_list_t *new_node = malloc(sizeof(linked_list_t));
    if (!new_node) return;

    new_node->data = new_item;
    linked_list_set_size(new_node, size);
    new_node->_next = NULL;

    DEBUG_PRINT("%s:%d: ref: %p\n", __FILE__, __LINE__, (void*) *ref);

    linked_list_t *last_node = linked_list_wind(ref);

    DEBUG_PRINT("%s:%d: last_node: %p\n", __FILE__, __LINE__, (void*) last_node);

    assert(last_node != NULL);
    last_node->_next = new_node;
}


void linked_list_del(linked_list_t **ref) {
    if (!ref || !*ref) return;

    linked_list_t *curitem = (*ref)->_next;
    do {
        if (curitem->data) free(curitem->data);
        curitem->data = NULL;

        DEBUG_PRINT("free item size: %zu\n", linked_list_get_size(curitem));

        linked_list_set_size(curitem, 0);

        linked_list_t *next = curitem->_next;
        free(curitem);
        curitem = next;
    } while (curitem);

    // Delete list
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


static inline size_t linked_list_get_size(const linked_list_t *ptr) {
    if (!ptr) return 0;
    return ptr->_data_size;
}


static inline void linked_list_set_size(linked_list_t *ptr, size_t size) {
    if (!ptr) return;
    ptr->_data_size = size;
}

