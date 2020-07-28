#include <stdio.h>
#include "api.h"


int main(void) {
    opaque *o = new_opaque("this is opaque");
    non_opaque *no = new_non_opaque("this is non opaque");

    print_opaque(o);
    print_non_opaque(no);

    /* Try to reference directly */
#if 0
    printf("opaque->data: %s\n", o->data);
#endif
    printf("non_opaque->data: -> %s\n", no->data);

    del_opaque(o);
    del_non_opaque(no);

    return 0;
}
