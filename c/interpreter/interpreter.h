#ifndef XVZD_INTERPRETER_H_
#define XVZD_INTERPRETER_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "parser.h"


int interpreter(void);
NODE *evaluate(NODE *ast);


#endif  // XVZD_INTERPRETER_H_
