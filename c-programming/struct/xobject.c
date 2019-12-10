#include "xobject.h"


inline void print_obj(obj_t *obj)
{
#if 0
    char *fmt;
    switch (obj->_type) {
    // Mixing primitive type with pointer is actually not a good idea
    case type_int:  // 😔
    case type_int_ptr:
        fmt = "%d\n";
        break;
    case type_str:
        fmt = "%s\n";
        break;
    case type_etc:
    default:
        fmt = "%p\n";
        break;
    }
    if (obj->_type == type_int_ptr) {
        printf(fmt, *(int *)obj->_ptr);
        return;
    }
    printf(fmt, obj->_ptr);
#endif
    // Now it's safer 🙂
    printf("%s\n", CALL_OBJECT_HANDLER(obj, cstr));
}

