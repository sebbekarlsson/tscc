#ifndef TSCC_AST_INTEGER_H
#define TSCC_AST_INTEGER_H
#include "AST.h"

typedef struct AST_INTEGER_STRUCT {
    AST base;
} AST_integer;

AST_integer* init_ast_integer(token* t);
#endif
