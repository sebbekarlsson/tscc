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
    dynamic_list* children = init_dynamic_list(sizeof(AST*));

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
    if (
        p->current_token->type == TOKEN_ID ||
        p->current_token->type == TOKEN_INTEGER_VALUE ||
        p->current_token->type == TOKEN_STRING_VALUE
    ) {
        return parser_parse_expr(p);
    }

    return (void*) 0;
}

AST* parser_parse_expr(parser* p) {
    AST* node = parser_parse_term(p);

    token* t = (void*) 0;

    while (p->current_token->type == TOKEN_PLUS) {
        t = p->current_token;

        if (p->current_token->type == TOKEN_PLUS) {
            parser_eat(p, TOKEN_PLUS);
        }

        printf("You are getting a nice lovely binop!\n");

        node = (AST*) init_ast_binop(t, node, parser_parse_term(p));
    }

    return node;
}

AST* parser_parse_term(parser* p) {
    AST* node = parser_parse_factor(p);

    // token* t = (void*) 0;

    return node;
}

AST* parser_parse_factor(parser* p) {
    token* t = p->current_token;

    if (t->type == TOKEN_INTEGER_VALUE) {
        parser_eat(p, TOKEN_INTEGER_VALUE);
        return (AST*) init_ast_integer(t);
    }

    return parser_parse_expr(p);
}
