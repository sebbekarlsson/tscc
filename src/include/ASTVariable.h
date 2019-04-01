#ifndef TSCC_AST_VARIABLE_H
#define TSCC_AST_VARIABLE_H
#include "AST.h"

typedef struct AST_VARIABLE_STRUCT {
    AST base;
} AST_variable;

AST_variable* init_ast_variable(token* t);
#endif
