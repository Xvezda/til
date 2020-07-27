#include "interpreter.h"
/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */


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
        ast = parse(parser);  // start symbol

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

