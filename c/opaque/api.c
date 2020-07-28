#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "api.h"

/* Let's use macro to define same structure functions
 * with different types
 */
#define DEF_ALL(type) \
    DEF_NEW(type)     \
    DEF_PRINT(type)   \
    DEF_DEL(type)     \

#define DEF_NEW(type)                    \
    type *new_##type(const char *src) {  \
        type *ret = malloc(sizeof *ret); \
        if (!ret) return NULL;           \
        ret->data = strdup(src);         \
        return ret;                      \
    }

#define DEF_PRINT(type)                     \
    void print_##type(type *self) {         \
        if (!self) return;                  \
        printf(#type ": %s\n", self->data); \
    }

#define DEF_DEL(type)             \
    void del_##type(type *self) { \
        if (!self) return;        \
        free(self->data);         \
        free(self);               \
    }


// Implementation of opaque type
struct opaque {
    char *data;
};

// Define all interfaces
DEF_ALL(opaque)
DEF_ALL(non_opaque)

