#ifndef XVZD_TRANSLATOR_H_
#define XVZD_TRANSLATOR_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "parser.h"
#include "util.h"


typedef struct translator trans_t;

trans_t *new_translator(void);
void del_translator(trans_t *self);
void translate(trans_t *self, const NODE *root);
void translator_print(trans_t *self);


#endif  // XVZD_TRANSLATOR_H_
