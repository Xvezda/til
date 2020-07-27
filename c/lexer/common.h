#ifndef XVZD_COMMON_H_
#define XVZD_COMMON_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#include "util.h"


#ifdef DEBUG
    #ifdef VERBOSE
        #define DEBUG_PRINTF(...)                      \
            do {                                       \
                printf("%s:%d: ", __FILE__, __LINE__); \
                printf(__VA_ARGS__);                   \
            } while (0)
    #else
        #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
    #endif
#else
    #define DEBUG_PRINTF(...) do {} while (0)
#endif


#define PS1 "> "
#define FMTSTR "%lld"
#define FACTOR long long int
#define FLOOR_(num) floorl(num)

typedef FACTOR factor_t;


#endif  // XVZD_COMMON_H_
