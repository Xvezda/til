/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define super(self) ((self)->super)
#define br() puts("")
#define header(message) puts("=== " message " ===")


typedef struct ancestor ANCESTOR;
struct ancestor {
    ANCESTOR *super;
};

typedef struct parent PARENT;
struct parent {
    /* extends ancestor */
    ANCESTOR *super;
    char *name;
    void (*print)(PARENT *self);
};

typedef struct child CHILD;
struct child {
    /* extends parent */
    PARENT *super;
    char *message;
    void (*print_message)(CHILD *self);
};

typedef struct grandchild GRANDCHILD;
struct grandchild {
    /* extends child */
    CHILD *super;
};


PARENT *new_parent(const char *name);
void del_parent(PARENT *self);
CHILD *new_child(const char *name, const char *message);
void del_child(CHILD *self);
GRANDCHILD *new_grandchild(const char *name, const char *message);
void del_grandchild(GRANDCHILD *self);

/* PARENT::print */
void print_parent(PARENT *self);
void print_grand_child(PARENT *self);

/* CHILD::print_message */
void print_message(CHILD *self);


int main(void) {
    PARENT *parent = new_parent("parent");
    if (!parent) goto parent_failed;
    br();

    CHILD *child = new_child("child", "hi");
    if (!child) goto child_failed;
    br();

    GRANDCHILD *grandchild = new_grandchild("grandchild", "hello");
    if (!grandchild) goto grandchild_failed;
    br();

    header("parent->print()");
    parent->print(parent);

    header("child->print()");
    super(child)->print(super(child));
    header("child->print_message()");
    child->print_message(child);

    header("granchild->print()");
    super(super(grandchild))->print(super(super(grandchild)));
    header("granchild->print_message()");
    super(grandchild)->print_message(super(grandchild));

    br();

    del_grandchild(grandchild);
    br();
grandchild_failed:
    del_child(child);
    br();
child_failed:
    del_parent(parent);
parent_failed:

    return 0;
}


PARENT *new_parent(const char *name) {
    PARENT *ret = malloc(sizeof *ret);
    if (!ret) return NULL;
    super(ret) = NULL;

    ret->name = strdup(name);
    ret->print = print_parent;

    puts("new parent");
    return ret;
}


CHILD *new_child(const char *name, const char *message) {
    CHILD *ret = malloc(sizeof *ret);
    if (!ret) return NULL;

    /* super(name) */
    super(ret) = new_parent(name);

    ret->message = strdup(message);
    ret->print_message = print_message;

    puts("new child");
    return ret;
}


GRANDCHILD *new_grandchild(const char *name, const char *message) {
    GRANDCHILD *ret = malloc(sizeof *ret);
    if (!ret) return NULL;

    super(ret) = new_child(name, message);
    /* override */
    super(super(ret))->print = print_grand_child;

    puts("new grandchild");
    return ret;
}


void del_parent(PARENT *self) {
    if (!self) return;

    free(self->name);
    free(self);
    puts("deleting parent");
}


void del_child(CHILD *self) {
    if (!self) return;

    /* call parent destructor */
    del_parent(super(self));

    free(self->message);
    puts("deleting child");
}


void del_grandchild(GRANDCHILD *self) {
    if (!self) return;

    del_child(super(self));
    puts("deleting grandchild");
}


/* parent->print() */
void print_parent(PARENT *self) {
    if (!self) return;
    printf("this is %s\n", self->name);
}


/* emulating override */
void print_grand_child(PARENT *self) {
    if (!self) return;
    print_parent(self);
    puts("do something different here");
}


/* child->print_message() */
void print_message(CHILD *self) {
    if (!self) return;

    printf("%s say: %s\n", super(self)->name, self->message);
}
