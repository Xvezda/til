/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linked_list.h"


static void run_test(void);


int main(int argc, char **argv) {
    // Unused variables
    (void) argc;
    (void) argv;
    // END

    run_test();

    return EXIT_SUCCESS;
}


static void run_test(void) {
    linked_list_t *list = linked_list_new();

    DEBUG_PRINT("before append: %p, %p\n", (void*) list, (void*) list->_next);
    int tmp = 1;
    linked_list_append(&list, &tmp, sizeof(int));
    DEBUG_PRINT("after append: %p\n", (void*) list);

    DEBUG_PRINT("before append: %p, %p\n", (void*) list, (void*) list->_next);
    tmp = 2;
    linked_list_append(&list, &tmp, sizeof(int));
    DEBUG_PRINT("after append: %p\n", (void*) list);

    DEBUG_PRINT("before unshift: %p\n", (void*) list);
    void *item = linked_list_unshift(&list);

    assert(item != NULL);
    DEBUG_PRINT("after unshift: %p\n", (void*) list);

    printf("%d\n", *(int*)item);

    item = linked_list_unshift(&list);
    assert(item != NULL);

    printf("%d\n", *(int*)item);

    linked_list_del(&list);
}


