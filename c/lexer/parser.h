#ifndef XVZD_PARSER_H_
#define XVZD_PARSER_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "lexer.h"

typedef struct node NODE;
typedef NODE *(*visit_t)(NODE *self, ...);

typedef enum parser_flag {
    P_OK,
    P_ERROR,  // General syntax error
    P_DIVIDE_BY_ZERO
} pflag_t;


#define DEF_ERROR(sym, msg) [sym] = msg
typedef const char* table_t[];

typedef struct parser {
    const TOKEN *head;
    TOKEN *ptr;
    pflag_t flag;
    table_t *error_table;
} parser_t;


struct node {
    NODE *left;
    NODE *right;
    TOKEN *ptr;
    visit_t visit;
};


parser_t *new_parser(const TOKEN *lexer);
int del_parser(parser_t *parser);
TOKEN *next(parser_t *self);

NODE *new_node(visit_t visit);
int del_node(NODE *node);
int free_node(NODE *node);

NODE *visit_integer(NODE *self, ...);
NODE *visit_operator(NODE *self, ...);

/* rules (production) */
NODE *parse_expr2(parser_t *self);
NODE *parse_expr1(parser_t *self);
NODE *parse_factor(parser_t *self);


#endif  // XVZD_PARSER_H_
