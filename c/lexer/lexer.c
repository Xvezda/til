#include "lexer.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


TOKEN *lexer(const char *string) {
    if (!string) goto error;

    int i = 0;
    int paren_cnt = 0;
    TOKEN *ret = new_token();
    TOKEN *cur = ret;
    if (!ret) goto error;

    while (string[i]) {
        switch (string[i]) {
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0': {
            cur->type = T_INT;

            int begin = i;
            do {
                ++i;
            } while (string[i] && isdigit(string[i]));
            int end = i;
            int len = end - begin;

            char *value = malloc(len + 1);
            if (!value) goto error;

            strncpy(value, &string[begin], len);
            value[len] = '\0';

            cur->value = value;
            break;
        }
        case '+':
            cur->type = T_ADD;
            cur->value = strdup("+");
            ++i;
            break;
        case '-':
            cur->type = T_SUB;
            cur->value = strdup("-");
            ++i;
            break;
        case '/':
            cur->type = T_DIV;
            cur->value = strdup("/");
            ++i;
            break;
        case '*':
            cur->type = T_MUL;
            cur->value = strdup("*");
            ++i;
            break;
        case '(':
            cur->type = T_LPAREN;
            cur->value = strdup("(");
            ++paren_cnt;
            ++i;
            break;
        case ')':
            cur->type = T_RPAREN;
            cur->value = strdup(")");
            --paren_cnt;
            if (paren_cnt < 0) goto error;
            ++i;
            break;
        case ' ':
        default:
            ++i;
            continue;
        }
        cur->next = new_token();
        if (!cur->next) goto error;

        cur = next_token(cur);
    }
    if (paren_cnt) goto error;

    cur->type = T_EOF;
    cur->value = strdup("EOF");

    return ret;

error:
    return NULL;
}


TOKEN *new_token(void) {
    TOKEN *ret = malloc(sizeof(TOKEN));
    if (!ret) return NULL;

    ret->type = T_EOF;
    ret->value = NULL;
    ret->next = NULL;

    return ret;
}


int del_token(TOKEN *head) {
    if (!head) return 0;

    TOKEN *cur = head;
    TOKEN *tmp = NULL;

    while ((tmp=cur) != NULL) {
        free(tmp->value);
        free(tmp);
        cur = next_token(cur);
    }
    return 0;
}


inline TOKEN *next_token(TOKEN *ptr) {
    if (!ptr) return NULL;
    return ptr->next;
}


void print_token(const TOKEN *head) {
    if (!head) return;
    TOKEN *ptr = (TOKEN*)head;
    while (ptr->next) {
        DEBUG_PRINTF("value: %s\n", ptr->value);
        ptr = next_token(ptr);
    }
}


