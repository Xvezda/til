#ifndef XVZD_LEXER_H_
#define XVZD_LEXER_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "common.h"


typedef enum TOKEN_TYPE {
    TOKEN_EOF,
    /* terminals */
    TOKEN_INT,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN
} token_t;


typedef struct token TOKEN;
struct token {
    token_t type;
    char    *value;
    TOKEN   *next;
};


TOKEN *lexer(const char *string);

TOKEN *new_token(void);
int del_token(TOKEN *head);
TOKEN *next_token(TOKEN *ptr);
void print_token(const TOKEN *head);


#endif  // XVZD_LEXER_H_
