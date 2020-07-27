#include "lexer.h"
#include "parser.h"
#include "translator.h"


int main(void) {
    trans_t *translator = new_translator();
    char *input = readline();
    if (!input) goto input_error;

    TOKEN *tokens = lexer(input);
    if (!tokens) goto lexer_error;
    parser_t *parser = new_parser(tokens);

    NODE *ast = parse(parser);
    if (!ast) goto parse_error;

    translate(translator, ast);
    translator_print(translator);

    del_translator(translator);

    return 0;

parse_error:
lexer_error:
    free(input);

input_error:
    return 1;
}
