#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#ifdef DEBUG
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...) do {} while (0)
#endif


#define PS1 "> "
#define FMTSTR "%lld"
#define FACTOR long long int
#define FLOOR_(num) floorl(num)


typedef enum types {
    T_EOF,
    /* terminals */
    T_INT,
    T_ADD,
    T_SUB,
    T_MUL,
    T_DIV,
    T_LPAREN,
    T_RPAREN
} token_t;


typedef struct token TOKEN;
struct token {
    token_t type;
    char *value;
    TOKEN *next;
};


typedef FACTOR factor_t;

typedef enum parser_flag {
    P_OK,
    P_ERROR,  // General syntax error
    P_DIVIDE_BY_ZERO
} pflag_t;

#define DEF_ERROR(sym, msg) [sym] = msg
typedef const char* table_t[];
table_t parser_error_table = {
    DEF_ERROR(P_ERROR, "syntax error occurred"),
    DEF_ERROR(P_DIVIDE_BY_ZERO, "divide by zero error"),
};

typedef struct parser {
    const TOKEN *head;
    TOKEN *ptr;
    factor_t result;
    pflag_t flag;
    table_t *error_table;
} parser_t;


int interpreter(void);
char *readline(void);
TOKEN *lexer(const char *string);

TOKEN *new_token(void);
int del_token(TOKEN *head);
TOKEN *next_token(TOKEN *ptr);
void print_token(const TOKEN *head);

parser_t *new_parser(const TOKEN *lexer);
int del_parser(parser_t *parser);
TOKEN *next(parser_t *self);

/* rules */
void parse_expr2(parser_t *self);
void parse_expr1(parser_t *self);
void parse_factor(parser_t *self);


int main(void) {
    int code = interpreter();
    return code;
}


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


int interpreter(void) {
    char *input = NULL;
    TOKEN *tokens = NULL;
    parser_t *parser = NULL;

    for (;;) {
        printf(PS1);
        input = readline();

        if (!input) break;

        DEBUG_PRINTF("input: %s\n", input);

        tokens = lexer(input);
        if (!tokens) goto error;
        print_token(tokens);

        /* for head(left-hand side) suffixed with digit,
         * smaller has higher precendence level.
         *
         * expr2: expr1 ( ( ADD | SUB ) expr1 )*
         * expr1: factor ( ( MUL | DIV ) factor )*
         * factor: INT | LPAREN expr2 RPAREN
         */
        parser = new_parser(tokens);
        if (!parser) goto error;
        parse_expr2(parser);  // start symbol

        if (parser->flag != P_OK) goto error;
        printf(FMTSTR "\n", parser->result);

        del_parser(parser);
        del_token(tokens);
        free(input);
    }
    return 0;

error:
    fprintf(stderr, "%s\n", (*parser->error_table)[parser->flag]);
    del_parser(parser);
    del_token(tokens);
    free(input);

    return 1;
}


parser_t *new_parser(const TOKEN *lexer) {
    parser_t *ret = malloc(sizeof *ret);
    if (!ret || !lexer) return NULL;

    ret->flag = P_OK;
    ret->head = lexer;
    ret->ptr = (TOKEN*)ret->head;
    ret->result = 0;

    ret->error_table = (table_t*)parser_error_table;

    return ret;
}


int del_parser(parser_t *parser) {
    parser->ptr = NULL;
    parser->result = 0;
    free(parser);

    return 0;
}


TOKEN *next(parser_t *self) {
    if (!self) return NULL;
    self->ptr = next_token(self->ptr);
    return self->ptr;
}


void parse_expr2(parser_t *self) {
    parse_expr1(self);
    factor_t left = self->result;
    factor_t right = 0;

    while (self->ptr && self->ptr->type != T_EOF) {
        token_t type = self->ptr->type;
        if (type != T_ADD && type != T_SUB) break;
        next(self);

        parse_expr1(self);
        right = self->result;

        if (type == T_ADD) {
            DEBUG_PRINTF("ADD\n");
            left = left + right;
        } else if (type == T_SUB) {
            DEBUG_PRINTF("SUB\n");
            left = left - right;
        }
    }
    self->result = left;
}


void parse_expr1(parser_t *self) {
    parse_factor(self);
    factor_t left = self->result;
    factor_t right = 0;


    while (self->ptr && self->ptr->type != T_EOF) {
        token_t type = self->ptr->type;
        if (type != T_MUL && type != T_DIV) break;
        next(self);

        parse_factor(self);
        right = self->result;

        if (type == T_MUL) {
            DEBUG_PRINTF("MUL\n");
            left = left * right;
        } else if (type == T_DIV) {
            if (!right) {
                self->flag = P_DIVIDE_BY_ZERO;
                return;
            }
            DEBUG_PRINTF("DIV\n");

            left = FLOOR_(FLOOR_(left) / right);
        }
    }
    self->result = left;
}


void parse_factor(parser_t *self) {
    if (!self) return;

    char *tmp;
    if (self->ptr->type != T_INT && self->ptr->type != T_LPAREN)
        goto error;

    if (self->ptr->type == T_LPAREN) {
        next(self);

        parse_expr2(self);

        if (self->ptr->type != T_RPAREN) goto error;
        next(self);

        return;
    }

    factor_t ret = strtol(self->ptr->value, &tmp, 10);
    next(self);

    DEBUG_PRINTF("factor: " FMTSTR "\n", ret);

    self->result = ret;

    return;
error:
    self->flag = P_ERROR;
}


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
