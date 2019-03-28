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
        printf("Unexpected token_type in parser: `%d` (%s)\n", p->current_token->type, p->current_token->value);
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

    if (p->current_token->type == TOKEN_FUNCTION_TYPE)
        return (AST*) parser_parse_function_definition(p);

    if (p->current_token->type == TOKEN_LET) {
        parser_eat(p, TOKEN_LET);
        return (AST*) parser_parse_variable_definition(p);
    }

    if (p->current_token->type == TOKEN_IF) {
        return (AST*) parser_parse_if(p);
    }

    return (void*) 0;
}

/**
 * Parses an expression
 *
 * @param parser* p
 *
 * @return AST*
 */
AST* parser_parse_expr(parser* p) {
    AST* node = parser_parse_term(p);

    token* t = (void*) 0;

    while (
        p->current_token->type == TOKEN_PLUS ||
        p->current_token->type == TOKEN_EQUALS_EQUALS ||
        p->current_token->type == TOKEN_NOT_EQUALS
    ) {
        t = p->current_token;

        if (p->current_token->type == TOKEN_PLUS) {
            parser_eat(p, TOKEN_PLUS);
        }

        else if (p->current_token->type == TOKEN_EQUALS_EQUALS) {
            parser_eat(p, TOKEN_EQUALS_EQUALS);
        }

        else if (p->current_token->type == TOKEN_NOT_EQUALS) {
            parser_eat(p, TOKEN_NOT_EQUALS);
        }

        node = (AST*) init_ast_binop(t, node, parser_parse_term(p));
    }

    return node;
}

/**
 * Parses division, multiplication
 *
 * @param parser* p
 *
 * @return AST*
 */
AST* parser_parse_term(parser* p) {
    AST* node = parser_parse_factor(p);

    token* t = (void*) 0;

    while (p->current_token->type == TOKEN_DIVIDE || p->current_token->type == TOKEN_MULTIPLY) {
        t = p->current_token;

        if (p->current_token->type == TOKEN_DIVIDE) {
            parser_eat(p, TOKEN_DIVIDE);
        } else if (p->current_token->type == TOKEN_MULTIPLY) {
            parser_eat(p, TOKEN_MULTIPLY);
        }

        node = (AST*) init_ast_binop(t, node, parser_parse_factor(p));
    }

    return node;
}

/**
 * Parses factorial, integers, numbers, functions, objects etc. (values?)
 *
 * @param parser* p
 *
 * @return AST*
 */
AST* parser_parse_factor(parser* p) {
    token* t = p->current_token;

    if (t->type == TOKEN_INTEGER_VALUE) {
        parser_eat(p, TOKEN_INTEGER_VALUE);
        return (AST*) init_ast_integer(t);
    }

    if (t->type == TOKEN_LPAREN) {
        parser_eat(p, TOKEN_LPAREN);
        AST* expr = parser_parse_expr(p);
        parser_eat(p, TOKEN_RPAREN);

        return expr;
    }

    if (t->type == TOKEN_FUNCTION_TYPE) {
        return (AST*) parser_parse_function_definition(p);
    }

    if (t->type == TOKEN_ID) {
        return parser_parse_id(p);
    }

    if (t->type == TOKEN_STRING_VALUE) {
        parser_eat(p, TOKEN_STRING_VALUE);
        return (AST*) init_ast_string(t);
    } 

    return parser_parse_expr(p);
}

AST* parser_parse_id(parser* p) {
    token* t = p->current_token;
    parser_eat(p, TOKEN_ID);

    if (p->current_token->type == TOKEN_LPAREN)
        return (AST*) parser_parse_function_call(p, t);

    return (void*) 0;
}

AST_function_call* parser_parse_function_call(parser* p, token* t) {
    char* name = t->value;
    dynamic_list* args = init_dynamic_list(sizeof(struct AST_STRUCT));
    parser_eat(p, TOKEN_LPAREN);

    AST* expr = parser_parse_expr(p);
    dynamic_list_append(args, expr);
    
    while (p->current_token->type == TOKEN_COMMA) {
        parser_eat(p, TOKEN_COMMA);
        expr = parser_parse_expr(p); 
        dynamic_list_append(args, expr);
    }

    parser_eat(p, TOKEN_RPAREN);

    return init_ast_function_call(t, name, args);
}

/**
 * Parses a function definition
 *
 * @param parser* p
 *
 * @return AST_function_definition*
 */
AST_function_definition* parser_parse_function_definition(parser* p) {
    parser_eat(p, TOKEN_FUNCTION_TYPE);
    dynamic_list* args = init_dynamic_list(sizeof(struct AST_VARIABLE_DEFINITION_STRUCT));
    char* name = p->current_token->value;
    parser_eat(p, TOKEN_ID);
    parser_eat(p, TOKEN_LPAREN);

    AST_variable_definition* definition = parser_parse_variable_definition(p);
    dynamic_list_append(args, definition);

    while (p->current_token->type == TOKEN_COMMA) {
        parser_eat(p, TOKEN_COMMA);
        definition = parser_parse_variable_definition(p); 
        dynamic_list_append(args, definition);
    }

    parser_eat(p, TOKEN_RPAREN);
    parser_eat(p, TOKEN_COLON);

    AST_datatype* datatype = parser_parse_data_type(p);

    parser_eat(p, TOKEN_LBRACE);
    AST_compound* compound = parser_parse_compound(p);
    parser_eat(p, TOKEN_RBRACE);

    return init_ast_function_definition(p->current_token, name, args, compound, datatype);
}

/**
 * Parses a variable definition
 *
 * @param parser* p
 *
 * @return AST_variable_definition*
 */
AST_variable_definition* parser_parse_variable_definition(parser* p) {
    char* name = p->current_token->value;
    AST* value = (void*) 0;
    parser_eat(p, TOKEN_ID);
    parser_eat(p, TOKEN_COLON);

    AST_datatype* datatype = parser_parse_data_type(p);

    if (p->current_token->type == TOKEN_EQUALS) {
        parser_eat(p, TOKEN_EQUALS);
        value = parser_parse_expr(p);
    }

    return init_ast_variable_definition(p->current_token, name, value, datatype);
}

/**
 * Parses a datatype
 *
 * @param parser* p
 *
 * @return AST_datatype*
 */
AST_datatype* parser_parse_data_type(parser* p) {
    token* t = p->current_token;

    int is_list = 0;

    switch (p->current_token->type) {
        case TOKEN_INTEGER_TYPE:
            parser_eat(p, TOKEN_INTEGER_TYPE);
        break;
        case TOKEN_STRING_TYPE:
            parser_eat(p, TOKEN_STRING_TYPE);
        break;
        case TOKEN_VOID_TYPE:
            parser_eat(p, TOKEN_VOID_TYPE);
        break;
        case TOKEN_NULL_TYPE:
            parser_eat(p, TOKEN_NULL_TYPE);
        default:
            printf("Unexpected data_type %s\n", p->current_token->value);
            exit(1);
        break;
    }

    if (p->current_token->type == TOKEN_LBRACKET) {
        is_list = 1;

        parser_eat(p, TOKEN_LBRACKET);
        parser_eat(p, TOKEN_RBRACKET);
    }

    return init_ast_datatype(t, is_list);
}

AST_if* parser_parse_if(parser* p) {
    AST* expr = (void*) 0;
    AST_if* otherwise = (void*) 0;

    if (p->current_token->type == TOKEN_IF) {
        parser_eat(p, TOKEN_IF);
        parser_eat(p, TOKEN_LPAREN);
        expr = parser_parse_expr(p);
        parser_eat(p, TOKEN_RPAREN);
    }

    parser_eat(p, TOKEN_LBRACE);
    AST_compound* compound = parser_parse_compound(p);
    parser_eat(p, TOKEN_RBRACE);

    if (p->current_token->type == TOKEN_ELSE) {
        parser_eat(p, TOKEN_ELSE);
        otherwise = parser_parse_if(p);
    }

    return init_ast_if(p->current_token, expr, compound, otherwise);
}
