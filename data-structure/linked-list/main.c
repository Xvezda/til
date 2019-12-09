/**
 * @copyright (C) 2019 Xvezda <https://xvezda.com/>
 */
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"


int main(int argc, char **argv) {
    // Unused variables
    (void) argc;
    (void) argv;
    // END

    linked_list_t *list = linked_list_new();
#ifdef DEBUG
    printf("before unshift: %p\n", (void*) list);
#endif
    int tmp = 1;
    linked_list_append(&list, &tmp, sizeof(int));
    void *item = linked_list_unshift(&list);
#ifdef DEBUG
    printf("after unshift: %p\n", (void*) list);
#endif
    if (!item) {
        linked_list_del(&list);
        return 1;
    }

    printf("%d\n", *(int*)item);
    linked_list_del(&list);

    return EXIT_SUCCESS;
}
