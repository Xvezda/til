#include "parser.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

#define FMTSTR "%lld"
#define FACTOR long long int
typedef FACTOR factor_t;

#define DEF_ERROR(sym, msg) [sym] = msg
const table_t parser_error_table = {
    DEF_ERROR(PARSER_OK, "unexpected error: exit while state ok"),
    DEF_ERROR(PARSER_ERROR, "syntax error occurred"),
};

static TOKEN *next(parser_t *self);


parser_t *new_parser(const TOKEN *lexer) {
    parser_t *ret = malloc(sizeof *ret);
    if (!ret || !lexer) return NULL;

    ret->flag = PARSER_OK;
    ret->head = lexer;
    ret->tokptr = (TOKEN*)ret->head;

    ret->error_table = (table_t*)parser_error_table;

    return ret;
}


int del_parser(parser_t *parser) {
    if (!parser) return 1;

    parser->tokptr = NULL;
    free(parser);

    return 0;
}


static TOKEN *next(parser_t *self) {
    if (!self) return NULL;
    self->tokptr = next_token(self->tokptr);
    return self->tokptr;
}


NODE *parse(parser_t *self) {
    if (!self) return NULL;

    return parse_expr2(self);  // start symbol
}


NODE *parse_expr2(parser_t *self) {
    assert(self != NULL);
    NODE *ast = NULL;
    NODE *node = new_node(visit_operator);

    NODE *left = parse_expr1(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr2: left: %s\n", node->left->tokptr->value);

    NODE *right = NULL;

    node->tokptr = self->tokptr;

    while (self->tokptr
            && (self->tokptr->type == TOKEN_ADD || self->tokptr->type == TOKEN_SUB)) {
        if (!node) {
            node = new_node(visit_operator);
        }
        if (!node->tokptr) {
            node->tokptr = self->tokptr;
        }
        next(self);

        right = parse_expr1(self);
        node->right = right;
        if (!node->right) goto error;
        DEBUG_PRINTF("expr2: right: %s\n", node->right->tokptr->value);
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
    self->flag = PARSER_ERROR;
    return NULL;
}


NODE *parse_expr1(parser_t *self) {
    assert(self != NULL);
    NODE *ast = NULL;
    NODE *node = new_node(visit_operator);

    NODE *left = parse_factor(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr1: left: %s\n", node->left->tokptr->value);

    NODE *right = NULL;

    node->tokptr = self->tokptr;

    while (self->tokptr
            && (self->tokptr->type == TOKEN_MUL || self->tokptr->type == TOKEN_DIV)) {
        if (!node) {
            node = new_node(visit_operator);
        }
        if (!node->tokptr) {
            node->tokptr = self->tokptr;
        }
        next(self);

        right = parse_factor(self);
        node->right = right;

        DEBUG_PRINTF("expr1: left: %s\n", node->right->tokptr->value);
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
    self->flag = PARSER_ERROR;
    return NULL;
}


NODE *parse_factor(parser_t *self) {
    assert(self != NULL);

    if (self->tokptr->type != TOKEN_INT && self->tokptr->type != TOKEN_LPAREN)
        goto error;

    NODE *ret = NULL;

    /* LPAREN expr2 RPAREN */
    if (self->tokptr->type == TOKEN_LPAREN) {
        DEBUG_PRINTF("context -> LPAREN\n");
        next(self);

        ret = parse_expr2(self);
        if (!ret) goto error;
        assert(ret->tokptr != NULL);
        DEBUG_PRINTF("context -> PAREN: factor: %s\n", ret->tokptr->value);

        if (self->tokptr->type != TOKEN_RPAREN) goto error;
        next(self);
        DEBUG_PRINTF("context -> RPAREN\n");

        return ret;
    }

    /* factor */
    TOKEN *factor = self->tokptr;
    if (self->tokptr->type != TOKEN_INT) goto error;

    ret = new_node(visit_integer);
    ret->tokptr = factor;

    DEBUG_PRINTF("factor: %s\n", ret->tokptr->value);
    next(self);

    return ret;
error:
    self->flag = PARSER_ERROR;
    return NULL;
}


NODE *new_node(visit_func_t handler) {
    NODE *ret = malloc(sizeof *ret);
    if (!ret || !handler) return NULL;

    ret->left = NULL;
    ret->right = NULL;
    ret->tokptr = NULL;

    ret->visit = handler;

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
    assert(self->tokptr->type == TOKEN_INT);
    NODE *ret = new_node(visit_integer);
    ret->tokptr = self->tokptr;
    return ret;
}


NODE *visit_operator(NODE *self, ...) {
    if (!self) goto error;

    /* TODO: Implement binary operators */
    NODE *left = NULL;
    NODE *right = NULL;

    assert(self->left != NULL && self->right != NULL);

    left = self->left->visit(self->left);
    DEBUG_PRINTF("visit: left: %s\n", left->tokptr->value);
    right = self->right->visit(self->right);
    DEBUG_PRINTF("visit: right: %s\n", right->tokptr->value);

    if (!left || !right) goto error;

    int len;
    char *tmp;
    factor_t lval = strtol(left->tokptr->value, &tmp, 10);
    factor_t rval = strtol(right->tokptr->value, &tmp, 10);
    factor_t result = 0;

    switch (self->tokptr->type) {
    case TOKEN_ADD: {
        DEBUG_PRINTF("visit: TOKEN_ADD\n");
        result = lval + rval;
        break;
    }
    case TOKEN_SUB:
        DEBUG_PRINTF("visit: TOKEN_SUB\n");
        result = lval - rval;
        break;
    case TOKEN_MUL:
        DEBUG_PRINTF("visit: TOKEN_MUL\n");
        result = lval * rval;
        break;
    case TOKEN_DIV:
        DEBUG_PRINTF("visit: TOKEN_DIV\n");
        if (rval == 0) goto error;
        result = floor(floor(lval) / rval);
        break;
    default:
        goto error;
    }
    len = snprintf(NULL, 0, FMTSTR, result);
    DEBUG_PRINTF("visit: len: %d\n", len);

    char *value = malloc(BUFSIZ);
    if (!value) {
        // FIXME
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
    token->type = TOKEN_INT;

    NODE *ret = new_node(visit_integer);
    ret->tokptr = token;

    return ret;

error:
    DEBUG_PRINTF("ERROR!\n");
    return NULL;
}


