#ifndef XVZD_UTIL_H_
#define XVZD_UTIL_H_
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


#include "common.h"


struct stringbuilder;
typedef struct stringbuilder sb_t;


char *readline(void);

sb_t *new_sb(const char *src);
void del_sb(sb_t *self);
int sb_len(sb_t *self);
sb_t *sb_append(sb_t *self, const char *src);
char *sb_to_str(sb_t *self);


#endif  // XVZD_UTIL_H_
