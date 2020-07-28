#ifndef API_H_
#define API_H_


typedef struct opaque opaque;
typedef struct non_opaque {
    char *data;
} non_opaque;

opaque *new_opaque(const char *src);
void print_opaque(opaque *self);
void del_opaque(opaque *self);
non_opaque *new_non_opaque(const char *src);
void print_non_opaque(non_opaque *self);
void del_non_opaque(non_opaque *self);


#endif  // API_H_

