#include "parser.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


/* for head(left-hand side) suffixed with digit,
 * smaller has higher precendence level.
 *
 * expr2: expr1 ( ( ADD | SUB ) expr1 )*
 * expr1: factor ( ( MUL | DIV ) factor )*
 * factor: ( ADD | SUB ) factor | LPAREN expr2 RPAREN | INT
 */

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
    NODE *node = new_node(visit_binary_operator);

    NODE *left = parse_expr1(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr2: left: %s\n", node->left->tokptr->value);

    NODE *right = NULL;

    node->tokptr = self->tokptr;

    while (self->tokptr
            && (self->tokptr->type == TOKEN_ADD || self->tokptr->type == TOKEN_SUB)) {
        if (!node) {
            node = new_node(visit_binary_operator);
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
    NODE *node = new_node(visit_binary_operator);

    NODE *left = parse_factor(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr1: left: %s\n", node->left->tokptr->value);

    NODE *right = NULL;

    node->tokptr = self->tokptr;

    while (self->tokptr
            && (self->tokptr->type == TOKEN_MUL || self->tokptr->type == TOKEN_DIV)) {
        if (!node) {
            node = new_node(visit_binary_operator);
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

    switch (self->tokptr->type) {
    /* unary operator */
    case TOKEN_SUB:
    case TOKEN_ADD:
    /* parentheses operator */
    case TOKEN_LPAREN:
    /* INT */
    case TOKEN_INT:
        break;
    default:
        goto error;
    }

    NODE *ret = NULL;
    TOKEN *factor = NULL;

    /* (ADD|SUB) factor */
    if (self->tokptr->type == TOKEN_ADD || self->tokptr->type == TOKEN_SUB) {
        NODE *ast = NULL;

        ret = new_node(visit_unary_operator);
        factor = self->tokptr;
        ret->tokptr = factor;

        DEBUG_PRINTF("unary: factor: %s\n", ret->tokptr->value);
        next(self);

        ast = parse_factor(self);
        if (!ast) goto error;

        ret->right = ast;

        return ret;
    }

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
    factor = self->tokptr;
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
    if (!ret) goto node_error;

    TOKEN *token = new_token();
    if (!token) goto token_error;

    token->value = strdup(self->tokptr->value);
    token->type = TOKEN_INT;

    ret->tokptr = token;
    return ret;

token_error:
    del_node(ret);

node_error:
    return NULL;
}


NODE *visit_unary_operator(NODE *self, ...) {
    if (!self) return NULL;
    assert(self->tokptr != NULL && self->tokptr->value != NULL);
    DEBUG_PRINTF("visit: unary: %s\n", self->tokptr->value);
    DEBUG_PRINTF("visit: left->%p, right-> %p\n",
            (void*)self->left, (void*)self->right);
    assert(self->tokptr->type == TOKEN_ADD
            || self->tokptr->type == TOKEN_SUB);
    NODE *ret = new_node(visit_integer);
    NODE *right = NULL;

    assert(self->right != NULL);
    right = self->right->visit(self->right);

    if (!ret || !right) goto error;

    char *tmp;
    factor_t rval = strtol(right->tokptr->value, &tmp, 10);
    switch (self->tokptr->type) {
    case TOKEN_SUB:
        rval *= -1;
        break;
    case TOKEN_ADD:
        break;
    default:
        goto error;
    }
    int len = snprintf(NULL, 0, FMTSTR, rval);
    char *value = malloc(BUFSIZ);
    if (!value) {
        goto error;
    }
    snprintf(value, BUFSIZ, FMTSTR, rval);
    value[len] = '\0';

    TOKEN *token = new_token();
    token->value = value;
    token->type = TOKEN_INT;
    DEBUG_PRINTF("visit: unary: return -> %s\n", value);

    ret->tokptr = token;
    return ret;

error:
    del_node(ret);
    return NULL;
}


NODE *visit_binary_operator(NODE *self, ...) {
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


