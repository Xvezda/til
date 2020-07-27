#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#ifdef DEBUG
    #ifdef VERBOSE
        #define DEBUG_PRINTF(...) \
            do { \
                printf("%s:%d: ", __FILE__, __LINE__); \
                printf(__VA_ARGS__); \
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
typedef struct node NODE;
typedef NODE *(*visit_t)(NODE *self, ...);

typedef enum parser_flag {
    P_OK,
    P_ERROR,  // General syntax error
    P_DIVIDE_BY_ZERO
} pflag_t;


#define DEF_ERROR(sym, msg) [sym] = msg
typedef const char* table_t[];
table_t parser_error_table = {
    DEF_ERROR(P_OK, "unexpected error: exit while state ok"),
    DEF_ERROR(P_ERROR, "syntax error occurred"),
    DEF_ERROR(P_DIVIDE_BY_ZERO, "divide by zero error"),
};


typedef struct parser {
    const TOKEN *head;
    TOKEN *ptr;
    pflag_t flag;
    table_t *error_table;
} parser_t;


struct node {
    NODE *left;
    NODE *right;
    TOKEN *ptr;
    visit_t visit;
};


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

NODE *new_node(visit_t visit);
int del_node(NODE *node);
int free_node(NODE *node);

NODE *visit_integer(NODE *self, ...);
NODE *visit_operator(NODE *self, ...);

/* rules */
NODE *parse_expr2(parser_t *self);
NODE *parse_expr1(parser_t *self);
NODE *parse_factor(parser_t *self);

NODE *evaluate(NODE *ast);


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
    NODE *ast = NULL;
    NODE *result = NULL;

    for (;;) {
        printf(PS1);
        input = readline();

        if (!input) break;

        DEBUG_PRINTF("input: %s\n", input);

        tokens = lexer(input);
        if (!tokens) {
            fprintf(stderr, "lexer failed while tokenizing input\n");
            goto lexer_error;
        }
        print_token(tokens);

        /* for head(left-hand side) suffixed with digit,
         * smaller has higher precendence level.
         *
         * expr2: expr1 ( ( ADD | SUB ) expr1 )*
         * expr1: factor ( ( MUL | DIV ) factor )*
         * factor: INT | LPAREN expr2 RPAREN
         */
        parser = new_parser(tokens);
        if (!parser) goto parser_error;
        ast = parse_expr2(parser);  // start symbol

        if (!ast) goto parser_error;
        if (parser->flag != P_OK) goto parser_error;
        result = evaluate(ast);

        if (!result) goto eval_error;
        DEBUG_PRINTF("result: %s\n", result->ptr->value);
        printf("%s\n", result->ptr->value);

        del_node(result);
        del_node(ast);
        del_parser(parser);
        del_token(tokens);
        free(input);
    }
    return 0;

parser_error:
    if (parser) {
        fprintf(stderr, "%s\n", (*parser->error_table)[parser->flag]);
    }
    del_parser(parser);

lexer_error:
    del_token(tokens);

eval_error:
    del_node(ast);
    free(input);

    return 1;
}


parser_t *new_parser(const TOKEN *lexer) {
    parser_t *ret = malloc(sizeof *ret);
    if (!ret || !lexer) return NULL;

    ret->flag = P_OK;
    ret->head = lexer;
    ret->ptr = (TOKEN*)ret->head;

    ret->error_table = (table_t*)parser_error_table;

    return ret;
}


int del_parser(parser_t *parser) {
    if (!parser) return 1;

    parser->ptr = NULL;
    free(parser);

    return 0;
}


TOKEN *next(parser_t *self) {
    if (!self) return NULL;
    self->ptr = next_token(self->ptr);
    return self->ptr;
}


NODE *parse_expr2(parser_t *self) {
    assert(self != NULL);
    NODE *ast = NULL;
    NODE *node = new_node(visit_operator);

    NODE *left = parse_expr1(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr2: left: %s\n", node->left->ptr->value);

    NODE *right = NULL;

    node->ptr = self->ptr;

    while (self->ptr
            && (self->ptr->type == T_ADD || self->ptr->type == T_SUB)) {
        if (!node) {
            node = new_node(visit_operator);
        }
        if (!node->ptr) {
            node->ptr = self->ptr;
        }
        next(self);

        right = parse_expr1(self);
        node->right = right;
        if (!node->right) goto error;
        DEBUG_PRINTF("expr2: right: %s\n", node->right->ptr->value);
        if (!ast) {
            ast = node;
        } else {
            node->left = ast;
            ast = node;
        }
        node = NULL;
    }
    if (!ast) {
        ast = node->left;
    }
    return ast;
error:
    self->flag = P_ERROR;
    return NULL;
}


NODE *parse_expr1(parser_t *self) {
    assert(self != NULL);
    NODE *ast = NULL;
    NODE *node = new_node(visit_operator);

    NODE *left = parse_factor(self);
    node->left = left;
    if (!node->left) goto error;
    DEBUG_PRINTF("expr1: left: %s\n", node->left->ptr->value);

    NODE *right = NULL;

    node->ptr = self->ptr;

    while (self->ptr
            && (self->ptr->type == T_MUL || self->ptr->type == T_DIV)) {
        if (!node) {
            node = new_node(visit_operator);
        }
        if (!node->ptr) {
            node->ptr = self->ptr;
        }
        next(self);

        right = parse_factor(self);
        node->right = right;

        /* if (!node->right) goto error; */
        DEBUG_PRINTF("expr1: left: %s\n", node->right->ptr->value);
        if (!ast) {
            ast = node;
        } else {
            node->left = ast;
            ast = node;
        }
        node = NULL;
    }
    /* if (!node->right) { */
    /*     node = node->left; */
    /* } */
    if (!ast) {
        ast = node->left;
    }
    return ast;
error:
    self->flag = P_ERROR;
    return NULL;
}


NODE *parse_factor(parser_t *self) {
    assert(self != NULL);

    if (self->ptr->type != T_INT && self->ptr->type != T_LPAREN)
        goto error;

    NODE *ret = NULL;

    /* LPAREN expr2 RPAREN */
    if (self->ptr->type == T_LPAREN) {
        DEBUG_PRINTF("context -> LPAREN\n");
        next(self);

        ret = parse_expr2(self);
        if (!ret) goto error;
        assert(ret->ptr != NULL);
        DEBUG_PRINTF("context -> PAREN: factor: %s\n", ret->ptr->value);

        if (self->ptr->type != T_RPAREN) goto error;
        next(self);
        DEBUG_PRINTF("context -> RPAREN\n");

        return ret;
    }

    /* factor */
    TOKEN *factor = self->ptr;
    if (self->ptr->type != T_INT) goto error;

    ret = new_node(visit_integer);
    ret->ptr = factor;

    DEBUG_PRINTF("factor: %s\n", ret->ptr->value);
    next(self);

    return ret;
error:
    self->flag = P_ERROR;
    return NULL;
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


NODE *new_node(visit_t visit) {
    NODE *ret = malloc(sizeof *ret);
    if (!ret || !visit) return NULL;

    ret->left = NULL;
    ret->right = NULL;
    ret->ptr = NULL;

    ret->visit = visit;

    return ret;
}


int del_node(NODE *node) {
    if (!node) return 1;

    if (node->left) {
        del_node(node->left);
    }
    if (node->right) {
        del_node(node->right);
    }
    free_node(node);

    return 0;
}


int free_node(NODE *node) {
    if (!node) return 1;

    free(node);
    return 0;
}


NODE *visit_integer(NODE *self, ...) {
    if (!self) return NULL;
    assert(self->ptr->type == T_INT);
    NODE *ret = new_node(visit_integer);
    ret->ptr = self->ptr;
    return ret;
}


NODE *visit_operator(NODE *self, ...) {
    if (!self) goto error;

    /* TODO: Implement binary operators */
    NODE *left = NULL;
    NODE *right = NULL;

    assert(self->left != NULL && self->right != NULL);

    left = self->left->visit(self->left);
    DEBUG_PRINTF("visit: left: %s\n", left->ptr->value);
    right = self->right->visit(self->right);
    DEBUG_PRINTF("visit: right: %s\n", right->ptr->value);

    if (!left || !right) goto error;

    int len;
    char *tmp;
    factor_t lval = strtol(left->ptr->value, &tmp, 10);
    factor_t rval = strtol(right->ptr->value, &tmp, 10);
    factor_t result = 0;

    switch (self->ptr->type) {
    case T_ADD: {
        DEBUG_PRINTF("visit: T_ADD\n");
        result = lval + rval;
        break;
    }
    case T_SUB:
        DEBUG_PRINTF("visit: T_SUB\n");
        result = lval - rval;
        break;
    case T_MUL:
        DEBUG_PRINTF("visit: T_MUL\n");
        result = lval * rval;
        break;
    case T_DIV:
        DEBUG_PRINTF("visit: T_DIV\n");
        if (rval == 0) goto error;
        result = FLOOR_(FLOOR_(lval) / rval);
        break;
    default:
        goto error;
    }
    len = snprintf(NULL, 0, FMTSTR, result);
    DEBUG_PRINTF("visit: len: %d\n", len);

    char *value = malloc(BUFSIZ);
    if (!value) {
        // TODO
        goto error;
    }

    TOKEN *token = new_token();
    if (!token) {
        goto error;
    }
    snprintf(value, BUFSIZ, FMTSTR, result);
    value[len] = '\0';

    DEBUG_PRINTF("visit: result: %s\n", value);

    token->value = value;
    token->type = T_INT;

    NODE *ret = new_node(visit_integer);
    ret->ptr = token;

    return ret;

error:
    DEBUG_PRINTF("ERROR!\n");
    return NULL;
}


NODE *evaluate(NODE *ast) {
    /* TODO: DFS */
    if (!ast || !ast->ptr) return NULL;

    if (ast->left) {
        ast->left = evaluate(ast->left);
    }
    if (ast->right) {
        ast->right = evaluate(ast->right);
    }
    assert(ast != NULL && ast->ptr != NULL);

    DEBUG_PRINTF("ast(%p): %s\n", (void*)ast, ast->ptr->value);

    return ast->visit(ast);
}
