#ifndef XVZD_LEXER_H_
#define XVZD_LEXER_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "common.h"


typedef enum types {
    T_EOF,
    /* terminals */
    T_INT,
    T_ADD,
    T_SUB,
    T_MUL,
    T_DIV,
    T_LPAREN,
    T_RPAREN
} token_t;


typedef struct token TOKEN;
struct token {
    token_t type;
    char *value;
    TOKEN *next;
};


TOKEN *lexer(const char *string);

TOKEN *new_token(void);
int del_token(TOKEN *head);
TOKEN *next_token(TOKEN *ptr);
void print_token(const TOKEN *head);


#endif  // XVZD_LEXER_H_
