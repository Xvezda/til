#include "parser.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


table_t parser_error_table = {
    DEF_ERROR(P_OK, "unexpected error: exit while state ok"),
    DEF_ERROR(P_ERROR, "syntax error occurred"),
    DEF_ERROR(P_DIVIDE_BY_ZERO, "divide by zero error"),
};


parser_t *new_parser(const TOKEN *lexer) {
    parser_t *ret = malloc(sizeof *ret);
    if (!ret || !lexer) return NULL;

    ret->flag = P_OK;
    ret->head = lexer;
    ret->ptr = (TOKEN*)ret->head;

    ret->error_table = (table_t*)parser_error_table;

    return ret;
}


int del_parser(parser_t *parser) {
    if (!parser) return 1;

    parser->ptr = NULL;
    free(parser);

    return 0;
}


TOKEN *next(parser_t *self) {
    if (!self) return NULL;
    self->ptr = next_token(self->ptr);
    return self->ptr;
}


NODE *parse_expr2(parser_t *self) {
    assert(self != NULL);
    NODE *ast = NULL;
    NODE *node = new_node(visit_operator);

    NODE *left = parse_expr1(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr2: left: %s\n", node->left->ptr->value);

    NODE *right = NULL;

    node->ptr = self->ptr;

    while (self->ptr
            && (self->ptr->type == T_ADD || self->ptr->type == T_SUB)) {
        if (!node) {
            node = new_node(visit_operator);
        }
        if (!node->ptr) {
            node->ptr = self->ptr;
        }
        next(self);

        right = parse_expr1(self);
        node->right = right;
        if (!node->right) goto error;
        DEBUG_PRINTF("expr2: right: %s\n", node->right->ptr->value);
        if (!ast) {
            ast = node;
        } else {
            node->left = ast;
            ast = node;
        }
        node = NULL;
    }
    if (!ast) {
        ast = node->left;
    }
    return ast;
error:
    self->flag = P_ERROR;
    return NULL;
}


NODE *parse_expr1(parser_t *self) {
    assert(self != NULL);
    NODE *ast = NULL;
    NODE *node = new_node(visit_operator);

    NODE *left = parse_factor(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr1: left: %s\n", node->left->ptr->value);

    NODE *right = NULL;

    node->ptr = self->ptr;

    while (self->ptr
            && (self->ptr->type == T_MUL || self->ptr->type == T_DIV)) {
        if (!node) {
            node = new_node(visit_operator);
        }
        if (!node->ptr) {
            node->ptr = self->ptr;
        }
        next(self);

        right = parse_factor(self);
        node->right = right;

        /* if (!node->right) goto error; */
        DEBUG_PRINTF("expr1: left: %s\n", node->right->ptr->value);
        if (!ast) {
            ast = node;
        } else {
            node->left = ast;
            ast = node;
        }
        node = NULL;
    }
    /* if (!node->right) { */
    /*     node = node->left; */
    /* } */
    if (!ast) {
        ast = node->left;
    }
    return ast;
error:
    self->flag = P_ERROR;
    return NULL;
}


NODE *parse_factor(parser_t *self) {
    assert(self != NULL);

    if (self->ptr->type != T_INT && self->ptr->type != T_LPAREN)
        goto error;

    NODE *ret = NULL;

    /* LPAREN expr2 RPAREN */
    if (self->ptr->type == T_LPAREN) {
        DEBUG_PRINTF("context -> LPAREN\n");
        next(self);

        ret = parse_expr2(self);
        if (!ret) goto error;
        assert(ret->ptr != NULL);
        DEBUG_PRINTF("context -> PAREN: factor: %s\n", ret->ptr->value);

        if (self->ptr->type != T_RPAREN) goto error;
        next(self);
        DEBUG_PRINTF("context -> RPAREN\n");

        return ret;
    }

    /* factor */
    TOKEN *factor = self->ptr;
    if (self->ptr->type != T_INT) goto error;

    ret = new_node(visit_integer);
    ret->ptr = factor;

    DEBUG_PRINTF("factor: %s\n", ret->ptr->value);
    next(self);

    return ret;
error:
    self->flag = P_ERROR;
    return NULL;
}


NODE *new_node(visit_t visit) {
    NODE *ret = malloc(sizeof *ret);
    if (!ret || !visit) return NULL;

    ret->left = NULL;
    ret->right = NULL;
    ret->ptr = NULL;

    ret->visit = visit;

    return ret;
}


int del_node(NODE *node) {
    if (!node) return 1;

    if (node->left) {
        del_node(node->left);
    }
    if (node->right) {
        del_node(node->right);
    }
    free_node(node);

    return 0;
}


int free_node(NODE *node) {
    if (!node) return 1;

    free(node);
    return 0;
}


NODE *visit_integer(NODE *self, ...) {
    if (!self) return NULL;
    assert(self->ptr->type == T_INT);
    NODE *ret = new_node(visit_integer);
    ret->ptr = self->ptr;
    return ret;
}


NODE *visit_operator(NODE *self, ...) {
    if (!self) goto error;

    /* TODO: Implement binary operators */
    NODE *left = NULL;
    NODE *right = NULL;

    assert(self->left != NULL && self->right != NULL);

    left = self->left->visit(self->left);
    DEBUG_PRINTF("visit: left: %s\n", left->ptr->value);
    right = self->right->visit(self->right);
    DEBUG_PRINTF("visit: right: %s\n", right->ptr->value);

    if (!left || !right) goto error;

    int len;
    char *tmp;
    factor_t lval = strtol(left->ptr->value, &tmp, 10);
    factor_t rval = strtol(right->ptr->value, &tmp, 10);
    factor_t result = 0;

    switch (self->ptr->type) {
    case T_ADD: {
        DEBUG_PRINTF("visit: T_ADD\n");
        result = lval + rval;
        break;
    }
    case T_SUB:
        DEBUG_PRINTF("visit: T_SUB\n");
        result = lval - rval;
        break;
    case T_MUL:
        DEBUG_PRINTF("visit: T_MUL\n");
        result = lval * rval;
        break;
    case T_DIV:
        DEBUG_PRINTF("visit: T_DIV\n");
        if (rval == 0) goto error;
        result = FLOOR_(FLOOR_(lval) / rval);
        break;
    default:
        goto error;
    }
    len = snprintf(NULL, 0, FMTSTR, result);
    DEBUG_PRINTF("visit: len: %d\n", len);

    char *value = malloc(BUFSIZ);
    if (!value) {
        // TODO
        goto error;
    }

    TOKEN *token = new_token();
    if (!token) {
        goto error;
    }
    snprintf(value, BUFSIZ, FMTSTR, result);
    value[len] = '\0';

    DEBUG_PRINTF("visit: result: %s\n", value);

    token->value = value;
    token->type = T_INT;

    NODE *ret = new_node(visit_integer);
    ret->ptr = token;

    return ret;

error:
    DEBUG_PRINTF("ERROR!\n");
    return NULL;
}


