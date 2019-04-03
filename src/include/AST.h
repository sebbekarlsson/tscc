#ifndef TSCC_AST_H
#define TSCC_AST_H
#include "token.h"

typedef struct AST_STRUCT {
    enum {
        AST_BINOP,
        AST_VARIABLE,
        AST_INTEGER,
        AST_FLOAT,
        AST_STRING,
        AST_COMPOUND,
        AST_DATATYPE,
        AST_FUNCTION_DEFINITION,
        AST_VARIABLE_DEFINITION,
        AST_FUNCTION_CALL,
        AST_IF,
        AST_NULL,
        AST_UNDEFINED,
        AST_CLASS,
        AST_OBJECT_INIT,
        AST_ATTRIBUTE_ACCESS,
        AST_ASSIGNMENT,
        AST_WHILE,
        AST_ARRAY
    } type;

    token* token;
    struct scope* s;
} AST;

void AST_constructor(AST* ast, token* t, int type);
#endif
