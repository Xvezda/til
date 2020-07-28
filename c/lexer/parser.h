#ifndef XVZD_PARSER_H_
#define XVZD_PARSER_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "lexer.h"

typedef struct node NODE;
typedef NODE *(*visit_func_t)(NODE *self, ...);
typedef char* table_t[];

typedef enum PARSER_FLAG {
    PARSER_OK,
    PARSER_ERROR,  // General syntax error
} pflag_t;

typedef struct parser {
    const   TOKEN *head;
    TOKEN   *tokptr;
    pflag_t flag;
    table_t *error_table;
} parser_t;

struct node {
    NODE    *left;
    NODE    *right;
    TOKEN   *tokptr;
    visit_func_t visit;
};


parser_t *new_parser(const TOKEN *lexer);
int del_parser(parser_t *parser);

NODE *new_node(visit_func_t handler);
int del_node(NODE *node);
int free_node(NODE *node);

NODE *visit_integer(NODE *self, ...);
NODE *visit_unary_operator(NODE *self, ...);
NODE *visit_binary_operator(NODE *self, ...);

/* rules (production) */
NODE *parse(parser_t *self);  // start symbol
NODE *parse_expr2(parser_t *self);
NODE *parse_expr1(parser_t *self);
NODE *parse_factor(parser_t *self);


#endif  // XVZD_PARSER_H_
