#include "include/parse.h"
#include "include/dynamic_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
AST_compound* parser_parse(parser* p, scope* s) {
    return parser_parse_compound(p, s);
}

/**
 * Parses a compound
 *
 * @param parser* p
 *
 * @return AST_compound*
 */
AST_compound* parser_parse_compound(parser* p, scope* s) {
    dynamic_list* children = init_dynamic_list(sizeof(AST*));

    AST* statement = parser_parse_statement(p, s);
    dynamic_list_append(children, statement);

    while (p->current_token->type == TOKEN_SEMI) {
        parser_eat(p, TOKEN_SEMI);

        statement = parser_parse_statement(p, s);
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
AST* parser_parse_statement(parser* p, scope* s) {
    if (
        p->current_token->type == TOKEN_ID ||
        p->current_token->type == TOKEN_INTEGER_VALUE ||
        p->current_token->type == TOKEN_STRING_VALUE
    ) {
        return parser_parse_expr(p, s);
    }

    if (p->current_token->type == TOKEN_FUNCTION_TYPE)
        return (AST*) parser_parse_function_definition(p, s);

    if (p->current_token->type == TOKEN_LET) {
        parser_eat(p, TOKEN_LET);
        return (AST*) parser_parse_variable_definition(p, s);
    }

    if (p->current_token->type == TOKEN_IF) {
        return (AST*) parser_parse_if(p, s);
    }

    if (p->current_token->type == TOKEN_CLASS_TYPE) {
        return (AST*) parser_parse_class(p, s);
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
AST* parser_parse_expr(parser* p, scope* s) {
    AST* node = parser_parse_term(p, s);

    token* t = (void*) 0;

    while (
        p->current_token->type == TOKEN_PLUS ||
        p->current_token->type == TOKEN_EQUALS_EQUALS ||
        p->current_token->type == TOKEN_NOT_EQUALS ||
        p->current_token->type == TOKEN_EQUALS
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

        else if (p->current_token->type == TOKEN_EQUALS) {
            parser_eat(p, TOKEN_EQUALS);
            AST* x = (AST*) init_ast_assignment(t, node, parser_parse_expr(p, s));
            return x;
        }

        node = (AST*) init_ast_binop(t, node, parser_parse_term(p, s));
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
AST* parser_parse_term(parser* p, scope* s) {
    AST* node = parser_parse_factor(p, s);

    token* t = (void*) 0;

    while (p->current_token->type == TOKEN_DIVIDE || p->current_token->type == TOKEN_MULTIPLY) {
        t = p->current_token;

        if (p->current_token->type == TOKEN_DIVIDE) {
            parser_eat(p, TOKEN_DIVIDE);
        } else if (p->current_token->type == TOKEN_MULTIPLY) {
            parser_eat(p, TOKEN_MULTIPLY);
        }

        node = (AST*) init_ast_binop(t, node, parser_parse_factor(p, s));
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
AST* parser_parse_factor(parser* p, scope* s) {
    token* t = p->current_token;

    if (t->type == TOKEN_INTEGER_VALUE) {
        parser_eat(p, TOKEN_INTEGER_VALUE);
        return (AST*) init_ast_integer(t);
    }

    if (t->type == TOKEN_LPAREN) {
        parser_eat(p, TOKEN_LPAREN);
        AST* expr = parser_parse_expr(p, s);
        parser_eat(p, TOKEN_RPAREN);

        return expr;
    }

    if (t->type == TOKEN_FUNCTION_TYPE) {
        return (AST*) parser_parse_function_definition(p, s);
    }

    if (t->type == TOKEN_ID) {
         AST* left = parser_parse_id(p, s);

         if (p->current_token->type == TOKEN_DOT) {
            parser_eat(p, TOKEN_DOT);

            AST* right = parser_parse_expr(p, s);

            return (AST*) init_ast_attribute_access(t, left, right);
         }

         return (AST*) left;
    }

    if (t->type == TOKEN_STRING_VALUE) {
        parser_eat(p, TOKEN_STRING_VALUE);
        return (AST*) init_ast_string(t);
    }

    if (t->type == TOKEN_NULL_TYPE) {
        parser_eat(p, TOKEN_NULL_TYPE);
        return (AST*) init_ast_null(t);
    }

    if (t->type == TOKEN_UNDEFINED_TYPE) {
        parser_eat(p, TOKEN_UNDEFINED_TYPE);
        return (AST*) init_ast_undefined(t);
    }

    if (t->type == TOKEN_NEW) {
        return (AST*) parser_parse_object_init(p, s);
    }

    return parser_parse_expr(p, s);
}

AST* parser_parse_id(parser* p, scope* s) {
    token* t = p->current_token;
    parser_eat(p, TOKEN_ID);

    if (p->current_token->type == TOKEN_LPAREN)
        return (AST*) parser_parse_function_call(p, s, t);

    return (AST*) init_ast_variable(t);
}

AST_function_call* parser_parse_function_call(parser* p, scope* s, token* t) {
    char* name = t->value;
    dynamic_list* args = init_dynamic_list(sizeof(struct AST_STRUCT));
    parser_eat(p, TOKEN_LPAREN);
    AST* expr = (void*) 0;

    if (p->current_token->type != TOKEN_RPAREN) {
        expr = parser_parse_expr(p, s);
        dynamic_list_append(args, expr);
        
        while (p->current_token->type == TOKEN_COMMA) {
            parser_eat(p, TOKEN_COMMA);
            expr = parser_parse_expr(p, s); 
            dynamic_list_append(args, expr);
        }
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
AST_function_definition* parser_parse_function_definition(parser* p, scope* s) {
    parser_eat(p, TOKEN_FUNCTION_TYPE);
    dynamic_list* args = init_dynamic_list(sizeof(struct AST_VARIABLE_DEFINITION_STRUCT));
    char* name = p->current_token->value;
    parser_eat(p, TOKEN_ID);
    parser_eat(p, TOKEN_LPAREN);

    if (p->current_token->type == TOKEN_ID) {
        AST_variable_definition* definition = parser_parse_variable_definition(p, s);
        dynamic_list_append(args, definition);

        while (p->current_token->type == TOKEN_COMMA) {
            parser_eat(p, TOKEN_COMMA);
            definition = parser_parse_variable_definition(p, s); 
            dynamic_list_append(args, definition);
        }
    }

    parser_eat(p, TOKEN_RPAREN);

    AST_datatype* datatype = (void*) 0;

    if (p->current_token->type == TOKEN_COLON) {
        parser_eat(p, TOKEN_COLON);
        datatype = parser_parse_data_type(p, s);
    }

    parser_eat(p, TOKEN_LBRACE);
    AST_compound* compound = parser_parse_compound(p, s);
    parser_eat(p, TOKEN_RBRACE);

    AST_function_definition* fd = init_ast_function_definition(p->current_token, name, args, compound, datatype);
    ((AST*) fd)->s = (struct scope*) s;

    // if the owner is a class and the parsed function definition name is
    // "constructor", then set the pointer on the class definition.
    if (s->owner) {
        if (s->owner->type == AST_CLASS) {
            AST_class* class_parent = (AST_class*) s->owner;

            if (strcmp(name, "constructor")) {
                class_parent->constructor_function_definition = fd;
            }
        }
    }

    return fd;
}

/**
 * Parses a variable definition
 *
 * @param parser* p
 *
 * @return AST_variable_definition*
 */
AST_variable_definition* parser_parse_variable_definition(parser* p, scope* s) {
    AST* left = parser_parse_expr(p, s);
    AST* value = (void*) 0;
    AST_datatype* datatype = (void*) 0;

    if (p->current_token->type == TOKEN_COLON) {
        parser_eat(p, TOKEN_COLON);

        datatype = parser_parse_data_type(p, s);
    }

    if (p->current_token->type == TOKEN_EQUALS) {
        parser_eat(p, TOKEN_EQUALS);
        value = parser_parse_expr(p, s);
    }

    return init_ast_variable_definition(p->current_token, left, value, datatype);
}

/**
 * Parses a datatype
 *
 * @param parser* p
 *
 * @return AST_datatype*
 */
AST_datatype* parser_parse_data_type(parser* p, scope* s) {
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
        break;
        case TOKEN_UNDEFINED_TYPE:
            parser_eat(p, TOKEN_UNDEFINED_TYPE);
        break;
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

AST_if* parser_parse_if(parser* p, scope* s) {
    AST* expr = (void*) 0;
    AST_if* otherwise = (void*) 0;

    if (p->current_token->type == TOKEN_IF) {
        parser_eat(p, TOKEN_IF);
        parser_eat(p, TOKEN_LPAREN);
        expr = parser_parse_expr(p, s);
        parser_eat(p, TOKEN_RPAREN);
    }

    parser_eat(p, TOKEN_LBRACE);
    AST_compound* compound = parser_parse_compound(p, s);
    parser_eat(p, TOKEN_RBRACE);

    if (p->current_token->type == TOKEN_ELSE) {
        parser_eat(p, TOKEN_ELSE);
        otherwise = parser_parse_if(p, s);
    }

    return init_ast_if(p->current_token, expr, compound, otherwise);
}

AST_class* parser_parse_class(parser* p, scope* s) {
    AST_class* class_ptr = (void*) 0;

    scope* class_scope = init_scope((AST*) &class_ptr);

    parser_eat(p, TOKEN_CLASS_TYPE);
    char* name = p->current_token->value;
    parser_eat(p, TOKEN_ID);
    parser_eat(p, TOKEN_LBRACE);
    dynamic_list* variable_definitions = init_dynamic_list(sizeof(struct AST_FUNCTION_DEFINITION_STRUCT));
    dynamic_list* function_definitions = init_dynamic_list(sizeof(struct AST_FUNCTION_DEFINITION_STRUCT));
    
    if (p->current_token->type == TOKEN_FUNCTION_TYPE) {
        dynamic_list_append(function_definitions, parser_parse_function_definition(p, class_scope));
    }

    while (p->current_token->type == TOKEN_SEMI) {
        parser_eat(p, TOKEN_SEMI);

        if (p->current_token->type == TOKEN_FUNCTION_TYPE) {
            dynamic_list_append(function_definitions, parser_parse_function_definition(p, class_scope));
        }
    }

    parser_eat(p, TOKEN_RBRACE);

    class_ptr = init_ast_class(p->current_token, name, (void*)0, function_definitions);
    class_scope->owner = (AST*) class_ptr;

    return class_ptr;
}

AST_object_init* parser_parse_object_init(parser* p, scope* s) {
    parser_eat(p, TOKEN_NEW);
    token* t = p->current_token;
    parser_eat(p, TOKEN_ID);
    AST_function_call* fc = parser_parse_function_call(p, s, t);

    return init_ast_object_init(p->current_token, fc);
}
