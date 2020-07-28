#include "interpreter.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

#define PS1 "> "


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

        parser = new_parser(tokens);
        if (!parser) goto parser_error;
        ast = parse(parser);  // start symbol

        if (!ast) goto parser_error;
        if (parser->flag != PARSER_OK) goto parser_error;
        result = evaluate(ast);

        if (!result) goto eval_error;
        DEBUG_PRINTF("result: %s\n", result->tokptr->value);
        printf("%s\n", result->tokptr->value);

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
    del_token(tokens);

eval_error:
    del_node(ast);

lexer_error:
    free(input);

    return 1;
}


NODE *evaluate(NODE *ast) {
    /* TODO: DFS */
    if (!ast || !ast->tokptr) return NULL;

    if (ast->left) {
        ast->left = evaluate(ast->left);
    }
    if (ast->right) {
        ast->right = evaluate(ast->right);
    }
    assert(ast != NULL && ast->tokptr != NULL);

    DEBUG_PRINTF("ast(%p): %s\n", (void*)ast, ast->tokptr->value);

    return ast->visit(ast);
}

