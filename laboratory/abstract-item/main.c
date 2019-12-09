#include "abstract_item.h"


char* nulltype_handler(abs_item_t *self) {
    (void) self;
    return "<Type 'NULL'>";
}

char* int_handler(abs_item_t *self) {
    if (!self) return NULL;

    int len = snprintf(NULL, 0, "%d", *(int*)self->data);
    char *ret = malloc(len+1);
    if (!ret) return NULL;

    snprintf(ret, len+1, "%d", *(int*)self->data);
    ret[len] = '\0';

    return ret;
}

int main(int argc, char **argv) {
    /* Unused variables */
    (void) argc;
    (void) argv;
    /* END */

    abs_item_t *item = item_new(null_e, NULL, 0, nulltype_handler);
    printf("1st item: %s\n", GET_ITEM_CSTR(item));

    item_del(item);

    int number = 1234;
    item = item_new(int_e, &number, sizeof number, int_handler);

    char *str = GET_ITEM_CSTR(item);
    printf("2nd item: %s\n", str);
    free(str);

    item_del(item);

    return 0;
}
