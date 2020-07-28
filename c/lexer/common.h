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


#ifndef DEBUG_PRINTF

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
#endif  // #ifdef DEBUG

#endif  // #ifndef DEBUG_PRINTF


#endif  // XVZD_COMMON_H_
