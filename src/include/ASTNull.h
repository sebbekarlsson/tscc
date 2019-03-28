#ifndef TSCC_AST_NULL_H
#define TSCC_AST_NULL_H
#include "AST.h"

typedef struct AST_NULL_STRUCT {
    AST base;
} AST_null;

AST_null* init_ast_null(token* t);
#endif
