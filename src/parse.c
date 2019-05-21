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
    }
    else {
        p->current_token = lexer_get_next_token(p->l);
    }
}

/**
 * Checks if the current token is expected and then fetches
 * the next token without returning an error if mismatch
 *
 * @param parser* p
 * @param int token_type
 */
void parser_consume(parser* p, int token_type) {
    if (p->current_token->type == token_type) {
        p->current_token = lexer_get_next_token(p->l);
    }
}

/**
 * Main entry point for the parser
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST_compound*
 */
AST_compound* parser_parse(parser* p, scope* s) {
    return parser_parse_body(p, s); //parser_parse_compound(p, s);
}

/**
 * Parses a compound
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST_compound*
 */
AST_compound* parser_parse_compound(parser* p, scope* s) {
    dynamic_list* children = init_dynamic_list(sizeof(AST*));

    AST* statement = parser_parse_statement(p, s);
    dynamic_list_append(children, statement);

    while (p->current_token->type == TOKEN_SEMI || p->current_token->type == TOKEN_COMMA) {
        if (p->current_token->type == TOKEN_SEMI)
            parser_eat(p, TOKEN_SEMI);
        else
            parser_eat(p, TOKEN_COMMA);

        statement = parser_parse_statement(p, s);
        dynamic_list_append(children, statement);
    }

    return init_ast_compound(p->current_token, children);
}

/**
 * Parses a statement body expecting a RBRace to end the body parsing
 *
 * @param paraser* p
 * @param scope* s
 */
AST_compound* parser_parse_body(parser* p, scope* s) {
    dynamic_list* children = init_dynamic_list(sizeof(AST*));

    if (p->current_token->type != TOKEN_SEMI && // if semicolon, body is empty
        p->current_token->type != TOKEN_RBRACE) {
        AST* statement = parser_parse_statement(p, s);
        dynamic_list_append(children, statement);

        while (p->current_token->type != TOKEN_RBRACE && p->current_token->type != TOKEN_EOF) {
            parser_consume(p, TOKEN_SEMI);
            statement = parser_parse_statement(p, s);
            if (statement == 0) {
                break;
            }
            dynamic_list_append(children, statement);
        }
    }

    // consume and ignore
    if (p->current_token->type == TOKEN_SEMI)
        parser_consume(p, TOKEN_SEMI);

    return init_ast_compound(p->current_token, children);
}


/**
 * Parses a statement
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST*
 */
AST* parser_parse_statement(parser* p, scope* s) {
    if (
        p->current_token->type == TOKEN_ID ||
        p->current_token->type == TOKEN_INTEGER_VALUE ||
        p->current_token->type == TOKEN_FLOAT_VALUE ||
        p->current_token->type == TOKEN_STRING_VALUE ||
        p->current_token->type == TOKEN_LPAREN
        ) {
        return parser_parse_expr(p, s);
    }

    if (p->current_token->type == TOKEN_FUNCTION_TYPE)
        return (AST*)parser_parse_function_definition(p, s);

    if (p->current_token->type == TOKEN_LET) {
        parser_eat(p, TOKEN_LET);
        return (AST*)parser_parse_variable_definition(p, s);
    }

    if (p->current_token->type == TOKEN_VAR || p->current_token->type == TOKEN_COMMA) {
        if (p->current_token->type == TOKEN_VAR)
            parser_eat(p, TOKEN_VAR);
        else
            parser_eat(p, TOKEN_COMMA);

        return (AST*)parser_parse_variable_definition(p, s);
    }

    if (p->current_token->type == TOKEN_IF) {
        return (AST*)parser_parse_if(p, s);
    }

    if (p->current_token->type == TOKEN_CLASS_TYPE) {
        return (AST*)parser_parse_class(p, s);
    }

    if (p->current_token->type == TOKEN_WHILE) {
        return (AST*)parser_parse_while(p, s);
    }
    if (p->current_token->type == TOKEN_FOR) {
        return (AST*)parser_parse_for(p, s);
    }
    if (p->current_token->type == TOKEN_RETURN) {
        return (AST*)parser_parse_return(p, s);
    }
    if (p->current_token->type == TOKEN_COMMENT_VALUE) {
        AST* a = (AST*)init_ast_comment(p->current_token);
        parser_eat(p, TOKEN_COMMENT_VALUE);
        return a;
    }

    return (void*)0;
}

/**
 * Parses an expression
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST*
 */
AST* parser_parse_expr(parser* p, scope* s) {
    AST* node = parser_parse_term(p, s);

    token* t = (void*)0;

    while (
        p->current_token->type == TOKEN_PLUS ||
        p->current_token->type == TOKEN_MINUS ||
        p->current_token->type == TOKEN_EQUALS_EQUALS ||
        p->current_token->type == TOKEN_NOT_EQUALS ||
        p->current_token->type == TOKEN_EQUALS ||
        p->current_token->type == TOKEN_LESS_THAN ||
        p->current_token->type == TOKEN_LARGER_THAN
        ) {
        t = p->current_token;

        if (p->current_token->type == TOKEN_PLUS) {
            parser_eat(p, TOKEN_PLUS);
        }
        if (p->current_token->type == TOKEN_MINUS) {
            parser_eat(p, TOKEN_MINUS);
        }
        else if (p->current_token->type == TOKEN_EQUALS_EQUALS) {
            parser_eat(p, TOKEN_EQUALS_EQUALS);
        }

        else if (p->current_token->type == TOKEN_NOT_EQUALS) {
            parser_eat(p, TOKEN_NOT_EQUALS);
        }

        else if (p->current_token->type == TOKEN_LESS_THAN) {
            parser_eat(p, TOKEN_LESS_THAN);
        }

        else if (p->current_token->type == TOKEN_LARGER_THAN) {
            parser_eat(p, TOKEN_LARGER_THAN);
        }

        else if (p->current_token->type == TOKEN_EQUALS) {
            parser_eat(p, TOKEN_EQUALS);
            return (AST*)init_ast_assignment(t, node, parser_parse_expr(p, s));
        }

        node = (AST*)init_ast_binop(t, node, parser_parse_term(p, s));
    }

    return node;
}

/**
 * Parses division, multiplication
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST*
 */
AST* parser_parse_term(parser* p, scope* s) {
    AST* node = parser_parse_factor(p, s);

    token* t = (void*)0;
    while (p->current_token->type == TOKEN_DIVIDE || p->current_token->type == TOKEN_MULTIPLY) {
        t = p->current_token;

        if (p->current_token->type == TOKEN_DIVIDE) {
            parser_eat(p, TOKEN_DIVIDE);
        }
        else if (p->current_token->type == TOKEN_MULTIPLY) {
            parser_eat(p, TOKEN_MULTIPLY);
        }

        node = (AST*)init_ast_binop(t, node, parser_parse_factor(p, s));
    }

    return node;
}

/**
 * Parses factorial, integers, numbers, functions, objects etc. (values?)
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST*
 */
AST* parser_parse_factor(parser* p, scope* s) {
    token* t = p->current_token;

    if (t->type == TOKEN_INTEGER_VALUE) {
        parser_eat(p, TOKEN_INTEGER_VALUE);
        return (AST*)init_ast_integer(t);
    }

    if (t->type == TOKEN_FLOAT_VALUE) {
        parser_eat(p, TOKEN_FLOAT_VALUE);
        return (AST*)init_ast_float(t);
    }

    if (t->type == TOKEN_LPAREN) {
        parser_eat(p, TOKEN_LPAREN);
        AST* expr = parser_parse_expr(p, s);
        parser_eat(p, TOKEN_RPAREN);

        return expr;
    }

    if (t->type == TOKEN_FUNCTION_TYPE) {
        return (AST*)parser_parse_function_definition(p, s);
    }

    if (t->type == TOKEN_ID) {
        AST* left = parser_parse_id(p, s);

        if (p->current_token->type == TOKEN_DOT) {
            parser_eat(p, TOKEN_DOT);

            AST* right = parser_parse_expr(p, s);

            return (AST*)init_ast_attribute_access(t, left, right);
        }

        return (AST*)left;
    }

    if (t->type == TOKEN_STRING_VALUE) {
        parser_eat(p, TOKEN_STRING_VALUE);
        return (AST*)init_ast_string(t);
    }

    if (t->type == TOKEN_NULL_TYPE) {
        parser_eat(p, TOKEN_NULL_TYPE);
        return (AST*)init_ast_null(t);
    }

    if (t->type == TOKEN_UNDEFINED_TYPE) {
        parser_eat(p, TOKEN_UNDEFINED_TYPE);
        return (AST*)init_ast_undefined(t);
    }

    if (t->type == TOKEN_NEW) {
        return (AST*)parser_parse_object_init(p, s);
    }

    if (t->type == TOKEN_LBRACKET) {
        return (AST*)parser_parse_array(p, s);
    }

    if (t->type == TOKEN_COMMENT_VALUE) {
        parser_eat(p, TOKEN_COMMENT_VALUE);
    }

    return parser_parse_expr(p, s);
}

AST* parser_parse_id(parser* p, scope* s) {
    token* t = p->current_token;
    parser_eat(p, TOKEN_ID);

    if (p->current_token->type == TOKEN_LPAREN)
        return (AST*)parser_parse_function_call(p, s, t);

    return (AST*)init_ast_variable(t);
}

AST_return* parser_parse_return(parser* p, scope* s) {
    parser_eat(p, TOKEN_RETURN);
    token* t = p->current_token;
    AST* statement;

    if (t->type != TOKEN_SEMI) {
        statement = (AST*)parser_parse_statement(p, s);
    }

    return init_ast_return(t, statement);
}

/**
 * Parses a function call
 *
 * @param parser* p
 * @param scope* s
 * @param token* t
 *
 * @return AST_function_call*
 */
AST_function_call* parser_parse_function_call(parser* p, scope* s, token* t) {
    char* name = t->value;
    dynamic_list* args = init_dynamic_list(sizeof(struct AST_STRUCT));
    parser_eat(p, TOKEN_LPAREN);
    AST* expr = (void*)0;

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
 * @param scope* s
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

    AST_datatype* datatype = (void*)0;

    if (p->current_token->type == TOKEN_COLON) {
        parser_eat(p, TOKEN_COLON);
        datatype = parser_parse_data_type(p, s);
    }

    parser_eat(p, TOKEN_LBRACE);
    //AST_compound* compound = parser_parse_compound(p, s);
    AST_compound* compound = parser_parse_body(p, s);
    parser_eat(p, TOKEN_RBRACE);

    AST_function_definition* fd = init_ast_function_definition(p->current_token, name, args, compound, datatype);
    ((AST*)fd)->s = (struct scope*) s;

    // if the owner is a class and the parsed function definition name is
    // "constructor", then set the pointer on the class definition.
    if (s->owner) {
        if (s->owner->type == AST_CLASS) {
            AST_class* class_parent = (AST_class*)s->owner;

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
 * @param scope* s
 *
 * @return AST_variable_definition*
 */
AST_variable_definition* parser_parse_variable_definition(parser* p, scope* s) {

    // note(Kalle): parser_parse_expr will return an assignment expression if an TOKEN_EQUALS is found without a type definition
    AST* left = parser_parse_expr(p, s);
    AST* value = (void*)0;
    AST_datatype* datatype = (void*)0;
    
    // take apart the assignment statement for "any" type definitions
    if (left->type == AST_ASSIGNMENT) {
        AST_assignment* assignment = (AST_assignment*)left;
        left = assignment->left;
        value = assignment->right;
        // todo(kalle): you would need to try and solve the type here
        //              or it will throw a node->datatype was nullptr in the output
        datatype = parser_solve_data_type(p, s, value);
    }

    
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
 * @param scope* s
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
    case TOKEN_i32_TYPE:
        parser_eat(p, TOKEN_i32_TYPE);
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

AST_datatype* parser_solve_data_type(parser* p, scope* s, AST* statement) {
    token* t = p->current_token;
    if (t->type == TOKEN_COLON) {
        parser_eat(p, TOKEN_COLON);
        return parser_parse_data_type(p, s);
    }

    // note(kalle): super stupid check for now. But would need to evalute the statement to get a return type         
    if (statement->type == AST_BINOP ||
        statement->type == AST_INTEGER ||
        statement->type == AST_FLOAT ||
        statement->type == AST_STRING) {

        int isList = 0;
        int type = TOKEN_FLOAT_VALUE;
        char* type_name = "number";

        // AST_FLOAT: default
        if (statement->type == AST_BINOP) {
            type = TOKEN_INTEGER_TYPE;
        }

        if (statement->type == AST_INTEGER) {
            type = TOKEN_INTEGER_TYPE;
        }

        if (statement->type == AST_STRING) {
            type = TOKEN_STRING_TYPE;
            type_name = "string";
        }

        if (statement->type == AST_ARRAY) {
            isList = 1;
            type_name = "[]";
            // defaults to integer.
            type = TOKEN_INTEGER_TYPE;
        }

        // note(kalle): urgh, would need a separate parameter that sets the type rather than on the token
        return init_ast_datatype(init_token(type, type_name), isList);
    }

    return init_ast_datatype(init_token(TOKEN_VOID_POINTER_TYPE, "void"), 0);
}

/**
 * Parses an if-else statement
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST_if*
 */
AST_if* parser_parse_if(parser* p, scope* s) {
    AST* expr = (void*)0;
    AST_if* otherwise = (void*)0;

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

/**
 * Parses a class
 *
 * @param parser* p
 * @param scope* s
 */
AST_class* parser_parse_class(parser* p, scope* s) {
    AST_class* class_ptr = (void*)0;

    scope* class_scope = init_scope((AST*)&class_ptr);

    parser_eat(p, TOKEN_CLASS_TYPE);
    char* name = p->current_token->value;
    parser_eat(p, TOKEN_ID);
    parser_eat(p, TOKEN_LBRACE);
    dynamic_list* variable_definitions = init_dynamic_list(sizeof(struct AST_FUNCTION_DEFINITION_STRUCT));
    dynamic_list* function_definitions = init_dynamic_list(sizeof(struct AST_FUNCTION_DEFINITION_STRUCT));

    if (p->current_token->type == TOKEN_FUNCTION_TYPE) {
        dynamic_list_append(function_definitions, parser_parse_function_definition(p, class_scope));
    }

    if (p->current_token->type == TOKEN_ID) {
        dynamic_list_append(variable_definitions, parser_parse_variable_definition(p, class_scope));
    }

    while (p->current_token->type == TOKEN_SEMI) {
        parser_eat(p, TOKEN_SEMI);

        if (p->current_token->type == TOKEN_FUNCTION_TYPE) {
            dynamic_list_append(function_definitions, parser_parse_function_definition(p, class_scope));
        }

        if (p->current_token->type == TOKEN_ID) {
            dynamic_list_append(variable_definitions, parser_parse_variable_definition(p, class_scope));
        }
    }

    parser_eat(p, TOKEN_RBRACE);

    class_ptr = init_ast_class(p->current_token, name, variable_definitions, function_definitions);
    class_scope->owner = (AST*)class_ptr;

    return class_ptr;
}

/**
 * Parses an object initialization
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST_object_init*
 */
AST_object_init* parser_parse_object_init(parser* p, scope* s) {
    parser_eat(p, TOKEN_NEW);
    token* t = p->current_token;
    parser_eat(p, TOKEN_ID);
    AST_function_call* fc = parser_parse_function_call(p, s, t);

    return init_ast_object_init(p->current_token, fc);
}

/**
 * Parses a while statement
 *
 * @param parser* p
 * @param scope* s
 *
 * @return AST_while*
 */
AST_while* parser_parse_while(parser* p, scope* s) {
    parser_eat(p, TOKEN_WHILE);
    parser_eat(p, TOKEN_LPAREN);
    AST* expr = parser_parse_expr(p, s);
    parser_eat(p, TOKEN_RPAREN);
    parser_eat(p, TOKEN_LBRACE);
    AST_compound* compound = parser_parse_compound(p, s);
    parser_eat(p, TOKEN_RBRACE);

    return init_ast_while(p->current_token, expr, compound);
}

AST_array* parser_parse_array(parser* p, scope* s) {
    parser_eat(p, TOKEN_LBRACKET);
    AST_datatype* datatype = (void*)0;
    dynamic_list* elements = init_dynamic_list(sizeof(AST*));

    if (p->current_token->type != TOKEN_RBRACKET) {
        dynamic_list_append(elements, parser_parse_expr(p, s));
    }

    while (p->current_token->type == TOKEN_COMMA) {
        parser_eat(p, TOKEN_COMMA);
        dynamic_list_append(elements, parser_parse_expr(p, s));
    }

    parser_eat(p, TOKEN_RBRACKET);

    return init_ast_array(p->current_token, datatype, elements);
}

AST_for* parser_parse_for(parser* p, scope* s) {
    parser_eat(p, TOKEN_FOR);
    parser_eat(p, TOKEN_LPAREN);
    dynamic_list* expressions = init_dynamic_list(sizeof(struct AST_STRUCT));

    AST* expr = parser_parse_statement(p, s);

    if (expr)
        dynamic_list_append(expressions, expr);

    while (p->current_token->type == TOKEN_SEMI) {
        parser_eat(p, TOKEN_SEMI);
        
        AST* e = parser_parse_statement(p, s);

        if (e)
            dynamic_list_append(expressions, e);
    }

    parser_eat(p, TOKEN_RPAREN);
    parser_eat(p, TOKEN_LBRACE);
    AST_compound* compound = parser_parse_compound(p, s);
    parser_eat(p, TOKEN_RBRACE);

    return init_ast_for(p->current_token, expressions, compound);
}
