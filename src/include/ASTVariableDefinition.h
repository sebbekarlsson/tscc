#ifndef TSCC_AST_VARIABLE_DEFINITION_H
#define TSCC_AST_VARIABLE_DEFINITION_H
#include "AST.h"
#include "ASTDatatype.h"

typedef struct AST_VARIABLE_DEFINITION_STRUCT {
    AST base;
    AST* left;
    AST* value;
    AST_datatype* datatype;
} AST_variable_definition;

AST_variable_definition* init_ast_variable_definition(token* t, AST* left, AST* value, AST_datatype* datatype);
#endif
