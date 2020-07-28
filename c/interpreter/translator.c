#include "translator.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


struct translator {
    sb_t *data;
};


trans_t *new_translator(void) {
    trans_t *ret = malloc(sizeof *ret);
    if (!ret) return NULL;

    ret->data = new_sb(NULL);

    return ret;
}


void del_translator(trans_t *self) {
    if (!self) return;

    del_sb(self->data);
    free(self);
}


void translate(trans_t *self, const NODE *root) {
    if (!self || !root) return;

#if (USE_LISP_STYLE)
    if (root->tokptr->type != TOKEN_INT) {
        sb_append(self->data, "( ");
    }
    sb_append(self->data, root->tokptr->value);
    sb_append(self->data, " ");
#endif
    translate(self, root->left);
    translate(self, root->right);

#if (USE_LISP_STYLE)
    if (root->tokptr->type != TOKEN_INT) {
        sb_append(self->data, ") ");
    }
#else
    sb_append(self->data, root->tokptr->value);
    sb_append(self->data, " ");
#endif
}


void translator_print(trans_t *self) {
    if (!self) return;
    printf("%s\n", sb_to_str(self->data));
}

