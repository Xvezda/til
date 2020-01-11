#include "abstract_item.h"


abs_item_t *item_new(item_type_t type,
        void *ptr, size_t size, cstr_handler_t handler)
{
    abs_item_t *ret = malloc(sizeof *ret);

    ret->type = type;
    abs_item_t *data = malloc(size);
    memcpy(data, ptr, size);
    ret->data = data;
    ret->size = size;

    ret->c_str_ = handler;

    return ret;
}


void item_del(abs_item_t *item)
{
    free(item->data);
    free(item);
}
