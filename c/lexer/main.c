#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef enum types {
    T_INTEGER,
    T_PLUS,
    T_MINUS,
    T_NOP,
    T_EOF
} token_t;

typedef struct token TOKEN;
struct token {
    token_t type;
    char *value;
    TOKEN *next;
};


int interpreter(void);
char *readline(void);
TOKEN *lexer(char *string);

TOKEN *new_token(void);
int del_token(TOKEN *head);

TOKEN *next_token(TOKEN *ptr);


int main(void) {
    int code = interpreter();

    return code;
}


char *readline() {
    char *ret = NULL;
    char buffer[BUFSIZ] = { 0 };
    size_t size = sizeof buffer;

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (!ret) {
            ret = malloc(sizeof buffer);
            ret[0] = '\0';
        } else {
            size += sizeof buffer;
            ret = realloc(ret, size);
        }
        if (!ret) return NULL;

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


int interpreter() {
    char *input = NULL;
    TOKEN *tokens = NULL;
    TOKEN *cur = NULL;

    while (1) {
        printf("> ");
        input = readline();
        if (!input) break;

        printf("input: %s\n", input);
        tokens = lexer(input);

        cur = tokens;
        /* Evaluate */
        int result = 0;
        int tmp = 0;
        char *ptr = NULL;
        token_t prev = T_NOP;
        while (cur) {
            printf("%s\n", cur->value);
            switch (cur->type) {
            case T_INTEGER:
                tmp = strtol(cur->value, &ptr, 10);
                switch (prev) {
                case T_PLUS:
                    result += tmp;
                    break;
                case T_MINUS:
                    result -= tmp;
                    break;
                case T_NOP:
                    result = tmp;
                    break;
                case T_EOF:
                case T_INTEGER:
                    goto error;
                }
                break;
            case T_PLUS:
            case T_MINUS:
                prev = cur->type;
                break;
            case T_NOP:
            case T_EOF:
                break;
            default:
                goto error;
            }
            cur = next_token(cur);
        }
        printf("result: %d\n", result);

        del_token(tokens);
        free(input);
    }
    return 0;

error:
    fprintf(stderr, "Syntax error occurred!");
    return 1;
}


TOKEN *lexer(char *string) {
    if (!string) {
        return NULL;
    }
    int i = 0;
    TOKEN *ret = new_token();
    TOKEN *cur = ret;
    if (!ret) return NULL;

    while (string[i]) {
        switch (string[i]) {
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0': {
            cur->type = T_INTEGER;

            int begin = i;
            do {
                ++i;
            } while (string[i] && isdigit(string[i]));
            int end = i;
            int len = end - begin;

            char *value = malloc(len + 1);
            if (!value) return NULL;

            strncpy(value, &string[begin], len);
            value[len] = '\0';

            cur->value = value;
            break;
        }
        case '+':
            cur->type = T_PLUS;
            cur->value = strdup("+");
            ++i;
            break;
        case '-':
            cur->type = T_MINUS;
            cur->value = strdup("-");
            ++i;
            break;
        default:
            ++i;
            continue;
        }
        cur->next = new_token();
        if (!cur->next) return NULL;

        cur = next_token(cur);
    }
    cur->type = T_EOF;
    cur->value = strdup("EOF");

    return ret;
}


TOKEN *new_token() {
    TOKEN *ret = malloc(sizeof(TOKEN));
    if (!ret) return NULL;

    ret->type = T_NOP;
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
