#include "util.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


char *readline(void) {
    char *ret = NULL;
    char buffer[BUFSIZ] = { 0 };
    size_t size = 0;

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (!ret) {
            ret = malloc(sizeof buffer);
            size = sizeof buffer;
        } else {
            size += sizeof buffer;
            ret = realloc(ret, size);
        }
        if (!ret) return NULL;
        else if (size == sizeof buffer) {
            ret[0] = '\0';
        }

        char *pos;
        if ((pos=strchr(buffer, '\r')) != NULL
                || (pos=strchr(buffer, '\n')) != NULL) {
            strncat(ret, buffer, (size_t)(pos - &buffer[0]));
            break;
        } else {
            strncat(ret, buffer, strlen(buffer));
        }
    }
    if (ret && !ret[0]) {
        free(ret);
        return NULL;
    }
    return ret;
}


