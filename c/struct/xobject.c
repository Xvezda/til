#include "xobject.h"


inline void print_obj(obj_t *obj)
{
    printf("%s\n", CALL_OBJECT_HANDLER(obj, cstr));
}

