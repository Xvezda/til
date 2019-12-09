#include "abstract_item.h"


abs_item_t* item_new(enum item_type_e type,
        void *ptr, size_t size, char* (*handler)(abs_item_t *handler)) {
    abs_item_t* ret = malloc(sizeof(abs_item_t));

    ret->type = type;
    abs_item_t* data = malloc(size);
    memcpy(data, ptr, size);
    ret->data = data;
    ret->size = size;

    ret->c_str_ = handler;

    return ret;
}


void item_del(abs_item_t* item) {
    free(item->data);
    free(item);
}
