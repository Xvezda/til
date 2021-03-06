/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#include "linked_list.h"


static linked_list_t *linked_list_wind(const linked_list_t *ref);
/* Getter, Setter */
static inline size_t linked_list_get_size(const linked_list_t *ptr);
static inline void linked_list_set_size(linked_list_t *ptr, size_t size);


linked_list_t *linked_list_new(void)
{
    linked_list_t *ret = malloc(sizeof(*ret));
    linked_list_init(&ret);

    return ret;
}


void linked_list_init(linked_list_t **ref)
{
    if (!ref || !*ref) return;

    (*ref)->data = NULL;
    linked_list_set_size(*ref, 0);

    // Create entry
    linked_list_t *entry = malloc(sizeof(*entry));
    entry->data = NULL;
    // Entry must has size 0 \w not null data
    linked_list_set_size(entry, 0);
    entry->next_ = NULL;

    (*ref)->next_ = entry;
}


void *linked_list_unshift(linked_list_t **ref)
{
    if (!ref || !*ref) return NULL;

    linked_list_t *entry = (*ref)->next_;
    if (!entry->next_) {
        fprintf(stderr, "EmptyError: unshift operation failed."
                        " (linked list is empty)\n");
        return NULL;
    }

    void *ret = NULL;
    void *data = entry->next_->data;
    size_t size = linked_list_get_size(entry->next_);

    DEBUG_PRINT("ref: %p, size: %zu\n", (void*) entry->next_, size);

    if (data) {
        ret = malloc(size);
        memcpy(ret, data, size);
    }
    free(entry->next_->data);
    entry->next_->data = NULL;

    entry->next_ = entry->next_->next_;

    return ret;
}


void linked_list_append(linked_list_t **ref, const void *ptr, size_t size)
{
    if (!ref || !*ref) return;
    if (!ptr || !size) return;

    void *new_item = malloc(size);
    memcpy(new_item, ptr, size);

    linked_list_t *new_node = malloc(sizeof(*new_node));
    if (!new_node) return;

    new_node->data = new_item;
    linked_list_set_size(new_node, size);
    new_node->next_ = NULL;

    DEBUG_PRINT("ref: %p\n", (void*) *ref);

    linked_list_t *last_node = linked_list_wind(*ref);

    DEBUG_PRINT("last_node: %p\n", (void*) last_node);

    assert(last_node != NULL);
    last_node->next_ = new_node;
}


void linked_list_del(linked_list_t **ref)
{
    if (!ref || !*ref) return;

    linked_list_t *curitem = (*ref)->next_;
    do {
        if (curitem->data) free(curitem->data);
        curitem->data = NULL;

        DEBUG_PRINT("free item size: %zu\n", linked_list_get_size(curitem));

        linked_list_set_size(curitem, 0);

        linked_list_t *next = curitem->next_;
        free(curitem);
        curitem = next;
    } while (curitem);

    // Delete list
    free(*ref);
    *ref = NULL;
}


linked_list_t *linked_list_wind(const linked_list_t *ptr)
{
    if (!ptr) return NULL;

    linked_list_t *curitem = (linked_list_t *)ptr;
    while (curitem->next_) {
        curitem = curitem->next_;
    }
    return curitem;
}


static inline size_t
linked_list_get_size(const linked_list_t *ptr)
{
    if (!ptr) return 0;
    return ptr->data_size_;
}


static inline void
linked_list_set_size(linked_list_t *ptr, size_t size)
{
    if (!ptr) return;
    ptr->data_size_ = size;
}

