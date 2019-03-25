#include "include/parse.h"
#include "include/dynamic_list.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Initializes a new parser
 *
 * @param lexer* l
 *
 * @return parser*
 */
parser* init_parser(lexer* l) {
    parser* p = calloc(1, sizeof(struct PARSER_STRUCT));
    p->l = l;
    p->current_token = lexer_get_next_token(p->l);

    return p;
}

/**
 * Checks if the current token is expected and then fetches
 * the next token.
 *
 * @param parser* p
 * @param int token_type
 */
void parser_eat(parser* p, int token_type) {
    if (p->current_token->type != token_type) {
        printf("Unexpected token_type in parser: `%d`\n", token_type);
        exit(1);
    } else {
        p->current_token = lexer_get_next_token(p->l);
    }
}

/**
 * Main entry point for the parser
 *
 * @param parser* p
 *
 * @return AST_compound*
 */
AST_compound* parser_parse(parser* p) {
    return parser_parse_compound(p);
}

/**
 * Parses a compound
 *
 * @param parser* p
 *
 * @return AST_compound*
 */
AST_compound* parser_parse_compound(parser* p) {
    dynamic_list* children = init_dynamic_list(sizeof(struct AST_STRUCT));

    AST* statement = parser_parse_statement(p);
    dynamic_list_append(children, statement);

    while (p->current_token->type == TOKEN_SEMI) {
        parser_eat(p, TOKEN_SEMI);

        statement = parser_parse_statement(p);
        dynamic_list_append(children, statement);
    }

    return init_ast_compound(p->current_token, children);
}

/**
 * Parses a statement
 *
 * @param parser* p
 *
 * @return AST*
 */
AST* parser_parse_statement(parser* p) {
    return (void*) 0;
}
