#include "util.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


struct stringbuilder {
    char *data;
    int length;
    int capacity;
    int unit;
};


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


sb_t *new_sb(const char *src) {
    const int unit = BUFSIZ;
    int srclen = 0;
    int capacity = unit;
    if (src) {
        srclen = strlen(src);
        if (srclen > capacity) {
            int newcap = unit;
            do {
                newcap *= unit;
                if (newcap < 0) goto error;
            } while (newcap < srclen);
            capacity = newcap;
        }
    }
    sb_t *ret = malloc(sizeof *ret);
    if (!ret) goto error;

    ret->unit = unit;
    ret->capacity = capacity;
    ret->length = srclen;
    ret->data = malloc(ret->capacity);

    if (!ret->data) {
        free(ret);
        goto error;
    }

    if (src) {
        strncpy(ret->data, src, ret->length);
        ret->data[ret->length] = '\0';
    } else {
        ret->data[0] = '\0';
    }
    return ret;

error:
    return NULL;
}


void del_sb(sb_t *self) {
    if (!self) return;
    self->capacity = 0;
    self->length = 0;
    self->unit = 0;
    free(self->data);
    free(self);
}


int sb_len(sb_t *self) {
    if (!self) return -1;
    return self->length;
}


int sb_cap(sb_t *self) {
    if (!self) return -1;
    return self->capacity;
}


sb_t *sb_append(sb_t *self, const char *src) {
    if (!self || !self->data) goto error;

    int srclen = strlen(src);
    int newlen = sb_len(self) + srclen;

    if (sb_len(self) + srclen > sb_cap(self)) {
        int newcap = sb_cap(self);

        do {
            newcap *= self->unit;
            if (newcap < self->unit) goto error;
        } while (newcap < newlen);

        self->capacity = newcap;

        char *newptr = realloc(self->data, self->capacity);
        if (!newptr) return NULL;

        self->data = newptr;
    }
    self->length = newlen;

    strncat(self->data, src, srclen);
    self->data[self->length] = '\0';

    return self;

error:
    return NULL;
}


char *sb_to_str(sb_t *self) {
    if (!self) return NULL;
    return self->data;
}

