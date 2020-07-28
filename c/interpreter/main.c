#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "translator.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


int main(void) {
    int code = interpreter();
    return code;
}

