#include "translator.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#define LISP_STYLE 1

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


#ifdef LISP_STYLE
void translate(trans_t *self, const NODE *root) {
    if (!self || !root) return;

    if (root->ptr->type != T_INT) {
        sb_append(self->data, "( ");
    }
    sb_append(self->data, root->ptr->value);
    sb_append(self->data, " ");

    translate(self, root->left);
    translate(self, root->right);

    if (root->ptr->type != T_INT) {
        sb_append(self->data, ") ");
    }
}

#else

void translate(trans_t *self, const NODE *root) {
    if (!self || !root) return;

    if (root->left) {
        translate(self, root->left);
    }

    if (root->right) {
        translate(self, root->right);
    }

    /* Reverse Polish Notation (RPN) */
    sb_append(self->data, root->ptr->value);
    sb_append(self->data, " ");
}
#endif  // ifdef LISP_STYLE


void translator_print(trans_t *self) {
    if (!self) return;
    printf("%s\n", sb_to_str(self->data));
}

