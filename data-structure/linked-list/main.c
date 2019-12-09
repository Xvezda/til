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

    DEBUG_PRINT("before append: %p, %p\n",
            (void*) list, (void*) list->_next->_next);
    int tmp = 1;
    linked_list_append(&list, &tmp, sizeof(tmp));
    DEBUG_PRINT("after append: %p\n", (void*) list);

    DEBUG_PRINT("before append: %p, %p\n",
            (void*) list, (void*) list->_next->_next);
    tmp = 2;
    linked_list_append(&list, &tmp, sizeof(tmp));
    DEBUG_PRINT("after append: %p\n", (void*) list);

    DEBUG_PRINT("before unshift: %p\n", (void*) list);
    void *item = linked_list_unshift(&list);

    assert(item != NULL);
    DEBUG_PRINT("after unshift: %p\n", (void*) list);

    printf("1st item: %d\n", *(int*)item);
    free(item);

    item = linked_list_unshift(&list);
    assert(item != NULL);

    printf("2nd item: %d\n", *(int*)item);
    free(item);

    char tmp2[] = "Hello, World!";
    DEBUG_PRINT("sizeof tmp2: %zu\n", sizeof(tmp2));
    linked_list_append(&list, tmp2, sizeof(tmp2));

    item = linked_list_unshift(&list);
    printf("last item: %s\n", item);
    free(item);

    // Try extra unshifting
    item = linked_list_unshift(&list);

    linked_list_del(&list);
}


