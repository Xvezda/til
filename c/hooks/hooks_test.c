#include <stdio.h>


typedef void (*xcb_t)(void);
typedef struct xobj_s {
    xcb_t  pre_hook;
    char  *msg;
    xcb_t  post_hook;
} xobj_t;

void init(xobj_t *ref);
void print_with_hooks(xobj_t *self);

static void pre_hook(void);
static void post_hook(void);


int main(void)
{
    xobj_t obj;
    init(&obj);

#ifdef PREHOOK
    obj.pre_hook = pre_hook;
#endif

    obj.msg = "bar";

#ifdef POSTHOOK
    obj.post_hook = post_hook;
#endif

    print_with_hooks(&obj);

    return 0;
}


void init(xobj_t *ref) {
    ref->pre_hook = NULL;
    ref->msg = NULL;
    ref->post_hook = NULL;
}

void print_with_hooks(xobj_t *self) {
    if (!self->pre_hook) goto skip;
    self->pre_hook();

skip:
    if (!self->msg) goto end;
    printf("%s\n", self->msg);

end:
    if (!self->post_hook) return;
    self->post_hook();
}

void pre_hook(void) {
    puts("foo");
}

void post_hook(void) {
    puts("baz");
}

